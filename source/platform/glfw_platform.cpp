#include <GLFW/glfw3.h>
#include "glfw_platform.h"
#include <stdexcept>

namespace ranbam::platform
{
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

Platform::Platform(std::shared_ptr<::ranbam::iEventQueue> const& spEventQueue) 
  : _spEventQueue(spEventQueue)
{
  assert(_spEventQueue);
  if(glfwInit() == false) { throw std::runtime_error("glfw failed to initialize"); }
}

Platform::~Platform() {
  glfwTerminate();
}

std::shared_ptr<::ranbam::iWindow> Platform::create_window(const std::string& title, std::size_t width, std::size_t height) {
  return std::make_shared<GLFWwindow, decltype(glfwDestroyWindow)>(std::forward<ARGS>(args)..., glfwDestroyWindow);
}

std::size_t Platform::poll_events(std::shared_ptr<iWindow>& window) {
  glfwPollEvents();
  return _spEventQueue.size();
}

std::size_t Platform::vsync() {
  return _vsync;
}

void Platform::vsync(const std::size_t s) {
  _vsync = s;
  glfwSwapInterval(_vsync);
}
}
}
