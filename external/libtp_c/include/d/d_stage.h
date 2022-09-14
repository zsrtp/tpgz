#ifndef D_D_STAGE_H
#define D_D_STAGE_H

#include "../addrs.h"
#include "save/d_save.h"
#include "../f_op/f_op_actor.h"
#include "../defines.h"

struct stage_vrboxcol_info_class {};

struct stage_vrbox_info_class {};

struct stage_tresure_class {};

struct stage_tgsc_data_class {};

struct stage_tgsc_class {};

struct stage_stag_info_class {};

struct stage_scls_info_dummy_class {};

struct stage_pure_lightvec_info_class {};

struct stage_pselect_info_class {};

struct stage_plight_info_class {};

struct stage_palette_info_class {};

struct stage_map_info_dummy_class {};

struct stage_map_info_class {};

struct stage_envr_info_class {};

struct stage_camera_class {};

struct stage_camera2_data_class {};

struct stage_arrow_class {};

struct stage_actor_data_class {};

struct stage_actor_class {};

struct roomRead_class {};

struct dStage_FileList2_dt_c {};

struct dStage_MemoryMap_c {};

struct dStage_dPath_c {};

struct dStage_Multi_c {};

struct dStage_SoundInfo_c {};

struct dStage_FileList_dt_c {};

struct dStage_dPnt_c {};

struct dStage_FloorInfo_c {};

struct dStage_Lbnk_c {};

struct dStage_Elst_c {};

struct dStage_MemoryConfig_c {};

struct dStage_DMap_c {};

struct dStage_MapEventInfo_c {};

class dStage_dt_c {
public:
    void setRoomNo(int8_t roomNo) { mRoomNo = roomNo; }
    int8_t getRoomNo() { return mRoomNo; }

    /* 0x00 */ void* vtable;
    /* 0x04 */ int8_t mRoomNo;
};

class dStage_stageDt_c : public dStage_dt_c {
public:
    stage_camera_class* mCamera;
    stage_arrow_class* mArrow;
    stage_actor_class* mPlayer;
    roomRead_class* mRoom;
    stage_map_info_class* mMapInfo;
    stage_map_info_dummy_class* mMapInfoBase;
    stage_palette_info_class* mPaletteInfo;
    stage_pselect_info_class* mPselectInfo;
    stage_envr_info_class* mEnvrInfo;
    stage_vrbox_info_class* mVrboxInfo;
    stage_vrboxcol_info_class* mVrboxcolInfo;
    stage_plight_info_class* mPlightInfo;
    dStage_MapEventInfo_c* mMapEventInfo;
    uint32_t mPaletteNumInfo;
    uint32_t mPselectNumInfo;
    uint32_t mEnvrNumInfo;
    uint32_t mVrboxNumInfo;
    int mVrboxcolNumInfo;
    uint32_t mPlightNumInfo;
    uint16_t mPlayerNum;
    uint16_t field_0x56;
    uint16_t field_0x58;
    uint16_t field_0x5a;
    stage_stag_info_class* mStagInfo;
    stage_scls_info_dummy_class* mSclsInfo;
    dStage_dPnt_c* mPntInfo;
    dStage_dPath_c* mPathInfo;
    dStage_dPnt_c* mPnt2Inf;
    dStage_dPath_c* mPath2Info;
    dStage_SoundInfo_c* mSoundInf;
    dStage_SoundInfo_c* mSoundInfCL;
    dStage_FloorInfo_c* mFloorInfo;
    dStage_MemoryConfig_c* mMemoryConfig;
    dStage_MemoryMap_c* mMemoryMap;
    dStage_Multi_c* mMulti;
    dStage_Multi_c* mOldMulti;
    stage_tresure_class* mTreasure;
    dStage_DMap_c* mDMap;
    stage_tgsc_class* mDrTg;
    stage_tgsc_class* mDoor;
    dStage_Elst_c* mElst;
};
static_assert(sizeof(dStage_stageDt_c) == 0xA4);

