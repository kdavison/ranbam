#pragma once

namespace vk {
typedef std::shared_ptr<std::remove_pointer_t<VkPipelineLayout>> PipelineLayout;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineLayout> create(
  Device                                    device,
  const PipelineLayoutCreateInfo*           pCreateInfo,
  const AllocationCallbacks*                pAllocator
) {
  VkPipelineLayout layout{};
  vk::Result result = vkCreatePipelineLayout(
    device.get(),
    pCreateInfo,
    pAllocator,
    &layout
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return PipelineLayout(nullptr);
  }
  return PipelineLayout(
    std::move(layout),
    [device, pAllocator](VkPipelineLayout p) {
      vkDestroyPipelineLayout(
        device.get(),
        p,
        pAllocator
      );
    }
  );
}

template<typename T>
enable_if_same_t<T, PipelineLayout> create(
  Device                                    device,
  const PipelineLayoutCreateInfo*           pCreateInfo
) {
  VkPipelineLayout layout{};
  vk::Result result = vkCreatePipelineLayout(
    device.get(),
    pCreateInfo,
    nullptr,
    &layout
  );
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return PipelineLayout(nullptr);
  }
  return PipelineLayout(
    std::move(layout),
    [device](VkPipelineLayout p) {
      vkDestroyPipelineLayout(
        device.get(),
        p,
        nullptr
      );
    }
  );
}
}
}
