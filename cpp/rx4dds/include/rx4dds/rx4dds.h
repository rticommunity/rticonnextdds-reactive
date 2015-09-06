#pragma once 

#include <dds/sub/ddssub.hpp>
#include <dds/core/ddscore.hpp>
#include <dds/core/cond/StatusCondition.hpp>

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <mutex>

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

  namespace detail {
    template <typename T>
    struct function_traits
    {
      typedef typename function_traits<decltype(&T::operator())>::result_type result_type;
      typedef typename function_traits<decltype(&T::operator())>::argument_type argument_type;
    };

    template <typename R, typename C, typename A>
    struct function_traits<R(C::*)(A)>
    {
      typedef R result_type;
      typedef A argument_type;
    };

    template <typename R, typename C, typename A>
    struct function_traits<R(C::*)(A) const>
    {
      typedef R result_type;
      typedef A argument_type;
    };

    template <typename R, typename A>
    struct function_traits<R(*)(A)>
    {
      typedef R result_type;
      typedef A argument_type;
    };

    template <typename R, typename C, typename A1, typename A2>
    struct function_traits<R(C::*)(A1, A2)>
    {
      typedef R result_type;
      typedef void argument_type;
    };

    template <typename R, typename C, typename A1, typename A2>
    struct function_traits<R(C::*)(A1, A2) const>
    {
      typedef R result_type;
      typedef void argument_type;
    };

    template <typename R, typename A1, typename A2>
    struct function_traits<R(*)(A1, A2)>
    {
      typedef R result_type;
      typedef void argument_type;
    };

    template <class KeySelector>
    struct argument_type
    {
      typedef
        typename std::remove_const<
        typename std::remove_reference<
        typename detail::function_traits<KeySelector>::argument_type>::type>::type
        type;
    };

    template <class KeySelector>
    struct result_type
    {
      typedef
        typename std::remove_const<
        typename std::remove_reference<
        typename detail::function_traits<KeySelector>::result_type>::type>::type
        type;
    };

  } // namespace detail

    struct NotAliveNoWriters : std::runtime_error
    {
        explicit NotAliveNoWriters(const std::string& what_arg)
          : std::runtime_error(what_arg)
        { }

        explicit NotAliveNoWriters(const char* what_arg)
          : std::runtime_error(what_arg)
        { }
    };

    struct StatusSet
    {
      dds::core::status::StatusMask                     status_mask;
      dds::core::status::LivelinessChangedStatus        liveliness_changed_status;
      dds::core::status::SampleRejectedStatus           sample_rejected_status;
      dds::core::status::SampleLostStatus               sample_lost_status;
      dds::core::status::RequestedDeadlineMissedStatus  requested_deadline_missed_status;
      dds::core::status::RequestedIncompatibleQosStatus requested_incompatible_qos_status;
      dds::core::status::SubscriptionMatchedStatus      subscription_matched_status;
      rti::core::status::DataReaderCacheStatus          datareader_cache_status;
      rti::core::status::DataReaderProtocolStatus       datareader_protocol_status;
    };

    template <class T>
    class TopicSubscription
    {
    private:
      struct SubscriptionState
      {
        bool init_dr_done_;
        bool init_read_condition_done_;
        bool init_status_condition_done_;

        dds::domain::DomainParticipant participant_;
        std::string topic_name_;
        dds::topic::Topic<T> topic_;
        dds::sub::DataReader<T> reader_;
        dds::core::cond::WaitSet wait_set_;
        dds::sub::cond::ReadCondition read_condition_;
        dds::core::cond::StatusCondition status_condition_;
        rxcpp::schedulers::worker worker_;
        rxcpp::subjects::subject<rti::sub::LoanedSample<T>> data_subject_;
        rxcpp::subjects::subject<StatusSet> status_subject_;

        SubscriptionState(dds::domain::DomainParticipant part,
                          const std::string & topic_name,
                          dds::core::cond::WaitSet wait_set,
                          rxcpp::schedulers::worker worker)
          : init_dr_done_(false),
            init_read_condition_done_(false),
            init_status_condition_done_(false),
            participant_(part),
            topic_name_(topic_name),
            topic_(dds::core::null),
            reader_(dds::core::null),
            wait_set_(wait_set),
            read_condition_(dds::core::null),
            status_condition_(dds::core::null),
            worker_(worker)
        { }

        ~SubscriptionState()
        {
          if (init_read_condition_done_)
            wait_set_ -= read_condition_;

          if (init_status_condition_done_)
            wait_set_ -= status_condition_;
        }
      };

      std::shared_ptr<SubscriptionState> state_;

      void initialize_datareader()
      {
        if (!state_->init_dr_done_)
        {
          state_->topic_ =
            dds::topic::Topic<T>(state_->participant_, state_->topic_name_);

          state_->reader_ = dds::sub::DataReader<T>(
            dds::sub::Subscriber(state_->participant_),
            state_->topic_);

          state_->init_dr_done_ = true;
        }
      }

      void initialize_read_condition()
      {
        if (!state_->init_read_condition_done_)
        {
          this->initialize_datareader();

          typename rxcpp::subjects::subject<rti::sub::LoanedSample<T>>::subscriber_type subscriber =
            state_->data_subject_.get_subscriber();

          std::shared_ptr<SubscriptionState> state = state_;

          state_->read_condition_ =
            dds::sub::cond::ReadCondition(
            state_->reader_,
            dds::sub::status::DataState::any(),
            [state, subscriber]()
          {
            try {
              dds::sub::LoanedSamples<T> samples =
                state->reader_.take();

              for (auto sample : samples)
              {
                subscriber.on_next(sample);
              }
            }
            catch (...)
            {
              subscriber.on_error(std::current_exception());
              state->data_subject_ = rxcpp::subjects::subject<rti::sub::LoanedSample<T>>();
            }
          });

          state_->wait_set_ += state->read_condition_;
          state_->init_read_condition_done_ = true;
        }
      }

      void initialize_status_condition()
      {
        if (!state_->init_read_condition_done_)
        {
          this->initialize_datareader();

          typename rxcpp::subjects::subject<StatusSet>::subscriber_type subscriber =
            state_->data_subject_.get_subscriber();

          std::shared_ptr<SubscriptionState> state = state_;

          state_->status_condition_ = dds::core::cond::StatusCondition(state_->reader_);
          state_->status_condition_.enabled_statuses(dds::core::status::StatusMask::all());
          /* It's a tragedy that StatusCondition has no dispatch handler. */
          state_->wait_set_ += state->read_condition_;
          state_->init_status_condition_done_ = true;
        }
      }

    public:
      TopicSubscription(dds::domain::DomainParticipant part,
                          const std::string & topic_name,
                          dds::core::cond::WaitSet wait_set,
                          rxcpp::schedulers::worker worker)
        : state_(std::make_shared<SubscriptionState>(
                 part, topic_name, wait_set, worker))
      { }

      rxcpp::observable<rti::sub::LoanedSample<T>> create_data_observable()
      {
        TopicSubscription<T> topic_sub = *this;

        return rxcpp::observable<>::create<rti::sub::LoanedSample<T>>(
          [topic_sub](rxcpp::subscriber<rti::sub::LoanedSample<T>> subscriber)
        {
          const_cast<TopicSubscription<T> &>(topic_sub).initialize_read_condition();
          rxcpp::composite_subscription subscription =
            topic_sub.state_->data_subject_.get_observable().subscribe(subscriber);
          return subscription;
        });
      }

      rxcpp::observable<StatusSet> create_status_observable()
      {
        TopicSubscription<T> topic_sub = *this;

        return rxcpp::observable<>::create<StatusSet>(
          [topic_sub](rxcpp::subscriber<StatusSet> subscriber)
        {
          const_cast<TopicSubscription<T> &>(topic_sub).initialize_status_condition();
          rxcpp::composite_subscription subscription =
            topic_sub.state_->status_subject_.get_observable().subscribe(subscriber);
          return subscription;
        });
      }

      void reset()
      {
        state_.reset();
      }
    };

    namespace detail {

      template <class T>
      T & remove_const(const T & t)
      {
        return const_cast<T &>(t);
      }

      template <class T>
      T & remove_const(T & t)
      {
        return t;
      }

      template <class Key, class T, class KeySelector>
      class GroupByDDSInstanceOp
      {
        typedef rxcpp::grouped_observable<Key, rti::sub::LoanedSample<T>> GroupedObservable;

        class Bucket
        {
          rxcpp::subjects::subject<rti::sub::LoanedSample<T>> subject_;
          rxcpp::composite_subscription subscription_;

        public:

          Bucket() {}

          Bucket(Key key,
            rxcpp::subjects::subject<GroupedObservable> shared_topsubject)
          {
            subscription_ =
              subject_
              .get_observable()
              .group_by([key](rti::sub::LoanedSample<T> sample) {
              return key;
            },
              [](rti::sub::LoanedSample<T> sample) { return sample; })
              .map([shared_topsubject](GroupedObservable go) {
              const_cast<rxcpp::subjects::subject<GroupedObservable> &>(shared_topsubject).get_subscriber().on_next(go);
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

        struct GroupByState
        {
          KeySelector key_selector_;
          BucketMap buckets_;
          rxcpp::subjects::subject<GroupedObservable> shared_topsubject_;

          explicit GroupByState(KeySelector&& key_selector)
            : key_selector_(std::move(key_selector))
          {}
        };

        std::shared_ptr<GroupByState> state_;

      public:

        explicit GroupByDDSInstanceOp(KeySelector key_selector)
          : state_(std::make_shared<GroupByState>(std::move(key_selector)))
        { }

        rxcpp::observable<GroupedObservable>
          operator()(const rxcpp::observable<rti::sub::LoanedSample<T>> & prev) const
        {
          std::shared_ptr<GroupByState> groupby_state = state_;

          return rxcpp::observable<>::create<GroupedObservable>(
            [groupby_state, prev](rxcpp::subscriber<GroupedObservable> subscriber)
          {
            rxcpp::composite_subscription subscription;
            subscription.add(groupby_state->shared_topsubject_.get_observable().subscribe(subscriber));

            subscription.add(prev.subscribe(
              [groupby_state, subscription](rti::sub::LoanedSample<T> sample)
            {
              try {
                dds::sub::status::InstanceState istate;
                sample.info().state() >> istate;
                dds::core::InstanceHandle handle = sample.info().instance_handle();
                BucketMap::const_iterator got = groupby_state->buckets_.find(handle);

                if (istate == dds::sub::status::InstanceState::not_alive_disposed())
                {
                  if (got != groupby_state->buckets_.end()) // instance exists
                  {
                    groupby_state->buckets_[handle]
                      .get_subject()
                      .get_subscriber()
                      .on_completed();

                    groupby_state->buckets_.erase(handle);
                  }
                  else
                  {
                    throw std::runtime_error("Instance should really exist at this point");
                  }
                }
                else
                {
                  if (sample.info().valid() && (got == groupby_state->buckets_.end())) // new instance
                  {
                    groupby_state->buckets_.emplace(
                      std::make_pair(handle, Bucket(groupby_state->key_selector_(sample.data()),
                      groupby_state->shared_topsubject_)));
                  }

                  // A new grouped_observable is pushed through 
                  // topsubject before sample.
                  groupby_state->buckets_[handle].get_subject().get_subscriber().on_next(sample);
                }
              }
              catch (...)
              {
                groupby_state->shared_topsubject_.get_subscriber().on_error(std::current_exception());
                subscription.unsubscribe();
              }

            }));

            return subscription;
          });
        }
      };

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

      template <class OnNext, class OnError, class OnCompleted>
      class DoOp // Same as tap
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
          OnNext on_next = on_next_;
          OnError on_error = on_error_;
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

    } // namespace detail

    template <class OnNext, class OnError, class OnCompleted>
    detail::DoOp<OnNext, OnError, OnCompleted> do_effect(OnNext&&, OnError&&, OnCompleted&&);

    namespace detail {

    template <class T>
    class PublishOverDDSOp
    {
      dds::pub::DataWriter<T> data_writer_;
      T dispose_instance_;
    public:

      PublishOverDDSOp(dds::pub::DataWriter<T> datawriter,
        const T & instance)
        : data_writer_(datawriter),
        dispose_instance_(instance)
      { }

      rxcpp::observable<T> operator ()(const rxcpp::observable<T> & prev) const
      {
        dds::pub::DataWriter<T> data_writer = data_writer_;
        const T & instance = dispose_instance_;

        return prev.tap(
          [data_writer](T & t) {
          const_cast<dds::pub::DataWriter<T> &>(data_writer).write(t);
        },
          [](std::exception_ptr eptr) { /* no-op */ },
          [data_writer, instance]() {
          dds::pub::DataWriter<T> & dw = const_cast<dds::pub::DataWriter<T> &>(data_writer);
          dw.dispose_instance(dw.register_instance(instance));
        });
      }
    };

    class CoalesceAliveOp
    {
    public:

      template <class Observable>
      static void remove_observable(
        std::vector<Observable> & observable_vec,
        std::vector<rxcpp::subscription> & subscription_vec,
        Observable observable)
      {
        auto iter = std::find(observable_vec.begin(), observable_vec.end(), observable);
        if (iter != observable_vec.end())
        {
          size_t index = iter - observable_vec.begin();
          observable_vec.erase(iter);
          subscription_vec.erase(subscription_vec.begin() + index);
        }
      }

      template <class ObservableOfObservable>
      rxcpp::observable<std::vector<typename ObservableOfObservable::value_type>>
        operator ()(ObservableOfObservable prev) const
      {
        typedef std::vector<typename ObservableOfObservable::value_type> ResultType;
        typedef std::vector<rxcpp::subscription> SubscriptionVecType;
          
        auto alive_vec_ptr = std::make_shared<ResultType> ();
        auto alive_sub_ptr = std::make_shared<SubscriptionVecType>();
        auto lock = std::make_shared<std::mutex>();

        return rxcpp::observable<>::create<ResultType>(
          [alive_vec_ptr, alive_sub_ptr, prev, lock](rxcpp::subscriber<ResultType> subscriber)
          {
            return prev.subscribe(
              [alive_vec_ptr, alive_sub_ptr, subscriber, lock]
              (typename ObservableOfObservable::value_type next_observable) {
                std::unique_lock<std::mutex> guard(*lock);
                auto & alive_vector = *detail::remove_const(alive_vec_ptr);
                auto iter = std::find(alive_vector.begin(), alive_vector.end(), next_observable);
                if (iter == alive_vector.end())
                {
                  alive_vector.push_back(next_observable);
                  detail::remove_const(alive_sub_ptr)->push_back(next_observable.subscribe(
                    [](const typename ObservableOfObservable::value_type::value_type &) { /* No-op */ },
                    [alive_vec_ptr, alive_sub_ptr, subscriber, next_observable, lock](std::exception_ptr) {
                      std::unique_lock<std::mutex> guard(*lock);
                      remove_observable(remove_const(*alive_vec_ptr),
                                        remove_const(*alive_sub_ptr),
                                        next_observable);
                      subscriber.on_next(*alive_vec_ptr);
                    },
                    [alive_vec_ptr, alive_sub_ptr, subscriber, next_observable, lock]() {
                      std::unique_lock<std::mutex> guard(*lock);
                      remove_observable(remove_const(*alive_vec_ptr),
                                        remove_const(*alive_sub_ptr),
                                        next_observable);
                      subscriber.on_next(*alive_vec_ptr);
                    }));
                }
                subscriber.on_next(*alive_vec_ptr);
            },
            [alive_vec_ptr, alive_sub_ptr, subscriber, lock](std::exception_ptr eptr) {
                subscriber.on_error(eptr);
                std::unique_lock<std::mutex> guard(*lock);
                remove_const(alive_vec_ptr).reset();
                remove_const(alive_sub_ptr).reset();
            },
              [alive_vec_ptr, alive_sub_ptr, subscriber, lock]() {
                subscriber.on_completed();
                std::unique_lock<std::mutex> guard(*lock);
                remove_const(alive_vec_ptr).reset();
                remove_const(alive_sub_ptr).reset();
            });
          });
      }
    };

    template<class T>
    class DynamicCombineLatestOp
    {
      struct CombineLatestSubscriptionState 
      {
        std::vector<T> result_vector;
        std::vector<char> init_vector;
        rxcpp::composite_subscription subscription;
        size_t init_count;
        size_t expected_count;
        size_t completed_count;

        explicit CombineLatestSubscriptionState()
          : init_count(0),
            expected_count(0),
            completed_count(0)
        { }

        void restart(size_t expected)
        {
          subscription = rxcpp::composite_subscription();
          result_vector = std::vector<T>(expected, T());
          init_vector = std::vector<char>(expected, 0);
          init_count = 0;
          expected_count = expected;
          completed_count = 0;
        }
      };
    
    public:

      template <class Observable>
      rxcpp::observable<std::vector<T>> operator ()(rxcpp::observable<std::vector<Observable>> prev)
      {
        return rxcpp::observable<>::create<std::vector<T>>([prev](rxcpp::subscriber<std::vector<T>> subscriber)
        {
          auto state = std::make_shared<CombineLatestSubscriptionState>();

          return prev.subscribe(
            [prev, subscriber, state]
            (const std::vector<Observable> & alive_observables) { 
              size_t i = 0;
              state->restart(alive_observables.size());

              for (auto & observable : alive_observables)
              {
                state->subscription.add(
                  observable.subscribe(
                  [i, state, subscriber](const typename Observable::value_type & v) {
                    state->result_vector[i] = v;

                    if (state->init_vector[i] != 1)
                    {
                      state->init_vector[i] = 1;
                      state->init_count++;
                    }

                    if (state->init_count == state->expected_count)
                      subscriber.on_next(state->result_vector);
                  },
                  [state, subscriber](std::exception_ptr eptr) {
                    subscriber.on_error(eptr);
                    state->subscription.unsubscribe();
                    remove_const(state).reset();
                  },
                  [state, subscriber](){
                    bool flush = true;
                    if (state->init_count == state->expected_count) // all initialized
                    {
                      state->completed_count++;
                      if (state->completed_count == state->expected_count)
                        flush = true;
                      else
                        flush = false;
                    }
                    if (flush)
                    {
                      subscriber.on_completed();
                      state->subscription.unsubscribe();
                      remove_const(state).reset();
                    }
                  }));
                i++;
              }
            },
            [subscriber, state](std::exception_ptr eptr) { 
              subscriber.on_error(eptr);  
              remove_const(state).reset();
            },
            [subscriber, state]() { 
              subscriber.on_completed(); 
              remove_const(state).reset();
            });
        });
      }
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

    template <class T>
    struct CombineLatestSubscriptionState
    {
      std::vector<T> result_vector;
      std::vector<char> init_vector;
      rxcpp::composite_subscription subscription;
      size_t init_count;
      size_t expected_count;
      size_t completed_count;

      explicit CombineLatestSubscriptionState(size_t expected)
        : result_vector(expected, T()),
          init_vector(expected, 0),
          subscription(),
          init_count(0),
          expected_count(expected),
          completed_count(0)
      { }
    };
  } // namespace detail

  template <class Key, class T, class KeySelector>
  detail::GroupByDDSInstanceOp<Key, T, KeySelector> group_by_dds_instance(KeySelector&& key_selector)
  {
    return detail::GroupByDDSInstanceOp<Key, T, KeySelector>(std::forward<KeySelector>(key_selector));
  }

  template <class KeySelector>
  detail::GroupByDDSInstanceOp<
    typename detail::result_type<KeySelector>::type,
    typename detail::argument_type<KeySelector>::type,
    KeySelector>
  group_by_key(KeySelector&& key_selector)
  {
    return detail::GroupByDDSInstanceOp<
      typename detail::result_type<KeySelector>::type,
      typename detail::argument_type<KeySelector>::type,
      KeySelector>(std::forward<KeySelector>(key_selector));
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

  inline detail::CoalesceAliveOp coalesce_alive()
  {
    return detail::CoalesceAliveOp();
  }

  template <class T>
  inline detail::DynamicCombineLatestOp<T> dynamic_combine_latest()
  {
    return detail::DynamicCombineLatestOp<T>();
  }

  template<class T>
  detail::PublishOverDDSOp<T> publish_over_dds(dds::pub::DataWriter<T> datawriter,
                                               const T & dispose_instance)
  {
    return detail::PublishOverDDSOp<T>(datawriter, dispose_instance);
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

  template <class Observable>
  rxcpp::observable<std::vector<typename Observable::value_type>>
    combine_latest(const std::vector<Observable> & sources)
  {
    typedef typename std::vector<typename Observable::value_type> EmittedType;

    return rxcpp::observable<>::create<EmittedType>
      ([sources](rxcpp::subscriber<EmittedType> subscriber)
      {
        auto state = 
          std::make_shared<detail::CombineLatestSubscriptionState<
            typename EmittedType::value_type>>(sources.size());

        size_t i = 0;

        for (auto & observable : sources)
        {
          state->subscription.add(
            observable.subscribe(
            [i, state, subscriber](const typename EmittedType::value_type & v) {
              state->result_vector[i] = v;

              if (state->init_vector[i] != 1)
              {
                state->init_vector[i] = 1;
                state->init_count++;
              }

              if (state->init_count == state->expected_count)
                subscriber.on_next(state->result_vector);
            },
            [state, subscriber](std::exception_ptr eptr) {
              subscriber.on_error(eptr);
              state->subscription.unsubscribe();
              remove_const(state).reset();
            },
            [state, subscriber](){
              bool flush = true;
              if (state->init_count == state->expected_count) // all initialized
              {
                state->completed_count++;
                if (state->completed_count == state->expected_count)
                  flush = true;
                else
                  flush = false;
              }
              if (flush)
              {
                subscriber.on_completed();
                state->subscription.unsubscribe();
                remove_const(state).reset();
              }
            }));
          i++;
        }

        return rxcpp::make_subscription([state]() {
          state->subscription.unsubscribe();
          remove_const(state).reset();
        });

      });
  }

  template <class ObservableIter>
  rxcpp::observable<std::vector<typename ObservableIter::value_type::template value_type>>
    combine_latest(ObservableIter begin, ObservableIter end)
  {
    std::vector<typename ObservableIter::value_type> sources(begin, end);
    return rx4dds::combine_latest(sources);
  }

} // namespace rx4dds
