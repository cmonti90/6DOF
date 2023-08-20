set(target EngineIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )


######################################


set(target Engine)

set(SOURCES     EngineComponent.cpp)

set(HEADERS     EngineComponent.h
                EngineTypes.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  TimeMngr
                                        Messages
                                PRIVATE mathlib
                                        PubSub
                                        engineAlgorithm
                                        )

add_subdirectory(Algorithm)