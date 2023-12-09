set(target ControlSurfaces)

set(SOURCES ControlSurfaces.cpp
            Actuator.cpp)

set(HEADERS ControlSurfaces.h
            ControlSurfaceTypes.h
            Actuator.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE mathlib
                                        SimLib
                                        Messages
                                        AircraftProperties
                                        Utility
                                        )