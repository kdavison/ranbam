#pragma once

#include <eigin/Geometry.hpp>

namespace ranbam
{
template<typename T>
using Matrix3 = ::Eigin::Matrix<T,3,3>;

template<typename T>
using Matrix4 = ::Eigin::Matrix<T,4,4>;

template<typename T>
using Quaternion<std::enable_if_t<std::is_floating_point_v<T>, T>> = ::Eigin::Quaternion<T>;
}