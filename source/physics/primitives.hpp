#pragma once

#include <Eigen/Core.hpp>
#include <math/vector.hpp>
#include <cstdint>

// template<typename T, uint32_t DIM1, typename TAG>
// class VectorN : public ::Eigen::Matrix<T,DIM1,1> {
// public:
//   VectorN() : ::Eigen::Matrix<T,DIM1,1>() {}

//   template<typename ...ARGS>
//   VectorN(ARGS&& ...args) : ::Eigen::Matrix<T,DIM1,1>(std::forward<ARGS>(args)...) {}

//   template<typename OTHER>
//   VectorN(const ::Eigen::MatrixBase<OTHER>& other) : ::Eigen::Matrix<T,DIM1,1>(other) {}

//   template<typename OTHER>
//   VectorN<T, DIM1, TAG>& operator=(const ::Eigen::MatrixBase<OTHER>& other) {
//     this->::Eigen::Matrix<T,DIM1,1>::operator=(other);
//     return *this;
//   }
// };

namespace ranbam
{
namespace physics
{
namespace _impl
{
template<typename T, typename V, typename TAG>
class taggedVector : public V<T> {
public:
  taggedVector() : V<T>() {}

  template<typename ...ARGS>
  taggedVector(ARGS&& ...args) : V<T>(std::forward<ARGS>(args)...) {}

  template<typename OTHER>
  taggedVector(const ::Eigen::MatrixBase<OTHER>& other) : V<T>(other) {}

  template<typename OTHER>
  V<T>& operator=(const ::Eigen::MatrixBase<OTHER>& other) {
    this->V<T>::operator=(other);
    return *this;
  }
};

struct position2d {};
struct velocity2d {};
struct position3d {};
struct velocity3d {};
}

template<typename T>
using Position2D = _impl::taggedVector<T, math::Vector2, _impl::position2d>;

template<typename T>
using Position3D = _impl::taggedVector<T, math::Vector3, _impl::position3d>;

template<typename T>
using Velocity2D = _impl::taggedVector<T, math::Vector2, _impl::velocity2d>;

template<typename T>
using Velocity3D = _impl::taggedVector<T, math::Vector3, _impl::velocity3d>;
}
}