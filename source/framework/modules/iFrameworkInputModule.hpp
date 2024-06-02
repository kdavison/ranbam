#pragma once

#include <rocket/rocket.hpp>
#include "iFrameworkModule.hpp"

namespace ranbam
{
namespace framework
{
class iInputModule
  : public iFrameworkModule
{
public:
  iInputModule() = default;
  virtual ~iInputModule() = default;
public:
  using ::rocket::thread_safe_signal;
  /* mouse events */
  signal<void(int32_t x, int32_t y, int32_t dx, int32_t dy)> mouse_move;
  signal<void(uint8_t button, bool state, uint8_t clicks, int32_t x, int32_t y)> mouse_click;
  signal<void(float dx, float dy)> mouse_wheel;
  signal<void(uint32_t key, bool state, bool repeat, uint32_t mod)> keypress;
};
}
}