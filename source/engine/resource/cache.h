#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <cstdint>

namespace resource
{
template<typename T>
class Cache
  : public compile::identifier<Cache<T>>
{
public:
  const std::size_t Load(const std::string& filepath) {
    auto hash = _StringHasher(filepath);
    _resources.push_back(std::make_tuple(hash, _load(filepath)));
    return hash;
  }

  const void Unload(const std::size_t id) {
    auto iterator = std::find_if(std::begin(_resources), std::end(_resources), [id](const auto& element) {
      return id == std::get<0>(element);
    });
    if(iterator != std::end(_resources)) {
      std::swap(*iterator, _resources.back());
      _resources.pop_back();
    }
  }

  std::tuple<T, bool> Get(const std::size_t id) {
    auto iterator = std::find_if(std::begin(_resources), std::end(_resources), [id](const auto& element) {
      return id == std::get<0>(element);
    });
    return std::make_tuple(std::get<1>(*iterator), (iterator != std::end(_resources)));
  }
private:
  T _load(const std::string& filepath) const;

  static constexpr std::hash<std::string> _StringHasher{};
  std::vector<std::tuple<std::size_t, T>> _resources;
};
}  //::resource
