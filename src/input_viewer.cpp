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
void draw_ellipse(uint32_t color, Vec2 center, Vec2 dim) {
    constexpr const size_t n_points = 4;
    float dx[n_points] = {0};
    float dy[n_points] = {0};
    float tmp;
    for (size_t i = 0; i < n_points; ++i) {
        dx[i] = tp_cos(i * M_PI / 2.0 / n_points);
        dy[i] = tp_sin(i * M_PI / 2.0 / n_points);
    }
    Draw::begin(4 * n_points, GX_TRIANGLEFAN);
    for (uint8_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < n_points; ++j) {
            Draw::add_vertex(color, {center.x + dim.x / 2 * dx[j], center.y + dim.y / 2 * dy[j]},
                             {0.5f + dx[j], 0.5f + dy[j]});
            tmp = dx[j];
            dx[j] = -dy[j];
            dy[j] = tmp;
        }
    }
    Draw::end();
}

void draw_ellipse_outline(uint32_t color, Vec2 center, Vec2 dim, uint8_t line_width) {
    constexpr const size_t n_points = 4;
    float dx[n_points] = {0};
    float dy[n_points] = {0};
    float tmp;
    for (size_t i = 0; i < n_points; ++i) {
        dx[i] = tp_cos(i * M_PI / 2.0 / n_points);
        dy[i] = tp_sin(i * M_PI / 2.0 / n_points);
    }
    Draw::begin_outline(4 * n_points + 1, line_width);
    for (uint8_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < n_points; ++j) {
            Draw::add_vertex(color, {center.x + dim.x / 2 * dx[j], center.y + dim.y / 2 * dy[j]},
                             {0.5f + dx[j], 0.5f + dy[j]});
            tmp = dx[j];
            dx[j] = -dy[j];
            dy[j] = tmp;
        }
    }
    Draw::add_vertex(color, {center.x + dim.x / 2 * dx[0], center.y + dim.y / 2 * dy[0]},
                     {0.5f + dx[0], 0.5f + dy[0]});
    Draw::end();
}

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

void draw_button(Controller::Button button, char c, uint32_t color, Vec2 pos, Vec2 dim,
                 float char_size) {
    bool is_button_down = Controller::button_is_down(button);
    Draw::draw_rect_outline(color, {pos.x, pos.y}, dim, OUTLINE_WIDTH);
    if (is_button_down) {
        Draw::draw_rect(color, {pos.x, pos.y}, dim);
    }
    float width = Font::get_char_width(c, char_size);
    Font::gz_renderChar(c, pos.x + (dim.x - width) / 2, pos.y + (dim.y + char_size / 2) / 2,
                        is_button_down ? 0x00000060 : color, false, char_size);
}

void draw_button_ellipse(Controller::Button button, char c, uint32_t color, Vec2 pos, Vec2 dim,
                         float char_size) {
    bool is_button_down = Controller::button_is_down(button);
    draw_ellipse_outline(color, {pos.x + dim.x / 2, pos.y + dim.y / 2}, dim, OUTLINE_WIDTH);
    if (is_button_down) {
        draw_ellipse(color, {pos.x + dim.x / 2, pos.y + dim.y / 2}, dim);
    }
    float width = Font::get_char_width(c, char_size);
    Font::gz_renderChar(c, pos.x + (dim.x - width) / 2, pos.y + (dim.y + char_size / 2) / 2,
                        is_button_down ? 0x00000060 : color, false, char_size);
}

void draw_cross(uint32_t color, Vec2 pos, float size) {
    float branch_width = 3.f * size / 11.f;
    float branch_length = 4.f * size / 11.f;
    draw_button(Controller::DPAD_LEFT, '-', color, {pos.x, pos.y + branch_length},
                {branch_length, branch_width}, 8 * size / 25);
    draw_button(Controller::DPAD_UP, '|', color, {pos.x + branch_length, pos.y},
                {branch_width, branch_length}, 4 * size / 25);
    draw_button(Controller::DPAD_RIGHT, '-', color,
                {pos.x + branch_length + branch_width, pos.y + branch_length},
                {branch_length, branch_width}, 8 * size / 25);
    draw_button(Controller::DPAD_DOWN, '|', color,
                {pos.x + branch_length, pos.y + branch_length + branch_width},
                {branch_width, branch_length}, 4 * size / 25);
}

