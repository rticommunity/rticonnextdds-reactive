#include <algorithm>
#include <iostream>
#include <vector>

#include <dds/sub/ddssub.hpp>
#include <dds/core/ddscore.hpp>
// Or simply include <dds/dds.hpp> 

#include "ShapeType.hpp"
#include "rx4dds/rx4dds.h"
#include "solar_system.h"

namespace rx = rxcpp;
namespace rxu = rxcpp::util;

struct print_exception_on_error
{
  void operator()(std::exception_ptr eptr) const
  {
    try {
      std::rethrow_exception(eptr);
    }
    catch (std::exception & ex)
    {
      std::cout << ex.what() << "\n";
    }
  }
};

void test_dynamic_correlator(int domain_id, int sample_count)
{
  dds::domain::DomainParticipant participant(domain_id);
  dds::topic::Topic<ShapeType> triangle_topic(participant, "Triangle");
  dds::pub::DataWriter<ShapeType> triangle_writer(
    dds::pub::Publisher(participant), triangle_topic);
  dds::core::cond::WaitSet waitset;
  int count = 0;

  rxcpp::schedulers::scheduler scheduler =
    rxcpp::schedulers::make_current_thread();

  rxcpp::schedulers::worker worker
    = scheduler.create_worker();

  rx4dds::TopicSubscription<ShapeType> 
    topic_sub(participant, "Square", waitset, worker);

  auto subscription =
    topic_sub
      .create_data_observable()
      .op(rx4dds::group_by_dds_instance([](const ShapeType & shape) {
            return shape.color(); 
        }))
      .map([](rxcpp::grouped_observable<dds::core::string, rti::sub::LoanedSample<ShapeType>> go) {
         return go.op(rx4dds::to_unkeyed())
                  .op(rx4dds::complete_on_dispose())
                  .op(rx4dds::error_on_no_alive_writers())
                  .op(rx4dds::skip_invalid_samples())
                  .op(rx4dds::map_samples_to_data())
                  .publish()
                  .ref_count()
                  .as_dynamic();
      })
      .op(rx4dds::coalesce_alive())
      .map([](const std::vector<rxcpp::observable<ShapeType>> & sources) {
          return rx4dds::combine_latest(sources.begin(), sources.end());
        })
      .switch_on_next()
      .map([](const std::vector<ShapeType> & shapes) {
          ShapeType avg("ORANGE", 0, 0, 30);
        
          for(auto & shape : shapes)
          {
            avg.x(avg.x() + shape.x());
            avg.y(avg.y() + shape.y());
          }
          avg.x(avg.x() / shapes.size());
          avg.y(avg.y() / shapes.size());

          return avg;
        })
      .op(rx4dds::publish_over_dds(triangle_writer, ShapeType("ORANGE", -1, -1, -1)))
      .subscribe();

  rxcpp::schedulers::schedulable schedulable =
    rxcpp::schedulers::make_schedulable(
    worker,
    [waitset](const rxcpp::schedulers::schedulable &) {
    const_cast<dds::core::cond::WaitSet &>(waitset).dispatch(dds::core::Duration(4));
  });

  while (count < sample_count || sample_count == 0) {
    worker.schedule(schedulable);
  }
  
}

void test_solar_system(int domain_id, int)
{
  SolarSystem system(domain_id);
  //rxcpp::composite_subscription subscription = system.blue();
  rxcpp::composite_subscription subscription = system.multiple();
  system.orbit(subscription);
}

void test_keyed_topic(int domain_id, int sample_count)
{
  using namespace rxcpp::operators;
  using namespace rx4dds;

  dds::domain::DomainParticipant participant(domain_id);
  dds::core::cond::WaitSet waitset;
  int count = 0;

  rxcpp::schedulers::scheduler scheduler =
    rxcpp::schedulers::make_current_thread();

  rxcpp::schedulers::worker worker
    = scheduler.create_worker();

  rx4dds::TopicSubscription<ShapeType> topic_sub(participant, "Square", waitset, worker);
  typedef rxcpp::grouped_observable<
            dds::core::string, 
            rti::sub::LoanedSample<ShapeType>> 
              GroupedObservable;

  auto observable = 
    topic_sub.create_data_observable()
             >> group_by_dds_instance(
                [](const ShapeType & shape) { return shape.color(); });

  auto subscription1 =
    observable
      .flat_map([&count](GroupedObservable go) {
            return go >> to_unkeyed()
                      >> complete_on_dispose()
                      >> error_on_no_alive_writers()
                      >> skip_invalid_samples()
                      >> map_samples_to_data();
         }, 
         [](GroupedObservable, ShapeType & shape) { 
                return rx4dds::detail::remove_const(shape);  
         })
      .subscribe([&count](const ShapeType & shape) {
            std::cout << "color = " << shape.color()
                      << " x = " << shape.x() << "\n";
            count++;
        }, print_exception_on_error());

  rxcpp::schedulers::schedulable schedulable =
    rxcpp::schedulers::make_schedulable(
    worker,
    [waitset](const rxcpp::schedulers::schedulable &) {
    const_cast<dds::core::cond::WaitSet &>(waitset).dispatch(dds::core::Duration(4));
  });

  while (count < sample_count || sample_count == 0) {
    worker.schedule(schedulable);
  }

  //std::cout << "unsubscribing\n";
  //subscription2.unsubscribe();
  //subscription1.unsubscribe();
}

