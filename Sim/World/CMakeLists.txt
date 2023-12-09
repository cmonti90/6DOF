set(target Entities)

set(SOURCES     AircraftEntity.cpp
                )

set(HEADERS     AircraftEntity.h
                )

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  
                                PRIVATE SimLib
                                        procModule
                                        Engine
                                        IMU
                                        Messages
                                        )


######################################


set(target SixDOFWorld)

set(SOURCES     6DOFSimulation.cpp
                )

set(HEADERS     6DOFSimulation.h
                )

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  
                                PRIVATE SimLib
                                        Entities
                                        )