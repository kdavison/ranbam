#pragma once

#include <vulkan/vulkan.h>
#include "vk_convenience.h"

namespace vk {
typedef std::shared_ptr<std::remove_pointer_t<VkImageView>> ImageView;

namespace _impl {
template<typename T>
enable_if_same_t<T, ImageView> create(
    vk::Device                     device,
    const vk::ImageViewCreateInfo* pCreateInfo,
    const vk::AllocationCallbacks* pAllocator
) {
  assert(device);
  assert(pCreateInfo);
  VkImageView image_view;
  vk::Result result = vkCreateImageView(
    device.get(),
    pCreateInfo,
    pAllocator,
    &image_view
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return ImageView(nullptr);
  }
  return ImageView(
    std::move(image_view),
    [device, pAllocator](VkImageView p) {
      vkDestroyImageView(
        device.get(),
        p,
        pAllocator
      );
    }
  );
}

template<typename T>
enable_if_same_t<T, ImageView> create(
    vk::Device                     device,
    const vk::ImageViewCreateInfo* pCreateInfo
) {
  assert(device);
  assert(pCreateInfo);
  VkImageView image_view;
  vk::Result result = vkCreateImageView(
    device.get(),
    pCreateInfo,
    nullptr,
    &image_view
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return ImageView(nullptr);
  }
  return ImageView(
    std::move(image_view),
    [device](VkImageView p) {
      vkDestroyImageView(
        device.get(),
        p,
        nullptr
      );
    }
  );
}
}
}
