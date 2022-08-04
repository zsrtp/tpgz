file(GLOB_RECURSE TPGZ_GNC_CPPFILES "${CMAKE_SOURCE_DIR}/external/gcn_c/src/*.c")

include_directories("${CMAKE_SOURCE_DIR}/external/gcn_c/include")

add_library(gcn_c STATIC "${TPGZ_GNC_CPPFILES}")
set_property(TARGET gcn_c PROPERTY COMPILE_FLAGS "-g -c -O2 -Wall ${DEVKITPRO_MACHDEP}")