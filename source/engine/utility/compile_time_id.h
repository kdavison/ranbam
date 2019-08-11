#pragma once

namespace compile {
template<typename T>
static constexpr std::size_t id() {
  return reinterpret_cast<std::size_t>(&id<T>);
}

template<typename T>
struct identifier {
  static constexpr std::size_t ID() {
    return id<T>();
  }
};
} //::compile
