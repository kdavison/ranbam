#pragma once

#include <vulkan/vulkan.h>
#include <unordered_map>

namespace vk {
typedef VkResult Result;

static const std::unordered_map<int32_t, std::string> ERROR_CODE_DESCRIPTIONS = {
  {VK_SUCCESS, "(0) Command successfully completed"},
  {VK_NOT_READY, "(1) A fence or query has not yet completed"},
  {VK_TIMEOUT, "(2) A wait operation has not completed in the specified time"},
  {VK_EVENT_SET, "(3) An event is signaled"},
  {VK_EVENT_RESET, "(4) An event is unsignaled"},
  {VK_INCOMPLETE, "(5) A return array was too small for the result"},
  {VK_ERROR_OUT_OF_HOST_MEMORY, "(-1) A host memory allocation has failed."},
  {VK_ERROR_OUT_OF_DEVICE_MEMORY, "(-2) A device memory allocation has failed."},
  {VK_ERROR_INITIALIZATION_FAILED, "(-3) Initialization of an object could not be completed for implementation-specific reasons."},
  {VK_ERROR_DEVICE_LOST, "(-4) The logical or physical device has been lost. See Lost Device"},
  {VK_ERROR_MEMORY_MAP_FAILED, "(-5) Mapping of a memory object has failed."},
  {VK_ERROR_LAYER_NOT_PRESENT, "(-6) A requested layer is not present or could not be loaded."},
  {VK_ERROR_EXTENSION_NOT_PRESENT, "(-7) A requested extension is not supported."},
  {VK_ERROR_FEATURE_NOT_PRESENT, "(-8) A requested feature is not supported."},
  {VK_ERROR_INCOMPATIBLE_DRIVER, "(-9) The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons."},
  {VK_ERROR_TOO_MANY_OBJECTS, "(-10) Too many objects of the type have already been created."},
  {VK_ERROR_FORMAT_NOT_SUPPORTED, "(-11) A requested format is not supported on this device."},
  {VK_ERROR_FRAGMENTED_POOL, "(-12) A pool allocation has failed due to fragmentation of the pool’s memory. This must only be returned if no attempt to allocate host or device memory was made to accomodate the new allocation."},
  {VK_ERROR_OUT_OF_POOL_MEMORY, "(-1000069000) out of pool memory"},
  {VK_ERROR_INVALID_EXTERNAL_HANDLE, "(-1000072003) invalid external handle"},
  {VK_ERROR_SURFACE_LOST_KHR, "(-1000000000) surface lost"},
  {VK_ERROR_NATIVE_WINDOW_IN_USE_KHR, "(-1000000001) native window in use"},
  {VK_SUBOPTIMAL_KHR, "(1000001003) suboptimal"},
  {VK_ERROR_OUT_OF_DATE_KHR, "(-1000001004) out of date"},
  {VK_ERROR_INCOMPATIBLE_DISPLAY_KHR, "(-1000003001) incompatible display"},
  {VK_ERROR_VALIDATION_FAILED_EXT, "(-1000011001) validation failed"},
  {VK_ERROR_INVALID_SHADER_NV, "(-1000012000) invalid shader"}
//  {VK_ERROR_FRAGMENTATION_EXT, "(-1000161000) fragmentation error(?)"},
//  {VK_ERROR_NOT_PERMITTED_EXT, "(-1000174001) not permitted"},
};

static bool is_error(int32_t code) { return (code < 0); }

static void handle_code(int32_t code) {
  if(is_error(code)) {
    throw std::runtime_error("vk::ERROR " + ERROR_CODE_DESCRIPTIONS.at(code));
  }
}
}
