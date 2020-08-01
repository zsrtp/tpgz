#include "save_injector.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "log.h"
#include "utils.h"
#include "menu.h"
#include <string.h>
#include "fs.h"

namespace SaveInjector {

    static Log log;

    // inject qlog bytes into RAM
    void inject_save() {
        // copy out scratchpad
        memcpy((void*)&tp_gameInfo, (void*)practice_file.qlog_bytes, 2392);
    };

    void inject_default_before() {
        tp_putSave(&tp_gameInfo,tp_gameInfo.area_id);
        inject_save();
        tp_getSave(&tp_gameInfo,tp_gameInfo.area_id);
        tp_gameInfo.spawn_speed = 0.0f;
        tp_gameInfo.loading_animation = 13; // instant load
        tp_gameInfo.respawn_animation = 0;
        tp_gameInfo.warp.entrance.void_flag = 0;
    }

    void no_op() { }

    void inject_default_during() {

        int spawn = practice_file.qlog_bytes[SPAWN_INDEX];
        int room = practice_file.qlog_bytes[ROOM_INDEX];
        char stage[8];
        log.PrintLog("Copying stage to load from practice file obj", DEBUG);
        for (int i = 0; i < 8; i++) {
            stage[i] = practice_file.qlog_bytes[STAGE_INDEX + i];
        }
        int state = tp_getLayerNo(stage, room, 0xFF);
        log.PrintLog("Setting spawn to: %d", spawn, DEBUG);
        tp_gameInfo.warp.entrance.spawn = spawn;
        log.PrintLog("Setting room to: %d", room, DEBUG);
        tp_gameInfo.warp.entrance.room = room;
        log.PrintLog("Setting stage to: %s", stage, DEBUG);
        strcpy((char*)tp_gameInfo.warp.entrance.stage, stage);
        log.PrintLog("Setting state to: %d", state, DEBUG);
        tp_gameInfo.warp.entrance.state = state;
        
        // fixes some bug causing link to auto drown, figure out later
        tp_gameInfo.link_air_meter = 600;
        tp_gameInfo.link_air_meter_2 = 600;
        tp_gameInfo.link_max_air_meter = 600;
    }

    void inject_default_after() {

    }
}  // namespace SaveInjector