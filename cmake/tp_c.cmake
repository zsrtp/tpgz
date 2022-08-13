file(GLOB_RECURSE TPGZ_TP_C_CPPFILES "${CMAKE_SOURCE_DIR}/external/libtp_c/src/*.cpp")

add_library(tp_c STATIC "${TPGZ_TP_C_CPPFILES}")
set_property(TARGET tp_c PROPERTY COMPILE_FLAGS "-g -c -O2 -Wall ${DEVKITPRO_MACHDEP}")
target_include_directories(tp_c PUBLIC "${CMAKE_SOURCE_DIR}/external/libtp_c/include")