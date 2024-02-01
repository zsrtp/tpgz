#include <cstdio>
#include "fs.h"
#include "libtp_c/include/dolphin/os/OSCache.h"
#include "settings.h"
#include "gz_flags.h"
#include "practice.h"
#include "memfiles.h"
#include "save_manager.h"
#include "menu.h"
#include "utils/loading.h"
#include "fifo_queue.h"
#include "utils/card.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "menus/utils/menu_mgr.h"

static char l_filename[80];
SaveManager gSaveManager;

KEEP_VAR bool SaveManager::s_injectSave = false;
KEEP_VAR bool SaveManager::s_injectMemfile = false;
KEEP_VAR s8 SaveManager::s_applyAfterTimer = -1;

void SaveManager::injectSave(void* buffer) {
    memcpy(&g_dComIfG_gameInfo, buffer, 0x9F8);
    dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
}

void SaveManager::injectMemfile(void* buffer) {
    memcpy(&g_dComIfG_gameInfo, buffer, sizeof(dSv_info_c));
    dComIfGs_getSave(g_dComIfG_gameInfo.info.mDan.mStageNo);
}

void SaveManager::injectDefault_before() {
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 0.0f;
    g_dComIfG_gameInfo.play.mNextStage.wipe = 13;  // instant load
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0;
}

void SaveManager::injectDefault_during() {}

void SaveManager::injectDefault_after() {}

void SaveManager::defaultLoad() {
    gSaveManager.mPracticeFileOpts.inject_options_during_load = SaveManager::injectDefault_during;
    gSaveManager.mPracticeFileOpts.inject_options_after_load = SaveManager::injectDefault_after;
    g_fifoVisible = true;
    g_menuMgr->hide();
}

void SaveManager::loadSave(uint32_t id, const char* category, special i_specials[], int size) {
    SaveManager::injectDefault_before();

    // Load the corresponding file path and properties
    snprintf(l_filename, sizeof(l_filename), "tpgz/save_files/%s.bin", category);
    loadFile(l_filename, &gSaveManager.mPracticeSaveInfo, sizeof(gSaveManager.mPracticeSaveInfo),
             id * sizeof(gSaveManager.mPracticeSaveInfo));
    snprintf(l_filename, sizeof(l_filename), "tpgz/save_files/%s/%s.bin", category,
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
                break;
            }
        }
    }

    // Store all the info in case file reload is used
    last_save_index = id;
    strncpy(last_category, category, sizeof(last_category));
    last_special_ptr = i_specials;
    last_special_size = size;
}

void SaveManager::loadSavefile(const char* l_filename) {
    loadFile(l_filename, MEMFILE_BUF, 2400, 0);
}

KEEP_FUNC void SaveManager::triggerLoad(uint32_t id, const char* category, special i_specials[],
                                        int size) {
    loadSave(id, category, i_specials, size);
 
    SaveManager::loadSavefile(l_filename);
    dSv_save_c* save = (dSv_save_c*)MEMFILE_BUF;

    int state = tp_getLayerNo(save->getPlayer().mPlayerReturnPlace.mName,
                              save->getPlayer().mPlayerReturnPlace.mRoomNo, 0xFF);

    g_dComIfG_gameInfo.info.mRestart.mStartPoint =
        save->getPlayer().mPlayerReturnPlace.mPlayerStatus;
    g_dComIfG_gameInfo.play.mNextStage.mRoomNo = save->getPlayer().mPlayerReturnPlace.mRoomNo;
    g_dComIfG_gameInfo.play.mNextStage.mPoint = save->getPlayer().mPlayerReturnPlace.mPlayerStatus;
    strcpy(g_dComIfG_gameInfo.play.mNextStage.mStage, save->getPlayer().mPlayerReturnPlace.mName);
    g_dComIfG_gameInfo.play.mNextStage.mLayer = state;

    // inject options after initial stage set since some options change stage loc
    if (gSaveManager.mPracticeFileOpts.inject_options_during_load) {
        gSaveManager.mPracticeFileOpts.inject_options_during_load();
    }

    g_dComIfG_gameInfo.play.mNextStage.enabled = true;
    s_injectSave = true;
}

KEEP_FUNC void SaveManager::triggerMemfileLoad() {
    // GZ_readMemfile already puts the savedata in g_tmpBuf
    dSv_save_c* save = (dSv_save_c*)MEMFILE_BUF;

    int state = tp_getLayerNo(save->getPlayer().mPlayerReturnPlace.mName,
                              save->getPlayer().mPlayerReturnPlace.mRoomNo, 0xFF);

    g_dComIfG_gameInfo.info.mRestart.mStartPoint =
        save->getPlayer().mPlayerReturnPlace.mPlayerStatus;
    g_dComIfG_gameInfo.play.mNextStage.mRoomNo = save->getPlayer().mPlayerReturnPlace.mRoomNo;
    g_dComIfG_gameInfo.play.mNextStage.mPoint = save->getPlayer().mPlayerReturnPlace.mPlayerStatus;
    strcpy(g_dComIfG_gameInfo.play.mNextStage.mStage, save->getPlayer().mPlayerReturnPlace.mName);
    g_dComIfG_gameInfo.play.mNextStage.mLayer = state;

    gSaveManager.mPracticeFileOpts.inject_options_after_load = GZ_setLinkPosition;

    g_dComIfG_gameInfo.play.mNextStage.enabled = true;
    s_injectMemfile = true;
}

// runs at the beginning of phase_1 of dScnPly_c load sequence
KEEP_FUNC void SaveManager::loadData() {
    if (s_injectMemfile) {
        SaveManager::injectMemfile(MEMFILE_BUF);
    } else {
        SaveManager::injectSave(MEMFILE_BUF);
    }

// swap equip logic
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

void SaveManager::setLinkInfo() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->shape_angle.y = gSaveManager.mPracticeSaveInfo.angle;
        cXyz tmp(gSaveManager.mPracticeSaveInfo.position.x,
                 gSaveManager.mPracticeSaveInfo.position.y,
                 gSaveManager.mPracticeSaveInfo.position.z);
        dComIfGp_getPlayer()->current.pos = tmp;
    }
}

void SaveManager::setPositionCamera() {
    if (matrixInfo.matrix_info) {
        matrixInfo.matrix_info->target = gSaveManager.mPracticeSaveInfo.cam_target;
        matrixInfo.matrix_info->pos = gSaveManager.mPracticeSaveInfo.cam_pos;
    }

    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->shape_angle.y = gSaveManager.mPracticeSaveInfo.angle;
        cXyz tmp(gSaveManager.mPracticeSaveInfo.position.x,
                 gSaveManager.mPracticeSaveInfo.position.y,
                 gSaveManager.mPracticeSaveInfo.position.z);
        dComIfGp_getPlayer()->current.pos = tmp;
    }
}