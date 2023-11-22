#pragma once

#include "sphere.h"
#include <random>
#include <boost/math/constants/constants.hpp>
#include <tuple>

namespace ranbam::math::volume
{

class ellipsoid
{
public:
  typedef std::tuple<float,float,float> result_type;
public:
  ellipsoid(
    const double min_a, const double min_b, const double min_c,
    const double max_a, const double max_b, const double max_c
  )
    : _r2(
        std::pow(min_a, 2) + std::pow(min_b, 2) + std::pow(min_c, 2),
        std::pow(max_a, 2) + std::pow(max_b, 2) + std::pow(max_c, 2)
      )
    , _max_a(max_a)
    , _max_b(max_b)
    , _max_c(max_c)
    , _radians(0.0, ::boost::math::constants::two_pi<double>())
  {
  }

  template<typename GENERATOR>
  result_type operator()(GENERATOR& g) {
    const auto theta = _radians(g);
    const auto phi = _radians(g);
    const double maxr2 = std::pow(_max_a, 2) + std::pow(_max_b, 2) + std::pow(_max_c, 2);
    const double scale = std::sqrt(_r2(g) / maxr2);
    return std::make_tuple(
      _max_a * scale * std::cos(theta)*std::sin(phi),
      _max_b * scale * std::sin(theta)*std::sin(phi),
      _max_c * scale * std::cos(phi)
    );
  }

private:
  std::uniform_real_distribution<> _r2;
  const double _max_a;
  const double _max_b;
  const double _max_c;
  std::uniform_real_distribution<> _radians;
};

}
