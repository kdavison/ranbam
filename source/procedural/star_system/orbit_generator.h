#pragma once

#include "orbit.h"
#include <boost/math/constants/constants.hpp>
#include <random>

class orbit_generator {
public:
  typedef orbit result_type;
public:
  orbit_generator(
    std::normal_distribution<> eccentricity,
    std::uniform_real_distribution<> semimajor,
    std::normal_distribution<> inclination,
    std::normal_distribution<> ascending,
    std::normal_distribution<> periapsis
  )
  : _eccentricity(std::move(eccentricity))
  , _semimajor(std::move(semimajor))
  , _inclination(std::move(inclination))
  , _ascending(std::move(ascending))
  , _periapsis(std::move(periapsis))
  {
  }

  template<typename G>
  result_type operator()(G &g) {
    auto e = _eccentricity(g);
    auto a = std::sqrt(std::abs(_semimajor(g)));
    auto i = _inclination(g) * ::boost::math::constants::half_pi<double>();
    auto l = _ascending(g) * ::boost::math::constants::two_pi<double>();
    auto p = _periapsis(g) * ::boost::math::constants::pi<double>();

    if(e > 1.0) {
      a = a * e;
      e = 1/e;
      p -= ::boost::math::constants::half_pi<double>();
    }

    return result_type{
      e,
      a,
      i,
      l,
      p
    };
  }

private:
  std::normal_distribution<> _eccentricity;
  std::uniform_real_distribution<> _semimajor;
  std::normal_distribution<> _inclination;
  std::normal_distribution<> _ascending;
  std::normal_distribution<> _periapsis;
};

/*
//some example distributions for planets and shit

  auto asteroid_belt = ::utility::generator<TYPE>(
    std::normal_distribution<>(1.0, 0.01),
    std::uniform_real_distribution<>(400, 420),
    std::normal_distribution<>(0.0, 0.05),
    std::normal_distribution<>(0.0, 0.1),
    std::normal_distribution<>(0.0, 0.1)
  );

  auto inner_planets = ::utility::generator<TYPE>(
    std::normal_distribution<>(1.0, 0.01),
    std::uniform_real_distribution<>(1, 100),
    std::normal_distribution<>(0.0, 0.01),
    std::normal_distribution<>(0.0, 0.01),
    std::normal_distribution<>(0.0, 0.01)
  );

  auto outer_planets = ::utility::generator<TYPE>(
    std::normal_distribution<>(1.0, 0.02),
    std::uniform_real_distribution<>(2000, 6000),
    std::normal_distribution<>(0.0, 0.1),
    std::normal_distribution<>(0.0, 0.1),
    std::normal_distribution<>(0.0, 0.1)
  );

  auto comets = ::utility::generator<TYPE>(
    std::normal_distribution<>(1.0, 1.0),
    std::uniform_real_distribution<>(2000, 8000),
    std::normal_distribution<>(0.0, 0.5),
    std::normal_distribution<>(0.0, 1.0),
    std::normal_distribution<>(0.0, 1.0)
  );
*/
