#ifndef D_SAVE_D_SAVE_H
#define D_SAVE_D_SAVE_H

#include "../../SSystem/SComponent/c_xyz.h"
#include "../../defines.h"
#include <stdint.h>

#define DEFAULT_SELECT_ITEM_INDEX 0
#define MAX_SELECT_ITEM 3
#define MAX_EVENTS 256
#define MAX_ITEM_SLOTS 24
#define ITEM_XY_MAX_DUMMY 8
#define LIGHT_DROP_STAGE 4
#define LETTER_INFO_BIT 64
#define BOMB_BAG_MAX 3
#define BOTTLE_MAX 4
#define TBOX_MAX 64
#define DSV_MEMBIT_ENUM_MAX 8

enum Wallets {
    /* 0x0 */ WALLET,
    /* 0x1 */ BIG_WALLET,
    /* 0x2 */ GIANT_WALLET
};

enum ItemSlots {
    /* 0x00 */ SLOT_0,
    /* 0x01 */ SLOT_1,
    /* 0x02 */ SLOT_2,
    /* 0x03 */ SLOT_3,
    /* 0x04 */ SLOT_4,
    /* 0x05 */ SLOT_5,
    /* 0x06 */ SLOT_6,
    /* 0x07 */ SLOT_7,
    /* 0x08 */ SLOT_8,
    /* 0x09 */ SLOT_9,
    /* 0x0A */ SLOT_10,
    /* 0x0B */ SLOT_11,
    /* 0x0C */ SLOT_12,
    /* 0x0D */ SLOT_13,
    /* 0x0E */ SLOT_14,
    /* 0x0F */ SLOT_15,
    /* 0x10 */ SLOT_16,
    /* 0x11 */ SLOT_17,
    /* 0x12 */ SLOT_18,
    /* 0x13 */ SLOT_19,
    /* 0x14 */ SLOT_20,
    /* 0x15 */ SLOT_21,
    /* 0x16 */ SLOT_22,
    /* 0x17 */ SLOT_23
};

