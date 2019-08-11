cmake_minimum_required(VERSION 3.8)
## platform detection
include(cmake/platform/platform.cmake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/artifacts")

add_subdirectory(dependencies)

include_directories(
  ${CMAKE_INSTALL_PREFIX}/include
)
link_directories(
  ${CMAKE_INSTALL_PREFIX}/lib
)
add_subdirectory(source)
