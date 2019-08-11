#pragma once

namespace vk {
typedef VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineDepthStencilStateCreateInfo> create(
    const void*                               pNext,
    VkPipelineDepthStencilStateCreateFlags    flags,
    VkBool32                                  depthTestEnable,
    VkBool32                                  depthWriteEnable,
    VkCompareOp                               depthCompareOp,
    VkBool32                                  depthBoundsTestEnable,
    VkBool32                                  stencilTestEnable,
    VkStencilOpState                          front,
    VkStencilOpState                          back,
    float                                     minDepthBounds,
    float                                     maxDepthBounds
) {
  return PipelineDepthStencilStateCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .depthTestEnable = depthTestEnable,
    .depthWriteEnable = depthWriteEnable,
    .depthCompareOp = depthCompareOp,
    .depthBoundsTestEnable = depthBoundsTestEnable,
    .stencilTestEnable = stencilTestEnable,
    .front = front,
    .back = back,
    .minDepthBounds = minDepthBounds,
    .maxDepthBounds = maxDepthBounds
  };
}

template<typename T>
enable_if_same_t<T, PipelineDepthStencilStateCreateInfo> create(
    VkPipelineDepthStencilStateCreateFlags    flags,
    VkBool32                                  depthTestEnable,
    VkBool32                                  depthWriteEnable,
    VkCompareOp                               depthCompareOp,
    VkBool32                                  depthBoundsTestEnable,
    VkBool32                                  stencilTestEnable,
    VkStencilOpState                          front,
    VkStencilOpState                          back,
    float                                     minDepthBounds,
    float                                     maxDepthBounds
) {
  return _impl::create<PipelineDepthStencilStateCreateInfo>(
    nullptr,
    flags,
    depthTestEnable,
    depthWriteEnable,
    depthCompareOp,
    depthBoundsTestEnable,
    stencilTestEnable,
    front,
    back,
    minDepthBounds,
    maxDepthBounds
  );
}

template<typename T>
enable_if_same_t<T, PipelineDepthStencilStateCreateInfo> create(
    VkBool32                                  depthTestEnable,
    VkBool32                                  depthWriteEnable,
    VkCompareOp                               depthCompareOp,
    VkBool32                                  depthBoundsTestEnable,
    VkBool32                                  stencilTestEnable,
    VkStencilOpState                          front,
    VkStencilOpState                          back,
    float                                     minDepthBounds,
    float                                     maxDepthBounds
) {
  return _impl::create<PipelineDepthStencilStateCreateInfo>(
    nullptr,
    0,
    depthTestEnable,
    depthWriteEnable,
    depthCompareOp,
    depthBoundsTestEnable,
    stencilTestEnable,
    front,
    back,
    minDepthBounds,
    maxDepthBounds
  );
}

}
}