enum ItemTable {
    /* 0x00 */ HEART,
    /* 0x01 */ GREEN_RUPEE,
    /* 0x02 */ BLUE_RUPEE,
    /* 0x03 */ YELLOW_RUPEE,
    /* 0x04 */ RED_RUPEE,
    /* 0x05 */ PURPLE_RUPEE,
    /* 0x06 */ ORANGE_RUPEE,
    /* 0x07 */ SILVER_RUPEE,
    /* 0x08 */ S_MAGIC,
    /* 0x09 */ L_MAGIC,
    /* 0x0A */ BOMB_5,
    /* 0x0B */ BOMB_10,
    /* 0x0C */ BOMB_20,
    /* 0x0D */ BOMB_30,
    /* 0x0E */ ARROW_10,
    /* 0x0F */ ARROW_20,
    /* 0x10 */ ARROW_30,
    /* 0x11 */ ARROW_1,
    /* 0x12 */ PACHINKO_SHOT,
    /* 0x13 */ noentry1,
    /* 0x14 */ noentry2,
    /* 0x15 */ noentry3,
    /* 0x16 */ WATER_BOMB_5,
    /* 0x17 */ WATER_BOMB_10,
    /* 0x18 */ WATER_BOMB_20,
    /* 0x19 */ WATER_BOMB_30,
    /* 0x1A */ BOMB_INSECT_5,
    /* 0x1B */ BOMB_INSECT_10,
    /* 0x1C */ BOMB_INSECT_20,
    /* 0x1D */ BOMB_INSECT_30,
    /* 0x1E */ RECOVERY_FAILY,
    /* 0x1F */ TRIPLE_HEART,
    /* 0x20 */ SMALL_KEY,
    /* 0x21 */ KAKERA_HEART,
    /* 0x22 */ UTAWA_HEART,
    /* 0x23 */ MAP,
    /* 0x24 */ COMPUS,
    /* 0x25 */ DUNGEON_EXIT,
    /* 0x26 */ BOSS_KEY,
    /* 0x27 */ DUNGEON_BACK,
    /* 0x28 */ SWORD,
    /* 0x29 */ MASTER_SWORD,
    /* 0x2A */ WOOD_SHIELD,
    /* 0x2B */ SHIELD,
    /* 0x2C */ HYLIA_SHIELD,
    /* 0x2D */ TKS_LETTER,
    /* 0x2E */ WEARS_CASUAL,
    /* 0x2F */ WEAR_KOKIRI,
    /* 0x30 */ ARMOR,
    /* 0x31 */ WEAR_ZORA,
    /* 0x32 */ MAGIC_LV1,
    /* 0x33 */ DUNGEON_EXIT_2,
    /* 0x34 */ WALLET_LV1,
    /* 0x35 */ WALLET_LV2,
    /* 0x36 */ WALLET_LV3,
    /* 0x37 */ noentry4,
    /* 0x38 */ noentry5,
    /* 0x39 */ noentry6,
    /* 0x3A */ noentry7,
    /* 0x3B */ noentry8,
    /* 0x3C */ noentry9,
    /* 0x3D */ ZORAS_JEWEL,
    /* 0x3E */ HAWK_EYE,
    /* 0x3F */ WOOD_STICK,
    /* 0x40 */ BOOMERANG,
    /* 0x41 */ SPINNER,
    /* 0x42 */ IRONBALL,
    /* 0x43 */ BOW,
    /* 0x44 */ HOOKSHOT,
    /* 0x45 */ HVY_BOOTS,
    /* 0x46 */ COPY_ROD,
    /* 0x47 */ W_HOOKSHOT,
    /* 0x48 */ KANTERA,
    /* 0x49 */ LIGHT_SWORD,
    /* 0x4A */ FISHING_ROD_1,
    /* 0x4B */ PACHINKO,
    /* 0x4C */ COPY_ROD_2,
    /* 0x4D */ noentry10,
    /* 0x4E */ noentry11,
    /* 0x4F */ BOMB_BAG_LV2,
    /* 0x50 */ BOMB_BAG_LV1,
    /* 0x51 */ BOMB_IN_BAG,
    /* 0x52 */ noentry12,
    /* 0x53 */ LIGHT_ARROW,
    /* 0x54 */ ARROW_LV1,
    /* 0x55 */ ARROW_LV2,
    /* 0x56 */ ARROW_LV3,
    /* 0x57 */ noentry13,
    /* 0x58 */ LURE_ROD,
    /* 0x59 */ BOMB_ARROW,
    /* 0x5A */ HAWK_ARROW,
    /* 0x5B */ BEE_ROD,
    /* 0x5C */ JEWEL_ROD,
    /* 0x5D */ WORM_ROD,
    /* 0x5E */ JEWEL_BEE_ROD,
    /* 0x5F */ JEWEL_WORM_ROD,
    /* 0x60 */ EMPTY_BOTTLE,
    /* 0x61 */ RED_BOTTLE,
    /* 0x62 */ GREEN_BOTTLE,
    /* 0x63 */ BLUE_BOTTLE,
    /* 0x64 */ MILK_BOTTLE,
    /* 0x65 */ HALF_MILK_BOTTLE,
    /* 0x66 */ OIL_BOTTLE,
    /* 0x67 */ WATER_BOTTLE,
    /* 0x68 */ OIL_BOTTLE_2,
    /* 0x69 */ RED_BOTTLE_2,
    /* 0x6A */ UGLY_SOUP,
    /* 0x6B */ HOT_SPRING,
    /* 0x6C */ FAIRY,
    /* 0x6D */ HOT_SPRING_2,
    /* 0x6E */ OIL2,
    /* 0x6F */ OIL,
    /* 0x70 */ NORMAL_BOMB,
    /* 0x71 */ WATER_BOMB,
    /* 0x72 */ POKE_BOMB,
    /* 0x73 */ FAIRY_DROP,
    /* 0x74 */ WORM,
    /* 0x75 */ DROP_BOTTLE,
    /* 0x76 */ BEE_CHILD,
    /* 0x77 */ CHUCHU_RARE,
    /* 0x78 */ CHUCHU_RED,
    /* 0x79 */ CHUCHU_BLUE,
    /* 0x7A */ CHUCHU_GREEN,
    /* 0x7B */ CHUCHU_YELLOW,
    /* 0x7C */ CHUCHU_PURPLE,
    /* 0x7D */ LV1_SOUP,
    /* 0x7E */ LV2_SOUP,
    /* 0x7F */ LV3_SOUP,
    /* 0x80 */ LETTER,
    /* 0x81 */ BILL,
    /* 0x82 */ WOOD_STATUE,
    /* 0x83 */ IRIAS_PENDANT,
    /* 0x84 */ HORSE_FLUTE,
    /* 0x85 */ noentry14,
    /* 0x86 */ noentry15,
    /* 0x87 */ noentry16,
    /* 0x88 */ noentry17,
    /* 0x89 */ noentry18,
    /* 0x8A */ noentry19,
    /* 0x8B */ noentry20,
    /* 0x8C */ noentry21,
    /* 0x8D */ noentry22,
    /* 0x8E */ noentry23,
    /* 0x8F */ noentry24,
    /* 0x90 */ RAFRELS_MEMO,
    /* 0x91 */ ASHS_SCRIBBLING,
    /* 0x92 */ noentry25,
    /* 0x93 */ noentry26,
    /* 0x94 */ noentry27,
    /* 0x95 */ noentry28,
    /* 0x96 */ noentry29,
    /* 0x97 */ noentry30,
    /* 0x98 */ noentry31,
    /* 0x99 */ noentry32,
    /* 0x9A */ noentry33,
    /* 0x9B */ noentry34,
    /* 0x9C */ CHUCHU_YELLOW2,
    /* 0x9D */ OIL_BOTTLE3,
    /* 0x9E */ SHOP_BEE_CHILD,
    /* 0x9F */ CHUCHU_BLACK,
    /* 0xA0 */ LIGHT_DROP,
    /* 0xA1 */ DROP_CONTAINER,
    /* 0xA2 */ DROP_CONTAINER02,
    /* 0xA3 */ DROP_CONTAINER03,
    /* 0xA4 */ FILLED_CONTAINER,
    /* 0xA5 */ MIRROR_PIECE_2,
    /* 0xA6 */ MIRROR_PIECE_3,
    /* 0xA7 */ MIRROR_PIECE_4,
    /* 0xA8 */ noentry35,
    /* 0xA9 */ noentry36,
    /* 0xAA */ noentry37,
    /* 0xAB */ noentry38,
    /* 0xAC */ noentry39,
    /* 0xAD */ noentry40,
    /* 0xAE */ noentry41,
    /* 0xAF */ noentry42,
    /* 0xB0 */ SMELL_YELIA_POUCH,
    /* 0xB1 */ SMELL_PUMPKIN,
    /* 0xB2 */ SMELL_POH,
    /* 0xB3 */ SMELL_FISH,
    /* 0xB4 */ SMELL_CHILDREN,
    /* 0xB5 */ SMELL_MEDICINE,
    /* 0xB6 */ noentry43,
    /* 0xB7 */ noentry44,
    /* 0xB8 */ noentry45,
    /* 0xB9 */ noentry46,
    /* 0xBA */ noentry47,
    /* 0xBB */ noentry48,
    /* 0xBC */ noentry49,
    /* 0xBD */ noentry50,
    /* 0xBE */ noentry51,
    /* 0xBF */ noentry52,
    /* 0xC0 */ M_BEETLE,
    /* 0xC1 */ F_BEETLE,
    /* 0xC2 */ M_BUTTERFLY,
    /* 0xC3 */ F_BUTTERFLY,
    /* 0xC4 */ M_STAG_BEETLE,
    /* 0xC5 */ F_STAG_BEETLE,
    /* 0xC6 */ M_GRASSHOPPER,
    /* 0xC7 */ F_GRASSHOPPER,
    /* 0xC8 */ M_NANAFUSHI,
    /* 0xC9 */ F_NANAFUSHI,
    /* 0xCA */ M_DANGOMUSHI,
    /* 0xCB */ F_DANGOMUSHI,
    /* 0xCC */ M_MANTIS,
    /* 0xCD */ F_MANTIS,
    /* 0xCE */ M_LADYBUG,
    /* 0xCF */ F_LADYBUG,
    /* 0xD0 */ M_SNAIL,
    /* 0xD1 */ F_SNAIL,
    /* 0xD2 */ M_DRAGONFLY,
    /* 0xD3 */ F_DRAGONFLY,
    /* 0xD4 */ M_ANT,
    /* 0xD5 */ F_ANT,
    /* 0xD6 */ M_MAYFLY,
    /* 0xD7 */ F_MAYFLY,
    /* 0xD8 */ noentry53,
    /* 0xD9 */ noentry54,
    /* 0xDA */ noentry55,
    /* 0xDB */ noentry56,
    /* 0xDC */ noentry57,
    /* 0xDD */ noentry58,
    /* 0xDE */ noentry59,
    /* 0xDF */ noentry60,
    /* 0xE0 */ POU_SPIRIT,
    /* 0xE1 */ noentry61,
    /* 0xE2 */ noentry62,
    /* 0xE3 */ noentry63,
    /* 0xE4 */ noentry64,
    /* 0xE5 */ noentry65,
    /* 0xE6 */ noentry66,
    /* 0xE7 */ noentry67,
    /* 0xE8 */ noentry68,
    /* 0xE9 */ ANCIENT_DOCUMENT,
    /* 0xEA */ AIR_LETTER,
    /* 0xEB */ ANCIENT_DOCUMENT2,
    /* 0xEC */ LV7_DUNGEON_EXIT,
    /* 0xED */ LINKS_SAVINGS,
    /* 0xEE */ SMALL_KEY2,
    /* 0xEF */ POU_FIRE1,
    /* 0xF0 */ POU_FIRE2,
    /* 0xF1 */ POU_FIRE3,
    /* 0xF2 */ POU_FIRE4,
    /* 0xF3 */ BOSSRIDER_KEY,
    /* 0xF4 */ TOMATO_PUREE,
    /* 0xF5 */ TASTE,
    /* 0xF6 */ LV5_BOSS_KEY,
    /* 0xF7 */ SURFBOARD,
    /* 0xF8 */ KANTERA2,
    /* 0xF9 */ L2_KEY_PIECES1,
    /* 0xFA */ L2_KEY_PIECES2,
    /* 0xFB */ L2_KEY_PIECES3,
    /* 0xFC */ KEY_OF_CARAVAN,
    /* 0xFD */ LV2_BOSS_KEY,
    /* 0xFE */ KEY_OF_FILONE,
    /* 0xFF */ NO_ITEM
};

