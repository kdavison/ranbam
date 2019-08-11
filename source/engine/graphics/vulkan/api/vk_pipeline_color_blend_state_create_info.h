#pragma once

namespace vk {
typedef VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineColorBlendStateCreateInfo> create(
  const void*                                           pNext,
  VkPipelineColorBlendStateCreateFlags                  flags,
  VkBool32                                              logicOpEnable,
  VkLogicOp                                             logicOp,
  std::vector<PipelineColorBlendAttachmentState> const& Attachments,
  std::array<float, 4> const&                           blendConstants
) {
  return PipelineColorBlendStateCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .logicOpEnable = logicOpEnable,
    .logicOp = logicOp,
    .attachmentCount = static_cast<uint32_t>(Attachments.size()),
    .pAttachments = Attachments.data(),
    .blendConstants = {
      blendConstants[0],
      blendConstants[1],
      blendConstants[2],
      blendConstants[3]
    }
  };
}

template<typename T>
enable_if_same_t<T, PipelineColorBlendStateCreateInfo> create(
  VkPipelineColorBlendStateCreateFlags                  flags,
  VkBool32                                              logicOpEnable,
  VkLogicOp                                             logicOp,
  std::vector<PipelineColorBlendAttachmentState> const& Attachments,
  std::array<float, 4> const&                           blendConstants
) {
  return _impl::create<PipelineColorBlendStateCreateInfo>(
    nullptr,
    flags,
    logicOpEnable,
    logicOp,
    Attachments,
    blendConstants
  );
}

template<typename T>
enable_if_same_t<T, PipelineColorBlendStateCreateInfo> create(
  VkBool32                                              logicOpEnable,
  VkLogicOp                                             logicOp,
  std::vector<PipelineColorBlendAttachmentState> const& Attachments,
  std::array<float, 4> const&                           blendConstants
) {
  return _impl::create<PipelineColorBlendStateCreateInfo>(
    nullptr,
    0,
    logicOpEnable,
    logicOp,
    Attachments,
    blendConstants
  );
}
}
}
