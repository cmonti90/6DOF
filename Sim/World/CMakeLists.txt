
# set(target sixDofIntf)
# add_library(${target} INTERFACE)
# target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )
# target_link_libraries(${target} INTERFACE Messages
#                                           Serialization)


######################################


set(target SixDOFWorld)

set(SOURCES     6DOFSimulation.cpp
                AircraftEntity.cpp
                )

set(HEADERS     6DOFSimulation.h
                AircraftEntity.h
                )

add_library(${target} ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  
                                PRIVATE SimLib
                                        )

add_subdirectory(Algorithm)