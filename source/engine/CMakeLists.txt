project(ranbam.engine)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

list(APPEND
  SOURCE_FILES
  main.cpp
  #graphics/vulkan/api/vk_debug_callback.cpp
)

#add_definitions("-Wall -Werror")
add_definitions("-Wno-error=int-in-bool-context")

include_directories(
  ${OPENGL_INCLUDE_DIR}
  ${CMAKE_INSTALL_PREFIX}/include/bullet
  ${CMAKE_INSTALL_PREFIX}/include/vulkan
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/graphics/vulkan/api
)

add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
)
add_dependencies(${PROJECT_NAME}
  ranbam.shaders
)
target_link_libraries(${PROJECT_NAME}
  boost_system
  boost_filesystem
  vulkan
  Threads::Threads
  glfw3
  dl
  X11
#  ${OPENGL_gl_LIBRARY}
)

SET(CMAKE_INSTALL_RPATH "/home/kyle/workspace/ranbam-dev/artifacts/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
install(
  TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}
)
