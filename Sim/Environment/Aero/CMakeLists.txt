set(target Aero)

set(SOURCES Aero.cpp)

set(HEADERS Aero.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE mathlib
                                        SimLib
                                        AircraftProperties
                                        AeroTables
                                        eom
                                        # EarthGRAM
                                        )