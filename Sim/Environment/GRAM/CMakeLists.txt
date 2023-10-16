
set(target GRAMComponent)

set(SOURCES     GRAMComponent.cpp)

set(HEADERS     GRAMComponent.h
                GRAMTypes.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE GRAM_Earth
                                        Messages
                                        mathlib
                                        PubSub
                                        Serialization
                                        DebugTools
                                        Utility
                                        )