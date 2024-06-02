#pragma once

#include <eigin/Geometry.hpp>
#include <cstdint>

namespace ranbam
{
namespace math
{
template<typename T, std::size_t N, std::size_t M>
using Matrix = ::Eigen::Matrix<T, N, M>;

template<typename T>
using Matrix3 = Matrix<T,3,3>;

template<typename T>
using Matrix4 = Matrix<T,4,4>;

template<typename T>
using Quaternion = ::Eigin::Quaternion<std::enable_if_t<std::is_floating_point_v<T>, T>>;
}
}