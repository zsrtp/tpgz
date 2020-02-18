#pragma once

#define MAX_MESSAGES 5

struct QueueMessage {
    char msg[100];
    int ttl;
};

struct _FIFOQueue {
    // max of 5 messages on the queue at a time
    public:
    QueueMessage messages[MAX_MESSAGES];
};

class FIFOQueue {
   private:

   public:
    FIFOQueue();
    static void renderItems(_FIFOQueue& Queue);
    static void push(const char *msg, _FIFOQueue& Queue);
};

extern _FIFOQueue Queue;