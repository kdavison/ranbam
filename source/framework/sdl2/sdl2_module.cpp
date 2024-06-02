#include <SDL2/SDL.h>
#include "framework/modules/sdl2/sdl2_module.hpp"

namespace ranbam
{
namespace framework
{
namespace sdl2
{
namespace _impl
{
Library::Library() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
}

Library::~Library() {
  SDL_Quit();
}
}

void Module::update(const ::ranbam::timepoint& t, const ::ranbam::microseconds& delta) override {
  SDL_Event event;
  /* TODO: maybe put some limits here */
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_DISPLAYEVENT:
      break;
    case SDL_WINDOWEVENT:
      if((event.windowID > 0) && !(event.windowID == get_window_id())) continue;
      switch(event.event) {
      case SDL_WINDOWEVENT_SHOWN:
        shown();
        break;
      case SDL_WINDOWEVENT_HIDDEN:
        hidden();
        break;
      case SDL_WINDOWEVENT_EXPOSED:
        exposed()
        break;
      case SDL_WINDOWEVENT_MOVED:
        /*todo: handle*/
        break;
      case SDL_WINDOWEVENT_RESIZED:
        resized(event.data1, event.data2);
        break;
      case SDL_WINDOWEVENT_SIZE_CHANGED:
        {
          int32_t width, height;
          SDL_GetWindowSize(_window.get(), &width, &height);
          resized(width, height);
        }
        break;
      case SDL_WINDOWEVENT_ENTER:
        mouse_gained();
        break;
      case SDL_WINDOWEVENT_LEAVE:
        mouse_lost();
        break;
      case SDL_WINDOWEVENT_FOCUS_GAINED:
        keyboard_gained();
        break;
      case SDL_WINDOWEVENT_FOCUS_LOST:
        keyboard_lost();
        break;
      case SDL_WINDOWEVENT_DISPLAY_CHANGED:
        display_changed(event.data1);
        break;
      default:
        /* todo: log or something */
        break;
      }
      break;
    case SDL_KEYDOWN:
      if((event.windowID > 0) && !(event.windowID == get_window_id())) continue;
      keypress(event.keysym.scancode, event.state, event.repeat, event.keysym.mode);
      break;
    case SDL_KEYUP:
      if((event.windowID > 0) && !(event.windowID == get_window_id())) continue;
      keypress(event.keysym.scancode, event.state, event.repeat, event.keysym.mode);
      break;
    case SDL_MOUSEMOTION:
      if((event.windowID > 0) && !(event.windowID == get_window_id())) continue;
      mouse_move(event.x, event.y, event.xrel, event.yrel);
      break;
    case SDL_MOUSEBUTTONDOWN:
      if((event.windowID > 0) && !(event.windowID == get_window_id())) continue;
      mouse_click(event.button, event.state, event.clicks, event.x, event.y);
      break;
    case SDL_MOUSEBUTTONUP:
      if((event.windowID > 0) && !(event.windowID == get_window_id())) continue;
      mouse_click(event.button, event.state, event.clicks, event.x, event.y);
      break;
    case SDL_MOUSEWHEEL:
      if((event.windowID > 0) && !(event.windowID == get_window_id())) continue;
      mouse_wheel(event.preciseX, event.preciseY);
      break;
    default:
      /* idk got some event we don't use */
      break;
    }
  }
}

uint32_t Module::get_window_id() const {
  return SDL_GetWindowID(_window.get());
}
}
}
}