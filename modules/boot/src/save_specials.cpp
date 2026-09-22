#include "save_specials.h"
#include "gz_flags.h"
#include "libtp_c/include/utils.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/f_op/f_op_actor_iter.h"
#include "libtp_c/include/rel/d/a/b/d_a_b_ds.h"
#include "libtp_c/include/d/a/d_a_e_zs.h"
#include "libtp_c/include/rel/d/a/obj/d_a_obj_lv4sand.h"
#include "libtp_c/include/d/d_procname.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "rels/include/defines.h"

typedef bool (*predicate_t)(fopAc_ac_c&);

fopAc_ac_c* find_actor(predicate_t const& predicate) {
    if (predicate == nullptr) {
        return nullptr;
    }
    node_class* node = g_fopAcTg_Queue.mpHead;
    fopAc_ac_c* actorData = NULL;
    for (int i = 0; i < g_fopAcTg_Queue.mSize; i++) {
        if (node != NULL) {
            create_tag_class* tag = (create_tag_class*)node;
            fopAc_ac_c* tmpData = (fopAc_ac_c*)tag->mpTagData;
            if (predicate(*tmpData)) {
                actorData = tmpData;
                break;
            }
            node = node->mpNextNode;
        }
    }
    return actorData;
}

#if defined(WII_NTSCU_10) || defined(WII_PAL)
#define ROCK_ID 763
#else
#define ROCK_ID 765
#endif

KEEP_FUNC void SaveMngSpecial_OrdonRock() {
    gSaveManager.setSaveAngle(32768);
    gSaveManager.setSavePosition(400.0f, 307.5f, -11270.2f);
    gSaveManager.setLinkInfo();

    cXyz position(400.0f, 307.8f, -11365.f);

    fopAc_ac_c* actorData = find_actor([](fopAc_ac_c& act) {
        return act.mBase.mProcName == ROCK_ID && act.mBase.mParameters == 0x00FF6511;
    });

    if (actorData != NULL) {
        actorData->current.pos = position;
        actorData->shape_angle.y = 5880;
    }
}

KEEP_FUNC void SaveMngSpecial_BossFlags() {
    gSaveManager.injectDefault_during();
    bossFlags = 0xFF;
}

KEEP_FUNC void SaveMngSpecial_Goats1() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(5);
    dComIfGs_onTmpBit(0x1480); // disable fado text
}

KEEP_FUNC void SaveMngSpecial_Hugo() {
    gSaveManager.injectDefault_during();
    dComIfGs_onSwitch(47, 0);   // midna trigger off
    dComIfGs_offSwitch(63, 0);  // hugo alive
}

#if defined(WII_NTSCU_10) || defined(WII_PAL)
#define HUGO_ACTOR_ID 466
#else
#define HUGO_ACTOR_ID 468
#endif

KEEP_FUNC void SaveMngSpecial_SpawnHugo() {
    gSaveManager.setSaveAngle(40166);
    gSaveManager.setSavePosition(2.9385, 396.9580, -18150.087);
    gSaveManager.setLinkInfo();

    cXyz position(-289.9785, 401.5400, -18533.078);

    // Find hugo in the actor list
    fopAc_ac_c* actorData =
        find_actor([](auto& act) { return act.mBase.mProcName == HUGO_ACTOR_ID; });

    if (actorData != NULL) {
        actorData->current.pos = position;
        actorData->shape_angle.y = 5880;
    }
}

#if defined(WII_NTSCU_10) || defined(WII_PAL)
#define BUBBLE_ACTOR_ID 489
#else
#define BUBBLE_ACTOR_ID 491
#endif

KEEP_FUNC void SaveMngSpecial_PurpleMist() {
    gSaveManager.injectDefault_during();
    dComIfGs_setTransformStatus(STATUS_HUMAN);
}

