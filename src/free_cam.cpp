#include "free_cam.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "menu.h"

#define M_PI ((double)3.141592653589793238462643383279502884e+00)

#define ROTATION_SPEED (0.002)
#define FREECAM_SPEED (0.5)

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define tp_atan2 ((double(*)(double,double))(0x8036c720))
#define tp_sqrt ((double(*)(double))(0x8036ca54))
#define tp_sin ((double(*)(double))(0x8036c590))
#define tp_cos ((double(*)(double))(0x8036c028))
#define tp_fmod ((double(*)(double,double))(0x8036c760))

bool init_once = false;
double pitch = 0.0;
double yaw = 0.0;

namespace FreeCam {
	void handle_free_cam() {
		if (ToolItems[Tools::FREE_CAM_INDEX].active) {
			auto& cam_target = *((Vec3*)& tp_matrixInfo.matrix_info->target);
			auto& cam_pos = *((Vec3*)& tp_matrixInfo.matrix_info->pos);
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
			double dy = tp_mPadSticks.control_y * tp_sin(pitch);
			double dx = tp_mPadSticks.control_y * tp_cos(yaw) * tp_cos(pitch) - tp_mPadSticks.control_x * tp_sin(yaw);
			double dz = tp_mPadSticks.control_y * tp_sin(yaw) * tp_cos(pitch) + tp_mPadSticks.control_x * tp_cos(yaw);

			// Apply the translation with a speed factor
			cam_pos.x += FREECAM_SPEED * dx;
			cam_pos.y += FREECAM_SPEED * dy;
			cam_pos.z += FREECAM_SPEED * dz;

			// Setup the target to correspond to the pitch and yaw
			cam_target.x = cam_pos.x + tp_cos(yaw) * tp_cos(pitch);
			cam_target.z = cam_pos.z + tp_sin(yaw) * tp_cos(pitch);
			cam_target.y = cam_pos.y + tp_sin(pitch);

			// Update the pitch and yaw
			yaw += tp_mPadSticks.c_x * ROTATION_SPEED;
			yaw = tp_fmod(yaw + 2 * M_PI, 2 * M_PI);
			pitch = MIN(MAX(pitch + tp_mPadSticks.c_y * ROTATION_SPEED, -M_PI / 2), M_PI / 2);
		}
		else {
			if (init_once) {
				tp_gameInfo.freeze_game = false;
				tp_gameInfo.lock_camera = false;
				init_once = false;
			}
		}
	}
} // namespace FreeCam