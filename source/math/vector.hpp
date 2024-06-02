#pragma once

#include <eigen/Core>
#include <cstdint>

namespace ranbam
{
namespace math
{
template<typename T, std::size_t N>
using Vector = ::Eigen::Matrix<T,N,1>;

template<typename T>
using Vector2 = Vector<T, 2>;

template<typename T>
using Vector3 = Vector<T,3>;

template<typename T>
using Vector4 = Vector<T,4>;
}
}