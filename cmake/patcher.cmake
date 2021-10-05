string(TOLOWER ${PLATFORM} TPGZ_PATCHER_DIR)

set(TPGZ_PATCHER_EXE "${TPGZ_PATCHER_DIR}/romhack")
if(WIN32)
    set(TPGZ_PATCHER_EXE "${TPGZ_PATCHER_EXE}.exe")
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/bin/${TPGZ_PATCHER_EXE}")
    message(FATAL_ERROR "please put \"${TPGZ_PATCHER_EXE}\" in the bin/ folder")
endif()