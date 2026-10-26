#ifndef _REPORT_H_
#define _REPORT_H_

#include <stdio.h>

#define REPORT    g_ReportLog

void g_InitReportSetting(const char* szServerType, UINT8 byServerID, const char* szOutPutPath);

BOOL g_ReportLog(INT32 nLevel, const char* pcszMessage, ...);

#endif // _REPORT_H_