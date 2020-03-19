#pragma once
#include "font.h"
#include <string.h>

// main menu
#define INVENTORY_INDEX 2
#define CHEAT_INDEX 3
#define WARPING_INDEX 4
#define MEMORY_INDEX 5
#define PRACTICE_INDEX 6
#define TOOLS_INDEX 7
#define SETTINGS_INDEX 8
extern bool mm_visible;

// inventory
#define ITEM_WHEEL_INDEX 2
#define PAUSE_MENU_INDEX 3
extern bool inventory_visible;

// item wheel
#define stuff 2
extern bool item_wheel_visible;

// pause menu
#define stuff 2
extern bool pause_visible;

// cheats
#define INVINCIBLE_INDEX 0
#define INVINCIBLE_ENEMIES_INDEX 1
#define INFINITE_AIR_INDEX 2
#define INFINITE_OIL_INDEX 3
#define INFINITE_BOMBS_INDEX 4
#define INFINITE_RUPEES_INDEX 5
#define INFINITE_ARROWS_INDEX 6
#define MOON_JUMP_INDEX 7
#define TELEPORT_INDEX 8
#define RELOAD_AREA_INDEX 9
#define FAST_MOVEMENT_INDEX 10
extern bool cheats_visible;

// warping
#define stuff 2
extern bool warping_visible;

// memory
#define stuff 2
extern bool memory_visible;

// practice
#define ORDON_GATE_CLIP_INDEX 2
#define BACK_IN_TIME_INDEX 3
#define GOATS_INDEX 4
#define HUGO_INDEX 5
#define EMS_INDEX 6
#define MIST_INDEX 7
#define FRST_BIT_INDEX 8
#define FRST_ESCAPE_INDEX 9
#define GORGE_VOID_INDEX 10
#define RUPEE_ROLL_INDEX 11
#define LANAYRU_GATE_CLIP_INDEX 12
#define PILLAR_CLIP_INDEX 13
#define LAKEBED_1_INDEX 14
#define TOAD_INDEX 15
#define KARG_INDEX 16
#define ELDIN_TWILIGHT_INDEX 17
#define LANAYRU_TWILIGHT_INDEX 18
#define BOSS_BUG_INDEX 19
#define IZA_INDEX 20
#define NORGOR_INDEX 21
#define SPR_WARP_SKIP_INDEX 22
#define SPR_INDEX 23
#define DARK_HAMMER_INDEX 24
#define LAKEBED_2_INDEX 25
#define LAKEBED_BK_SKIP_INDEX 26
#define ONEBOMB_INDEX 27
#define MDH_TOWER_INDEX 28
#define MDH_BRIDGE_INDEX 29
#define BULBLIN_CAMP_INDEX 30
#define AG_INDEX 31
#define POE_1_SKIP_INDEX 32
#define DSS_INDEX 33
#define STALLORD_INDEX 34
#define CITS_EARLY_INDEX 35
#define CITS_1_INDEX 36
#define AERALFOS_SKIP_INDEX 37
#define CITS_2_INDEX 38
#define FAN_TOWER_INDEX 39
#define ARGOROK_INDEX 40
#define PALACE_1_INDEX 41
#define PALACE_2_INDEX 42
#define EARLY_PLATFORM_INDEX 43
#define HC_INDEX 44
#define DARKNUT_INDEX 45
#define HC_TOWER_INDEX 46
#define BEAST_GANON_INDEX 47
#define HORSEBACK_GANON_INDEX 48

extern bool prac_visible;
extern bool inject_save_flag;
extern bool g_load_happened;

// tools
#define INPUT_VIEWER_INDEX 2
#define TIMER_INDEX 3
#define ROLL_INDEX 4
#define GORGE_INDEX 5
extern bool tools_visible;

// settings
#define LOG_LEVEL_INDEX 2
#define RESET_TEMP_FLAGS_INDEX 3
#define DROP_SHADOWS_INDEX 4
extern bool settings_visible;
extern bool g_reset_temp_flags;
extern bool g_drop_shadows;

struct Line {
    char line[50];
    const int idx;
    char description[100];
    bool toggleable = false;
    bool* activation_flag;
};

class Menu {
   protected:
    // char MenuName[32];
    // int MenuId;
    // char MenuDescription[32];

   public:
    Menu() {}
    // Menu(const char* _MenuName, int _MenuId, const char* _MenuDescription) {
    //     strcpy(MenuName, _MenuName);
    //     strcpy(MenuDescription, _MenuDescription);
    //     MenuId = _MenuId;
    // }
    virtual void transition_into() = 0;
    virtual void render() = 0;
};

class MainMenu : public Menu {
   public:
    MainMenu() : Menu(){};
    void transition_into();
    static void render(Font& font);
};

class InventoryMenu : public Menu {
   public:
    InventoryMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class PauseMenu : public Menu {
   public:
    PauseMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class ItemWheelMenu : public Menu {
   public:
    ItemWheelMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class CheatsMenu : public Menu {
   public:
    CheatsMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class WarpingMenu : public Menu {
   public:
    WarpingMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class MemoryMenu : public Menu {
   public:
    MemoryMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};
namespace PracticeMenu {

    void inject_default_during();
    void inject_default_after();
    class PracticeMenu : public Menu {
       public:
        PracticeMenu() : Menu() {}
        void transition_into(){};
        static void render(Font& font);
    };
};  // namespace PracticeMenu

class SettingsMenu : public Menu {
   public:
    SettingsMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};

class ToolsMenu : public Menu {
   public:
    ToolsMenu() : Menu() {}
    void transition_into(){};
    static void render(Font& font);
};