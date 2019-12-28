list(APPEND
  MOODYCAMEL_CONCURRENTQUEUE_CMAKE_ARGS
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}"
)

ExternalProject_Add(dependency_moodycamel_concurrentqueue
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/moodycamel/concurrentqueue
  CMAKE_ARGS ${MOODYCAMEL_CONCURRENTQUEUE_CMAKE_ARGS}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND
    COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX}/include/moodycamel
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/moodycamel/concurrentqueue/blockingconcurrentqueue.h ${CMAKE_INSTALL_PREFIX}/include/moodycamel
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/moodycamel/concurrentqueue/concurrentqueue.h ${CMAKE_INSTALL_PREFIX}/include/moodycamel
)
