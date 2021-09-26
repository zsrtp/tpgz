
#include "fs.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/dolphin/os/OSCache.h"
#include "menus/settings_menu.h"
#include "menus/practice_menu.h"
#include "save_manager.h"
#include "menu.h"
#include "utils/loading.h"
#include "fifo_queue.h"
#include "utils/card.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"

int apply_after_counter = 0;
int injection_counter = 0;
char currentFileName[80];
SaveManager gSaveManager;

void SaveManager::inject_save(void* buffer) {
    tp_memcpy((void*)&g_dComIfG_gameInfo, buffer, 2392);
    dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
};

void SaveManager::inject_memfile(void* buffer) {
    tp_memcpy((void*)&g_dComIfG_gameInfo, buffer, sizeof(dSv_info_c));
    dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
};

void SaveManager::inject_default_before() {
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 0.0f;
    g_dComIfG_gameInfo.play.mNextStage.wipe = 13;  // instant load
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0;
    g_dComIfG_gameInfo.play.mNextStage.mPoint = 0;
}

void SaveManager::inject_default_during() {
    // Load the save file over game info
    if (!inject_memfile_flag) {
        SaveManager::load_save_file(currentFileName);
    } else {
        SaveManager::inject_memfile((void*)sTmpBuf);
    }

    // Get default state based on file info
    int state = tp_getLayerNo((char*)g_dComIfG_gameInfo.info.getPlayer().mPlayerReturnPlace.mName,
                              g_dComIfG_gameInfo.info.getPlayer().mPlayerReturnPlace.mRoomNo, 0xFF);

    // Next stage info
    g_dComIfG_gameInfo.info.mRestart.mStartPoint =
        g_dComIfG_gameInfo.info.getPlayer().mPlayerReturnPlace.mPlayerStatus;
    g_dComIfG_gameInfo.play.mNextStage.mRoomNo =
        g_dComIfG_gameInfo.info.getPlayer().mPlayerReturnPlace.mRoomNo;
    g_dComIfG_gameInfo.play.mNextStage.mPoint =
        g_dComIfG_gameInfo.info.getPlayer().mPlayerReturnPlace.mPlayerStatus;
    tp_strcpy((char*)g_dComIfG_gameInfo.play.mNextStage.mStage,
              (char*)g_dComIfG_gameInfo.info.getPlayer().mPlayerReturnPlace.mName);
    g_dComIfG_gameInfo.play.mNextStage.mLayer = state;

    // fixes some bug causing link to auto drown, figure out later
    dComIfGs_setOxygen(600);
    dComIfGs_setNowOxygen(600);
    dComIfGs_setMaxOxygen(600);

#ifdef GCN_PLATFORM
    if (g_swap_equips_flag) {
        uint8_t tmp = dComIfGs_getSelectItemIndex(SELECT_ITEM_X);
        uint8_t tmp_mix = dComIfGs_getMixItemIndex(SELECT_ITEM_X);

        dComIfGs_setSelectItemIndex(SELECT_ITEM_X, dComIfGs_getSelectItemIndex(SELECT_ITEM_Y));
        dComIfGs_setSelectItemIndex(SELECT_ITEM_Y, tmp);
        dComIfGs_setMixItemIndex(SELECT_ITEM_X, dComIfGs_getMixItemIndex(SELECT_ITEM_Y));
        dComIfGs_setMixItemIndex(SELECT_ITEM_Y, tmp_mix);
    }
#endif
    // add wii swap equip logic here later
#ifdef WII_PLATFORM
    if (g_swap_equips_flag) {
        uint8_t tmp = dComIfGs_getSelectItemIndex(SELECT_ITEM_LEFT);
        uint8_t tmp_mix = dComIfGs_getMixItemIndex(SELECT_ITEM_LEFT);

        dComIfGs_setSelectItemIndex(SELECT_ITEM_LEFT, dComIfGs_getSelectItemIndex(SELECT_ITEM_RIGHT));
        dComIfGs_setSelectItemIndex(SELECT_ITEM_RIGHT, tmp);
        dComIfGs_setMixItemIndex(SELECT_ITEM_LEFT, dComIfGs_getMixItemIndex(SELECT_ITEM_RIGHT));
        dComIfGs_setMixItemIndex(SELECT_ITEM_RIGHT, tmp_mix);
    }
#endif
}

void SaveManager::inject_default_after() {}

void SaveManager::default_load() {
    gSaveManager.mPracticeFileOpts.inject_options_during_load = SaveManager::inject_default_during;
    gSaveManager.mPracticeFileOpts.inject_options_after_load = SaveManager::inject_default_after;
    inject_save_flag = true;
    fifo_visible = true;
    MenuRendering::set_menu(MN_NONE_INDEX);
}

