set(target NavigationAlgorithm)

set(SOURCES NavigationAlgorithm.cpp )

set(HEADERS NavigationAlgorithm.h )

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
Utility
                                PRIVATE mathlib
                                        PubSub
                                        )