KEEP_FUNC void SaveMngSpecial_ForestBit() {
    gSaveManager.injectDefault_during();
    dComIfGp_getPlayer()->mNoResetFlg2 |= 1; // lantern out
    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
    gSaveManager.setSaveAngle(32768);
    gSaveManager.setSavePosition(45.0f, 1911.1345f, 20425.0f);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_KargOoB() {
    gSaveManager.mPracticeFileOpts.inject_options_before_load = nullptr;
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0xA;  // spawn on kargorok
    dComIfGs_setTransformStatus(STATUS_HUMAN);
}

KEEP_FUNC void SaveMngSpecial_WaterfallSidehop() {
    SaveMngSpecial_RemoveAreaBannerBefore_ZorasDomain();
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 10.0f;  // link spawns swimming forward
}

KEEP_FUNC void SaveMngSpecial_EarlyEle() {
    gSaveManager.injectDefault_during();
    dComIfGs_onTmpBit(0x0002);
    dComIfGs_onTmpBit(0x0004); // rusl td
}

KEEP_FUNC void SaveMngSpecial_ElevatorEscape() {
    gSaveManager.injectDefault_during();
    dComIfGp_getPlayer()->onNoResetFlg0(daPy_py_c::FLG0_EQUIP_HVY_BOOTS);
    dComIfGs_onTmpBit(0x0002);
    dComIfGs_onTmpBit(0x0004); // rusl td
}

KEEP_FUNC void SaveMngSpecial_EarlyEleSpawn() {
    gSaveManager.setSaveAngle(43917);
    gSaveManager.setSavePosition(1130, -355.6, -5569);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_HorseSpawn() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 1;  // spawn on epona
}

KEEP_FUNC void SaveMngSpecial_EldinCollection() {
    SaveMngSpecial_HorseSpawn();
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 42.0f;
}

KEEP_FUNC void SaveMngSpecial_KB2Skip() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(3);
}

KEEP_FUNC void SaveMngSpecial_Escort() {
    gSaveManager.injectDefault_during();
    setNextStageRoom(0xD);
    setNextStagePoint(98);
    setNextStageLayer(2);
}

KEEP_FUNC void SaveMngSpecial_EscortLJA() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(2);
}

KEEP_FUNC void SaveMngSpecial_EscortKeys() {
    dComIfGs_setKeyNum(2);  // give 2 keys for field gates
}

KEEP_FUNC void SaveMngSpecial_Dangoro() {
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x200000;  // turn off intro cs, start fight
}

KEEP_FUNC void SaveMngSpecial_Norgor() {
    g_meter2_info.mRentalBombBag = 0;  // Rental Bomb Bag Idx set to bag 0
    dComIfGs_setItem(SLOT_15, NORMAL_BOMB);
    dComIfGs_setBombNum(0, 30);
    dComIfGs_setSelectItemIndex(SELECT_ITEM_Y, SLOT_15);
}

KEEP_FUNC void SaveMngSpecial_LakebedBKSkip() {
    gSaveManager.injectDefault_during();
    dComIfGs_onSwitch(2, 0);    // bridge turned
    dComIfGs_onSwitch(122, 0);  // dungeon intro cs off
}

KEEP_FUNC void SaveMngSpecial_Darkhammer() {
    dComIfGs_onEventBit(0x0B02);
    dComIfGs_onEventBit(0x0B04);  // iza bomb bag stolen
}

KEEP_FUNC void SaveMngSpecial_Morpheel() {
    dComIfGp_getPlayer()->mEquipItem = HOOKSHOT;                        // clawshot
    dComIfGp_getPlayer()->onNoResetFlg0(daPy_py_c::FLG0_EQUIP_HVY_BOOTS);  // ib
    gSaveManager.setSaveAngle(10754);
    gSaveManager.setSavePosition(-1193.0f, -23999.0f, -770.0f);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_Iza1Skip() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0xA;  // spawn on kargorok
    setNextStageName("F_SP112");                       // set stage to river
    setNextStageRoom(1);
    setNextStagePoint(0);
    setNextStageLayer(4);
}

KEEP_FUNC void SaveMngSpecial_AnyPlummOoB() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0xA;  // spawn on kargorok
    setNextStageName("F_SP112");                       // set stage to river
    setNextStageRoom(1);
    setNextStagePoint(0);
    setNextStageLayer(4);
    bossFlags = 0xFF;
}

