set(target Engine)

set(SOURCES Engine.cpp)

set(HEADERS Engine.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  mathlib
                                PRIVATE SimLib
                                        AircraftProperties
                                        )