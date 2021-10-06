string(TOLOWER ${PLATFORM} TPGZ_PATCHER_DIR)

find_program(TPGZ_PATCHER_EXE romhack HINTS ${CMAKE_CURRENT_SOURCE_DIR}/bin/${TPGZ_PATCHER_DIR})

if(NOT TPGZ_PATCHER_EXE)
    message(FATAL_ERROR "please put \"romhack\" in the bin/ folder")
endif()