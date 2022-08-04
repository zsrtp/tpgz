# TODO Each module will be taken into account here

# Custom target that will compile all the modules at once
add_custom_target(rels)

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

    add_executable(${module_name} EXCLUDE_FROM_ALL)
    target_sources(${module_name}
        PUBLIC ${module_srcs})
    target_link_libraries(${module_name} tp_rel)
    set_property(TARGET ${module_name} APPEND PROPERTY LINK_OPTIONS "-Wl,-Map,${module_name}.map")
    set_property(TARGET ${module_name} APPEND PROPERTY LINK_DEPENDS "${TPGZ_TP_REL_LDFILES}")

    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.rel
        DEPENDS ${module_name} ${CMAKE_SOURCE_DIR}/res/map/${PLATFORM}_${REGION}.lst
        COMMAND ${TPGZ_ELF2REL_EXE} $<TARGET_FILE:${module_name}> -s ${CMAKE_SOURCE_DIR}/res/map/${PLATFORM}_${REGION}.lst)
    add_custom_target(${module_name}_rel
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.rel)

    add_dependencies(rels ${module_name}_rel)
    set_property(TARGET rels APPEND PROPERTY "TPGZ_MODULES" ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.rel)
endfunction()

include_directories(${CMAKE_SOURCE_DIR}/external/libtp_rel/include)
add_compile_options(-fno-exceptions -fno-rtti -std=gnu++17 -nostdlib -ffreestanding -ffunction-sections -fdata-sections -g -Os -Wall -Werror -Wno-address-of-packed-member -r -e_prolog -u_prolog -u_epilog -u_unresolved -Wl,--gc-sections -nostdlib -g ${DEVKITPRO_MACHDEP_LIST}) # -T ${CMAKE_SOURCE_DIR}/external/libtp_rel/source/cxx.ld
add_link_options(-r -e_prolog -u_prolog -u_epilog -u_unresolved -Wl,--gc-sections -nostdlib -g ${DEVKITPRO_MACHDEP_LIST})

# Include all the submodules
add_subdirectory(hello_world)

add_custom_command(TARGET rels
    POST_BUILD
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/rels)

# Once all the submodules are included, setup the transfer of the module
get_target_property(TPGZ_RELS rels TPGZ_MODULES)
foreach(rel ${TPGZ_RELS})
    get_filename_component(rel_name ${rel} NAME)
    add_custom_command(TARGET rels
        POST_BUILD
        BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/rels/${rel_name}
        COMMAND cp ${rel} ${CMAKE_CURRENT_BINARY_DIR}/rels/${rel_name})
endforeach()
