set(tpgz_hello_world_srcs
    src/main.cpp)
list(TRANSFORM tpgz_hello_world_srcs PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)
tpgz_add_module(hello_world "${tpgz_hello_world_srcs}" "${CMAKE_CURRENT_SOURCE_DIR}/include")