KEEP_FUNC void SaveMngSpecial_Stallord() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
}

KEEP_FUNC void SaveMngSpecial_Stallord2() {
    daB_DS_c* stallord = (daB_DS_c*)fopAcM_SearchByName(PROC_B_DS);

    // create the phase 2 version of stallord
    fopAcM_create(PROC_B_DS, fopAcM_GetParam(stallord) | 2, &stallord->current.pos,
                fopAcM_GetRoomNo(stallord), nullptr, nullptr, -1);
    fopAcM_delete(stallord);  // delete phase 1 stallord

    daObjLv4Wall_c* rwall = (daObjLv4Wall_c*)fopAcM_SearchByName(PROC_Obj_Lv4RailWall);
    daObjSwSpinner_c* spinnersw = (daObjSwSpinner_c*)fopAcM_SearchByName(PROC_Obj_SwSpinner);

    spinnersw->mRotSpeedY = 3000;  // set arena spinner switch to max speed
    rwall->field_0x954 = 101;  // set spinner switch speed counter to threshold
    rwall->mHeight = 3370.0f;  // set arena height to max
}

KEEP_FUNC void SaveMngSpecial_Stallord2_init() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
}

KEEP_FUNC void SaveMngSpecial_StallordCad() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
    //gSaveManager.setSaveAngle(60562);
    gSaveManager.setSaveAngle(59392);
    //gSaveManager.setSavePosition(327.221771f, 1800.0f, -4990.98975f); // corner for old diagonal setup
    gSaveManager.setSavePosition(50.997982f, 1775.0f, -4024.03882f);
    gSaveManager.setLinkInfo();

    SaveMngSpecial_CenterCamera();

    // Find joseph in the actor list
    fopAc_ac_c* actorData1 =
        find_actor([](auto& act) { return act.mBase.mProcName == PROC_E_ZS && (int) act.current.pos.x == -920; });

    daE_ZS_c* joseph = (daE_ZS_c*) actorData1;
    joseph->mAction = 1; // not functionally important, slouching idle with both arms down
    joseph->mMode = 0; // not functionally important, slouching idle with both arms down

    // cXyz posi (327.221771, 1800.0, -4990.98975);
    // joseph->current.pos = posi;
    daE_ZS_c__setBck_void_(joseph, 9, 2, 3.0f, 1.0f); // rise up animation
    joseph->field_0x65c = 0; // something something vertical matrix
    joseph->field_0x673 = 1; // visibility?
    joseph->mCyl.mGObjInf.OnTgSetBit(); // hitbox
    joseph->mCyl.mGObjInf.OnCoSetBit(); // push collider
    joseph->mStatus |= 0x200000; // clawshottable
}

KEEP_FUNC void SaveMngSpecial_StallordWallClip() {
    gSaveManager.injectDefault_during();
    dComIfGs_setSelectItemIndex(SELECT_ITEM_X, SLOT_0); // rang on x
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
    gSaveManager.setSaveAngle(32741);
    gSaveManager.setSavePosition(356.972076f, 1775.0f, -4439.97656f);
    gSaveManager.setLinkInfo();

    // Find joseph in the actor list
    fopAc_ac_c* actorData1 =
        find_actor([](auto& act) { return act.mBase.mProcName == PROC_E_ZS && (int) act.current.pos.x == -920; });

    daE_ZS_c* joseph = (daE_ZS_c*) actorData1;
    joseph->mAction = 1; // not functionally important, slouching idle with both arms down
    joseph->mMode = 0; // not functionally important, slouching idle with both arms down
    
    daE_ZS_c__setBck_void_(joseph, 9, 2, 3.0f, 1.0f); // rise up animation
    joseph->field_0x65c = 0; // something something vertical matrix
    joseph->field_0x673 = 1; // visibility?
    joseph->mCyl.mGObjInf.OnTgSetBit(); // hitbox
    joseph->mCyl.mGObjInf.OnCoSetBit(); // push collider
    joseph->mStatus |= 0x200000; // clawshottable
    cXyz corner (301.9, 1800.0, -4966.0);
    joseph->current.pos = corner;
}

