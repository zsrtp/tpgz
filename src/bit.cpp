#ifdef WII_PLATFORM
#include "bit.h"
#include "libtp_c/include/msl_c/math.h.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/msl_c/string.h"
#include "fifo_queue.h"
#include "controller.h"
#include "fifo_queue.h"
#include "fs.h"
#include "font.h"

#define VOID_HEIGHT -2098.58
#define NORMAL_ACC -3.4
#define NORMAL_TERM_VEL -200.0
#define BOOTS_ACC -7.65
#define BOOTS_TERM_VEL -300.0
#define TARGET_FRAME 28

bool inject_bit_flag = false;
extern Font font;

namespace BiTIndicator {
using namespace Controller;

static char buf[30];

void set_camera_angle_position() {
    dComIfGp_getPlayer()->mCurrent.mPosition = {466.622467f, 319.770752f, -11651.3867f};
    dComIfGp_getPlayer()->mCollisionRot.mY = 32000;
    tp_matrixInfo.matrix_info->target = {465.674622f, 421.052704f, -11651.0684f};
    tp_matrixInfo.matrix_info->pos = {735.525391f, 524.418701f, -11576.4746f};
}

void run() {
    double dt = 0;

    if (dComIfGp_getPlayer()) {
        const bool has_boots = (dComIfGp_getPlayer()->mNoResetFlg0 & 0x02) != 0;
        const double term_vel = has_boots ? BOOTS_TERM_VEL : NORMAL_TERM_VEL;
        const double acc = has_boots ? BOOTS_ACC : NORMAL_ACC;
        const double v_y1 = dComIfGp_getPlayer()->mSpeed.y;
        const double dist_from_last_ground =
            (dComIfGp_getPlayer()->mCurrent.mPosition.y - dComIfGp_getPlayer()->field_0x33c8);

        // Calculate how many frames before reaching terminal velocity
        double dt_1 = (term_vel - v_y1) / acc;
        // Calculate how much height we will lose during that period
        double x_dt_1 = dist_from_last_ground + v_y1 * dt_1 + 0.5 * acc * dt_1 * dt_1;

        // If we reach terminal velocity after the voiding point, ...
        if (x_dt_1 <= VOID_HEIGHT) {
            // ... just calculate the time remaining before void using the quadratic formula
            dt =
                (-v_y1 -
                 tp_sqrt((double)(v_y1 * v_y1 + 2 * acc * (VOID_HEIGHT - dist_from_last_ground)))) /
                    acc +
                0.5;
        } else {
            // ... else, the time remaining before the void is the time to reach terminal velocity +
            // linear time at velocity
            dt = dt_1 + (VOID_HEIGHT - x_dt_1) / term_vel + 0.5;
        }

        // if (tp_homeMenuSts.is_visible == 0 && !tp_fopScnRq.isLoading) {
        //     sprintf(buf, "frames before void: %d", (int)dt);
        //     log.PrintLog(buf, DEBUG);
        // }

        if (tp_strcmp((const char*)tp_gameInfo.current_stage, "F_SP104") == 0 &&
            button_is_down(HOME) && tp_homeMenuSts.is_visible == 0 && !tp_fopScnRq.isLoading) {
            if ((int)dt == TARGET_FRAME) {
                tp_sprintf(buf, "Got it");
            }
            if ((int)dt > TARGET_FRAME) {
                tp_sprintf(buf, "%d frames early", (int)dt - TARGET_FRAME);
            }
            if ((int)dt < TARGET_FRAME) {
                tp_sprintf(buf, "%d frames late", TARGET_FRAME - (int)dt);
            }
            FIFOQueue::push(buf, Queue);
        }
    }
}
}  // namespace BiTIndicator
#endif