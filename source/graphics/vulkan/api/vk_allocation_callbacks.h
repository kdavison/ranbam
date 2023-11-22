#pragma once

#include <vulkan/vulkan.h>
#include "vk_convenience.h"

namespace vk {
typedef VkAllocationCallbacks AllocationCallbacks;

namespace _impl {
template<typename T>
enable_if_same_t<T, AllocationCallbacks> create(
    void*                                   pUserData,
    PFN_vkAllocationFunction                pfnAllocation,
    PFN_vkReallocationFunction              pfnReallocation,
    PFN_vkFreeFunction                      pfnFree,
    PFN_vkInternalAllocationNotification    pfnInternalAllocation,
    PFN_vkInternalFreeNotification          pfnInternalFree
) {
  return AllocationCallbacks {
    .pUserData = pUserData,
    .pfnAllocation = pfnAllocation,
    .pfnReallocation = pfnReallocation,
    .pfnFree = pfnFree,
    .pfnInternalAllocation = pfnInternalAllocation,
    .pfnInternalFree = pfnInternalFree
  };
}

template<typename T>
enable_if_same_t<T, AllocationCallbacks> create(
    PFN_vkAllocationFunction                pfnAllocation,
    PFN_vkReallocationFunction              pfnReallocation,
    PFN_vkFreeFunction                      pfnFree,
    PFN_vkInternalAllocationNotification    pfnInternalAllocation,
    PFN_vkInternalFreeNotification          pfnInternalFree
) {
  return _impl::create<AllocationCallbacks>(
    nullptr,
    pfnAllocation,
    pfnReallocation,
    pfnFree,
    pfnInternalAllocation,
    pfnInternalFree
  );
}
}
}
