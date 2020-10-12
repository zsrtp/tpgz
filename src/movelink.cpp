#include "movelink.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/math.h"
#include "libtp_c/include/controller.h"
#include "menu.h"
#include "controller.h"

#define M_PI ((double)3.141592653589793238462643383279502884e+00)

#define ROTATION_SPEED (10)
#define CAM_FAST_SPEED (2.0)
#define CAM_SPEED (0.2)
#define DIST_FROM_LINK (600)

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

bool move_link_active;

bool init_once = false;

double pitch = 0.0;
double yaw = 0.0;
float angle = 0.0f;

namespace MoveLink {
    void move_link() {
        if (move_link_active) {
            auto& cam_target = tp_matrixInfo.matrix_info->target;
            auto& cam_pos = tp_matrixInfo.matrix_info->pos;

            auto& link_pos = tp_zelAudio.link_debug_ptr->position;
            auto& link_angle = tp_zelAudio.link_debug_ptr->facing;

            // Freeze the game to prevent control stick inputs to move link
            tp_gameInfo.freeze_game = true;
            // Lock the camera to allow for its movement
            tp_gameInfo.lock_camera = true;

            if (!init_once) {
                // Initialize the pitch and yaw to the current angle of the camera
                yaw = tp_atan2(cam_target.z - cam_pos.z, cam_target.x - cam_pos.x);
                double horizontal = tp_sqrt((cam_target.x - cam_pos.x) * (cam_target.x - cam_pos.x) + (cam_target.z - cam_pos.z) * (cam_target.z - cam_pos.z));
                pitch = tp_atan2(cam_target.y - cam_pos.y, horizontal);
                angle = (float)link_angle / 65536.f * (2 * M_PI);
                init_once = true;
            }

            // Calculate the translation
            double dy = tp_mPadSticks.c_y;
            double dx = tp_mPadSticks.control_y * tp_cos(yaw) * tp_cos(pitch) - tp_mPadSticks.control_x * tp_sin(yaw);
            double dz = tp_mPadSticks.control_y * tp_sin(yaw) * tp_cos(pitch) + tp_mPadSticks.control_x * tp_cos(yaw);

            auto speed = (tp_mPadButton.buttons & Controller::Pad::Z) != 0 ? CAM_FAST_SPEED : CAM_SPEED;
            // Apply the translation with a speed factor
            link_pos.x += speed * dx;
            link_pos.y += speed * dy;
            link_pos.z += speed * dz;

            // Change facing angle with c stick
            if (Controller::button_is_held(Controller::Pad::R)) {
                if (Controller::button_is_pressed(Controller::DPAD_RIGHT)) {
                    link_angle++;
                }
                if (Controller::button_is_pressed(Controller::DPAD_LEFT)) {
                    link_angle--;
                }
            }
			
            link_angle += tp_mPadSticks.c_x * ROTATION_SPEED;

            // Fix Camera behind link
            cam_target.x = link_pos.x;
            cam_target.y = link_pos.y + 200.f;
            cam_target.z = link_pos.z;
            cam_pos.z = link_pos.z - DIST_FROM_LINK * tp_cos(angle);
            cam_pos.x = link_pos.x - DIST_FROM_LINK * tp_sin(angle);
            cam_pos.y = link_pos.y + 200.f;
        } else {
            if (init_once) {
                tp_gameInfo.freeze_game = false;
                tp_gameInfo.lock_camera = false;
                init_once = false;
            }
        }
    }
}  // namespace MoveLink