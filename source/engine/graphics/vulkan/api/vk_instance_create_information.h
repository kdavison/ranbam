#pragma once

#include <vulkan/vulkan.h>
#include "vk_application_information.h"
#include <vector>

namespace vk {
typedef VkInstanceCreateInfo InstanceCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T,InstanceCreateInfo> create(
    void*                           pNext,
    VkInstanceCreateFlags           flags,
    const ApplicationInfo*      pApplicationInfo,
    std::vector<const char*> const& Layers,
    std::vector<const char*> const& Extensions
) {
  return InstanceCreateInfo{
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pNext = static_cast<void*>(pNext),
    .flags = flags,
    .pApplicationInfo = pApplicationInfo,
    .enabledLayerCount = static_cast<uint32_t>(Layers.size()),
    .ppEnabledLayerNames = Layers.data(),
    .enabledExtensionCount = static_cast<uint32_t>(Extensions.size()),
    .ppEnabledExtensionNames = Extensions.data()
  };
}

template<typename T>
enable_if_same_t<T,InstanceCreateInfo> create(
    VkInstanceCreateFlags           flags,
    const ApplicationInfo*      pApplicationInfo,
    std::vector<const char*> const& Layers,
    std::vector<const char*> const& Extensions
) {
  return _impl::create<InstanceCreateInfo>(
    nullptr,
    flags,
    pApplicationInfo,
    Layers,
    Extensions
  );
}

template<typename T>
enable_if_same_t<T,InstanceCreateInfo> create(
    const vk::ApplicationInfo*      pApplicationInfo,
    std::vector<const char*> const& Layers,
    std::vector<const char*> const& Extensions
) {
  return _impl::create<InstanceCreateInfo>(
    0,
    pApplicationInfo,
    Layers,
    Extensions
  );
}
}
}
