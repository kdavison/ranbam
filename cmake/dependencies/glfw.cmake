list(APPEND
  GLFW_CMAKE_ARGS
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
  "-DGLFW_BUILD_EXAMPLES=OFF"
  "-DGLFW_BUILD_TESTS=OFF"
  "-DGLFW_BUILD_DOCS=OFF"
)

ExternalProject_Add(dependency_glfw
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw
  CMAKE_ARGS ${GLFW_CMAKE_ARGS}
  BUILD_COMMAND $(MAKE)
  INSTALL_COMMAND $(MAKE) install
)


