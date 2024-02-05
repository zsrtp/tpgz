#ifndef M_DO_M_DO_PRINTF_H
#define M_DO_M_DO_PRINTF_H

extern "C" {
void OSReport(const char* string, ...);
void OSReport_Error(const char* fmt, ...);
void OSReport_FatalError(const char* fmt, ...);
void OSReport_System(const char* fmt, ...);
void OSReport_Warning(const char* fmt, ...);
void OSReportDisable(void);
void OSReportEnable(void);
}

#endif