
set(target MassPropertiesIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${target} INTERFACE Messages
                                          Serialization)


######################################


set(target MassProperties)

set(SOURCES     MassPropertiesComponent.cpp)

set(HEADERS     MassPropertiesComponent.h
                MassPropertiesTypes.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        MassPropertiesAlgorithm
                                        Serialization
                                        )

add_subdirectory(Algorithm)