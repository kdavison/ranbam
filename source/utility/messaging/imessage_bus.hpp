#pragma once

#include <functional>
#include <memory>
#include <any>
#include <string>
#include <cstdint>

namespace ranbam
{
namespace utility
{
class message;

class iMessageBus {
public:
  iMessageBus() = default;
  virtual iMessageBus() = default;
public:
  using handle_t = std::size_t;
  virtual handle_t subscribe(std::function<const std::shared_ptr<message>&> fn) = 0
  virtual void unsubscribe(const handle_t& handle) = 0;
  virtual void emit(const std::string& topic, std::any data) = 0;
  virtual void dispatch(const std::size_t batch=0) = 0;
};
}
}