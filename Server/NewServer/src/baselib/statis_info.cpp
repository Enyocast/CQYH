#include "stdafx.h"
#include "statis_info.h"
#include "share_mem.h"
#include "psapi.h"

stStatisInfoShm* s_pStatisShareMemory = NULL;
stStatisProcess* s_pCurrentStatisProcess = NULL;

//BOOL g_InitStatisInfo( UINT32 dwProcessID )
//{
//	INT32 nRetCode = FALSE;
//	INT32  nCurrentStatisProcessIndex = -1;
//    stStatisInfo* pInfo = NULL;
//    stStatisInfoShm * pShm = g_GetStatisInfoShm();
//    LOG_PROCESS_ERROR( pShm );
//
//    pInfo = &pShm->oInfo;
//
//	do 
//	{
//		Sleep(1);
//		nRetCode = InterlockedCompareExchange((volatile long*)&pShm->bWriting, TRUE, FALSE);
//	} while (nRetCode != FALSE);
//
//    for (INT32 i=0; i<MAX_STATIS_PROCESS_COUNT; ++i)
//    {
//		if (pShm->oInfo.ProcessInfo[i].bUsed)
//        {
//			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, TRUE, pShm->oInfo.ProcessInfo[i].dwProcessID);
//            if (hProcess == NULL)
//            {
//				pShm->oInfo.ProcessInfo[i].dwProcessID = 0;
//                pShm->oInfo.ProcessInfo[i].bUsed = FALSE;
//            }
//            else
//			{
//				DWORD dwExitCode = STILL_ACTIVE;
//				GetExitCodeProcess(hProcess, &dwExitCode);
//				if (dwExitCode != STILL_ACTIVE)
//				{
//					pShm->oInfo.ProcessInfo[i].dwProcessID = 0;
//					pShm->oInfo.ProcessInfo[i].bUsed = FALSE;
//				}
//                CloseHandle(hProcess);
//			}
//			LOG_PROCESS_ERROR(dwProcessID != pShm->oInfo.ProcessInfo[i].dwProcessID);
//        }
//    }
//
//    for (INT32 i=0; i<MAX_STATIS_PROCESS_COUNT; ++i)
//    {
//		if (!pShm->oInfo.ProcessInfo[i].bUsed)
//        {
//			pShm->oInfo.ProcessInfo[i].bUsed = TRUE;
//            pShm->oInfo.ProcessInfo[i].dwProcessID = dwProcessID;
//            nCurrentStatisProcessIndex = i;
//            break;
//        }
//    }
//    LOG_PROCESS_ERROR( nCurrentStatisProcessIndex >= 0 && nCurrentStatisProcessIndex < MAX_STATIS_PROCESS_COUNT );
//    s_pCurrentStatisProcess = s_pStatisShareMemory->oInfo.ProcessInfo + nCurrentStatisProcessIndex;
//    INF("Statis info: process %d get statis process index %d", dwProcessID, nCurrentStatisProcessIndex);
//
//	nRetCode = TRUE;
//
//Exit0:
//	if (pShm)
//	{
//		pShm->bWriting = FALSE;
//	}
//    return nRetCode;
//}

BOOL g_InitStatisInfo(UINT32 dwProcessID)
{
	INT32 nRetCode = FALSE;
	INT32  nCurrentStatisProcessIndex = -1;

	stStatisInfoShm * pShm = g_GetStatisInfoShm();
	LOG_PROCESS_ERROR(pShm);

	// check
	for (INT32 i=0; i<MAX_STATIS_PROCESS_COUNT; ++i)
	{
		if (pShm->oInfo.ProcessInfo[i].bUsed)
	    {
			LOG_PROCESS_ERROR(dwProcessID != pShm->oInfo.ProcessInfo[i].dwProcessID);
	    }
	}

	for (INT32 i = 0; i < MAX_STATIS_PROCESS_COUNT; ++i)
	{
		if (!pShm->oInfo.ProcessInfo[i].bUsed)
		{
			nRetCode = InterlockedCompareExchange((volatile long*)&pShm->oInfo.ProcessInfo[i].bUsed, TRUE, FALSE);
			if ( nRetCode == FALSE )// old value
			{
				pShm->oInfo.ProcessInfo[i].dwProcessID = dwProcessID;
				nCurrentStatisProcessIndex = i;

				break;
			}
		}
	}

	LOG_PROCESS_ERROR(nCurrentStatisProcessIndex >= 0 && nCurrentStatisProcessIndex < MAX_STATIS_PROCESS_COUNT);
	s_pCurrentStatisProcess = s_pStatisShareMemory->oInfo.ProcessInfo + nCurrentStatisProcessIndex;
	INF("Statis info: process %d get statis process index %d", dwProcessID, nCurrentStatisProcessIndex);

	nRetCode = TRUE;

Exit0:
	return nRetCode;
}

