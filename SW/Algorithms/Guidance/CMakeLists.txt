set(target GuidanceIntf)
add_library(${target} INTERFACE)
target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${target} INTERFACE Messages
                                          Serialization)


######################################


set(target Guidance)

set(SOURCES     GuidanceComponent.cpp )

set(HEADERS     GuidanceComponent.h
                GuidanceTypes.h )

add_library(${target} STATIC ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE mathlib
                                        PubSub
                                        GuidanceAlgorithm
                                        DebugTools
                                        GuidanceIntf
                                        Utility
                                        )

add_subdirectory(Algorithm)