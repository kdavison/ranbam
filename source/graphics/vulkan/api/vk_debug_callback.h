#pragma once

#include <vulkan/vulkan.h>
#include "vk_convenience.h"
#include "vk_instance.h"
#include <memory>
#include <cassert>

namespace vk {
typedef VkDebugReportCallbackCreateInfoEXT DebugReportCallbackCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, DebugReportCallbackCreateInfo> create(
    const void*                     pNext,
    VkDebugReportFlagsEXT           flags,
    PFN_vkDebugReportCallbackEXT    pfnCallback,
    void*                           pUserData
) {
  return DebugReportCallbackCreateInfo {
    .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
    .pNext = pNext,
    .flags = flags,
    .pfnCallback = pfnCallback,
    .pUserData = pUserData
  };
}

template<typename T>
enable_if_same_t<T, DebugReportCallbackCreateInfo> create(
    VkDebugReportFlagsEXT           flags,
    PFN_vkDebugReportCallbackEXT    pfnCallback,
    void*                           pUserData
) {
  return _impl::create<DebugReportCallbackCreateInfo>(
    nullptr,
    flags,
    pfnCallback,
    pUserData
  );
}
}

typedef std::shared_ptr<std::remove_pointer_t<VkDebugReportCallbackEXT>> DebugReportCallback;
namespace _impl {
template<typename T>
enable_if_same_t<T, DebugReportCallback> create(
  Instance instance,
  const DebugReportCallbackCreateInfo* pCreateInfo,
  const AllocationCallbacks* pAllocator
) {
  assert(instance);
  auto CreateDebugReportCallback = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance.get(), "vkCreateDebugReportCallbackEXT"));
  auto DestroyDebugReportCallback = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance.get(), "vkDestroyDebugReportCallbackEXT"));
  assert(CreateDebugReportCallback);
  assert(DestroyDebugReportCallback);

  VkDebugReportCallbackEXT callback;
  vk::Result result = CreateDebugReportCallback(
    instance.get(),
    pCreateInfo,
    pAllocator,
    &callback
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return DebugReportCallback(nullptr);
  }
  return DebugReportCallback(
    std::move(callback),
    [instance, pAllocator, DestroyDebugReportCallback](VkDebugReportCallbackEXT p) {
      DestroyDebugReportCallback(
        instance.get(),
        p,
        pAllocator
      );
    }
  );
}

template<typename T>
enable_if_same_t<T, DebugReportCallback> create(
  Instance instance,
  const DebugReportCallbackCreateInfo* pCreateInfo
) {
  assert(instance);
  auto CreateDebugReportCallback = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance.get(), "vkCreateDebugReportCallbackEXT"));
  auto DestroyDebugReportCallback = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance.get(), "vkDestroyDebugReportCallbackEXT"));
  assert(CreateDebugReportCallback);
  assert(DestroyDebugReportCallback);

  VkDebugReportCallbackEXT callback;
  vk::Result result = CreateDebugReportCallback(
    instance.get(),
    pCreateInfo,
    nullptr,
    &callback
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return DebugReportCallback(nullptr);
  }
  return DebugReportCallback(
    std::move(callback),
    [instance, DestroyDebugReportCallback](VkDebugReportCallbackEXT p) {
      DestroyDebugReportCallback(
        instance.get(),
        p,
        nullptr
      );
    }
  );
}
}
}