enum CollectItem {
    /* 0x0 */ COLLECT_CLOTHING,
    /* 0x1 */ COLLECT_SWORD,
    /* 0x2 */ COLLECT_SHIELD,
    /* 0x3 */ COLLECT_SMELL,
    /* 0x4 */ B_BUTTON_ITEM
};

enum Swords {
    /* 0x0 */ COLLECT_ORDON_SWORD,
    /* 0x1 */ COLLECT_MASTER_SWORD,
    /* 0x2 */ COLLECT_WOODEN_SWORD,
    /* 0x3 */ COLLECT_LIGHT_SWORD
};

enum Shields {
    /* 0x0 */ COLLECT_WOODEN_SHIELD,
    /* 0x1 */ COLLECT_ORDON_SHIELD,
    /* 0x2 */ COLLECT_HYLIAN_SHIELD
};

enum Clothes {
    /* 0x0 */ KOKIRI_CLOTHES_FLAG
};

enum LightDropStages {
    /* 0x0 */ FARON_VESSEL,
    /* 0x1 */ ELDIN_VESSEL,
    /* 0x2 */ LANAYRU_VESSEL
};

enum ItemMax {
    /* 0x0 */ ARROW_MAX,
    /* 0x1 */ NORMAL_BOMB_MAX,
    /* 0x2 */ WATER_BOMB_MAX,
    /* 0x6 */ POKE_BOMB_MAX = 6
};

