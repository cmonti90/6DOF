set(target GuidanceAlgorithm)

set(SOURCES GuidanceAlgorithm.cpp )

set(HEADERS GuidanceAlgorithm.h )

add_library(${target} STATIC ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE mathlib
                                        PubSub
                                        GuidanceIntf
                                        )