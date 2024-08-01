cmake_minimum_required(VERSION 3.16)

# Check if the platform is valid
if(NOT DEFINED PLATFORM)
    set(PLATFORM "GCN" CACHE STRING "The platform of the version to be patched (GCN or WII).")
    message(STATUS "PLATFORM not defined, defaulting to ${PLATFORM}")
elseif(NOT ${PLATFORM} STREQUAL "GCN")
    if(NOT ${PLATFORM} STREQUAL "WII")
        message(FATAL_ERROR "PLATFORM has to be either GCN or WII. \"${PLATFORM}\" was given.")
    endif()
endif()

if(${PLATFORM} STREQUAL "GCN")
    # Supported regions for GCN
    list(APPEND TPGZ_SUPPORTED_REGIONS NTSCU NTSCJ PAL)
else()
    # Supported regions for Wii
    list(APPEND TPGZ_SUPPORTED_REGIONS NTSCU_10 NTSCU_12 NTSCJ PAL)
endif()

if(NOT DEFINED REGION)
    # If the region is not defined, set one by default (the first in the supported list)
    list(GET TPGZ_SUPPORTED_REGIONS 0 REGION_ELEMENT)
    set(REGION ${REGION_ELEMENT} CACHE STRING "The region of the version to be patched.")
    message(STATUS "REGION not defined, defaulting to ${REGION}")
else()
    list(FIND TPGZ_SUPPORTED_REGIONS ${REGION} REGION_IDX)
    if(REGION_IDX EQUAL -1)
        message(FATAL_ERROR "\"${REGION}\" is not a valid region for the platform ${PLATFORM}")
    endif()
endif()

if(DEFINED PR_TEST)
    set(RUN_PR_TEST "-DPR_TEST=1")
endif()

if(DEFINED DEBUG)
    set(DEBUG "-DDEBUG=1")
endif()

# Start configuring the build directory
message(STATUS "Configuring for ${PLATFORM}_${REGION}...")

# These two lists are used as a map to get the right ISO file name for each version.
set(TPGZ_ISO_VERSIONS GCN_NTSCU GCN_NTSCJ GCN_PAL WII_NTSCU_10 WII_NTSCU_12 WII_NTSCJ WII_PAL)
set(TPGZ_ISO_FILES    GZ2E01    GZ2J01    GZ2P01  RZDE01       RZDE01_2     RZDJ01    RZDP01)

list(FIND TPGZ_ISO_VERSIONS ${PLATFORM}_${REGION} TPGZ_ISO_VERSION)
list(GET TPGZ_ISO_FILES ${TPGZ_ISO_VERSION} TPGZ_ISO_FILE)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/cmake
)

# Once we have the platform and region ready, we can check and setup the compiler toolchain.
include(cmake/CheckDevkitPro.cmake)

include_directories(${DEVKITPRO_LIBOGC_INC})
link_directories(${DEVKITPRO_LIBOGC_LIB})

include(cmake/patcher.cmake)
include(cmake/elf2rel.cmake)
include(cmake/relmapper.cmake)
include(cmake/fonts.cmake)

project(TPGZ
        VERSION 1.1.0
        DESCRIPTION "Twilight Princess speedrunning practice and testing tool"
        HOMEPAGE_URL "tpgz.io"
        LANGUAGES C CXX ASM)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/isos)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set compiler stuff
include_directories(external)
add_definitions(-D${PLATFORM}_${REGION} -D${PLATFORM}_PLATFORM -DGZ_VERSION=${CMAKE_PROJECT_VERSION} -D_PROJECT_NAME="${CMAKE_PROJECT_NAME}" -D_VERSION="${CMAKE_PROJECT_VERSION}" -D_VARIANT="public" -D_BUILDID="${CMAKE_PROJECT_VERSION}" ${DEBUG} ${RUN_PR_TEST})
add_compile_options(-fdiagnostics-color=always -fvisibility=hidden)

include(cmake/tp_c.cmake)
include(cmake/gcn_c.cmake)
include(cmake/${PLATFORM}_${REGION}.cmake)

# Load the REL Loader code and parse it
file(READ "res/bin/${PLATFORM}_${REGION}.bin" TPGZ_LOADER_BIN HEX)
string(REGEX REPLACE "([0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F])" "u32 0x\\1\n" TPGZ_CFG_LOADER_BIN ${TPGZ_LOADER_BIN})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/patch.asm.in ${CMAKE_CURRENT_BINARY_DIR}/patch.asm)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/RomHack.toml.in ${CMAKE_CURRENT_BINARY_DIR}/RomHack.toml)

add_subdirectory(modules)

add_custom_target(tpgz ALL)
add_dependencies(tpgz tp_c gcn_c modules)
set_property(TARGET tpgz PROPERTY COMPILE_FLAGS "-g -c -Os -std=gnu++20 -Wall ${DEVKITPRO_MACHDEP}")

get_target_property(TPGZ_MODULES modules TPGZ_MODULES)
foreach(module ${TPGZ_MODULES})
    add_dependencies(tpgz ${module}_rel)
endforeach()

set(TPGZ_RELS ${TPGZ_MODULES})
list(TRANSFORM TPGZ_RELS REPLACE "(.+)" "\\1_rel")

foreach(rel_tgt ${TPGZ_RELS})
    get_target_property(rel_tgt_file ${rel_tgt} TPGZ_MODULE_FILE)
    list(APPEND TPGZ_REL_FILES ${rel_tgt_file})
endforeach()

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_BLD_ISO}
    DEPENDS tpgz modules ${TPGZ_PATCHER_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_SOURCE_DIR}/isos/${TPGZ_ISO_FILE}.iso  ${CMAKE_CURRENT_BINARY_DIR}/patch.asm ${CMAKE_CURRENT_BINARY_DIR}/RomHack.toml ${TPGZ_REL_FILES}
    COMMAND ${TPGZ_PATCHER_EXE} build)

string(REPLACE ".iso" ".patch" TPGZ_CFG_BLD_PATCH_OLD ${TPGZ_CFG_BLD_ISO})
string(TOLOWER ${PLATFORM} tpgz_platform_lower)
string(TOLOWER ${REGION} tpgz_region_lower)
string(REPLACE "_" "-" tpgz_region_lower ${tpgz_region_lower})
set(TPGZ_CFG_BLD_PATCH ${CMAKE_PROJECT_VERSION}-${tpgz_platform_lower}-${tpgz_region_lower}.patch)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_BLD_PATCH}
    DEPENDS tpgz modules ${TPGZ_PATCHER_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/patch.asm ${CMAKE_CURRENT_BINARY_DIR}/RomHack.toml ${TPGZ_REL_FILES}
    COMMAND ${TPGZ_PATCHER_EXE} build --patch
    COMMAND ${CMAKE_COMMAND} -E rename ${TPGZ_CFG_BLD_PATCH_OLD} ${TPGZ_CFG_BLD_PATCH})

add_custom_target(iso
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_BLD_ISO})

add_custom_target(patch
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_BLD_PATCH})
