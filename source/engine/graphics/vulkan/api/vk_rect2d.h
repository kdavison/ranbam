#pragma once

namespace vk {
typedef VkRect2D Rect2D;

namespace _impl {
template<typename T>
enable_if_same_t<T, Rect2D> create(
  VkOffset2D    offset,
  VkExtent2D    extent
) {
  return Rect2D {
    offset,
    extent
  };
}
}
}
