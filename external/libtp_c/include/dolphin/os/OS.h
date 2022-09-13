#ifndef OS_H_
#define OS_H_

#include <stdint.h>

// move stuff to appropriate headers later

#define OS_MESSAGE_NON_BLOCKING 0
#define OS_MESSAGE_BLOCKING 1

struct OSThread;
struct OSMutex {
    uint8_t unk[24];
};

struct OSMutexLink {
    struct OSMutex* prev;
    struct OSMutex* next;
};

struct OSMutexQueue {
    struct OSMutex* prev;
    struct OSMutex* next;
};

struct OSContext {
    uint32_t gpr[32];
    uint32_t cr;
    uint32_t lr;
    uint32_t ctr;
    uint32_t xer;
    double fpr[32];
    uint32_t padding_1;
    uint32_t fpscr;
    uint32_t srr0;
    uint32_t srr1;
    uint16_t mode;
    uint16_t state;
    uint32_t gqr[8];
    uint32_t padding_2;
    double ps[32];
};

typedef void (*OSSwitchThreadCallback)(OSThread* from, OSThread* to);

struct OSThreadLink {
    struct OSThread* prev;
    struct OSThread* next;
};

struct OSThreadQueue {
    struct OSThread* head;
    struct OSThread* tail;
};

struct OSCond {
    struct OSThreadQueue queue;
};

typedef void* OSMessage;

struct OSMessageQueue {
    struct OSThreadQueue sending_queue;
    struct OSThreadQueue receiving_queue;
    void** message_array;
    int32_t num_messages;
    int32_t first_index;
    int32_t num_used;
};

typedef uint32_t OSTick;

typedef int64_t OSTime;

struct OSCalendarTime {
    int32_t seconds;
    int32_t minutes;
    int32_t hours;
    int32_t day_of_month;
    int32_t month;
    int32_t year;
    int32_t week_day;
    int32_t year_day;
    int32_t milliseconds;
    int32_t microseconds;
};

typedef int32_t OSHeapHandle;

typedef enum OSSoundMode {
    SOUND_MODE_MONO = 0,
    SOUND_MODE_STEREO = 1,
} OSSoundMode;

typedef uint16_t OSThreadState;
#define OS_THREAD_STATE_UNINITIALIZED 0
#define OS_THREAD_STATE_READY 1
#define OS_THREAD_STATE_RUNNING 2
#define OS_THREAD_STATE_WAITING 4
#define OS_THREAD_STATE_DEAD 8

struct OSThread {
    OSContext context;
    OSThreadState state;
    uint16_t attributes;
    int32_t suspend_count;
    uint32_t effective_priority;
    uint32_t base_priority;
    void* exit_value;
    OSThreadQueue* queue;
    OSThreadLink link;
    OSThreadQueue join_queue;
    OSMutex* mutex;
    OSMutexQueue owned_mutexes;
    OSThreadLink active_threads_link;
    uint8_t* stack_base;
    uint8_t* stack_end;
    uint8_t* error_code;
    void* data[2];
};

struct OSModuleInfo {
    uint32_t id;
    OSModuleInfo* next;
    OSModuleInfo* prev;
    uint32_t numSections;
    uint32_t sectionInfoOffset;
    uint32_t nameOffset;
    uint32_t nameSize;
    uint32_t version;
    uint32_t bssSize;
    uint32_t relOffset;
    uint32_t impOffset;
    uint32_t impSize;
    uint8_t prologSection;
    uint8_t epilogSection;
    uint8_t unresolvedSection;
    uint8_t bssSection;
    uint32_t prologFuncOffset;
    uint32_t epilogFuncOffset;
    uint32_t unresolvedFuncOffset;
    uint32_t moduleAlignment;
    uint32_t bssAlignment;
    uint32_t fixSize;
} __attribute__((__packed__));

struct OSModuleList {
    OSModuleInfo* first;
    OSModuleInfo* last;
    const char* unk;
} __attribute__((__packed__));

static_assert(sizeof(OSModuleInfo) == 0x4C);
static_assert(sizeof(OSModuleList) == 0xC);

extern "C" {
bool OSLink(OSModuleInfo* newModule, void* bss);
bool OSLinkFixed(OSModuleInfo* newModule, void* bss);
bool OSUnlink(OSModuleInfo* module);

bool OSDisableInterrupts();
bool OSRestoreInterrupts(bool enable);

extern OSModuleList osModuleList;
}
#endif