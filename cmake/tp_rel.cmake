file(GLOB_RECURSE TPGZ_TP_REL_CPPFILES "${CMAKE_SOURCE_DIR}/external/libtp_rel/source/*.cpp")
file(GLOB_RECURSE TPGZ_TP_REL_ASMFILES "${CMAKE_SOURCE_DIR}/external/libtp_rel/source/*.s")
file(GLOB_RECURSE TPGZ_TP_REL_LDFILES "${CMAKE_SOURCE_DIR}/external/libtp_rel/source/*.ld")

include_directories("${CMAKE_SOURCE_DIR}/external/libtp_rel/include")

add_library(tp_rel STATIC)
target_sources(tp_rel
    PUBLIC ${TPGZ_TP_REL_CPPFILES}
    PUBLIC ${TPGZ_TP_REL_ASMFILES})
set_property(TARGET tp_rel APPEND PROPERTY COMPILE_OPTIONS "-Wl,-Map,tp_rel.map")