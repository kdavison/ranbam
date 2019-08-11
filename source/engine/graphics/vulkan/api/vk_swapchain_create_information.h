#pragma once

#include <vulkan/vulkan.h>

namespace vk {
typedef VkSwapchainCreateInfoKHR SwapchainCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, SwapchainCreateInfo> create(
    const void*                      pNext,
    VkSwapchainCreateFlagsKHR        flags,
    vk::Surface                      surface,
    uint32_t                         minImageCount,
    VkFormat                         imageFormat,
    VkColorSpaceKHR                  imageColorSpace,
    VkExtent2D                       imageExtent,
    uint32_t                         imageArrayLayers,
    VkImageUsageFlags                imageUsage,
    VkSharingMode                    imageSharingMode,
    uint32_t                         queueFamilyIndexCount,
    const uint32_t*                  pQueueFamilyIndices,
    VkSurfaceTransformFlagBitsKHR    preTransform,
    VkCompositeAlphaFlagBitsKHR      compositeAlpha,
    VkPresentModeKHR                 presentMode,
    VkBool32                         clipped,
    VkSwapchainKHR                   oldSwapchain
) {
  return SwapchainCreateInfo {
    .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
    .pNext = pNext,
    .flags = flags,
    .surface = surface.get(),
    .minImageCount = minImageCount,
    .imageFormat = imageFormat,
    .imageColorSpace = imageColorSpace,
    .imageExtent = imageExtent,
    .imageArrayLayers = imageArrayLayers,
    .imageUsage = imageUsage,
    .imageSharingMode = imageSharingMode,
    .queueFamilyIndexCount = queueFamilyIndexCount,
    .pQueueFamilyIndices = pQueueFamilyIndices,
    .preTransform = preTransform,
    .compositeAlpha = compositeAlpha,
    .presentMode = presentMode,
    .clipped = clipped,
    .oldSwapchain = oldSwapchain
  };
}

template<typename T>
enable_if_same_t<T, SwapchainCreateInfo> create(
    VkSwapchainCreateFlagsKHR        flags,
    vk::Surface                      surface,
    uint32_t                         minImageCount,
    VkFormat                         imageFormat,
    VkColorSpaceKHR                  imageColorSpace,
    VkExtent2D                       imageExtent,
    uint32_t                         imageArrayLayers,
    VkImageUsageFlags                imageUsage,
    VkSharingMode                    imageSharingMode,
    uint32_t                         queueFamilyIndexCount,
    const uint32_t*                  pQueueFamilyIndices,
    VkSurfaceTransformFlagBitsKHR    preTransform,
    VkCompositeAlphaFlagBitsKHR      compositeAlpha,
    VkPresentModeKHR                 presentMode,
    VkBool32                         clipped,
    VkSwapchainKHR                   oldSwapchain
) {
  return _impl::create<SwapchainCreateInfo>(
    nullptr,
    flags,
    surface,
    minImageCount,
    imageFormat,
    imageColorSpace,
    imageExtent,
    imageArrayLayers,
    imageUsage,
    imageSharingMode,
    queueFamilyIndexCount,
    pQueueFamilyIndices,
    preTransform,
    compositeAlpha,
    presentMode,
    clipped,
    oldSwapchain
  );
}

template<typename T>
enable_if_same_t<T, SwapchainCreateInfo> create(
    vk::Surface                      surface,
    uint32_t                         minImageCount,
    VkFormat                         imageFormat,
    VkColorSpaceKHR                  imageColorSpace,
    VkExtent2D                       imageExtent,
    uint32_t                         imageArrayLayers,
    VkImageUsageFlags                imageUsage,
    VkSharingMode                    imageSharingMode,
    uint32_t                         queueFamilyIndexCount,
    const uint32_t*                  pQueueFamilyIndices,
    VkSurfaceTransformFlagBitsKHR    preTransform,
    VkCompositeAlphaFlagBitsKHR      compositeAlpha,
    VkPresentModeKHR                 presentMode,
    VkBool32                         clipped,
    VkSwapchainKHR                   oldSwapchain
) {
  return _impl::create<SwapchainCreateInfo>(
    nullptr,
    0,
    surface,
    minImageCount,
    imageFormat,
    imageColorSpace,
    imageExtent,
    imageArrayLayers,
    imageUsage,
    imageSharingMode,
    queueFamilyIndexCount,
    pQueueFamilyIndices,
    preTransform,
    compositeAlpha,
    presentMode,
    clipped,
    oldSwapchain
  );
}
}
}
