#include "features/movelink/include/movelink.h"
#include <cstdio>
#include "global_data.h"
#include "libtp_c/include/msl_c/math.h"
#include "settings.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"
#include "rels/include/defines.h"

#define ROTATION_SPEED (30)
#define ROTATION_FAST_SPEED (80)
#define ROTATION_VERY_FAST_SPEED (800)
#define CAM_SPEED (1.0)
#define CAM_FAST_SPEED (2.5)
#define CAM_VERY_FAST_SPEED (10.0)
#define DIST_FROM_LINK (600)

#ifdef GCN_PLATFORM
#define CONTROL_Y (mPadStatus.stick_y)
#define CONTROL_X (mPadStatus.stick_x)
#define VERTICAL_DISPLACEMENT (mPadStatus.substick_y)
#define HORIZONTAL_DISPLACEMENT -(mPadStatus.substick_x)
#define SPEED_PREDICATE_1 (mPadButton.mButton & CButton::Z)
#define SPEED_PREDICATE_2 (mPadButton.mButton & CButton::R)
#define LOCK_CAMERA (mPadButton.mButton & CButton::L)
#endif

#ifdef WII_PLATFORM
#define CONTROL_Y ((mPad.mHoldButton & CButton::C) == 0 ? mPad.stick.y * 72 : 0)
#define CONTROL_X ((mPad.mHoldButton & CButton::C) == 0 ? -mPad.stick.x * 72 : 0)
#define VERTICAL_DISPLACEMENT ((mPad.mHoldButton & CButton::C) != 0 ? mPad.stick.y * 59 : 0)
#define HORIZONTAL_DISPLACEMENT ((mPad.mHoldButton & CButton::C) != 0 ? -mPad.stick.x * 59 : 0)
#define SPEED_PREDICATE_1 (mPadButton.mButton & CButton::Z)
#define SPEED_PREDICATE_2 (mPadButton.mButton & CButton::MINUS)
#define LOCK_CAMERA (mPadButton.mButton & CButton::A)
#endif

#define WHITE_RGBA 0xFFFFFFFF
#define LINE_X_OFFSET 20.0f

namespace MoveLink {

double pitch = 0.0;
double yaw = 0.0;
float angle = 0.0f;
bool event_halt_already_on = false;

KEEP_FUNC void execute() {
    if (g_moveLinkEnabled) {
        auto& cam_target = matrixInfo.matrix_info->target;
        auto& cam_pos = matrixInfo.matrix_info->pos;

        cXyz& link_pos = dComIfGp_getPlayer()->current.pos;
        int16_t& link_horizontal_angle = dComIfGp_getPlayer()->shape_angle.y;
        int16_t& link_verticle_angle = dComIfGp_getPlayer()->shape_angle.x;

        // Freeze the game to prevent control stick inputs to move link
        dComIfGp_getEvent().mHalt ? event_halt_already_on = true : dComIfGp_getEvent().mHalt = true;
        
        // Lock the camera to allow for its movement
        dComIfGp_getEventManager().mCameraPlay = 1;

        // Set Link momentum to 0
        cXyz tmp(0.0f, 0.0f, 0.0f);
        dComIfGp_getPlayer()->speed = tmp;

        if (!LOCK_CAMERA) {
            angle = (float)link_horizontal_angle / 65536.f * (2 * M_PI);
        }

        // Fix Camera behind link
        cam_target.x = link_pos.x;
        cam_target.y = link_pos.y + 200.f;
        cam_target.z = link_pos.z;
        cam_pos.z = link_pos.z - DIST_FROM_LINK * cos(angle);
        cam_pos.x = link_pos.x - DIST_FROM_LINK * sin(angle);
        cam_pos.y = link_pos.y + 200.f;

        // Calculate the pitch and yaw
        yaw = atan2(cam_target.z - cam_pos.z, cam_target.x - cam_pos.x);
        double horizontal = sqrt((cam_target.x - cam_pos.x) * (cam_target.x - cam_pos.x) +
                                    (cam_target.z - cam_pos.z) * (cam_target.z - cam_pos.z));
        pitch = atan2(cam_target.y - cam_pos.y, horizontal);

        // Calculate the translation
        double dy = LOCK_CAMERA ? 0.0f : VERTICAL_DISPLACEMENT;
        double dx = CONTROL_Y * cos(yaw) * cos(pitch) - CONTROL_X * sin(yaw);
        double dz = CONTROL_Y * sin(yaw) * cos(pitch) + CONTROL_X * cos(yaw);

        auto move_speed = SPEED_PREDICATE_1 != 0 ? SPEED_PREDICATE_2 != 0 ? CAM_VERY_FAST_SPEED : CAM_FAST_SPEED : CAM_SPEED;
        auto cam_speed = SPEED_PREDICATE_1 != 0 ? SPEED_PREDICATE_2 != 0 ? ROTATION_VERY_FAST_SPEED : ROTATION_FAST_SPEED : ROTATION_SPEED;

        // Apply the translation with a speed factor
        link_pos.x += move_speed * dx;
        link_pos.y += move_speed * dy;
        link_pos.z += move_speed * dz;

        // Change facing angle with c stick
        if (LOCK_CAMERA) { 
            link_verticle_angle -= -VERTICAL_DISPLACEMENT * cam_speed;
            link_horizontal_angle -= -HORIZONTAL_DISPLACEMENT * cam_speed;
        } else {
            link_horizontal_angle -= HORIZONTAL_DISPLACEMENT * cam_speed;
        }

    } else {
        if (event_halt_already_on) {
            dComIfGp_getEvent().mHalt = false;
            dComIfGp_getEventManager().mCameraPlay = 0;
        }
    }
}
}  // namespace MoveLink