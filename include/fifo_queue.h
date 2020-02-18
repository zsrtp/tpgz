#pragma once

struct QueueMessage {
    char msg[100];
    int ttl;
};

struct _FIFOQueue {
    // max of 5 messages on the queue at a time
    QueueMessage messages[5];
};

class FIFOQueue {
   private:

   public:
    FIFOQueue();
    FIFOQueue(_FIFOQueue Queue);
    static void renderItems(_FIFOQueue& Queue, int& max_message_count);
    static void push(const char *msg, _FIFOQueue& Queue);
};