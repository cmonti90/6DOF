set(target Navigation)

set(SOURCES NavigationComponent.cpp )

set(HEADERS NavigationComponent.h )

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  TimeMngr
                                        Messages
                                PRIVATE mathlib
                                        PubSub
                                        )