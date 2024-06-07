#ifndef LIB_TP_CHEATS
#define LIB_TP_CHEATS

#include "settings.h"

void GZ_applyCheats();

inline bool GZ_checkCheat(GZSettingID cheatIdx) {
    auto* stng = GZStng_getSetting(cheatIdx);
    return stng && *static_cast<bool*>(stng->data);
}

#endif