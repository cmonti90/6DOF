
set(target AeroTables)

set(HEADERS AltitudeTables.h )

add_library(${target} INTERFACE ${HEADERS})

target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} INTERFACE  TableTemplates)