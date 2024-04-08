set(target AutopilotFilters)

set(SOURCES
        FilterP.cpp
        FilterQR.cpp
        FilterRollDC.cpp

        HighRateDigitalFilter2.cpp
        HighRateDigitalFilter4.cpp

        LowRateDigitalFilterComp.cpp
        LowRateDigitalFilterLeadLag.cpp
        LowRateDigitalFilterLowPass2.cpp
        LowRateDigitalFilterNotch2.cpp
        )

add_library(${target} STATIC ${SOURCES})

target_include_directories(${target}    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
                                                )

target_link_libraries(${target} PRIVATE mathlib )