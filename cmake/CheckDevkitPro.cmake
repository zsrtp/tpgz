if(NOT DEFINED ENV{DEVKITPPC} OR NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR "DevkitPro in your system.")
endif()

include($ENV{DEVKITPRO}/cmake/devkitPPC.cmake)

if(PLATFORM STREQUAL "GCN")
    message(STATUS "DevkitPro loaded for Gamecube")
    set(devkitpro_platform_path "gamecube")
    set(devkitpro_ogclib_path "cube")
    set(DEVKITPRO_MACHDEP "-DGEKKO -mogc -mcpu=750 -meabi -mhard-float")
else()
message(STATUS "DevkitPro loaded for Wii")
    set(devkitpro_platform_path "wii")
    set(devkitpro_ogclib_path "wii")
    set(DEVKITPRO_MACHDEP "-DGEKKO -mrvl -mcpu=750 -meabi -mhard-float")
endif()

set(DEVKITPRO_PORTLIBS_PATH "$ENV{DEVKITPRO}/portlibs")
set(DEVKITPRO_PORTLIBS "${DEVKITPRO_PORTLIBS_PATH}/${devkitpro_platform_path} ${DEVKITPRO_PORTLIBS_PATH}/ppc")

set(DEVKITPRO_LIBOGC_INC "$ENV{DEVKITPRO}/libogc/include")
set(DEVKITPRO_LIBOGC_LIB "$ENV{DEVKITPRO}/libogc/lib/${devkitpro_ogclib_path}")
