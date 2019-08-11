#pragma once

namespace vk {
typedef VkFormatProperties FormatProperties;

FormatProperties GetPhysicalDeviceFormatProperties(
  vk::PhysicalDevice physicalDevice,
  VkFormat format
) {
  VkFormatProperties props;
  vkGetPhysicalDeviceFormatProperties(
    physicalDevice,
    format,
    &props
  );
  return props;
}
}
