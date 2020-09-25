#include "free_cam.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/math.h"
#include "libtp_c/include/controller.h"
#include "menu.h"

#define ROTATION_SPEED (0.002)
#define FREECAM_FAST_SPEED (2.0)
#define FREECAM_SPEED (0.2)

bool free_cam_active;

bool init_once = false;
double pitch = 0.0;
double yaw = 0.0;

namespace FreeCam {
    void handle_free_cam() {
        if (free_cam_active) {
            auto &cam_target = tp_matrixInfo.matrix_info->target;
            auto &cam_pos = tp_matrixInfo.matrix_info->pos;
            // Freeze the game to prevent control stick inputs to move link
            tp_gameInfo.freeze_game = true;
            // Lock the camera to allow for its movement
            tp_gameInfo.lock_camera = true;

            if (!init_once) {
                // Initialize the pitch and yaw to the current angle of the camera
                yaw = tp_atan2(cam_target.z - cam_pos.z, cam_target.x - cam_pos.x);
                double horizontal = tp_sqrt((cam_target.x - cam_pos.x) * (cam_target.x - cam_pos.x) + (cam_target.z - cam_pos.z) * (cam_target.z - cam_pos.z));
                pitch = tp_atan2(cam_target.y - cam_pos.y, horizontal);
                init_once = true;
            }

            // Calculate the translation
            double dy = tp_mPadSticks.control_y * tp_sin(pitch) + tp_mPadTriggers.trig_L - tp_mPadTriggers.trig_R;
            double dx = tp_mPadSticks.control_y * tp_cos(yaw) * tp_cos(pitch) - tp_mPadSticks.control_x * tp_sin(yaw);
            double dz = tp_mPadSticks.control_y * tp_sin(yaw) * tp_cos(pitch) + tp_mPadSticks.control_x * tp_cos(yaw);

            auto speed = (tp_mPadButton.buttons & Controller::Pad::Z) != 0 ? FREECAM_FAST_SPEED : FREECAM_SPEED;
            // Apply the translation with a speed factor
            cam_pos.x += speed * dx;
            cam_pos.y += speed * dy;
            cam_pos.z += speed * dz;

            // Setup the target to correspond to the pitch and yaw
            cam_target.x = cam_pos.x + tp_cos(yaw) * tp_cos(pitch);
            cam_target.z = cam_pos.z + tp_sin(yaw) * tp_cos(pitch);
            cam_target.y = cam_pos.y + tp_sin(pitch);

            // Update the pitch and yaw
            yaw += tp_mPadSticks.c_x * ROTATION_SPEED;
            yaw = tp_fmod(yaw + 2 * M_PI, 2 * M_PI);
            pitch = MIN(MAX(pitch + tp_mPadSticks.c_y * ROTATION_SPEED, -M_PI / 2 + 0.1), M_PI / 2 - 0.1);
        } else {
            if (init_once) {
                tp_gameInfo.freeze_game = false;
                tp_gameInfo.lock_camera = false;
                init_once = false;
            }
        }
    }
}  // namespace FreeCam