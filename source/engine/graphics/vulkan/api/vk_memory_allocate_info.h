#pragma once

namespace vk {
typedef VkMemoryAllocateInfo MemoryAllocateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, MemoryAllocateInfo> create(
  const void*   pNext,
  VkDeviceSize  allocationSize,
  uint32_t      memoryTypeIndex
) {
  return MemoryAllocateInfo {
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext = pNext,
    .allocationSize = allocationSize,
    .memoryTypeIndex = memoryTypeIndex
  };
}

template<typename T>
enable_if_same_t<T, MemoryAllocateInfo> create(
  VkDeviceSize  allocationSize,
  uint32_t      memoryTypeIndex
) {
  return MemoryAllocateInfo {
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext = nullptr,
    .allocationSize = allocationSize,
    .memoryTypeIndex = memoryTypeIndex
  };
}
}
}
