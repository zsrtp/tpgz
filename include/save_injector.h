#pragma once

#include "libtp_c/include/tp.h"

// index into qlog where these exist
#define SPAWN_INDEX 96
#define ROOM_INDEX 97
#define STAGE_INDEX 88

struct CameraMatrix {
    float camera0;
    float camera1;
    float camera2;
    float camera3;
    float camera4;
    float camera5;
    float camera6;
    float camera7;
};

struct Options {
    uint8_t temp_flags[40];
    Vec3 position;
    uint16_t angle;
    CameraMatrix camera_matrix;
};

struct PracticeFile {
    uint8_t qlog_bytes[2720] __attribute__ ((aligned (32)));
    Options options;
    bool inject_options;
};

extern bool execute_injection_loading_prep;
extern PracticeFile practice_file;

namespace SaveInjector {
    void get_temp_flags();
    void set_temp_flags(uint8_t temp_flags[40]);
    void inject_save();
    void inject_temp_flags();
    void inject_position();
    void load_area();
}  // namespace SaveInjector