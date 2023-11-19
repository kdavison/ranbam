#pragma once

#include <algorithm>

#define RANBAM_PI      3.14159265358979323846264338327950288L
#define RANBAM_2PI     6.28318530717958647692528676655900576L
#define RANBAM_E       2.71828182845904523536028747135266249L
#define RANBAM_PHI     1.61803398874989484820458683436563811L
#define RANBAM_SQRT2   1.41421356237309504880168872420969807L
#define RANBAM_SQRT3   1.73205080756887729352744634150587236L

namespace ranbam {
namespace math {

template<typename T>
constexpr static std::enable_if_t<std::is_floating_point_v<T>, T> PI     = static_cast<T>(RANBAM_PI);

template<typename T>
constexpr static std::enable_if_t<std::is_floating_point_v<T>, T> PI_2   = static_cast<T>(RANBAM_2PI);

template<typename T>
constexpr static std::enable_if_t<std::is_floating_point_v<T>, T> E      = static_cast<T>(RANBAM_E)

template<typename T>
constexpr static std::enable_if_t<std::is_floating_point_v<T>, T> PHI    = static_cast<T>(RANBAM_PHI);

template<typename T>
constexpr static std::enable_if_t<std::is_floating_point_v<T>, T> SQRT_2 = static_cast<T>(RANBAM_SQRT2);

template<typename T>
constexpr static std::enable_if_t<std::is_floating_point_v<T>, T> SQRT_3 = static_cast<T>(RANBAM_SQRT3);

template<typename T>
constexpr static std::enable_if_t<std::is_floating_point_v<T>, T> RADIAN_PER_DEGREE = static_cast<T>(RANBAM_2PI / static_cast<T>(360.0L));

template<typename T>
constexpr static std::enable_if_t<std::is_floating_point_v<T>, T> DEGREE_PER_RADIAN = static_cast<T>(static_cast<T>(360.0L) / RANBAM_2PI);
}
}