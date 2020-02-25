#pragma once
#include "libtp_c/include/tp.h"

// index into qlog where these exist
#define SPAWN_INDEX 96
#define ROOM_INDEX 97
#define STAGE_INDEX 88

extern bool execute_injection_loading_prep;

struct PracticeFile {
    uint8_t qlog_bytes[2700];
    uint8_t temp_flags[40];
    Vec3 position;
};

namespace SaveInjector {
    void get_temp_flags(PracticeFile& practice_file);
    void set_temp_flags(PracticeFile& practice_file, uint8_t temp_flags[40]);
    void inject_save(PracticeFile practice_file);
    void inject_temp_flags(PracticeFile& practice_file);
    void inject_position(PracticeFile& practice_file);
    void load_area(PracticeFile& practice_file);
}  // namespace SaveInjector