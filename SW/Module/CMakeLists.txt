set(target procModule)

set(SOURCES ProcModule.cpp)

set(HEADERS ProcModule.h)

add_library(${target} ${SOURCES} ${HEADERS})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE MassProperties
                                        Gravity
                                        eom
                                        Aero
                                        Navigation
                                        Guidance
                                        Autopilot
                                        Engine
                                        ControlSurfaces
                                        IMU
                                        Clock
                                        PubSub
                                        )