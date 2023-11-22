#pragma once

#include <vulkan/vulkan.h>

namespace vk {
typedef std::shared_ptr<std::remove_pointer_t<VkSwapchainKHR>> Swapchain;
namespace _impl {
template<typename T>
enable_if_same_t<T, Swapchain> create(
  Device device,
  SwapchainCreateInfo* pCreateInfo,
  AllocationCallbacks* pAllocationCallbacks
) {
  VkSwapchainKHR swapchain;
  vk::Result result = vkCreateSwapchainKHR(
    device.get(),
    pCreateInfo,
    pAllocationCallbacks,
    &swapchain
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return Swapchain(nullptr);
  }
  return Swapchain(
    swapchain,
    [device, pAllocationCallbacks](VkSwapchainKHR p) {
      vkDestroySwapchainKHR(device.get(), p, pAllocationCallbacks);
    }
  );
}

template<typename T>
enable_if_same_t<T, Swapchain> create(
  Device device,
  SwapchainCreateInfo* pCreateInfo
) {
  VkSwapchainKHR swapchain;
  vk::Result result = vkCreateSwapchainKHR(
    device.get(),
    pCreateInfo,
    nullptr,
    &swapchain
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return Swapchain(nullptr);
  }
  return Swapchain(
    swapchain,
    [device](VkSwapchainKHR p) {
      vkDestroySwapchainKHR(device.get(), p, nullptr);
    }
  );
}
}
}
