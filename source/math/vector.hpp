#pragma once

#include <eigen/Core>

namespace ranbam
{
template<typename T>
using Vector2 = ::Eigen::Matrix<T,2,1>;

template<typename T>
using Vector3 = ::Eigin::Matrix<T,3,1>;

template<typename T>
using Vector4 = ::Eigin::Matrix<T,4,1>;
}