void test_keyless_topic(int domain_id, int sample_count)
{
  using namespace rxcpp::operators;
  using namespace rx4dds;

  dds::domain::DomainParticipant participant(domain_id);
  dds::core::cond::WaitSet waitset;
  int count = 0;

  rxcpp::schedulers::scheduler scheduler =
    rxcpp::schedulers::make_current_thread();

  rxcpp::schedulers::worker worker
    = scheduler.create_worker();

  rx4dds::TopicSubscription<ShapeType> topic_sub(participant, "Square", waitset, worker);

  auto observable = topic_sub.create_data_observable()
                      >> complete_on_dispose()
                      >> error_on_no_alive_writers()
                      >> skip_invalid_samples()
                      >> map_samples_to_data();

  auto subscription1 =
    observable >> subscribe<ShapeType>([&count](const ShapeType & shape) {
      std::cout << "x= " << shape.x() << "\n";
      count++;
  }, 
  print_exception_on_error());

  auto subscription2 =
    observable 
     >> subscribe<ShapeType>([](const ShapeType & shape) {
          std::cout << "y= " << shape.y() << "\n";
        },
        print_exception_on_error());


  rxcpp::schedulers::schedulable schedulable =
    rxcpp::schedulers::make_schedulable(
    worker,
    [waitset](const rxcpp::schedulers::schedulable &) {
    const_cast<dds::core::cond::WaitSet &>(waitset).dispatch(dds::core::Duration(4));
  });

  while (count < sample_count || sample_count == 0) {
    worker.schedule(schedulable);
  }

  //std::cout << "unsubscribing\n";
  //subscription2.unsubscribe();
  //subscription1.unsubscribe();
}

void test_original_subscriber(int domain_id, int sample_count)
{
    // Create a DomainParticipant with default Qos
    dds::domain::DomainParticipant participant(domain_id);

    // Create a Topic -- and automatically register the type
    dds::topic::Topic<ShapeType> topic(participant, "Square");

    // Create a DataReader with default Qos (Subscriber created in-line)
    dds::sub::DataReader<ShapeType> reader(dds::sub::Subscriber(participant), topic);

    rx::subjects::subject<ShapeType> subject;
    auto subscriber = subject.get_subscriber();
    rxcpp::composite_subscription subscription  = 
      subject.get_observable().subscribe([](ShapeType & shape) {
      std::cout << "x= " << shape.x() << " "
                << "y= " << shape.y() << "\n";
    });

    // Create a ReadCondition for any data on this reader and associate a handler
    int count = 0;
    dds::sub::cond::ReadCondition read_condition(
        reader,
        dds::sub::status::DataState::any(),
        [&reader, &count, &subscriber, &subscription]()
        {
            // Take all samples
            dds::sub::LoanedSamples<ShapeType> samples = reader.take();
            for (auto sample : samples){
                if (sample.info().valid()){
                    count++;
                    //std::cout << sample.data() << std::endl; 
                    subscriber.on_next(sample.data());
                    if (count == 300)
                      subscription.unsubscribe();
                }   
            }

        } // The LoanedSamples destructor returns the loan
    );

    // Create a WaitSet and attach the ReadCondition
    dds::core::cond::WaitSet waitset;
    waitset += read_condition;

    while (count < sample_count || sample_count == 0) {
        // Dispatch will call the handlers associated to the WaitSet conditions
        // when they activate
        //std::cout << "ShapeType subscriber sleeping for 4 sec...\n";
        waitset.dispatch(dds::core::Duration(4)); // Wait up to 4s each time
    }
}

int main(int argc, char *argv[])
{
    int domain_id = 0;
    int sample_count = 0;
    std::string name = "solar_system";

    if (argc >= 2) {
        domain_id = atoi(argv[1]);
    }
    if (argc >= 3) {
       name = argv[2];
    }
    if (argc >= 4) {
      sample_count = atoi(argv[2]);
    }

    // To turn on additional logging, include <rti/config/Logger.hpp> and
    // uncomment the following line:
    // rti::config::Logger::instance().verbosity(rti::config::Verbosity::STATUS_ALL);

    try {
      if (name == "dynamic_correlator")
        test_dynamic_correlator(domain_id, sample_count);
      else if (name == "solar_system")
        test_solar_system(domain_id, sample_count);
      else if (name == "keyed_topic")
        test_keyed_topic(domain_id, sample_count);
      else if (name == "keyless_topic")
        test_keyless_topic(domain_id, sample_count);
      else
        test_original_subscriber(domain_id, sample_count);
    } 
    catch (const std::exception& ex) {
        // This will catch DDS exceptions
        std::cerr << "Exception in subscriber_main(): " << ex.what() << std::endl;
        return -1;
    }

    // RTI Connext provides a finalize_participant_factory() method
    // if you want to release memory used by the participant factory singleton.
    // Uncomment the following line to release the singleton:
    //
    // dds::domain::DomainParticipant::finalize_participant_factory();

#ifndef RTI_WIN32
    std::cout << "Done. Press any key to continue...\n";
    getchar();
#endif

    return 0;
}

