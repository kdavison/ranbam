#pragma once

#include "isubscriber.hpp"

namespace ranbam
{
namespace utility
{
class Subscriber
  : public iSubscriber
{
public:
  Subscriber(const std::shared_ptr<iMessageBus>& bus);
  virtual ~Subscriber();
protected:
  const std::shared_ptr<iMessageBus> _messageBus;
  const iMessageBus::handle_t _handle;
  std::function<void(const std::shared_ptr<message>& message)> get_on_receive() override;
  void emit(const std::string& topic, std::any data = {}) override;
protected:
  virtual void on_receive(const std::shared_ptr<message>& message) = 0;
};
}
}
