#pragma once

#include <vulkan/vulkan.h>
#include "vk_result.h"
#include "vk_device_create_information.h"

namespace vk {
typedef std::shared_ptr<std::remove_pointer_t<VkDevice>> Device;

namespace _impl {
template<typename T>
enable_if_same_t<T, Device> create(
  vk::PhysicalDevice            physicalDevice,
  const vk::DeviceCreateInfo    *pCreateInfo,
  const vk::AllocationCallbacks *pAllocator
) {
  assert(pCreateInfo);
  VkDevice device;
  vk::Result result = vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, &device);
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return Device(nullptr);
  }
  return Device(
    std::move(device),
    [pAllocator](VkDevice p) {
      vkDestroyDevice(p, pAllocator);
    }
  );
}

template<typename T>
enable_if_same_t<T, Device> create(
  vk::PhysicalDevice            physicalDevice,
  const vk::DeviceCreateInfo    *pCreateInfo
) {
  return _impl::create<Device>(
    physicalDevice,
    pCreateInfo,
    nullptr
  );
}
}
}
