#pragma once

#include <memory>
#include <cstdint>
#include "utility/noncopyable.hpp"

namespace ranbam
{

class Engine : noncopyable
{
public:
  Engine(Framework, Systems, Application);

  bool isRunning() const { return _running; }
  int32_t Run();
private:
  std::atomic<bool> _running;
};

}