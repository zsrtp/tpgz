#include "commands.h"
#include "menu.h"
#include "utils.h"
#include "timer.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/tp.h"

bool reload_area_flag = false;
bool timer_started = false;
bool reset_timer = false;

namespace Commands {
    static float saved_x = 0.0f;
    static float saved_y = 0.0f;
    static float saved_z = 0.0f;
    static uint16_t saved_angle = 0;
    static float saved_c0 = 0.0f;
    static float saved_c1 = 0.0f;
    static float saved_c2 = 0.0f;
    static float saved_c3 = 0.0f;
    static float saved_c4 = 0.0f;
    static float saved_c5 = 0.0f;
    static float saved_c6 = 0.0f;
    static float saved_c7 = 0.0f;

    void store_position() {
        saved_x = tp_zelAudio.link_debug_ptr->position.x;
        saved_y = tp_zelAudio.link_debug_ptr->position.y;
        saved_z = tp_zelAudio.link_debug_ptr->position.z;
        saved_angle = tp_zelAudio.link_debug_ptr->facing;
        saved_c0 = tp_matrixInfo.matrix_info->camera0;
        saved_c1 = tp_matrixInfo.matrix_info->camera1;
        saved_c2 = tp_matrixInfo.matrix_info->camera2;
        saved_c3 = tp_matrixInfo.matrix_info->camera3;
        saved_c4 = tp_matrixInfo.matrix_info->camera4;
        saved_c5 = tp_matrixInfo.matrix_info->camera5;
        saved_c6 = tp_matrixInfo.matrix_info->camera6;
        saved_c7 = tp_matrixInfo.matrix_info->camera7;
    }

    void load_position() {
        tp_zelAudio.link_debug_ptr->position.x = saved_x;
        tp_zelAudio.link_debug_ptr->position.y = saved_y;
        tp_zelAudio.link_debug_ptr->position.z = saved_z;
        tp_zelAudio.link_debug_ptr->facing = saved_angle;
        tp_matrixInfo.matrix_info->camera0 = saved_c0;
        tp_matrixInfo.matrix_info->camera1 = saved_c1;
        tp_matrixInfo.matrix_info->camera2 = saved_c2;
        tp_matrixInfo.matrix_info->camera3 = saved_c3;
        tp_matrixInfo.matrix_info->camera4 = saved_c4;
        tp_matrixInfo.matrix_info->camera5 = saved_c5;
        tp_matrixInfo.matrix_info->camera6 = saved_c6;
        tp_matrixInfo.matrix_info->camera7 = saved_c7;
    }

    void moon_jump() {
        if (tp_gameInfo.momentum_ptr) {
            tp_gameInfo.momentum_ptr->link_momentum.y = 56.0f;
        };
    };

    void toggle_timer() {
        timer_started = !timer_started;
    }

    void hit_reset() {
        reset_timer = true;
    }

    void reload_area() {
        reload_area_flag = true;
    };

    struct Command {
        bool active;
        uint16_t buttons;
        void (*command)();
    };

    static Command Commands[6] = {
        {true, 0x0028, store_position},
        {true, 0x0024, load_position},
        {true, 0x0120, moon_jump},
        {true, 0x1160, reload_area},
        {true, 0x0110, toggle_timer},
        {true, 0x0210, hit_reset}};

    

    void process_inputs() {
        for (auto c : Commands) {
            if (c.active == true && tp_mPadStatus.sval == c.buttons) {
                c.command();
                Controller::set_buttons_down(0x0);
                Controller::set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
            };
        };
    };

    void enable_command(int idx) {
        Commands[idx].active = true;
    }

    void disable_command(int idx) {
        Commands[idx].active = false;
    }

}  // namespace Commands