enum GCSelectItem {
    /* 0x0 */ SELECT_ITEM_X,
    /* 0x1 */ SELECT_ITEM_Y,
};

enum WiiSelectItem {
    /* 0x0 */ SELECT_ITEM_LEFT,
    /* 0x1 */ SELECT_ITEM_RIGHT,
    /* 0x2 */ SELECT_ITEM_DOWN,
    /* 0x3 */ SELECT_ITEM_B,
};

enum TransformStatus { STATUS_HUMAN, STATUS_WOLF };

enum BombBags { BOMB_BAG_1, BOMB_BAG_2, BOMB_BAG_3 };

class dSv_player_status_a_c {
public:
    uint16_t& getMaxLife() { return mMaxLife; }
    uint16_t& getLife() { return mLife; }
    uint16_t& getRupee() { return mRupee; }
    uint16_t& getOil() { return mOil; }
    uint8_t& getWalletSize() { return mWalletSize; }
    uint8_t getSelectEquip(int item) const { return mSelectEquip[item]; }
    uint8_t getTransformStatus() const { return mTransformStatus; }

    void setOil(uint16_t oil) { mOil = oil; }
    void setMaxOil(uint16_t max) { mMaxOil = max; }
    void setWalletSize(uint8_t size) { mWalletSize = size; }
    void setMagic(uint8_t magic) { mMagic = magic; }
    void setMaxMagic(uint8_t max) { mMaxMagic = max; }
    void setRupee(uint16_t rupees) { mRupee = rupees; }
    void setLife(uint16_t life) { mLife = life; }
    void setMaxLife(uint8_t max) { mMaxLife = max; }
    void setSelectEquip(int item_index, uint8_t item) { mSelectEquip[item_index] = item; }
    void setTransformStatus(uint8_t status) { mTransformStatus = status; }

    /* 0x00 */ uint16_t mMaxLife;
    /* 0x02 */ uint16_t mLife;
    /* 0x04 */ uint16_t mRupee;
    /* 0x06 */ uint16_t mMaxOil;
    /* 0x08 */ uint16_t mOil;
    /* 0x0A */ uint8_t unk10;
    /* 0x0B */ uint8_t mSelectItem[4];
    /* 0x0F */ uint8_t mMixItem[4];
    /* 0x13 */ uint8_t mSelectEquip[6];
    /* 0x19 */ uint8_t mWalletSize;
    /* 0x1A */ uint8_t mMaxMagic;
    /* 0x1B */ uint8_t mMagic;
    /* 0x1C */ uint8_t mMagicFlag;
    /* 0x1D */ uint8_t unk29;
    /* 0x1E */ uint8_t mTransformStatus;
    /* 0x1F */ uint8_t unk31[3];
};  // Size: 0x28

class dSv_player_status_b_c {
public:
    void setTime(float pTime) { mTime = pTime; }
    float getTime() const { return mTime; }
    void offTransformLV(int32_t flag) { mTransformLevelFlag &= ~(1 << flag); }

    /* 0x00 */ int64_t mDateIpl;
    /* 0x08 */ uint8_t mTransformLevelFlag;
    /* 0x09 */ uint8_t mDarkClearLevelFlag;
    /* 0x0A */ uint8_t unk10;
    /* 0x0B */ uint8_t unk11;
    /* 0x0C */ float mTime;
    /* 0x10 */ uint16_t mDate;
    /* 0x12 */ uint8_t unk18[3];
};  // Size: 0x18

class dSv_horse_place_c {
public:
    /* 0x00 */ cXyz mPos;
    /* 0x0C */ uint16_t mAngleY;
    /* 0x0E */ char mName[8];
    /* 0x16 */ uint8_t mSpawnId;
    /* 0x17 */ uint8_t mRoomNo;
};  // Size: 0x18

class dSv_player_return_place_c {
public:
    /* 0x00 */ char mName[8];
    /* 0x08 */ uint8_t mPlayerStatus;
    /* 0x09 */ int8_t mRoomNo;
    /* 0x0A */ uint8_t unk10;
    /* 0x0B */ uint8_t unk11;
};  // Size: 0xC

class dSv_player_field_last_stay_info_c {
public:
    /* 0x00 */ cXyz mPos;
    /* 0x0C */ int16_t mAngleY;
    /* 0x0E */ char mName[8];
    /* 0x16 */ uint8_t mLastSpawnId;
    /* 0x17 */ uint8_t mRegionNo;
    /* 0x18 */ bool mFieldDataExistFlag;
    /* 0x19 */ uint8_t mRegion;
    /* 0x1A */ uint8_t unk26[2];
};  // Size: 0x1C

class dSv_player_last_mark_info_c {
public:
    const char* getName() { return mName; }
    cXyz getPos() { return mPos; }
    int16_t getAngleY() { return mAngleY; }
    int8_t getRoomNo() { return mRoomNo; }
    char getWarpAcceptStage() { return mWarpAcceptStage; }

    /* 0x00 */ cXyz mPos;
    /* 0x0C */ int16_t mAngleY;
    /* 0x0E */ char mName[8];
    /* 0x16 */ uint8_t mSpawnId;
    /* 0x17 */ int8_t mRoomNo;
    /* 0x18 */ char mWarpAcceptStage;
    /* 0x19 */ uint8_t unk25[3];
};  // Size: 0x1C

