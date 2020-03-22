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
extern bool cheats_visible;

// warping
#define stuff 2
extern bool warping_visible;

// memory
#define stuff 2
extern bool memory_visible;

// practice
enum PracticeIndex {
    ORDON_GATE_CLIP_INDEX = 2,
    BACK_IN_TIME_INDEX,
    GOATS_INDEX,
    HUGO_INDEX,
    EMS_INDEX,
    MIST_INDEX,
    FRST_BIT_INDEX,
    FRST_ESCAPE_INDEX,
    GORGE_VOID_INDEX,
    RUPEE_ROLL_INDEX,
    LANAYRU_GATE_CLIP_INDEX,
    PILLAR_CLIP_INDEX,
    LAKEBED_1_INDEX,
    TOAD_INDEX,
    KARG_INDEX,
    ELDIN_TWILIGHT_INDEX,
    LANAYRU_TWILIGHT_INDEX,
    BOSS_BUG_INDEX,
    IZA_INDEX,
    NORGOR_INDEX,
    SPR_WARP_SKIP_INDEX,
    SPR_INDEX,
    DARK_HAMMER_INDEX,
    LAKEBED_2_INDEX,
    LAKEBED_BK_SKIP_INDEX,
    ONEBOMB_INDEX,
    MDH_TOWER_INDEX,
    MDH_BRIDGE_INDEX,
    BULBLIN_CAMP_INDEX,
    AG_INDEX,
    POE_1_SKIP_INDEX,
    DSS_INDEX,
    STALLORD_INDEX,
    CITS_EARLY_INDEX,
    CITS_1_INDEX,
    AERALFOS_SKIP_INDEX,
    CITS_2_INDEX,
    FAN_TOWER_INDEX,
    ARGOROK_INDEX,
    PALACE_1_INDEX,
    PALACE_2_INDEX,
    EARLY_PLATFORM_INDEX,
    ZANT_INDEX,
    HC_INDEX,
    DARKNUT_INDEX,
    HC_TOWER_INDEX,
    BEAST_GANON_INDEX,
    HORSEBACK_GANON_INDEX
};

extern bool prac_visible;
extern bool inject_save_flag;
extern bool g_load_happened;

// tools
#define INPUT_VIEWER_INDEX 2
#define TIMER_INDEX 3
#define ROLL_INDEX 4
#define GORGE_INDEX 5
#define FREEZE_ACTOR_INDEX 6
#define HIDE_ACTOR_INDEX 7
#define FREEZE_CAMERA_INDEX 8
extern bool tools_visible;

// settings
#define LOG_LEVEL_INDEX 2
#define DROP_SHADOWS_INDEX 3
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