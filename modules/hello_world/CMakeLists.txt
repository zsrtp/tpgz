file(GLOB_RECURSE tpgz_hello_world_srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
tpgz_add_module(hello_world "${tpgz_hello_world_srcs}" "${CMAKE_CURRENT_SOURCE_DIR}/include")