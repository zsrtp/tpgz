#ifndef D_MSG_D_MSG_FLOW_H
#define D_MSG_D_MSG_FLOW_H

#include "../../f_op/f_op_actor.h"

struct mesg_flow_node_branch {};

struct mesg_flow_node_event {};

struct mesg_flow_node {};

class dMsgFlow_c {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ void* field_0x04;
    /* 0x08 */ void* field_0x08;
    /* 0x0C */ void* field_0x0c;
    /* 0x10 */ uint16_t field_0x10;
    /* 0x12 */ uint16_t field_0x12;
    /* 0x14 */ fopAc_ac_c* field_0x14;
    /* 0x18 */ int field_0x18;
    /* 0x1C */ uint16_t field_0x1c;
    /* 0x1E */ uint8_t field_0x1e[2];
    /* 0x20 */ int mMsg;
    /* 0x24 */ uint8_t mSelectMessage;
    /* 0x25 */ uint8_t field_0x25;
    /* 0x26 */ uint8_t field_0x26;
    /* 0x27 */ uint8_t field_0x27;
    /* 0x28 */ int mMsgNo;
    /* 0x2C */ int mNowMsgNo;
    /* 0x30 */ uint16_t field_0x30;
    /* 0x32 */ uint16_t mEventId;
    /* 0x34 */ int field_0x34;
    /* 0x38 */ uint16_t field_0x38;
    /* 0x3A */ int16_t mChoiceNo;
    /* 0x3C */ int field_0x3c;
    /* 0x40 */ uint8_t field_0x40;
    /* 0x41 */ uint8_t field_0x41;
    /* 0x42 */ int8_t field_0x42;
    /* 0x43 */ int8_t field_0x43;
    /* 0x44 */ int8_t field_0x44;
    /* 0x45 */ int8_t field_0x45;
    /* 0x46 */ uint8_t field_0x46;
    /* 0x47 */ uint8_t field_0x47;
    /* 0x48 */ uint8_t mNonStopJunpFlowFlag;
};

#endif /* D_MSG_D_MSG_FLOW_H */
