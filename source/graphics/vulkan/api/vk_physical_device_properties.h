#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk
{
typedef VkPhysicalDeviceProperties PhysicalDeviceProperties;

namespace _impl {
template<typename T>
enable_if_same_t<T, PhysicalDeviceProperties> create(vk::PhysicalDevice physicalDevice) {
  PhysicalDeviceProperties properties;
  vkGetPhysicalDeviceProperties(physicalDevice, &properties);
  return properties;
}
}
}
