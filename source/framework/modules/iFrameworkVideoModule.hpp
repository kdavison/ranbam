#pragma once

#include <memory>
#include <rocket/rocket.hpp>
#include "framework/modules/iFrameworkModule.hpp"

namespace ranbam
{
namespace framework
{
class iVideoModule
  : public iFrameworkModule
{
public:
  iVideoModule() = default;
  virtual ~iVideoModule() = default;
public:
  using signal = ::rocket::thread_safe_signal;
  signal<void()> shown;
  signal<void()> hidden;
  signal<void()> exposed;
  signal<void()> closed;
  signal<void()> minimized;
  signal<void()> maximized;
  signal<void(std::size_t width, std::size_t height)> resized;
  signal<void()> mouse_gained;
  signal<void()> mouse_lost;
  signal<void()> keyboard_gained;
  signal<void()> keyboard_lost;
  signal<void(std::size_t)> display_changed;
};
}
}