#pragma once

#include <vulkan/vulkan.h>

namespace vk {
typedef VkImageViewCreateInfo ImageViewCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, ImageViewCreateInfo> create(
  const void*                pNext,
  VkImageViewCreateFlags     flags,
  vk::Image                  image,
  VkImageViewType            viewType,
  VkFormat                   format,
  VkComponentMapping         components,
  VkImageSubresourceRange    subresourceRange
) {
  return ImageViewCreateInfo {
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .image = image,
    .viewType = viewType,
    .format = format,
    .components = components,
    .subresourceRange = subresourceRange
  };
}

template<typename T>
enable_if_same_t<T, ImageViewCreateInfo> create(
  VkImageViewCreateFlags     flags,
  vk::Image                  image,
  VkImageViewType            viewType,
  VkFormat                   format,
  VkComponentMapping         components,
  VkImageSubresourceRange    subresourceRange
) {
  return _impl::create<ImageViewCreateInfo>(
    nullptr,
    flags,
    image,
    viewType,
    format,
    components,
    subresourceRange    
  );
}

template<typename T>
enable_if_same_t<T, ImageViewCreateInfo> create(
  vk::Image                  image,
  VkImageViewType            viewType,
  VkFormat                   format,
  VkComponentMapping         components,
  VkImageSubresourceRange    subresourceRange
) {
  return _impl::create<ImageViewCreateInfo>(
    nullptr,
    0,
    image,
    viewType,
    format,
    components,
    subresourceRange    
  );
}
}
}
