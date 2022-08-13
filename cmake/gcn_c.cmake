file(GLOB_RECURSE TPGZ_GNC_CPPFILES "${CMAKE_SOURCE_DIR}/external/gcn_c/src/*.c")

add_library(gcn_c STATIC "${TPGZ_GNC_CPPFILES}")
set_property(TARGET gcn_c PROPERTY COMPILE_FLAGS "-g -c -Os -Wall ${DEVKITPRO_MACHDEP}")
target_include_directories(gcn_c PUBLIC "${CMAKE_SOURCE_DIR}/external/gcn_c/include")
