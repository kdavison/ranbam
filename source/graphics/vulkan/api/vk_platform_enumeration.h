#pragma once
/*
** I would have loved to call this
**   vk_platform.h
** but that is already taken by vulkan itself... for some reason lol
*/

#include <vulkan/vulkan.h>

namespace vk {
//typedef enum _platform : uint8_t {
  //UNKNOWN = 0,
  //ANDROID,
  //IOS,
  //MACOS,
  //MIR,
  //VI,
  //WAYLAND,
  //WINDOWS,
  //XCB,
  //XLIB,
  //XLIB_XRANDR
//} platform_t;

#ifdef VK_USE_PLATFORM_ANDROID_KHR
namespace _impl {
struct SurfaceCreateInfo {
  typedef VkAndroidSurfaceCreateInfoKHR type;
  static constexpr VkStructureType stype = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
  static constexpr auto CreateFn = vkCreateAndroidSurfaceKHR;
};
}
#endif
#ifdef VK_USE_PLATFORM_IOS_MVK
namespace _impl {
struct SurfaceCreateInfo {
  typedef VkMacOSSurfaceCreateInfoMVK type;
  static constexpr VkStructureType stype = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
  static constexpr auto CreateFn = vkCreateIOSSurfaceMVK;
};
}
#endif
#ifdef VK_USE_PLATFORM_MACOS_MVK
namespace _impl {
struct SurfaceCreateInfo {
  typedef VkIOSSurfaceCreateInfoMVK type;
  static constexpr VkStructureType stype = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
  static constexpr auto CreateFn = vkCreateMacOSSurfaceMVK;
};
}
#endif
#ifdef VK_USE_PLATFORM_MIR_KHR
namespace _impl {
struct SurfaceCreateInfo {
  typedef VkMirSurfaceCreateInfoKHR type;
  static constexpr VkStructureType stype = VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR;
  static constexpr auto CreateFn = vkCreateMirSurfaceKHR;
};
}
#endif
#ifdef VK_USE_PLATFORM_VI_NN
namespace _impl {
struct SurfaceCreateInfo {
  typedef VkViSurfaceCreateInfoNN type;
  static constexpr stype = VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN;
  static constexpr auto CreateFn = vkCreateViSurfaceNN;
};
}
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
namespace _impl {
struct SurfaceCreateInfo {
  typedef VkWaylandSurfaceCreateInfoKHR type;
  static constexpr VkStructureType stype = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
  static constexpr auto CreateFn = vkCreateWaylandSurfaceKHR;
};
}
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
namespace _impl {
struct SurfaceCreateInfo {
  typedef VkWin32SurfaceCreateInfoKHR type;
  static constexpr VkStructureType stype = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  static constexpr auto CreateFn = vkCreateWin32SurfaceKHR;
};
}
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
namespace _impl {
struct SurfaceCreateInfo {
  typedef VkXcbSurfaceCreateInfoKHR type;
  static constexpr VkStructureType stype = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
  static constexpr auto CreateFn = vkCreateXcbSurfaceKHR;
};
}
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
namespace _impl {
struct SurfaceCreateInfo {
  typedef VkXlibSurfaceCreateInfoKHR type;
  static constexpr VkStructureType stype = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
  static constexpr auto CreateFn = vkCreateXlibSurfaceKHR;
};
}
#endif
#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
#error "idk how to support this... yet"
#endif
}
