#pragma once

#include "window_events.hpp"

namespace ranbam
{
namespace framework
{
namespace event
{
enum class Mouse : uint32_t {
  none    = 0,
  button1 = 1<<1,
  button2 = 1<<2,
  button3 = 1<<3,
  button4 = 1<<4,
  button5 = 1<<5,
  button6 = 1<<6,
  button8 = 1<<7,
  left   = button1,
  right  = button2,
  center = button3,
};

enum class Modifier : uint32_t {
  none   = 0;
  lshift = 1<<1,
  rshift = 1<<2,
  lctrl  = 1<<3,
  rctrl  = 1<<4,
  lalt   = 1<<5,
  ralt   = 1<<6,
  lgui   = 1<<7,
  rgui   = 1<<8,
  num    = 1<<9,
  caps   = 1<<10,
  mode   = 1<<11,
  scroll = 1<<12,
  shift  = lshift | rshift,
  ctrl   = lctrl  | rctrl,
  alt    = lalt   | ralt,
  gui    = lgui   | rgui
};

enum class Action : uint32_t {
  none    = 0,
  release = 1<<1,
  press   = 1<<2,
  repeat  = 1<<3
};
}
}
}