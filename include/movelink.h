#pragma once
#include "font.h"

extern bool move_link_active;

#ifdef GCN_PLATFORM
#define MOVE_LINK_MOVEMENT_TEXT "Stick/C"
#define MOVE_LINK_ANGLE_TEXT "C-left/right"
#endif
#ifdef WII_PLATFORM
#define MOVE_LINK_MOVEMENT_TEXT "Stick"
#define MOVE_LINK_ANGLE_TEXT "C+Stick"
#endif

namespace MoveLink {
void move_link();
void render_info_input();
}  // namespace MoveLink
