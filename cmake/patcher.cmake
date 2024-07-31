find_program(TPGZ_PATCHER_EXE romhack HINTS ${CMAKE_SOURCE_DIR}/bin)

if(NOT TPGZ_PATCHER_EXE)
    message(FATAL_ERROR "please put \"romhack\" in the bin/ folder")
endif()