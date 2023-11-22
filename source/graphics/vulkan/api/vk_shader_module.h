#pragma once

namespace vk {
typedef VkShaderModuleCreateInfo ShaderModuleCreateInfo;

namespace _impl {
template<typename T>
enable_if_same_t<T, ShaderModuleCreateInfo> create(
    const void*                  pNext,
    VkShaderModuleCreateFlags    flags,
    std::vector<uint8_t> const& code
) {
  assert((code.size() > 0) && (code.size() % 4 == 0));
  return ShaderModuleCreateInfo {
    .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext = pNext,
    .flags = flags,
    .codeSize = code.size(),
    .pCode = reinterpret_cast<const uint32_t*>(code.data())
  };
}

template<typename T>
enable_if_same_t<T, ShaderModuleCreateInfo> create(
    VkShaderModuleCreateFlags    flags,
    std::vector<uint8_t> const& code
) {
  return _impl::create<ShaderModuleCreateInfo>(
    nullptr,
    flags,
    code
  );
}

template<typename T>
enable_if_same_t<T, ShaderModuleCreateInfo> create(
    std::vector<uint8_t> const& code
) {
  return _impl::create<ShaderModuleCreateInfo>(
    nullptr,
    0,
    code
  );
}
}

typedef std::shared_ptr<std::remove_pointer_t<VkShaderModule>> ShaderModule;

namespace _impl {
template<typename T>
enable_if_same_t<T, ShaderModule> create(
    Device                        device,
    const ShaderModuleCreateInfo* pCreateInfo,
    const AllocationCallbacks*    pAllocator
) {
  assert(pCreateInfo);
  VkShaderModule shaderModule;
  ::vk::Result result = vkCreateShaderModule(
    device.get(),
    pCreateInfo,
    pAllocator,
    &shaderModule);
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return ShaderModule(nullptr);
  }
  return ShaderModule(
    std::move(shaderModule),
    [device, pAllocator](VkShaderModule p) {
      vkDestroyShaderModule(device.get(), p, pAllocator);
    }
  );
}

template<typename T>
enable_if_same_t<T, ShaderModule> create(
    Device                        device,
    const ShaderModuleCreateInfo* pCreateInfo
) {
  assert(pCreateInfo);
  VkShaderModule shaderModule;
  ::vk::Result result = vkCreateShaderModule(
    device.get(),
    pCreateInfo,
    nullptr,
    &shaderModule);
  if(vk::is_error(result)) {
    vk::handle_code(result);
    return ShaderModule(nullptr);
  }
  return ShaderModule(
    std::move(shaderModule),
    [device](VkShaderModule p) {
      vkDestroyShaderModule(device.get(), p, nullptr);
    }
  );
}
}
}
