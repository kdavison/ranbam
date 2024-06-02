#pragma once

#include "concurrentqueue/concurrentqueue.h"
#include "imessage_bus.hpp"
#include <mutex>

namespace ranbam
{
namespace utility
{

class BroadcastMessageBus
  : public ::ranbam::utility::iMessageBus
{
public:
  using handle_t = ::ranbam::utility::iMessageBus::handle_t;
  handle_t subscribe(std::function<const std::shared_ptr<message>&> fn) override;
  void unsubscribe(const handle_t& handle) override;
  void emit(const std::string& topic, std::any data) override;
  void dispatch(const std::size_t batch=0) override;
private:
  std::atomic<std::size_t> _handle;
  std::mutex _mutex;
  std::unordered_map<handle_t, std::function<void(std::shared_ptr<message>)>> _subscribers;
  ::moodycamel::ConcurrentQueue<std::shared_ptr<message>> _queue;
};

}
}