KEEP_FUNC void SaveMngSpecial_StallordBombBoost() {
    gSaveManager.injectDefault_during();
    dComIfGs_setSelectItemIndex(SELECT_ITEM_X, SLOT_0); // rang on x
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
    gSaveManager.setSaveAngle(32097);
    gSaveManager.setSavePosition(623.792603f, 1800.0f, -4914.61377f);
    gSaveManager.setLinkInfo();

    // Find joseph in the actor list
    fopAc_ac_c* actorData1 =
        find_actor([](auto& act) { return act.mBase.mProcName == PROC_E_ZS && (int) act.current.pos.x == -920; });

    daE_ZS_c* joseph = (daE_ZS_c*) actorData1;
    joseph->mAction = 1; // not functionally important, slouching idle with both arms down
    joseph->mMode = 0; // not functionally important, slouching idle with both arms down
    
    daE_ZS_c__setBck_void_(joseph, 9, 2, 3.0f, 1.0f); // rise up animation
    joseph->field_0x65c = 0; // something something vertical matrix
    joseph->field_0x673 = 1; // visibility?
    joseph->mCyl.mGObjInf.OnTgSetBit(); // hitbox
    joseph->mCyl.mGObjInf.OnCoSetBit(); // push collider
    joseph->mStatus |= 0x200000; // clawshottable
    cXyz corner (301.9, 1800.0, -4966.0);
    joseph->current.pos = corner;
}

KEEP_FUNC void SaveMngSpecial_StallordDisplacementClip() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
    gSaveManager.setSaveAngle(59392);
    gSaveManager.setSavePosition(-327.861115f, 1800.0f, -4990.23926f);
    gSaveManager.setLinkInfo();

    // Find joseph in the actor list
    fopAc_ac_c* actorData1 =
        find_actor([](auto& act) { return act.mBase.mProcName == PROC_E_ZS && (int) act.current.pos.x == -920; });

    daE_ZS_c* joseph = (daE_ZS_c*) actorData1;
    joseph->mAction = 1; // not functionally important, slouching idle with both arms down
    joseph->mMode = 0; // not functionally important, slouching idle with both arms down
    
    daE_ZS_c__setBck_void_(joseph, 9, 2, 3.0f, 1.0f); // rise up animation
    joseph->field_0x65c = 0; // something something vertical matrix
    joseph->field_0x673 = 1; // visibility?
    joseph->mCyl.mGObjInf.OnTgSetBit(); // hitbox
    joseph->mCyl.mGObjInf.OnCoSetBit(); // push collider
    joseph->mStatus |= 0x200000; // clawshottable
    cXyz corner (-301.9, 1800.0, -4966.0);
    joseph->current.pos = corner;
}

#if defined(WII_NTSCU_10) || defined(WII_PAL)
#define ZANT_ACTOR_ID 247
#else
#define ZANT_ACTOR_ID 249
#endif

KEEP_FUNC void SaveMngSpecial_ZantFinal() {
    class daB_ZANT_c {
    public:
        /* 0x0000 */ fopEn_enemy_c base;
        /* 0x05AC */ u8 field_0x5ac[0x6d4 - 0x5ac];
        /* 0x06D4 */ int mAction;
        /* 0x06D8 */ int field_0x6d8;
        /* 0x06DC */ int mMode;
        /* 0x06E0 */ u8 field_0x6e0[0x1b];
        /* 0x06FB */ u8 mFightPhase;
    };

    // Find zant in the actor list
    daB_ZANT_c* actorData = (daB_ZANT_c*)find_actor([](auto& act) { return act.mBase.mProcName == PROC_B_ZANT; });

    // Set his action, fight phase and mode to trigger the transition demo
    if (actorData != nullptr) {
        // Set Zant's state
        actorData->mAction = 23;      // ACT_ROOM_CHANGE
        actorData->mFightPhase = 5;   // PHASE_YO
        actorData->mMode = 0;         // MODE_START_DEMO
    }

    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
}

