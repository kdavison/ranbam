#pragma once

#include <vulkan/vulkan.h>
#include "vk_result.h"
#include "vk_instance_create_information.h"
#include "vk_allocation_callbacks.h"
#include <memory>
#include <cassert>

namespace vk {
typedef std::shared_ptr<std::remove_pointer_t<VkInstance>> Instance;

namespace _impl {
template<typename T>
enable_if_same_t<T,Instance> create(
    const vk::InstanceCreateInfo*  pCreateInfo,
    const vk::AllocationCallbacks* pAllocator
) {
  assert(pCreateInfo);
  VkInstance instance;
  const auto result = vkCreateInstance(pCreateInfo, pAllocator, &instance);
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return Instance(nullptr);
  }
  return Instance(std::move(instance), [pAllocator](VkInstance p) {
    vkDestroyInstance(p, pAllocator);
  });
}

template<typename T>
enable_if_same_t<T,Instance> create(
  const vk::InstanceCreateInfo* pCreateInfo
) {
  return _impl::create<Instance>(
    pCreateInfo,
    nullptr
  );
}
}
}
