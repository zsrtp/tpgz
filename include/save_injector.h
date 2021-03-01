#pragma once

#include "libtp_c/include/tp.h"

// index into qlog where these exist
#define SPAWN_INDEX 96
#define ROOM_INDEX 97
#define STAGE_INDEX 88

struct PracticeFile {
    void (*inject_options_before_load)();
    void (*inject_options_during_load)();
    void (*inject_options_after_load)();
    int inject_options_after_counter = 0;
};

extern PracticeFile practice_file;

namespace SaveInjector {

void inject_save(void* buffer);
void inject_memfile(void* buffer);
void inject_default_before();
void inject_default_during();
void inject_default_after();

}  // namespace SaveInjector