#include "save_injector.h"
#include "fs.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menu.h"

namespace SaveInjector {

// inject qlog bytes into RAM
void inject_save(void* buffer) {
    tp_memcpy((void*)&tp_gameInfo, buffer, 2392);
    tp_getSave(&tp_gameInfo, tp_gameInfo.area_id);
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
}

void inject_default_after() {}
}  // namespace SaveInjector