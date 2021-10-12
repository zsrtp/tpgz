# Get Host system distribution
execute_process(
    COMMAND uname -o
    OUTPUT_VARIABLE TPGZ_HOST_SYS)

set(TPGZ_ELF2REL_EXE ${CMAKE_SOURCE_DIR}/bin/elf2rel.exe)

if(TPGZ_HOST_SYS MATCHES "Linux")
    message(DEBUG "We're on Linux [${TPGZ_HOST_SYS}], found '${TPGZ_ELF2REL_EXE}'")
    set(TPGZ_ELF2REL_EXE wine ${TPGZ_ELF2REL_EXE})
else()
    message(DEBUG "We are not on Linux [${TPGZ_HOST_SYS}], ${TPGZ_ELF2REL_EXE}")
endif()

if(NOT TPGZ_ELF2REL_EXE)
    message(FATAL_ERROR "please put \"elf2rel.exe\" in the bin/ folder")
endif()