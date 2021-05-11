#include "gz_flags.h"
#include "actor.h"
#include "fifo_queue.h"
#include "gorge.h"
#include "umd.h"
#include "bit.h"
#include "menus/scene_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"
#include "rollcheck.h"
#include "system.h"
#include "time.h"
#include "utils/audio.h"
#include "utils/lines.h"
#include "utils/link.h"
#include "utils/loading.h"
#include "flaglog.h"
#include "menus/memfiles_menu.h"

bool inject_save_flag = false;

GZFlag GZ_Flags[MAX_GZ_FLAGS] = {
    {&ToolItems[Tools::GORGE_INDEX].active, 0, GorgeVoidIndicator::run},
#ifdef GCN_PLATFORM
    {&ToolItems[Tools::UMD_INDEX].active, 1, UMDIndicator::run},
#endif
#ifdef WII_PLATFORM
    {&ToolItems[Tools::BIT_INDEX].active, 0, BiTIndicator::run},
#endif
    {&ToolItems[Tools::ROLL_INDEX].active, 0, RollIndicator::run},
    {&g_flag_log_active, 0, FlagLog::run},
    {&inject_save_flag, 0, Utilities::trigger_load},
    {&SceneItems[Scene::FREEZE_ACTOR_INDEX].active, 0, Actor::freeze_actors, Actor::unfreeze_actors},
    {&SceneItems[Scene::HIDE_ACTOR_INDEX].active, 0, Actor::hide_actors, Actor::show_actors},
    {&SceneItems[Scene::FREEZE_CAMERA_INDEX].active, 0, System::lock_camera, System::unlock_camera},
    {&SceneItems[Scene::HIDE_HUD_INDEX].active, 0, System::hide_hud, System::show_hud},
    {&SceneItems[Scene::FREEZE_TIME_INDEX].active, 0, Utilities::freeze_time},
    {&g_tunic_color_flag, 0, Utilities::change_tunic_color, Utilities::change_tunic_color},
    {&g_cursor_color_flag, 0, Utilities::change_cursor_color, Utilities::change_cursor_color},
    {&SceneItems[Scene::DISABLE_BG_INDEX].active, 0, Utilities::disable_bg_music, Utilities::enable_bg_music},
    {&SceneItems[Scene::DISABLE_SFX_INDEX].active, 0, Utilities::disable_sfx, Utilities::enable_sfx},
    {&set_position_data, 0, set_memfile_position}};

namespace GZFlags {
void apply_active_flags(int phase) {

    for (int i = 0; i < MAX_GZ_FLAGS; i++) {

        if (phase == GZ_Flags[i].requiredPhase) {
       
            if (*GZ_Flags[i].activation_flag) {
                GZ_Flags[i].flag_active_function();
            } else if (GZ_Flags[i].flag_deactive_function) {
                GZ_Flags[i].flag_deactive_function();
            }
        }
    }
}
}  // namespace GZFlags