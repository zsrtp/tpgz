#include "libtp_c/include/system.h"
#include "fifo_queue.h"
#include "fonts/consolas.h"
#include "font.h"
#include <string.h>

static Font Consolas;

void FIFOQueue::renderItems(_FIFOQueue& Queue) {
    Consolas = Font(f_Consolas, consolas_bytes);
    Consolas.setupRendering();
    Queue.messages[0].ttl--;
    for (int i = 0; i < MAX_MESSAGES; i++) {
        float offset = (float)i * 14.0f;
        int color = 0xFFFFFF00;
        int alpha;
        switch (Queue.messages[i].ttl) {
            case 0:
                alpha = 0x00;
                break;
            case 1 ... 10:
                alpha = 0x40;
                break;
            case 11 ... 20:
                alpha = 0x80;
                break;
            case 21 ... 30:
                alpha = 0xBF;
                break;
            default:
                alpha = 0xFF;
                break;
        }
        color |= alpha;
        Consolas.renderChars(Queue.messages[i].msg, 20.0f, offset + 114.0f, color);
    }
};

void FIFOQueue::push(const char* msg, _FIFOQueue& Queue) {
    for (int i = MAX_MESSAGES - 1; i > 0; i--) {
        tp_osReport("%d",i);
        strcpy(Queue.messages[i].msg, Queue.messages[i - 1].msg);
    }
    strcpy(Queue.messages[0].msg, msg);
    Queue.messages[0].ttl = 120;
};