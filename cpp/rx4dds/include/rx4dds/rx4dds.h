#pragma once 

#include <dds/sub/ddssub.hpp>
#include <dds/core/ddscore.hpp>

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <functional>

#include "rxcpp/rx.hpp"

namespace std
{
  template <>
  struct hash<dds::core::InstanceHandle>
  {
  private:
    std::string handle_;

  public:
    hash()
    {
      handle_.resize(64);
    }

    std::size_t operator()(const dds::core::InstanceHandle& ihandle) const
    {
      std::ostringstream out(handle_);
      out << ihandle;
      return std::hash<std::string>()(handle_);
    }
  };

  
  template <>
  struct hash<dds::core::string>
  {
    std::size_t operator()(const dds::core::string& str) const
    {
      return std::hash<const char *>()(str.c_str());
    }

  };

} // namespace std

namespace dds {
  namespace core {

    bool operator < (const dds::core::string & lhs, const dds::core::string & rhs)
    {
      return strcmp(lhs.c_str(), rhs.c_str()) < 0;
    }

  } // namespace core
} // namespace dds

namespace rx4dds {

  class NotAliveNoWriters : std::runtime_error
  {
    public:
      explicit NotAliveNoWriters(const std::string& what_arg)
        : std::runtime_error(what_arg)
      { }

      explicit NotAliveNoWriters(const char* what_arg)
        : std::runtime_error(what_arg)
      { }
  };

  namespace detail {

    template <class T>
    class KeyLessSubscription
    {
    private:
      struct SubscriptionState
      {
        bool initdone_;
        dds::domain::DomainParticipant participant_;
        std::string topic_name_;
        dds::topic::Topic<T> topic_;
        dds::sub::DataReader<T> reader_;
        dds::core::cond::WaitSet wait_set_;
        dds::sub::cond::ReadCondition read_condition_;
        rxcpp::schedulers::worker worker_;

        SubscriptionState(dds::domain::DomainParticipant part,
          const std::string & topic_name,
          dds::core::cond::WaitSet wait_set,
          rxcpp::schedulers::worker worker)
          : initdone_(false),
          participant_(part),
          topic_name_(topic_name),
          topic_(dds::core::null),
          reader_(dds::core::null),
          wait_set_(wait_set),
          read_condition_(dds::core::null),
          worker_(worker)
        { }

        ~SubscriptionState()
        {
          if (initdone_)
            wait_set_ -= read_condition_;
        }
      };

      std::shared_ptr<SubscriptionState> state_;

    public:
      KeyLessSubscription(dds::domain::DomainParticipant part,
        const std::string & topic_name,
        dds::core::cond::WaitSet wait_set,
        rxcpp::schedulers::worker worker)
        : state_(std::make_shared<SubscriptionState>(
        part, topic_name, wait_set, worker))
      { }

      void initialize_once(rxcpp::subjects::subject<rti::sub::LoanedSample<T>> subject)
      {
        if (!state_->initdone_)
        {
          state_->topic_ =
            dds::topic::Topic<T>(state_->participant_, state_->topic_name_);

          state_->reader_ = dds::sub::DataReader<ShapeTypeExtended>(
            dds::sub::Subscriber(state_->participant_),
            state_->topic_);

          typename rxcpp::subjects::subject<rti::sub::LoanedSample<T>>::subscriber_type subscriber =
            subject.get_subscriber();

          auto schedule_dr_subscription_end = [this]()
          {
            state_->worker_.schedule(
              rxcpp::schedulers::make_schedulable(
              state_->worker_,
              [this](const rxcpp::schedulers::schedulable &) {
              state_.reset();
            }));
          };

          state_->read_condition_ =
            dds::sub::cond::ReadCondition(
            state_->reader_,
            dds::sub::status::DataState::any(),
            [this, subscriber, schedule_dr_subscription_end]()
            {
              try {
                dds::sub::LoanedSamples<ShapeTypeExtended> samples =
                  state_->reader_.take();

                for (auto sample : samples)
                {
                  dds::sub::status::InstanceState istate;
                  sample.info().state() >> istate;

                  if (sample.info().valid())
                  {
                    // RxCpp documentation suggests that the following check is 
                    // is a good practice. See docs for rxcpp::observable<void,void>
                    if(subscriber.is_subscribed())
                      subscriber.on_next(sample);
                  }
                  else if (istate == dds::sub::status::InstanceState::not_alive_no_writers())
                  {
                    /*subscriber.on_error(
                      std::make_exception_ptr(
                      NotAliveNoWriters("No alive writers for topic = " + state_->topic_name_)));
                      schedule_dr_subscription_end();*/
                    if (subscriber.is_subscribed())
                      subscriber.on_next(sample);
                  }
                  else if (istate == dds::sub::status::InstanceState::not_alive_disposed())
                  {
                    subscriber.on_completed();
                    schedule_dr_subscription_end();
                    break;
                  }
                }
              }
              catch (...)
              {
                subscriber.on_error(std::current_exception());                
                schedule_dr_subscription_end();
              }
            });

          state_->wait_set_ += state_->read_condition_;
          state_->initdone_ = true;
        }
      }

    };

