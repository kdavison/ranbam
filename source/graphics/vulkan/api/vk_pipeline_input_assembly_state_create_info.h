#pragma once

namespace vk {
typedef VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineInputAssemblyStateCreateInfo> create(
  const void*                                pNext,
  VkPipelineInputAssemblyStateCreateFlags    flags,
  VkPrimitiveTopology                        topology,
  bool                                       primitiveRestartEnable
) {
  return PipelineInputAssemblyStateCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .topology = topology,
    .primitiveRestartEnable = static_cast<VkBool32>(primitiveRestartEnable ? VK_TRUE : VK_FALSE)
  };
}

template<typename T>
enable_if_same_t<T, PipelineInputAssemblyStateCreateInfo> create(
  VkPipelineInputAssemblyStateCreateFlags    flags,
  VkPrimitiveTopology                        topology,
  bool                                       primitiveRestartEnable
) {
  return _impl::create<PipelineInputAssemblyStateCreateInfo> (
    nullptr,
    flags,
    topology,
    primitiveRestartEnable
  );
}

template<typename T>
enable_if_same_t<T, PipelineInputAssemblyStateCreateInfo> create(
  VkPrimitiveTopology                        topology,
  bool                                       primitiveRestartEnable
) {
  return _impl::create<PipelineInputAssemblyStateCreateInfo> (
    nullptr,
    0,
    topology,
    primitiveRestartEnable
  );
}
}
}
