#include "save_specials.h"
#include "gz_flags.h"
#include "libtp_c/include/utils.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/f_op/f_op_actor_iter.h"
#include "libtp_c/include/rel/d/a/b/d_a_b_ds.h"
#include "libtp_c/include/rel/d/a/obj/d_a_obj_lv4sand.h"

void SaveMngSpecial_BossFlags() {
    gSaveManager.injectDefault_during();
    tp_bossFlags = 0xFF;
}

void SaveMngSpecial_Goats1() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(5);
}

void SaveMngSpecial_Goats2() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(4);
}

void SaveMngSpecial_Hugo() {
    gSaveManager.injectDefault_during();
    dComIfGs_onSwitch(47, 0);   // midna trigger off
    dComIfGs_offSwitch(63, 0);  // hugo alive
}

#ifdef GCN_PLATFORM
#define HUGO_ACTOR_ID 468
#elif defined(WII_PLATFORM)
#define HUGO_ACTOR_ID 466
#endif

void SaveMngSpecial_SpawnHugo() {
    gSaveManager.setSaveAngle(40166);
    gSaveManager.setSavePosition(2.9385, 396.9580, -18150.087);
    gSaveManager.setLinkInfo();

    cXyz position(-289.9785, 401.5400, -18533.078);

    // Find hugo in the actor list
    node_class* node = g_fopAcTg_Queue.mpHead;
    fopAc_ac_c* actorData = NULL;
    for (int i = 0; i < g_fopAcTg_Queue.mSize; i++) {
        if (node != NULL) {
            create_tag_class* tag = (create_tag_class*)node;
            fopAc_ac_c* tmpData = (fopAc_ac_c*)tag->mpTagData;
            if (tmpData->mBase.mProcName == HUGO_ACTOR_ID) {
                actorData = tmpData;
                break;
            }
            node = node->mpNextNode;
        }
    }

    if (actorData != NULL) {
        actorData->mCurrent.mPosition = position;
        actorData->mCollisionRot.mY = 5880;
    }
}

void SaveMngSpecial_PurpleMist() {
    gSaveManager.injectDefault_during();
    dComIfGs_setTransformStatus(STATUS_HUMAN);
}

void SaveMngSpecial_KargOoB() {
    gSaveManager.mPracticeFileOpts.inject_options_before_load = nullptr;
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0xA;  // spawn on kargorok
    dComIfGs_setTransformStatus(STATUS_HUMAN);
}

void SaveMngSpecial_WaterfallSidehop() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 10.0f;  // link spawns swimming forward
}

void SaveMngSpecial_KB2Skip() {
    gSaveManager.injectDefault_during();
    setNextStageLayer(3);
}

void SaveMngSpecial_Escort() {
    gSaveManager.injectDefault_during();
    setNextStageRoom(0xD);
    setNextStagePoint(98);
    setNextStageLayer(2);
    dComIfGs_setKeyNum(2);  // give 2 keys for field gates
}

void SaveMngSpecial_Dangoro() {
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x200000;  // turn off intro cs, start fight
}

void SaveMngSpecial_Norgor() {
    g_meter2_info.mRentalBombBag = 0;  // Rental Bomb Bag Idx set to bag 0
    dComIfGs_setItem(SLOT_15, NORMAL_BOMB);
    dComIfGs_setBombNum(0, 30);
    dComIfGs_setSelectItemIndex(SELECT_ITEM_Y, SLOT_15);
}

void SaveMngSpecial_LakebedBKSkip() {
    gSaveManager.injectDefault_during();
    dComIfGs_onSwitch(2, 0);    // bridge turned
    dComIfGs_onSwitch(122, 0);  // dungeon intro cs off
}

void SaveMngSpecial_Darkhammer() {
    dComIfGs_onEventBit(0x0B02);
    dComIfGs_onEventBit(0x0B04);  // iza bomb bag stolen
}

void SaveMngSpecial_Morpheel() {
    dComIfGp_getPlayer()->mEquipItem = HOOKSHOT;                        // clawshot
    dComIfGp_getPlayer()->onNoResetFlg0(daPy_py_c::EQUIP_HEAVY_BOOTS);  // ib
    gSaveManager.setSaveAngle(10754);
    gSaveManager.setSavePosition(-1193.0f, -23999.0f, -770.0f);
    gSaveManager.setLinkInfo();
}

void SaveMngSpecial_Iza1Skip() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 0xA;  // spawn on kargorok
    setNextStageName("F_SP112");                       // set stage to river
    setNextStageRoom(1);
    setNextStagePoint(0);
    setNextStageLayer(4);
}

void SaveMngSpecial_Stallord() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
}

void SaveMngSpecial_Stallord2() {
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
        // tp_matrixInfo.matrix_info->target = {865.203f, -1414.390f, 2496.8774f};
        // tp_matrixInfo.matrix_info->pos = {644.438f, -1480.324f, 2194.693f};
    }
}

void SaveMngSpecial_Stallord2_init() {
    gSaveManager.repeat_during = true;
    gSaveManager.repeat_count = 120;

    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x300000;  // turn off intro cs, start fight
    setNextStagePoint(1);                                          // spawn at in front of stally
}

void SaveMngSpecial_SPRBossKey() {
    gSaveManager.injectDefault_during();
    setNextStageRoom(0xB);  // boss key room
    setNextStagePoint(0);   // default spawn
}

void SaveMngSpecial_ToTEarlyPoe() {
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(49299);
    gSaveManager.setSavePosition(-2462.85f, 2750.0f, -7.10f);
    gSaveManager.setLinkInfo();
}

void SaveMngSpecial_ToTEarlyHP() {
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(49152);
    gSaveManager.setSavePosition(-8000.50f, 5100.0f, -3226.17f);
    gSaveManager.setLinkInfo();
}

void SaveMngSpecial_HugoArchery() {
    gSaveManager.injectDefault_during();
    // g_dComIfG_gameInfo.temp_flags.flags[14] = 0xC0;  // start archery minigame
}

void SaveMngSpecial_CityPoeCycle() {
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(71);
    gSaveManager.setSavePosition(-14005.31f, 3000.0f, -15854.05f);
    gSaveManager.setLinkInfo();
}

void SaveMngSpecial_FanTower() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;  // reset city switches
}

void SaveMngSpecial_Argorok() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mZone[0].mBit.mSwitch[0] |= 0x10000;
}

void SaveMngSpecial_Palace1() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;  // reset palace switches
}

void SaveMngSpecial_Palace2() {
    dComIfGp_getPlayer()->mEquipItem = 3;  // master sword
    gSaveManager.injectDefault_during();
    gSaveManager.setSaveAngle(32731);
    gSaveManager.setSavePosition(251.83f, -200.0f, 10993.50f);
    gSaveManager.setLinkInfo();
}

void SaveMngSpecial_CaveOfOrdeals() {
    gSaveManager.injectDefault_during();
    g_dComIfG_gameInfo.info.mDan.mSwitch[0] = 0;
}
