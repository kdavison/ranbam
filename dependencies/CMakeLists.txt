##
## This file includes all the
##   dependencies used by the project
##
## Some are simple, some are complex
## 

project(ranbam.dependencies)

include(ExternalProject)

list(APPEND DEPENDENCY_PROJECTS
#  boost
#  spdlog
#  googletest
#  protobuf
  assimp
  bullet3
#  breakpad
#  rng
#  glm
  eigen
#  glfw
  enet
  moodycamel_concurrentqueue
#  vulkan
#  cegui
)

foreach(_dependency ${DEPENDENCY_PROJECTS})
  include(${CMAKE_SOURCE_DIR}/cmake/dependencies/${_dependency}.cmake)
  list(APPEND DEPENDENCIES
    dependency_${_dependency}
  )
endforeach()

add_custom_target(ranbam.dependencies
  DEPENDS
    ${DEPENDENCIES}
)
