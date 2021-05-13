
#include "fs.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/gc/OSCache.h"
#include "menus/settings_menu.h"
#include "menus/practice_menu.h"
#include "save_manager.h"
#include "menu.h"
#include "utils/loading.h"
#include "fifo_queue.h"

int apply_after_counter = 0;
int injection_counter = 0;
char currentFileName[80];
SaveManager gSaveManager;

void SaveManager::inject_save(void* buffer) {
    tp_memcpy((void*)&tp_gameInfo, buffer, 2392);
    tp_getSave(&tp_gameInfo, tp_gameInfo.dungeon_temp_flags.mStageNum);
};

void SaveManager::inject_memfile(void* buffer) {
    tp_memcpy((void*)&tp_gameInfo, buffer, 3818);
    tp_getSave(&tp_gameInfo, tp_gameInfo.dungeon_temp_flags.mStageNum);
};

void SaveManager::inject_default_before() {
    tp_gameInfo.spawn_speed = 0.0f;
    tp_gameInfo.loading_animation = 13;  // instant load
    tp_gameInfo.respawn_animation = 0;
    tp_gameInfo.warp.entrance.void_flag = 0;
}

void SaveManager::inject_default_during() {
    // Load the save file over game info
    SaveManager::load_save_file(currentFileName);

    // Get default state based on file info
    int state = tp_getLayerNo((char*)tp_gameInfo.player.player_stage,
                              tp_gameInfo.player.player_room_id, 0xFF);

    // Next stage info
    tp_gameInfo.special_spawn_id = tp_gameInfo.player.player_spawn_id;
    tp_gameInfo.warp.entrance.room = tp_gameInfo.player.player_room_id;
    tp_gameInfo.warp.entrance.spawn = tp_gameInfo.player.player_spawn_id;
    tp_strcpy((char*)tp_gameInfo.warp.entrance.stage, (char*)tp_gameInfo.player.player_stage);
    tp_gameInfo.warp.entrance.state = state;

    // fixes some bug causing link to auto drown, figure out later
    tp_gameInfo.link_air_meter = 600;
    tp_gameInfo.link_air_meter_2 = 600;
    tp_gameInfo.link_max_air_meter = 600;

#ifdef GCN_PLATFORM
    if (g_swap_equips_flag) {
        uint8_t tmp = tp_gameInfo.link.item_on_x;
        uint8_t tmp_mix = tp_gameInfo.link.slot_x_combo_item;

        tp_gameInfo.link.item_on_x = tp_gameInfo.link.item_on_y;
        tp_gameInfo.link.item_on_y = tmp;
        tp_gameInfo.link.slot_x_combo_item = tp_gameInfo.link.slot_y_combo_item;
        tp_gameInfo.link.slot_y_combo_item = tmp_mix;
    }
#endif
    // add wii swap equip logic here later
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
    loadFile(currentFileName, &gSaveManager.mPracticeSaveInfo, sizeof(gSaveManager.mPracticeSaveInfo),
             id * sizeof(gSaveManager.mPracticeSaveInfo));
    tp_sprintf(currentFileName, "tpgz/save_files/%s/%s.bin", category, gSaveManager.mPracticeSaveInfo.filename);

    // 0xFF is used to identify a call from file reload, which doesn't need to run the default load
    if (size != 0xFF) {
        SaveManager::default_load();
    } else {
        size = last_special_size;
    }

    if (gSaveManager.mPracticeSaveInfo.requirements) {
        gSaveManager.mPracticeFileOpts.inject_options_after_load = gSaveManager.mPracticeSaveInfo.requirements & REQ_CAM ?
                                                          Utilities::set_camera_angle_position :
                                                          Utilities::set_angle_position;
        gSaveManager.mPracticeFileOpts.inject_options_after_counter = gSaveManager.mPracticeSaveInfo.counter;
    }

    tp_bossFlags = 0;

    // If the selected file was a special, run the special callbacks
    if (i_specials) {
        for (int i = 0; i < size; ++i) {
            if (id == i_specials[i].idx) {
                if (i_specials[i].CallbackDuring) {
                    gSaveManager.mPracticeFileOpts.inject_options_during_load = i_specials[i].CallbackDuring;
                }
                if (i_specials[i].CallbackAfter) {
                    gSaveManager.mPracticeFileOpts.inject_options_after_load = i_specials[i].CallbackAfter;
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

void SaveManager::trigger_load() {
    // Loading hasn't started yet, run the before load function and initiate loading
    if (!tp_fopScnRq.isLoading && !gSaveManager.loading_initiated) {
        // Patch out setWaterDropColor call temporarily (prevents a crash in some scenarios)
        *reinterpret_cast<uint32_t*>(0x800CCE08) = 0x60000000;  // nop
        gc::os_cache::DCFlushRange((void*)(0x800CCE08), sizeof(uint32_t));
        gc::os_cache::ICInvalidateRange((void*)(0x800CCE08), sizeof(uint32_t));

        // Trigger loading
        tp_gameInfo.warp.enabled = true;
    }

    // Loading has started, run the during load function
    if (tp_fopScnRq.isLoading && tp_gameInfo.warp.enabled) {
        if (gSaveManager.mPracticeFileOpts.inject_options_during_load) {
            gSaveManager.mPracticeFileOpts.inject_options_during_load();
        }
        gSaveManager.loading_initiated = true;
        tp_gameInfo.warp.enabled = false;
    }

    if (gSaveManager.loading_initiated) {
        // Loading has completed, run the after load function
        if (!tp_fopScnRq.isLoading) {
            // Patch back in setWaterDropColor call
            *reinterpret_cast<uint32_t*>(0x800CCE08) =
                0x4BFFF55D;  // bl daAlink_c::setWaterDropColor
            gc::os_cache::DCFlushRange((void*)(0x800CCE08), sizeof(uint32_t));
            gc::os_cache::ICInvalidateRange((void*)(0x800CCE08), sizeof(uint32_t));

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
            } else {
                apply_after_counter++;
            }
        }
    }
}