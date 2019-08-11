#include "graphics/vulkan/api/vulkan.hpp"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#include <memory>
#include <algorithm>
#include <fstream>
#include <set>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstring>
#include <cassert>

//glfw

namespace glfw {
typedef std::shared_ptr<std::remove_pointer_t<GLFWwindow>> Window;

struct library {
  library() {
    assert(glfwInit() != false);
    assert(glfwVulkanSupported());
  }
  ~library() {
    glfwTerminate();
  }

  template<typename... ARGS>
  ::glfw::Window CreateWindow(ARGS&&... args) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    return ::glfw::Window(
      (GLFWwindow*)glfwCreateWindow(std::forward<ARGS>(args)...),
      glfwDestroyWindow
    );
  }

  ::vk::Surface CreateSurface(
    ::vk::Instance instance,
    ::glfw::Window window,
    ::vk::AllocationCallbacks* pAllocator
  ) {
    
    VkSurfaceKHR surface;
    const auto result = glfwCreateWindowSurface(
      instance.get(),
      window.get(),
      pAllocator,
      &surface
    );
    if(vk::is_error(result)) {
      vk::handle_code(result);
      return nullptr;
    }
    return vk::Surface(surface, [instance, pAllocator](VkSurfaceKHR p) {
      vkDestroySurfaceKHR(instance.get(), p, pAllocator);
    });
  }

  ::vk::Surface CreateSurface(
    ::vk::Instance instance,
    ::glfw::Window window
  ) {
    return CreateSurface(instance, window, nullptr);
  }

  std::vector<const char*> RequiredExtensions() {
    uint32_t count(0);
    const auto extensions = glfwGetRequiredInstanceExtensions(&count);
    return std::vector<const char*>(extensions, extensions + count);
  }
};

template<typename... ARGS>
auto CreateWindow(ARGS&&... args) {
  auto deleter = [](GLFWwindow* w) {
    glfwDestroyWindow(w);
  };
  return std::unique_ptr<GLFWwindow, decltype(deleter)>(glfwCreateWindow(std::forward<ARGS>(args)...), deleter);
}
}

std::vector<uint8_t> read_binary_file(const std::string filepath) {
  std::ifstream file(filepath, std::fstream::in | std::fstream::binary);
  assert(file.is_open());
  if(file.is_open()) {
    file.seekg(0, std::ios::end);
    const std::size_t filesize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> content(filesize, 0);
    file.read(reinterpret_cast<char*>(content.data()), filesize);
    file.close();
    return content;
  }
  return std::vector<uint8_t>{};
}

