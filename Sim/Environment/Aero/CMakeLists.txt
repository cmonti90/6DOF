
set(target aeroIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${target} INTERFACE Messages
                                          Serialization)


######################################


set(target Aero)

set(SOURCES     AeroComponent.cpp)

set(HEADERS     AeroComponent.h
                AeroTypes.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        AeroAlgorithm
                                        Serialization
                                        Utility
                                        )

add_subdirectory(Algorithm)