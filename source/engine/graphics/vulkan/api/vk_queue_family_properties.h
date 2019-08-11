#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <bitset>

namespace vk
{
typedef VkQueueFamilyProperties QueueFamilyProperties;

enum class QueueFlags {
  Graphics      = VK_QUEUE_GRAPHICS_BIT,
  Compute       = VK_QUEUE_COMPUTE_BIT,
  Transfer      = VK_QUEUE_TRANSFER_BIT,
  SparseBinding = VK_QUEUE_SPARSE_BINDING_BIT,
  Protected     = VK_QUEUE_PROTECTED_BIT
};
typedef std::bitset<4> QueueFlagBits;

std::vector<QueueFamilyProperties> GetQueueFamilyProperties(vk::PhysicalDevice& device) {
  uint32_t count(0);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
  std::vector<QueueFamilyProperties> qfp(count, QueueFamilyProperties{});
  vkGetPhysicalDeviceQueueFamilyProperties(device, &count, const_cast<QueueFamilyProperties*>(qfp.data()));
  return qfp;
}
}
