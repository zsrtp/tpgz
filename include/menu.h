#pragma once
#include "font.h"
#include "timer.h"
#include "input_viewer.h"
#include "cheats.h"
#include "libtp_c/include/utils.h"
#include <string.h>
#define CURSOR_RGBA cursor_rgba

// main menu
enum MainMenuIndex {
    CHEAT_INDEX,
    FLAGS_INDEX,
    INVENTORY_INDEX,
    MEMORY_INDEX,
    PRACTICE_INDEX,
    SCENE_INDEX,
    SETTINGS_INDEX,
    TOOLS_INDEX,
    WARPING_INDEX,
};
extern bool mm_visible;

// inventory
#define ITEM_WHEEL_INDEX 0
#define PAUSE_MENU_INDEX 1
#define AMOUNTS_MENU_INDEX 2
extern bool inventory_visible;

// item wheel
extern bool item_wheel_visible;
enum ItemID {
    OOCCOO_SR = 37,
    OOCCOO_JR = 39,
    OOCCOOS_NOTE = 45,
    HAWKEYE = 62,
    GALE_BOOMERANG = 64,
    SPINNER,
    BALL_AND_CHAIN,
    HEROS_BOW,
    CLAWSHOT,
    IRON_BOOTS,
    DOMINION_ROD,
    DOUBLE_CLAWSHOT,
    LANTERN,
    MASTER_SWORD,
    FISHING_ROD,
    SLINGSHOT,
    EMPTY_BOMBBAG = 80,
    ROD_BEE_LARVA = 91,
    ROD_CORAL_EARRING,
    ROD_WORM,
    ROD_CORAL_EARRING_BEE_LARVA,
    ROD_CORAL_EARRING_WORM,
    EMPTY_BOTTLE,
    RED_POTION,
    MAGIC_POTION,
    BLUE_POTION,
    MILK,
    HALF_MILK,
    LANTERN_OIL,
    WATER,
    NASTY_SOUP = 106,
    HOT_SPRING_WATER,
    FAIRY,
    REGULAR_BOMBS = 112,
    WATER_BOMBS,
    BOMBLINGS,
    FAIRY_TEARS,
    WORM,
    BEE_LARVA = 118,
    RARE_CHU,
    RED_CHU,
    BLUE_CHU,
    GREEN_CHU,
    YELLOW_CHU,
    PURPLE_CHU,
    SIMPLE_SOUP,
    GOOD_SOUP,
    SUPERB_SOUP,
    RENADOS_LETTER,
    INVOICE,
    WOODEN_STATUE,
    ILIAS_CHARM,
    HORSE_CALL,
    AURUS_MEMO = 144,
    ASHEIS_SKETCH,
    ANCIENT_SKY_BOOK_EMPTY = 233,
    ANCIENT_SKY_BOOK_PARTIAL,
    ANCIENT_SKY_BOOK_FILLED,
    NO_ITEM = 255
};

enum Slot {
    SLOT_0,
    SLOT_1,
    SLOT_2,
    SLOT_3,
    SLOT_4,
    SLOT_5,
    SLOT_6,
    SLOT_7,
    SLOT_8,
    SLOT_9,
    SLOT_10,
    SLOT_11,
    SLOT_12,
    SLOT_13,
    SLOT_14,
    SLOT_15,
    SLOT_16,
    SLOT_17,
    SLOT_18,
    SLOT_19,
    SLOT_20,
    SLOT_21,
    SLOT_22,
    SLOT_23
};

struct ItemLookup {
    enum ItemID item_id;
    char item_description[40];
};

// pause menu
enum PauseIndex {
    ORDON_SWORD_INDEX,
    MASTER_SWORD_INDEX,
    WOOD_SHIELD_INDEX,
    HYLIAN_SHIELD_INDEX,
    HERO_TUNIC_INDEX,
    ZORA_ARMOR_INDEX,
    MAGIC_ARMOR_INDEX,
    BOMB_CAPACITY_INDEX,
    WALLET_INDEX,
    ARROW_CAPACITY_INDEX,
    ENDING_BLOW_INDEX,
    SHIELD_BASH_INDEX,
    BACKSLICE_INDEX,
    HELM_SPLITTER_INDEX,
    MORTAL_DRAW_INDEX,
    JUMP_STRIKE_INDEX,
    GREAT_SPIN_INDEX
};

extern bool pause_visible;

