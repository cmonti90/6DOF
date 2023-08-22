
set(target GravityIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )


######################################


set(target Gravity)

set(SOURCES     GravityComponent.cpp)

set(HEADERS     GravityComponent.h
                GravityTypes.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        GravityAlgorithm
                                        )

add_subdirectory(Algorithm)