#pragma once

namespace vk {
typedef VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, PipelineViewportStateCreateInfo> create(
  const void*                           pNext,
  VkPipelineViewportStateCreateFlags    flags,
  std::vector<Viewport> const&          viewports,
  std::vector<Rect2D>   const&          scissors
) {
  return PipelineViewportStateCreateInfo {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .viewportCount = static_cast<uint32_t>(viewports.size()),
    .pViewports = viewports.data(),
    .scissorCount = static_cast<uint32_t>(scissors.size()),
    .pScissors = scissors.data()
  };
}

template<typename T>
enable_if_same_t<T, PipelineViewportStateCreateInfo> create(
  VkPipelineViewportStateCreateFlags    flags,
  std::vector<Viewport> const&          viewports,
  std::vector<Rect2D>   const&          scissors
) {
  return _impl::create<PipelineViewportStateCreateInfo>(
    nullptr,
    flags,
    viewports,
    scissors
  );
}

template<typename T>
enable_if_same_t<T, PipelineViewportStateCreateInfo> create(
  std::vector<Viewport> const&          viewports,
  std::vector<Rect2D>   const&          scissors
) {
  return _impl::create<PipelineViewportStateCreateInfo>(
    nullptr,
    0,
    viewports,
    scissors
  );
}
}
}
