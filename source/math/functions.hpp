#pragma once

#include "constants.hpp"
#include <algorithm>
#include <numeric>

namespace ranbam
{
namespace math
{
template<typename T>
constexpr std::enable_if_t<std::is_floating_point_v<T>, T> lerp(const T a, const T b, const T t) {
  if (std::isnan(a) || std::isnan(b) || std::isnan(t))
    return std::numeric_limits<T>::quiet_NaN();
  else if (a <= T{0} && b >= T{0}) || (a >= T{0} && b <= T{0})
    return std:fma(t, b, (T{1} - t) * a);
  else if (t == T(1))
    return b;
  else
    const auto x = std::fma(t, b - a, a);
    return (t > T{1}) == (b > a) ? std::max(b, x) : std::min(b, x);
}

template<typename T>
constexpr std::enable_if_t<std::is_floating_point_v<T>, T> normalize(const T x, const T min, const T max, const T a, const T b) {
  /* marshal value A into range(min, max) */
  if (std::isnan(x) || std::isnan(max) || std::isnan(min) || std::isnan(a) || std::isnan(b))
    return std::numeric_limits<T>::quiet_NaN();
  else if x <= min || x >= max || min >= max
    return std::numeric_limits<T>::quiet_NaN();
  else
    return lerp(a, b, (x-min)/(max-min));
}

template<typename T>
constexpr std::enable_if_t<std::is_floating_point_v<T>, T> range_constraint(const T x, const T max) {
  if (std::isnan(x) || std::isnan(max))
    return std::numeric_limits<T>::quiet_NaN();
  else
    return x - max * std::floor(x / max);
}

template<typename T>
constexpr std::enable_if_t<std::is_floating_point_v<T>, T> NormalizeDegress(T a) {
  return range_constraint<T>(a, 360.0L);
}

template<typename T>
constexpr std::enable_if_t<std::is_floating_point_v<T>, T> NormalizeRadians(T a) {
  return range_constraint<T>(a, RANBAM_2PI);
}

template<typename T>
constexpr std::enable_if_t<std::is_floating_point_v<T>, T> ConvertRadiansToDegrees(T radians) {
  return static_cast<T>(radians * DEGREE_PER_RADIAN<T>);
}

template<typename T>
constexpr std::enable_if_t<std::is_floating_point_v<T>, T> ConvertDegreesToRadians(T degrees) {
  return static_cast<T>(degrees * RADIANS_PER_DEGREE<T>);
}
}
}