#pragma once

#include "math/random/volume/cone.h"
#include <boost/math/constants/constants.hpp>
#include <eigen3/Eigen/Dense>
#include <algorithm>

namespace galaxy {
class spiral
{
  class arm_generator {
  public:
    typedef ::ranbam::math::volume::cone result_type;
  public:
    arm_generator(std::normal_distribution<double> height, std::normal_distribution<double> radius)
      : _height(height)
      , _radius(radius)
    {
    }

    template<typename GENERATOR>
    result_type operator()(GENERATOR& g) {
      const auto h = _height(g);
      const auto r = _radius(g);
      return result_type(h, 0.0, r);
    }

  private:
    std::normal_distribution<double> _height;
    std::normal_distribution<double> _radius;
  };

public:
  typedef std::tuple<double,double,double> point_t;
  typedef std::vector<point_t> result_type;
public:
  spiral(
    const std::size_t number_of_points,
    const std::size_t number_of_arms,
    const double radius_mean,
    const double radius_stddev,
    const double height_mean,
    const double height_stddev,
    const double swirl_mean,
    const double swirl_stddev
  )
    : _arms(number_of_arms)
    , _count(number_of_points)
    , _radius(radius_mean, radius_stddev)
    , _height(height_mean, height_stddev)
    , _swirl(swirl_mean, swirl_stddev)
  {
  }

  template<typename GENERATOR>
  result_type operator()(GENERATOR& g) {
    auto arms = generate_arms(g);

    std::vector<std::vector<point_t>> arm_points(arms.size(), std::vector<point_t>{});
    for(std::size_t index(0); index < _count; ++index) {
      std::size_t arm_index = g() % arms.size();
      auto point = arms.at(arm_index)(g);
      std::get<2>(point) -= arms.at(arm_index).height() * 1.05;
      arm_points.at(arm_index).push_back(std::move(point));
    }

    const Eigen::Vector3d center(0.0, 0.0, 0.0);
    Eigen::Affine3d rot90 = 
      Eigen::Translation3d(center) *
      Eigen::AngleAxis<double>(
          ::boost::math::constants::half_pi<double>(),
          Eigen::Vector3d::UnitY()
        ) *
      Eigen::Translation3d(-center);

    const double arm_rotation = ::boost::math::constants::two_pi<double>() / arms.size();

    result_type result;
    result.reserve(_count);
    std::size_t arm_index(1);
    for(auto& arm : arm_points) {
      arm_index += 1;
      Eigen::Affine3d rotArm = 
        Eigen::Translation3d(center) *
        Eigen::AngleAxis<double>(
            arm_rotation * arm_index,
            Eigen::Vector3d::UnitZ()
          ) *
        Eigen::Translation3d(-center);

      for(auto& point : arm) {
        Eigen::Vector3d p0(
          std::get<0>(point),
          std::get<1>(point),
          std::get<2>(point)
        );

        Eigen::Vector3d p1(rot90 * p0);
        Eigen::Vector3d p2(rotArm * p1);

        Eigen::Affine3d rotSwirl = 
          Eigen::Translation3d(center) *
          Eigen::AngleAxis<double>(
              _swirl(g) / (::boost::math::constants::pi<double>() * p2.squaredNorm()),
              Eigen::Vector3d::UnitZ()
            ) *
          Eigen::Translation3d(-center);

        Eigen::Vector3d p3(rotSwirl * p2);

        result.emplace_back(p3.x(), p3.y(), p3.z());
      }
    }

    return result;
  }

private:
  template<typename GENERATOR>
  std::vector<arm_generator::result_type> generate_arms(GENERATOR &g) {
    std::vector<arm_generator::result_type> arms;
    arms.reserve(_arms);
    arm_generator arm_generator(_radius, _height);
    std::generate_n(std::back_inserter(arms), _arms, std::bind(arm_generator, g));
    return arms;
  }

  const std::size_t _arms;
  const std::size_t _count;
  std::normal_distribution<double> _swirl;
  std::normal_distribution<double> _radius;
  std::normal_distribution<double> _height;
};
}
