set(target engineAlgorithm)

set(SOURCES engine.cpp)

set(HEADERS engine.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        AircraftProperties
                                        EngineIntf
                                        )