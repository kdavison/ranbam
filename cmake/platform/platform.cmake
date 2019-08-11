message("--- PLATFORM INFORMATION ---")
message("CMAKE_SYSTEM_INFO_FILE: ${CMAKE_SYSTEM_INFO_FILE}")
message("CMAKE_SYSTEM_NAME:      ${CMAKE_SYSTEM_NAME}")
message("CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_SYSTEM:           ${CMAKE_SYSTEM}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  include(cmake/platform/unix.cmake)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  include(cmake/platform/apple.cmake)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  include(cmake/platform/windows.cmake)
endif()
