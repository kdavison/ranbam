#pragma once

namespace vk {
typedef VkImageCreateInfo ImageCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, ImageCreateInfo> create(
  const void*              pNext,
  VkImageCreateFlags       flags,
  VkImageType              imageType,
  VkFormat                 format,
  VkExtent3D               extent,
  uint32_t                 mipLevels,
  uint32_t                 arrayLayers,
  VkSampleCountFlagBits    samples,
  VkImageTiling            tiling,
  VkImageUsageFlags        usage,
  VkSharingMode            sharingMode,
  uint32_t                 queueFamilyIndexCount,
  const uint32_t*          pQueueFamilyIndices,
  VkImageLayout            initialLayout
) {
  return ImageCreateInfo {
    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .imageType = imageType,
    .format = format,
    .extent = extent,
    .mipLevels = mipLevels,
    .arrayLayers = arrayLayers,
    .samples = samples,
    .tiling = tiling,
    .usage = usage,
    .sharingMode = sharingMode,
    .queueFamilyIndexCount = queueFamilyIndexCount,
    .pQueueFamilyIndices = pQueueFamilyIndices,
    .initialLayout = initialLayout
  };
}

template<typename T>
enable_if_same_t<T, ImageCreateInfo> create(
  VkImageCreateFlags       flags,
  VkImageType              imageType,
  VkFormat                 format,
  VkExtent3D               extent,
  uint32_t                 mipLevels,
  uint32_t                 arrayLayers,
  VkSampleCountFlagBits    samples,
  VkImageTiling            tiling,
  VkImageUsageFlags        usage,
  VkSharingMode            sharingMode,
  uint32_t                 queueFamilyIndexCount,
  const uint32_t*          pQueueFamilyIndices,
  VkImageLayout            initialLayout
) {
  return _impl::create<ImageCreateInfo>(
    nullptr,
    flags,
    imageType,
    format,
    extent,
    mipLevels,
    arrayLayers,
    samples,
    tiling,
    usage,
    sharingMode,
    queueFamilyIndexCount,
    pQueueFamilyIndices,
    initialLayout
  );
}
}
}
