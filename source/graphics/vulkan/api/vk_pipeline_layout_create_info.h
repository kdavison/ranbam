#pragma once

namespace vk {
typedef VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineLayoutCreateInfo> create(
    const void*                               pNext,
    VkPipelineLayoutCreateFlags               flags,
    std::vector<VkDescriptorSetLayout> const& SetLayouts,
    std::vector<VkPushConstantRange>   const& PushConstantRanges
) {
  return PipelineLayoutCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .setLayoutCount = static_cast<uint32_t>(SetLayouts.size()),
    .pSetLayouts = SetLayouts.data(),
    .pushConstantRangeCount = static_cast<uint32_t>(PushConstantRanges.size()),
    .pPushConstantRanges = PushConstantRanges.data()
  };
}

template<typename T>
enable_if_same_t<T, PipelineLayoutCreateInfo> create(
    VkPipelineLayoutCreateFlags               flags,
    std::vector<VkDescriptorSetLayout> const& SetLayouts,
    std::vector<VkPushConstantRange>   const& PushConstantRanges
) {
  return _impl::create<PipelineLayoutCreateInfo>(
    nullptr,
    flags,
    SetLayouts,
    PushConstantRanges
  );
}

template<typename T>
enable_if_same_t<T, PipelineLayoutCreateInfo> create(
    std::vector<VkDescriptorSetLayout> const& SetLayouts,
    std::vector<VkPushConstantRange>   const& PushConstantRanges
) {
  return _impl::create<PipelineLayoutCreateInfo>(
    nullptr,
    0,
    SetLayouts,
    PushConstantRanges
  );
}
}
}
