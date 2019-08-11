#pragma once

#include <vulkan/vulkan.h>

namespace vk {
typedef VkDeviceCreateInfo DeviceCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, DeviceCreateInfo> create(
  const void*                                   pNext,
  VkDeviceCreateFlags                           flags,
  std::vector<vk::DeviceQueueCreateInfo> const& QueueCreateInfo,
  std::vector<const char*> const&               Layers,
  std::vector<const char*> const&               Extensions,
  const VkPhysicalDeviceFeatures*               pEnabledFeatures
) {
  return DeviceCreateInfo {
    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .queueCreateInfoCount = static_cast<uint32_t>(QueueCreateInfo.size()),
    .pQueueCreateInfos = QueueCreateInfo.data(),
    .enabledLayerCount = static_cast<uint32_t>(Layers.size()),
    .ppEnabledLayerNames = Layers.data(),
    .enabledExtensionCount = static_cast<uint32_t>(Extensions.size()),
    .ppEnabledExtensionNames = Extensions.data(),
    .pEnabledFeatures = pEnabledFeatures
  };
}

template<typename T>
enable_if_same_t<T, DeviceCreateInfo> create(
  VkDeviceCreateFlags                           flags,
  std::vector<vk::DeviceQueueCreateInfo> const& QueueCreateInfo,
  std::vector<const char*> const&               Layers,
  std::vector<const char*> const&               Extensions,
  const VkPhysicalDeviceFeatures*               pEnabledFeatures
) {
  return _impl::create<DeviceCreateInfo>(
    nullptr,
    flags,
    QueueCreateInfo,
    Layers,
    Extensions,
    pEnabledFeatures
  );
}

template<typename T>
enable_if_same_t<T, DeviceCreateInfo> create(
  std::vector<vk::DeviceQueueCreateInfo> const& QueueCreateInfo,
  std::vector<const char*> const&               Layers,
  std::vector<const char*> const&               Extensions,
  const VkPhysicalDeviceFeatures*               pEnabledFeatures
) {
  return _impl::create<DeviceCreateInfo>(
    nullptr,
    0,
    QueueCreateInfo,
    Layers,
    Extensions,
    pEnabledFeatures
  );
}
}
}
