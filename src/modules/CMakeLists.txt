# TODO Each module will be taken into account here

# Custom target that will compile all the modules at once
add_custom_target(rels)

set(TPGZ_REL_SRC
    cxx.cpp
    memory.cpp
    patch.cpp
    tools.cpp
    chronos/timer.cpp
    display/console.cpp
    gc_wii/card.cpp
    runtime/restfpr_x.s
    runtime/restgpr_x.s)

list(TRANSFORM TPGZ_REL_SRC PREPEND ${CMAKE_SOURCE_DIR}/external/libtp_rel/source/)

# This function will setup an individual module to be compiled and added to the dependencies of the "rels" target
function(tpgz_add_module module_name module_srcs)
    if(ARGC GREATER "2")
        set(module_inc_paths ${ARGV2})
    endif()
    if(ARGC GREATER "3")
        set(module_lib_paths ${ARGV3})
    endif()

    if(module_inc_paths)
        include_directories(${module_inc_paths})
    endif()
    if(module_lib_paths)
        link_directories(${module_lib_paths})
    endif()

    add_executable(${module_name}.elf EXCLUDE_FROM_ALL ${module_srcs} ${TPGZ_REL_SRC})

    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.rel
        DEPENDS ${module_name}.elf ${CMAKE_SOURCE_DIR}/res/map/${PLATFORM}_${REGION}.lst
        COMMAND ${TPGZ_ELF2REL_EXE} ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.elf -s ${CMAKE_SOURCE_DIR}/res/map/${PLATFORM}_${REGION}.lst)

    add_custom_target(${module_name}
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.rel)
    add_dependencies(rels ${module_name})
endfunction()

include_directories(${CMAKE_SOURCE_DIR}/external/libtp_rel/include)
add_definitions(-D_PROJECT_NAME="${CMAKE_PROJECT_NAME}" -D_VERSION="${CMAKE_PROJECT_VERSION}" -D_VARIANT="public" -D_BUILDID="<unk>")
add_link_options(-fno-exceptions -fno-rtti -std=gnu++17 -nostdlib -ffreestanding -ffunction-sections -fdata-sections -g -Os -Wall -Werror -Wno-address-of-packed-member -r -e _prolog -u _prolog -u _epilog -u _unresolved -Wl,--gc-sections -nostdlib -g  ${DEVKITPRO_MACHDEP} -Wl,-Map,${module_name}.map -T ${CMAKE_SOURCE_DIR}/external/libtp_rel/source/cxx.ld)

add_subdirectory(hello_world)