set(target eom)

set(SOURCES eom.cpp
            eomGetters.cpp)

set(HEADERS eom.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE SimLib
                                        mathlib
                                        AircraftProperties
                                        EarthModels
                                        MassProperties
                                        Utility
                                        )