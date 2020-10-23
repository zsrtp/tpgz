#include "libtp_c/include/system.h"
#include "fifo_queue.h"
#include "font.h"
#include "menus/position_settings_menu.h"
#include <string.h>

bool fifo_visible;

void FIFOQueue::renderItems(_FIFOQueue& Queue) {
    for (int i = 0; i < MAX_MESSAGES; i++) {
        if (Queue.messages[i].ttl > 0) {
            Queue.messages[i].ttl--;
        }
        float offset = (-(float)i * 14.0f);
        int color = Queue.messages[i].RGBA;
        int alpha = 0xFF;
        if (Queue.messages[i].ttl < 30) {
            // linear alpha fade
            alpha = Queue.messages[i].ttl * 8.5;
        }
        color |= alpha;
        if (fifo_visible) {
            Font::renderChars(Queue.messages[i].msg, (sprite_offsets[FIFO_SPR_INDEX].x), offset + (sprite_offsets[FIFO_SPR_INDEX].y), color);
        }
    }
};

void FIFOQueue::push(const char* msg, _FIFOQueue& Queue) {
    for (int i = MAX_MESSAGES - 1; i > 0; i--) {
        strcpy(Queue.messages[i].msg, Queue.messages[i - 1].msg);
        Queue.messages[i].ttl = Queue.messages[i - 1].ttl;
        Queue.messages[i].RGBA = Queue.messages[i - 1].RGBA;
    }
    strcpy(Queue.messages[0].msg, msg);
    Queue.messages[0].ttl = 120;
    Queue.messages[0].RGBA = 0xFFFFFF00;
};

void FIFOQueue::push(const char* msg, _FIFOQueue& Queue, int RGBA) {
    for (int i = MAX_MESSAGES - 1; i > 0; i--) {
        strcpy(Queue.messages[i].msg, Queue.messages[i - 1].msg);
        Queue.messages[i].ttl = Queue.messages[i - 1].ttl;
        Queue.messages[i].RGBA = Queue.messages[i - 1].RGBA;
    }
    strcpy(Queue.messages[0].msg, msg);
    Queue.messages[0].ttl = 120;
    Queue.messages[0].RGBA = RGBA;
};