#include "save_injector.h"
#include "libtp_c/include/tp.h"
#include "log.h"
#include <string.h>

static bool loading_initiated = false;
bool execute_injection_loading_prep = false;

namespace SaveInjector {
    uint8_t* get_qlog_bytes(){

    };

    // fetches current temp flags from RAM into practice file object
    void get_temp_flags(PracticeFile& practice_file) {
        memcpy(&practice_file.temp_flags, &tp_gameInfo.temp_flags, 40);
    };

    // sets arbitrary flags to practice file object
    void set_temp_flags(PracticeFile& practice_file, uint8_t temp_flags[40]) {
        memcpy(&practice_file.temp_flags, &temp_flags, 40);
    };

    // inject qlog bytes into RAM
    void inject_save(PracticeFile practice_file) {
        //change to gameinfo later
        memcpy((void*)0x804061C0, (void*)practice_file.qlog_bytes, 2700);
    };

    // inject temp flags into RAM
    void inject_temp_flags(PracticeFile& practice_file) {
        memcpy(&tp_gameInfo.temp_flags, &practice_file.temp_flags, 40);
    }

    // inject position into RAM
    void inject_position(PracticeFile& practice_file) {
        tp_zelAudio.link_debug_ptr->position = practice_file.position;
    }

    // load area based on qlog
    void load_area(PracticeFile& practice_file) {
        if (execute_injection_loading_prep) {
            Log log;
            // fetch area info from practice file object
            int spawn = practice_file.qlog_bytes[SPAWN_INDEX];
            int room = practice_file.qlog_bytes[ROOM_INDEX];
            char stage[8];
            log.PrintLog("Copying stage to load from practice file obj",DEBUG);
            memcpy(&stage, &practice_file.qlog_bytes[STAGE_INDEX], 8);

            // set next area loading info
            // tp_gameInfo.warp.entrance.void_flag = 0;
            // tp_gameInfo.event_to_play = 0;
            // tp_gameInfo.respawn_animation = 0;
            log.PrintLog("Setting spawn to: %d", spawn, DEBUG);
            tp_gameInfo.warp.entrance.spawn = spawn;
            log.PrintLog("Setting room to: %d", room, DEBUG);
            tp_gameInfo.warp.entrance.room = room;
            log.PrintLog("Setting stage to: %s", stage, DEBUG);
            strcpy((char*)tp_gameInfo.warp.entrance.stage, stage);

            // trigger loading
            log.PrintLog("Initiating warp",INFO);
            tp_gameInfo.warp.enabled = true;

            if (tp_fopScnRq.isLoading == 1) {
                loading_initiated = true;
            }
            if (loading_initiated == true) {
                // fire once load finishes
                if (tp_fopScnRq.isLoading == 0) {
                    // store temp flags as soon as loading is done
                    log.PrintLog("Saving temp flags to RAM",DEBUG);
                    SaveInjector::get_temp_flags(practice_file);
                    execute_injection_loading_prep = false;
                }
            }
        }
    }
}  // namespace SaveInjector