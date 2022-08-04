cmake_minimum_required(VERSION 3.14)

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
    list(APPEND TPGZ_SUPPORTED_REGIONS NTSCU_10 PAL)
endif()

if(NOT DEFINED REGION)
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

message(STATUS "Configuring for ${PLATFORM}_${REGION}...")

set(TPGZ_ISO_VERSIONS GCN_NTSCU GCN_NTSCJ GCN_PAL WII_NTSCU_10 WII_PAL)
set(TPGZ_ISO_FILES    GZ2E01    GZ2J01    GZ2P01  RZDE01       RZDP01)

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
include(cmake/fonts.cmake)

project(TPGZ
        VERSION 0.5.0
        DESCRIPTION "Twilight Princess speedrunning practice and testing tool"
        HOMEPAGE_URL "tpgz.io"
        LANGUAGES C CXX ASM)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/isos)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set compiler stuff
include_directories(include external)
#set(CMAKE_CXX_FLAGS "-g -c -O2 -Wall ${DEVKITPRO_MACHDEP} -D${PLATFORM}_${REGION} -D${PLATFORM}_PLATFORM -DGZ_VERSION=${CMAKE_PROJECT_VERSION} ${RUN_PR_TEST}")
add_definitions(-D${PLATFORM}_${REGION} -D${PLATFORM}_PLATFORM -DPLATFORM_${PLATFORM} -DGZ_VERSION=${CMAKE_PROJECT_VERSION} -D_PROJECT_NAME="${CMAKE_PROJECT_NAME}" -D_VERSION="${CMAKE_PROJECT_VERSION}" -D_VARIANT="public" -D_BUILDID="${CMAKE_PROJECT_VERSION}" ${RUN_PR_TEST})

include(cmake/tp_c.cmake)
include(cmake/gcn_c.cmake)
include(cmake/tp_rel.cmake)
include(cmake/${PLATFORM}_${REGION}.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/patch.asm.in ${CMAKE_CURRENT_BINARY_DIR}/patch.asm)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/RomHack.toml.in ${CMAKE_CURRENT_BINARY_DIR}/RomHack.toml)

add_subdirectory(src)
add_subdirectory(modules)

add_library(tpgz STATIC "${CPPFILES}")
add_dependencies(tpgz tp_c gcn_c) #tp_rel
set_property(TARGET tpgz PROPERTY COMPILE_FLAGS "-g -c -O2 -Wall ${DEVKITPRO_MACHDEP}")

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/res
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/res
    COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/res/ ${CMAKE_CURRENT_BINARY_DIR}/res
    COMMENT Copying res/ folder)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_BINARY_DIR}/res")

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_BLD_ISO}
    DEPENDS tpgz ${TPGZ_PATCHER_EXE} ${CMAKE_CURRENT_BINARY_DIR}/res ${CMAKE_CURRENT_SOURCE_DIR}/isos/${TPGZ_ISO_FILE}.iso 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${TPGZ_PATCHER_EXE} build --raw)

string(REPLACE ".iso" ".patch" TPGZ_CFG_BLD_PATCH ${TPGZ_CFG_BLD_ISO})
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_BLD_PATCH}
    DEPENDS tpgz ${TPGZ_PATCHER_EXE} ${CMAKE_CURRENT_BINARY_DIR}/res
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${TPGZ_PATCHER_EXE} build --raw --patch)

add_custom_target(iso
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_BLD_ISO})

add_custom_target(patch
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_BLD_PATCH})
