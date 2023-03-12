set(target eom)

set(SOURCES eom.cpp)

set(HEADERS eom.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  Motor
                                        TimeMngr
                                PRIVATE mathlib
                                        )