#include "cheats.h"
#include "commands.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/d/d_procname.h"
#include "libtp_c/include/d/a/d_a_e_zs.h"
#include "libtp_c/include/d/a/d_a_e_s1.h"
#include "libtp_c/include/d/d_item.h"
#include "rels/include/patch.h"
#include "libtp_c/include/defines.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"
#include "fifo_queue.h"

#ifdef GCN_PLATFORM
#define INVINCIBLE_ENEMIES_OFFSET (0x328)
#define cc_at_check cc_at_check__FP10fopAc_ac_cP11dCcU_AtInfo
#endif
#ifdef WII_PLATFORM
#define INVINCIBLE_ENEMIES_OFFSET (0x244)
#define cc_at_check cc_at_check_fopAc_ac_c____dCcU_AtInfo___
#endif

extern "C" {
void* cc_at_check(void*, void*);
}

Cheat g_cheats[CHEAT_AMNT] = {
    {InfiniteAir, false},       {InfiniteArrows, false},    {InfiniteBombs, false},
    {InfiniteHearts, false},    {InfiniteOil, false},       {InfiniteRupees, false},
    {InfiniteSlingshot, false}, {Invincible, false},        {InvincibleEnemies, false},
    {MoonJump, false},          {DoorStorage, false},       {SuperClawshot, false},
    {UnrestrictedItems, false}, {TransformAnywhere, false}, {DisableItemTimer, false},
#ifdef WII_PLATFORM
    {GaleLJA, false},
#endif
};

bool l_doorCollision;

void GZ_applyCheats() {
    if (GZ_checkCheat(MoonJump)) {
        GZCmd_enable(CMD_MOON_JUMP);
    } else {
        GZCmd_disable(CMD_MOON_JUMP);
    }

    if (GZ_checkCheat(InvincibleEnemies)) {
        /* Patch cc_at_check instruction to nop out health subtraction */
        *reinterpret_cast<uint32_t*>((uint32_t)(&cc_at_check) + INVINCIBLE_ENEMIES_OFFSET) =
            0x60000000;  // nop
        DCFlushRange((void*)((uint32_t)(&cc_at_check) + INVINCIBLE_ENEMIES_OFFSET),
                     sizeof(uint32_t));
        ICInvalidateRange((void*)((uint32_t)(&cc_at_check) + INVINCIBLE_ENEMIES_OFFSET),
                          sizeof(uint32_t));

        /* Special handling for any enemy that doesn't use cc_at_check */
        node_class* node = g_fopAcTg_Queue.mpHead;
        for (int i = 0; i < g_fopAcTg_Queue.mSize; i++) {
            if (node != NULL) {
                create_tag_class* tag = (create_tag_class*)node;
                fopEn_enemy_c* actor = (fopEn_enemy_c*)tag->mpTagData;
                
                if (actor != NULL) {
                    switch (fopAcM_GetName(actor)) {
                    case PROC_E_ZS: {
                        daE_ZS_c* zs = static_cast<daE_ZS_c*>(actor);

                        // if action is damage action
                        if (zs->mAction == 2) {
                            zs->mAction = 1; // set back to wait action, mode 0
                            zs->mMode = 0;

                            zs->mCyl.mGObjInf.OnTgSetBit();  // turn back on hit collision
                            zs->mCyl.mGObjInf.OnCoSetBit();  // turn back on push collision
                            zs->mHealth = 20;  // reset health back to max
                        }
                        break;
                    }
                    case PROC_E_S1: {
                        e_s1_class* s1 = static_cast<e_s1_class*>(actor);
                        s1->mHealth = 50;

                        if (s1->mAction == 9 || s1->mAction == 5 || s1->mAction == 10) {
                            s1->mAction = 0;  // reset action back to idle if in damage/fail action
                        }
                        break;
                    }
                    }
                }
            }
            node = node->mpNextNode;
        }
    } else {
        /* Unpatch cc_at_check instruction to restore health subtraction */
        *reinterpret_cast<uint32_t*>((uint32_t)(&cc_at_check) + INVINCIBLE_ENEMIES_OFFSET) =
            0x7C030050;  // sub r0, r0, r3
        DCFlushRange((void*)((uint32_t)(&cc_at_check) + INVINCIBLE_ENEMIES_OFFSET),
                     sizeof(uint32_t));
        ICInvalidateRange((void*)((uint32_t)(&cc_at_check) + INVINCIBLE_ENEMIES_OFFSET),
                          sizeof(uint32_t));
    }

    if (GZ_checkCheat(Invincible)) {
        daAlink_c* player = dComIfGp_getPlayer();
        if (player != NULL) {
            for (int i = 0; i < 3; i++) {
                player->field_0x850[i].mGObjInf.OffTgSetBit();
                player->field_0x850[i].mGObjInf.ResetTgHit();
            }

            if (player->checkWolf()) {
                player->field_0xFB8.mGObjInf.OffTgSetBit();
                player->field_0xFB8.mGObjInf.ResetTgHit();
            }
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
            dComIfGp_getPlayer()->mLinkAcch.ClrWallNone();
            dComIfGp_getPlayer()->mLinkAcch.OffLineCheckNone();
            l_doorCollision = false;
        }
    }

    if (GZ_checkCheat(DisableItemTimer)) {
        daItemBase__data.field_0x16 = 0x7FFF;
    } else {
        daItemBase__data.field_0x16 = 240;
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
