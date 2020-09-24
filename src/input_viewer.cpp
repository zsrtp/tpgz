#include <stdio.h>
#define GXFlush_addr 0x8035becc
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/flag.h"
#include "controller.h"
#include "libtp_c/include/controller.h"
#include "font.h"
#include "input_viewer.h"
#include "menu.h"
#include "gcn_c/include/gfx.h"

bool iv_visible;
GXTexObj _ivTexObj;
const char _iv_text_data[1] __attribute__ ((aligned (32))) = {0xff};

namespace InputViewer {
    void init() {
        memset(&_ivTexObj, 0x0, sizeof(GXTexObj));
        GX_InitTexObj(&_ivTexObj, (void*)_iv_text_data, 1, 1, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    }

    void add_vertex(uint32_t color, Vec2 p) {
        GX_Position2f32(p.x, p.y);
        GX_Color1u32(color);
        GX_TexCoord2f32(0.0f, 0.0f);
    }

    void draw_quad(uint32_t color, Vec2 p[4]) {
        GX_InvalidateTexAll();
        GX_LoadTexObj(&_ivTexObj, (uint8_t)GX_TEXMAP0);
        GX_Begin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
            add_vertex(color, p[0]);
            add_vertex(color, p[1]);
            add_vertex(color, p[3]);
            add_vertex(color, p[2]);
        GX_End();
    }

    void draw_quad_outline(uint32_t color, Vec2 p[4]) {
        GX_InvalidateTexAll();
        GX_LoadTexObj(&_ivTexObj, (uint8_t)GX_TEXMAP0);
        GX_SetLineWidth(0x10, GX_TO_ZERO);
        GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 5);
            add_vertex(color, p[0]);
            add_vertex(color, p[1]);
            add_vertex(color, p[2]);
            add_vertex(color, p[3]);
            add_vertex(color, p[0]);
        GX_End();
    }

    void draw_stick(uint32_t color, Vec2 pos, float size) {
        float s2 = size / 2;
        float dx1 = 0;
        float dy1 = -s2;
        float dx2 = s2 * 0.7071f;
        float dy2 = - s2 * 0.7071f;
        float tmp;
        GX_InvalidateTexAll();
        GX_LoadTexObj(&_ivTexObj, (uint8_t)GX_TEXMAP0);
        GX_Begin(GX_TRIANGLEFAN, GX_VTXFMT0, 8);
            for (uint8_t i = 0; i < 4; ++i) {
                add_vertex(color, {pos.x + dx1, pos.y + dy1});
                add_vertex(color, {pos.x + dx2, pos.y + dy2});
                tmp = dx1;
                dx1 = -dy1;
                dy1 = tmp;
                tmp = dx2;
                dx2 = -dy2;
                dy2 = tmp;
            }
        GX_End();
    }

