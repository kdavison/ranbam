#pragma once

#include <vulkan/vulkan.h>
#include "vk_platform_enumeration.h"

namespace vk {
typedef vk::_impl::SurfaceCreateInfo::type SurfaceCreateInfo;

namespace _impl {
template<typename T, typename... ARGS>
enable_if_same_t<T, SurfaceCreateInfo> create(
  const void* pNext,
  uint32_t    flags,
  ARGS&&... args
) {
  return SurfaceCreateInfo{
    .sType = vk::_impl::SurfaceCreateInfo::stype,
    .pNext = pNext,
    .flags = flags,
    std::forward<ARGS>(args)...
  };
}

template<typename T, typename... ARGS>
enable_if_same_t<T, SurfaceCreateInfo> create(
  uint32_t    flags,
  ARGS&&... args
) {
  return _impl::create<SurfaceCreateInfo>(
    nullptr,
    flags,
    std::forward<ARGS>(args)...
  );
}

template<typename T, typename... ARGS>
enable_if_same_t<T, SurfaceCreateInfo> create(
  ARGS&&... args
) {
  return _impl::create<SurfaceCreateInfo>(
    nullptr,
    0,
    std::forward<ARGS>(args)...
  );
}
}
}
