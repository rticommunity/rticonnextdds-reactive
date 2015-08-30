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

    inline bool operator < (const dds::core::string & lhs, const dds::core::string & rhs)
    {
      return strcmp(lhs.c_str(), rhs.c_str()) < 0;
    }

  } // namespace core
} // namespace dds

namespace rx4dds {

  struct NotAliveNoWriters : std::runtime_error
  {
      explicit NotAliveNoWriters(const std::string& what_arg)
        : std::runtime_error(what_arg)
      { }

      explicit NotAliveNoWriters(const char* what_arg)
        : std::runtime_error(what_arg)
      { }
  };

    template <class T>
    class KeylessTopicSubscription
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
        rxcpp::subjects::subject<rti::sub::LoanedSample<T>> subject_;

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

      void initialize_once()
      {
        if (!state_->initdone_)
        {
          state_->topic_ =
            dds::topic::Topic<T>(state_->participant_, state_->topic_name_);

          state_->reader_ = dds::sub::DataReader<T>(
            dds::sub::Subscriber(state_->participant_),
            state_->topic_);

          typename rxcpp::subjects::subject<rti::sub::LoanedSample<T>>::subscriber_type subscriber =
            state_->subject_.get_subscriber();

          state_->read_condition_ =
            dds::sub::cond::ReadCondition(
            state_->reader_,
            dds::sub::status::DataState::any(),
            [this, subscriber]()
          {
            try {
              dds::sub::LoanedSamples<T> samples =
                state_->reader_.take();

              for (auto sample : samples)
              {
                subscriber.on_next(sample);
              }
            }
            catch (...)
            {
              subscriber.on_error(std::current_exception());
              state_->subject_ = rxcpp::subjects::subject<rti::sub::LoanedSample<T>>();
            }
          });

          state_->wait_set_ += state_->read_condition_;
          state_->initdone_ = true;
        }
      }

    public:
      KeylessTopicSubscription(dds::domain::DomainParticipant part,
                          const std::string & topic_name,
                          dds::core::cond::WaitSet wait_set,
                          rxcpp::schedulers::worker worker)
        : state_(std::make_shared<SubscriptionState>(
                 part, topic_name, wait_set, worker))
      { }

      rxcpp::observable<rti::sub::LoanedSample<T>> create_observable()
      {
        KeylessTopicSubscription<T> keyless_sub = *this;

        return rxcpp::observable<>::create<rti::sub::LoanedSample<T>>(
          [keyless_sub](rxcpp::subscriber<rti::sub::LoanedSample<T>> subscriber)
          {
            const_cast<KeylessTopicSubscription<T> &>(keyless_sub).initialize_once();
            rxcpp::composite_subscription subscription =
              keyless_sub.state_->subject_.get_observable().subscribe(subscriber);
            return subscription;
          });
      }