class dSv_player_item_c {
public:
    /* 0x00 */ uint8_t mItems[24];
    /* 0x18 */ uint8_t mItemSlots[24];
};  // Size: 0x30

class dSv_player_get_item_c {
public:
    /* 0x0 */ uint32_t mItemFlags[8];
};  // Size: 0x20

class dSv_player_item_record_c {
public:
    void setArrowNum(uint8_t amount) { mArrowNum = amount; }
    uint8_t getArrowNum() { return mArrowNum; }
    void setPachinkoNum(uint8_t amount) { mPachinkoNum = amount; }
    uint8_t getPachinkoNum() { return mPachinkoNum; }

    /* 0x0 */ uint8_t mArrowNum;
    /* 0x1 */ uint8_t mBombNum[3];
    /* 0x4 */ uint8_t mBottleNum[4];
    /* 0x8 */ uint8_t mPachinkoNum;
    /* 0x9 */ uint8_t unk5[3];
};  // Size: 0xC

class dSv_player_item_max_c {
public:
    void setArrowNum(uint8_t max) { mItemMax[ARROW_MAX] = max; }
    uint8_t getArrowNum() { return mItemMax[ARROW_MAX]; }

    /* 0x0 */ uint8_t mItemMax[8];
};  // Size: 0x8

class dSv_player_collect_c {
public:
    uint8_t getPohNum() { return mPohNum; }
    void setPohNum(uint8_t num) { mPohNum = num; }

    /* 0x0 */ uint8_t mItem[8];
    /* 0x8 */ uint8_t unk8;
    /* 0x9 */ uint8_t mCrystal;
    /* 0xA */ uint8_t mMirror;
    /* 0xB */ uint8_t unk11;
    /* 0xC */ uint8_t mPohNum;
    /* 0xD */ uint8_t padding[3];
};  // Size: 0x10

class dSv_player_wolf_c {
public:
    /* 0x0 */ uint8_t unk0[3];
    /* 0x3 */ uint8_t unk3;
};  // Size: 0x4

class dSv_light_drop_c {
public:
    /* 0x0 */ uint8_t mLightDropNum[4];
    /* 0x4 */ uint8_t mLightDropGetFlag;
    /* 0x5 */ uint8_t unk5[3];
};  // Size: 0x8

class dSv_letter_info_c {
public:
    /* 0x00 */ uint32_t mLetterGetFlags[2];
    /* 0x08 */ uint32_t mLetterReadFlags[2];
    /* 0x10 */ uint8_t mGetNumber[64];
};  // Size: 0x50

class dSv_fishing_info_c {
public:
    /* 0x00 */ uint16_t mFishCount[16];
    /* 0x20 */ uint8_t mMaxSize[16];
};  // Size: 0x34

class dSv_player_info_c {
public:
    char* getLinkName() { return (char*)mPlayerName; }

    /* 0x00 */ uint32_t unk0;
    /* 0x04 */ uint32_t unk4;
    /* 0x08 */ uint64_t mTotalTime;
    /* 0x10 */ uint16_t unk16;
    /* 0x12 */ uint16_t mDeathCount;
    /* 0x14 */ uint8_t mPlayerName[16];
    /* 0x24 */ uint8_t unk36;
    /* 0x25 */ uint8_t mHorseName[16];
    /* 0x35 */ uint8_t unk53;
    /* 0x36 */ uint8_t mClearCount;
    /* 0x37 */ uint8_t unk55[5];
};  // Size: 0x40

class dSv_player_config_c {
public:
    /* 0x0 */ uint8_t unk0;
    /* 0x1 */ uint8_t mSoundMode;
    /* 0x2 */ uint8_t mAttentionType;  // Lock-On Type; 0 : hold, 1 : switch
    /* 0x3 */ uint8_t mVibration;      // Rumble status
    /* 0x4 */ uint8_t unk4;
    /* 0x5 */ uint8_t unk5;
    /* 0x6 */ uint16_t mCalibrateDist;  // Wii pointer horizontal calibration. Default is 0x015E
    /* 0x8 */ uint8_t mCalValue;        // Wii pointer vertical calibration. Default is 0x00
    /* 0x9 */ bool mShortCut;           // Wii icon shortcut enabled/disabled.
    /* 0xA */ uint8_t mCameraControl;   // 0 : normal, 1 : inverted
    /* 0xB */ bool mPointer;            // Wii pointer enabled/disabled.
};                                      // Size: 0xC

class dSv_player_c {
public:
    dSv_player_info_c& getPlayerInfo() { return mPlayerInfo; }
    dSv_player_status_a_c& getPlayerStatusA() { return mPlayerStatusA; }
    dSv_player_status_b_c& getPlayerStatusB() { return mPlayerStatusB; }
    dSv_player_item_c& getItem() { return mItem; }
    dSv_player_collect_c& getCollect() { return mCollect; }
    dSv_player_item_record_c& getItemRecord() { return mItemRecord; }
    dSv_player_item_max_c& getItemMax() { return mItemMax; }
    dSv_player_last_mark_info_c& getPlayerLastMarkInfo() { return mPlayerLastMarkInfo; }
    dSv_player_return_place_c& getPlayerReturnPlace() { return mPlayerReturnPlace; }
    dSv_light_drop_c& getLightDrop() { return mLightDrop; }
    dSv_player_get_item_c& getGetItem() { return mGetItem; }
    dSv_player_config_c& getConfig() { return mConfig; }
    dSv_letter_info_c& getLetterInfo() { return mLetterInfo; }

