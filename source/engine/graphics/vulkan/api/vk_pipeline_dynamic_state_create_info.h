#pragma once

namespace vk {
typedef VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, VkPipelineDynamicStateCreateInfo> create(
  const void*                          pNext,
  VkPipelineDynamicStateCreateFlags    flags,
  std::vector<VkDynamicState> const&   states
) {
  return VkPipelineDynamicStateCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .dynamicStateCount = static_cast<uint32_t>(states.size()),
    .pDynamicStates = states.data()
  };
}

template<typename T>
enable_if_same_t<T, VkPipelineDynamicStateCreateInfo> create(
  VkPipelineDynamicStateCreateFlags    flags,
  std::vector<VkDynamicState> const&   states
) {
  return _impl::create<VkPipelineDynamicStateCreateInfo>(
    nullptr,
    flags,
    states
  );
}

template<typename T>
enable_if_same_t<T, VkPipelineDynamicStateCreateInfo> create(
  std::vector<VkDynamicState> const&   states
) {
  return _impl::create<VkPipelineDynamicStateCreateInfo>(
    nullptr,
    0,
    states
  );
}
}
}
