list(APPEND
  VULKAN_CMAKE_ARGS
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

add_custom_target(copy_vulkan_sdk
  COMMAND
    cp -r ${CMAKE_CURRENT_SOURCE_DIR}/VulkanSDK/1.1.70.1/x86_64/. ${CMAKE_INSTALL_PREFIX}
  DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanSDK/1.1.70.1/x86_64/include/vulkan/vk_sdk_platform.h
)

ExternalProject_Add(dependency_vulkan
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw
  CMAKE_ARGS ${VULKAN_CMAKE_ARGS}
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  DEPENDS
    copy_vulkan_sdk
)
