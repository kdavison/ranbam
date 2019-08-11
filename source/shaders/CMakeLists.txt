project(ranbam.shaders)

##lets just assume vulkan for now
set(EXECUTABLE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin")
if(WIN32)
set(GLSL_VALIDATOR "${EXECUTABLE_DIRECTORY}/glslangValidator.exe")
elseif(UNIX AND NOT APPLE)
set(GLSL_VALIDATOR "${EXECUTABLE_DIRECTORY}/glslangValidator")
else()
message(FATAL_ERROR "idk how to do this yet")
endif()

list(
  APPEND SOURCE
  test0.vert
  test0.frag
)

foreach(_shader ${SOURCE})
  get_filename_component(FILENAME ${_shader} NAME)
  set(SPIRV "${FILENAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${GLSL_VALIDATOR} -V ${CMAKE_CURRENT_SOURCE_DIR}/${_shader} -o ${SPIRV}
    DEPENDS ${_shader}
  )
  install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${SPIRV}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/shaders
  )
  list(
    APPEND SHADERS
    ${SPIRV}
  )
endforeach(_shader)

add_custom_target(
  ${PROJECT_NAME}
  SOURCES ${SHADERS}
)
