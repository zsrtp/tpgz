# ASM values
set(TPGZ_CFG_ARENALO "0x8032f7dc")
set(TPGZ_CFG_ARENALO_VAL "0x3c608056")
set(TPGZ_CFG_MAIN "0x80008d04")
set(TPGZ_CFG_MAIN_TRAMPOLINE "0x803b929c")
set(TPGZ_CFG_FIRST_INSTRUCTION "0x542b06fe")
set(TPGZ_CFG_RETURN_TO_MAIN "0x4BC4FA68")
set(TPGZ_CFG_SET_WATER_DROP_EFFECT1 "0x80117c50")
set(TPGZ_CFG_SET_WATER_DROP_EFFECT2 "0x80117c60")
set(TPGZ_CFG_SET_WATER_DROP_EFFECT3 "0x80117c70")
set(TPGZ_CFG_WATER_DROP_COLOR "0x800c3dd4")
set(TPGZ_CFG_DEBUG "0x80012084")
set(TPGZ_CFG_DEBUG_INSTRUCTION "0x48000190")

# TOML values
set(TPGZ_CFG_SRC_ISO "../isos/RZDP01.iso")
set(TPGZ_CFG_SRC_MAP "map/Rfinal/Release/RframeworkF.map")
set(TPGZ_CFG_BLD_ISO "tpgzw.iso")
set(TPGZ_CFG_BLD_MAP "RZDP01.map")
set(TPGZ_CFG_LINK_BASE "0x8053_8000")
set(TPGZ_CFG_SAVE_ANY_PATH "res/save_files_wii")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/patch.asm.in ${CMAKE_CURRENT_BINARY_DIR}/patch.asm)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/RomHack.toml.in ${CMAKE_CURRENT_BINARY_DIR}/RomHack.toml)