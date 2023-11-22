#pragma once

#include <vulkan/vulkan.h>
#include "vk_result.h"
#include "vk_platform_enumeration.h"

namespace vk {
typedef std::shared_ptr<std::remove_pointer_t<VkSurfaceKHR>> Surface;

namespace _impl {
template<typename T>
enable_if_same_t<T, Surface> create(
  vk::Instance                   instance,
  const vk::SurfaceCreateInfo*   pCreateInfo,
  const vk::AllocationCallbacks* pAllocator
) {
  VkSurfaceKHR surface;
  const auto result = vk::_impl::SurfaceCreateInfo::CreateFn(
    instance.get(),
    pCreateInfo,
    pAllocator,
    &surface
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return Surface(nullptr);
  }

  return Surface(surface, [instance, pAllocator](VkSurfaceKHR p) {
    vkDestroySurfaceKHR(instance.get(), p, pAllocator);
  });
}

template<typename T>
enable_if_same_t<T, Surface> create(
  vk::Instance                   instance,
  const vk::SurfaceCreateInfo*   pCreateInfo
) {
  return create<::vk::Surface>(instance, pCreateInfo, nullptr);
}
}
}
