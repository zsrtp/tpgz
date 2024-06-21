#ifdef WII_PLATFORM
#include "bit.h"
#include <cstdio>
#include "libtp_c/include/msl_c/math.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "libtp_c/include/m_Do/m_Do_audio.h"
#include "fifo_queue.h"
#include "commands.h"
#include "controller.h"
#include "fs.h"
#include "font.h"
#include "save_manager.h"
#include "settings.h"

#define VOID_HEIGHT -2098.58
#define NORMAL_ACC -3.4
#define NORMAL_TERM_VEL -200.0
#define BOOTS_ACC -7.65
#define BOOTS_TERM_VEL -300.0
#define TARGET_FRAME 28

#define LAST_Y_GROUND_POS (dComIfGp_getPlayer()->field_0x3404)

#ifdef WII_PLATFORM
KEEP_FUNC void GZCmd_bitPractice() {
    if (GZCmd_checkTrig(GZStng_getSettingData<uint16_t>(STNG_CMD_BIT, BACK_IN_TIME_BUTTONS))) {
        // TODO: maybe simplify this
        special sp[] = {
            special(0, nullptr, BiTIndicator::setPosition),
        };

        SaveManager::triggerLoad(0, "any", sp, 1);
    }
}
#endif

static char buf[30];

KEEP_FUNC void BiTIndicator::setPosition() {
    dComIfGp_getPlayer()->current.pos = (cXyz){466.622467f, 319.770752f, -11651.3867f};
    dComIfGp_getPlayer()->shape_angle.y = 32000;
    matrixInfo.matrix_info->target = {465.674622f, 421.052704f, -11651.0684f};
    matrixInfo.matrix_info->pos = {735.525391f, 524.418701f, -11576.4746f};
}

KEEP_FUNC void BiTIndicator::execute() {
    double dt = 0;

    if (dComIfGp_getPlayer()) {
        const bool has_boots = (dComIfGp_getPlayer()->mNoResetFlg0 & 0x02) != 0;
        const double term_vel = has_boots ? BOOTS_TERM_VEL : NORMAL_TERM_VEL;
        const double acc = has_boots ? BOOTS_ACC : NORMAL_ACC;
        const double v_y1 = dComIfGp_getPlayer()->speed.y;
        const double dist_from_last_ground =
            (dComIfGp_getPlayer()->current.pos.y - LAST_Y_GROUND_POS);

        // Calculate how many frames before reaching terminal velocity
        double dt_1 = (term_vel - v_y1) / acc;
        // Calculate how much height we will lose during that period
        double x_dt_1 = dist_from_last_ground + v_y1 * dt_1 + 0.5 * acc * dt_1 * dt_1;

        // If we reach terminal velocity after the voiding point, ...
        if (x_dt_1 <= VOID_HEIGHT) {
            // ... just calculate the time remaining before void using the quadratic formula
            dt = (-v_y1 -
                  sqrt((double)(v_y1 * v_y1 + 2 * acc * (VOID_HEIGHT - dist_from_last_ground)))) /
                     acc +
                 0.5;
        } else {
            // ... else, the time remaining before the void is the time to reach terminal velocity +
            // linear time at velocity
            dt = dt_1 + (VOID_HEIGHT - x_dt_1) / term_vel + 0.5;
        }

        // if (homeMenuSts.is_visible == 0 && !fopScnRq.isLoading) {
        //     sprintf(buf, "frames before void: %d", (int)dt);
        //     log.PrintLog(buf, DEBUG);
        // }

        if (daAlink_c__checkStageName("F_SP104") && GZ_getButtonPressed(GZPad::HOME) &&
            homeMenuSts.is_visible == 0 && !fopScnRq.isLoading) {
            if ((int)dt == TARGET_FRAME) {
                snprintf(buf, sizeof(buf), "Got it");
            }
            if ((int)dt > TARGET_FRAME) {
                snprintf(buf, sizeof(buf), "%d frames early", (int)dt - TARGET_FRAME);
            }
            if ((int)dt < TARGET_FRAME) {
                snprintf(buf, sizeof(buf), "%d frames late", TARGET_FRAME - (int)dt);
            }
            FIFOQueue::push(buf, Queue);
        }
    }
}
#endif