//vulkan
namespace vk {
template<typename T, typename... ARGS>
auto create(ARGS&&... args) {
  return _impl::create<T>(std::forward<ARGS>(args)...);
}

std::vector<const char*> Layers {
  "VK_LAYER_LUNARG_standard_validation"
};

std::vector<const char*> InstanceExtensions {
  "VK_EXT_debug_report"
};

std::vector<const char*> DeviceExtensions {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

ShaderModule LoadShaderFromFile(const std::string filepath, vk::Device device) {
  const auto code = read_binary_file(filepath);
  auto shaderCreateInfo = create<vk::ShaderModuleCreateInfo>(code);
  return create<vk::ShaderModule>(
    device,
    &shaderCreateInfo
  );
  return ShaderModule(nullptr);
}
}

struct whaterver1 {
  const uint32_t index;
  const uint32_t count;
};

whaterver1 FindQueueFamilyIndex(std::vector<vk::QueueFamilyProperties> const& families, uint32_t flags) {
  auto iterator = std::find_if(std::begin(families), std::end(families), [flags](const auto& family) {
    return ((family.queueFlags & flags) == flags);
  });
  assert(iterator != std::end(families));
  return whaterver1 {
    (uint32_t)std::distance(std::begin(families), iterator),
    iterator->queueCount
  };
}

int main(int argc, char *argv[])
{
  glfw::library libglfw;

  assert(vk::CheckValidationLayerSupport(vk::Layers));
  {
    const auto glfw_extensions = libglfw.RequiredExtensions();
    vk::InstanceExtensions.insert(std::end(vk::InstanceExtensions), std::begin(glfw_extensions), std::end(glfw_extensions));
  }
  assert(vk::CheckInstanceExtensionSupport(vk::InstanceExtensions));

  auto application_information = vk::create<vk::ApplicationInfo>("test", 1, "ranbam", 1, VK_API_VERSION_1_1);
  auto instance_information = vk::create<vk::InstanceCreateInfo>(
    &application_information,
    vk::Layers,
    vk::InstanceExtensions
  );
  auto spInstance = vk::create<vk::Instance>(&instance_information);


  auto physicalDevices = vk::GetPhysicalDevices(spInstance);
  assert(physicalDevices.size() > 0);
  assert(vk::CheckDeviceExtensionSupport(physicalDevices.at(0), vk::DeviceExtensions));

  auto queueFamilyProperties = vk::GetQueueFamilyProperties(physicalDevices.at(0));
  assert(queueFamilyProperties.size() > 0);

  auto queue_info = FindQueueFamilyIndex(queueFamilyProperties, (uint32_t)vk::QueueFlags::Graphics);
  std::vector<float> queuePriorities(queue_info.count, 0.0);
  
  std::vector<vk::DeviceQueueCreateInfo> deviceQueueCreateInfos {
    vk::create<vk::DeviceQueueCreateInfo>(
      queue_info.index,
      queuePriorities
    )
  };

  auto deviceCreateInfo = vk::create<vk::DeviceCreateInfo>(
    deviceQueueCreateInfos,
    vk::Layers,
    vk::DeviceExtensions,
    nullptr
  );

  auto spDevice = vk::create<vk::Device>(physicalDevices.at(0), &deviceCreateInfo);
  assert(spDevice);

  auto commandPoolCreateInfo = vk::create<vk::CommandPoolCreateInfo>(
    vk::CommandPoolCreateFlags::EMPTY,
    queue_info.index
  );

  auto spCommandPool = vk::create<vk::CommandPool>(
    spDevice,
    &commandPoolCreateInfo
  );
  assert(spCommandPool);
  auto commandBufferAllocateInfo = vk::create<vk::CommandBufferAllocateInfo>(
    spCommandPool,
    vk::CommandBufferLevel::Primary,
    1
  );
  auto commandBuffers = vk::AllocateCommandBuffers(
    spDevice,
    &commandBufferAllocateInfo,
    1
  );
  assert(commandBuffers.size() > 0);

  auto spWindow = libglfw.CreateWindow(640, 480, "My Title", nullptr, nullptr);
  assert(spWindow);

  auto spSurface = libglfw.CreateSurface(spInstance, spWindow);
  assert(spSurface);

  auto surfaceCapabilities = vk::GetPhysicalDeviceSurfaceCapabilities(
    physicalDevices.at(0),
    spSurface
  );

  std::vector<VkBool32> PresentSupport(queueFamilyProperties.size(), VK_FALSE);
  for(std::size_t index(0); index < queueFamilyProperties.size(); ++index) {
    vk::Result result = vkGetPhysicalDeviceSurfaceSupportKHR(
      physicalDevices.at(0),
      index,
      spSurface.get(),
      &PresentSupport[index]
    );
    if(vk::is_error(result)) {
      vk::handle_code(result);
      assert(false);
    }
  }
  //in my case index 0 is always presentable, so lets use that!

  auto surfaceFormats = vk::GetPhysicalDeviceSurfaceFormats(
    physicalDevices.at(0),
    spSurface
  );
  assert(surfaceFormats.size() > 0);
  vk::SurfaceFormat surfaceFormat;
  if(surfaceFormats.size() == 1 && surfaceFormats.at(0).format == VK_FORMAT_UNDEFINED) {
    surfaceFormat = vk::SurfaceFormat {
      VK_FORMAT_B8G8R8A8_UNORM,
      surfaceFormats.at(0).colorSpace
    };
  } else {
    auto found = std::find_if(std::begin(surfaceFormats), std::end(surfaceFormats), [](const auto& surfaceFormat) {
      return (surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM);
    });
    if(found != std::end(surfaceFormats)) {
      surfaceFormat = (*found);
    } else {
      surfaceFormat = surfaceFormats.at(0);
    }
  }

  VkSurfaceTransformFlagBitsKHR preTransform;
  if (surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
      preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  } else {
      preTransform = surfaceCapabilities.currentTransform;
  }

  VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[4] = {
      VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
      VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
      VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
  };
  for (uint32_t i = 0; i < sizeof(compositeAlphaFlags); i++) {
      if (surfaceCapabilities.supportedCompositeAlpha & compositeAlphaFlags[i]) {
          compositeAlpha = compositeAlphaFlags[i];
          break;
      }
  }

  vk::PresentMode presentMode = [](vk::PhysicalDevice physicalDevice, vk::Surface surface) {
    const auto present_mode_list = vk::GetPhysicalDeviceSurfacePresentModes(
      physicalDevice,
      surface
    );
    const std::set<vk::PresentMode> available_modes(std::begin(present_mode_list), std::end(present_mode_list));
    if(available_modes.count(VK_PRESENT_MODE_MAILBOX_KHR)) {
      return VK_PRESENT_MODE_MAILBOX_KHR;
    } else if(available_modes.count(VK_PRESENT_MODE_FIFO_KHR)) {
      return VK_PRESENT_MODE_FIFO_KHR;
    } else {
      return VK_PRESENT_MODE_IMMEDIATE_KHR;
    }
  }(physicalDevices.at(0), spSurface);

  VkExtent2D extent = [](const vk::SurfaceCapabilities& capabilities) {
    VkExtent2D e;
    if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
      e = capabilities.currentExtent;
    } else {
      e = {640, 480};
      e.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, e.width));
      e.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, e.height));
    }
    return e;
  }(surfaceCapabilities);

  const uint32_t queueIndices[1] = {0};
  auto swapchainCreateInfo = vk::create<vk::SwapchainCreateInfo>(
    spSurface,
    surfaceCapabilities.minImageCount,
    surfaceFormat.format,
    surfaceFormat.colorSpace,
    extent,
    1,
    VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
    VK_SHARING_MODE_EXCLUSIVE,
    1,
    queueIndices,
    preTransform,
    compositeAlpha,
    presentMode,
    VK_TRUE,
    nullptr
  );

  auto spSwapchain = vk::create<vk::Swapchain>(
    spDevice,
    &swapchainCreateInfo
  );

  auto swapchainImages = vk::GetSwapchainImages(
    spDevice,
    spSwapchain
  );

  std::vector<vk::ImageView> imageViews;
  imageViews.reserve(swapchainImages.size());
  for(const auto& swapchain_image : swapchainImages) {
    auto create_info = vk::create<vk::ImageViewCreateInfo>(
      swapchain_image,
      VK_IMAGE_VIEW_TYPE_2D,
      surfaceFormat.format,
      VkComponentMapping {
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY,
      },
      VkImageSubresourceRange {
        VK_IMAGE_ASPECT_COLOR_BIT,
        0,
        1,
        0,
        1
      }
    );
    auto imageView = vk::create<vk::ImageView>(
      spDevice,
      &create_info
    );
    assert(imageView);
    imageViews.push_back(std::move(imageView));
  }

  auto spVertexShaderModule = vk::LoadShaderFromFile("source/shaders/test0.vert.spv", spDevice);
  assert(spVertexShaderModule);
  auto spFragmentShaderModule = vk::LoadShaderFromFile("source/shaders/test0.frag.spv", spDevice);
  assert(spFragmentShaderModule);

  std::vector<vk::PipelineShaderStageCreateInfo> shaderStages = {
    vk::create<vk::PipelineShaderStageCreateInfo>(
      VK_SHADER_STAGE_VERTEX_BIT,
      spVertexShaderModule,
      "main"
    ),
    vk::create<vk::PipelineShaderStageCreateInfo>(
      VK_SHADER_STAGE_FRAGMENT_BIT,
      spFragmentShaderModule,
      "main"
    )
  };

  auto vertexInputInfo = vk::create<vk::PipelineVertexInputStateCreateInfo>(
    std::vector<vk::VertexInputBindingDescription>{},
    std::vector<vk::VertexInputAttributeDescription>{}
  );

  auto inputAssembly = vk::create<vk::PipelineInputAssemblyStateCreateInfo>(
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
    false
  );

  auto viewport = vk::create<vk::Viewport>(
    0.0f,
    0.0f,
    static_cast<float>(extent.width),
    static_cast<float>(extent.height),
    0.0f,
    1.0f
  );

  auto scissor = vk::create<vk::Rect2D>(
    VkOffset2D{0,0},
    extent
  );

  auto viewportStateCreateInfo = vk::create<vk::PipelineViewportStateCreateInfo>(
    std::vector<vk::Viewport>{
      viewport
    },
    std::vector<vk::Rect2D>{
      scissor
    }
  );

  auto rasterizerStateCreateInfo = vk::create<vk::PipelineRasterizationStateCreateInfo>(
    VK_FALSE,
    VK_FALSE,
    VK_POLYGON_MODE_FILL,
    VK_CULL_MODE_BACK_BIT,
    VK_FRONT_FACE_CLOCKWISE,
    VK_FALSE,
    0.0f,
    0.0f,
    0.0f,
    1.0f
  );

  std::vector<vk::PipelineColorBlendAttachmentState> colorblendAttachments {
    vk::create<vk::PipelineColorBlendAttachmentState>(
      VK_FALSE,
      VK_BLEND_FACTOR_ONE,
      VK_BLEND_FACTOR_ZERO,
      VK_BLEND_OP_ADD,
      VK_BLEND_FACTOR_ONE,
      VK_BLEND_FACTOR_ZERO,
      VK_BLEND_OP_ADD,
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
    )
  };

  auto colorBlendStateCreateInfo = vk::create<vk::PipelineColorBlendStateCreateInfo>(
    VK_FALSE,
    VK_LOGIC_OP_COPY,
    std::move(colorblendAttachments),
    std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f}
  );

  auto dynamicStateCreateInfo = vk::create<vk::PipelineDynamicStateCreateInfo>(
    std::vector<VkDynamicState> {
      VK_DYNAMIC_STATE_VIEWPORT,
      VK_DYNAMIC_STATE_LINE_WIDTH
    }
  );

  auto pipelineLayoutCreateInfo = vk::create<vk::PipelineLayoutCreateInfo>(
    std::vector<VkDescriptorSetLayout>{},
    std::vector<VkPushConstantRange>{}
  );

  auto spPipelineLayout = vk::create<vk::PipelineLayout>(
    spDevice,
    &pipelineLayoutCreateInfo
  );


  while(!glfwWindowShouldClose(spWindow.get())) {
    glfwSwapBuffers(spWindow.get());
    glfwPollEvents();
  }

  return 0;
}
