#include "free_cam.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/msl_c/math.h"
#include "menu.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"
#include "rels/include/defines.h"

#define ROTATION_SPEED (0.002)
#define FREECAM_FAST_SPEED (2.0)
#define FREECAM_SPEED (0.2)

bool g_freeCamEnabled;

#ifdef GCN_PLATFORM
#define CONTROL_Y (mPadStatus.stick_y)
#define CONTROL_X (mPadStatus.stick_x)
#define VERTICAL_DISPLACEMENT (mPadStatus.trigger_left - mPadStatus.trigger_right)
#define SPEED_PREDICATE (mPadButton.mButton & CButton::Z)
#define PITCH_CONTROL (mPadStatus.substick_y)
#define YAW_CONTROL (mPadStatus.substick_x)
#endif

#ifdef WII_PLATFORM
#define CONTROL_Y ((mPad.mHoldButton & CButton::C) == 0 ? mPad.stick.y * 0x48 : 0)
#define CONTROL_X ((mPad.mHoldButton & CButton::C) == 0 ? -mPad.stick.x * 0x48 : 0)
#define VERTICAL_DISPLACEMENT                                                                      \
    ((mPad.mHoldButton & CButton::DPAD_UP ? 75 : 0) -                                              \
     (mPad.mHoldButton & CButton::DPAD_DOWN ? 75 : 0))
#define SPEED_PREDICATE (mPad.mHoldButton & CButton::Z)
#define PITCH_CONTROL ((mPad.mHoldButton & CButton::C) != 0 ? mPad.stick.y * 0x3B : 0)
#define YAW_CONTROL ((mPad.mHoldButton & CButton::C) != 0 ? -mPad.stick.x * 0x3B : 0)
#endif

namespace FreeCam {
bool init_once = false;
double pitch = 0.0;
double yaw = 0.0;

KEEP_FUNC void execute() {
    if (g_freeCamEnabled) {
        auto& cam_target = matrixInfo.matrix_info->target;
        auto& cam_pos = matrixInfo.matrix_info->pos;
        // Freeze the game to prevent control stick inputs to move link
        dComIfGp_getEvent().mHalt = true;
        // Lock the camera to allow for its movement
        dComIfGp_getEventManager().mCameraPlay = 1;

        if (!init_once) {
            // Initialize the pitch and yaw to the current angle of the camera
            yaw = atan2(cam_target.z - cam_pos.z, cam_target.x - cam_pos.x);
            double horizontal = sqrt((cam_target.x - cam_pos.x) * (cam_target.x - cam_pos.x) +
                                     (cam_target.z - cam_pos.z) * (cam_target.z - cam_pos.z));
            pitch = atan2(cam_target.y - cam_pos.y, horizontal);
            init_once = true;
        }

        // Calculate the translation
        double dy = CONTROL_Y * sin(pitch) + VERTICAL_DISPLACEMENT;
        double dx = CONTROL_Y * cos(yaw) * cos(pitch) - CONTROL_X * sin(yaw);
        double dz = CONTROL_Y * sin(yaw) * cos(pitch) + CONTROL_X * cos(yaw);

        auto speed = SPEED_PREDICATE != 0 ? FREECAM_FAST_SPEED : FREECAM_SPEED;
        // Apply the translation with a speed factor
        cam_pos.x += speed * dx;
        cam_pos.y += speed * dy;
        cam_pos.z += speed * dz;

        // Setup the target to correspond to the pitch and yaw
        cam_target.x = cam_pos.x + cos(yaw) * cos(pitch);
        cam_target.z = cam_pos.z + sin(yaw) * cos(pitch);
        cam_target.y = cam_pos.y + sin(pitch);

        // Update the pitch and yaw
        yaw += YAW_CONTROL * ROTATION_SPEED;
        yaw = fmod(yaw + 2 * M_PI, 2 * M_PI);
        pitch = MIN(MAX((pitch + PITCH_CONTROL * ROTATION_SPEED), -M_PI / 2 + 0.1), M_PI / 2 - 0.1);
    } else {
        if (init_once) {
            dComIfGp_getEvent().mHalt = false;
            dComIfGp_getEventManager().mCameraPlay = 0;
            init_once = false;
        }
    }
}
}  // namespace FreeCam
