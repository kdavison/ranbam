#pragma once

#include <random>
#include <boost/math/constants/constants.hpp>
#include <tuple>

namespace ranbam::math::volume
{

class sphere
{
public:
  typedef std::tuple<double,double,double> result_type;

public:
  sphere(const double minimum_radius, const double maximum_radius)
    : _radius(std::pow(minimum_radius, 2.0), std::pow(maximum_radius, 2.0))
    , _g(0.0, 1.0)
  {
  }

  template<typename GENERATOR>
  result_type operator()(GENERATOR &g) {
    const auto theta = ::boost::math::constants::two_pi<double>() * _g(g);
    const auto phi = std::acos(2.0 * _g(g) - 1.0);
    const auto r = std::sqrt(_radius(g));
    return std::make_tuple(
      r * std::cos(theta) * std::sin(phi),
      r * std::sin(theta) * std::sin(phi),
      r * std::cos(phi)
    );

  }

private:
  std::uniform_real_distribution<> _radius;
  std::uniform_real_distribution<> _g;
};

}