BOOL g_MainloopStatisInfo()
{
	INT32 nRetCode = FALSE;
	INT32  nCurrentStatisProcessIndex = -1;
	stStatisInfoShm * pShm = g_GetStatisInfoShm();
	LOG_PROCESS_ERROR(pShm);

	for (INT32 i = 0; i < MAX_STATIS_PROCESS_COUNT; ++i)
	{
		if (pShm->oInfo.ProcessInfo[i].bUsed)
		{
			INT32 nRemovedProcessIndex = -1;
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, TRUE, pShm->oInfo.ProcessInfo[i].dwProcessID);
			if (hProcess == NULL)
			{
				nRemovedProcessIndex = i;
			}
			else
			{
				DWORD dwExitCode = STILL_ACTIVE;
				GetExitCodeProcess(hProcess, &dwExitCode);
				if (dwExitCode != STILL_ACTIVE)
				{
					nRemovedProcessIndex = i;
				}
				CloseHandle(hProcess);
			}

			if (nRemovedProcessIndex > -1)
			{
				CRI("remove disactive process %d index %d", pShm->oInfo.ProcessInfo[i].dwProcessID, nRemovedProcessIndex);
				pShm->oInfo.ProcessInfo[nRemovedProcessIndex].dwProcessID = 0;
				pShm->oInfo.ProcessInfo[nRemovedProcessIndex].bUsed = FALSE;
			}
		}
	}

	nRetCode = TRUE;

Exit0:
	return nRetCode;
}

stStatisInfoShm* g_GetStatisInfoShm( void )
{
    BOOL nRetCode = FALSE;
    if ( NULL == s_pStatisShareMemory )
    {
        MemPtr mp;

        nRetCode = CreateSharedMemory(STATIS_MEMORY_NAME, sizeof(stStatisInfoShm), mp);
        LOG_PROCESS_ERROR(nRetCode);

        s_pStatisShareMemory = (stStatisInfoShm*)mp.pSharedMem;
        LOG_PROCESS_ERROR(s_pStatisShareMemory);

        if ( mp.bIsNew )
        {
            INF("new Statis Info share memory, init 0");
            memset(s_pStatisShareMemory, 0, sizeof(stStatisInfoShm));
            s_pStatisShareMemory->dwTag = STATIS_MEMORY_TAG;
        }
    }

    return s_pStatisShareMemory;
Exit0:
    return NULL;  
}

void g_ResetStatisInfo(void)
{
    stStatisInfo* pInfo = NULL;
    stStatisInfoShm * pShm = g_GetStatisInfoShm();
    LOG_PROCESS_ERROR( pShm );

    pInfo = &pShm->oInfo;
    LOG_PROCESS_ERROR( pInfo );

    for ( INT32 i=0; i<MAX_STATIS_PROCESS_COUNT; ++i )
    {
        memset(pInfo->ProcessInfo[i].qwStatisEntry, 0LL ,sizeof(pInfo->ProcessInfo[i].qwStatisEntry));
    }

Exit0:
    return ;
}

INT32 g_GetProcessStatisIndex(UINT32 dwProcessID)
{
	INT32 nStatisProcessIndex = -1;
	stStatisInfoShm * pShm = g_GetStatisInfoShm();

	for (INT32 i = 0; i < MAX_STATIS_PROCESS_COUNT; ++i)
	{
		if (pShm->oInfo.ProcessInfo[i].dwProcessID == dwProcessID)
		{
			if (nStatisProcessIndex < 0)
			{
				nStatisProcessIndex = i;
				//break;
			} 
			else
			{
				INT3();
			}
		}
	}
	PROCESS_ERROR(nStatisProcessIndex >= 0 && nStatisProcessIndex < MAX_STATIS_PROCESS_COUNT);
	return nStatisProcessIndex;
Exit0:
	return -1;
}

