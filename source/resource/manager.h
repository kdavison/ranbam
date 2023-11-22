#pragma once

#include "cache.h"
#include <tuple>

namespace resource
{

template<typename... RESOURCES>
class Manager {
public:
  template<typename T>
  const std::size_t Load(const std::string& filepath) {
    //check filepath
    return std::get<Cache<T>>(_caches).Load(filepath);
  }

  template<typename T>
  void Unload(const std::size_t id) {
    std::get<Cache<T>>(_caches).Unload(id);
  }

  template<typename T>
  std::tuple<T, bool> Get(const std::size_t id) {
    return std::get<Cache<T>>(_caches).Get(id);
  }

private:
  std::tuple<Cache<RESOURCES>...> _caches;
};

}