    /* 0x000 */ dSv_player_status_a_c mPlayerStatusA;
    /* 0x028 */ dSv_player_status_b_c mPlayerStatusB;
    /* 0x040 */ dSv_horse_place_c mHorsePlace;
    /* 0x058 */ dSv_player_return_place_c mPlayerReturnPlace;
    /* 0x064 */ dSv_player_field_last_stay_info_c mPlayerFieldLastStayInfo;
    /* 0x080 */ dSv_player_last_mark_info_c mPlayerLastMarkInfo;
    /* 0x09C */ dSv_player_item_c mItem;
    /* 0x0CC */ dSv_player_get_item_c mGetItem;
    /* 0x0EC */ dSv_player_item_record_c mItemRecord;
    /* 0x0F8 */ dSv_player_item_max_c mItemMax;
    /* 0x100 */ dSv_player_collect_c mCollect;
    /* 0x110 */ dSv_player_wolf_c mWolf;
    /* 0x114 */ dSv_light_drop_c mLightDrop;
    /* 0x11C */ dSv_letter_info_c mLetterInfo;
    /* 0x16C */ dSv_fishing_info_c mFishingInfo;
    /* 0x1A0 */ dSv_player_info_c mPlayerInfo;
    /* 0x1E0 */ dSv_player_config_c mConfig;
};  // Size: 0x1EC

class dSv_memBit_c {
public:
    enum {
        /* 0x0 */ MAP,
        /* 0x1 */ COMPASS,
        /* 0x2 */ BOSS_KEY,
        /* 0x3 */ STAGE_BOSS_ENEMY,
        /* 0x4 */ STAGE_LIFE,
        /* 0x5 */ STAGE_BOSS_DEMO,
        /* 0x6 */ OOCCOO_NOTE,
        /* 0x7 */ STAGE_BOSS_ENEMY_2
    };

    uint8_t getKeyNum() { return mKeyNum; }
    void setKeyNum(uint8_t num) { mKeyNum = num; }
    void offDungeonItem(int flag) { mDungeonItem &= ~(1 << flag); }

    /* 0x00 */ uint32_t mTbox[2];
    /* 0x08 */ uint32_t mSwitch[4];
    /* 0x18 */ uint32_t mItem[1];
    /* 0x1C */ uint8_t mKeyNum;
    /* 0x1D */ uint8_t mDungeonItem;
};  // Size: 0x20

class dSv_event_c {
public:
    /* 0x0 */ uint8_t mEvent[256];
};  // Size: 0x100

class dSv_MiniGame_c {
public:
    /* 0x00 */ uint8_t unk0;
    /* 0x01 */ uint8_t unk1[3];
    /* 0x04 */ uint32_t mStarTime;
    /* 0x08 */ uint32_t mBalloonScore;
    /* 0x0C */ uint32_t mRaceGameTime;
    /* 0x10 */ uint32_t unk16;
    /* 0x14 */ uint32_t unk20;
};  // Size: 0x18

class dSv_memory_c {
public:
    dSv_memBit_c& getBit() { return mBit; }
    const dSv_memBit_c& getBit() const { return mBit; }

    enum {
        /* 0x00 */ ORDON,
        /* 0x01 */ SEWERS,
        /* 0x02 */ FARON,
        /* 0x03 */ ELDIN,
        /* 0x04 */ LANAYRU,
        /* 0x06 */ FIELD = 6,
        /* 0x07 */ GROVE,
        /* 0x08 */ SNOWPEAK,
        /* 0x09 */ TOWN,
        /* 0x0A */ DESERT,
        /* 0x0B */ POND,
        /* 0x10 */ FOREST_TEMPLE = 16,
        /* 0x11 */ GORON_MINES,
        /* 0x12 */ LAKEBED,
        /* 0x13 */ ARBITERS,
        /* 0x14 */ SNOWPEAK_RUINS,
        /* 0x15 */ TEMPLE_OF_TIME,
        /* 0x16 */ CITY,
        /* 0x17 */ PALACE,
        /* 0x18 */ HYRULE_CASTLE,
        /* 0x19 */ CAVE_1,
        /* 0x1A */ CAVE_2,
        /* 0x1B */ GROTTO
    };

    /* 0x0 */ dSv_memBit_c mBit;
};  // Size: 0x20

class dSv_memory2_c {
public:
    /* 0x0 */ uint32_t mVisitedRoom[2];
};  // Size: 0x8

class dSv_danBit_c {
public:
    /* 0x00 */ int8_t mStageNo;
    /* 0x01 */ uint8_t unk1;
    /* 0x02 */ uint8_t unk2[2];
    /* 0x04 */ uint32_t mSwitch[2];
    /* 0x0C */ uint32_t mItem[4];
    /* 0x1C */ int16_t unk28[16];
};  // Size: 0x3C

class dSv_zoneBit_c {
public:
    /* 0x00 */ uint16_t mSwitch[2];
    /* 0x04 */ uint16_t mRoomSwitch;
    /* 0x06 */ uint16_t mItem[2];
    /* 0x0A */ uint16_t mRoomItem;
    /* 0x0C */ uint16_t unk12;
};  // Size: 0xE

