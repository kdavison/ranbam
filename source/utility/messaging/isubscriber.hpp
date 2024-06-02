#pragma once

#include "imessage_bus.hpp"
#include <memory>
#include <any>

namespace ranbam
{
namespace utility
{
class message;

class iSubscriber
{
protected:
  virtual std::function<void(const std::shared_ptr<message>& message)> get_on_receive() = 0;
  virtual void emit(const std::string& topic, std::any data = {}) = 0;
  virtual void on_receive(const std::shared_ptr<message>& message) = 0;
};
}
}