#include "commands.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/tp.h"

namespace Commands {
    static float saved_x = 0.0f;
    static float saved_y = 0.0f;
    static float saved_z = 0.0f;
    static uint16_t saved_a = 0;
    static float saved_c0 = 0.0f;
    static float saved_c1 = 0.0f;
    static float saved_c2 = 0.0f;
    static float saved_c3 = 0.0f;
    static float saved_c4 = 0.0f;
    static float saved_c5 = 0.0f;
    static float saved_c6 = 0.0f;
    static float saved_c7 = 0.0f;

    void store_position();
    void load_position();
    void moon_jump();
    void reload_area();

    struct Command {
        bool active;
        uint16_t buttons;
        void (*command)();
    };

    static Command Commands[4] = {
        {true, 0x0028, store_position},
        {true, 0x0024, load_position},
        {true, 0x0120, moon_jump},
        {true, 0x1160, reload_area}};

    void store_position() {}

    void load_position() {}

    void moon_jump() {
        if (tp_gameInfo.momentum_ptr) {
            tp_gameInfo.momentum_ptr->link_momentum.y = 56.0f;
        };
    };

    void reload_area() {
        tp_gameInfo.warp.enabled = true;
    };

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