void draw_input_viewer(Vec2 pos, float scale, bool is_shadow) {
#ifdef GCN_PLATFORM
    draw_button(Controller::A, 'A', is_shadow ? 0x00000060 : 0x00FF7fFF,
                {pos.x + 130.f * scale, pos.y + 30.f * scale}, {30.f * scale, 30.f * scale},
                8 * scale);
    draw_button(Controller::B, 'B', is_shadow ? 0x00000060 : 0xFF0000FF,
                {pos.x + 108.5f * scale, pos.y + 45.f * scale}, {13.f * scale, 13.f * scale},
                8 * scale);
    draw_button(Controller::X, 'X', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                {pos.x + 167.5f * scale, pos.y + 30.f * scale}, {15.f * scale, 30.f * scale},
                8 * scale);
    draw_button(Controller::Y, 'Y', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                {pos.x + 130.f * scale, pos.y + 7.5f * scale}, {30.f * scale, 15.f * scale},
                8 * scale);
    draw_button(Controller::Z, 'Z', is_shadow ? 0x00000060 : 0x8A2BE2FF,
                {pos.x + 167.5f * scale, pos.y + 7.5f * scale}, {15.f * scale, 15.f * scale},
                8 * scale);
    draw_button(Controller::START, ' ', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                {pos.x + 87.5f * scale, pos.y + 40.f * scale}, {10.f * scale, 10.f * scale},
                8 * scale);
    draw_cross(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x + 95.f * scale, pos.y + 10.f * scale},
               25.f * scale);

    // analog sticks
    draw_stick_outline(is_shadow ? 0x00000060 : 0xFFFFFFFF,
                       {pos.x + 17.5f * scale, pos.y + 30.f * scale}, 35.0f * scale);
    draw_stick_outline(is_shadow ? 0x00000060 : 0xFFD138FF,
                       {pos.x + 62.5f * scale, pos.y + 30.f * scale}, 35.0f * scale);
    draw_ellipse(is_shadow ? 0x00000060 : 0xFFFFFFFF,
                 {pos.x + (17.5f + tp_mPadMStick.control_analog.x * 10) * scale,
                  pos.y + (30.f - tp_mPadMStick.control_analog.y * 10) * scale},
                 {20.0f * scale, 20.0f * scale});
    draw_ellipse(is_shadow ? 0x00000060 : 0xFFD138FF,
                 {pos.x + (62.5f + tp_mPadSStick.c_analog.x * 10) * scale,
                  pos.y + (30.f - tp_mPadSStick.c_analog.y * 10) * scale},
                 {20.0f * scale, 20.0f * scale});

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

    // stick inputs
    char control_x[5];  // control stick x
    char control_y[5];  // control stick y
    char c_x[5];        // c stick x
    char c_y[5];        // c stick y

    tp_sprintf(control_x, "%d", tp_mPadStatus.control_x);
    tp_sprintf(control_y, "%d", tp_mPadStatus.control_y);
    tp_sprintf(c_x, "%d", tp_mPadStatus.c_x);
    tp_sprintf(c_y, "%d", tp_mPadStatus.c_y);

    Font::gz_renderChars(control_x, pos.x, pos.y + 65.f * scale,
                         is_shadow ? 0x00000060 : 0xFFFFFFFF, false, 13 * scale);
    Font::gz_renderChars(control_y, pos.x + 23.f * scale, pos.y + 65.f * scale,
                         is_shadow ? 0x00000060 : 0xFFFFFFFF, false, 13 * scale);
    Font::gz_renderChars(c_x, pos.x + 45.f * scale, pos.y + 65.f * scale,
                         is_shadow ? 0x00000060 : 0xFFD138FF, false, 13 * scale);
    Font::gz_renderChars(c_y, pos.x + 70.f * scale, pos.y + 65.f * scale,
                         is_shadow ? 0x00000060 : 0xFFD138FF, false, 13 * scale);
#endif
#ifdef WII_PLATFORM
    draw_button_ellipse(Controller::C, 'c', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                        {pos.x + 42.5f * scale, pos.y + 15.f * scale}, {15.f * scale, 10.f * scale},
                        8 * scale);
    draw_button(Controller::Z, 'Z', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                {pos.x + 40.f * scale, pos.y + 30.f * scale}, {20.f * scale, 15.f * scale},
                8 * scale);
    draw_button_ellipse(Controller::A, 'A', is_shadow ? 0x00000060 : 0xBFBFBFFF,
                        {pos.x + 70.f * scale, pos.y + 42.5f * scale}, {15.f * scale, 15.f * scale},
                        8 * scale);
    draw_button(Controller::B, 'B', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                {pos.x + 95.f * scale, pos.y + 40.f * scale}, {10.f * scale, 20.f * scale},
                8 * scale);
    draw_button_ellipse(Controller::MINUS, '-', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                        {pos.x + 115.f * scale, pos.y + 12.5f * scale},
                        {10.f * scale, 10.f * scale}, 8 * scale);
    draw_button_ellipse(Controller::HOME, ' ', is_shadow ? 0x00000060 : 0x00BFFFFF,
                        {pos.x + 130.f * scale, pos.y + 12.5f * scale},
                        {10.f * scale, 10.f * scale}, 8 * scale);
    draw_button_ellipse(Controller::PLUS, '+', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                        {pos.x + 145.f * scale, pos.y + 12.5f * scale},
                        {10.f * scale, 10.f * scale}, 8 * scale);
    draw_button_ellipse(Controller::ONE, '1', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                        {pos.x + 127.5f * scale, pos.y + 30.f * scale},
                        {15.f * scale, 15.f * scale}, 8 * scale);
    draw_button_ellipse(Controller::TWO, '2', is_shadow ? 0x00000060 : 0xFFFFFFFF,
                        {pos.x + 127.5f * scale, pos.y + 50.f * scale},
                        {15.f * scale, 15.f * scale}, 8 * scale);
    draw_cross(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x + 75.f * scale, pos.y + 10.f * scale},
               25.f * scale);

    // analog sticks
    draw_stick_outline(is_shadow ? 0x00000060 : 0xFFFFFFFF,
                       {pos.x + 17.5f * scale, pos.y + 30.f * scale}, 35.0f * scale);
    draw_ellipse(is_shadow ? 0x00000060 : 0xFFFFFFFF,
                 {pos.x + (17.5f + tp_mPad.stick.x * 10) * scale,
                  pos.y + (30.f - tp_mPad.stick.y * 10) * scale},
                 {20.0f * scale, 20.0f * scale});

    // stick inputs
    char control_x[5];  // control stick x
    char control_y[5];  // control stick y

    tp_sprintf(control_x, "%.2f", tp_mPad.stick.x);
    tp_sprintf(control_y, "%.2f", tp_mPad.stick.y);

    Font::gz_renderChars(control_x, pos.x, pos.y + 65.f * scale,
                         is_shadow ? 0x00000060 : 0xFFFFFFFF, false, 8 * scale);
    Font::gz_renderChars(control_y, pos.x + 23.f * scale, pos.y + 65.f * scale,
                         is_shadow ? 0x00000060 : 0xFFFFFFFF, false, 8 * scale);

    // Analog triggers
    Draw::draw_rect_outline(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x, pos.y},
                            {35.f * scale, 7.f * scale}, OUTLINE_WIDTH);
    Draw::draw_rect(is_shadow ? 0x00000060 : tp_mPad.nunchuck_shake > 0.2 ? 0x00FF00FF : 0xFFFFFFFF,
                    {pos.x, pos.y},
                    {35.f * MIN(1.0f, tp_mPad.nunchuck_shake) * scale, 7.f * scale});
    Draw::draw_rect_outline(is_shadow ? 0x00000060 : 0xFFFFFFFF, {pos.x + 117.5f * scale, pos.y},
                            {35.f * scale, 7.f * scale}, OUTLINE_WIDTH);
    Draw::draw_rect(
        is_shadow ? 0x00000060 : tp_mPad.wiimote_shake > 0.2 ? 0x00FF00FF : 0xFFFFFFFF,
        {pos.x + (117.5f + 35.f * (1 - MIN(1.0f, tp_mPad.wiimote_shake))) * scale, pos.y},
        {35.f * MIN(1.0f, tp_mPad.wiimote_shake) * scale, 7.f * scale});

#endif
}

void render() {
    Vec2 pos = {0.f, 0.f};
    pos.x += sprite_offsets[VIEWER_INDEX].x;
    pos.y += sprite_offsets[VIEWER_INDEX].y;
    float scale = 1.0f;  // 0.5f * tp_cos(TP::get_frame_count() / 20.f) + 1.0f;
    if (g_drop_shadows)
        draw_input_viewer({pos.x + 1.f, pos.y + 1.f}, scale, true);
    draw_input_viewer(pos, scale, false);
}
}  // namespace InputViewer