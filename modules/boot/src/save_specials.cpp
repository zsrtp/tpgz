#include "save_specials.h"
#include "gz_flags.h"
#include "libtp_c/include/utils.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/f_op/f_op_actor_iter.h"
#include "libtp_c/include/rel/d/a/b/d_a_b_ds.h"
#include "libtp_c/include/rel/d/a/obj/d_a_obj_lv4sand.h"
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
        actorData->mCurrent.mPosition = position;
        actorData->mCollisionRot.mY = 5880;
    }
}

KEEP_FUNC void SaveMngSpecial_BossFlags() {
    gSaveManager.injectDefault_during();
    bossFlags = 0xFF;
}

KEEP_FUNC void SaveMngSpecial_Goats1() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(5);
}

KEEP_FUNC void SaveMngSpecial_Goats2() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(4);
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
        actorData->mCurrent.mPosition = position;
        actorData->mCollisionRot.mY = 5880;
    }
}

KEEP_FUNC void SaveMngSpecial_PurpleMist() {
    gSaveManager.injectDefault_during();
    dComIfGs_setTransformStatus(STATUS_HUMAN);
}

KEEP_FUNC void SaveMngSpecial_KargOoB() {
    gSaveManager.mPracticeFileOpts.inject_options_before_load = nullptr;
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0xA;  // spawn on kargorok
    dComIfGs_setTransformStatus(STATUS_HUMAN);
}

KEEP_FUNC void SaveMngSpecial_WaterfallSidehop() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 10.0f;  // link spawns swimming forward
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
    dComIfGp_getPlayer()->onNoResetFlg0(daPy_py_c::EQUIP_HEAVY_BOOTS);  // ib
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

KEEP_FUNC void SaveMngSpecial_Stallord() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
}

KEEP_FUNC void SaveMngSpecial_Stallord2() {
    gSaveManager.mPracticeFileOpts.inject_options_after_counter = 20;

    daB_DS_c* stallord = (daB_DS_c*)fopAcM_SearchByName(246);          // stallord proc name
    daObjLv4Sand_c* sand = (daObjLv4Sand_c*)fopAcM_SearchByName(189);  // sand proc name

    if (stallord != NULL) {
        stallord->mBase.mParameters |= 0x2;   // make actor phase 2 version
        stallord->mAttentionInfo.mFlags = 4;  // makes stallord targetable when hit down
        stallord->mActionMode1 = 1;           // make stallord head active
        stallord->mGravity = 0.0f;            // change gravity to 0
        g_env_light.mWeatherPalette = 2;      // set arena light
        sand->mSpeed.y = 1000.0f;             // move sand out of the way

        dComIfGs_onOneZoneSwitch(6, stallord->mCurrent.mRoomNo);
        dComIfGs_onZoneSwitch(7, stallord->mCurrent.mRoomNo);  // sets arena to raised

        stallord->mCurrent.mPosition.x = -2097.20f;  //-2397.22f;
        stallord->mCurrent.mPosition.y = 1022.21f;   // 1697.20f;
        stallord->mCurrent.mPosition.z = -1246.87f;  // 1131.33f;

        dComIfGp_getPlayer()->mCurrent.mPosition.x = 644.91f;
        dComIfGp_getPlayer()->mCurrent.mPosition.y = 300.3158f;
        dComIfGp_getPlayer()->mCurrent.mPosition.z = 2195.0237f;
        dComIfGp_getPlayer()->mCollisionRot.mY = 39350;
        // matrixInfo.matrix_info->target = {865.203f, -1414.390f, 2496.8774f};
        // matrixInfo.matrix_info->pos = {644.438f, -1480.324f, 2194.693f};
    }
}

KEEP_FUNC void SaveMngSpecial_Stallord2_init() {
    gSaveManager.repeat_during = true;
    gSaveManager.repeat_count = 120;

    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
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
    dComIfGs_onSwitch(224, 4);   // gate moved to correct pos
}

KEEP_FUNC void SaveMngSpecial_HugoArchery() {
    gSaveManager.injectDefault_during();
    // g_dComIfG_gameInfo.temp_flags.flags[14] = 0xC0;  // start archery minigame
}

KEEP_FUNC void SaveMngSpecial_CityPoeCycle() {
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(71);
    gSaveManager.setSavePosition(-14005.31f, 3000.0f, -15854.05f);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_AeralfosSkip() {
    dComIfGp_getPlayer()->mEquipItem = HOOKSHOT;  // clawshot out
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
    dComIfGp_getPlayer()->mEquipItem = 3;  // master sword
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(32731);
    gSaveManager.setSavePosition(251.83f, -200.0f, 10993.50f);
    gSaveManager.setLinkInfo();
}

KEEP_FUNC void SaveMngSpecial_CaveOfOrdeals() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;
}

KEEP_FUNC void BeastGanonSpecial_setLayer() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(1);
}
