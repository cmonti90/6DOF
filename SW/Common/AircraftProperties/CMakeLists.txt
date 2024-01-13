
set(target AircraftProperties)

set(SOURCES PhysicalProperties.cpp )
set(HEADERS PhysicalProperties.h )

add_library(${target} STATIC ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )