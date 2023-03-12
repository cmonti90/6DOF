set(target Encoder)

set(SOURCES Encoder.cpp)

set(HEADERS Encoder.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  eom
                                        TimeMngr
                                PRIVATE mathlib
                                        )