#pragma once

#include <vulkan/vulkan.h>
#include "vk_result.h"

namespace vk {
typedef std::shared_ptr<std::remove_pointer_t<VkCommandPool>> CommandPool;

namespace _impl {
template<typename T>
enable_if_same_t<T, CommandPool> create(
  vk::Device                       device,
  const vk::CommandPoolCreateInfo* pCreateInfo,
  const vk::AllocationCallbacks*   pAllocator
) {
  assert(pCreateInfo);
  VkCommandPool command_pool;
  vk::Result result = vkCreateCommandPool(
    device.get(),
    pCreateInfo,
    pAllocator,
    &command_pool
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return CommandPool(nullptr);
  }
  return CommandPool(
    std::move(command_pool),
    [device, pAllocator](VkCommandPool p) {
      vkDestroyCommandPool(device.get(), p, pAllocator);
    }
  );
}

template<typename T>
enable_if_same_t<T, CommandPool> create(
  vk::Device                       device,
  const vk::CommandPoolCreateInfo* pCreateInfo
) {
  return _impl::create<CommandPool>(
    device,
    pCreateInfo,
    nullptr
  );
}
}
}