    void draw_stick_outline(uint32_t color, Vec2 pos, float size) {
        float s2 = size / 2;
        float dx1 = 0;
        float dy1 = -s2;
        float dx2 = s2 * 0.7071f;
        float dy2 = - s2 * 0.7071f;
        float tmp;
        GX_InvalidateTexAll();
        GX_LoadTexObj(&_ivTexObj, (uint8_t)GX_TEXMAP0);
        GX_SetLineWidth(0x10, GX_TO_ZERO);
        GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 9);
            for (uint8_t i = 0; i < 4; ++i) {
                add_vertex(color, {pos.x + dx1, pos.y + dy1});
                add_vertex(color, {pos.x + dx2, pos.y + dy2});
                tmp = dx1;
                dx1 = -dy1;
                dy1 = tmp;
                tmp = dx2;
                dx2 = -dy2;
                dy2 = tmp;
            }
            add_vertex(color, {pos.x + dx1, pos.y + dy1});
        GX_End();
    }

    void draw_rect(uint32_t color, Vec2 pos, Vec2 dim) {
        Vec2 vertices[4] = {
            {pos.x - dim.x / 2, pos.y - dim.y / 2},
            {pos.x + dim.x / 2, pos.y - dim.y / 2},
            {pos.x + dim.x / 2, pos.y + dim.y / 2},
            {pos.x - dim.x / 2, pos.y + dim.y / 2}};
        draw_quad(color, vertices);
    }

    void draw_rect_outline(uint32_t color, Vec2 pos, Vec2 dim) {
        Vec2 vertices[4] = {
            {pos.x - dim.x / 2, pos.y - dim.y / 2},
            {pos.x + dim.x / 2, pos.y - dim.y / 2},
            {pos.x + dim.x / 2, pos.y + dim.y / 2},
            {pos.x - dim.x / 2, pos.y + dim.y / 2}};
        draw_quad_outline(color, vertices);
    }

    void draw_cross(uint32_t color, Vec2 pos, float size) {
        float branch_width = 8.f * size;
        float branch_length = 10.f * size;
        float branch_offset = (branch_width / 2 + branch_length / 2);
        draw_rect_outline(color, {pos.x - branch_offset, pos.y}, {branch_length, branch_width});
        if (Controller::button_is_down(Controller::DPAD_LEFT)) {
            draw_rect(color, {pos.x - branch_offset, pos.y}, {branch_length, branch_width});
        }

        draw_rect_outline(color, {pos.x, pos.y + branch_offset}, {branch_width, branch_length});
        if (Controller::button_is_down(Controller::DPAD_DOWN)) {
            draw_rect(color, {pos.x, pos.y + branch_offset}, {branch_width, branch_length});
        }

        draw_rect_outline(color, {pos.x + branch_offset, pos.y}, {branch_length, branch_width});
        if (Controller::button_is_down(Controller::DPAD_RIGHT)) {
            draw_rect(color, {pos.x + branch_offset, pos.y}, {branch_length, branch_width});
        }

        draw_rect_outline(color, {pos.x, pos.y - branch_offset}, {branch_width, branch_length});
        if (Controller::button_is_down(Controller::DPAD_UP)) {
            draw_rect(color, {pos.x, pos.y - branch_offset}, {branch_width, branch_length});
        }
    }

    void render(Font& font) {
        using namespace Controller;

        if (g_drop_shadows) draw_rect_outline(0x000000FF, {495.f + sprite_offsets[VIEWER_INDEX].x + 1, 420.f + sprite_offsets[VIEWER_INDEX].y + 1}, {30.f, 30.f});
        draw_rect_outline(0x00FF7fFF, {495.f + sprite_offsets[VIEWER_INDEX].x, 420.f + sprite_offsets[VIEWER_INDEX].y}, {30.f, 30.f});
        if (button_is_down(A)) {
            if (g_drop_shadows) draw_rect(0x000000FF, {495.f + sprite_offsets[VIEWER_INDEX].x + 1, 420.f + sprite_offsets[VIEWER_INDEX].y + 1}, {30.f, 30.f});
            draw_rect(0x00FF7FFF, {495.f + sprite_offsets[VIEWER_INDEX].x, 420.f + sprite_offsets[VIEWER_INDEX].y}, {30.f, 30.f});
        }

        if (g_drop_shadows) draw_rect_outline(0x000000FF, {460.f + sprite_offsets[VIEWER_INDEX].x + 1, 430.f + sprite_offsets[VIEWER_INDEX].y + 1}, {13.f, 13.f});
        draw_rect_outline(0xFF0000FF, {460.f + sprite_offsets[VIEWER_INDEX].x, 430.f + sprite_offsets[VIEWER_INDEX].y}, {13.f, 13.f});
        if (button_is_down(B)) {
            if (g_drop_shadows) draw_rect(0x000000FF, {460.f + sprite_offsets[VIEWER_INDEX].x + 1, 430.f + sprite_offsets[VIEWER_INDEX].y + 1}, {13.f, 13.f});
            draw_rect(0xFF0000FF, {460.f + sprite_offsets[VIEWER_INDEX].x, 430.f + sprite_offsets[VIEWER_INDEX].y}, {13.f, 13.f});
        }

        if (g_drop_shadows) draw_rect_outline(0x000000FF, {525.f + sprite_offsets[VIEWER_INDEX].x + 1, 420.f + sprite_offsets[VIEWER_INDEX].y + 1}, {15.f, 30.f});
        draw_rect_outline(0xFFFFFFFF, {525.f + sprite_offsets[VIEWER_INDEX].x, 420.f + sprite_offsets[VIEWER_INDEX].y}, {15.f, 30.f});
        if (button_is_down(X)) {
            if (g_drop_shadows) draw_rect(0x000000FF, {525.f + sprite_offsets[VIEWER_INDEX].x + 1, 420.f + sprite_offsets[VIEWER_INDEX].y + 1}, {15.f, 30.f});
            draw_rect(0xFFFFFFFF, {525.f + sprite_offsets[VIEWER_INDEX].x, 420.f + sprite_offsets[VIEWER_INDEX].y}, {15.f, 30.f});
        }

        if (g_drop_shadows) draw_rect_outline(0x000000FF, {495.f + sprite_offsets[VIEWER_INDEX].x + 1, 390.f + sprite_offsets[VIEWER_INDEX].y + 1}, {30.f, 15.f});
        draw_rect_outline(0xFFFFFFFF, {495.f + sprite_offsets[VIEWER_INDEX].x, 390.f + sprite_offsets[VIEWER_INDEX].y}, {30.f, 15.f});
        if (button_is_down(Y)) {
            if (g_drop_shadows) draw_rect(0x000000FF, {495.f + sprite_offsets[VIEWER_INDEX].x + 1, 390.f + sprite_offsets[VIEWER_INDEX].y + 1}, {30.f, 15.f});
            draw_rect(0xFFFFFFFF, {495.f + sprite_offsets[VIEWER_INDEX].x, 390.f + sprite_offsets[VIEWER_INDEX].y}, {30.f, 15.f});
        }

        if (g_drop_shadows) draw_rect_outline(0x000000FF, {525.f + sprite_offsets[VIEWER_INDEX].x + 1, 390.f + sprite_offsets[VIEWER_INDEX].y + 1}, {15.f, 15.f});
        draw_rect_outline(0x8A2BE2FF, {525.f + sprite_offsets[VIEWER_INDEX].x, 390.f + sprite_offsets[VIEWER_INDEX].y}, {15.f, 15.f});
        if (button_is_down(Z)) {
            if (g_drop_shadows) draw_rect(0x000000FF, {525.f + sprite_offsets[VIEWER_INDEX].x + 1, 390.f + sprite_offsets[VIEWER_INDEX].y + 1}, {15.f, 15.f});
            draw_rect(0x8A2BE2FF, {525.f + sprite_offsets[VIEWER_INDEX].x, 390.f + sprite_offsets[VIEWER_INDEX].y}, {15.f, 15.f});
        }

        if (g_drop_shadows) draw_rect_outline(0x000000FF, {460.f + sprite_offsets[VIEWER_INDEX].x + 1, 410.f + sprite_offsets[VIEWER_INDEX].y + 1}, {10.f, 10.f});
        draw_rect_outline(0xFFFFFFFF, {460.f + sprite_offsets[VIEWER_INDEX].x, 410.f + sprite_offsets[VIEWER_INDEX].y}, {10.f, 10.f});
        if (button_is_down(START)) {
            if (g_drop_shadows) draw_rect(0x000000FF, {460.f + sprite_offsets[VIEWER_INDEX].x + 1, 410.f + sprite_offsets[VIEWER_INDEX].y + 1}, {10.f, 10.f});
            draw_rect(0xFFFFFFFF, {460.f + sprite_offsets[VIEWER_INDEX].x, 410.f + sprite_offsets[VIEWER_INDEX].y}, {10.f, 10.f});
        }

        if (g_drop_shadows) draw_cross(0x000000FF, {430.f + sprite_offsets[VIEWER_INDEX].x + 1, 420.f + sprite_offsets[VIEWER_INDEX].y + 1}, 1.f);
        draw_cross(0xFFFFFFFF, {430.f + sprite_offsets[VIEWER_INDEX].x, 420.f + sprite_offsets[VIEWER_INDEX].y}, 1.f);

        // stick inputs
        char control_x[5];  // control stick x
        char control_y[5];  // control stick y
        char c_x[5];        // c stick x
        char c_y[5];        // c stick y

        sprintf(control_x, "%d", tp_mPadSticks.control_x);
        sprintf(control_y, "%d", tp_mPadSticks.control_y);
        sprintf(c_x, "%d", tp_mPadSticks.c_x);
        sprintf(c_y, "%d", tp_mPadSticks.c_y);

        font.gz_renderChars(control_x, 295.0f + sprite_offsets[VIEWER_INDEX].x, 440.0f + sprite_offsets[VIEWER_INDEX].y, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars(control_y, 330.0f + sprite_offsets[VIEWER_INDEX].x, 440.0f + sprite_offsets[VIEWER_INDEX].y, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars(c_x, 360.0f + sprite_offsets[VIEWER_INDEX].x, 440.0f + sprite_offsets[VIEWER_INDEX].y, 0xFFD138FF, g_drop_shadows);
        font.gz_renderChars(c_y, 390.0f + sprite_offsets[VIEWER_INDEX].x, 440.0f + sprite_offsets[VIEWER_INDEX].y, 0xFFD138FF, g_drop_shadows);

        // analog input viewer
        if (g_drop_shadows) {
            draw_stick_outline(0x000000FF, {320.0f + sprite_offsets[VIEWER_INDEX].x + 1, 405.0f + sprite_offsets[VIEWER_INDEX].y + 1}, 36.0f);
            draw_stick_outline(0x000000FF, {385.0f + sprite_offsets[VIEWER_INDEX].x + 1, 405.0f + sprite_offsets[VIEWER_INDEX].y + 1}, 36.0f);
            draw_stick(0x000000FF, {320.0f + tp_mPadAStick.x * 10 + sprite_offsets[VIEWER_INDEX].x + 1, 405.0f - tp_mPadAStick.y * 10 + sprite_offsets[VIEWER_INDEX].y + 1}, 20.0f);
            draw_stick(0x000000FF, {385.0f + tp_mPadACStick.x * 10 + sprite_offsets[VIEWER_INDEX].x + 1, 405.0f - tp_mPadACStick.y * 10 + sprite_offsets[VIEWER_INDEX].y + 1}, 20.0f);
        }
        draw_stick_outline(0xFFFFFFFF, {320.0f + sprite_offsets[VIEWER_INDEX].x, 405.0f + sprite_offsets[VIEWER_INDEX].y}, 36.0f);
        draw_stick_outline(0xFFD138FF, {385.0f + sprite_offsets[VIEWER_INDEX].x, 405.0f + sprite_offsets[VIEWER_INDEX].y}, 36.0f);
        draw_stick(0xFFFFFFFF, {320.0f + tp_mPadAStick.x * 10 + sprite_offsets[VIEWER_INDEX].x, 405.0f - tp_mPadAStick.y * 10 + sprite_offsets[VIEWER_INDEX].y}, 20.0f);
        draw_stick(0xFFD138FF, {385.0f + tp_mPadACStick.x * 10 + sprite_offsets[VIEWER_INDEX].x, 405.0f - tp_mPadACStick.y * 10 + sprite_offsets[VIEWER_INDEX].y}, 20.0f);

        // Analog triggers
        if (g_drop_shadows) {
            draw_rect_outline(0x000000FF, {320.0f + sprite_offsets[VIEWER_INDEX].x + 1, 375.f + sprite_offsets[VIEWER_INDEX].y + 1}, {45.f, 7.f});
            draw_rect(0x000000FF, {320.0f - 45.f * (1 - tp_mPadATriggers.l) / 2 + sprite_offsets[VIEWER_INDEX].x + 1, 375.f + sprite_offsets[VIEWER_INDEX].y + 1}, {45.f * tp_mPadATriggers.l, 8.f});
            draw_rect_outline(0x000000FF, {385.0f + sprite_offsets[VIEWER_INDEX].x + 1, 375.f + sprite_offsets[VIEWER_INDEX].y + 1}, {45.f, 7.f});
            draw_rect(0x000000FF, {385.0f + 45.f * (1 - tp_mPadATriggers.r) / 2 + sprite_offsets[VIEWER_INDEX].x + 1, 375.f + sprite_offsets[VIEWER_INDEX].y + 1}, {45.f * tp_mPadATriggers.r, 8.f});
        }
        draw_rect_outline(0xFFFFFFFF, {320.0f + sprite_offsets[VIEWER_INDEX].x, 375.f + sprite_offsets[VIEWER_INDEX].y}, {45.f, 7.f});
        draw_rect(button_is_down(L) ? 0x00FF00FF : 0xFFFFFFFF, {320.0f - 45.f * (1 - tp_mPadATriggers.l) / 2 + sprite_offsets[VIEWER_INDEX].x, 375.f + sprite_offsets[VIEWER_INDEX].y}, {45.f * tp_mPadATriggers.l, 8.f});
        draw_rect_outline(0xFFFFFFFF, {385.0f + sprite_offsets[VIEWER_INDEX].x, 375.f + sprite_offsets[VIEWER_INDEX].y}, {45.f, 7.f});
        draw_rect(button_is_down(R) ? 0x00FF00FF : 0xFFFFFFFF, {385.0f + 45.f * (1 - tp_mPadATriggers.r) / 2 + sprite_offsets[VIEWER_INDEX].x, 375.f + sprite_offsets[VIEWER_INDEX].y}, {45.f * tp_mPadATriggers.r, 8.f});
        font.gz_renderChars(control_x, 295.0f + sprite_offsets[VIEWER_INDEX].x, 440.0f + sprite_offsets[VIEWER_INDEX].y, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars(control_y, 330.0f + sprite_offsets[VIEWER_INDEX].x, 440.0f + sprite_offsets[VIEWER_INDEX].y, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars(c_x, 360.0f + sprite_offsets[VIEWER_INDEX].x, 440.0f + sprite_offsets[VIEWER_INDEX].y, 0xFFD138FF, g_drop_shadows);
        font.gz_renderChars(c_y, 390.0f + sprite_offsets[VIEWER_INDEX].x, 440.0f + sprite_offsets[VIEWER_INDEX].y, 0xFFD138FF, g_drop_shadows);

        // analog input viewer
        if (g_drop_shadows) {
            draw_stick_outline(0x000000FF, {320.0f + sprite_offsets[VIEWER_INDEX].x + 1, 405.0f + sprite_offsets[VIEWER_INDEX].y + 1}, 36.0f);
            draw_stick_outline(0x000000FF, {385.0f + sprite_offsets[VIEWER_INDEX].x + 1, 405.0f + sprite_offsets[VIEWER_INDEX].y + 1}, 36.0f);
            draw_stick(0x000000FF, {320.0f + tp_mPadAStick.x * 10 + sprite_offsets[VIEWER_INDEX].x + 1, 405.0f - tp_mPadAStick.y * 10 + sprite_offsets[VIEWER_INDEX].y + 1}, 20.0f);
            draw_stick(0x000000FF, {385.0f + tp_mPadACStick.x * 10 + sprite_offsets[VIEWER_INDEX].x + 1, 405.0f - tp_mPadACStick.y * 10 + sprite_offsets[VIEWER_INDEX].y + 1}, 20.0f);
        }
        draw_stick_outline(0xFFFFFFFF, {320.0f + sprite_offsets[VIEWER_INDEX].x, 405.0f + sprite_offsets[VIEWER_INDEX].y}, 36.0f);
        draw_stick_outline(0xFFD138FF, {385.0f + sprite_offsets[VIEWER_INDEX].x, 405.0f + sprite_offsets[VIEWER_INDEX].y}, 36.0f);
        draw_stick(0xFFFFFFFF, {320.0f + tp_mPadAStick.x * 10 + sprite_offsets[VIEWER_INDEX].x, 405.0f - tp_mPadAStick.y * 10 + sprite_offsets[VIEWER_INDEX].y}, 20.0f);
        draw_stick(0xFFD138FF, {385.0f + tp_mPadACStick.x * 10 + sprite_offsets[VIEWER_INDEX].x, 405.0f - tp_mPadACStick.y * 10 + sprite_offsets[VIEWER_INDEX].y}, 20.0f);

        // Analog triggers
        if (g_drop_shadows) {
            draw_rect_outline(0x000000FF, {320.0f + sprite_offsets[VIEWER_INDEX].x + 1, 375.f + sprite_offsets[VIEWER_INDEX].y + 1}, {45.f, 7.f});
            draw_rect(0x000000FF, {320.0f - 45.f * (1 - tp_mPadATriggers.l) / 2 + sprite_offsets[VIEWER_INDEX].x + 1, 375.f + sprite_offsets[VIEWER_INDEX].y + 1}, {45.f * tp_mPadATriggers.l, 8.f});
            draw_rect_outline(0x000000FF, {385.0f + sprite_offsets[VIEWER_INDEX].x + 1, 375.f + sprite_offsets[VIEWER_INDEX].y + 1}, {45.f, 7.f});
            draw_rect(0x000000FF, {385.0f + 45.f * (1 - tp_mPadATriggers.r) / 2 + sprite_offsets[VIEWER_INDEX].x + 1, 375.f + sprite_offsets[VIEWER_INDEX].y + 1}, {45.f * tp_mPadATriggers.r, 8.f});
        }
        draw_rect_outline(0xFFFFFFFF, {320.0f + sprite_offsets[VIEWER_INDEX].x, 375.f + sprite_offsets[VIEWER_INDEX].y}, {45.f, 7.f});
        draw_rect(button_is_down(L) ? 0x00FF00FF : 0xFFFFFFFF, {320.0f - 45.f * (1 - tp_mPadATriggers.l) / 2 + sprite_offsets[VIEWER_INDEX].x, 375.f + sprite_offsets[VIEWER_INDEX].y}, {45.f * tp_mPadATriggers.l, 8.f});
        draw_rect_outline(0xFFFFFFFF, {385.0f + sprite_offsets[VIEWER_INDEX].x, 375.f + sprite_offsets[VIEWER_INDEX].y}, {45.f, 7.f});
        draw_rect(button_is_down(R) ? 0x00FF00FF : 0xFFFFFFFF, {385.0f + 45.f * (1 - tp_mPadATriggers.r) / 2 + sprite_offsets[VIEWER_INDEX].x, 375.f + sprite_offsets[VIEWER_INDEX].y}, {45.f * tp_mPadATriggers.r, 8.f});
    }
}  // namespace InputViewer
