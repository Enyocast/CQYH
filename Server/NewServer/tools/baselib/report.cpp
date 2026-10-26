#include "stdafx.h"

#include "report.h"
#include "time_ex.h"

static char gs_szServerType[8] = { 0 };
static UINT8 gs_byServerID = 0;
static char gs_szOutPutPath[256] = { 0 };
static UINT32 gs_dwPID = 0;
//static char gs_szIP4[64] = { 0 };

void g_InitReportSetting(const char* szServerType, UINT8 byServerID, const char* szOutPutPath)
{
	strxcpy(gs_szServerType, szServerType, sizeof(gs_szServerType));
	gs_byServerID = byServerID;
	strxcpy(gs_szOutPutPath, szOutPutPath, sizeof(gs_szOutPutPath));

	gs_dwPID = GetCurrentProcessId();

	//struct in_addr addr;
	//addr.s_addr = GetIp(g_ServerConfig.Common.szIntranetAddr, g_ServerConfig.Common.szIntranetMask, TRUE, 0);
	//LOG_PROCESS_ERROR(addr.s_addr);
	//snprintf(gs_szIP4, sizeof(gs_szIP4), "%s", inet_ntoa(addr));
}

BOOL g_ReportLog(INT32 nLevel, const char* pcszMessage, ...)
{
	BOOL nResult = FALSE;
	INT32 nRetCode = 0;
	WIN32_FIND_DATA FileData;
	const tm_ex* pNow = NULL;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szBuffer[1024] = { 0 };
	DWORD nBufferLen = 0;
	DWORD nBufferWritenLen = 0;
	INT32 nOpenFailedCount = 0;

	char szFilePath[256] = {0};
	strxcpy(szFilePath, gs_szOutPutPath, sizeof(szFilePath));

	HANDLE hFind = FindFirstFile(szFilePath, &FileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		nRetCode = CreateDirectory(szFilePath, NULL);
		LOG_PROCESS_ERROR(nRetCode);
	}
	else
	{
		FindClose(hFind);
		if (!(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			CRI("%s exist but not a directory!", szFilePath);
			LOG_PROCESS_ERROR(FALSE);
		}
	}
	snprintf(szFilePath + strlen(szFilePath), sizeof(szFilePath) - strlen(szFilePath), "\\%s", "report.log");

	do 
	{
		hFile = CreateFile(szFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
		++nOpenFailedCount;
		const INT32 MAX_TRY_TIMES = 32;
		if (nOpenFailedCount > MAX_TRY_TIMES) // avoid infinite loop
		{
			CRI("failed to open file %s again and again beyond %d times!", szFilePath, MAX_TRY_TIMES);
			break;
		}
	} while (hFile == INVALID_HANDLE_VALUE);
	LOG_PROCESS_ERROR(hFile != INVALID_HANDLE_VALUE);

	pNow = localtime_ex();
	nRetCode = snprintf(szBuffer, sizeof(szBuffer),
		"REPORT_%d [%s:%d] PID=%05d %d-%02d-%02d %02d:%02d:%02d.%03d ",
		nLevel, gs_szServerType, gs_byServerID, gs_dwPID,
		pNow->tm_year, pNow->tm_mon, pNow->tm_mday,
		pNow->tm_hour, pNow->tm_min, pNow->tm_sec, pNow->tm_msec);

	va_list valist;
	va_start(valist, pcszMessage);

	nBufferLen = strlen(szBuffer);
	vsnprintf(szBuffer + nBufferLen, sizeof(szBuffer) - nBufferLen, pcszMessage, valist);

	va_end(valist);

	nBufferLen = strlen(szBuffer);
	snprintf(szBuffer + nBufferLen, sizeof(szBuffer) - nBufferLen, "\r\n");

	nBufferLen = strlen(szBuffer);

	SetFilePointer(hFile, 0, NULL, FILE_END);

	WriteFile(hFile, szBuffer, nBufferLen, &nBufferWritenLen, NULL);
	LOG_PROCESS_ERROR(nBufferLen == nBufferWritenLen);

	nResult = TRUE;
Exit0:
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}
	return nResult;
}

