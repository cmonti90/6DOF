set(target procModule)

set(SOURCES ProcModule.cpp)

set(HEADERS ProcModule.h)

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  TimeMngr
                                PRIVATE MassProperties
                                        eom
                                        Aero
                                        Navigation
                                        Guidance
                                        Autopilot
                                        Engine
                                        Clock
                                        PubSub
                                        )