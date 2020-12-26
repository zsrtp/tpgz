#include "libtp_c/include/utils.h"
#include "input_viewer.h"
#include "controller.h"
#include "font.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/flag.h"
#include "libtp_c/include/math.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"
#include "utils/draw.h"

#define OUTLINE_WIDTH 0x10

bool iv_visible;

namespace InputViewer {
void draw_stick(uint32_t color, Vec2 pos, float size) {
    float s2 = size / 2;
    float dx1 = 0;
    float dy1 = -1.0f;
    float dx2 = 0.7071f;
    float dy2 = -0.7071f;
    float tmp;
    Draw::begin(8, GX_TRIANGLEFAN);
    for (uint8_t i = 0; i < 4; ++i) {
        Draw::add_vertex(color, {pos.x + s2 * dx1, pos.y + s2 * dy1}, {0.5f + dx1, 0.5f + dy1});
        Draw::add_vertex(color, {pos.x + s2 * dx2, pos.y + s2 * dy2}, {0.5f + dx2, 0.5f + dy2});
        tmp = dx1;
        dx1 = -dy1;
        dy1 = tmp;
        tmp = dx2;
        dx2 = -dy2;
        dy2 = tmp;
    }
    Draw::end();
}

void draw_stick_outline(uint32_t color, Vec2 pos, float size) {
    float s2 = size / 2;
    float dx1 = 0;
    float dy1 = -1.0f;
    float dx2 = 0.7071f;
    float dy2 = -0.7071f;
    float tmp;
    Draw::begin_outline(9, OUTLINE_WIDTH);
    for (uint8_t i = 0; i < 4; ++i) {
        Draw::add_vertex(color, {pos.x + s2 * dx1, pos.y + s2 * dy1}, {0.5f + dx1, 0.5f + dy1});
        Draw::add_vertex(color, {pos.x + s2 * dx2, pos.y + s2 * dy2}, {0.5f + dx2, 0.5f + dy2});
        tmp = dx1;
        dx1 = -dy1;
        dy1 = tmp;
        tmp = dx2;
        dx2 = -dy2;
        dy2 = tmp;
    }
    Draw::add_vertex(color, {pos.x + s2 * dx1, pos.y + s2 * dy1}, {0.5f + dx1, 0.5f + dy1});
    Draw::end();
}

void draw_button(Controller::Button button, uint32_t color, Vec2 pos, Vec2 dim) {
    Draw::draw_rect_outline(color, {pos.x, pos.y}, dim, OUTLINE_WIDTH);
    if (Controller::button_is_down(button)) {
        Draw::draw_rect(color, {pos.x, pos.y}, dim);
    }
}

void draw_cross(uint32_t color, Vec2 pos, float size) {
    float branch_width = 3.f * size / 11.f;
    float branch_length = 4.f * size / 11.f;
    draw_button(Controller::DPAD_LEFT, color, {pos.x, pos.y + branch_length},
                {branch_length, branch_width});
    draw_button(Controller::DPAD_UP, color, {pos.x + branch_length, pos.y},
                {branch_width, branch_length});
    draw_button(Controller::DPAD_RIGHT, color,
                {pos.x + branch_length + branch_width, pos.y + branch_length},
                {branch_length, branch_width});
    draw_button(Controller::DPAD_DOWN, color,
                {pos.x + branch_length, pos.y + branch_length + branch_width},
                {branch_width, branch_length});
}

void draw_input_viewer(Vec2 pos, float scale, bool is_shadow) {
    draw_button(Controller::A, is_shadow ? 0x00000060 : 0x00FF7fFF,
                {pos.x + 130.f * scale, pos.y + 30.f * scale}, {30.f * scale, 30.f * scale});
    draw_button(Controller::B, is_shadow ? 0x00000060 : 0xFF0000FF,
                {pos.x + 108.5f * scale, pos.y + 45.f * scale}, {13.f * scale, 13.f * scale});
    draw_button(Controller::X, is_shadow ? 0x00000060 : 0xFFFFFFFF,
                {pos.x + 167.5f * scale, pos.y + 30.f * scale}, {15.f * scale, 30.f * scale});
    draw_button(Controller::Y, is_shadow ? 0x00000060 : 0xFFFFFFFF,
                {pos.x + 130.f * scale, pos.y + 7.5f * scale}, {30.f * scale, 15.f * scale});
    draw_button(Controller::Z, is_shadow ? 0x00000060 : 0x8A2BE2FF,
                {pos.x + 167.5f * scale, pos.y + 7.5f * scale}, {15.f * scale, 15.f * scale});
    draw_button(Controller::START, is_shadow ? 0x00000060 : 0xFFFFFFFF,
                {pos.x + 87.5f * scale, pos.y + 40.f * scale}, {10.f * scale, 10.f * scale});
    draw_cross(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x + 95.f * scale, pos.y + 10.f * scale},
               25.f * scale);

