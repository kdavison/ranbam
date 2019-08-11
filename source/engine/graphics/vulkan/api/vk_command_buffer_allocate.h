#pragma once

#include <vulkan/vulkan.h>

namespace vk {

typedef VkCommandBuffer CommandBuffer;

std::vector<vk::CommandBuffer> AllocateCommandBuffers(
  vk::Device                           device,
  const vk::CommandBufferAllocateInfo* pAllocateInfo,
  std::size_t                          CommandBufferCount
) {
  std::vector<vk::CommandBuffer> buffers(CommandBufferCount, vk::CommandBuffer{});
  vk::Result result = vkAllocateCommandBuffers(
    device.get(),
    pAllocateInfo,
    buffers.data()
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return std::vector<vk::CommandBuffer>{};
  }
  return std::move(buffers);
}

}