      void reset()
      {
        state_.reset();
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

          state_->reader_ = dds::sub::DataReader<T>(
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
                dds::sub::LoanedSamples<T> samples =
                  state_->reader_.take();

                for (auto sample : samples)
                {
                  dds::sub::status::InstanceState istate; 
                  sample.info().state() >> istate;
                  dds::core::InstanceHandle handle = sample.info().instance_handle();
                  BucketMap::const_iterator got = state_->buckets_.find(handle);

                  if (istate == dds::sub::status::InstanceState::not_alive_disposed())
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
                  else
                  {
                    if (sample.info().valid() && (got == state_->buckets_.end())) // new instance
                    {
                      state_->buckets_.emplace(
                        std::make_pair(handle, Bucket(state_->key_selector_(sample.data()), topsubject)));
                    }

                    // A new grouped_observable is pushed through 
                    // topsubject before sample.
                    state_->buckets_[handle].get_subject().get_subscriber().on_next(sample);
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

  namespace detail {

    class InstanceStateInterpreter
    {
      dds::sub::status::InstanceState interpreted_instance_state_;

      explicit InstanceStateInterpreter(dds::sub::status::InstanceState state)
        : interpreted_instance_state_(state)
        {
          if ((state != dds::sub::status::InstanceState::not_alive_disposed()) &&
              (state != dds::sub::status::InstanceState::not_alive_no_writers()))
          throw std::logic_error("Precondition not met: Only NOT_ALIVE_DISPOSED and NOT_ALIVE_NO_WRITERS states can be interpreted.");
        }

    public:

      static InstanceStateInterpreter create_not_alive_disposed_intrepreter()
      {
        return InstanceStateInterpreter(dds::sub::status::InstanceState::not_alive_disposed());
      }

      static InstanceStateInterpreter create_not_alive_no_writers_intrepreter()
      {
        return InstanceStateInterpreter(dds::sub::status::InstanceState::not_alive_no_writers());
      }

      template <class Observable>
      Observable operator()(const Observable & prev) const
      {
        typedef typename Observable::value_type LoanedSample;
        dds::sub::status::InstanceState match_istate =
          interpreted_instance_state_;

        return rxcpp::observable<>::create<LoanedSample>(
          [prev, match_istate](rxcpp::subscriber<LoanedSample> subscriber)
        {
          rxcpp::composite_subscription subscription;
          subscription.add(rxcpp::composite_subscription::empty());

          subscription.add(
            prev.subscribe(
            [subscriber, subscription, match_istate](LoanedSample sample)
            {
              dds::sub::status::InstanceState istate;
              sample.info().state() >> istate;

              if (istate == match_istate)
              {
                if (istate == dds::sub::status::InstanceState::not_alive_disposed())
                {
                  subscriber.on_completed();
                  subscription.unsubscribe();
                }
                else if (istate == dds::sub::status::InstanceState::not_alive_no_writers())
                {
                  subscriber.on_error(
                    std::make_exception_ptr(NotAliveNoWriters("NotAliveNoWriters")));
                  subscription.unsubscribe();
                }
              }
              else
                subscriber.on_next(sample);
            },
            [subscriber](std::exception_ptr eptr) { subscriber.on_error(eptr);  },
            [subscriber]() { subscriber.on_completed();  }
          ));

          return subscription;
        });
      };
    };

    class SkipInvalidSamplesOp
    {
    public:

      template <class Observable>
      Observable operator ()(const Observable & prev) const
      {
        typedef typename Observable::value_type LoanedSample;
        return prev.filter([](LoanedSample sample) {
          return sample.info().valid();
        });
      };
    };

    class MapSampleToDataOp
    {
    public:

      template <class Observable>
      rxcpp::observable<typename Observable::value_type::DataType>
        operator ()(const Observable & prev) const
      {
        typedef typename Observable::value_type LoanedSample;
        return prev.map([](LoanedSample sample) {
          return sample.data();
        });
      }
    };

    class UnkeyOp
    {
    public:

      template <class GroupedObservable>
      rxcpp::observable<typename GroupedObservable::value_type>
        operator ()(const GroupedObservable & prev) const
      {
        typedef typename GroupedObservable::value_type LoanedSample;
        rxcpp::observable<LoanedSample> unkeyed_observable = prev;
        return unkeyed_observable;
      }
    };

    template <class T>
    class PublishOverDDSOp
    {
      dds::pub::DataWriter<T> data_writer_;
      const T & dispose_instance_;
    public:

      PublishOverDDSOp(dds::pub::DataWriter<T> datawriter,
                       const T & instance)
        : data_writer_(datawriter),
          dispose_instance_(instance)
      { }

      rxcpp::observable<T> operator ()(const rxcpp::observable<T> & prev) const
      {
        dds::pub::DataWriter<T> data_writer = this->data_writer_;
        const T & instance = this->dispose_instance_;

        return rxcpp::observable<>::create<T>([prev, data_writer, instance](rxcpp::subscriber<T> subscriber)
        {
          rxcpp::composite_subscription subscription;
          subscription.add(rxcpp::composite_subscription::empty());

          subscription.add(
            prev.subscribe(
              [data_writer, instance, subscriber, subscription](T & t) 
                {
                  dds::pub::DataWriter<T> datawriter = data_writer;
                  try {
                    datawriter.write(t);
                    subscriber.on_next(t);
                  }
                  catch (...)
                  {
                    subscriber.on_error(std::current_exception());
                    datawriter.dispose_instance(datawriter.register_instance(instance));
                    subscription.unsubscribe();
                  }
                },
                [subscriber](std::exception_ptr eptr) { subscriber.on_error(eptr);  },
                [data_writer, instance, subscriber, subscription]() {
                  try {
                    dds::pub::DataWriter<T> datawriter = data_writer;
                    datawriter.dispose_instance(datawriter.register_instance(instance));
                    subscriber.on_completed();
                  }
                  catch (...)
                  {
                    subscriber.on_error(std::current_exception());
                    subscription.unsubscribe();
                  }
                }
          ));

          return subscription;
        });
      }
    };

    template <class OnNext, class OnError, class OnCompleted>
    class DoOp
    {
      OnNext on_next_;
      OnError on_error_;
      OnCompleted on_completed_;

    public:

      DoOp(OnNext on_next,
           OnError on_error,
           OnCompleted on_completed)
        : on_next_(std::move(on_next)),
          on_error_(std::move(on_error)),
          on_completed_(std::move(on_completed))
      { }

      template <class T>
      rxcpp::observable<T> operator ()(const rxcpp::observable<T> & prev) const
      {
        OnNext on_next           = on_next_;
        OnError on_error         = on_error_;
        OnCompleted on_completed = on_completed_;

        return rxcpp::observable<>::create<T>(
          [prev, on_next, on_error, on_completed](rxcpp::subscriber<T> subscriber)
        {
          rxcpp::composite_subscription subscription;
          subscription.add(rxcpp::composite_subscription::empty());

          subscription.add(prev.subscribe(
            [subscriber, subscription, on_next](T & t)
            {
              try {
                on_next(t);
                subscriber.on_next(t);
              }
              catch (...)
              {
                subscriber.on_error(std::current_exception());
                subscription.unsubscribe();
              }
            },
            [subscriber, subscription, on_error](std::exception_ptr eptr)
            { 
              try {
                on_error(eptr);
                subscriber.on_error(eptr);
              }
              catch (...)
              {
                subscriber.on_error(std::current_exception());
                subscription.unsubscribe();
              }
            },
            [subscriber, subscription, on_completed]() {
              try {
                on_completed();
                subscriber.on_completed();
              }
              catch (...)
              {
                subscriber.on_error(std::current_exception());
                subscription.unsubscribe();
              }
          }));

          return subscription;
        });
      }
    };


    class ToObservableOp
    {
      // No-op
    };

    class NoOpOnCompleted
    {
      public:
        void operator ()() const { }
    };

    class NoOpOnError
    {
      public:
        void operator ()(std::exception_ptr) const { }
    };

  } // namespace detail

  template <class T>
  KeylessTopicSubscription<T> from_topic(
    dds::domain::DomainParticipant participant,
    const std::string & topic_name,
    dds::core::cond::WaitSet wait_set,
    rxcpp::schedulers::worker worker)
  {
    return KeylessTopicSubscription<T>(participant, topic_name, wait_set, worker);
  }

  template <class Key, class T, class KeySelector>
  rxcpp::observable<rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>>> from_keyed_topic(
    dds::domain::DomainParticipant participant,
    const std::string & topic_name,
    dds::core::cond::WaitSet wait_set,
    rxcpp::schedulers::worker worker,
    KeySelector&& key_selector /* Key(T) */)
  {
    KeyedSubscription<Key, T, KeySelector> dr_subscription(
      participant, topic_name, wait_set, worker, std::forward<KeySelector>(key_selector));

    rxcpp::subjects::subject<rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>>> subject;

    return rxcpp::observable<>::create<
      rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>>>(
      [dr_subscription, subject]
      (rxcpp::subscriber<rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>>> subscriber)
      {
        const_cast<KeyedSubscription<Key, T, KeySelector> &>(dr_subscription).initialize_once(subject);
        rxcpp::composite_subscription subscription =
          subject.get_observable().subscribe(subscriber);
        return subscription;
      });
  }

  inline detail::InstanceStateInterpreter error_on_no_alive_writers()
  {
    return detail::InstanceStateInterpreter::create_not_alive_no_writers_intrepreter();
  }

  inline detail::InstanceStateInterpreter complete_on_dispose()
  {
    return detail::InstanceStateInterpreter::create_not_alive_disposed_intrepreter();
  }

  inline detail::SkipInvalidSamplesOp skip_invalid_samples()
  {
    return detail::SkipInvalidSamplesOp();
  }

  inline detail::MapSampleToDataOp map_sample_to_data()
  {
    return detail::MapSampleToDataOp();
  }

  inline detail::UnkeyOp to_unkeyed()
  {
    return detail::UnkeyOp();
  }

  template<class T>
  detail::PublishOverDDSOp<T> publish_over_dds(dds::pub::DataWriter<T> datawriter, 
                                               const T & dispose_instance)
  {
    return detail::PublishOverDDSOp<T>(datawriter, dispose_instance);
  }

  inline detail::ToObservableOp to_observable()
  {
    return detail::ToObservableOp();
  }

  template <class T>
  rxcpp::observable<rti::sub::LoanedSample<T>> operator >>
    (KeylessTopicSubscription<T> keyless_sub, detail::ToObservableOp)
  {
    return keyless_sub.create_observable();
  }

  template <class OnNext, class OnError, class OnCompleted>
  detail::DoOp<OnNext, OnError, OnCompleted> do_effect(OnNext&& on_next, OnError&& on_error, OnCompleted&& on_completed)
  {
    return detail::DoOp<OnNext, OnError, OnCompleted>(
      std::forward<OnNext>(on_next),
      std::forward<OnError>(on_error),
      std::forward<OnCompleted>(on_completed));
  }

  template <class OnNext, class OnError>
  detail::DoOp<OnNext, OnError, detail::NoOpOnCompleted> do_effect(OnNext&& on_next, OnError&& on_error)
  {
    return detail::DoOp<OnNext, OnError, detail::NoOpOnCompleted>(
      std::forward<OnNext>(on_next),
      std::forward<OnError>(on_error),
      detail::NoOpOnCompleted());
  }

  template <class OnNext>
  detail::DoOp<OnNext, detail::NoOpOnError, detail::NoOpOnCompleted> do_effect(OnNext&& on_next)
  {
    return detail::DoOp<OnNext, detail::NoOpOnError, detail::NoOpOnCompleted>(
      std::forward<OnNext>(on_next),
      detail::NoOpOnError(),
      detail::NoOpOnCompleted());
  }

} // namespace rx4dds
