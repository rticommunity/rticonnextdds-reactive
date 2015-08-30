#pragma once

#include <unordered_map>
#include <dds/dds.hpp>

#include "ShapeType.hpp"
#include "rx4dds/rx4dds.h"

struct PlanetInfo
{
  int orbit_radius_;
  int size_;
  int year_in_earth_days_;

  PlanetInfo() { };

  PlanetInfo(int radious, int size, int year)
    : orbit_radius_(radious),
    size_(size),
    year_in_earth_days_(year)
  { }
};

class SolarSystem
{
  dds::domain::DomainParticipant participant_;
  dds::topic::Topic<ShapeType> circle_topic_; 
  dds::topic::Topic<ShapeType> triangle_topic_;
  dds::pub::DataWriter<ShapeType> circle_writer_;
  dds::pub::DataWriter<ShapeType> triangle_writer_;
  dds::core::cond::WaitSet waitset_;

  rxcpp::schedulers::scheduler scheduler_;
  rxcpp::schedulers::worker worker_;

  rx4dds::TopicSubscription<ShapeType> topic_subscription_;

  static std::unordered_map<std::string, PlanetInfo> planets;
  static const int earthYear = 365;

public:
  SolarSystem(int domain_id);
  rxcpp::composite_subscription big_bang();
  rxcpp::composite_subscription big_bang2();
  void orbit(rxcpp::composite_subscription);

  static ShapeType planet_location(const ShapeType & sun,
                                   double degree,
                                   const std::string & planet_name);
};