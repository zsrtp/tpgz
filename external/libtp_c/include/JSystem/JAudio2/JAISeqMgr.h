#ifndef JAISEQMGR_H
#define JAISEQMGR_H

#include "JAIAudience.h"
#include "JAISeqDataMgr.h"
#include "JAISound.h"
#include "../JSupport/JSUList.h"

struct JAISeq;

class JAISeqMgr : public JAISeqDataUser {
public:
    /* 0x04 */ JAISoundActivity mActivity;
    /* 0x08 */ void* field_0x8;
    /* 0x0C */ JAIAudience* mAudience;
    /* 0x10 */ JAISeqDataMgr* seqDataMgr_;
    /* 0x14 */ JAISoundParamsMove mMove;
    /* 0x64 */ JSUList<JAISeq> mSeqList;
    /* 0x70 */ int field_0x70;
};  // Size: 0x74

#endif /* JAISEQMGR_H */