#pragma once

#include <random>
#include <boost/math/constants/constants.hpp>
#include <tuple>

namespace ranbam::math::area
{

class ellipse
{
public:
  typedef std::tuple<double, double> result_type;
public:
  ellipse(const double minimum_a, const double minimum_b, const double maximum_a, const double maximum_b)
    : min_a(minimum_a)
    , min_b(minimum_b)
    , max_a(maximum_a)
    , max_b(maximum_b)
    , _u(0.0, 1.0)
  {
  }

  template<typename GENERATOR>
  result_type operator()(GENERATOR &g) {
    const auto u = _u(g);
    const auto a = (max_a - min_a) * std::sqrt(u) + min_a;
    const auto b = (max_b - min_b) * std::sqrt(u) + min_b;
    const auto t = theta(a,b,_u(g), _u(g));
    const auto r = radius(a,b,t);

    return std::make_tuple(
      r * std::cos(t),
      r * std::sin(t)
    );
  }

private:
  const double min_a, min_b;
  const double max_a, max_b;
  std::uniform_real_distribution<> _u;

  double radius(const double a, const double b, const double theta) const {
    return (a * b) / std::sqrt(std::pow(b * std::cos(theta), 2) + std::pow(a * std::sin(theta), 2));
  }
  
  double theta(const double a, const double b, const double u, const double v) const {
    const auto result = std::atan((b/a) * std::tan(::boost::math::constants::two_pi<double>() * u/4.0));
    if(v < 0.25) {
      return result;
    } else if(v < 0.5) {
      return (::boost::math::constants::pi<double>() - result);    
    } else if(v < 0.75) {
      return (::boost::math::constants::pi<double>() + result);
    }
    return (-1.0 * result);
  }
};

}
