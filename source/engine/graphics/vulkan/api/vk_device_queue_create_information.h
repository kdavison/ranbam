#pragma once

#include <vulkan/vulkan.h>
#include "vk_convenience.h"
#include <vector>

namespace vk {
typedef VkDeviceQueueCreateInfo DeviceQueueCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T,DeviceQueueCreateInfo> create(
  const void*                pNext,
  VkDeviceQueueCreateFlags   flags,
  uint32_t                   queueFamilyIndex,
  std::vector<float> const&  QueuePriorities
) {
  return DeviceQueueCreateInfo {
    .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .queueFamilyIndex = queueFamilyIndex,
    .queueCount = static_cast<uint32_t>(QueuePriorities.size()),
    .pQueuePriorities = QueuePriorities.data()
  };
}

template<typename T>
enable_if_same_t<T,DeviceQueueCreateInfo> create(
  VkDeviceQueueCreateFlags   flags,
  uint32_t                   queueFamilyIndex,
  std::vector<float> const&  QueuePriorities
) {
  return DeviceQueueCreateInfo {
    .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    .pNext = nullptr,
    .flags = flags,
    .queueFamilyIndex = queueFamilyIndex,
    .queueCount = static_cast<uint32_t>(QueuePriorities.size()),
    .pQueuePriorities = QueuePriorities.data()
  };
}

template<typename T>
enable_if_same_t<T,DeviceQueueCreateInfo> create(
  uint32_t                   queueFamilyIndex,
  std::vector<float> const&  QueuePriorities
) {
  return _impl::create<DeviceQueueCreateInfo>(
    nullptr,
    0,
    queueFamilyIndex,
    QueuePriorities
  );
}
}
}
