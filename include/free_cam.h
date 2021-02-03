#pragma once

extern bool free_cam_active;

#ifdef GCN_PLATFORM
#define FREE_CAM_MOVEMENT_TEXT "Stick/L/R"
#define FREE_CAM_VIEW_TEXT "C-stick"
#endif
#ifdef WII_PLATFORM
#define FREE_CAM_MOVEMENT_TEXT "Stick+DPad"
#define FREE_CAM_VIEW_TEXT "C+Stick"
#endif

namespace FreeCam {
void handle_free_cam();
}  // namespace FreeCam
