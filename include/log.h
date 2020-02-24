extern int g_log_level;

enum LogLevel {
    NONE = 0,
    INFO = 1,
    DEBUG = 2
};

class Log {
    public:
     void SetLogLevel(LogLevel level);
     void PrintLog(const char *msg, int l_log_level);
};