// amounts menu
enum AmountsIndex {
    ARROW_AMMO_INDEX,
    BOMB_BAG_1_AMMO_INDEX,
    BOMB_BAG_2_AMMO_INDEX,
    BOMB_BAG_3_AMMO_INDEX,
    SLINGSHOT_AMMO_INDEX,
    HEART_PIECE_COUNT_INDEX,
    POE_COUNT_INDEX,
    RUPEE_COUNT_INDEX
};

extern bool amounts_visible;

// cheats
extern bool cheats_visible;

// warping
extern bool warping_visible;
enum WarpingIndex {
    WARP_TYPE_INDEX,
    WARP_STAGE_INDEX,
    WARP_ROOM_INDEX,
    WARP_SPAWN_INDEX,
    WARP_LAYER_INDEX,
    WARP_BUTTON_INDEX
};

struct StageInfo {
    char num_stages;
    char stage_id[31];
    char stage_name[32];
};

struct RoomInfo {
    char num_rooms;
    char room_id[31];
    char room_name[32];
};

struct SpawnInfo {
    char num_spawns;
    char spawn_id[3];
};

struct WarpInfo {
    StageInfo stage_info;
    RoomInfo room_info;
    SpawnInfo spawn_info;
}__attribute__((aligned(32)));

// memory
#define MAX_WATCHES 10
extern bool memory_visible;

enum MemoryType {
    u8,
    i8,
    u16,
    i16,
    u32,
    i32,
    f32,
    string
};

enum MemoryColumns {
    WatchAddress,
    WatchX,
    WatchY,
    WatchHex,
    WatchType,
    WatchOffset
};

struct MemoryWatch {
    uint32_t address = 0x80000000;
    float x = 400.0f;
    float y = 100.0f;
    bool hex = false;
    uint8_t type = string;
    uint16_t offset = 0x0000;
    uint32_t value;
    bool visible = false;
    bool line_selected = false;
    bool value_selected = false;
};

extern MemoryWatch Watches[MAX_WATCHES];
extern bool watches_visible;

// memory editor

struct MemoryLine {
    bool line_selected = false;
    bool value_selected = false;
};

extern bool memory_editor_visible;

// flags
#define GENERAL_FLAGS_INDEX 0
#define DUNGEON_FLAGS_INDEX 1
#define PORTAL_FLAGS_INDEX 2
#define TEMP_FLAGS_INDEX 3
extern bool flags_menu_visible;

enum GeneralFlagsIndex {
    BOSS_FLAG_INDEX,
    RUPEE_CS_FLAG_INDEX,
    EPONA_STOLEN_INDEX,
    EPONA_TAMED_INDEX,
    MAP_WARPING_INDEX,
    MIDNA_CHARGE_INDEX,
    MIDNA_HEALTHY,
    MIDNA_ON_BACK,
    MIDNA_Z_INDEX,
    TRANSFORM_WARP_INDEX,
    WOLF_SENSE_INDEX
};

extern bool general_flags_visible;

enum DungeonFlagsIndex {
    SELECT_DUNGEON_INDEX,
    MAP_FLAG_INDEX,
    COMPASS_FLAG_INDEX,
    BOSS_KEY_FLAG_INDEX,
    SMALL_KEY_FLAG_INDEX,
    DEFEAT_MINIBOSS_FLAG_INDEX,
    DEFEAT_BOSS_FLAG_INDEX,
    CLEAR_DUNGEON_FLAGS_INDEX
};

extern bool dungeon_flags_visible;

enum PortalFlagsIndex {
    SPRING_WARP_INDEX,
    S_FARON_WARP_INDEX,
    N_FARON_WARP_INDEX,
    GROVE_WARP_INDEX,
    GORGE_WARP_INDEX,
    KAKARIKO_WARP_INDEX,
    MOUNTAIN_WARP_INDEX,
    BRIDGE_WARP_INDEX,
    TOWN_WARP_INDEX,
    LAKE_WARP_INDEX,
    DOMAIN_WARP_INDEX,
    UZR_WARP_INDEX,
    SNOWPEAK_WARP_INDEX,
    MESA_WARP_INDEX,
    MIRROR_WARP_INDEX
};

extern bool portal_flags_visible;

// Temp Flags
struct AreaNode {
    uint8_t offset;
    bool bit[8];
    bool line_selected = false;
};

extern bool temp_flags_visible;

// practice
#define ANY_INDEX 0
#define HUNDO_INDEX 1
extern bool prac_visible;
extern bool inject_save_flag;

