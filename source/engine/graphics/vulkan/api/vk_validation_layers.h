#pragma once

#include <vulkan/vulkan.h>
#include <algorithm>
#include <vector>
#include <cstring>

namespace vk {
typedef VkLayerProperties LayerProperties;
std::vector<vk::LayerProperties> GetAvailableLayerProperties() {
  uint32_t count(0);
  vkEnumerateInstanceLayerProperties(&count, nullptr);
  std::vector<vk::LayerProperties> layer_properties(count);
  vkEnumerateInstanceLayerProperties(&count, layer_properties.data());
  return layer_properties;
}

bool IsLayerSupported(const char* RequestedLayer, std::vector<vk::LayerProperties> const& AvailableLayers) {
  auto iterator = std::find_if(std::begin(AvailableLayers), std::end(AvailableLayers), [RequestedLayer](const auto& property) {
    return (std::strcmp(RequestedLayer, property.layerName) == 0);
  });
  return (iterator != std::end(AvailableLayers));
}

bool CheckValidationLayerSupport(std::vector<const char*> const& ValidationLayers) {
  bool result = true;
  const auto AvailableLayerProperties = GetAvailableLayerProperties();
  for(const auto& validation_layer : ValidationLayers) {
    result &= IsLayerSupported(validation_layer, AvailableLayerProperties);
  }
  return result;
}
}
