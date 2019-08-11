#pragma once

#include <type_traits>

template<typename E>
inline constexpr std::enable_if_t<std::is_enum<E>::value, E> operator|(const E a, const E b) {
  using TYPE = typename std::underlying_type<E>::type;
  return static_cast<E>(static_cast<TYPE>(a) | static_cast<TYPE>(b));
}

template<typename E>
inline constexpr std::enable_if_t<std::is_enum<E>::value, E> operator&(const E a, const E b) {
  using TYPE = typename std::underlying_type<E>::type;
  return static_cast<E>(static_cast<TYPE>(a) & static_cast<TYPE>(b));
}
