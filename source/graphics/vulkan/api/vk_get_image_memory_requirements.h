#pragma once

namespace vk {
typedef VkMemoryRequirements MemoryRequirements;

MemoryRequirements GetImageMemoryRequirements(
  vk::Device device,
  vk::Image image
) {
  MemoryRequirements result;
  vkGetImageMemoryRequirements(
    device.get(),
    image,
    &result
  );
  return result;
}
}
