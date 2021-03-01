#include "save_injector.h"
#include "fs.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/settings_menu.h"
#include "menu.h"

namespace SaveInjector {

// inject qlog bytes into RAM
void inject_save(void* buffer) {
    tp_memcpy((void*)&tp_gameInfo, buffer, 2392);
    tp_getSave(&tp_gameInfo, tp_gameInfo.dungeon_temp_flags.mStageNum);
};

void inject_memfile(void* buffer) {
    tp_memcpy((void*)&tp_gameInfo, buffer, 3818);
    tp_getSave(&tp_gameInfo, tp_gameInfo.dungeon_temp_flags.mStageNum);
};

void inject_default_before() {
    tp_gameInfo.spawn_speed = 0.0f;
    tp_gameInfo.loading_animation = 13;  // instant load
    tp_gameInfo.respawn_animation = 0;
    tp_gameInfo.warp.entrance.void_flag = 0;
}

void inject_default_during() {
    int state = tp_getLayerNo((char*)tp_gameInfo.player.player_stage,
                              tp_gameInfo.player.player_room_id, 0xFF);
    tp_gameInfo.warp.entrance.spawn = tp_gameInfo.player.player_spawn_id;
    tp_gameInfo.special_spawn_id = tp_gameInfo.player.player_spawn_id;
    tp_gameInfo.warp.entrance.room = tp_gameInfo.player.player_room_id;
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

void inject_default_after() {}
}  // namespace SaveInjector