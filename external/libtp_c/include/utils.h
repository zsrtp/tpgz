#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include "d/com/d_com_inf_game.h"

// Toggles save event flags
void setEventFlag(uint16_t flag);

// Set stage restart info
void setRestartPoint(int16_t point);

// Set Savefile spawn info
void setReturnPlace(const char* stage, int8_t room, uint8_t spawn);

void setNextStageName(const char* name);
void setNextStageLayer(int8_t layer);
void setNextStageRoom(int8_t room);
void setNextStagePoint(int16_t point);

#endif