#ifndef D_D_STAGE_H
#define D_D_STAGE_H

#include "../addrs.h"
#include "save/d_save.h"
#include "../f_op/f_op_actor.h"
#include "../defines.h"
#include "d_path.h"

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

class stage_actor_data_class {
public:
    /* 0x00 */ char mName[8];
    /* 0x08 */ u32 mParameter;
    /* 0x0C */ cXyz mSpawnPos;
    /* 0x18 */ csXyz mAngle;
    /* 0x1E */ u16 mEnemyNo;
};  // Size: 0x20

class stage_actor_class {
public:
    /* 0x0 */ int mEntryNum;
    /* 0x4 */ stage_actor_data_class* mEntries;
};

struct roomRead_class {};

struct dStage_FileList2_dt_c {};

struct dStage_MemoryMap_c {};

struct dStage_dPath_c {
    /* 0x0 */ int m_num;
    /* 0x4 */ dPath* m_path;
};

struct dStage_Multi_c {};

struct dStage_SoundInfo_c {};

struct dStage_FileList_dt_c {};

struct dStage_dPnt_c {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
    /* 0x4 */ Vec m_position;
};  // Size: 0x10

struct dStage_FloorInfo_c {};

struct dStage_Lbnk_c {};

struct dStage_Elst_c {};

struct dStage_MemoryConfig_c {};

struct dStage_DMap_c {};

struct dStage_MapEventInfo_c {};

class dStage_dt_c {
public:
    void setRoomNo(s8 roomNo) { mRoomNo = roomNo; }
    s8 getRoomNo() { return mRoomNo; }

    /* 0x00 */ void* vtable;
    /* 0x04 */ s8 mRoomNo;
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
    u32 mPaletteNumInfo;
    u32 mPselectNumInfo;
    u32 mEnvrNumInfo;
    u32 mVrboxNumInfo;
    int mVrboxcolNumInfo;
    u32 mPlightNumInfo;
    u16 mPlayerNum;
    u16 field_0x56;
    u16 field_0x58;
    u16 field_0x5a;
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
    u16 mPlayerNum;
    u16 field_0x62;
    int mVrboxNumInfo;
    int mVrboxcolNumInfo;
};  // Size: 0x6C

class dStage_roomControl_c {
public:
    struct roomDzs_c {};

    u8 field_0x0[4];
};

class dStage_startStage_c {
public:
    inline char* getName() { return mStage; }
    s8 getLayer() { return mLayer; }
    void setLayer(s8 layer) { mLayer = layer; }
    void setPoint(s16 point) { mPoint = point; }
    void setRoomNo(s8 room) { mRoomNo = room; }

    /* 0x0 */ char mStage[8];
    /* 0x8 */ s16 mPoint;
    /* 0xA */ s8 mRoomNo;
    /* 0xB */ s8 mLayer;
    /* 0xC */ s8 mDarkArea;
#ifdef WII_PLATFORM
    /* 0xD */ s8 enabled;
#endif  // WII_PLATFORM
};
static_assert(sizeof(dStage_startStage_c) == 0xE);

class dStage_nextStage_c : public dStage_startStage_c {
public:
#ifndef WII_PLATFORM
    s8 enabled;
#endif  // WII_PLATFORM
    u8 wipe;
    u8 wipe_speed;
};
#ifndef WII_PLATFORM
static_assert(sizeof(dStage_nextStage_c) == 0x12);
#endif  // WII_PLATFORM

class dStage_roomStatus_c : public dStage_roomDt_c {
public:
    /* 0x06C */ u8 mJ3DLightInfo[0xA0 - 0x6C];
    /* 0x0A0 */ u8 unk_A0[0x3F7 - 0xA0];
    /* 0x3F7 */ s8 mZoneNo;
    /* 0x3F8 */ u8 unk_3F8[0x404 - 0x3F8];

    int getZoneNo() const { return mZoneNo; }
};  // Size: 0x404

// unknown name
struct dStage_objectNameInf {
    char mName[8];
    s16 mProcName;
    s8 mSubtype;
};  // Size: 0xC

enum TimePass { TIME_STOP, TIME_MOVE };

// Functions
LIBTP_DEFINE_FUNC(SetTimePass__20dStage_roomControl_cFi, dStage_roomControl_c__SetTimePass_int_,
                  void, dStage_roomControl_c__setTimePass, (TimePass flag))

typedef void (*dStage_nextStage_c__set_t)(void* addr, const char* stage, s8 room, s16 point,
                                          s8 layer, s8 wipe, u8 wipe_speed);
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

#ifndef WII_PLATFORM
#define dStage_roomControl_c__mStatus mStatus__20dStage_roomControl_c
#endif
extern dStage_roomStatus_c dStage_roomControl_c__mStatus[64];

#endif /* D_D_STAGE_H */
