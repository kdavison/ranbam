#pragma once

/*
The way these hardware abstractions work if the video/events/os systems are
not separate.  The come as a single thing, so if you get one you get em all.
*/

#include <SDL2/SDL.h>
#include <mutex>
#include <atomic>
#include "framework/modules/iFrameworkInputModule.hpp"
#include "framework/modules/iFrameworkVideoModule.hpp"

namespace ranbam
{
namespace framework
{
namespace sdl2
{
namespace _impl {
class Library {
  Library();
  ~Library();
};
}

static _impl::Library library();

class Module
  : public ::ranbam::framework::iInputModule
  , public ::ranbam::framework::iVideoModule
{
public:
  Module() = default;
  virtual ~Module() = default;
public:
  void update(const ::ranbam::timepoint& t, const ::ranbam::microseconds& delta) override;
private:
  uint32_t get_window_id() const;
};
}
}
}