// any% saves
enum AnyPracticeIndex {
    ORDON_GATE_CLIP_INDEX,
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

struct PracticeSaveInfo {
    uint8_t requirements;
    uint8_t _p0[1];
    uint16_t angle;
    Vec3 position;
    Vec3 cam_pos;
    Vec3 cam_target;
    uint32_t counter;
    char filename[32];
    uint8_t _p1[4];
} __attribute__((packed));

extern bool any_saves_visible;

// hundo saves
enum HundoPracticeIndex {
    HND_GOATS_1_INDEX,
    HND_ORDON_GATE_CLIP_INDEX,
    HND_GOATS_2_INDEX,
    HND_FARON_TWILIGHT_INDEX,
    HND_EMS_INDEX,
    HND_MIST_INDEX,
    HND_FRST_BIT_INDEX,
    HND_FRST_2_INDEX,
    HND_OOKLESS_INDEX,
    HND_ELDIN_TWILIGHT_INDEX,
    HND_LANAYRU_GATE_CLIP_INDEX,
    HND_PILLAR_CLIP_INDEX,
    HND_LAKEBED_1_INDEX,
    HND_TOAD_INDEX,
    HND_KARG_INDEX,
    HND_LANAYRU_TWILIGHT_INDEX,
    HND_BOSS_BUG_INDEX,
    HND_KB_2_INDEX,
    HND_ESCORT_INDEX,
    HND_COROTD_INDEX,
    HND_GM_INDEX,
    HND_DANGORO_INDEX,
    HND_KB_1_INDEX,
    HND_LAKEBED_BK_SKIP_INDEX,
    HND_MORPHEEL_INDEX,
    HND_STAR_1_INDEX,
    HND_MDH_TOWER_INDEX,
    HND_MDH_BRIDGE_INDEX,
    HND_POST_MDH_INDEX,
    HND_MOUNTAIN_INDEX,
    HND_IZA_1_SKIP_INDEX,
    HND_IZA_2_INDEX,
    HND_LH_CAVE_INDEX,
    HND_BULBLIN_CAMP_INDEX,
    HND_AG_INDEX,
    HND_POE_1_SKIP_INDEX,
    HND_DSS_INDEX,
    HND_STALLORD_INDEX,
    HND_GORGE_INDEX,
    HND_SPR_INDEX,
    HND_DARK_HAMMER_INDEX,
    HND_SPR_SUPERJUMP_INDEX,
    HND_SPR_BK_LJA_INDEX,
    HND_SPR_BK_ROOM_INDEX,
    HND_BLIZZETA_INDEX,
    HND_BOMB_BOOST_INDEX,
    HND_GROVE_2_INDEX,
    HND_TOT_INDEX,
    HND_EARLY_POE_INDEX,
    HND_STATUE_THROWS_INDEX,
    HND_EARLY_HP_INDEX,
    HND_DARKNUT_INDEX,
    HND_DOT_SKIP_INDEX,
    HND_ARMOGOHMA_INDEX,
    HND_POST_TOT_INDEX,
    HND_HOTSPRING_INDEX,
    HND_BELL_INDEX,
    HND_FBF_INDEX,
    HND_PUZZLE_INDEX,
    HND_ARCHERY_INDEX,
    HND_CITY_EARLY_INDEX,
    HND_CITY_1_INDEX,
    HND_AERALFOS_INDEX,
    HND_CITY_2_INDEX,
    HND_POE_CYCLE_INDEX,
    HND_FAN_TOWER_INDEX,
    HND_ARGOROK_INDEX,
    HND_STAR_2_INDEX,
    HND_PALACE_1_INDEX,
    HND_PALACE_2_INDEX,
    HND_EARLY_PLATFORM_INDEX,
    HND_ZANT_INDEX,
    HND_COO_INDEX,
    HND_COO_10_INDEX,
    HND_COO_20_INDEX,
    HND_COO_30_INDEX,
    HND_CATS_INDEX,
    HND_HYRULE_INDEX,
    HND_DARKNUT_SKIP_INDEX,
    HND_FINAL_TOWER_INDEX,
    HND_BEAST_GANON_INDEX,
    HND_HORSEBACK_GANON_INDEX
};

extern bool hundo_saves_visible;

// scene
extern bool scene_menu_visible;
#define SCENE_AMNT 9
namespace Scene {
    enum SceneIndex {
        DISABLE_BG_INDEX,
        DISABLE_SFX_INDEX,
        FREEZE_ACTOR_INDEX,
        FREEZE_CAMERA_INDEX,
        HIDE_ACTOR_INDEX,
        HIDE_HUD_INDEX,
		FREEZE_TIME_INDEX,
        TIME_HOURS_INDEX,
        TIME_MINUTES_INDEX
    };

