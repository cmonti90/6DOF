set(target runner)

set(SOURCES runner.cpp)

set(HEADERS runner.h)

add_executable(${target} ${SOURCES} ${HEADERS})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

set(libs    Motor
            eom
            imu
            Encoder
            Controller
            Navigation
            TimeMngr
    )

target_link_libraries(${target} PUBLIC ${libs}
                                 mathlib)