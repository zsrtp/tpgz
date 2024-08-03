#include "lfc_checker.h"
#include "controller.h"
#include "fifo_queue.h"
#include <cstdio>
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "libtp_c/include/d/d_procname.h"
#include "libtp_c/include/SSystem/SComponent/c_counter.h"

enum Phase {
    LADDER_START,
    LADDER_DURING,
    LADDER_DURING_2,
    LADDER_DROP,
    LADDER_DROP_2,
    LADDER_REGRAB
};

u8 phase = Phase::LADDER_START;
int frameDelta = 0;
s32 drop_1_start_frame;       // The frame the first drop started on.
s32 drop_2_start_frame;         // The frame the second drop ended on.
bool game_paused;

fopAc_ac_c* findLadderFreezard() {
    node_class* node = g_fopAcTg_Queue.mpHead;
    fopAc_ac_c* actorData = nullptr;
    const int actorName = PROC_E_FB;
    fopAc_ac_c* freezards[2] = {nullptr, nullptr};
    const float LADDER_FREEZARD_Y_POS = 950.0f;

    int foundFreezards = 0;
    for (int i = 0; i < g_fopAcTg_Queue.mSize && foundFreezards < 2; i++) {
        if (node != nullptr) {
            create_tag_class* tag = (create_tag_class*)node;
            actorData = static_cast<fopAc_ac_c*>(tag->mpTagData);

            if (actorData != nullptr && (actorData->mBase.mProcName == actorName)) {
                freezards[foundFreezards++] = actorData;
            }
            node = node->mpNextNode;
        }
    }

    for (int i = 0; i < 2; i++) {
        if (freezards[i] != nullptr && freezards[i]->current.pos.y == LADDER_FREEZARD_Y_POS) {
            return freezards[i];
        }
    }

    return nullptr;
}

void checkOnLadder(daAlink_c* link) {
    u16 current_action = link->mActionID;
    
    if (current_action == daAlink_c::PROC_LADDER_UP_START ||
            current_action == daAlink_c::PROC_LADDER_UP_END ||
            current_action == daAlink_c::PROC_LADDER_DOWN_START ||
            current_action == daAlink_c::PROC_LADDER_DOWN_END ||
            current_action == daAlink_c::PROC_LADDER_MOVE) {
                if (phase == Phase::LADDER_START) {
                    phase = Phase::LADDER_DURING;
                } else if (phase == Phase::LADDER_DROP) {
                    phase = Phase::LADDER_DURING_2;
                } else {
                    phase = Phase::LADDER_REGRAB;
                }
    } else if (phase != Phase::LADDER_DROP) {
        phase = Phase::LADDER_START;
    }
}

void checkFirstDrop(daAlink_c* link) {
    if (link->mActionID == daAlink_c::PROC_FALL) {
        if (link->current.pos.y < 247.0f) {
            char msg[15];
            sprintf(msg, "off by -%f", 247.0f - link->current.pos.y);
            FIFOQueue::push(msg, Queue, 0xFFFF0000);
            phase = Phase::LADDER_START;
            return;
        }

        if (link->current.pos.y >= 247.0f && link->current.pos.y < 249.8f) {
            FIFOQueue::push("Got it (1/2)", Queue, 0x00FF0000);
            phase = Phase::LADDER_DROP;
            drop_1_start_frame = cCt_getFrameCount();
            return;
        }

        if (link->current.pos.y >= 249.8f) {
            char msg[15];
            sprintf(msg, "off by +%f", link->current.pos.y - 249.8f);
            FIFOQueue::push(msg, Queue, 0xFF000000);
            phase = Phase::LADDER_START;
            return;
        }
    }
}

void checkSecondDrop(daAlink_c* link) {
    if (link->mActionID == daAlink_c::PROC_FALL) {
        drop_2_start_frame = cCt_getFrameCount();
        s32 delta = drop_2_start_frame - drop_1_start_frame;
#if DEBUG
        OSReport("delta: %d\n", delta);
#endif


        if (delta < 260 && delta >= 255) {
            char msg[15];
            sprintf(msg, "early by %df", 260 - delta);
            FIFOQueue::push(msg, Queue, 0x00FF0000);
            phase = Phase::LADDER_DROP_2;
            return;
        }

        if (delta >= 260 && delta < 268) {
            FIFOQueue::push("Got it (2/2)", Queue, 0x00FF0000);
            phase = Phase::LADDER_REGRAB;
            return;
        }

        if (delta >= 268 && delta < 273) {
            char msg[15];
            sprintf(msg, "late by %df", delta - 267);
            FIFOQueue::push(msg, Queue, 0x00FF0000);
            phase = Phase::LADDER_DROP_2;
            return;
        }
        
        if (delta >= 273) {
            phase = Phase::LADDER_START;
            return;
        }
        
    }
}

void framePauseUpdate() {
    if (g_dComIfG_gameInfo.play.mPauseFlag) {
#if DEBUG
        OSReport("game paused, incrementing start frame!\n");
#endif

        drop_1_start_frame += 1;
        game_paused = true;
    } else {
        if (game_paused) {
            game_paused = false;
            drop_1_start_frame++;
        }
    }
}

KEEP_FUNC void LFCChecker::execute() {
    // Retrieve player pointer
    daAlink_c* link = dComIfGp_getPlayer();

    // Early return if player pointer is invalid
    if (!link) {
        return;
    }

    if (dComIfGp_getEvent().mHalt == true) {
#if DEBUG
        OSReport("In event\n");
#endif
        return;
    }

    if (dComIfGs_getTransformStatus() != STATUS_HUMAN) {
#if DEBUG
        OSReport("Player is not in human form\n");
#endif
        return;
    }

    if (!daAlink_c__checkStageName("D_MN11")) {
#if DEBUG
        OSReport("Player is not in Snowpeak Ruins\n");
#endif
        return;
    }

    if (fopAcM_GetRoomNo(link) != 4) {
#if DEBUG
        OSReport("Player is not in courtyard\n");
#endif
        return;
    }

    fopAc_ac_c* ladder_freezard = findLadderFreezard();

    if (!ladder_freezard) {
#if DEBUG
        OSReport("Ladder Freezard not found\n");
#endif
        return;
    }

    switch(phase) {
        case Phase::LADDER_START:
            OSReport("Checking for link on ladder 1\n");
            checkOnLadder(link);
            break;
        case Phase::LADDER_DURING:
            OSReport("Checking for first drop\n");
            checkFirstDrop(link);
            break;
        case Phase::LADDER_DROP:
            OSReport("Checking for link on ladder 2\n");
            checkOnLadder(link);
            framePauseUpdate();
            break;
        case Phase::LADDER_DURING_2:
            OSReport("Checking for second drop\n");
            framePauseUpdate();
            checkSecondDrop(link);
            break;
        case Phase::LADDER_DROP_2:
            OSReport("Checking for link on ladder 3\n");
            checkOnLadder(link);
            break;
        case Phase::LADDER_REGRAB:
            OSReport("Finished!\n");
        default:
            phase = Phase::LADDER_START;
            break;
    }
}