void SaveManager::load_save(uint32_t id, char* category, special i_specials[], int size) {
    SaveManager::inject_default_before();

    // Load the corresponding file path and properties
    tp_sprintf(currentFileName, "tpgz/save_files/%s.bin", category);
    loadFile(currentFileName, &gSaveManager.mPracticeSaveInfo,
             sizeof(gSaveManager.mPracticeSaveInfo), id * sizeof(gSaveManager.mPracticeSaveInfo));
    tp_sprintf(currentFileName, "tpgz/save_files/%s/%s.bin", category,
               gSaveManager.mPracticeSaveInfo.filename);

    // 0xFF is used to identify a call from file reload, which doesn't need to run the default load
    if (size != 0xFF) {
        SaveManager::default_load();
    } else {
        size = last_special_size;
    }

    if (gSaveManager.mPracticeSaveInfo.requirements) {
        gSaveManager.mPracticeFileOpts.inject_options_after_load =
            gSaveManager.mPracticeSaveInfo.requirements & REQ_CAM ?
                Utilities::set_camera_angle_position :
                Utilities::set_angle_position;
        gSaveManager.mPracticeFileOpts.inject_options_after_counter =
            gSaveManager.mPracticeSaveInfo.counter;
    }

    tp_bossFlags = 0;

    // If the selected file was a special, run the special callbacks
    if (i_specials) {
        for (int i = 0; i < size; ++i) {
            if (id == i_specials[i].idx) {
                if (i_specials[i].CallbackDuring) {
                    gSaveManager.mPracticeFileOpts.inject_options_during_load =
                        i_specials[i].CallbackDuring;
                }
                if (i_specials[i].CallbackAfter) {
                    gSaveManager.mPracticeFileOpts.inject_options_after_load =
                        i_specials[i].CallbackAfter;
                }
            }
        }
    }

    // Store all the info in case file reload is used
    last_save_index = id;
    tp_strcpy(last_category, category);
    last_special_ptr = i_specials;
    last_special_size = size;
}

void SaveManager::load_save_file(const char* fileName) {
    loadFile(fileName, (void*)sTmpBuf, 2400, 0);
    SaveManager::inject_save((void*)sTmpBuf);
}

#if (GCN_NTSCU)
#define SET_WATER_DROP_COLOR_BL ((uint32_t*)0x800CCE08)
#endif
#if (GCN_PAL)
#define SET_WATER_DROP_COLOR_BL ((uint32_t*)0x800CD014)
#endif
#if (GCN_NTSCJ)
#define SET_WATER_DROP_COLOR_BL ((uint32_t*)0x800CCE40)
#endif
#if (WII_NTSCU_10)
#define SET_WATER_DROP_COLOR_BL ((uint32_t*)0x800C38BC)
#endif
#if (WII_PAL)
#define SET_WATER_DROP_COLOR_BL ((uint32_t*)0x800C3DD4)
#endif

uint32_t setWaterDropColorInstr = 0x60000000;

void SaveManager::trigger_load() {
    // Loading hasn't started yet, run the before load function and initiate loading
    if (!tp_fopScnRq.isLoading && !gSaveManager.loading_initiated) {
        // Patch out setWaterDropColor call temporarily (prevents a crash in some scenarios)
        setWaterDropColorInstr = *reinterpret_cast<uint32_t*>(SET_WATER_DROP_COLOR_BL);
        *reinterpret_cast<uint32_t*>(SET_WATER_DROP_COLOR_BL) = 0x60000000;  // nop
        DCFlushRange((void*)(SET_WATER_DROP_COLOR_BL), sizeof(uint32_t));
        ICInvalidateRange((void*)(SET_WATER_DROP_COLOR_BL), sizeof(uint32_t));

        // Trigger loading
        g_dComIfG_gameInfo.play.mNextStage.enabled = true;
    }

    // Loading has started, run the during load function
    if (tp_fopScnRq.isLoading && g_dComIfG_gameInfo.play.mNextStage.enabled) {
        if (gSaveManager.mPracticeFileOpts.inject_options_during_load) {
            gSaveManager.mPracticeFileOpts.inject_options_during_load();
        }
        gSaveManager.loading_initiated = true;
        g_dComIfG_gameInfo.play.mNextStage.enabled = false;
    }

    if (gSaveManager.loading_initiated) {
        // Loading has completed, run the after load function
        if (!tp_fopScnRq.isLoading) {
            // Patch back in setWaterDropColor call
            *reinterpret_cast<uint32_t*>(SET_WATER_DROP_COLOR_BL) =
                setWaterDropColorInstr;  // bl daAlink_c::setWaterDropColor
            DCFlushRange((void*)(SET_WATER_DROP_COLOR_BL), sizeof(uint32_t));
            ICInvalidateRange((void*)(SET_WATER_DROP_COLOR_BL), sizeof(uint32_t));

            if (gSaveManager.mPracticeFileOpts.inject_options_after_load) {
                gSaveManager.mPracticeFileOpts.inject_options_after_load();
            }

            if (gSaveManager.mPracticeFileOpts.inject_options_after_counter ==
                apply_after_counter) {
                apply_after_counter = 0;
                gSaveManager.mPracticeFileOpts.inject_options_after_load = nullptr;
                gSaveManager.mPracticeFileOpts.inject_options_after_counter = 0;
                gSaveManager.loading_initiated = false;

                inject_save_flag = false;
                inject_memfile_flag = false;
            } else {
                apply_after_counter++;
            }
        }
    }
}

void SaveManager::setLinkInfo() {
    dComIfGp_getPlayer()->mCollisionRot.mY = gSaveManager.mPracticeSaveInfo.angle;
    cXyz tmp(gSaveManager.mPracticeSaveInfo.position.x, gSaveManager.mPracticeSaveInfo.position.y,
             gSaveManager.mPracticeSaveInfo.position.z);
    dComIfGp_getPlayer()->mCurrent.mPosition = tmp;
}