class dSv_zoneActor_c {
public:
    static const int ACTOR_MAX = 0xFFFF;

    /* 0x00 */ uint32_t mActorFlags[4];
};  // Size: 0x10

class dSv_zone_c {
public:
    dSv_zoneBit_c& getZoneBit() { return mBit; }
    const dSv_zoneBit_c& getBit() const { return mBit; }
    dSv_zoneActor_c& getActor() { return mActor; }
    const dSv_zoneActor_c& getActor() const { return mActor; }

    int8_t& getRoomNo() { return mRoomNo; }

    /* 0x00 */ int8_t mRoomNo;
    /* 0x01 */ uint8_t unk1;
    /* 0x02 */ dSv_zoneBit_c mBit;
    /* 0x10 */ dSv_zoneActor_c mActor;
};  // Size: 0x20

class dSv_restart_c {
public:
    /* 0x00 */ int8_t mRoomNo;
    /* 0x01 */ uint8_t field_0x01[3];
    /* 0x04 */ int16_t mStartPoint;
    /* 0x06 */ int16_t mRoomAngleY;
    /* 0x08 */ cXyz mRoomPos;
    /* 0x14 */ uint32_t mRoomParam;
    /* 0x18 */ float mLastSpeedF;
    /* 0x1C */ uint32_t mLastMode;
    /* 0x20 */ int16_t mLastAngleY;
};  // Size: 0x24

class dSv_turnRestart_c {
public:
    class dSv_turnRestart_camera_c {
        /* 0x00 */ cXyz mCameraCtr;
        /* 0x0C */ cXyz mCameraEye;
        /* 0x18 */ cXyz mCameraUp;
    };  // Size: 0x24

    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ uint32_t mParam;
    /* 0x10 */ int16_t mAngleY;
    /* 0x12 */ int8_t unk18;
    /* 0x14 */ dSv_turnRestart_camera_c mCamera;
    /* 0x38 */ float mCameraFvy;
};  // Size: 0x3C

class dSv_reserve_c {
public:
    uint8_t unk[80];
};

class dSv_save_c {
public:
    dSv_player_c& getPlayer() { return mPlayer; }
    dSv_event_c& getEvent() { return mEvent; }
    dSv_memory_c& getSave(int i_stageNo) { return mSave[i_stageNo]; }
    void putSave(int i_stageNo, dSv_memory_c mem) { mSave[i_stageNo] = mem; }

    static const int STAGE_MAX = 32;
    static const int STAGE2_MAX = 64;

    /* 0x000 */ dSv_player_c mPlayer;
    /* 0x1F0 */ dSv_memory_c mSave[STAGE_MAX];
    /* 0x5F0 */ dSv_memory2_c mSave2[STAGE2_MAX];
    /* 0x7F0 */ dSv_event_c mEvent;
    /* 0x8F0 */ dSv_reserve_c reserve;
    /* 0x940 */ dSv_MiniGame_c mMiniGame;
};  // Size: 0x958

class dSv_info_c {
public:
    dSv_save_c& getSavedata() { return mSavedata; }
    dSv_memory_c& getMemory() { return mMemory; }
    dSv_zone_c* getZones() { return mZone; }
    dSv_player_c& getPlayer() { return mSavedata.getPlayer(); }
    dSv_event_c& getTmp() { return mTmp; }

    /* 0x000 */ dSv_save_c mSavedata;
    /* 0x958 */ dSv_memory_c mMemory;
    /* 0x978 */ dSv_danBit_c mDan;
    /* 0x9B4 */ dSv_zone_c mZone[32];
    /* 0xDB4 */ dSv_restart_c mRestart;
    /* 0xDD8 */ dSv_event_c mTmp;
    /* 0xED8 */ dSv_turnRestart_c mTurnRestart;
    /* 0xF14 */ uint8_t field_0xf14[4];
    /* 0xF18 */ uint8_t mDataNum;
    /* 0xF19 */ uint8_t mNewFile;
    /* 0xF1A */ uint8_t mNoFile;
    /* 0xF1B */ uint8_t field_0xf1b[13];
    /* 0xF28 */ int64_t mStartTime;
    /* 0xF30 */ int64_t mSaveTotalTime;
};  // Size: 0xF38

static_assert(sizeof(dSv_info_c) == 0xF38);

#ifdef WII_PLATFORM
struct HomeMenuSts {
    uint8_t is_visible;  //              8053A968 // No idea if it is actually its true purpose, but
                         //              it seems to work
};
#endif  // WII_PLATFORM

// Functions
LIBTP_DEFINE_FUNC(setItem__17dSv_player_item_cFiUc, dSv_player_item_c__setItem_int__unsigned_char_,
                  void, dSv_player_item_c__setItem, (void* addr, int32_t slot, uint8_t item));

LIBTP_DEFINE_FUNC(getItem__17dSv_player_item_cCFib, dSv_player_item_c__getItem_int__bool__const,
                  uint8_t, dSv_player_item_c__getItem, (void* addr, int32_t slot, bool is_combo_item));

LIBTP_DEFINE_FUNC(setBombNum__24dSv_player_item_record_cFUcUc, dSv_player_item_record_c__setBombNum_unsigned_char__unsigned_char_,
                  void, dSv_player_item_record_c__setBombNum, (void* addr, uint8_t idx, uint8_t i_no));

