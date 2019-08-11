project(ranbam.launcher)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

list(APPEND
  SOURCE_FILES
  main.cpp
  log.cpp
)

add_definitions("-Wall -Werror")

add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
)
target_link_libraries(${PROJECT_NAME}
  boost_system
  boost_filesystem
  Threads::Threads
)

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
install(
  TARGETS ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}
)
