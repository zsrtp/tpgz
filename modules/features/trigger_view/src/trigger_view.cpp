#include "features/trigger_view/include/trigger_view.h"
#include "collision_view.h"
#include "trigger_view.h"
#include "libtp_c/include/msl_c/math.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "rels/include/defines.h"

namespace TriggerViewer {
KEEP_FUNC void execute() {
    if (g_triggerViewFlags[VIEW_LOAD_ZONES].active) {
        // test cube draw
        OSReport("TriggerViewer::execute is running\n");
        daAlink_c* player = dComIfGp_getPlayer();
        cXyz pos(player->current.pos.x, player->current.pos.y + 100.0f, player->current.pos.z);
        cXyz size(50.0f, 50.0f, 50.0f);
        csXyz angle(0, 0, 0);
        GXColor color = {0x00, 0xFF, 0x00, 0xA0};

        dDbVw_drawCubeXlu(pos, size, angle, color);
    }
}
}  // namespace TriggerViewer