    // analog sticks
    draw_stick_outline(is_shadow ? 0x00000060 : 0xFFFFFFFF,
                       {pos.x + 17.5f * scale, pos.y + 30.f * scale}, 35.0f * scale);
    draw_stick_outline(is_shadow ? 0x00000060 : 0xFFD138FF,
                       {pos.x + 62.5f * scale, pos.y + 30.f * scale}, 35.0f * scale);
    draw_stick(is_shadow ? 0x00000060 : 0xFFFFFFFF,
               {pos.x + (17.5f + tp_mPadMStick.control_analog.x * 10) * scale,
                pos.y + (30.f - tp_mPadMStick.control_analog.y * 10) * scale},
               20.0f * scale);
    draw_stick(is_shadow ? 0x00000060 : 0xFFD138FF,
               {pos.x + (62.5f + tp_mPadSStick.c_analog.x * 10) * scale,
                pos.y + (30.f - tp_mPadSStick.c_analog.y * 10) * scale},
               20.0f * scale);

    // Analog triggers
    Draw::draw_rect_outline(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x, pos.y},
                            {35.f * scale, 7.f * scale}, OUTLINE_WIDTH);
    Draw::draw_rect(is_shadow ? 0x00000060 :
                                Controller::button_is_down(Controller::L) ? 0x00FF00FF : 0xFFFFFFFF,
                    {pos.x, pos.y}, {35.f * tp_mPadButton.l_analog * scale, 7.f * scale});
    Draw::draw_rect_outline(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x + 45.f * scale, pos.y},
                            {35.f * scale, 7.f * scale}, OUTLINE_WIDTH);
    Draw::draw_rect(is_shadow ? 0x00000060 :
                                Controller::button_is_down(Controller::R) ? 0x00FF00FF : 0xFFFFFFFF,
                    {pos.x + (45.f + 35.f * (1 - tp_mPadButton.r_analog)) * scale, pos.y},
                    {35.f * tp_mPadButton.r_analog * scale, 7.f * scale});
}

void render() {
    Vec2 pos = {0.f, 0.f};
    pos.x += sprite_offsets[VIEWER_INDEX].x;
    pos.y += sprite_offsets[VIEWER_INDEX].y;
    float scale = 1.0f;  // 0.5f * tp_cos(TP::get_frame_count() / 20.f) + 1.0f;
    if (g_drop_shadows)
        draw_input_viewer({pos.x + 1.f, pos.y + 1.f}, scale, true);
    draw_input_viewer(pos, scale, false);

    // stick inputs
    char control_x[5];  // control stick x
    char control_y[5];  // control stick y
    char c_x[5];        // c stick x
    char c_y[5];        // c stick y

    tp_sprintf(control_x, "%d", tp_mPadStatus.control_x);
    tp_sprintf(control_y, "%d", tp_mPadStatus.control_y);
    tp_sprintf(c_x, "%d", tp_mPadStatus.c_x);
    tp_sprintf(c_y, "%d", tp_mPadStatus.c_y);

    Font::gz_renderChars(control_x, pos.x, pos.y + 65.f * scale, 0xFFFFFFFF, g_drop_shadows,
                         13 * scale);
    Font::gz_renderChars(control_y, pos.x + 23.f * scale, pos.y + 65.f * scale, 0xFFFFFFFF,
                         g_drop_shadows, 13 * scale);
    Font::gz_renderChars(c_x, pos.x + 45.f * scale, pos.y + 65.f * scale, 0xFFD138FF,
                         g_drop_shadows, 13 * scale);
    Font::gz_renderChars(c_y, pos.x + 70.f * scale, pos.y + 65.f * scale, 0xFFD138FF,
                         g_drop_shadows, 13 * scale);
}
}  // namespace InputViewer