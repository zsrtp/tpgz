# ASM values
set(TPGZ_CFG_ARENALO "0x803449dc")
set(TPGZ_CFG_ARENALO_VAL "0x3c608059")
set(TPGZ_CFG_MAIN "0x80008cec")
set(TPGZ_CFG_MAIN_TRAMPOLINE "0x803ce3dc")
set(TPGZ_CFG_FIRST_INSTRUCTION "0x542b06fe")
set(TPGZ_CFG_RETURN_TO_MAIN "0x4bc3a910")
set(TPGZ_CFG_SET_WATER_DROP_EFFECT1 "0x8011759c")
set(TPGZ_CFG_SET_WATER_DROP_EFFECT2 "0x801175ac")
set(TPGZ_CFG_SET_WATER_DROP_EFFECT3 "0x801175bc")
set(TPGZ_CFG_WATER_DROP_COLOR "0x800c38bc")
set(TPGZ_CFG_DEBUG "0x80011f90")
set(TPGZ_CFG_DEBUG_INSTRUCTION "0x48000190")

# TOML values
set(TPGZ_CFG_SRC_ISO "../isos/RZDE01.iso")
set(TPGZ_CFG_SRC_MAP "map/Rfinal/Release/RframeworkF.map")
set(TPGZ_CFG_BLD_ISO "tpgz.iso")
set(TPGZ_CFG_BLD_MAP "RZDE01.map")
set(TPGZ_CFG_LINK_BASE "0x8056_0000")
set(TPGZ_CFG_SAVE_ANY_PATH "res/save_files_wii")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/patch.asm.in ${CMAKE_CURRENT_BINARY_DIR}/patch.asm)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/RomHack.toml.in ${CMAKE_CURRENT_BINARY_DIR}/RomHack.toml)