#pragma once

#include <cstdint>

namespace compile {
template<typename T>
static constexpr std::size_t identifier() {
  return reinterpret_cast<std::size_t>(&identifier<T>);
}

template<typename T>
struct type {
  std::size_t id() {
    return ::compile::identifier<T>();
  }
};

} //::compile
