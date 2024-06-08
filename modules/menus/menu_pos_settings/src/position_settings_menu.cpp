#include "menus/menu_pos_settings/include/position_settings_menu.h"
#include <cstdio>
#include "utils/draw.h"
#include "fifo_queue.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define INITAL_SPEED 1.0f
#define INCREMENT_FACTOR 1.05f
#define MAX_SPEED 20.f

KEEP_FUNC PosSettingsMenu::PosSettingsMenu(Cursor& cursor, PosSettingsData& data)
    : Menu(cursor), init_once(data.init_once), l_cursorSpeed(data.l_cursorSpeed),
      l_selItem(data.l_selItem),
      lines{{"main menu", SpritesIndex::MENU_INDEX, "Change main menu position", false},
            {"input viewer", SpritesIndex::VIEWER_INDEX, "Change input viewer position", false},
            {"link debug info", SpritesIndex::DEBUG_INFO_INDEX, "Change link debug info position",
             false},
            {"timer", SpritesIndex::TIMER_SPR_INDEX, "Change timer position", false},
            {"load timer", SpritesIndex::LOAD_TIMER_SPR_INDEX, "Change load timer position", false},
            {"igt timer", SpritesIndex::IGT_TIMER_SPR_INDEX, "Change IGT timer position", false},
            {"fifo queue", SpritesIndex::FIFO_SPR_INDEX, "Change fifo queue position", false},
            {"heap info", SpritesIndex::HEAP_INFO_INDEX, "Change Heap info position", false},
            {"mash checker", SpritesIndex::MASH_INFO_INDEX, "Change Mash Checker position", false},
            {"transform indicator", SpritesIndex::TRANSFORM_IND_INDEX, "Change Transform Indicator position", false}} {}

PosSettingsMenu::~PosSettingsMenu() {}

#ifdef WII_PLATFORM
extern bool isWidescreen;
#else
#define isWidescreen (false)
#endif

void drawCursor(Vec2 pos) {
    bool cycle = (cCt_getFrameCount() / 8) % 2;
    if (GZ_checkDropShadows()) {
        Draw::drawRectOutline(DROP_SHADOWS_RGBA, {pos.x - 10 * (isWidescreen ? 0.75f : 1.0f) + 1, pos.y + 1}, {20 * (isWidescreen ? 0.75f : 1.0f), 0}, 0xA);
        Draw::drawRectOutline(DROP_SHADOWS_RGBA, {pos.x + 1, pos.y - 10 + 1}, {0, 20}, 0xA);
    }
    Draw::drawRectOutline(cycle ? g_cursorColor : 0xFFFFFFFF, {pos.x - 10 * (isWidescreen ? 0.75f : 1.0f), pos.y}, {20 * (isWidescreen ? 0.75f : 1.0f), 0}, 0xA);
    Draw::drawRectOutline(cycle ? g_cursorColor : 0xFFFFFFFF, {pos.x, pos.y - 10}, {0, 20}, 0xA);
}

GZSettingID l_mapping[] = {
    STNG_SPRITES_MENU,
    STNG_SPRITES_INPUT_VIEWER,
    STNG_SPRITES_DEBUG_INFO,
    STNG_SPRITES_TIMER_SPR,
    STNG_SPRITES_LOAD_TIMER_SPR,
    STNG_SPRITES_IGT_TIMER_SPR,
    STNG_SPRITES_FIFO_SPR,
    STNG_SPRITES_HEAP_INFO,
    STNG_SPRITES_MASH_INFO,
    STNG_SPRITES_TRANSFORM_IND,
};

void PosSettingsMenu::draw() {
    cursor.setMode(Cursor::MODE_UNRESTRICTED);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        if (l_selItem != POSITION_SETTINGS_NO_SELECTION) {
            l_selItem = POSITION_SETTINGS_NO_SELECTION;
        } else {
            init_once = false;
            g_menuMgr->pop();
            return;
        }
    }

    if (!init_once) {
        l_selItem = POSITION_SETTINGS_NO_SELECTION;
        init_once = true;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        if (cursor.y < SPRITES_AMNT) {
            l_selItem = l_selItem == cursor.y ? POSITION_SETTINGS_NO_SELECTION : cursor.y;
        }
    }

    auto* stng = GZStng_getSetting(l_mapping[l_selItem]);
    if (!stng) {
        stng = new GZSettingEntry{l_mapping[l_selItem], sizeof(Vec2), new Vec2{0.0f, 0.0f}};
        g_settings.push_back(stng);
    }
    if (l_selItem != POSITION_SETTINGS_NO_SELECTION && l_selItem < SPRITES_AMNT) {
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT, 3)) {
            static_cast<Vec2*>(stng->data)->x += l_cursorSpeed;
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_LEFT, 3)) {
            static_cast<Vec2*>(stng->data)->x -= l_cursorSpeed;
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_UP, 3)) {
            static_cast<Vec2*>(stng->data)->y -= l_cursorSpeed;
        }
        if (GZ_getButtonRepeat(GZPad::DPAD_DOWN, 3)) {
            static_cast<Vec2*>(stng->data)->y += l_cursorSpeed;
        }

        // Draw visual cursor
        drawCursor(*static_cast<Vec2*>(stng->data));
    }

    if (GZ_getButtonPressed(GZPad::DPAD_RIGHT) || GZ_getButtonPressed(GZPad::DPAD_LEFT) ||
        GZ_getButtonPressed(GZPad::DPAD_UP) || GZ_getButtonPressed(GZPad::DPAD_DOWN)) {
        if (l_cursorSpeed < MAX_SPEED) {
            l_cursorSpeed *= INCREMENT_FACTOR;
        }
        if (l_cursorSpeed > MAX_SPEED) {
            l_cursorSpeed = MAX_SPEED;
        }
    } else {
        l_cursorSpeed = INITAL_SPEED;
    }

    cursor.lock_x = l_selItem != POSITION_SETTINGS_NO_SELECTION;
    cursor.lock_y = l_selItem != POSITION_SETTINGS_NO_SELECTION;

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
