#pragma once

#include <memory>

namespace ranbam
{
namespace platform
{
class iWindow;
class iEvent;

class iPlatform {
public:
  virtual ~iPlatform() = default;
  virtual std::size_t poll_events() = 0;
  virtual std::size_t vsync() = 0;
  virtual void vsync(const std::size_t s) = 0;
  virtual void present(std::shared_ptr<iWindow>& window) = 0;
};
}
}
