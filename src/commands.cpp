#include "commands.h"
#include "controller.h"
#include "free_cam.h"
#include "fs.h"
#include "gorge.h"
#ifdef WII_PLATFORM
#include "bit.h"
#endif
#include "lib.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/practice_menu.h"
#include "menus/settings_menu.h"
#include "menus/hundo_saves_menu.h"
#include "movelink.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_draw_tag.h"
#include "timer.h"
#include "utils/loading.h"

using namespace Controller;

bool reload_area_flag = false;
bool timer_started = false;
bool reset_timer = false;

bool commands_states[COMMANDS_AMNT];

namespace Commands {
static cXyz saved_player_pos(0.0f, 0.0f, 0.0f);
static uint16_t saved_angle = 0;

static Vec saved_pos = {0.0f, 0.0f, 0.0f};
static Vec saved_target = {0.0f, 0.0f, 0.0f};
static int button_last_frame;
static int button_this_frame;

void store_position() {
    if (dComIfGp_getPlayer()) {
        saved_player_pos = dComIfGp_getPlayer()->mCurrent.mPosition;
        saved_angle = dComIfGp_getPlayer()->mCollisionRot.mY;
    }

    if (tp_matrixInfo.matrix_info) {
        saved_pos = tp_matrixInfo.matrix_info->pos;
        saved_target = tp_matrixInfo.matrix_info->target;
    }
}

void load_position() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->mCurrent.mPosition = saved_player_pos;
        dComIfGp_getPlayer()->mCollisionRot.mY = saved_angle;
    }

    if (tp_matrixInfo.matrix_info) {
        tp_matrixInfo.matrix_info->pos = saved_pos;
        tp_matrixInfo.matrix_info->target = saved_target;
    }
}

void moon_jump() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->mSpeed.y = 56.0f;
    };
};

void toggle_timer() {
    if (button_this_frame == TIMER_TOGGLE_BUTTONS && button_last_frame != TIMER_TOGGLE_BUTTONS) {
        timer_started = !timer_started;
    };
}

void hit_reset() {
    reset_timer = true;
}

void reload_area() {
    inject_save_flag = true;
    if (g_area_reload_behavior == LOAD_AREA) {
        tp_memcpy(
            &g_dComIfG_gameInfo.info.mMemory, gSaveManager.mAreaReloadOpts.temp_flags,
            sizeof(
                gSaveManager.mAreaReloadOpts.temp_flags));  // restore last set of saved temp flags

        // restore last tear count
        for (int i = 0; i < 4; i++) {
            dComIfGs_setLightDropNum(i, gSaveManager.mAreaReloadOpts.tears[i]);
        }

        gSaveManager.mPracticeFileOpts.inject_options_before_load =
            SaveManager::inject_default_before;
        gSaveManager.mPracticeFileOpts.inject_options_during_load = nullptr;
        gSaveManager.mPracticeFileOpts.inject_options_after_load = nullptr;
    } else {
        SaveManager::load_save(last_save_index, last_category, last_special_ptr, 0xFF);
    }
}  // namespace Commands

void gorge_void() {
    if (button_this_frame == GORGE_VOID_BUTTONS && button_last_frame != GORGE_VOID_BUTTONS) {
        SaveManager::load_save_file("tpgz/save_files/any/gorge_void.bin");
        gSaveManager.mPracticeFileOpts.inject_options_before_load =
            SaveManager::inject_default_before;
        gSaveManager.mPracticeFileOpts.inject_options_during_load =
            GorgeVoidIndicator::warp_to_gorge;
        gSaveManager.mPracticeFileOpts.inject_options_after_load =
            GorgeVoidIndicator::prep_rupee_roll;
        inject_save_flag = true;
    }
}

#ifdef WII_PLATFORM
void back_in_time() {
    if (button_this_frame == BACK_IN_TIME_BUTTONS && button_last_frame != BACK_IN_TIME_BUTTONS) {
        SaveManager::load_save_file("tpgz/save_files/any/ordon_gate_clip.bin");
        gSaveManager.mPracticeFileOpts.inject_options_before_load =
            gSaveManager.inject_default_before;
        gSaveManager.mPracticeFileOpts.inject_options_during_load =
            gSaveManager.inject_default_during;
        gSaveManager.mPracticeFileOpts.inject_options_after_load =
            BiTIndicator::set_camera_angle_position;
        gSaveManager.mPracticeFileOpts.inject_options_after_counter = 10;
        inject_save_flag = true;
    }
}
#endif

void toggle_free_cam() {
    if (button_this_frame == FREE_CAM_BUTTONS && button_last_frame != FREE_CAM_BUTTONS) {
        free_cam_active = !free_cam_active;
    }
}

void toggle_move_link() {
    if (button_this_frame == MOVE_LINK_BUTTONS && button_last_frame != MOVE_LINK_BUTTONS) {
        move_link_active = !move_link_active;
    }
}

struct Command {
    bool& active;
    uint16_t buttons;
    void (*command)();
};

static Command Commands[COMMANDS_AMNT] = {
    {commands_states[CMD_STORE_POSITION], STORE_POSITION_BUTTONS, store_position},
    {commands_states[CMD_LOAD_POSITION], LOAD_POSITION_BUTTONS, load_position},
    {commands_states[CMD_MOON_JUMP], MOON_JUMP_BUTTONS, moon_jump},
    {commands_states[CMD_RELOAD_AREA], RELOAD_AREA_BUTTONS, reload_area},
    {commands_states[CMD_TIMER_TOGGLE], TIMER_TOGGLE_BUTTONS, toggle_timer},
    {commands_states[CMD_TIMER_RESET], TIMER_RESET_BUTTONS, hit_reset},
    {commands_states[CMD_GORGE_VOID], GORGE_VOID_BUTTONS, gorge_void},
#ifdef WII_PLATFORM
    {commands_states[CMD_BIT], BACK_IN_TIME_BUTTONS, back_in_time},
#endif
    {commands_states[CMD_FREE_CAM], FREE_CAM_BUTTONS, toggle_free_cam},
    {commands_states[CMD_MOVE_LINK], MOVE_LINK_BUTTONS, toggle_move_link}};

void process_inputs() {
    button_this_frame = Controller::get_current_inputs();
    for (auto c : Commands) {
        if (c.active == true && Controller::get_current_inputs() == c.buttons) {
            c.command();
            set_buttons_down(0x0);
            set_buttons_pressed(0x0);
            tp_mPadButton.sval = 0x0;
            tp_mPadStatus.sval = 0x0;
        };
    };
    button_last_frame = button_this_frame;
};

void enable_command(int idx) {
    Commands[idx].active = true;
}

void disable_command(int idx) {
    Commands[idx].active = false;
}

}  // namespace Commands