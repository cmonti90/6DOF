set(target CtrlSurfAlgorithm)

set(SOURCES ControlSurfaces.cpp
            Actuator.cpp)

set(HEADERS ControlSurfaces.h
            Actuator.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        AircraftProperties
                                        ControlSurfacesIntf
                                        Utility
                                        )