KEEP_FUNC void SaveMngSpecial_ZantDangoro() {
    class daB_ZANT_c {
    public:
        /* 0x0000 */ fopEn_enemy_c base;
        /* 0x05AC */ u8 field_0x5ac[0x6d4 - 0x5ac];
        /* 0x06D4 */ int mAction;
        /* 0x06D8 */ int field_0x6d8;
        /* 0x06DC */ int mMode;
        /* 0x06E0 */ u8 field_0x6e0[0x1b];
        /* 0x06FB */ u8 mFightPhase;
    };

    // Find zant in the actor list
    daB_ZANT_c* actorData = (daB_ZANT_c*)find_actor([](auto& act) { return act.mBase.mProcName == PROC_B_ZANT; });

    // Set his action, fight phase and mode to trigger the transition demo

    if (actorData != nullptr) {
        // Set Zant's state
        actorData->mAction = 0;      // ACT_SMALL_ATTACK
        //actorData->mFightPhase = 5;   // PHASE_YO
        //actorData->mMode = 0;         // MODE_START_DEMO
        actorData->base.current.pos.set(-200.0f, -1050.0f, -1250.0f);
    }
    //cXyz(-1000.0f, 400.0f, 1500.0f),

    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
    gSaveManager.setSaveAngle(32768);
    gSaveManager.setSavePosition(-200.0f, -800.0f, -850.0f);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_SPRBossKey() {
    gSaveManager.injectDefault_during();
    setNextStageRoom(0xB);  // boss key room
    setNextStagePoint(0);   // default spawn
}

KEEP_FUNC void SaveMngSpecial_ToTEarlyPoe() {
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(49299);
    gSaveManager.setSavePosition(-2462.85f, 2750.0f, -7.10f);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_ToTEarlyHP() {
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(0);
    gSaveManager.setSavePosition(-6626.f, 5250.0f, -5587.f);
    gSaveManager.setLinkInfo();
    dComIfGs_onSwitch(224, 4);  // gate moved to correct pos
}

KEEP_FUNC void SaveMngSpecial_HugoArchery() {
    gSaveManager.injectDefault_during();
    // g_dComIfG_gameInfo.temp_flags.flags[14] = 0xC0;  // start archery minigame
}

KEEP_FUNC void SaveMngSpecial_CityPoeCycle() {
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(0);
    gSaveManager.setSavePosition(-13990.0f, 3000.0f, -16200.0f);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_FanTower() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;  // reset city switches
}

KEEP_FUNC void SaveMngSpecial_Argorok() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x10000;
}

KEEP_FUNC void SaveMngSpecial_Palace1() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;  // reset palace switches
}

KEEP_FUNC void SaveMngSpecial_Palace2() {
    gSaveManager.injectDefault_during();
    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
    // gSaveManager.setSaveAngle(32731);
    // gSaveManager.setSavePosition(251.83f, 1400.0f, 584.0f);
    // gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_CaveOfOrdeals() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;
}

KEEP_FUNC void BeastGanonSpecial_setLayer() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(1);
}

KEEP_FUNC void SaveMngSpecial_emptyLake() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(4);
    bossFlags = 0xFF;
}

KEEP_FUNC void SaveMngSpecial_Aeralfos() {
    gSaveManager.injectDefault_during();
    dComIfGp_getPlayer()->mEquipItem = HOOKSHOT; // claw out (doesn't show as out, but still is for this intention, which is that b will slash)
}

KEEP_FUNC void SaveMngSpecial_NoSQAeralfos() {
    gSaveManager.injectDefault_during();
    dComIfGs_setLife(4);  // one heart
}

KEEP_FUNC void SaveMngSpecial_DeathSword() {
    gSaveManager.injectDefault_during();
    dComIfGs_setLife(2);  // half heart
}

KEEP_FUNC void SaveMngSpecial_ArgorokCSSkip() {
    gSaveManager.injectDefault_during();
    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
    // gSaveManager.setSaveAngle(16267);
    // gSaveManager.setSavePosition(-10406.9248f, 0.0f, -12446.7979f);
    // gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_PalaceBossKey() {
    gSaveManager.injectDefault_during();
    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
}

