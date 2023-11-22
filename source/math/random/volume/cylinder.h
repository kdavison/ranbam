#pragma once

#include <random>
#include <boost/math/constants/constants.hpp>
#include <tuple>

namespace ranbam::math::volume
{

class cylinder
{
public:
  typedef std::tuple<float,float,float> result_type;
public:
  cylinder(const double height, const double minimum_radius, const double maximum_radius)
    : _radius(minimum_radius * minimum_radius, maximum_radius * maximum_radius)
    , _theta(0, ::boost::math::constants::two_pi<double>())
    , _height(0.0, height)
  {
  }

  template<typename GENERATOR>
  result_type operator()(GENERATOR &g) {
    const auto r = _radius(g);
    const auto t = _theta(g);
    return std::make_tuple(
      std::sqrt(r)*std::cos(t),
      std::sqrt(r)*std::sin(t),
      _height(g)
    );
  }

private:
  std::uniform_real_distribution<> _radius;
  std::uniform_real_distribution<> _theta;
  std::uniform_real_distribution<> _height;
};

}