    template <class Key, class T, class KeySelector>
    class KeyedSubscription
    {
    private:
      typedef rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>> GroupedObservable;

      class Bucket 
      {
        rxcpp::subjects::subject<rti::sub::LoanedSample<T>> subject_;
        rxcpp::composite_subscription subscription_;

      public:

        Bucket() {}

        Bucket(Key key, 
               rxcpp::subjects::subject<GroupedObservable> topsubject)
        { 
          subscription_ =
            subject_
            .get_observable()
            .group_by([key](rti::sub::LoanedSample<T> sample) { 
                        return key;
                      },
                      [](rti::sub::LoanedSample<T> sample) { return sample; })
            .map([topsubject](GroupedObservable go) {
                   const_cast<rxcpp::subjects::subject<GroupedObservable> &>(topsubject).get_subscriber().on_next(go);
                   return 0;
          }).subscribe();
        }

        rxcpp::subjects::subject<rti::sub::LoanedSample<T>> & get_subject()
        {
          return subject_;
        }
        
        const Key & get_key() const
        {
          return key_;
        }
      };

      typedef std::unordered_map<dds::core::InstanceHandle, Bucket> BucketMap;

      struct SubscriptionState
      {
        bool initdone_;
        dds::domain::DomainParticipant participant_;
        std::string topic_name_;
        dds::topic::Topic<T> topic_;
        dds::sub::DataReader<T> reader_;
        dds::core::cond::WaitSet wait_set_;
        dds::sub::cond::ReadCondition read_condition_;
        rxcpp::schedulers::worker worker_;
        BucketMap buckets_;
        KeySelector key_selector_;

        SubscriptionState(dds::domain::DomainParticipant part,
                          const std::string & topic_name,
                          dds::core::cond::WaitSet wait_set,
                          rxcpp::schedulers::worker worker,
                          KeySelector&& key_selector)
          : initdone_(false),
            participant_(part),
            topic_name_(topic_name),
            topic_(dds::core::null),
            reader_(dds::core::null),
            wait_set_(wait_set),
            read_condition_(dds::core::null),
            worker_(worker),
            key_selector_(std::move(key_selector))
        { }

        ~SubscriptionState()
        {
          if (initdone_)
            wait_set_ -= read_condition_;
        }
      };

      std::shared_ptr<SubscriptionState> state_;

    public:
      KeyedSubscription(dds::domain::DomainParticipant part,
                        const std::string & topic_name,
                        dds::core::cond::WaitSet wait_set,
                        rxcpp::schedulers::worker worker,
                        KeySelector key_selector)
        : state_(std::make_shared<SubscriptionState>(
                    part, topic_name, wait_set, worker, std::move(key_selector)))
      { }

