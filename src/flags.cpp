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
    {&ToolItems[Tools::GORGE_INDEX].active, GorgeVoidIndicator::run},
    {&ToolItems[Tools::ROLL_INDEX].active, RollIndicator::run},
    {&inject_save_flag, Utilities::trigger_load},
    {&ToolItems[Tools::FREEZE_ACTOR_INDEX].active, Actor::freeze_actors, Actor::unfreeze_actors},
    {&ToolItems[Tools::HIDE_ACTOR_INDEX].active, Actor::hide_actors, Actor::show_actors},
    {&ToolItems[Tools::FREEZE_CAMERA_INDEX].active, System::lock_camera, System::unlock_camera},
    {&ToolItems[Tools::HIDE_HUD_INDEX].active, System::hide_hud, System::show_hud},
    {&g_tunic_color_flag, Utilities::change_tunic_color, Utilities::change_tunic_color},
    {&ToolItems[Tools::DISABLE_BG_INDEX].active, Utilities::disable_bg_music, Utilities::enable_bg_music},
    {&ToolItems[Tools::DISABLE_SFX_INDEX].active, Utilities::disable_sfx, Utilities::enable_sfx}};

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