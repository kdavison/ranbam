#pragma once

#include <atomic>
#include <any>
#include <cstdint>

namespace ranbam
{
namespace utility
{
class message {
public:
  message(const std::string& topic, std::any data) : sequence(_sequence++), topic(topic), data(data) {}
  const std::string topic;
  const std::size_t sequence;
  std::any payload;
private:
  static std::atomic<std::size_t> _sequence;
};

static std::atomic<std::size_t> message::_sequence(0);
}
}