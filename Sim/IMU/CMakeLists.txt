set(target imu)

set(SOURCES imu.cpp)

set(HEADERS imu.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  eom
                                        TimeMngr
                                PRIVATE mathlib
                                        )