set(target AutopilotIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${target} INTERFACE Messages
                                          Serialization)


######################################


set(target Autopilot)

set(SOURCES AutopilotComponent.cpp )

set(HEADERS AutopilotComponent.h )

add_library(${target} STATIC ${SOURCES} )

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE mathlib
                                        PubSub
                                        AutopilotAlgorithm
                                        DebugTools
                                        AutopilotIntf
                                        Utility
                                        )

add_subdirectory(Algorithm)