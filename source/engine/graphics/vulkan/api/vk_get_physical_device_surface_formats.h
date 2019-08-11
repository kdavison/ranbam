#pragma once

#include <vulkan/vulkan.h>

namespace vk {
typedef VkSurfaceFormatKHR SurfaceFormat;
typedef VkColorSpaceKHR ColorSpace;

std::vector<SurfaceFormat> GetPhysicalDeviceSurfaceFormats(
  PhysicalDevice physicalDevice,
  Surface surface
) {
  uint32_t count(0);
  vk::Result result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface.get(), &count, nullptr);
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return std::vector<SurfaceFormat>{};
  }
  std::vector<SurfaceFormat> formats(count, SurfaceFormat{});
  result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface.get(), &count, formats.data());
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return std::vector<SurfaceFormat>{};
  }
  return formats;
}
}
