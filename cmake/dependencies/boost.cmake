set(BOOST_SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR}/dependencies/boost)


if(UNIX)
  set(BOOST_BOOTSTRAP_EXECUTABLE ${BOOST_SOURCE_DIRECTORY}/bootstrap.sh)
elseif(WIN32)
  set(BOOST_BOOTSTRAP_EXECUTABLE ${BOOST_SOURCE_DIRECTORY}/bootstrap.bat)
endif()

set(BOOST_B2_EXECUTABLE ${BOOST_SOURCE_DIRECTORY}/b2)

ExternalProject_Add(dependency_boost
  SOURCE_DIR ${BOOST_SOURCE_DIRECTORY}
  CONFIGURE_COMMAND ${BOOST_BOOTSTRAP_EXECUTABLE}
  BUILD_COMMAND ""
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND
    ${BOOST_B2_EXECUTABLE}
    install
    -a
    threading=multi
    runtime-link=shared
    variant=release
    --prefix=${CMAKE_INSTALL_PREFIX}
    --includedir=${CMAKE_INSTALL_PREFIX}/include
    --libdir=${CMAKE_INSTALL_PREFIX}/lib
    --build-dir=${CMAKE_CURRENT_BINARY_DIR}
    --with-system
    --with-filesystem
)
