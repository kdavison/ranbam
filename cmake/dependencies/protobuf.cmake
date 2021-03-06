list(APPEND
  PROTOBUF_CMAKE_ARGS
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
  "-Dprotobuf_BUILD_TESTS=OFF"
  "-Dprotobuf_BUILD_EXAMPLES=OFF"
  "-Dprotobuf_VERBOSE=OFF"
  "-Dprotobuf_MODULE_COMPATIBLE=OFF"
)

ExternalProject_Add(dependency_protobuf
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/cmake
  CMAKE_ARGS ${PROTOBUF_CMAKE_ARGS}
  BUILD_COMMAND $(MAKE)
  INSTALL_COMMAND $(MAKE) install
)
