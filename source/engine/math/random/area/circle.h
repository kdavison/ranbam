#pragma once

#include <random>
#include <boost/math/constants/constants.hpp>
#include <tuple>

namespace ranbam::math::area
{

class circle
{
public:
  typedef std::tuple<double,double> result_type;
public:
  circle(const double minimum_radius, const double maximum_radius)
    : _radius(std::pow(minimum_radius, 2.0), std::pow(maximum_radius, 2.0))
    , _theta(0, ::boost::math::constants::two_pi<double>())
  {
  }

  template<typename GENERATOR>
  result_type operator()(GENERATOR &g) {
    const auto r = std::sqrt(_radius(g));
    const auto t = _theta(g);
    return std::make_tuple(
      r*std::cos(t),
      r*std::sin(t)
    );
  }

private:
  std::uniform_real_distribution<> _radius;
  std::uniform_real_distribution<> _theta;
};

}
