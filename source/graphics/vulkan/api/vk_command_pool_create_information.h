#pragma once

#include <vulkan/vulkan.h>

namespace vk {
typedef VkCommandPoolCreateInfo CommandPoolCreateInfo;

enum class CommandPoolCreateFlags {
  EMPTY           = 0,
  CreateTransient = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
  CreateReset     = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
};

namespace _impl {
template<typename T>
enable_if_same_t<T, CommandPoolCreateInfo> create(
  const void*            pNext,
  CommandPoolCreateFlags flags,
  uint32_t               queueFamilyIndex
) {
  return CommandPoolCreateInfo {
    .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext = pNext,
    .flags = static_cast<uint32_t>(flags),
    .queueFamilyIndex = queueFamilyIndex
  };
}

template<typename T>
enable_if_same_t<T, CommandPoolCreateInfo> create(
  CommandPoolCreateFlags flags,
  uint32_t               queueFamilyIndex
) {
  return _impl::create<CommandPoolCreateInfo>(
    nullptr,
    flags,
    queueFamilyIndex
  );
}
}
}
