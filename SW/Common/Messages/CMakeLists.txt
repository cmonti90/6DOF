set(target Messages)

set(SOURCES test1Msg.cpp
            test2Msg.cpp
            test3Msg.cpp)

set(HEADERS test1Msg.h
            test2Msg.h
            test3Msg.h)

add_library(${target} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  TimeMngr
                                PRIVATE PubSub
                                        )