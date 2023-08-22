set(target ImuAlgorithm)

set(SOURCES Imu.cpp)

set(HEADERS Imu.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Messages
                                PRIVATE mathlib
                                        PubSub
                                        ImuIntf
                                        )