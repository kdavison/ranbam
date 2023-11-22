#pragma once

#include <vulkan/vulkan.h>

namespace vk {
typedef VkImage Image;

std::vector<Image> GetSwapchainImages(
  vk::Device device,
  vk::Swapchain swapchain
) {
  uint32_t count(0);
  vk::Result result = vkGetSwapchainImagesKHR(
    device.get(),
    swapchain.get(),
    &count,
    nullptr
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return std::vector<Image>{};
  }
  std::vector<Image> images(count, Image{});
  result = vkGetSwapchainImagesKHR(
    device.get(),
    swapchain.get(),
    &count,
    images.data()
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return std::vector<Image>{};
  }
  return images;
}

}
