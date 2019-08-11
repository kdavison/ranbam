#pragma once

namespace vk {
typedef VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineMultisampleStateCreateInfo> create(
    const void*                              pNext,
    VkPipelineMultisampleStateCreateFlags    flags,
    VkSampleCountFlagBits                    rasterizationSamples,
    VkBool32                                 sampleShadingEnable,
    float                                    minSampleShading,
    const VkSampleMask*                      pSampleMask,
    VkBool32                                 alphaToCoverageEnable,
    VkBool32                                 alphaToOneEnable
) {
  return PipelineMultisampleStateCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .rasterizationSamples = rasterizationSamples,
    .sampleShadingEnable = sampleShadingEnable,
    .minSampleShading = minSampleShading,
    .pSampleMask = pSampleMask,
    .alphaToCoverageEnable = alphaToCoverageEnable,
    .alphaToOneEnable = alphaToOneEnable
  };
}

template<typename T>
enable_if_same_t<T, PipelineMultisampleStateCreateInfo> create(
    VkPipelineMultisampleStateCreateFlags    flags,
    VkSampleCountFlagBits                    rasterizationSamples,
    VkBool32                                 sampleShadingEnable,
    float                                    minSampleShading,
    const VkSampleMask*                      pSampleMask,
    VkBool32                                 alphaToCoverageEnable,
    VkBool32                                 alphaToOneEnable
) {
  return _impl::create<PipelineMultisampleStateCreateInfo>(
    nullptr,
    flags,
    rasterizationSamples,
    sampleShadingEnable,
    minSampleShading,
    pSampleMask,
    alphaToCoverageEnable,
    alphaToOneEnable
  );
}

template<typename T>
enable_if_same_t<T, PipelineMultisampleStateCreateInfo> create(
    VkSampleCountFlagBits                    rasterizationSamples,
    VkBool32                                 sampleShadingEnable,
    float                                    minSampleShading,
    const VkSampleMask*                      pSampleMask,
    VkBool32                                 alphaToCoverageEnable,
    VkBool32                                 alphaToOneEnable
) {
  return _impl::create<PipelineMultisampleStateCreateInfo>(
    nullptr,
    0,
    rasterizationSamples,
    sampleShadingEnable,
    minSampleShading,
    pSampleMask,
    alphaToCoverageEnable,
    alphaToOneEnable
  );
}
}
}
