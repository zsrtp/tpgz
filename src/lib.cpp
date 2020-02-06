#include "controller.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "gcn_c/include/gfx.h"

static bool visible = false;

void render() {
    if (Controller::is_pressed(Controller::Pad::DPAD_DOWN)) {
        visible = false;
        tp_osReport("Goodbye!");
        return;
    }
}

extern "C" void game_loop() {
    bool a_down = button_is_pressed(Controller::A);
    bool z_down = button_is_down(Controller::Z);
    bool r_down = Controller::button_is_down(Controller::R);
    bool l_down = Controller::button_is_down(Controller::L);

    if (visible) {
        render();
    } else if (l_down && r_down && z_down && a_down) {
        visible = true;
    }
}

extern "C" void draw() {
    GX_SetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_SET);

    GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_NRM_XYZ, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

    GX_Begin(GX_TRIANGLES, GX_VTXFMT0, 3);
    {
        GX_Position2f32(150.0f, 150.0f);
        GX_Color1u32(0xFF0000FF);
        GX_Position2f32(250.0f, 150.0f);
        GX_Color1u32(0x00FF00FF);
        GX_Position2f32(200.0f, 250.0f);
        GX_Color1u32(0x0000FFFF);
    }
    GX_End();
}