BOOL g_SetProcessStatisInfo(INT32 nStatisProcessIndex, INT32 nEnum, INT64 llValue)
{
	stStatisProcess* pStatisProcess = NULL;

	LOG_PROCESS_ERROR( s_pStatisShareMemory );
	LOG_PROCESS_ERROR(nEnum > statInvalid && nEnum < statTotal);

	LOG_PROCESS_ERROR(nStatisProcessIndex >= 0 && nStatisProcessIndex < MAX_STATIS_PROCESS_COUNT);

	pStatisProcess = s_pStatisShareMemory->oInfo.ProcessInfo + nStatisProcessIndex;
	PROCESS_ERROR(pStatisProcess);
	pStatisProcess->qwStatisEntry[nEnum] = llValue;

	return TRUE;
Exit0:
	return FALSE;
}
//
//static INT64 _CompareFileTime( FILETIME time1, FILETIME time2 )
//{
//	//LARGE_INTEGER a, b;
//	//a.LowPart = time1.dwLowDateTime;
//	//a.HighPart = time1.dwHighDateTime;
//
//	//b.LowPart = time2.dwLowDateTime;
//	//b.HighPart = time2.dwHighDateTime;
//
//	//return a.QuadPart - b.QuadPart;
//
//    INT64 a = ((INT64)time1.dwHighDateTime) << 32 | time1.dwLowDateTime;
//    INT64 b = ((INT64)time2.dwHighDateTime) << 32 | time2.dwLowDateTime;
//    return a - b;
//}
//
//static FILETIME s_LatestIdelTime = { 0 };
//static FILETIME s_LatestKernelTime = { 0 };
//static FILETIME s_LatestUserTime = { 0 };
//
//BOOL g_UpdateSystemStatisInfo(void)
//{
//	INT64 llCpuUsage = 0;
//	INT64 llMemUsage = 0;
//
//	FILETIME PreIdleTime = s_LatestIdelTime;
//	FILETIME PreKernelTime = s_LatestKernelTime;
//	FILETIME PreUserTime = s_LatestUserTime;
//
//	GetSystemTimes(&s_LatestIdelTime, &s_LatestKernelTime, &s_LatestUserTime);
//
//	INT64 nIdleTime = _CompareFileTime(s_LatestIdelTime, PreIdleTime);
//	INT64 nKernelTime = _CompareFileTime(s_LatestKernelTime, PreKernelTime);
//	INT64 nUserTime = _CompareFileTime(s_LatestUserTime, PreUserTime);
//
//	LOG_PROCESS_ERROR(nKernelTime + nUserTime > 0);
//	llCpuUsage = (nKernelTime + nUserTime - nIdleTime) * 100 / (nKernelTime + nUserTime);
//	g_SetStatisInfo(statCpuUsage, (INT32)llCpuUsage);
//
//	MEMORYSTATUSEX Status;
//	Status.dwLength = sizeof(Status);
//	GlobalMemoryStatusEx(&Status);
//
//	llMemUsage = Status.ullTotalPageFile - Status.ullAvailPageFile;
//	g_SetStatisInfo(statMemUsage, (INT32)llMemUsage);
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
//
//static FILETIME s_SystemLatestIdelTime = { 0 };
//static FILETIME s_SystemLatestKernelTime = { 0 };
//static FILETIME s_SystemLatestUserTime = { 0 };
//
//static FILETIME s_ProcessLatestKernelTime = { 0 };
//static FILETIME s_ProcessLatestUserTime = { 0 };

//BOOL g_UpdateProcessStatisInfo(void)
//{
//	INT64 llCpuUsage = 0;
//	INT64 llMemUsage = 0;
//
//	//SYSTEM_INFO siSysInfo;
//	//GetSystemInfo(&siSysInfo);
//	//INT32 nCoreNum = siSysInfo.dwNumberOfProcessors;
//	PROCESS_MEMORY_COUNTERS pmc;
//
//	FILETIME ftProcessCreation = { 0 };
//	FILETIME ftProcessExit = { 0 };
//	FILETIME ftSystemIdleTime = { 0 };
//
//	FILETIME PreProcessKernelTime = s_ProcessLatestKernelTime;
//	FILETIME PreProcessUserTime = s_ProcessLatestUserTime;
//	FILETIME PreSystemKernelTime = s_SystemLatestKernelTime;
//	FILETIME PreSystemUserTime = s_SystemLatestUserTime;
//
//	GetSystemTimes(&ftSystemIdleTime, &s_SystemLatestKernelTime, &s_SystemLatestUserTime);
//	GetProcessTimes(GetCurrentProcess(), &ftProcessCreation, &ftProcessExit, &s_ProcessLatestKernelTime, &s_ProcessLatestUserTime);
//
//	INT64 nSystemKernelDiff = _CompareFileTime(s_SystemLatestKernelTime, PreSystemKernelTime);
//	INT64 nSystemUserDiff = _CompareFileTime(s_SystemLatestUserTime, PreSystemUserTime);
//
//	INT64 nProcessKernelDiff = _CompareFileTime(s_ProcessLatestKernelTime, PreProcessKernelTime);
//	INT64 nProcessUserDiff = _CompareFileTime(s_ProcessLatestUserTime, PreProcessUserTime);
//
//	INT64 nTotalSys = nSystemKernelDiff + nSystemUserDiff;
//	INT64 nTotalProc = nProcessKernelDiff + nProcessUserDiff;
//
//	if (nTotalSys > 0)
//	{
//		llCpuUsage = (INT64)((100.0 * nTotalProc) / nTotalSys);
//		llCpuUsage = llCpuUsage < 0 ? 0 : llCpuUsage;
//	}
//	g_SetStatisInfo(statCpuUsage, (INT32)llCpuUsage);
//
//	//
//	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
//	llMemUsage = pmc.PeakWorkingSetSize / 1024;
//	g_SetStatisInfo(statMemUsage, (INT32)llMemUsage);
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
