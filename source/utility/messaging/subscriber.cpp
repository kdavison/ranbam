#include "subscriber.hpp"
#include <cassert>

namespace ranbam
{
namespace utility
{

Subscriber::Subscriber(const std::shared_ptr<iMessageBus>& bus)
  : _messageBus(bus)
{
  assert(_messageBus);
  _handle = _messageBus->subscribe(this->get_on_receive());
}

Subscriber::~Subscriber() {
  _messageBus(nullptr);
}

std::function<void(const std::shared_ptr<message>& message)> Subsciber::get_on_receive() override {
  return [=](const std::shared_ptr<message>& message) -> void {
    this->on_receive(message);
  }
}

void Subscriber::emit(const std::string& topic, std::any data) override {
  assert(_messageBus);
  _messageBus->emit(topic, data);
}

}
}