#include "cheats.h"
#include "commands.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/patch.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/cheats_menu.h"
#include "gz_flags.h"

#define LINE_NUM CHEAT_AMNT

#ifdef GCN_PLATFORM
#define INVINCIBLE_ENEMIES_OFFSET (0x328)
#endif
#ifdef WII_PLATFORM
#define INVINCIBLE_ENEMIES_OFFSET (0x244)
#endif

Cursor CheatsMenu::cursor;

Cheat g_cheats[CHEAT_AMNT] = {
    {InfiniteAir, false},       {InfiniteArrows, false},    {InfiniteBombs, false},
    {InfiniteHearts, false},    {InfiniteOil, false},       {InfiniteRupees, false},
    {InfiniteSlingshot, false}, {Invincible, false},        {InvincibleEnemies, false},
    {MoonJump, false},          {DoorStorage, false},       {SuperClawshot, false},
    {UnrestrictedItems, false}, {TransformAnywhere, false},
#ifdef WII_PLATFORM
    {GaleLJA, false},
#endif
};

Line lines[LINE_NUM] = {
    {"infinite air", InfiniteAir, "Gives infinite air underwater", true,
     &g_cheats[InfiniteAir].active},
    {"infinite arrows", InfiniteArrows, "Always have 99 arrows", true,
     &g_cheats[InfiniteArrows].active},
    {"infinite bombs", InfiniteBombs, "Always have 99 bombs", true,
     &g_cheats[InfiniteBombs].active},
    {"infinite hearts", InfiniteHearts, "Always have full hearts", true,
     &g_cheats[InfiniteHearts].active},
    {"infinite oil", InfiniteOil, "Gives infinite lantern oil", true,
     &g_cheats[InfiniteOil].active},
    {"infinite rupees", InfiniteRupees, "Always have 1000 rupees", true,
     &g_cheats[InfiniteRupees].active},
    {"infinite slingshot", InfiniteSlingshot, "Always have 99 slingshot pellets", true,
     &g_cheats[InfiniteSlingshot].active},
    {"invincible", Invincible, "Disables Link's hurtbox", true, &g_cheats[Invincible].active},
    {"invincible enemies", InvincibleEnemies, "Make some enemies invincible", true,
     &g_cheats[InvincibleEnemies].active},
    {"moon jump", MoonJump, "Hold " MOON_JUMP_TEXT " to moon jump", true,
     &g_cheats[MoonJump].active},
    {"disable walls", DoorStorage, "Disables most wall collision", true,
     &g_cheats[DoorStorage].active},
    {"super clawshot", SuperClawshot, "Super fast / long Clawshot", true,
     &g_cheats[SuperClawshot].active},
    {"unrestricted items", UnrestrictedItems, "Disable item restrictions", true,
     &g_cheats[UnrestrictedItems].active},
    {"transform anywhere", TransformAnywhere, "Transform at any location", true,
     &g_cheats[TransformAnywhere].active},
#ifdef WII_PLATFORM
    {"gale LJA", GaleLJA, "Yeet everywhere", true, &g_cheats[GaleLJA].active},
#endif
};

bool l_doorCollision = false;

void GZ_applyCheats() {
    if (GZ_checkCheat(MoonJump)) {
        GZCmd_enable(CMD_MOON_JUMP);
    } else {
        GZCmd_disable(CMD_MOON_JUMP);
    }

    if (GZ_checkCheat(InvincibleEnemies)) {
        *reinterpret_cast<uint32_t*>(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET) =
            0x60000000;  // nop
        DCFlushRange((void*)(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET), sizeof(uint32_t));
        ICInvalidateRange((void*)(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET),
                          sizeof(uint32_t));
    } else {
        *reinterpret_cast<uint32_t*>(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET) =
            0x7C030050;  // sub r0, r0, r3
        DCFlushRange((void*)(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET), sizeof(uint32_t));
        ICInvalidateRange((void*)(tp_cc_at_check_addr + INVINCIBLE_ENEMIES_OFFSET),
                          sizeof(uint32_t));
    }

    if (GZ_checkCheat(Invincible)) {
        if (dComIfGp_getPlayer()) {
            dComIfGp_getPlayer()->mDamageTimer = 5;
        }
    }

    if (GZ_checkCheat(InfiniteHearts)) {
        uint16_t max_life = dComIfGs_getMaxLife();
        dComIfGs_setLife((max_life / 5) * 4);
    }

    if (GZ_checkCheat(InfiniteAir)) {
        dComIfGs_setOxygen(600);
    }

    if (GZ_checkCheat(InfiniteOil)) {
        dComIfGs_setOil(21600);
    }

    if (GZ_checkCheat(InfiniteBombs)) {
        dComIfGs_setBombNum(BOMB_BAG_1, 99);
        dComIfGs_setBombNum(BOMB_BAG_2, 99);
        dComIfGs_setBombNum(BOMB_BAG_3, 99);
    }

    if (GZ_checkCheat(InfiniteRupees)) {
        dComIfGs_setRupee(1000);
    }

    if (GZ_checkCheat(InfiniteArrows)) {
        dComIfGs_setArrowNum(99);
    }

    if (GZ_checkCheat(InfiniteSlingshot)) {
        dComIfGs_setPachinkoNum(99);
    }

    if (GZ_checkCheat(SuperClawshot)) {
        daAlinkHIO_hookshot.mShootSpeed = 2870.0f;
        daAlinkHIO_hookshot.mMaxLength = 69420.0f;
        daAlinkHIO_hookshot.mReturnSpeed = 2870.0f;
        daAlinkHIO_hookshot.mClawReturnSpeed = 500.0f;
    } else {
        daAlinkHIO_hookshot.mShootSpeed = 100.0f;
        daAlinkHIO_hookshot.mMaxLength = 2000.0f;
        daAlinkHIO_hookshot.mReturnSpeed = 150.0f;
        daAlinkHIO_hookshot.mClawReturnSpeed = 60.0f;
    }

    if (GZ_checkCheat(DoorStorage)) {
        if (dComIfGp_getPlayer()) {
            dComIfGp_getPlayer()->mLinkAcch.SetWallNone();
            dComIfGp_getPlayer()->mLinkAcch.OnLineCheckNone();
            l_doorCollision = true;
        }
    } else {
        if (dComIfGp_getPlayer() && l_doorCollision) {
            dComIfGp_getPlayer()->mLinkAcch.OffWallNone();
            dComIfGp_getPlayer()->mLinkAcch.OffLineCheckNone();
            l_doorCollision = false;
        }
    }
#ifdef WII_PLATFORM

    if (GZ_checkCheat(GaleLJA)) {
        if (dComIfGp_getPlayer() && dComIfGp_getPlayer()->mActionID == 0x60 &&
            dComIfGp_getPlayer()->mEquipItem == NO_ITEM) {
            dComIfGp_getPlayer()->mEquipItem = 0x0103;
        }
    }
#endif
}

void CheatsMenu::draw() {
    cursor.move(0, LINE_NUM);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(MN_MAIN_MENU_INDEX);
        return;
    }

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_cheats[cursor.y].active = !g_cheats[cursor.y].active;
    }

    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}