#include "time.h"
#include "libtp_c/include/d/d_stage.h"
#include "menus/scene_menu.h"

namespace Utilities {
void freeze_time() {
    if (&SceneItems[Scene::FREEZE_TIME_INDEX].active) {
        dStage_roomControl_c__setTimePass(TIME_STOP);
    } else {
        return;
    }
}

}  // namespace Utilities
