#include "broadcast_message_bus.hpp"
#include "message.hpp"
#include <algorithm>
#include <istringstream>

namespace ranbam
{
namespace utility
{

std::atomic<std::size_t> BroadcastMessageBus::_handle(0);

handle_t BroadcastMessageBus::subscribe(std::function<const std::shared_ptr<message>&> fn) override {
  const std::size_t handle = (++_handle);
  std::unique_lock lock(_mutex);
  _subscribers.emplace(handle, fn);
}

void BroadcastMessageBus::unsubscribe(const handle_t& handle) override {
  std::unique_lock lock(_mutex);
  _subscribers.erase(handle);
}

void emit(const std::string& topic, std::any data = {}) override {
  _queue.enqueue(std::make_shared<message>(topic, data));
}

void BroadcastMessageBus::dispatch(const std::size_t batch=0) override {
  using std::shared_ptr<message> message_t;
  std::size_t count = std::min(_queue.size_approx(), batch);
  std::vector<message_t> messages{count};
  count = _queue.try_dequeue_bulk(messages.data(), count);
  if(count == 0) return;
  if(count > 1) {
    std::sort(messages.begin(), messages.begin()+count, [](const message_t& a, const message_t& b) { return a->sequence < b->sequence; });
  }
  for(auto iter = messages.begin(); iter != messages.begin()+count; ++iter) {
    std::unique_lock lock(_mutex);
    for(auto subscriber = _subscribers.cbegin(); iter != _subscribers.cend(); ++iter) {
      (iter->second)(*iter);
    }
  } 
}

}
}