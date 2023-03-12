set(target Controller)

set(SOURCES Controller.cpp)

set(HEADERS Controller.h)

add_library(Controller SHARED ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                        )

target_link_libraries(${target} PUBLIC  Navigation
                                        TimeMngr
                                 mathlib
                                )

