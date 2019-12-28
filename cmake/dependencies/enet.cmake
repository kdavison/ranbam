list(APPEND
  ENET_CMAKE_ARGS
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(dependency_enet
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/enet
  CMAKE_ARGS ${ENET_CMAKE_ARGS}
  BUILD_COMMAND $(MAKE)
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND
    COMMAND cp -R ${CMAKE_CURRENT_SOURCE_DIR}/enet/include/enet ${CMAKE_INSTALL_PREFIX}/include
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/enet/libenet.a ${CMAKE_INSTALL_PREFIX}/lib
)

