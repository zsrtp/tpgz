#include "libtp_c/include/system.h"
#include "fifo_queue.h"
#include "fonts/consolas.h"
#include "font.h"
#include <string.h>

static Font Consolas;

void FIFOQueue::renderItems(_FIFOQueue& Queue) {
    Consolas = Font(f_Consolas, consolas_bytes);
    Consolas.setupRendering();
    for (int i = 0; i < MAX_MESSAGES; i++) {
        float offset = (float)i * 14.0f;
        Consolas.renderChars(Queue.messages[i].msg, 20.0f, offset + 114.0f, 0xFFFFFFFF);
    }
};

void FIFOQueue::push(const char* msg, _FIFOQueue& Queue) {
    for (int i = MAX_MESSAGES - 1; i > 0; i--) {
        tp_osReport("%d",i);
        strcpy(Queue.messages[i].msg, Queue.messages[i - 1].msg);
    }
    strcpy(Queue.messages[0].msg, msg);
};