      void initialize_once(rxcpp::subjects::subject<GroupedObservable> topsubject)
      {
        if (!state_->initdone_)
        {
          state_->topic_ =
            dds::topic::Topic<T>(state_->participant_, state_->topic_name_);

          state_->reader_ = dds::sub::DataReader<ShapeTypeExtended>(
            dds::sub::Subscriber(state_->participant_),
            state_->topic_);

          auto schedule_dr_subscription_end = [this]()
          {
            state_->worker_.schedule(
              rxcpp::schedulers::make_schedulable(
              state_->worker_,
              [this](const rxcpp::schedulers::schedulable &) {
                state_.reset();
            }));
          };

          state_->read_condition_ =
            dds::sub::cond::ReadCondition(
            state_->reader_,
            dds::sub::status::DataState::any(),
            [this, topsubject, schedule_dr_subscription_end]() mutable
          {
            try {
              dds::sub::LoanedSamples<ShapeTypeExtended> samples =
                state_->reader_.take();

              for (auto sample : samples)
              {
                dds::sub::status::InstanceState istate; 
                sample.info().state() >> istate;
                dds::core::InstanceHandle handle = sample.info().instance_handle();
                BucketMap::const_iterator got = state_->buckets_.find(handle);

                if (sample.info().valid()) 
                {
                  if (got != state_->buckets_.end()) // instance exists
                  {
                    state_->buckets_[handle].get_subject()
                                            .get_subscriber()
                                            .on_next(sample);
                  }
                  else // new instance 
                  {
                    state_->buckets_.emplace(
                      std::make_pair(handle, Bucket(state_->key_selector_(sample.data()), topsubject)));

                    // A new grouped_observable is pushed through 
                    // topsubject before sample.data.
                    state_->buckets_[handle].get_subject().get_subscriber().on_next(sample);
                  }
                }
                else if (istate == dds::sub::status::InstanceState::not_alive_disposed())
                {
                  if (got != state_->buckets_.end()) // instance exists
                  {
                    state_->buckets_[handle].get_subject()
                                            .get_subscriber()
                                            .on_completed();
                    
                    state_->buckets_.erase(handle);
                  }
                  else
                  {
                    throw std::runtime_error("Instance should really exist at this point");
                  }
                }
                else if (istate == dds::sub::status::InstanceState::not_alive_no_writers())
                {
                  if (got != state_->buckets_.end()) // instance exists
                  {
                    state_->buckets_[handle]
                          .get_subject()
                          .get_subscriber()
                          .on_next(sample);

                    state_->buckets_.erase(handle);
                  }
                  else
                  {
                    throw std::runtime_error("Instance should really exist at this point");
                  }                    
                }
                
              }
            }
            catch (...)
            {
              topsubject.get_subscriber().on_error(std::current_exception());
              schedule_dr_subscription_end();
            }
          });

          state_->wait_set_ += state_->read_condition_;
          state_->initdone_ = true;
        }
      }

    };

  } // namespace detail

  template <class T>
  rxcpp::observable<rti::sub::LoanedSample<T>> from_topic(
    dds::domain::DomainParticipant participant,
    const std::string & topic_name,
    dds::core::cond::WaitSet wait_set,
    rxcpp::schedulers::worker worker)
  {
    detail::KeyLessSubscription<T> dr_subscription(
      participant, topic_name, wait_set, worker);

    rx::subjects::subject<rti::sub::LoanedSample<T>> subject;

    return rxcpp::observable<>::create<rti::sub::LoanedSample<T>>(
      [dr_subscription, subject]
      (rxcpp::subscriber<rti::sub::LoanedSample<T>> subscriber)
      {
        const_cast<detail::KeyLessSubscription<T> &>(dr_subscription).initialize_once(subject);
        rxcpp::composite_subscription subscription =
          subject.get_observable().subscribe(subscriber);
        return subscription;
      });
  }

  template <class Key, class T, class KeySelector>
  rxcpp::observable<rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>>> from_keyed_topic(
    dds::domain::DomainParticipant participant,
    const std::string & topic_name,
    dds::core::cond::WaitSet wait_set,
    rxcpp::schedulers::worker worker,
    KeySelector&& key_selector /* Key(T) */)
  {
    detail::KeyedSubscription<Key, T, KeySelector> dr_subscription(
      participant, topic_name, wait_set, worker, std::forward<KeySelector>(key_selector));

    rxcpp::subjects::subject<rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>>> subject;

    return rxcpp::observable<>::create<
      rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>>>(
      [dr_subscription, subject]
      (rxcpp::subscriber<rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>>> subscriber)
      {
        const_cast<detail::KeyedSubscription<Key, T, KeySelector> &>(dr_subscription).initialize_once(subject);
        rxcpp::composite_subscription subscription =
          subject.get_observable().subscribe(subscriber);
        return subscription;
      });
  }
} // namespace rx4dds


/*class KeyStorage
{
Key key_;
public:

explicit KeyStorage(const Key & k) : key_(k) { }
explicit KeyStorage(Key&& k) : key_(std::move(k)) { }

const Key & on_get_key() const
{
return key_;
}
};*/
