#ifndef LIB_TP_CHEATS
#define LIB_TP_CHEATS

#include "settings.h"

void GZ_applyCheats();

inline bool GZ_checkCheat(GZSettingID cheatIdx) {
    return GZStng_getSettingData(cheatIdx, false);
}

#endif