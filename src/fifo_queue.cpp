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

        // decrement the ttl every frame until it hits zero
        if (Queue.messages[i].ttl > 0){
            Queue.messages[i].ttl--;
        }
        float offset = ((float)i * 14.0f) + 114.0f;
        int color = 0xFFFFFF00;
        int alpha = 0xFF;

        if (Queue.messages[i].ttl < 30) {
            // linear alpha fade
            alpha = Queue.messages[i].ttl * 8.5;
        }
        color |= alpha;
        Consolas.renderChars(Queue.messages[i].msg, 20.0f, offset, color);
    }
};

void FIFOQueue::push(const char* msg, _FIFOQueue& Queue) {
    for (int i = MAX_MESSAGES - 1; i > 0; i--) {
        strcpy(Queue.messages[i].msg, Queue.messages[i - 1].msg);
    }
    strcpy(Queue.messages[0].msg, msg);
    Queue.messages[0].ttl = 120;
};