KEEP_FUNC void SaveMngSpecial_EarlyPlatform() {
    gSaveManager.injectDefault_during();
    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
}

KEEP_FUNC void SaveMngSpecial_reBiTE() {
    setNextStageLayer(2);
}

KEEP_FUNC void SaveMngSpecial_MDHBridge() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 25.0f;
}

#if defined(WII_NTSCU_10) || defined(WII_PAL)
#define WOLFOS_ACTOR_ID 519
#else
#define WOLFOS_ACTOR_ID 521
#endif

KEEP_FUNC void SaveMngSpecial_SPR_MBBB() {
    fopAc_ac_c* actorData1 = find_actor([](auto& act) { return act.mBase.mProcName == WOLFOS_ACTOR_ID; });
    fopAcM_delete(actorData1); // delete wolfos
    fopAc_ac_c* actorData2 = find_actor([](auto& act) { return act.mBase.mProcName == WOLFOS_ACTOR_ID; });
    fopAcM_delete(actorData2); // delete wolfos

    gSaveManager.setSaveAngle(49152);
    gSaveManager.setSavePosition(659.949341, 50, -2762.14014); // corner of wall
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_SPR_SpinnerBoost() {
    fopAc_ac_c* actorData1 = find_actor([](auto& act) { return act.mBase.mProcName == WOLFOS_ACTOR_ID; });
    fopAcM_delete(actorData1); // delete wolfos
    fopAc_ac_c* actorData2 = find_actor([](auto& act) { return act.mBase.mProcName == WOLFOS_ACTOR_ID; });
    fopAcM_delete(actorData2); // delete wolfos

    gSaveManager.setSaveAngle(49152);
    gSaveManager.setSavePosition(1998.8147, 0, -1984.20801); // corner of wall
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_KB1Phase2() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(4); // phase 2
}

KEEP_FUNC void SaveMngSpecial_KB4() {
    gSaveManager.injectDefault_during();
    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
    gSaveManager.setSaveAngle(24354);
    gSaveManager.setSavePosition(-8566.32617f, 200.0f, -4870.11084f);
    gSaveManager.setLinkInfo();

    SaveMngSpecial_CenterCamera();
}

KEEP_FUNC void SaveMngSpecial_Wormhole() {
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(32768);
    gSaveManager.setSavePosition(1.7732302f, 1503.0f, 7134.00684f);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_AGEarlyBk() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 25.0f;
}

KEEP_FUNC void SaveMngSpecial_Sword() {
    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
}

KEEP_FUNC void SaveMngSpecial_ZD_Yellows() {
    dComIfGs_onItemFirstBit(YELLOW_RUPEE); // yellow text
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 25.0f;
}

KEEP_FUNC void SaveMngSpecial_RopeSkip() {
    setNextStageLayer(2);
    //g_dComIfG_gameInfo.info.mRestart.mLastMode |= 0x100000; // holding first sol
}

KEEP_FUNC void SaveMngSpecial_HoldSol() {
    g_dComIfG_gameInfo.info.mRestart.mLastMode |= 0x100000; // holding first sol
    // 2nd sol is 0x80000
}

// ---- WII 100% START ----

#if defined(WII_NTSCU_10) || defined(WII_PAL)
#define SMALL_POT_ID 762
#else
#define SMALL_POT_ID 764
#endif

KEEP_FUNC void SaveMngSpecial_MidnaDivePot() {
    gSaveManager.setSaveAngle(28225);
    gSaveManager.setSavePosition(-95846.8359f, -24550.7012f, 32464.5996f);
    gSaveManager.setLinkInfo();

    int type = 7; // small red pot
    u16 angleZ = ((u16)type << 1) & 0x1F; // extra params, like type of pot, is stored in the z angle on init
    u32 params = 0x00003FFF;
    s8 roomNo = dComIfGp_getPlayer()->current.roomNo;
    cXyz position1 (-95882.8f, -24400.0f, 32388.6f);
    csXyz someangle(0, 21487, angleZ);

    fopAcM_create(SMALL_POT_ID, params, &position1, roomNo, &someangle, nullptr, -1);
}

KEEP_FUNC void SaveMngSpecial_KargOoBWolf() {
    gSaveManager.mPracticeFileOpts.inject_options_before_load = nullptr;
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0xA;  // spawn on kargorok
}

KEEP_FUNC void SaveMngSpecial_SetDigging() {
    gSaveManager.mPracticeFileOpts.inject_options_before_load = nullptr;
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 9; // dig exit mode
}

KEEP_FUNC void SaveMngSpecial_KB1TriggerSkip() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(2);
}

