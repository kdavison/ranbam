#pragma once

#include "iGenerator.h"
#include <boost/math/constants/constants.hpp>
#include <cstdint>
#include <cassert>

namespace ranbam::point_cloud
{

class torus
  : public iGenerator
{
public:
  torus(
    const std::size_t major_radius,
    const std::size_t minor_radius
  )
    : _major_radius(major_radius)
    , _minor_radius(minor_radius)
  {
    assert(_major_radius > 0);
    assert(_minor_radius > 0);
  }

  std::vector<point_t> generate(const std::size_t count, ::rng::rng128 &rng) override {
    std::vector<point_t> points;
    points.reserve(count);

    std::uniform_real_distribution<> theta_distribution(0, ::boost::math::constants::two_pi<double>());
    std::uniform_real_distribution<> phi_distribution(0, ::boost::math::constants::two_pi<double>());
    std::uniform_real_distribution<> minor_distribution(0, _minor_radius);
    for(std::size_t index(0); index < count; ++index) {
     
      const double theta = theta_distribution(rng);
      const double phi = phi_distribution(rng);
      const double minor_r = minor_distribution(rng);

      points.push_back(point_t{
        (static_cast<double>(_major_radius) + (minor_r * std::cos(theta))) * std::cos(phi),
        (static_cast<double>(_major_radius) + (minor_r * std::cos(theta))) * std::sin(phi),
        minor_r * std::sin(theta)
      });
    }
    return points;
  }

private:
  const std::size_t _major_radius;
  const std::size_t _minor_radius;
};

}
