#pragma once

#include <GLFW/glfw3.h>
#include "utility/EventQueue.h"
#include <cassert>

#include <iostream>

#define LOCK(x) std::lock_guard<decltype(x)> lock_##x(x)

namespace GLFW
{
namespace _impl {
std::shared_ptr<::ranbam::iEventQueue> GetQueue(GLFWwindow *w) {
  void* pVoid = glfwGetWindowUserPointer(w);
  assert(pVoid);
  return (*reinterpret_cast<std::weak_ptr<::ranbam::iEventQueue>*>(pVoid)).lock();
}

template<typename T, typename... ARGS>
void EnqueueEvent(GLFWwindow *w, ARGS&&... args) {
  auto queue = GetQueue(w);
  const ::ranbam::iEvent::id_t source = reinterpret_cast<uint64_t>(w);
  const ::ranbam::iEvent::id_t destination = 0;
  queue->enqueue(
    std::make_shared<::ranbam::Event<T>>(source, destination, T{std::forward<ARGS>(args)...})
  );
}
}

class Window {
public:
  struct Close { };
  struct Position { int32_t x, y; };
  struct Resize { int32_t width, height; };
  struct FramebufferResize { int32_t width, height; };
  struct Focus { bool focus; };
  struct Key { int32_t key, scancode, action, mods; };
  struct Character { uint32_t codepoint; int32_t mods; };
  struct MouseButton { int32_t button, action, mods; };
  struct CursorEnter { bool focus; };
  struct CursorPosition { double x, y; };
public:
  template<typename... ARGS>
  Window(std::shared_ptr<::ranbam::EventQueue> queue, ARGS&&... args)
    : _event_queue(queue)
    , _window( glfwCreateWindow(std::forward<ARGS>(args)...) )
  {
    assert(_window);
    glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(&_event_queue));
    setup_callbacks(_window);
  }

  ~Window() {
    glfwDestroyWindow(_window);
  }

  void make_context_current() {
    LOCK(_mutex);
    glfwMakeContextCurrent(_window);
  }

  bool should_close() {
    LOCK(_mutex);
    return glfwWindowShouldClose(_window);
  }

  void close(const bool b) {
    LOCK(_mutex);
    glfwSetWindowShouldClose(_window, b ? GLFW_TRUE : GLFW_FALSE);
  }

  void swap() {
    LOCK(_mutex);
    return glfwSwapBuffers(_window);
  }

private:
  void setup_callbacks(GLFWwindow *w) {
    //window
    glfwSetWindowPosCallback(w, [](GLFWwindow *window, int32_t x, int32_t y) {
      _impl::EnqueueEvent<Position>(window, x, y);
    });

    glfwSetWindowSizeCallback(w, [](GLFWwindow *window, int32_t width, int32_t height) {
      _impl::EnqueueEvent<Resize>(window, width, height);
    });

    glfwSetWindowCloseCallback(w, [](GLFWwindow *window) {
      //close in event processing
      glfwSetWindowShouldClose(window, GLFW_FALSE);
      _impl::EnqueueEvent<Close>(window);
    });

    glfwSetWindowFocusCallback(w, [](GLFWwindow *window, int32_t focused) {
      _impl::EnqueueEvent<Focus>(window, (focused != GLFW_FALSE));
    });

    glfwSetFramebufferSizeCallback(w, [](GLFWwindow *window, int32_t width, int32_t height) {
      _impl::EnqueueEvent<FramebufferResize>(window, width, height);
    });

    //inputs
    glfwSetKeyCallback(w, [](GLFWwindow *window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {     
      _impl::EnqueueEvent<Key>(window, key, scancode, action, mods);
    });

    glfwSetCharModsCallback(w, [](GLFWwindow* window, uint32_t codepoint, int32_t mods) {
      _impl::EnqueueEvent<Character>(window, codepoint, mods);
    });

    glfwSetMouseButtonCallback(w, [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods) {
      _impl::EnqueueEvent<MouseButton>(window, button, action, mods);
    });

    glfwSetCursorEnterCallback(w, [](GLFWwindow* window, int32_t entered) {
      _impl::EnqueueEvent<CursorEnter>(window, (entered != GLFW_FALSE));
    });

    glfwSetCursorPosCallback(w, [](GLFWwindow* window, double x, double y) {
      _impl::EnqueueEvent<CursorPosition>(window, x, y);
    });
  }

  std::weak_ptr<::ranbam::iEventQueue> _event_queue;
  std::mutex _mutex;
  GLFWwindow *_window;
};
}
