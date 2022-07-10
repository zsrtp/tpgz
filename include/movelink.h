#pragma once
#include "font.h"

extern bool g_moveLinkEnabled;

#ifdef GCN_PLATFORM
#define MOVE_LINK_MOVEMENT_TEXT "Stick/C"
#define MOVE_LINK_ANGLE_TEXT "C-left/right"
#endif
#ifdef WII_PLATFORM
#define MOVE_LINK_MOVEMENT_TEXT "Stick"
#define MOVE_LINK_ANGLE_TEXT "C+Stick"
#endif

namespace MoveLink {
void execute();
// void render_info_input();
}  // namespace MoveLink
