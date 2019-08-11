#pragma once

namespace vk {
typedef std::shared_ptr<std::remove_pointer_t<VkDeviceMemory>> DeviceMemory;

DeviceMemory AllocateMemory(
  Device                      device,
  const MemoryAllocateInfo*   pAllocateInfo,
  const AllocationCallbacks*  pAllocator
) {
  VkDeviceMemory memory;
  vk::Result result = vkAllocateMemory(
    device.get(),
    pAllocateInfo,
    pAllocator,
    &memory
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
  }
  return DeviceMemory(
    std::move(memory),
    [device, pAllocator](VkDeviceMemory p) {
      vkFreeMemory(
        device.get(),
        p,
        pAllocator
      );
    }
  );
}

DeviceMemory AllocateMemory(
  Device                      device,
  const MemoryAllocateInfo*   pAllocateInfo
) {
  VkDeviceMemory memory;
  vk::Result result = vkAllocateMemory(
    device.get(),
    pAllocateInfo,
    nullptr,
    &memory
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
  }
  return DeviceMemory(
    std::move(memory),
    [device](VkDeviceMemory p) {
      vkFreeMemory(
        device.get(),
        p,
        nullptr
      );
    }
  );
}
}
