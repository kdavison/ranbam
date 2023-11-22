#pragma once

#include <algorithm>
#include <vector>
#include <cstdint>

namespace utility {
template<typename T>
class generator {
public:
  template<typename... ARGS>
  generator(ARGS&&... args)
    : _generator(std::forward<ARGS>(args)...)
  {
  }

  template<typename GENERATOR>
  std::vector<typename T::result_type> operator()(GENERATOR& g, const std::size_t count) {
    std::vector<typename T::result_type> result(count, typename T::result_type{});
    std::generate(std::begin(result), std::end(result), std::bind(_generator, g));
    return result;
  }

private:
  T _generator;
};
}
