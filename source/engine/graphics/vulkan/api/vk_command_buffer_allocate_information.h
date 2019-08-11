#pragma once

#include <vulkan/vulkan.h>

namespace vk {
typedef VkCommandBufferAllocateInfo CommandBufferAllocateInfo;

enum class CommandBufferLevel {
  Primary   = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
  Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
};
namespace _impl {
template<typename T>
enable_if_same_t<T, CommandBufferAllocateInfo> create(
  const void*            pNext,
  vk::CommandPool        commandPool,
  vk::CommandBufferLevel level,
  uint32_t               commandBufferCount
) {
  assert(commandBufferCount > 0);
  return CommandBufferAllocateInfo {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
    .pNext = pNext,
    .commandPool = commandPool.get(),
    .level = static_cast<VkCommandBufferLevel>(level),
    .commandBufferCount = commandBufferCount
  };
}

template<typename T>
enable_if_same_t<T, CommandBufferAllocateInfo> create(
  vk::CommandPool        commandPool,
  vk::CommandBufferLevel level,
  uint32_t               commandBufferCount
) {
  return _impl::create<CommandBufferAllocateInfo>(
    nullptr,
    commandPool,
    level,
    commandBufferCount
  );
}
}
}
