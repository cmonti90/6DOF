set(target NavIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${target} INTERFACE Messages
                                          Serialization)


######################################


set(target Navigation)

set(SOURCES     NavigationComponent.cpp )

set(HEADERS     NavigationComponent.h
                NavigationTypes.h )

add_library(${target} STATIC ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        NavigationAlgorithm
                                        DebugTools
                                        Utility
                                        Serialization
                                        )

add_subdirectory(Algorithm)