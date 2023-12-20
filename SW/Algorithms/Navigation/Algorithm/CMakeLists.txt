set(target NavigationAlgorithm)

set(SOURCES NavigationAlgorithm.cpp )

set(HEADERS NavigationAlgorithm.h )

add_library(${target} STATIC ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE mathlib
                                        PubSub
                                        NavIntf
                                        Utility
                                        )