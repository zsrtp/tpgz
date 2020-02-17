#include "fifo_queue.h"
#include "fonts/consolas.h"
#include "font.h"

static Font Consolas;

void renderQueue() {
    // get all items in queue

    // if items > 1
    // render
}

void renderItems(_FIFOQueue messages) {
    Consolas.setupRendering();
    for (int i = 0; i < sizeof(messages); i++) {
        Consolas.renderChars(messages.QueueMessage[i].msg, 20.0f, 60.0f, 0xFFFFFFFF);
    }
}

void push(QueueMessage msg) {
}