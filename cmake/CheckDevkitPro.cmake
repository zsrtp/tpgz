if(NOT DEFINED ENV{DEVKITPPC} OR NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR "Please set DEVKITPPC and DEVKITPRO in your environment. export DEVKITPPC=<path to>devkitPro/devkitPPC")
endif()

set(CMAKE_SYSTEM_NAME "Gecko")
set(CMAKE_SYSTEM_PROCESSOR powerpc)

set(DEVKITPRO_TOOLS "$ENV{DEVKITPRO}/tools/bin")
set(DEVKITPPC_BIN "$ENV{DEVKITPRO}/devkitPPC/bin")
set(DEVKITPPC_PREFIX "${DEVKITPPC_BIN}/powerpc-eabi-")

set(CMAKE_C_COMPILER "${DEVKITPPC_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${DEVKITPPC_PREFIX}g++")
set(CMAKE_C_COMPILER_AR "${DEVKITPPC_PREFIX}gcc-ar")

set(DEVKITPRO_MACHDEP "-DGEKKO -mogc -mcpu=750 -meabi -mhard-float")

if(PLATFORM STREQUAL "GCN")
    set(devkitpro_platform_path "gamecube")
    set(devkitpro_ogclib_path "cube")
else()
    set(devkitpro_platform_path "wii")
    set(devkitpro_ogclib_path "wii")
endif()

set(DEVKITPRO_PORTLIBS_PATH "$ENV{DEVKITPRO}/portlibs")
set(DEVKITPRO_PORTLIBS "${DEVKITPRO_PORTLIBS_PATH}/${devkitpro_platform_path} ${DEVKITPRO_PORTLIBS_PATH}/ppc")

set(DEVKITPRO_LIBOGC_INC "$ENV{DEVKITPRO}/libogc/include")
set(DEVKITPRO_LIBOGC_LIB "$ENV{DEVKITPRO}/libogc/lib/${devkitpro_ogclib_path}")
