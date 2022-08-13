#pragma once
#include "font.h"
#define MAX_MESSAGES 25

struct QueueMessage {
    char msg[100];
    int ttl;
    uint32_t RGBA;
};

struct _FIFOQueue {
    // max of 5 messages on the queue at a time
public:
    QueueMessage messages[MAX_MESSAGES];
};

extern _FIFOQueue Queue;
extern bool g_fifoVisible;

class FIFOQueue {
private:
public:
    FIFOQueue();
    static void renderItems(_FIFOQueue& Queue);
    static void push(const char* msg, _FIFOQueue& Queue);
    static void push(const char* msg, _FIFOQueue& Queue, int RGBA);
};

extern _FIFOQueue Queue;