#include "flags.h"
#include "gorge.h"
#include "rollcheck.h"
#include "utils.h"
#include "menu.h"
#include "actor.h"
#include "system.h"
#include "fifo_queue.h"

bool inject_save_flag = false;

MenuFlag MenuFlags[MAX_MENU_FLAGS] = {
    {&g_gorge_active, GorgeVoidIndicator::run},
    {&g_roll_check_active, RollIndicator::run},
    {&inject_save_flag, Utilities::trigger_load},
    {&g_freeze_actors, Actor::freeze_actors, Actor::unfreeze_actors},
    {&g_hide_actors, Actor::hide_actors, Actor::show_actors},
    {&g_lock_camera, System::lock_camera, System::unlock_camera},
    {&g_hide_hud, System::hide_hud, System::show_hud},
    {&g_tunic_color_flag, Utilities::change_tunic_color, Utilities::change_tunic_color},
    {&g_disable_bg_music, Utilities::disable_bg_music, Utilities::enable_bg_music},
    {&g_disable_sfx, Utilities::disable_sfx, Utilities::enable_sfx}};

namespace Flags {
    void apply_active_flags() {
        for (int i = 0; i < MAX_MENU_FLAGS; i++) {
            if (*MenuFlags[i].activation_flag) {
                MenuFlags[i].flag_active_function();
            } else if (MenuFlags[i].flag_deactive_function) {
                MenuFlags[i].flag_deactive_function();
            }
        }
    }
}  // namespace Flags