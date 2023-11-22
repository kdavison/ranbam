#pragma once

namespace vk {
typedef VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentState;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineColorBlendAttachmentState> create(
  VkBool32                 blendEnable,
  VkBlendFactor            srcColorBlendFactor,
  VkBlendFactor            dstColorBlendFactor,
  VkBlendOp                colorBlendOp,
  VkBlendFactor            srcAlphaBlendFactor,
  VkBlendFactor            dstAlphaBlendFactor,
  VkBlendOp                alphaBlendOp,
  VkColorComponentFlags    colorWriteMask
) {
  return PipelineColorBlendAttachmentState {
    .blendEnable = blendEnable,
    .srcColorBlendFactor = srcColorBlendFactor,
    .dstColorBlendFactor = dstColorBlendFactor,
    .colorBlendOp = colorBlendOp,
    .srcAlphaBlendFactor = srcAlphaBlendFactor,
    .dstAlphaBlendFactor = dstAlphaBlendFactor,
    .alphaBlendOp = alphaBlendOp,
    .colorWriteMask = colorWriteMask
  };
}
}
}
