set(target IMU)

set(SOURCES IMU.cpp)

set(HEADERS IMU.h
            IMUTypes.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE SimLib
                                        PubSub
                                        mathlib
                                        Messages
                                        )