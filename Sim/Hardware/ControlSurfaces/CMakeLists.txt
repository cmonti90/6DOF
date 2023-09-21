set(target ControlSurfacesIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${target} INTERFACE Messages
                                          Serialization)


######################################


set(target ControlSurfaces)

set(SOURCES     ControlSurfacesComponent.cpp)

set(HEADERS     ControlSurfacesComponent.h
                ControlSurfacesTypes.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        CntrlSurfAlgorithm
                                        )

add_subdirectory(Algorithm)