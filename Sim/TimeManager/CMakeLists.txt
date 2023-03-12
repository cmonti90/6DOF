set(target TimeMngr)

set(SOURCES TimeMngr.cpp)

set(HEADERS TimeMngr.h)

add_library(${target} SHARED ${SOURCES})

target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})