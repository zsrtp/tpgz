#include "utils.h"
#include <cstring>
#include "defines.h"

// Toggles save event flags
KEEP_FUNC void setEventFlag(u16 flag) {
    if (dComIfGs_isEventBit(flag)) {
        dComIfGs_offEventBit(flag);
    } else {
        dComIfGs_onEventBit(flag);
    }
}

// Set Savefile spawn info
KEEP_FUNC void setReturnPlace(const char* stage, s8 room, u8 spawn) {
    dSv_player_return_place_c__set(&g_dComIfG_gameInfo.info.getPlayer().mPlayerReturnPlace, stage,
                                   room, spawn);
}

KEEP_FUNC void setNextStageName(const char* name) {
    strcpy((char*)g_dComIfG_gameInfo.play.mNextStage.mStage, name);
}

KEEP_FUNC void setNextStageLayer(s8 layer) {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(layer);
}

KEEP_FUNC void setNextStageRoom(s8 room) {
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(room);
}

KEEP_FUNC void setNextStagePoint(s16 point) {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(point);
}
