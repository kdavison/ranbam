#pragma once

#include <random>
#include <boost/math/constants/constants.hpp>
#include <tuple>

namespace ranbam::math::volume
{

class cone
{
public:
  typedef std::tuple<double,double,double> result_type;

public:
  cone(const double height, const double minimum_radius, const double maximum_radius)
    : _theta(0.0, ::boost::math::constants::two_pi<double>())
    , _phi(std::atan(minimum_radius / height), std::atan(maximum_radius / height))
    , _percent(0.0, 1.0)
    , _rhomax([height](const double phi) -> double { 
        return std::pow(height / std::cos(phi), 2.0);
      })
    , _height(height)
  {
  }

  template<typename GENERATOR>
  result_type operator()(GENERATOR &g) {
    const double theta = _theta(g);
    const double phi = _phi(g);
    const double rho = std::sqrt(_percent(g) * _rhomax(phi));
    return std::make_tuple(
      rho * std::sin(phi) * std::cos(theta),
      rho * std::sin(phi) * std::sin(theta),
      rho * std::cos(phi)
    );
  }

  const double height() const {
    return _height;
  }

private:
  std::uniform_real_distribution<> _theta;
  std::uniform_real_distribution<> _phi;
  std::uniform_real_distribution<> _percent;
  std::function<double(const double)> _rhomax;
  const double _height;
};

}
