#pragma once

namespace vk {
typedef VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineRasterizationStateCreateInfo> create(
  const void*                                pNext,
  VkPipelineRasterizationStateCreateFlags    flags,
  VkBool32                                   depthClampEnable,
  VkBool32                                   rasterizerDiscardEnable,
  VkPolygonMode                              polygonMode,
  VkCullModeFlags                            cullMode,
  VkFrontFace                                frontFace,
  VkBool32                                   depthBiasEnable,
  float                                      depthBiasConstantFactor,
  float                                      depthBiasClamp,
  float                                      depthBiasSlopeFactor,
  float                                      lineWidth
) {
  return PipelineRasterizationStateCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .depthClampEnable = depthClampEnable,
    .rasterizerDiscardEnable = rasterizerDiscardEnable,
    .polygonMode = polygonMode,
    .cullMode = cullMode,
    .frontFace = frontFace,
    .depthBiasEnable = depthBiasEnable,
    .depthBiasConstantFactor = depthBiasConstantFactor,
    .depthBiasClamp = depthBiasClamp,
    .depthBiasSlopeFactor = depthBiasSlopeFactor,
    .lineWidth = lineWidth
  };
}

template<typename T>
enable_if_same_t<T, PipelineRasterizationStateCreateInfo> create(
  VkPipelineRasterizationStateCreateFlags    flags,
  VkBool32                                   depthClampEnable,
  VkBool32                                   rasterizerDiscardEnable,
  VkPolygonMode                              polygonMode,
  VkCullModeFlags                            cullMode,
  VkFrontFace                                frontFace,
  VkBool32                                   depthBiasEnable,
  float                                      depthBiasConstantFactor,
  float                                      depthBiasClamp,
  float                                      depthBiasSlopeFactor,
  float                                      lineWidth
) {
  return _impl::create<PipelineRasterizationStateCreateInfo>(
    nullptr,
    flags,
    depthClampEnable,
    rasterizerDiscardEnable,
    polygonMode,
    cullMode,
    frontFace,
    depthBiasEnable,
    depthBiasConstantFactor,
    depthBiasClamp,
    depthBiasSlopeFactor,
    lineWidth
  );
}

template<typename T>
enable_if_same_t<T, PipelineRasterizationStateCreateInfo> create(
  VkBool32                                   depthClampEnable,
  VkBool32                                   rasterizerDiscardEnable,
  VkPolygonMode                              polygonMode,
  VkCullModeFlags                            cullMode,
  VkFrontFace                                frontFace,
  VkBool32                                   depthBiasEnable,
  float                                      depthBiasConstantFactor,
  float                                      depthBiasClamp,
  float                                      depthBiasSlopeFactor,
  float                                      lineWidth
) {
  return _impl::create<PipelineRasterizationStateCreateInfo>(
    nullptr,
    0,
    depthClampEnable,
    rasterizerDiscardEnable,
    polygonMode,
    cullMode,
    frontFace,
    depthBiasEnable,
    depthBiasConstantFactor,
    depthBiasClamp,
    depthBiasSlopeFactor,
    lineWidth
  );
}
}
}
