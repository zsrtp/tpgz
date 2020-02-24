#include "log.h"
#include "fifo_queue.h"
#include <stdio.h>

int g_log_level;
static char buf[100];

void Log::SetLogLevel(LogLevel level) {
    g_log_level = level;
}

void Log::PrintLog(const char *msg, int log_level) {
    if (g_log_level == INFO) {
        if (log_level == INFO) {
            sprintf(buf, "[INFO] %s", msg);
            FIFOQueue::push(buf, Queue);
        }
    }
    if (g_log_level == DEBUG) {
        if (log_level == INFO) {
            sprintf(buf, "[INFO] %s", msg);
            FIFOQueue::push(buf, Queue);
        }
        if (log_level == DEBUG) {
            sprintf(buf, "[DEBUG] %s", msg);
            FIFOQueue::push(buf, Queue);
        }
    }
}