set(TPGZ_SAVE_META_GCN_DIR ${CMAKE_CURRENT_BINARY_DIR}/save_files)
set(TPGZ_SAVE_META_WII_DIR ${CMAKE_CURRENT_BINARY_DIR}/save_files_wii)
file(MAKE_DIRECTORY ${TPGZ_SAVE_META_GCN_DIR})
file(MAKE_DIRECTORY ${TPGZ_SAVE_META_WII_DIR})

set(TPGZ_SAVE_META_GEN ${CMAKE_SOURCE_DIR}/external/misc/gen_save_meta.py)

execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import yaml"
    RESULT_VARIABLE TPGZ_PYYAML_CHECK)
if(NOT TPGZ_PYYAML_CHECK EQUAL 0)
    message(FATAL_ERROR "PyYAML is required to generate save metadata. Install it with: ${Python3_EXECUTABLE} -m pip install -r external/misc/requirements.txt")
endif()

function(tpgz_gen_save_meta data_path output_dir output_name)
    add_custom_command(
        OUTPUT ${output_dir}/${output_name}
        COMMAND ${Python3_EXECUTABLE} ${TPGZ_SAVE_META_GEN} ${CMAKE_SOURCE_DIR}/${data_path} ${output_dir}/${output_name}
        DEPENDS ${TPGZ_SAVE_META_GEN} ${CMAKE_SOURCE_DIR}/${data_path}
        VERBATIM)
endfunction()

tpgz_gen_save_meta(res/save_files/ad.yml ${TPGZ_SAVE_META_GCN_DIR} ad.bin)
tpgz_gen_save_meta(res/save_files/ad.yml ${TPGZ_SAVE_META_WII_DIR} ad.bin)

tpgz_gen_save_meta(res/save_files/any.yml ${TPGZ_SAVE_META_GCN_DIR} any.bin)
tpgz_gen_save_meta(res/save_files/any.yml ${TPGZ_SAVE_META_WII_DIR} any.bin)

tpgz_gen_save_meta(res/save_files/glitchless.yml ${TPGZ_SAVE_META_GCN_DIR} glitchless.bin)
tpgz_gen_save_meta(res/save_files/glitchless.yml ${TPGZ_SAVE_META_WII_DIR} glitchless.bin)

tpgz_gen_save_meta(res/save_files/nosq.yml ${TPGZ_SAVE_META_GCN_DIR} nosq.bin)
tpgz_gen_save_meta(res/save_files/nosq.yml ${TPGZ_SAVE_META_WII_DIR} nosq.bin)

tpgz_gen_save_meta(res/save_files/any_bite.yml ${TPGZ_SAVE_META_GCN_DIR} any_bite.bin)
tpgz_gen_save_meta(res/save_files_wii/any_bite.yml ${TPGZ_SAVE_META_WII_DIR} any_bite.bin)

tpgz_gen_save_meta(res/save_files/hundo.yml ${TPGZ_SAVE_META_GCN_DIR} hundo.bin)
tpgz_gen_save_meta(res/save_files_wii/hundo.yml ${TPGZ_SAVE_META_WII_DIR} hundo.bin)

set(TPGZ_SAVE_META_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_SAVE_META_PATH}/ad.bin
    ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_SAVE_META_PATH}/any.bin
    ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_SAVE_META_PATH}/glitchless.bin
    ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_SAVE_META_PATH}/nosq.bin
    ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_SAVE_META_PATH}/any_bite.bin
    ${CMAKE_CURRENT_BINARY_DIR}/${TPGZ_CFG_SAVE_META_PATH}/hundo.bin)

set(TPGZ_SAVE_META_ALL_FILES
    ${TPGZ_SAVE_META_GCN_DIR}/ad.bin ${TPGZ_SAVE_META_WII_DIR}/ad.bin
    ${TPGZ_SAVE_META_GCN_DIR}/any.bin ${TPGZ_SAVE_META_WII_DIR}/any.bin
    ${TPGZ_SAVE_META_GCN_DIR}/glitchless.bin ${TPGZ_SAVE_META_WII_DIR}/glitchless.bin
    ${TPGZ_SAVE_META_GCN_DIR}/nosq.bin ${TPGZ_SAVE_META_WII_DIR}/nosq.bin
    ${TPGZ_SAVE_META_GCN_DIR}/any_bite.bin ${TPGZ_SAVE_META_WII_DIR}/any_bite.bin
    ${TPGZ_SAVE_META_GCN_DIR}/hundo.bin ${TPGZ_SAVE_META_WII_DIR}/hundo.bin)
add_custom_target(save_metadata ALL DEPENDS ${TPGZ_SAVE_META_ALL_FILES})
