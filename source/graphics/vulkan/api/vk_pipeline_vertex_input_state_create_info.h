#pragma once

namespace vk {
typedef VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo;
typedef VkVertexInputBindingDescription VertexInputBindingDescription;
typedef VkVertexInputAttributeDescription VertexInputAttributeDescription;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineVertexInputStateCreateInfo> create(
  const void*                                 pNext,
  VkPipelineVertexInputStateCreateFlags       flags,
  std::vector<VertexInputBindingDescription>   const& BindingDescription,
  std::vector<VertexInputAttributeDescription> const& AttributeDescription
) {
  return PipelineVertexInputStateCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .vertexBindingDescriptionCount = static_cast<uint32_t>(BindingDescription.size()),
    .pVertexBindingDescriptions = BindingDescription.data(),
    .vertexAttributeDescriptionCount = static_cast<uint32_t>(AttributeDescription.size()),
    .pVertexAttributeDescriptions = AttributeDescription.data()
  };
}

template<typename T>
enable_if_same_t<T, PipelineVertexInputStateCreateInfo> create(
  VkPipelineVertexInputStateCreateFlags       flags,
  std::vector<VertexInputBindingDescription>   const& BindingDescription,
  std::vector<VertexInputAttributeDescription> const& AttributeDescription
) {
  return _impl::create<PipelineVertexInputStateCreateInfo>(
    nullptr,
    flags,
    BindingDescription,
    AttributeDescription
  );
}

template<typename T>
enable_if_same_t<T, PipelineVertexInputStateCreateInfo> create(
  std::vector<VertexInputBindingDescription>   const& BindingDescription,
  std::vector<VertexInputAttributeDescription> const& AttributeDescription
) {
  return _impl::create<PipelineVertexInputStateCreateInfo>(
    nullptr,
    0,
    BindingDescription,
    AttributeDescription
  );
}
}
}
