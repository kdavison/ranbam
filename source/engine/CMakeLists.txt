project(ranbam.engine)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

list(APPEND
  SOURCE_FILES
  main.cc
  #graphics/vulkan/api/vk_debug_callback.cpp
)

#add_definitions("-Wall -Werror")
add_definitions("-Wno-error=int-in-bool-context")

add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}
  Threads::Threads
)

SET(CMAKE_INSTALL_RPATH
  "${CMAKE_INSTALL_PREFIX}/artifacts/lib"
)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

install(
  TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}
)
