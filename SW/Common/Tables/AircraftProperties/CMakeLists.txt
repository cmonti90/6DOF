
set(target AircraftProperties)

set(HEADERS PhysicalProperties.h )

add_library(${target} INTERFACE ${HEADERS})

target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )