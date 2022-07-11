#include "movelink.h"
#include "libtp_c/include/msl_c/math.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/settings_menu.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"

#define ROTATION_SPEED (10)
#define CAM_FAST_SPEED (2.0)
#define CAM_SPEED (0.2)
#define DIST_FROM_LINK (600)

#ifdef GCN_PLATFORM
#define CONTROL_Y (tp_mPadStatus.stick_y)
#define CONTROL_X (tp_mPadStatus.stick_x)
#define VERTICAL_DISPLACEMENT (tp_mPadStatus.substick_y)
#define HORIZONTAL_DISPLACEMENT (tp_mPadStatus.substick_x)
#define SPEED_PREDICATE (tp_mPadButton.mButton & CButton::Z)
#endif

#ifdef WII_PLATFORM
#define CONTROL_Y ((tp_mPad.mHoldButton & GZPad::C) == 0 ? tp_mPad.stick.y * 72 : 0)
#define CONTROL_X ((tp_mPad.mHoldButton & GZPad::C) == 0 ? -tp_mPad.stick.x * 72 : 0)
#define VERTICAL_DISPLACEMENT                                                                      \
    ((tp_mPad.mHoldButton & GZPad::C) != 0 ? tp_mPad.stick.y * 59 : 0)
#define HORIZONTAL_DISPLACEMENT                                                                    \
    ((tp_mPad.mHoldButton & GZPad::C) != 0 ? -tp_mPad.stick.x * 59 : 0)
#define SPEED_PREDICATE (tp_mPad.mHoldButton & GZPad::Z)
#endif

#define WHITE_RGBA 0xFFFFFFFF
#define LINE_X_OFFSET 20.0f

bool g_moveLinkEnabled;

static Cursor cursor;

/* bool link_angle_selected = false;
bool link_x_selected = false;
bool link_y_selected = false;
bool link_z_selected = false; */

bool init_once = false;

double pitch = 0.0;
double yaw = 0.0;
float angle = 0.0f;

void MoveLink::execute() {
    if (g_moveLinkEnabled) {
        auto& cam_target = tp_matrixInfo.matrix_info->target;
        auto& cam_pos = tp_matrixInfo.matrix_info->pos;

        cXyz& link_pos = dComIfGp_getPlayer()->mCurrent.mPosition;
        int16_t& link_angle = dComIfGp_getPlayer()->mCollisionRot.mY;

        // Freeze the game to prevent control stick inputs to move link
        dComIfGp_getEvent().mHalt = true;

        // Lock the camera to allow for its movement
        dComIfGp_getEventManager().mCameraPlay = 1;

        // Set Link momentum to 0
        cXyz tmp(0.0f, 0.0f, 0.0f);
        dComIfGp_getPlayer()->mSpeed = tmp;

        if (!init_once) {
            angle = (float)link_angle / 65536.f * (2 * M_PI);
        }

        // Fix Camera behind link
        cam_target.x = link_pos.x;
        cam_target.y = link_pos.y + 200.f;
        cam_target.z = link_pos.z;
        cam_pos.z = link_pos.z - DIST_FROM_LINK * tp_cos(angle);
        cam_pos.x = link_pos.x - DIST_FROM_LINK * tp_sin(angle);
        cam_pos.y = link_pos.y + 200.f;

        if (!init_once) {
            // Initialize the pitch and yaw to the current angle of the camera
            yaw = tp_atan2(cam_target.z - cam_pos.z, cam_target.x - cam_pos.x);
            double horizontal = tp_sqrt((cam_target.x - cam_pos.x) * (cam_target.x - cam_pos.x) +
                                        (cam_target.z - cam_pos.z) * (cam_target.z - cam_pos.z));
            pitch = tp_atan2(cam_target.y - cam_pos.y, horizontal);
            init_once = true;
        }

        // Calculate the translation
        double dy = VERTICAL_DISPLACEMENT;
        double dx = CONTROL_Y * tp_cos(yaw) * tp_cos(pitch) - CONTROL_X * tp_sin(yaw);
        double dz = CONTROL_Y * tp_sin(yaw) * tp_cos(pitch) + CONTROL_X * tp_cos(yaw);

        auto speed = SPEED_PREDICATE != 0 ? CAM_FAST_SPEED : CAM_SPEED;

        // Apply the translation with a speed factor
        link_pos.x += speed * dx;
        link_pos.y += speed * dy;
        link_pos.z += speed * dz;

        // Change facing angle with c stick
        link_angle -= HORIZONTAL_DISPLACEMENT * ROTATION_SPEED;

    } else {
        if (init_once) {
            dComIfGp_getEvent().mHalt = false;
            dComIfGp_getEventManager().mCameraPlay = 0;
            init_once = false;
        }
    }
}

/* void render_info_input() {
    char link_angle[20];
    char link_x[20];
    char link_y[20];
    char link_z[20];
    uint8_t cursor_x_max = 1;

    tp_sprintf(link_angle, "angle: %05d", (uint16_t)dComIfGp_getPlayer()->mCollisionRot.mY);
    tp_sprintf(link_x, "x-pos: % 010.2f", dComIfGp_getPlayer()->mCurrent.mPosition.x);
    tp_sprintf(link_y, "y-pos: % 010.2f", dComIfGp_getPlayer()->mCurrent.mPosition.y);
    tp_sprintf(link_z, "z-pos: % 010.2f", dComIfGp_getPlayer()->mCurrent.mPosition.z);

    if (link_angle_selected) {
        cursor_x_max = 5;
        if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
            switch (cursor.x) {
            case 0: {
                dComIfGp_getPlayer()->mCollisionRot.mY += 10000;
                break;
            }
            case 1: {
                dComIfGp_getPlayer()->mCollisionRot.mY += 1000;
                break;
            }
            case 2: {
                dComIfGp_getPlayer()->mCollisionRot.mY += 100;
                break;
            }
            case 3: {
                dComIfGp_getPlayer()->mCollisionRot.mY += 10;
                break;
            }
            case 4: {
                dComIfGp_getPlayer()->mCollisionRot.mY += 1;
                break;
            }
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
            switch (cursor.x) {
            case 0: {
                dComIfGp_getPlayer()->mCollisionRot.mY -= 10000;
                break;
            }
            case 1: {
                dComIfGp_getPlayer()->mCollisionRot.mY -= 1000;
                break;
            }
            case 2: {
                dComIfGp_getPlayer()->mCollisionRot.mY -= 100;
                break;
            }
            case 3: {
                dComIfGp_getPlayer()->mCollisionRot.mY -= 10;
                break;
            }
            case 4: {
                dComIfGp_getPlayer()->mCollisionRot.mY -= 1;
                break;
            }
            }
        }

        Font::GZ_drawChar(link_angle[0], LINE_X_OFFSET, 80.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_angle[1], LINE_X_OFFSET + 8.0f, 80.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_angle[2], LINE_X_OFFSET + 16.0f, 80.0f, WHITE_RGBA,
                            g_dropShadows);
        Font::GZ_drawChar(link_angle[3], LINE_X_OFFSET + 26.0f, 80.0f, WHITE_RGBA,
                            g_dropShadows);
        Font::GZ_drawChar(link_angle[4], LINE_X_OFFSET + 32.0f, 80.0f, WHITE_RGBA,
                            g_dropShadows);
        Font::GZ_drawChar(link_angle[5], LINE_X_OFFSET + 40.0f, 80.0f, WHITE_RGBA,
                            g_dropShadows);
        Font::GZ_drawChar(link_angle[6], LINE_X_OFFSET + 48.0f, 80.0f, WHITE_RGBA,
                            g_dropShadows);

        Font::GZ_drawChar(link_angle[7], LINE_X_OFFSET + 56.0f, 80.0f,
                            (cursor.x == 0 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_angle[8], LINE_X_OFFSET + 65.0f, 80.0f,
                            (cursor.x == 1 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_angle[9], LINE_X_OFFSET + 74.0f, 80.0f,
                            (cursor.x == 2 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_angle[10], LINE_X_OFFSET + 83.0f, 80.0f,
                            (cursor.x == 3 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_angle[11], LINE_X_OFFSET + 92.0f, 80.0f,
                            (cursor.x == 4 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
    } else {
        Font::GZ_drawStr(link_angle, LINE_X_OFFSET, 80.0f,
                             (cursor.y == 0 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
    }

    if (link_x_selected) {
        if (dComIfGp_getPlayer()->mCurrent.mPosition.x <= -999998.99f) {
            dComIfGp_getPlayer()->mCurrent.mPosition.x = -999998.99f;
        } else if (dComIfGp_getPlayer()->mCurrent.mPosition.x >= 999998.99f) {
            dComIfGp_getPlayer()->mCurrent.mPosition.x = 999998.99f;
        }
        cursor_x_max = 9;
        if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
            switch (cursor.x) {
            case 0: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x += 100000.0f;
                break;
            }
            case 1: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x += 10000.0f;
                break;
            }
            case 2: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x += 1000.0f;
                break;
            }
            case 3: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x += 100.0f;
                break;
            }
            case 4: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x += 10.0f;
                break;
            }
            case 5: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x += 1.0f;
                break;
            }
            case 7: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x += 0.10f;
                break;
            }
            case 8: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x += 0.01f;
                break;
            }
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
            switch (cursor.x) {
            case 0: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x -= 100000.0f;
                break;
            }
            case 1: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x -= 10000.0f;
                break;
            }
            case 2: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x -= 1000.0f;
                break;
            }
            case 3: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x -= 100.0f;
                break;
            }
            case 4: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x -= 10.0f;
                break;
            }
            case 5: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x -= 1.0f;
                break;
            }
            case 7: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x -= 0.10f;
                break;
            }
            case 8: {
                dComIfGp_getPlayer()->mCurrent.mPosition.x -= 0.01f;
                break;
            }
            }
        }

        Font::GZ_drawChar(link_x[0], LINE_X_OFFSET, 100.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_x[1], LINE_X_OFFSET + 10.0f, 100.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_x[2], LINE_X_OFFSET + 16.0f, 100.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_x[3], LINE_X_OFFSET + 24.0f, 100.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_x[4], LINE_X_OFFSET + 34.0f, 100.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_x[5], LINE_X_OFFSET + 44.0f, 100.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_x[6], LINE_X_OFFSET + 52.0f, 100.0f, WHITE_RGBA, g_dropShadows);

        Font::GZ_drawChar(link_x[7], LINE_X_OFFSET + 56.0f, 100.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_x[8], LINE_X_OFFSET + 66.0f, 100.0f,
                            (cursor.x == 0 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_x[9], LINE_X_OFFSET + 76.0f, 100.0f,
                            (cursor.x == 1 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_x[10], LINE_X_OFFSET + 86.0f, 100.0f,
                            (cursor.x == 2 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_x[11], LINE_X_OFFSET + 96.0f, 100.0f,
                            (cursor.x == 3 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_x[12], LINE_X_OFFSET + 106.0f, 100.0f,
                            (cursor.x == 4 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_x[13], LINE_X_OFFSET + 116.0f, 100.0f,
                            (cursor.x == 5 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_x[14], LINE_X_OFFSET + 126.0f, 100.0f,
                            (cursor.x == 6 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_x[15], LINE_X_OFFSET + 131.0f, 100.0f,
                            (cursor.x == 7 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_x[16], LINE_X_OFFSET + 141.0f, 100.0f,
                            (cursor.x == 8 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
    } else {
        Font::GZ_drawStr(link_x, LINE_X_OFFSET, 100.0f,
                             (cursor.y == 1 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
    }

    if (link_y_selected) {
        if (dComIfGp_getPlayer()->mCurrent.mPosition.y <= -999998.99f) {
            dComIfGp_getPlayer()->mCurrent.mPosition.y = -999998.99f;
        } else if (dComIfGp_getPlayer()->mCurrent.mPosition.y >= 999998.99f) {
            dComIfGp_getPlayer()->mCurrent.mPosition.y = 999998.99f;
        }
        cursor_x_max = 9;
        if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
            switch (cursor.x) {
            case 0: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y += 100000.0f;
                break;
            }
            case 1: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y += 10000.0f;
                break;
            }
            case 2: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y += 1000.0f;
                break;
            }
            case 3: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y += 100.0f;
                break;
            }
            case 4: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y += 10.0f;
                break;
            }
            case 5: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y += 1.0f;
                break;
            }
            case 7: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y += 0.10f;
                break;
            }
            case 8: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y += 0.01f;
                break;
            }
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
            switch (cursor.x) {
            case 0: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y -= 100000.0f;
                break;
            }
            case 1: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y -= 10000.0f;
                break;
            }
            case 2: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y -= 1000.0f;
                break;
            }
            case 3: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y -= 100.0f;
                break;
            }
            case 4: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y -= 10.0f;
                break;
            }
            case 5: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y -= 1.0f;
                break;
            }
            case 7: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y -= 0.10f;
                break;
            }
            case 8: {
                dComIfGp_getPlayer()->mCurrent.mPosition.y -= 0.01f;
                break;
            }
            }
        }

        Font::GZ_drawChar(link_y[0], LINE_X_OFFSET, 120.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_y[1], LINE_X_OFFSET + 10.0f, 120.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_y[2], LINE_X_OFFSET + 16.0f, 120.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_y[3], LINE_X_OFFSET + 24.0f, 120.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_y[4], LINE_X_OFFSET + 34.0f, 120.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_y[5], LINE_X_OFFSET + 44.0f, 120.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_y[6], LINE_X_OFFSET + 52.0f, 120.0f, WHITE_RGBA, g_dropShadows);

        Font::GZ_drawChar(link_y[7], LINE_X_OFFSET + 56.0f, 120.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_y[8], LINE_X_OFFSET + 66.0f, 120.0f,
                            (cursor.x == 0 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_y[9], LINE_X_OFFSET + 76.0f, 120.0f,
                            (cursor.x == 1 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_y[10], LINE_X_OFFSET + 86.0f, 120.0f,
                            (cursor.x == 2 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_y[11], LINE_X_OFFSET + 96.0f, 120.0f,
                            (cursor.x == 3 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_y[12], LINE_X_OFFSET + 106.0f, 120.0f,
                            (cursor.x == 4 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_y[13], LINE_X_OFFSET + 116.0f, 120.0f,
                            (cursor.x == 5 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_y[14], LINE_X_OFFSET + 126.0f, 120.0f,
                            (cursor.x == 6 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_y[15], LINE_X_OFFSET + 131.0f, 120.0f,
                            (cursor.x == 7 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_y[16], LINE_X_OFFSET + 141.0f, 120.0f,
                            (cursor.x == 8 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
    } else {
        Font::GZ_drawStr(link_y, LINE_X_OFFSET, 120.0f,
                             (cursor.y == 2 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
    }

    if (link_z_selected) {
        if (dComIfGp_getPlayer()->mCurrent.mPosition.z <= -999998.99f) {
            dComIfGp_getPlayer()->mCurrent.mPosition.z = -999998.99f;
        } else if (dComIfGp_getPlayer()->mCurrent.mPosition.z >= 999998.99f) {
            dComIfGp_getPlayer()->mCurrent.mPosition.z = 999998.99f;
        }
        cursor_x_max = 9;
        if (GZ_getButtonRepeat(GZPad::DPAD_UP)) {
            switch (cursor.x) {
            case 0: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z += 100000.0f;
                break;
            }
            case 1: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z += 10000.0f;
                break;
            }
            case 2: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z += 1000.0f;
                break;
            }
            case 3: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z += 100.0f;
                break;
            }
            case 4: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z += 10.0f;
                break;
            }
            case 5: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z += 1.0f;
                break;
            }
            case 7: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z += 0.10f;
                break;
            }
            case 8: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z += 0.01f;
                break;
            }
            }
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_DOWN)) {
            switch (cursor.x) {
            case 0: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z -= 100000.0f;
                break;
            }
            case 1: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z -= 10000.0f;
                break;
            }
            case 2: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z -= 1000.0f;
                break;
            }
            case 3: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z -= 100.0f;
                break;
            }
            case 4: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z -= 10.0f;
                break;
            }
            case 5: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z -= 1.0f;
                break;
            }
            case 7: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z -= 0.10f;
                break;
            }
            case 8: {
                dComIfGp_getPlayer()->mCurrent.mPosition.z -= 0.01f;
                break;
            }
            }
        }

        Font::GZ_drawChar(link_z[0], LINE_X_OFFSET, 140.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_z[1], LINE_X_OFFSET + 10.0f, 140.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_z[2], LINE_X_OFFSET + 16.0f, 140.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_z[3], LINE_X_OFFSET + 24.0f, 140.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_z[4], LINE_X_OFFSET + 34.0f, 140.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_z[5], LINE_X_OFFSET + 44.0f, 140.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_z[6], LINE_X_OFFSET + 52.0f, 140.0f, WHITE_RGBA, g_dropShadows);

        Font::GZ_drawChar(link_z[7], LINE_X_OFFSET + 56.0f, 140.0f, WHITE_RGBA, g_dropShadows);
        Font::GZ_drawChar(link_z[8], LINE_X_OFFSET + 66.0f, 140.0f,
                            (cursor.x == 0 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_z[9], LINE_X_OFFSET + 76.0f, 140.0f,
                            (cursor.x == 1 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_z[10], LINE_X_OFFSET + 86.0f, 140.0f,
                            (cursor.x == 2 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_z[11], LINE_X_OFFSET + 96.0f, 140.0f,
                            (cursor.x == 3 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_z[12], LINE_X_OFFSET + 106.0f, 140.0f,
                            (cursor.x == 4 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_z[13], LINE_X_OFFSET + 116.0f, 140.0f,
                            (cursor.x == 5 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_z[14], LINE_X_OFFSET + 126.0f, 140.0f,
                            (cursor.x == 6 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_z[15], LINE_X_OFFSET + 131.0f, 140.0f,
                            (cursor.x == 7 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
        Font::GZ_drawChar(link_z[16], LINE_X_OFFSET + 141.0f, 140.0f,
                            (cursor.x == 8 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
    } else {
        Font::GZ_drawStr(link_z, LINE_X_OFFSET, 140.0f,
                             (cursor.y == 3 ? CURSOR_RGBA : WHITE_RGBA), g_dropShadows);
    }

    if (GZ_getButtonRepeat(GZPad::B)) {
        if (link_angle_selected) {
            link_angle_selected = false;
        } else if (link_x_selected) {
            link_x_selected = false;
        } else if (link_y_selected) {
            link_y_selected = false;
        } else if (link_z_selected) {
            link_z_selected = false;
        }
        cursor_x_max = 1;
        lock_cursor_y = false;
    }

    if (GZ_getButtonRepeat(GZPad::A)) {
        switch (cursor.y) {
        case 0: {
            link_angle_selected = true;
            break;
        }
        case 1: {
            link_x_selected = true;
            break;
        }
        case 2: {
            link_y_selected = true;
            break;
        }
        case 3: {
            link_z_selected = true;
            break;
        }
        }
        lock_cursor_y = true;
    }

    move_cursor(cursor, 4, cursor_x_max, lock_cursor_x, lock_cursor_y, true);
}; */