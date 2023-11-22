#pragma once

namespace vk {
typedef VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineShaderStageCreateInfo> create(
    const void*                       pNext,
    VkPipelineShaderStageCreateFlags  flags,
    VkShaderStageFlagBits             stage,
    vk::ShaderModule                  module,
    std::string const&                Name,
    const VkSpecializationInfo*       pSpecializationInfo
) {
  assert(stage != VK_SHADER_STAGE_ALL_GRAPHICS && stage != VK_SHADER_STAGE_ALL);
  return PipelineShaderStageCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .stage = stage,
    .module = module.get(),
    .pName = Name.c_str(),
    .pSpecializationInfo = pSpecializationInfo
  };
}

template<typename T>
enable_if_same_t<T, PipelineShaderStageCreateInfo> create(
    VkPipelineShaderStageCreateFlags  flags,
    VkShaderStageFlagBits             stage,
    vk::ShaderModule                  module,
    std::string const&                Name,
    const VkSpecializationInfo*       pSpecializationInfo
) {
  return _impl::create<PipelineShaderStageCreateInfo>(
    nullptr,
    flags,
    stage,
    module,
    Name,
    pSpecializationInfo
  );
}

template<typename T>
enable_if_same_t<T, PipelineShaderStageCreateInfo> create(
    VkShaderStageFlagBits             stage,
    vk::ShaderModule                  module,
    std::string const&                Name,
    const VkSpecializationInfo*       pSpecializationInfo
) {
  return _impl::create<PipelineShaderStageCreateInfo>(
    nullptr,
    0,
    stage,
    module,
    Name,
    pSpecializationInfo
  );
}

template<typename T>
enable_if_same_t<T, PipelineShaderStageCreateInfo> create(
    VkShaderStageFlagBits             stage,
    vk::ShaderModule                  module,
    std::string const&                Name
) {
  return _impl::create<PipelineShaderStageCreateInfo>(
    nullptr,
    0,
    stage,
    module,
    Name,
    nullptr
  );
}
}
}
