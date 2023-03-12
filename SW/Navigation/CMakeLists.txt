set(target Navigation)

set(SOURCES Navigation.cpp)

set(HEADERS Navigation.h)

add_library(${target} SHARED ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

add_dependencies(${target} mathlib)

target_link_libraries(${target} PUBLIC  TimeMngr
                                 mathlib
                                )
