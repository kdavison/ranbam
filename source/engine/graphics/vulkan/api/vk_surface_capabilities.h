#pragma once

#include <vulkan/vulkan.h>
#include "vk_result.h"

namespace vk {
typedef VkSurfaceCapabilitiesKHR SurfaceCapabilities;

SurfaceCapabilities GetPhysicalDeviceSurfaceCapabilities(
  vk::PhysicalDevice physicalDevice,
  vk::Surface        surface
) {
  SurfaceCapabilities capabilities;
  const auto result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    physicalDevice,
    surface.get(),
    &capabilities
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
  }
  return capabilities;
}
}
