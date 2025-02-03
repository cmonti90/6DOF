set(target runner)

set(SOURCES runner.cpp)

add_executable(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC SixDOFWorld
                                       SimLib
                                )


set(SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/runit.py)
set(OUTPUT_FILE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/runit)


add_custom_command(
       OUTPUT ${OUTPUT_FILE}
       COMMAND echo "#!/bin/env python" > ${OUTPUT_FILE}
       COMMAND ${CMAKE_COMMAND} -E cat ${SOURCE_FILE} >> ${OUTPUT_FILE}
       COMMAND chmod +x ${OUTPUT_FILE}
       DEPENDS ${SOURCE_FILE}
       COMMENT "Copying runit.py and prepending shebang"
       VERBATIM
)

add_custom_target(copy_runit ALL DEPENDS ${SOURCE_FILE} ${OUTPUT_FILE})
                               