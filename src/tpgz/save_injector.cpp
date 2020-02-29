#include "tpgz/save_injector.h"
#include "libtp_c/include/tp.h"
#include "tpgz/log.h"
#include "tpgz/utils.h"
#include "menus/menu.h"
#include <string.h>

bool inject_save_flag = false;

namespace SaveInjector {
    // uint8_t* get_qlog_bytes(){

    // };

    // fetches current temp flags from RAM into practice file object
    void get_temp_flags(PracticeFile& practice_file) {
        memcpy(&practice_file.temp_flags, &tp_gameInfo.temp_flags, 40);
    };

    // sets arbitrary flags to practice file object
    void set_temp_flags(uint8_t temp_flags[40]) {
        memcpy(&practice_file.temp_flags, &temp_flags, 40);
    };

    // inject qlog bytes into RAM
    void inject_save() {
        //change to gameinfo later
        memcpy((void*)0x804061C0, (void*)practice_file.qlog_bytes, 2700);
    };

    // inject temp flags into RAM
    void inject_temp_flags() {
        memcpy(&tp_gameInfo.temp_flags, &practice_file.temp_flags, 40);
    }

    // inject position into RAM
    void inject_position() {
        tp_zelAudio.link_debug_ptr->position = practice_file.position;
    }

    // load area
    void load_area() {
        if (inject_save_flag) {
            Utilities::trigger_load(SaveInjection);
        }
    }
}  // namespace SaveInjector