KEEP_FUNC void SaveMngSpecial_HFNGrotto() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(3);
}

KEEP_FUNC void SaveMngSpecial_CoO10() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] |= 0x300;
}

KEEP_FUNC void SaveMngSpecial_CoO20() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] |= 0x80000;
}

KEEP_FUNC void SaveMngSpecial_CoO30() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] |= 0x20000000;
}

KEEP_FUNC void SaveMngSpecial_CoO40() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[1] |= 0x80;
}

// ---- WII 100% END ----

KEEP_FUNC void SaveMngSpecial_Argorok2_after() {
    SaveMngSpecial_BossFlags();
    // class daB_DR_c {
    // public:
    //     /* 0x0000 */ fopEn_enemy_c base;
    //     /* 0x05AC */ u8 field_0x5ac[0x6d4 - 0x5ac];
    //     /* 0x06D4 */ int mAction;
    // };

    // daB_DR_c* actorData = (daB_DR_c*)find_actor([](auto& act) { return act.mBase.mProcName == PROC_B_DR; });

    // if (actorData != nullptr) {
    //     actorData->base.current.pos.y = 50;
    // }
    g_dComIfG_gameInfo.info.mRestart.mRoomAngleY = -32768;
    g_dComIfG_gameInfo.info.mRestart.mRoomPos.x = 8.585349082946777;
    g_dComIfG_gameInfo.info.mRestart.mRoomPos.y = 0.0;
    g_dComIfG_gameInfo.info.mRestart.mRoomPos.z = 2004.4146728515625;
    g_dComIfG_gameInfo.info.mRestart.mStartPoint = 2;
    g_dComIfG_gameInfo.info.mZone[0].mRoomNo = 50;
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[1] = 240;
    g_dComIfG_gameInfo.info.mMemory.mBit.mSwitch[0] = 843264206;
    g_dComIfG_gameInfo.info.mMemory.mBit.mSwitch[1] = 2395341057;
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] = 7; 
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 1191182405;
    g_dComIfG_gameInfo.info.mSavedata.mSave[22].mBit.mSwitch[0] = 843264206;
    g_dComIfG_gameInfo.info.mSavedata.mSave[22].mBit.mSwitch[1] = 2395341057;
    g_dComIfG_gameInfo.info.mRestart.mRoomParam = 0;

    gSaveManager.setSavePosition(0.0f, -300.0f, 4000.0f);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_Ganondorf() {
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 1048578;
    g_dComIfG_gameInfo.info.mZone[0].mBit.mRoomSwitch = 1024;
    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
    gSaveManager.setSavePosition(0.0f, -2000.0f, 0.0f);
    gSaveManager.setLinkInfo(); // void
}

KEEP_FUNC void SaveMngSpecial_YellowText() {
    dComIfGs_onItemFirstBit(YELLOW_RUPEE);
}

KEEP_FUNC void SaveMngSpecial_CenterCamera() {
    // needs to run in the "after" callback
    gSaveManager.setLinkInfo();

    cXyz pos = dComIfGp_getPlayer()->current.pos;
    u16 angle = dComIfGp_getPlayer()->shape_angle.y;
    f32 radians = angle * (2.0f * M_PI / 65536.0f);

    dComIfGp_getCamera(0)->mCamera.mCenter.x = pos.x - sin(radians) * -373.0f;
    dComIfGp_getCamera(0)->mCamera.mCenter.y = pos.y + 250.0f;
    dComIfGp_getCamera(0)->mCamera.mCenter.z = pos.z - cos(radians) * -373.0f;

    dComIfGp_getCamera(0)->mCamera.mEye.x = pos.x;
    dComIfGp_getCamera(0)->mCamera.mEye.y = pos.y + 105.0f;
    dComIfGp_getCamera(0)->mCamera.mEye.z = pos.z;
}

