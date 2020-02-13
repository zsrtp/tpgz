#ifndef LIB_TP_CHEATS
#define LIB_TP_CHEATS

namespace Cheats {
    void apply_cheats();
    void store_position();
    void load_position();
    void moon_jump();
    void reload_area();
    void process_inputs();
    void gorge_void();

    static bool doing_cheats = false;
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
    const int STORE_POSITION = 0;
    const int LOAD_POSITION = 1;
    const int MOON_JUMP = 2;
    const int RELOAD_AREA = 3;

    struct Command {
        bool active;
        uint16_t buttons;
        void (*command)();
    };

    static Command Commands[4] = {
        {true, 0x0028, store_position},
        {true, 0x0024, load_position},
        {true, 0x0120, moon_jump},
        {true, 0x1160, reload_area}
    };
};  // namespace Cheats

#endif