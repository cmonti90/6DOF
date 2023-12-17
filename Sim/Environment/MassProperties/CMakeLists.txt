set(target MassProperties)

set(SOURCES MassProperties.cpp)

set(HEADERS MassProperties.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC mathlib
                                        SimLib
                                        Engine
                                        )