LIBTP_DEFINE_FUNC(onFirstBit__21dSv_player_get_item_cFUc, dSv_player_get_item_c__onFirstBit_unsigned_char_,
                  void, dSv_player_get_item_c__onFirstBit, (void* addr, uint8_t item));

LIBTP_DEFINE_FUNC(offFirstBit__21dSv_player_get_item_cFUc, dSv_player_get_item_c__offFirstBit_unsigned_char_,
                  void, dSv_player_get_item_c__offFirstBit, (void* addr, uint8_t item))

LIBTP_DEFINE_FUNC(getBombNum__24dSv_player_item_record_cCFUc, dSv_player_item_record_c__getBombNum_unsigned_char__const,
                  uint8_t, dSv_player_item_record_c__getBombNum, (void* addr, uint8_t bag))

LIBTP_DEFINE_FUNC(getSelectItemIndex__21dSv_player_status_a_cCFi, dSv_player_status_a_c__getSelectItemIndex_int__const,
                  uint8_t, dSv_player_status_a_c__getSelectItemIndex, (void* addr, int32_t idx));

LIBTP_DEFINE_FUNC(isTransformLV__21dSv_player_status_b_cCFi, dSv_player_status_b_c__isTransformLV_int__const,
                  bool, dSv_player_status_b_c__isTransformLV, (void* addr, int32_t flag))

LIBTP_DEFINE_FUNC(onTransformLV__21dSv_player_status_b_cFi, dSv_player_status_b_c__onTransformLV_int_,
                  void, dSv_player_status_b_c__onTransformLV, (void* addr, int32_t flag))

LIBTP_DEFINE_FUNC(getLightDropNum__16dSv_light_drop_cCFUc, dSv_light_drop_c__getLightDropNum_unsigned_char__const,
                  uint8_t, dSv_light_drop_c__getLightDropNum, (void* addr, uint8_t area));

LIBTP_DEFINE_FUNC(setLightDropNum__16dSv_light_drop_cFUcUc, dSv_light_drop_c__setLightDropNum_unsigned_char__unsigned_char_,
                  void, dSv_light_drop_c__setLightDropNum, (void* addr, uint8_t area, uint8_t num));

LIBTP_DEFINE_FUNC(onSwitch__10dSv_info_cFii, dSv_info_c__onSwitch_int__int_,
                  void, dSv_info_c__onSwitch, (void* addr, int i_no, int i_roomNo))

LIBTP_DEFINE_FUNC(offSwitch__10dSv_info_cFii, dSv_info_c__offSwitch_int__int_,
                  void, dSv_info_c__offSwitch, (void* addr, int i_no, int i_roomNo))

LIBTP_DEFINE_FUNC(isSwitch__12dSv_memBit_cCFi, dSv_memBit_c__isSwitch_int__const,
                  bool, dSv_memBit_c__isSwitch, (void* addr, int i_no))

LIBTP_DEFINE_FUNC(onSwitch__12dSv_memBit_cFi, dSv_memBit_c__onSwitch_int_,
                  void, dSv_memBit_c__onSwitch, (void* addr, int i_no))

LIBTP_DEFINE_FUNC(offSwitch__12dSv_memBit_cFi, dSv_memBit_c__offSwitch_int_,
                  void, dSv_memBit_c__offSwitch, (void* addr, int i_no))

LIBTP_DEFINE_FUNC(getSave__10dSv_info_cFi, dSv_info_c__getSave_int_,
                  void, tp_getSave, (void* addr, int32_t areaID))

LIBTP_DEFINE_FUNC(putSave__10dSv_info_cFi, dSv_info_c__putSave_int_,
                  void, tp_putSave, (void* addr, int32_t areaID))

LIBTP_DEFINE_FUNC(isEventBit__11dSv_event_cCFUs, dSv_event_c__isEventBit_unsigned_short__const,
                  bool, dSv_event_c__isEventBit, (void* addr, uint16_t flag))

LIBTP_DEFINE_FUNC(onEventBit__11dSv_event_cFUs, dSv_event_c__onEventBit_unsigned_short_,
                  void, dSv_event_c__onEventBit, (void* addr, uint16_t flag))

LIBTP_DEFINE_FUNC(offEventBit__11dSv_event_cFUs, dSv_event_c__offEventBit_unsigned_short_,
                  void, dSv_event_c__offEventBit, (void* addr, uint16_t flag))

LIBTP_DEFINE_FUNC(isDungeonItem__12dSv_memBit_cCFi, dSv_memBit_c__isDungeonItem_int__const,
                  bool, dSv_memBit_c__isDungeonItem, (void* addr, int32_t flag))

LIBTP_DEFINE_FUNC(onDungeonItem__12dSv_memBit_cFi, dSv_memBit_c__onDungeonItem_int_,
                  void, dSv_memBit_c__onDungeonItem, (void* addr, int32_t flag))

LIBTP_DEFINE_FUNC(set__25dSv_player_return_place_cFPCcScUc, dSv_player_return_place_c__set_char_const____signed_char__unsigned_char_,
                  void, dSv_player_return_place_c__set, (void* addr, char const* i_name, int8_t roomNo, uint8_t pointNo))

#ifdef WII_PLATFORM
extern "C" {
extern bool dSv_player_get_item_c__isFirstBit_unsigned_char__const(void* addr, uint8_t idx);
}

extern HomeMenuSts homeMenuSts;
#endif  // WII_PLATFORM

#endif /* D_SAVE_D_SAVE_H */
