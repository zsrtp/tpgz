#include "time.h"
#include "menus/scene_menu.h"
#include "libtp_c/include/time.h"

namespace Utilities {
    void freeze_time() {
        if (&SceneItems[Scene::FREEZE_TIME_INDEX].active) {
            tp_setTimePass(0);
        } else {
            return;
        }
    }

}  // namespace Utilities
