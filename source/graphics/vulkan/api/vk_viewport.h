#pragma once

namespace vk {
typedef VkViewport Viewport;

namespace _impl {
template<typename T>
enable_if_same_t<T, Viewport> create(
  float    x,
  float    y,
  float    width,
  float    height,
  float    minDepth,
  float    maxDepth
) {
  assert(width > 0 && height > 0);
  return Viewport {
    x,
    y,
    width,
    height,
    minDepth,
    maxDepth
  };
}
}
}
