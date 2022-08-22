#include <cstdio>
#include "fs.h"
#include "libtp_c/include/dolphin/os/OSCache.h"
#include "settings.h"
#include "gz_flags.h"
#include "practice.h"
#include "menus/memfiles_menu.h"
#include "save_manager.h"
#include "menu.h"
#include "utils/loading.h"
#include "fifo_queue.h"
#include "utils/card.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "menus/utils/menu_mgr.h"

int apply_after_counter = 0;
int apply_during_counter = 0;
int injection_counter = 0;
char currentFileName[80];
SaveManager gSaveManager;

void SaveManager::injectSave(void* buffer) {
    memcpy((void*)&g_dComIfG_gameInfo, buffer, 2392);
    dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
};

void SaveManager::injectMemfile(void* buffer) {
    memcpy((void*)&g_dComIfG_gameInfo, buffer, sizeof(dSv_info_c));
    dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
};

void SaveManager::injectDefault_before() {
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 0.0f;
    g_dComIfG_gameInfo.play.mNextStage.wipe = 13;  // instant load
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0;
    g_dComIfG_gameInfo.play.mNextStage.mPoint = 0;
}

void SaveManager::injectDefault_during() {
    // Load the save file over game info
    if (!g_injectMemfile) {
        SaveManager::loadSavefile(currentFileName);
    } else {
        SaveManager::injectMemfile(MEMFILE_BUF);
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
    strcpy((char*)g_dComIfG_gameInfo.play.mNextStage.mStage,
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

        dComIfGs_setSelectItemIndex(SELECT_ITEM_LEFT,
                                    dComIfGs_getSelectItemIndex(SELECT_ITEM_RIGHT));
        dComIfGs_setSelectItemIndex(SELECT_ITEM_RIGHT, tmp);
        dComIfGs_setMixItemIndex(SELECT_ITEM_LEFT, dComIfGs_getMixItemIndex(SELECT_ITEM_RIGHT));
        dComIfGs_setMixItemIndex(SELECT_ITEM_RIGHT, tmp_mix);
    }
#endif
}

void SaveManager::injectDefault_after() {}

void SaveManager::defaultLoad() {
    gSaveManager.mPracticeFileOpts.inject_options_during_load = SaveManager::injectDefault_during;
    gSaveManager.mPracticeFileOpts.inject_options_after_load = SaveManager::injectDefault_after;
    g_injectSave = true;
    g_fifoVisible = true;
    g_menuMgr->hide();
}

void SaveManager::loadSave(uint32_t id, const char* category, special i_specials[], int size) {
    SaveManager::injectDefault_before();

    // Load the corresponding file path and properties
    snprintf(currentFileName, sizeof(currentFileName), "tpgz/save_files/%s.bin", category);
    loadFile(currentFileName, &gSaveManager.mPracticeSaveInfo,
             sizeof(gSaveManager.mPracticeSaveInfo), id * sizeof(gSaveManager.mPracticeSaveInfo));
    snprintf(currentFileName, sizeof(currentFileName), "tpgz/save_files/%s/%s.bin", category,
            gSaveManager.mPracticeSaveInfo.filename);

    // 0xFF is used to identify a call from file reload, which doesn't need to run the default load
    if (size != 0xFF) {
        SaveManager::defaultLoad();
    } else {
        size = last_special_size;
    }

    if (gSaveManager.mPracticeSaveInfo.requirements) {
        gSaveManager.mPracticeFileOpts.inject_options_after_load =
            gSaveManager.mPracticeSaveInfo.requirements & REQ_CAM ? setPositionCamera : setLinkInfo;
        gSaveManager.mPracticeFileOpts.inject_options_after_counter =
            gSaveManager.mPracticeSaveInfo.counter;
    }

    bossFlags = 0;

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
    strncpy(last_category, category, sizeof(last_category));
    last_special_ptr = i_specials;
    last_special_size = size;
}

void SaveManager::loadSavefile(const char* fileName) {
    loadFile(fileName, MEMFILE_BUF, 2400, 0);
    SaveManager::injectSave(MEMFILE_BUF);
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

void SaveManager::triggerLoad() {
    // Loading hasn't started yet, run the before load function and initiate loading
    if (!fopScnRq.isLoading && !gSaveManager.loading_initiated) {
        // Patch out setWaterDropColor call temporarily (prevents a crash in some scenarios)
        setWaterDropColorInstr = *reinterpret_cast<uint32_t*>(SET_WATER_DROP_COLOR_BL);
        *reinterpret_cast<uint32_t*>(SET_WATER_DROP_COLOR_BL) = 0x60000000;  // nop
        DCFlushRange((void*)(SET_WATER_DROP_COLOR_BL), sizeof(uint32_t));
        ICInvalidateRange((void*)(SET_WATER_DROP_COLOR_BL), sizeof(uint32_t));

        // Trigger loading
        g_dComIfG_gameInfo.play.mNextStage.enabled = true;
    }

    // Loading has started, run the during load function
    if (fopScnRq.isLoading && g_dComIfG_gameInfo.play.mNextStage.enabled) {
        if (gSaveManager.mPracticeFileOpts.inject_options_during_load) {
            gSaveManager.mPracticeFileOpts.inject_options_during_load();
        }
        gSaveManager.loading_initiated = true;
        g_dComIfG_gameInfo.play.mNextStage.enabled = false;
    }

    if (gSaveManager.loading_initiated) {
        // Loading has completed, run the after load function
        if (!fopScnRq.isLoading) {
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

                g_injectSave = false;
                g_injectMemfile = false;
            } else {
                apply_after_counter++;
            }
        }
        // should clean this up eventually
        if (fopScnRq.isLoading && gSaveManager.repeat_during &&
            gSaveManager.repeat_count != apply_during_counter) {
            if (gSaveManager.mPracticeFileOpts.inject_options_after_load) {
                gSaveManager.mPracticeFileOpts.inject_options_after_load();
            }
            apply_during_counter++;
        } else {
            apply_during_counter = 0;
            gSaveManager.repeat_during = false;
            gSaveManager.repeat_count = 0;
        }
    }
}

void SaveManager::setLinkInfo() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->mCollisionRot.mY = gSaveManager.mPracticeSaveInfo.angle;
        cXyz tmp(gSaveManager.mPracticeSaveInfo.position.x,
                 gSaveManager.mPracticeSaveInfo.position.y,
                 gSaveManager.mPracticeSaveInfo.position.z);
        dComIfGp_getPlayer()->mCurrent.mPosition = tmp;
    }
}

void SaveManager::setPositionCamera() {
    if (matrixInfo.matrix_info) {
        matrixInfo.matrix_info->target = gSaveManager.mPracticeSaveInfo.cam_target;
        matrixInfo.matrix_info->pos = gSaveManager.mPracticeSaveInfo.cam_pos;
    }

    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->mCollisionRot.mY = gSaveManager.mPracticeSaveInfo.angle;
        cXyz tmp(gSaveManager.mPracticeSaveInfo.position.x,
                 gSaveManager.mPracticeSaveInfo.position.y,
                 gSaveManager.mPracticeSaveInfo.position.z);
        dComIfGp_getPlayer()->mCurrent.mPosition = tmp;
    }
}