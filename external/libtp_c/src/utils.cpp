#include "utils.h"
#include <cstring>
#include "defines.h"

// Toggles save event flags
KEEP_FUNC void setEventFlag(uint16_t flag) {
    if (dComIfGs_isEventBit(flag)) {
        dComIfGs_offEventBit(flag);
    } else {
        dComIfGs_onEventBit(flag);
    }
}

// Set Savefile spawn info
KEEP_FUNC void setReturnPlace(const char* stage, int8_t room, uint8_t spawn) {
    dSv_player_return_place_c__set(&g_dComIfG_gameInfo.info.getPlayer().mPlayerReturnPlace, stage,
                                   room, spawn);
}

KEEP_FUNC void setRestartPoint(int16_t point) {
    g_dComIfG_gameInfo.info.getRestart().setStartPoint(point);
}

KEEP_FUNC void setNextStageName(const char* name) {
    strcpy((char*)g_dComIfG_gameInfo.play.mNextStage.mStage, name);
}

KEEP_FUNC void setNextStageLayer(int8_t layer) {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(layer);
}

KEEP_FUNC void setNextStageRoom(int8_t room) {
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(room);
}

KEEP_FUNC void setNextStagePoint(int16_t point) {
    g_dComIfG_gameInfo.play.mNextStage.setPoint(point);
}
