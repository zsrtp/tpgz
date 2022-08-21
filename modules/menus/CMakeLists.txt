file(GLOB TPGZ_SUB_MENU_MODULES CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*")

# Include all the submodules
foreach(module ${TPGZ_SUB_MENU_MODULES})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${module})
        message(VERBOSE "Including submodule '${module}'")
        add_subdirectory(${module})
    endif()
endforeach()