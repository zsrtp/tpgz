# IMPORTANT: if you add/remove a source file that has to be compiled, add it
# manually instead of automatically searching for it (as mentioned in the note
# of the "Filesystem" section of
# https://cmake.org/cmake/help/latest/command/file.html#filesystem)
file(GLOB_RECURSE CPPFILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(CPPFILES ${CPPFILES} PARENT_SCOPE)