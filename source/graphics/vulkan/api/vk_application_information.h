#pragma once

#include <vulkan/vulkan.h>
#include "vk_convenience.h"

namespace vk {
typedef VkApplicationInfo ApplicationInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T,ApplicationInfo> create(
    void* pNext,
    const char*        pApplicationName,
    uint32_t           applicationVersion,
    const char*        pEngineName,
    uint32_t           engineVersion,
    uint32_t           apiVersion
) {
  return ApplicationInfo {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pNext = pNext,
    .pApplicationName = pApplicationName,
    .applicationVersion = applicationVersion,
    .pEngineName = pEngineName,
    .engineVersion = engineVersion,
    .apiVersion = apiVersion
  };
}

template<typename T>
enable_if_same_t<T,ApplicationInfo> create(
    const char*        pApplicationName,
    uint32_t           applicationVersion,
    const char*        pEngineName,
    uint32_t           engineVersion,
    uint32_t           apiVersion
) {
  return _impl::create<ApplicationInfo>(
    nullptr,
    pApplicationName,
    applicationVersion,
    pEngineName,
    engineVersion,
    apiVersion
  );
}
}
}
