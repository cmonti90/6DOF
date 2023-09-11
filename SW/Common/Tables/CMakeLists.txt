
set(target TableTemplates)

set(HEADERS Table1D.h )

add_library(${target} INTERFACE ${HEADERS})

target_include_directories(${target}    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )


##################################################


add_subdirectory(Aero)