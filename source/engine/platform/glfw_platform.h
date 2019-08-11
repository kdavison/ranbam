#pragma once

#include "iplatform.h"
#include "utility/EventQueue.h"
#include <atomic>
#include <cstdint>

namespace ranbam::platform
{
namespace GLFW
{
class Platform
  : public iPlatform
{
public:
  Platform(std::shared_ptr<::ranbam::iEventQueue> const& spEventQueue);
  ~Platform();
  std::shared_ptr<iWindow> create_window(const std::string& title, std::size_t width, std::size_t height);
  std::size_t poll_events(std::shared_ptr<iWindow>& window);
  std::size_t vsync();
  void vsync(const std::size_t s);
private:
  std::atomic<uint8_t> _vsync;
  std::shared_ptr<::ranbam::iEventQueue> _spEventQueue;
};
}
}
