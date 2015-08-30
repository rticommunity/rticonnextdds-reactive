#include "solar_system.h"
#include <cmath>

namespace {
  const double M_PI = 3.14159265358979323846;
}

SolarSystem::SolarSystem(int domain_id)
  : participant_(domain_id),
    circle_topic_(participant_, "Circle"),
    triangle_topic_(participant_, "Triangle"),
    circle_writer_(dds::pub::Publisher(participant_), circle_topic_),
    triangle_writer_(dds::pub::Publisher(participant_), triangle_topic_),
    scheduler_(rxcpp::schedulers::make_current_thread()),
    worker_(scheduler_.create_worker())
{
  // PlanetInfo(orbitRadius, size, year-in-earth-days)
  planets_["Mercury"] = PlanetInfo(30, 8, 88);
  planets_["Venus"]   = PlanetInfo(50, 15, 225);
  planets_["Earth"]   = PlanetInfo(70, 17, 365);
  planets_["Mars"]    = PlanetInfo(90, 12, 686);
  planets_["Jupiter"] = PlanetInfo(120, 30, 4329);

  // Yes, the Moon too! I know, it's not a planet.
  planets_["Moon"] =  PlanetInfo(20, 8, 365);
}

ShapeType SolarSystem::planet_location(const ShapeType & sun, 
                                       double degree, 
                                       const std::string & planet_name) const
{
  const PlanetInfo & planet = planets_.at(planet_name);
  return ShapeType(
    sun.color(),
    sun.x() + (int) (planet.orbit_radius_ * std::cos(degree * M_PI / 180)),
    sun.y() + (int) (planet.orbit_radius_ * std::sin(degree * M_PI / 180)),
    planet.size_);
}

rxcpp::composite_subscription SolarSystem::big_bang()
{
  // The Sun observable
  auto sun_orbit =
    rx4dds::from_topic<ShapeType>(
    participant_, "Square", waitset_, worker_)
    >> rx4dds::error_on_no_alive_writers()
    >> rx4dds::skip_invalid_samples()
    >> rx4dds::map_sample_to_data();

/*  rx4dds::from_keyed_topic<dds::core::string, ShapeType>(
    participant_, "Square", waitset_, worker_,
    [](const ShapeType & shape) { return shape.color(); });
*/

  // The Earth observable
  double earth_degree = 0;
  auto earth_orbit = 
    sun_orbit.map([this, earth_degree](const ShapeType & sun_loc) {
      const_cast<double &>(earth_degree) += 2;
      return planet_location(sun_loc, earth_degree, "Earth");
  })
  .publish()
  .ref_count();

  // The Moon observable
  double moon_degree = 0;
  auto moon_orbit
    = earth_orbit.map([this, moon_degree](const ShapeType earth_loc)
  {
    const_cast<double &>(moon_degree) += 7;
    return planet_location(earth_loc, moon_degree, "Moon");
  });

  ShapeType blue_instance("BLUE", -1, -1, -1);
  
  rxcpp::composite_subscription subscription;
  subscription.add((earth_orbit
                    >> rx4dds::publish_over_dds(circle_writer_, blue_instance))
                    .subscribe());
  
  subscription.add((moon_orbit
                     >> rx4dds::publish_over_dds(triangle_writer_, blue_instance))
                    .subscribe());

  return subscription;
}

void SolarSystem::orbit(rxcpp::composite_subscription subscription)
{
  rxcpp::schedulers::schedulable schedulable =
    rxcpp::schedulers::make_schedulable(
    worker_,
    [this](const rxcpp::schedulers::schedulable &) {
      const_cast<dds::core::cond::WaitSet &>(waitset_).dispatch(dds::core::Duration(4));
  });

  while (true) {
    worker_.schedule(schedulable);
  }
}
