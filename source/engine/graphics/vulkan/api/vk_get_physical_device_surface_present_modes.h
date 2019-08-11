#pragma once

#include "vk_result.h"
#include "vk_physical_device.h"
#include "vk_surface.h"

namespace vk {
typedef VkPresentModeKHR PresentMode;
std::vector<PresentMode> GetPhysicalDeviceSurfacePresentModes(
  vk::PhysicalDevice physicalDevice,
  vk::Surface surface
) {
  vk::Result result;
  uint32_t count(0);
  result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface.get(), &count, nullptr);
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return std::vector<PresentMode>{};
  }
  std::vector<PresentMode> modes(count, PresentMode{});
  result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface.get(), &count, modes.data());
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return std::vector<PresentMode>{};
  }
  return modes;
}
}
