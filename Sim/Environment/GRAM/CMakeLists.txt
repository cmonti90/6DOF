
set(target EarthGRAM)

set(SOURCES     EarthGRAM.cpp)

set(HEADERS     EarthGRAM.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE GRAM_Earth
                                        SimLib
                                        mathlib
                                        eom
                                        DebugTools
                                        Utility
                                        )