    struct SceneItem {
        enum SceneIndex id;
        bool active;
    };
}  // namespace Scene
extern Scene::SceneItem SceneItems[SCENE_AMNT];

// tools
#define TOOL_AMNT 15
namespace Tools {
    enum ToolsIndex {
        RELOAD_AREA_INDEX,
        FAST_BONK_INDEX,
        FAST_MOVEMENT_INDEX,
        GORGE_INDEX,
        INPUT_VIEWER_INDEX,
        LINK_DEBUG_INDEX,
        SAND_INDEX,
        ROLL_INDEX,
        TELEPORT_INDEX,
        TIMER_INDEX,
		LOAD_TIMER_INDEX,
		IGT_TIMER_INDEX,
		FREE_CAM_INDEX,
		MOVE_LINK_INDEX,
        TUNIC_COLOR_INDEX
    };

    struct Tool {
        enum ToolsIndex id;
        bool active;
    };

    void apply_cheats();
};  // namespace Tools

extern Tools::Tool ToolItems[TOOL_AMNT];

extern bool tools_visible;
extern int g_tunic_color;
extern bool g_tunic_color_flag;

enum tunic_color {
    GREEN,
    BLUE,
    RED,
    ORANGE,
    YELLOW,
    WHITE,
    CYCLE,
    TUNIC_COLOR_COUNT
};

struct TunicColor {
    char name[7];
    bool active;
};

#define TUNIC_COLOR_AMNT 7
extern TunicColor TunicColors[TUNIC_COLOR_AMNT];

// settings
enum SettingsIndex {
    AREA_RELOAD_BEHAVIOR_INDEX,
	CURSOR_COLOR_INDEX,
    DROP_SHADOWS_INDEX,
    // SAVE_CARD_INDEX,
    // LOAD_CARD_INDEX,
	POS_SETTINGS_MENU_INDEX
};
extern bool settings_visible;
extern bool pos_settings_visible;
extern bool g_drop_shadows;
extern int g_area_reload_behavior;
extern bool g_autoload_card;
extern int g_cursor_color;
extern bool g_cursor_color_flag;
extern int cursor_rgba;
#define LOAD_AREA 0
#define LOAD_FILE 1

enum cursor_colors {
	CURSOR_GREEN,
	CURSOR_BLUE,
	CURSOR_RED,
	CURSOR_ORANGE,
	CURSOR_YELLOW,
	CURSOR_PURPLE
};

#define SPRITES_AMNT 7
enum SpritesIndex {
    MENU_INDEX = 0,
    VIEWER_INDEX = 1,
    DEBUG_INFO_INDEX = 2,
    TIMER_SPR_INDEX = 3,
    LOAD_TIMER_SPR_INDEX = 4,
    IGT_TIMER_SPR_INDEX = 5,
    FIFO_SPR_INDEX = 6
};

extern Vec2 sprite_offsets[SPRITES_AMNT];

struct SaveLayout {
    Cheats::Cheat CheatItems[CHEAT_AMNT];
    Tools::Tool ToolItems[TOOL_AMNT];
} __attribute__((aligned(32)));

#define MAX_LIST_MEMBER_LENGTH 40
#define MAX_LIST_ITEMS 20
#define MAX_LINE_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 100

struct ListMember {
    char member[MAX_LIST_MEMBER_LENGTH];
};

struct Line {
    char line[MAX_LINE_LENGTH];
    const int idx;
    char description[MAX_DESCRIPTION_LENGTH];
    bool toggleable = false;
    bool* activation_flag;
    uint8_t max_y_cursor_options;
};

class Menu {
   public:
    Menu() {}
    virtual void render() = 0;
};

class MainMenu : public Menu {
   public:
    MainMenu() : Menu(){};
    static void render(Font& font);
};

class InventoryMenu : public Menu {
   public:
    InventoryMenu() : Menu() {}
    static void render(Font& font);
};

class PauseMenu : public Menu {
   public:
    PauseMenu() : Menu() {}
    static void render(Font& font);
};

class ItemWheelMenu : public Menu {
   public:
    ItemWheelMenu() : Menu() {}
    static void render(Font& font);
};

class AmountsMenu : public Menu {
   public:
    AmountsMenu() : Menu() {}
    static void render(Font& font);
};

class CheatsMenu : public Menu {
   public:
    CheatsMenu() : Menu() {}
    static void render(Font& font);
};

class WarpingMenu : public Menu {
   public:
    WarpingMenu() : Menu() {}
    static void render(Font& font);
};

class MemoryMenu : public Menu {
   public:
    MemoryMenu() : Menu() {}
    static void render(Font& font);
};
class WatchesMenu : public Menu {
   public:
    WatchesMenu() : Menu() {}
    static void render(Font& font);
};
class MemoryEditorMenu : public Menu {
   public:
    MemoryEditorMenu() : Menu() {}
    static void render(Font& font);
};

class FlagsMenu : public Menu {
   public:
    FlagsMenu() : Menu() {}
    static void render(Font& font);
};
class GeneralFlagsMenu : public Menu {
   public:
    GeneralFlagsMenu() : Menu() {}
    static void render(Font& font);
};
class DungeonFlagsMenu : public Menu {
   public:
    DungeonFlagsMenu() : Menu() {}
    static void render(Font& font);
};
class PortalFlagsMenu : public Menu {
   public:
    PortalFlagsMenu() : Menu() {}
    static void render(Font& font);
};
class TempFlagsMenu : public Menu {
   public:
    TempFlagsMenu() : Menu() {}
    static void render(Font& font);
};

class PracticeMenu : public Menu {
   public:
    PracticeMenu() : Menu() {}
    static void render(Font& font);
};

class AnySavesMenu : public Menu {
   public:
    AnySavesMenu() : Menu() {}
    static void render(Font& font);
};

class HundoSavesMenu : public Menu {
   public:
    HundoSavesMenu() : Menu() {}
    static void render(Font& font);
};

class SceneMenu : public Menu {
   public:
    SceneMenu() : Menu() {}
    static void render(Font& font);
};

class SettingsMenu : public Menu {
   public:
    SettingsMenu() : Menu() {}
    static void render(Font& font);
};

class PosSettingsMenu : public Menu {
   public:
    PosSettingsMenu() : Menu() {}
    static void render(Font& font);
    static void initDefaults();
};

class ToolsMenu : public Menu {
   public:
    ToolsMenu() : Menu() {}
    static void render(Font& font);
};

#define MAX_MENU_RENDER_FLAGS 22

struct MenuRenderFlag {
    bool* activation_flag;
    void (*render_function)(Font& font);
};

MenuRenderFlag MenuRenderFlags[MAX_MENU_RENDER_FLAGS] = {
    {&mm_visible, MainMenu::render},
    {&inventory_visible, InventoryMenu::render},
    {&item_wheel_visible, ItemWheelMenu::render},
    {&warping_visible, WarpingMenu::render},
    {&memory_visible, MemoryMenu::render},
    {&watches_visible, WatchesMenu::render},
    {&memory_editor_visible, MemoryEditorMenu::render},
    {&flags_menu_visible, FlagsMenu::render},
    {&general_flags_visible, GeneralFlagsMenu::render},
    {&dungeon_flags_visible, DungeonFlagsMenu::render},
    {&portal_flags_visible, PortalFlagsMenu::render},
    {&temp_flags_visible, TempFlagsMenu::render},
    {&prac_visible, PracticeMenu::render},
    {&cheats_visible, CheatsMenu::render},
    {&scene_menu_visible, SceneMenu::render},
    {&settings_visible, SettingsMenu::render},
    {&tools_visible, ToolsMenu::render},
    {&pause_visible, PauseMenu::render},
    {&amounts_visible, AmountsMenu::render},
    {&any_saves_visible, AnySavesMenu::render},
    {&hundo_saves_visible, HundoSavesMenu::render},
    {&pos_settings_visible, PosSettingsMenu::render}};

namespace MenuRendering {
    void render_active_menus(Font& font) {
        for (int i = 0; i < MAX_MENU_RENDER_FLAGS; i++) {
            if (*MenuRenderFlags[i].activation_flag) {
                MenuRenderFlags[i].render_function(font);
            }
        }
    }

    void close_active_menus() {
        for (int i = 0; i < MAX_MENU_RENDER_FLAGS; i++) {
            if (*MenuRenderFlags[i].activation_flag) {
                *MenuRenderFlags[i].activation_flag = false;
            }
        }
    }

    bool is_menu_open() {
        int menus_open = 0;
        for (int i = 0; i < MAX_MENU_RENDER_FLAGS; i++) {
            if (*MenuRenderFlags[i].activation_flag) {
                menus_open++;
            }
        }
        if (menus_open > 0) {
            return true;
        } else {
            return false;
		}
    }
};  // namespace MenuRendering
