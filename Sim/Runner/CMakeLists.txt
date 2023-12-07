set(target runner)

set(SOURCES runner.cpp)

set(HEADERS runner.h)

add_executable(${target} ${SOURCES} ${HEADERS})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC SixDOFWorld
                                       SimLib
                                )