#pragma once

struct QueueMessage {
    char msg[50];
    int ttl;

};

struct _FIFOQueue {
    // max of 5 messages on the queue at a time
    QueueMessage msg[5];
};

class FIFOQueue {
   private:

   public:
    FIFOQueue();
    void initQueue();
    void renderQueue();
    void renderItems();
    void cleanupQueue();
    void push(QueueMessage msg);
    void pop(QueueMessage msg);
};