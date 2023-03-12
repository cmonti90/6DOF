set(target Motor)

set(SOURCES Motor.cpp)

set(HEADERS Motor.h)

add_library(Motor ${SOURCES})

target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${target} PUBLIC TimeMngr)