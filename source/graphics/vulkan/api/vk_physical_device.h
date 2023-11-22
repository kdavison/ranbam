#pragma once

#include <vulkan/vulkan.h>
#include "vk_instance.h"
#include <vector>

namespace vk
{
typedef VkPhysicalDevice PhysicalDevice;

std::vector<vk::PhysicalDevice> GetPhysicalDevices(vk::Instance instance) {
  uint32_t count(0);
  vk:Result result = vkEnumeratePhysicalDevices(instance.get(), &count, nullptr);
  if(!vk::is_error(result)) {
    std::vector<PhysicalDevice> devices(count, PhysicalDevice{});
    result = vkEnumeratePhysicalDevices(instance.get(), &count, const_cast<PhysicalDevice*>(devices.data()));
    if(!vk::is_error(result)) {
      return devices;
    }
  }
  vk::handle_code(result);
  return std::vector<PhysicalDevice>{};
}

}
