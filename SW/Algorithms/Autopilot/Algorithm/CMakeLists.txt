set(target AutopilotAlgorithm)

set(SOURCES AutopilotAlgorithm.cpp )

set(HEADERS AutopilotAlgorithm.h )

add_library(${target} STATIC ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE mathlib
                                        PubSub
                                        AutopilotIntf
                                        )