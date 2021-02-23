#include "controller.h"
#include "fifo_queue.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "flaglog.h"

namespace FlagLog {

static char buf[25];

uint8_t s_areatemp_record[0x20];
uint8_t s_event_record[0x100];
uint8_t s_minigame_record[0x18];
uint8_t s_danbit_record[0x18];
// uint8_t s_onetime_event_record[0x100];

bool init_save_record = false;

void save_record(uint8_t* record, uint8_t saved_record[], int record_size) {
    for (int i = 0; i < record_size; i++) {
        saved_record[i] = *(record + i);
    }
}

void display_log(const char* name, uint8_t* record, uint8_t saved_record[], int record_size) {
    for (int i = 0; i < record_size; i++) {
        if (*(record + i) != saved_record[i]) {
            for (uint8_t bit = 0; bit < 8; bit++) {
                if ((*(record + i) & (1 << bit)) != (saved_record[i] & (1 << bit))) {
                    tp_sprintf(buf, "%s [0x%02X: %d]", name, i, bit);
                    FIFOQueue::push(buf, Queue, 0xFFFFFF00);
                }
            }
            saved_record[i] = *(record + i);
        }
    }
}

void run() {
    if (!init_save_record) {
        save_record(tp_gameInfo.temp_flags.flags, s_areatemp_record, 0x20);
        save_record(tp_gameInfo.event_flags.flags, s_event_record, 0x100);
        save_record(tp_gameInfo.minigame_flags, s_minigame_record, 0x18);
        // save_record(tp_gameInfo.one_time_events, s_onetime_event_record, 0x100);
        save_record((uint8_t*)tp_gameInfo.dungeon_temp_flags.switch_bitfield, s_danbit_record, 0x18);
        init_save_record = true;
    }

    display_log("area temp", tp_gameInfo.temp_flags.flags, s_areatemp_record, 0x20);
    display_log("event", tp_gameInfo.event_flags.flags, s_event_record, 0x100);
    display_log("minigame", tp_gameInfo.minigame_flags, s_minigame_record, 0x18);
    display_log("dungeon", (uint8_t*)tp_gameInfo.dungeon_temp_flags.switch_bitfield, s_danbit_record, 0x18);
    // display_log("OT event", tp_gameInfo.one_time_events, s_onetime_event_record, 0x100);
}
}