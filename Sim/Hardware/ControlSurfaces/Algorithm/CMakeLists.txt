set(target CntrlSurfAlgorithm)

set(SOURCES ControlSurfaces.cpp)

set(HEADERS ControlSurfaces.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  TimeMngr
                                        Messages
                                PRIVATE mathlib
                                        PubSub
                                        AircraftProperties
                                        )