KEEP_FUNC void SaveMngSpecial_SolBacktrackCamera() {
    gSaveManager.setLinkInfo();

    dComIfGp_getCamera(0)->mCamera.mCenter.x = 0.0f;
    dComIfGp_getCamera(0)->mCamera.mCenter.y = 170.850647f;
    dComIfGp_getCamera(0)->mCamera.mCenter.z = 533.318665f;

    dComIfGp_getCamera(0)->mCamera.mEye.x = 0.0f;
    dComIfGp_getCamera(0)->mCamera.mEye.y = 93.3100357f;
    dComIfGp_getCamera(0)->mCamera.mEye.z = 299.36438f;
}

KEEP_FUNC void SaveMngSpecial_GorgeVoid() {
    g_dComIfG_gameInfo.info.mRestart.mRoomAngleY = 26033;
    g_dComIfG_gameInfo.info.mRestart.mRoomPos.x = -17316.703125;
    g_dComIfG_gameInfo.info.mRestart.mRoomPos.y = -6450.0;
    g_dComIfG_gameInfo.info.mRestart.mRoomPos.z = 67532.7578125;
    gSaveManager.setLinkInfo();
    
    SaveMngSpecial_CenterCamera();
} 

KEEP_FUNC void SaveMngSpecial_Morpheel2() {
    class daB_OB_c { // morpheel
    public:
        /* 0x0000 */ fopEn_enemy_c base;
        /* 0x05AC */ u8 field_0x5ac[0x4752 - 0x5ac];
        /* 0x4752 */ s16 mAction;
    };

    daB_OB_c* morpheel = (daB_OB_c*)find_actor([](auto& act) { return act.mBase.mProcName == PROC_B_OB; });
    
    if (morpheel != nullptr) {
        morpheel->mAction = 5; // OB_ACTION_CORE_END
    }
    
    gSaveManager.setSaveAngle(10754);
    gSaveManager.setSavePosition(-1193.0f, -23999.0f, -770.0f);
    gSaveManager.setLinkInfo();

    cXyz create_pos = (dComIfGp_getPlayer()->mLeftHandPos + dComIfGp_getPlayer()->mRightHandPos) * 0.5f;
    s16 bomb_proc_id = 0x221;
    int water_bomb_param = 9;

    // create water bomb actor
    fopAc_ac_c* actor = fopAcM_fastCreate(bomb_proc_id, water_bomb_param, &create_pos, -1, nullptr, nullptr, -1, nullptr, nullptr);

    setGrabItemActor(dComIfGp_getPlayer(), actor); // make link hold water bomb
    dComIfGp_getPlayer()->field_0x33e4 = 38.0f; // idk lol
    setGrabUpperAnime(dComIfGp_getPlayer(), 4.0f); // something something animation

    g_dComIfG_gameInfo.play.mOxygenShowFlag = 1; // show the bar otherwise it'll set the air to full
    dComIfGs_setOxygen(600 * 0.75); // about how much air you usually have start of phase 2
}

KEEP_FUNC void SaveMngSpecial_KittyClimb() {
    gSaveManager.injectDefault_during();
    daAlink_c__swordEquip(dComIfGp_getPlayer(), 0); // sword out
    gSaveManager.setSaveAngle(28409);
    gSaveManager.setSavePosition(-3849.0f, -188.0f, 3117.0f);
    gSaveManager.setLinkInfo();

    SaveMngSpecial_CenterCamera();
}

KEEP_FUNC void SaveMngSpecial_RemoveAreaBannerBefore_ZorasDomain() {
    char stageName[] = "F_SP113";
    g_dComIfG_gameInfo.play.setLastPlayStageName(stageName);
}

KEEP_FUNC void SaveMngSpecial_RemoveAreaBannerBefore_Snowpeak() {
    char stageName[] = "F_SP114";
    g_dComIfG_gameInfo.play.setLastPlayStageName(stageName);
}
