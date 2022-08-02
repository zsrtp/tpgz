file(GLOB_RECURSE TPGZ_TP_REL_CPPFILES "${CMAKE_SOURCE_DIR}/external/libtp_rel/source/*.cpp")
file(GLOB_RECURSE TPGZ_TP_REL_ASMFILES "${CMAKE_SOURCE_DIR}/external/libtp_rel/source/*.s")
file(GLOB_RECURSE TPGZ_TP_REL_LDFILES "${CMAKE_SOURCE_DIR}/external/libtp_rel/source/*.ld")

include_directories("${CMAKE_SOURCE_DIR}/external/libtp_rel/include")
add_definitions(-D_PROJECT_NAME="${CMAKE_PROJECT_NAME}" -D_VERSION="${CMAKE_PROJECT_VERSION}" -D_VARIANT="public" -D_BUILDID="<unk>")

add_library(tp_rel STATIC "${TPGZ_TP_REL_CPPFILES}" "${TPGZ_TP_REL_ASMFILES}")