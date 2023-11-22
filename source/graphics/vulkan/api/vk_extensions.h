#pragma once

#include <vulkan/vulkan.h>
#include "vk_physical_device.h"
#include <vector>

namespace vk {
typedef VkExtensionProperties ExtensionProperties;

namespace _impl {
//instance extension support
std::vector<vk::ExtensionProperties> GetAvailableInstanceExtensionProperties(const char* layer) {
  uint32_t count(0);
  vkEnumerateInstanceExtensionProperties(layer, &count, nullptr);
  std::vector<vk::ExtensionProperties> SupportedExtensions(count);
  vkEnumerateInstanceExtensionProperties(layer, &count, SupportedExtensions.data());
  return std::move(SupportedExtensions);
}

std::vector<vk::ExtensionProperties> GetAvailableInstanceExtensionProperties() {
  return GetAvailableInstanceExtensionProperties(nullptr);
}

//device extension support
std::vector<vk::ExtensionProperties> GetAvailableDeviceExtensionProperties(PhysicalDevice physicalDevice) {
  uint32_t count(0);
  vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, nullptr);
  std::vector<vk::ExtensionProperties> SupportedExtensions(count);
  vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, SupportedExtensions.data());
  return std::move(SupportedExtensions);
}

//general support checking
bool IsExtensionSupported(const char* RequestedExtension, std::vector<vk::ExtensionProperties> const& AvailableExtensions) {
  auto iterator = std::find_if(std::begin(AvailableExtensions), std::end(AvailableExtensions), [RequestedExtension](const auto& property) {
    return (std::strcmp(RequestedExtension, property.extensionName) == 0);
  });
  return (iterator != std::end(AvailableExtensions));
}
}

bool CheckInstanceExtensionSupport(std::vector<const char*> const& InstanceExtensions) {
  bool result(true);
  const auto AvailableExtensionProperties = _impl::GetAvailableInstanceExtensionProperties();
  for(const auto& extension : InstanceExtensions) {
    result &= _impl::IsExtensionSupported(extension, AvailableExtensionProperties);
  }
  return result;
}

bool CheckDeviceExtensionSupport(PhysicalDevice physicalDevice, std::vector<const char*> const& DeviceExtensions) {
  bool result(true);
  const auto AvailableExtensionProperties = _impl::GetAvailableDeviceExtensionProperties(physicalDevice);
  for(const auto& extension : DeviceExtensions) {
    result &= _impl::IsExtensionSupported(extension, AvailableExtensionProperties);
  }
  return result;
}


}
