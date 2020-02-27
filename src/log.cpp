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

void Log::PrintLog(const char *strformat,const char *string, int log_level) {
    
    char tempbuf[100];
    if (g_log_level == INFO) {
        if (log_level == INFO) {
            sprintf(tempbuf, strformat, string);
            sprintf(buf, "[INFO] %s", tempbuf);
            FIFOQueue::push(buf, Queue);
        }
    }
    if (g_log_level == DEBUG) {
        if (log_level == INFO) {
            sprintf(tempbuf, strformat, string);
            sprintf(buf, "[INFO] %s", tempbuf);
            FIFOQueue::push(buf, Queue);
        }
        if (log_level == DEBUG) {
            sprintf(tempbuf, strformat, string);
            sprintf(buf, "[DEBUG] %s", tempbuf);
            FIFOQueue::push(buf, Queue);
        }
    }
}

void Log::PrintLog(const char *strformat,int value, int log_level) {
    
    char tempbuf[100];
    if (g_log_level == INFO) {
        if (log_level == INFO) {
            sprintf(tempbuf, strformat, value);
            sprintf(buf, "[INFO] %s", tempbuf);
            FIFOQueue::push(buf, Queue);
        }
    }
    if (g_log_level == DEBUG) {
        if (log_level == INFO) {
            sprintf(tempbuf, strformat, value);
            sprintf(buf, "[INFO] %s", tempbuf);
            FIFOQueue::push(buf, Queue);
        }
        if (log_level == DEBUG) {
            sprintf(tempbuf, strformat, value);
            sprintf(buf, "[DEBUG] %s", tempbuf);
            FIFOQueue::push(buf, Queue);
        }
    }
}