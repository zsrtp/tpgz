#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include "d/com/d_com_inf_game.h"

// Toggles save event flags
void setEventFlag(u16 flag);

// Set Savefile spawn info
void setReturnPlace(const char* stage, s8 room, u8 spawn);

void setNextStageName(const char* name);
void setNextStageLayer(s8 layer);
void setNextStageRoom(s8 room);
void setNextStagePoint(s16 point);

#endif