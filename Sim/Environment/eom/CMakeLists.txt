
set(target eomIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${target} INTERFACE  Messages
                                           Serialization
                                           PubSub
                                            )


######################################


set(target eom)

set(SOURCES     EomComponent.cpp)

set(HEADERS     EomComponent.h
                EomTypes.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        eomAlgorithm
                                        Serialization
                                        Utility
                                        )

add_subdirectory(Algorithm)