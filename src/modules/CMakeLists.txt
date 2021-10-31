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

    set(${module_name}_obj_list "$<GENEX_EVAL:$<JOIN:$<TARGET_OBJECTS:${module_name}_elf_obj>, >>")
    set(${module_name}_lib_list "$<GENEX_EVAL:$<JOIN:$<TARGET_PROPERTY:${module_name}_elf_obj,LINK_LIBRARIES>, >>")

    add_library(${module_name}_elf_obj OBJECT EXCLUDE_FROM_ALL ${module_srcs} ${TPGZ_REL_SRC})
    link_libraries()
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.elf
        DEPENDS ${module_name}_elf_obj
        BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.map
        COMMAND sh -c "${CMAKE_LINKER} $<JOIN:$<TARGET_PROPERTY:${module_name}_elf_obj,LINK_FLAGS>, > $<JOIN:$<TARGET_PROPERTY:${module_name}_elf_obj,LINK_OPTIONS>, > --Map ${module_name}.map $<JOIN:$<TARGET_OBJECTS:${module_name}_elf_obj>, > $<JOIN:$<TARGET_PROPERTY:${module_name}_elf_obj,LINK_LIBRARIES>, > -o ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.elf")

    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.rel
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.elf ${CMAKE_SOURCE_DIR}/res/map/${PLATFORM}_${REGION}.lst
        COMMAND ${TPGZ_ELF2REL_EXE} ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.elf -s ${CMAKE_SOURCE_DIR}/res/map/${PLATFORM}_${REGION}.lst)

    add_custom_target(${module_name}
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.rel)
    add_dependencies(rels ${module_name})
    set_property(TARGET rels APPEND PROPERTY "TPGZ_MODULES" ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.rel)
endfunction()

include_directories(${CMAKE_SOURCE_DIR}/external/libtp_rel/include)
add_definitions(-D_PROJECT_NAME="${CMAKE_PROJECT_NAME}" -D_VERSION="${CMAKE_PROJECT_VERSION}" -D_VARIANT="public" -D_BUILDID="<unk>")
add_compile_options(-fno-exceptions -fno-rtti -std=gnu++17 -nostdlib -ffreestanding -ffunction-sections -fdata-sections -g -Os -Wall -Werror -Wno-address-of-packed-member -r -e_prolog -u_prolog -u_epilog -u_unresolved -Wl,--gc-sections -nostdlib -g  ${DEVKITPRO_MACHDEP}) # -T ${CMAKE_SOURCE_DIR}/external/libtp_rel/source/cxx.ld
add_link_options(-r -e _prolog -u _prolog -u _epilog -u _unresolved -g ${DEVKITPRO_MACHDEP})

add_subdirectory(hello_world)


get_target_property(TPGZ_RELS rels TPGZ_MODULES)
foreach(rel ${TPGZ_RELS})
    get_filename_component(rel_name ${rel} NAME)
    add_custom_command(TARGET rels
        POST_BUILD
        BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/rels/${rel_name}
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/rels
        COMMAND cp ${rel} ${CMAKE_CURRENT_BINARY_DIR}/rels/${rel_name})
endforeach()
