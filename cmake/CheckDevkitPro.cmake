cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR "Could not find DevkitPro in your system.")
endif()

include($ENV{DEVKITPRO}/cmake/devkitPPC.cmake)

if(PLATFORM STREQUAL "GCN")
    # include($ENV{DEVKITPRO}/cmake/GameCube.cmake)
    message(STATUS "DevkitPro loaded for Gamecube")
    set(devkitpro_platform_path "gamecube")
    set(devkitpro_ogclib_path "cube")
    set(DEVKITPRO_MACHDEP_LIST -mno-sdata -DGEKKO -mogc -mcpu=750 -meabi -mhard-float)
else()
    # include($ENV{DEVKITPRO}/cmake/Wii.cmake)
    message(STATUS "DevkitPro loaded for Wii")
    set(devkitpro_platform_path "wii")
    set(devkitpro_ogclib_path "wii")
    set(DEVKITPRO_MACHDEP_LIST -mno-sdata -DGEKKO -mrvl -mcpu=750 -meabi -mhard-float)
endif()
list(JOIN DEVKITPRO_MACHDEP_LIST " " DEVKITPRO_MACHDEP)

set(DEVKITPRO_PORTLIBS_PATH "$ENV{DEVKITPRO}/portlibs")
set(DEVKITPRO_PORTLIBS "${DEVKITPRO_PORTLIBS_PATH}/${devkitpro_platform_path} ${DEVKITPRO_PORTLIBS_PATH}/ppc")

set(DEVKITPRO_LIBOGC_INC "$ENV{DEVKITPRO}/libogc/include")
set(DEVKITPRO_LIBOGC_LIB "$ENV{DEVKITPRO}/libogc/lib/${devkitpro_ogclib_path}")
