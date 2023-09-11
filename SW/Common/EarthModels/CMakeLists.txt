
set(target EarthModels)

set(SOURCES WGS84.cpp )

set(HEADERS WGS84.h )

add_library(${target} SHARED ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE  mathlib )