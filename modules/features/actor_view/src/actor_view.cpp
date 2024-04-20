#include "features/actor_view/include/actor_view.h"
#include "menus/utils/menu_mgr.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "menus/menu_actor_list/include/actor_list_menu.h"
#include "collision_view.h"
#include "global_data.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"

namespace ActorViewer {
void drawGizmo(fopAc_ac_c* actor) {
    // Gizmo cube size and angle
    cXyz cube_size = {10.0f, 10.0f, 10.0f};
    csXyz cube_angle = {0, 0, 0};

    // Colors for the gizmo's axis lines and cube
    GXColor red = {255, 0, 0, 255};
    GXColor green = {0, 255, 0, 255};
    GXColor blue = {0, 0, 255, 255};
    GXColor white = {255, 255, 255, 255};

    // length of the gizmo's axis grid lines to draw
    f32 grid_line_length = 200.0f;

    // width of the gizmo's axis grid lines to draw
    u8 line_width = 20;

    // Draw a cube at the position of the actor
    dDbVw_drawCubeXlu(actor->current.pos, cube_size, cube_angle, white);

    // Gizmo axis line points
    cXyz point_x_a = {actor->current.pos.x + grid_line_length, actor->current.pos.y, actor->current.pos.z};
    cXyz point_x_b = {actor->current.pos.x - grid_line_length, actor->current.pos.y, actor->current.pos.z};
    cXyz point_y_a = {actor->current.pos.x, actor->current.pos.y + grid_line_length, actor->current.pos.z};
    cXyz point_y_b = {actor->current.pos.x, actor->current.pos.y - grid_line_length, actor->current.pos.z};
    cXyz point_z_a = {actor->current.pos.x, actor->current.pos.y, actor->current.pos.z + grid_line_length};
    cXyz point_z_b = {actor->current.pos.x, actor->current.pos.y, actor->current.pos.z - grid_line_length};
    

    // Gizmo axis lines
    dDbVw_drawLineXlu(point_x_a, point_x_b, red, 1, line_width);
    dDbVw_drawLineXlu(point_y_a, point_y_b, green, 1, line_width);
    dDbVw_drawLineXlu(point_z_a, point_z_b, blue, 1, line_width);
}

KEEP_FUNC void execute() {
    if (g_actorViewEnabled) {
        if (g_currentActor != NULL)
            drawGizmo(g_currentActor);
    }
}
}  // namespace ActorViewer