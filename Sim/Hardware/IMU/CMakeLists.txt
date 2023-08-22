set(target ImuIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )


######################################


set(target IMU)

set(SOURCES     ImuComponent.cpp)

set(HEADERS     ImuComponent.h
                ImuTypes.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        ImuAlgorithm
                                        )

add_subdirectory(Algorithm)