class dStage_roomDt_c : public dStage_dt_c {
public:
    stage_pure_lightvec_info_class* mLightVecInfo;
    int mLightVecInfoNum;
    stage_map_info_class* mMapInfo;
    stage_map_info_dummy_class* mMapInfoBase;
    stage_vrbox_info_class* mVrboxInfo;
    stage_vrboxcol_info_class* mVrboxcolInfo;
    dStage_FileList2_dt_c* mFileList2Info;
    dStage_FileList_dt_c* mFileListInfo;
    stage_actor_class* mPlayer;
    dStage_dPnt_c* mPnt2Info;
    dStage_dPath_c* mPath2Info;
    stage_camera_class* mCamera;
    stage_arrow_class* mArrow;
    dStage_MapEventInfo_c* mMapEventInfo;
    dStage_SoundInfo_c* mSoundInf;
    dStage_SoundInfo_c* mSoundInfCL;
    stage_scls_info_dummy_class* mSclsInfo;
    dStage_Lbnk_c* mLbnk;
    stage_tresure_class* mTreasure;
    stage_tgsc_class* mDrTg;
    stage_tgsc_class* mDoor;
    dStage_FloorInfo_c* mFloorInfo;
    uint16_t mPlayerNum;
    uint16_t field_0x62;
    int mVrboxNumInfo;
    int mVrboxcolNumInfo;
};  // Size: 0x6C

class dStage_roomControl_c {
public:
    struct roomDzs_c {};

    uint8_t field_0x0[4];
};

class dStage_startStage_c {
public:
    inline char* getName() { return mStage; }
    int8_t getLayer() { return mLayer; }
    void setLayer(int8_t layer) { mLayer = layer; }
    void setPoint(int16_t point) { mPoint = point; }
    void setRoomNo(int8_t room) { mRoomNo = room; }

    /* 0x0 */ char mStage[8];
    /* 0x8 */ int16_t mPoint;
    /* 0xA */ int8_t mRoomNo;
    /* 0xB */ int8_t mLayer;
    /* 0xC */ int8_t mDarkArea;
#ifdef WII_PLATFORM
    /* 0xD */ int8_t enabled;
#endif  // WII_PLATFORM
};
static_assert(sizeof(dStage_startStage_c) == 0xE);

class dStage_nextStage_c : public dStage_startStage_c {
public:
#ifndef WII_PLATFORM
    int8_t enabled;
#endif  // WII_PLATFORM
    uint8_t wipe;
    uint8_t wipe_speed;
};
#ifndef WII_PLATFORM
static_assert(sizeof(dStage_nextStage_c) == 0x12);
#endif  // WII_PLATFORM

class dStage_roomStatus_c : dStage_roomDt_c {
public:
    /* 0x06C */ uint8_t mJ3DLightInfo[0xA0 - 0x6C];
    /* 0x0A0 */ uint8_t unk_A0[0x3F7 - 0xA0];
    /* 0x3F7 */ int8_t mZoneNo;
    /* 0x3F8 */ uint8_t unk_3F8[0x404 - 0x3F8];

    int getZoneNo() const { return mZoneNo; }
};  // Size: 0x404

// unknown name
struct dStage_objectNameInf {
    char mName[8];
    int16_t mProcName;
    int8_t mSubtype;
};  // Size: 0xC

enum TimePass { TIME_STOP, TIME_MOVE };

// Functions
LIBTP_DEFINE_FUNC(SetTimePass__20dStage_roomControl_cFi, dStage_roomControl_c__SetTimePass_int_,
                  void, dStage_roomControl_c__setTimePass, (TimePass flag))

typedef void (*dStage_nextStage_c__set_t)(void* addr, const char* stage, int8_t room, int16_t point,
                                          int8_t layer, int8_t wipe, uint8_t wipe_speed);
#ifdef dStage_nextStage_c__set_addr
#define dStage_nextStage_c__set ((dStage_nextStage_c__set_t)dStage_nextStage_c__set_addr)
#else
#ifdef WII_PLATFORM
#define dStage_nextStage_c__set dStage_nextStage_c__set_char
#else
#define dStage_nextStage_c__set set__18dStage_nextStage_cFPCcScsScScUc
#endif
extern dStage_nextStage_c__set_t dStage_nextStage_c__set;
#endif

#endif /* D_D_STAGE_H */
