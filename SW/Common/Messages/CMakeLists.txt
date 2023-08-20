set(target Messages)

set(SOURCES     AeroMsg.cpp
                EngineMsg.cpp
                test1Msg.cpp
                test2Msg.cpp)

set(HEADERS     AeroMsg.h
                EngineMsg.h
                test1Msg.h
                test2Msg.h)

add_library(${target} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PUBLIC  TimeMngr
                                PRIVATE PubSub
                                        )