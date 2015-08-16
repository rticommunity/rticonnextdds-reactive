#pragma once 

#include <dds/sub/ddssub.hpp>
#include <dds/core/ddscore.hpp>
#include <memory>
#include <stdexcept>
#include <string>

#include "rxcpp/rx.hpp"

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

      void initialize_once(rxcpp::subjects::subject<T> subject)
      {
        if (!state_->initdone_)
        {
          state_->topic_ =
            dds::topic::Topic<T>(state_->participant_, state_->topic_name_);

          state_->reader_ = dds::sub::DataReader<ShapeTypeExtended>(
            dds::sub::Subscriber(state_->participant_),
            state_->topic_);

          auto subscriber = subject.get_subscriber();

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

                if (sample.info().valid()) {
                  subscriber.on_next(sample.data());
                }
                else if (istate == dds::sub::status::InstanceState::not_alive_no_writers())
                {
                  subscriber.on_error(
                    std::make_exception_ptr(
                    NotAliveNoWriters("No alive writers for topic = " + state_->topic_name_)));
                  schedule_dr_subscription_end();
                  break;
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

    template <class T>
    class KeyedSubscription
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
      KeyedSubscription(dds::domain::DomainParticipant part,
                        const std::string & topic_name,
                        dds::core::cond::WaitSet wait_set,
                        rxcpp::schedulers::worker worker)
        : state_(std::make_shared<SubscriptionState>(
                    part, topic_name, wait_set, worker))
      { }

      void initialize_once(rxcpp::subjects::subject<T> subject)
      {
        if (!state_->initdone_)
        {
          state_->topic_ =
            dds::topic::Topic<T>(state_->participant_, state_->topic_name_);

          state_->reader_ = dds::sub::DataReader<ShapeTypeExtended>(
            dds::sub::Subscriber(state_->participant_),
            state_->topic_);

          auto subscriber = subject.get_subscriber();

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

                if (sample.info().valid()) {
                  subscriber.on_next(sample.data());
                }
                else if (istate == dds::sub::status::InstanceState::not_alive_no_writers())
                {
                  subscriber.on_error(
                    std::make_exception_ptr(
                    NotAliveNoWriters("No alive writers for topic = " + state_->topic_name_)));
                  schedule_dr_subscription_end();
                  break;
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

  } // namespace detail

  template <class T>
  rxcpp::observable<T> from_topic(
    dds::domain::DomainParticipant participant,
    const std::string & topic_name,
    dds::core::cond::WaitSet wait_set,
    rxcpp::schedulers::worker worker)
  {
    detail::KeyLessSubscription<T> dr_subscription(
      participant, topic_name, wait_set, worker);

    rx::subjects::subject<T> subject;

    return rxcpp::observable<>::create<T>(
      [dr_subscription, subject]
    (rxcpp::subscriber<T> subscriber)
    {
      const_cast<detail::KeyLessSubscription<T> &>(dr_subscription).initialize_once(subject);
      rxcpp::composite_subscription subscription =
        subject.get_observable().subscribe(subscriber);
      return subscription;
    });
  }

  template <class T>
  rxcpp::observable<T> from_keyed_topic(
    dds::domain::DomainParticipant participant,
    const std::string & topic_name,
    dds::core::cond::WaitSet wait_set,
    rxcpp::schedulers::worker worker)
  {
    detail::KeyedSubscription<T> dr_subscription(
      participant, topic_name, wait_set, worker);

    rx::subjects::subject<T> subject;

    return rxcpp::observable<>::create<T>(
      [dr_subscription, subject]
    (rxcpp::subscriber<T> subscriber)
    {
      const_cast<detail::KeyedSubscription<T> &>(dr_subscription).initialize_once(subject);
      rxcpp::composite_subscription subscription =
        subject.get_observable().subscribe(subscriber);
      return subscription;
    });
  }
} // namespace rx4dds
