#pragma once

#include "orbit.h"
#include "math/random/area/ellipse.h"
#include <eigen3/Eigen/Dense>
#include <tuple>

template<typename G>
std::vector<std::tuple<double,double,double, int>> visualize_orbit(orbit const& o, const std::size_t s, G& g) {
  std::vector<std::tuple<double,double,double, int>> cloud;

  const auto center = ::Eigen::Vector3d::Zero();

  const Eigen::Affine3d transform_p = 
    Eigen::Translation3d(center) *
    Eigen::AngleAxis<double>(
        o.periapsis,
        Eigen::Vector3d::UnitZ()
      ) *
    Eigen::Translation3d(-center);
  const Eigen::Affine3d transform_i = 
    Eigen::Translation3d(center) *
    Eigen::AngleAxis<double>(
        o.inclination,
        Eigen::Vector3d::UnitY()
      ) *
    Eigen::Translation3d(-center);
  const Eigen::Affine3d transform_a = 
    Eigen::Translation3d(center) *
    Eigen::AngleAxis<double>(
        o.ascending,
        Eigen::Vector3d::UnitZ()
      ) *
    Eigen::Translation3d(-center);

  ::ranbam::math::area::ellipse ellipse(
    o.semimajor,
    o.semimajor * o.eccentricity,
    o.semimajor,
    o.semimajor * o.eccentricity
  );

  ::Eigen::Vector3d offset(
      std::sqrt(
        std::pow(o.semimajor, 2.0) * (1 - std::pow(o.eccentricity, 2.0))
      ),
      0.0,
      0.0
    );
  offset = transform_p * offset;
  offset = transform_i * offset;
  offset = transform_a * offset;

  ////generate orbit outline
  //for(std::size_t index(0); index < 100; ++index) {
    //auto p0 = ellipse(rng);
    //::Eigen::Vector3d p(
      //std::get<0>(p0),
      //std::get<1>(p0),
      //0.0
    //);

    //p = transform_p * p;
    //p = transform_i * p;
    //p = transform_a * p;
    //p += offset;

    //cloud.emplace_back(
      //p.x(),
      //p.y(),
      //p.z(),
      //1
    //);
  //}

  //generate point
  {
    auto p0 = ellipse(g);
    ::Eigen::Vector3d p(
      std::get<0>(p0),
      std::get<1>(p0),
      0.0
    );

    p = transform_p * p;
    p = transform_i * p;
    p = transform_a * p;
    p += offset;

    cloud.emplace_back(
      p.x(),
      p.y(),
      p.z(),
      s
    );
  }

  return cloud;
}
