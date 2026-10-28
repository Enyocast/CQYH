#include "stdafx.h"
#include "server_def.h"
#include "process_option.h"
#include "gd_session_mgr.h"
#include "process_mgr.h"
#include "guardserver.h"
#include "statis_info.h"
#include "time_ex.h"
#include "ifile.h"
#include "gd_session_mgr.h"
#include "gd_message_handler.h"

#if defined(WIN32)
    #include "psapi.h"
#endif

#include "guard_config.h"

CProcessMgr CProcessMgr::ms_Instance;
CProcessMgr::CProcessMgr()
{
	m_qwLastStatisTick = 0;
}

CProcessMgr::~CProcessMgr()
{
    UnInit();
}

BOOL CProcessMgr::Init()
{
    INT32 nRetCode = 0;
	m_qwLastStatisTick = 0;
    m_listProcess.clear();

#if defined(WIN32)
    DWORD dwProcessesList[1024] = {0}; 
    DWORD dwByteCount = 0;
    INT32 nProcessCount = 0;
	char stExpactProcessName[128] = { 0 };
	char stExpactDebugProcessName[128] = { 0 };
    char stProcessName[128] = {0};

    //do 
    //{
        nRetCode = EnumProcesses(dwProcessesList, sizeof(dwProcessesList), &dwByteCount);
        LOG_PROCESS_ERROR(nRetCode);

        nProcessCount = dwByteCount / sizeof(UINT32);
		LOG_PROCESS_ERROR(nProcessCount <= sizeof(dwProcessesList) / sizeof(dwProcessesList[0]));

        for ( INT32 i = 0; i < nProcessCount; i++ )
        {
            HMODULE hMod;
            DWORD dwByteNeeded;

            if(dwProcessesList[i] == 0 )
                continue;
            
            HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                FALSE, 
                dwProcessesList[i]);

            if(hProcess == NULL)
                continue;

            if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &dwByteNeeded))
            {
                nRetCode = GetModuleBaseName(hProcess, hMod, stProcessName, sizeof(stProcessName));
                if(nRetCode == 0)
                    continue;

                for (INT32 nType = stMS; nType <= stDL; ++nType)
                {
					snprintf(stExpactProcessName, sizeof(stExpactProcessName), "%s64.exe", GetServerName(nType));
					snprintf(stExpactDebugProcessName, sizeof(stExpactDebugProcessName), "%s64_d.exe", GetServerName(nType));//
                    if( strncmp(stExpactProcessName, stProcessName, strlen(stExpactProcessName)) == 0 ||
						strncmp(stExpactDebugProcessName, stProcessName, strlen(stExpactDebugProcessName)) == 0)//
                    {
                        SProcessInfo stProcessInfo;
                        stProcessInfo.byType = nType;
                        stProcessInfo.dwProcessID = dwProcessesList[i];
						stProcessInfo.ftProcessCreationTime = {0};
                        stProcessInfo.dwIP = 0;
                        m_listProcess.push_back(stProcessInfo);
                    }
                }
            }

            nRetCode = CloseHandle(hProcess);
            LOG_CHECK_ERROR(nRetCode);
        }
    //} while (nProcessCount >= 1024);

#elif defined(__linux__)

    {
        char szLine[256] = { 0 };
        char szProcessCmd[64] = {0};
        int  nProcessID = 0;
        char* pCmd = "/bin/ps x | /bin/grep server | /bin/grep -v grep | /bin/awk '{print $1,$5}' ";

        FILE* pFile = popen( pCmd, "r" );
        LOG_PROCESS_ERROR(pFile);

        while( fgets( szLine, sizeof(szLine), pFile ) )
        {
            sscanf(szLine, "%d %s", &nProcessID, szProcessCmd );

            for (INT32 nType = stMS; nType <= stDL; ++nType)
            {
				if(strstr(szProcessCmd, GetServerName[nType]) != 0)
                {
                    SProcessInfo stProcessInfo;
                    stProcessInfo.byType = nType;
                    stProcessInfo.dwProcessID = nProcessID;
                    stProcessInfo.dwIP = 0;
                    m_listProcess.push_back(stProcessInfo);
                }
            }
        }

        if ( pFile )
            pclose( pFile );
    }

#endif  // __linux__ 

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CProcessMgr::UnInit(void)
{
    m_listProcess.clear();
    return TRUE;
}

CProcessMgr& CProcessMgr::GetInstance(void)
{
    return ms_Instance;
}

BOOL CProcessMgr::StartProcess(UINT8 byType, char* szCmdLine, BOOL bView, BOOL bRunRelease, BOOL bAuto)
{
    INT32 nRetCode = 0;
    char szFullCmdLine[256] = {0};
    char szViewCmd[32] = {0};
    SProcessInfo stProcess;

#if defined(WIN32)
    switch (byType)
    {
    case stMS:
        {
            nRetCode = CountRuningProcessByType(stMS);
            PROCESS_ERROR(!nRetCode);

            if(bView)
                snprintf(szViewCmd, 32, "view 950 455");
        }
        break;
    case stDB:
        {
            nRetCode = CountRuningProcessByType(stDB);
            PROCESS_ERROR(!nRetCode);

            if(bView)
                snprintf(szViewCmd, 32, "view 240 455");
        }
        break;
    case stLS:
        {
            nRetCode = CountRuningProcessByType(stLS);
            PROCESS_ERROR(!nRetCode);

            if(bView)
                snprintf(szViewCmd, 32, "view 240 5");
        }
        break;
	case stBS:
		{
			nRetCode = CountRuningProcessByType(stBS);
			PROCESS_ERROR(!nRetCode);

            if(bView)
                snprintf(szViewCmd, 32, "view 5 5");
		}
		break;
	case stDL:
		{
			nRetCode = CountRuningProcessByType(stDL);
			PROCESS_ERROR(!nRetCode);

			if(bView)
				snprintf(szViewCmd, 32, "view 5 5");
		}
		break;
    case stGT:
        {
            if(bView)
                snprintf(szViewCmd, 32, "view 240 5");
        }
        break;
    case stGS:
        {
            if(bView)
                snprintf(szViewCmd, 32, "view 950 5");
        }
        break;
    case stGM:
        {
            if(bView)
                snprintf(szViewCmd, 32, "view 830 15");
        }
        break;
	case stMM:
	{
		if (bView)
			snprintf(szViewCmd, 32, "view 240 455");
		break;
	}
	case stMG:
	{
		if (bView)
			snprintf(szViewCmd, 32, "view 5 5");
		break;
	}
	default:
        LOG_PROCESS_ERROR(FALSE);
    };

    LOG_PROCESS_ERROR(byType> stGD && byType < stAll);

//#ifdef _DEBUG
//    snprintf(szFullCmdLine, 256, "./%s/%s64_d.exe", szProcessNameList[byType], szProcessNameList[byType]);
//#else
//    snprintf(szFullCmdLine, 256, "./%s/%s64.exe", szProcessNameList[byType], szProcessNameList[byType]);
//#endif

	if (g_GuardConfig.szServerRunPath[0] == '\0')
	{
		//snprintf(g_GuardConfig.szServerRunPath, sizeof(g_GuardConfig.szServerRunPath), "../../bin"); // default path
	}
    if(bRunRelease)
    {
		snprintf(szFullCmdLine, 256, "%s/%s/%s64.exe", g_GuardConfig.szServerRunPath, GetServerName(byType), GetServerName(byType));
    }
    else
    {
		snprintf(szFullCmdLine, 256, "%s/%s/%s64_d.exe", g_GuardConfig.szServerRunPath, GetServerName(byType), GetServerName(byType));
    }

	if (!g_IsFileExist(szFullCmdLine))
	{
		GD_ERROR_MT("file %s don't exist!", szFullCmdLine);
		CRI("file %s don't exist!", szFullCmdLine);
		LOG_PROCESS_ERROR(FALSE);
	}

    if(szCmdLine)
        snprintf(szFullCmdLine, 256, "%s %s", szFullCmdLine, szCmdLine);

    if(bView)
        snprintf(szFullCmdLine, 256, "%s %s", szFullCmdLine, szViewCmd);

    {
        STARTUPINFO stStartInfo = {sizeof(stStartInfo)};
        PROCESS_INFORMATION stNewProcessInfo;

        nRetCode = CreateProcess(NULL, szFullCmdLine, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE, NULL, g_GuardConfig.szServerRunPath, &stStartInfo, &stNewProcessInfo);
        if(nRetCode == 0)
        {
            UINT32 dwError = GetLastError();
			INF("createProcess %s error %u", szFullCmdLine, dwError);
			GD_ERROR_MT("createProcess %s error %u", szFullCmdLine, dwError);
			LOG_PROCESS_ERROR(FALSE);
        }
        LOG_PROCESS_ERROR(stNewProcessInfo.dwProcessId > 0);

        stProcess.byType = byType;
		stProcess.bySessionID = 0;
		stProcess.bAuto = bAuto;
		stProcess.dwProcessID = stNewProcessInfo.dwProcessId;
		stProcess.ftProcessCreationTime = { 0 };
        stProcess.dwIP = 0;
        m_listProcess.push_back(stProcess);

        CloseHandle(stNewProcessInfo.hProcess);
        CloseHandle(stNewProcessInfo.hThread);
    }
#elif defined(__linux__)
    {
        const int STR_LEN = 256;
        char szPath[STR_LEN] = {0};
        char szCmd[STR_LEN] = {0};
        //char szArgs[STR_LEN] = {0};

		snprintf(szPath, STR_LEN, "./%s", GetServerName[byType]);
		snprintf(szCmd, STR_LEN, "%s", GetServerName[byType]);

        nRetCode = fork();
        if ( nRetCode == 0 ) // child process
        {
            nRetCode = execlp( szPath, szCmd );
            CRI("execlp process failed! cmd: %s/%s", szPath, szCmd );
            LOG_PROCESS_ERROR(FALSE);
        }
        else if( nRetCode > 0 ) // this process
        {
            stProcess.byType = byType;
            stProcess.dwProcessID = nRetCode; // child process ID
            stProcess.dwIP = 0;
            m_listProcess.push_back(stProcess);
        }
        else // error
        {
            CRI("fork process failed! cmd: %s/%s", szPath, szCmd );
            LOG_PROCESS_ERROR(FALSE);
        }
    }
#endif

	nRetCode = CGDMessageHandler::GetInstance().DoMTUpdateProcess(InternalMessage::epsUnonnect, stProcess.dwProcessID,
		stProcess.byType, stProcess.bySessionID, stProcess.bAuto);
	LOG_CHECK_ERROR( nRetCode );

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CProcessMgr::CloseProcess(UINT8 byType)
{
    INT32 nRetCode = 0;
	HANDLE hHandle = NULL;
    CSprocessListItr itr = m_listProcess.begin();
    while(itr != m_listProcess.end())
    {
        if(itr->byType == byType ) 
        {
            if( itr->dwIP == 0)
            {

#if defined(WIN32)
                hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, itr->dwProcessID);
                LOG_PROCESS_ERROR(hHandle);

                nRetCode = TerminateProcess(hHandle, 0);
                LOG_PROCESS_ERROR(nRetCode);

                CloseHandle(hHandle);
                hHandle = NULL;

#elif defined(__linux__)
                {
                    char szCmd[256] = {0};
                    snprintf( szCmd, strlen(szCmd), "/bin/kill -9 %d", itr->dwProcessID );

                    FILE* pFile = popen( szCmd, "r" );
                    LOG_PROCESS_ERROR(pFile);    

                    if ( pFile)
                        pclose( pFile );
                }
#endif
            }
            else if(itr->dwIP > 0)
			{
				//远程关闭
				CRI("CProcessMgr::CloseProcess itr->dwIP > 0");
			}

			//itr = m_listProcess.erase(itr); // operate in mainloop
			++itr;
        }
        else
        {
            ++itr;
        } 
    }
    LOG_PROCESS_ERROR( itr != m_listProcess.end() );

    return TRUE;
Exit0:
	if(hHandle)
		CloseHandle(hHandle);

    return FALSE;
}

BOOL CProcessMgr::StartAllProcess(char* szCmdLine, BOOL bView, BOOL bRunRelease )
{
    INT32 nRetCode = 0;
	BOOL bAuto = TRUE;

	for (INT32 i = stMS; i <= stMG; ++i)
    {
        switch(i)
        {
        case stMS:
            {
                PROCESS_ERROR(!CountRuningProcessByType(stMS));
				
				LOG_CHECK_ERROR(g_GuardConfig.nLocalMSCount > 0);
				if (g_GuardConfig.nLocalMSCount > 0)
				{
					nRetCode = StartProcess(stMS, szCmdLine, bView, bRunRelease, bAuto);
					LOG_PROCESS_ERROR(nRetCode);
				}
            }
            break;
        case stLS:
            {
                PROCESS_ERROR(!CountRuningProcessByType(stLS));

				LOG_CHECK_ERROR(g_GuardConfig.nLocalLSCount > 0);
				if(g_GuardConfig.nLocalLSCount > 0)
				{
					nRetCode = StartProcess(stLS, szCmdLine, bView, bRunRelease, bAuto);
					LOG_PROCESS_ERROR(nRetCode);
				}
            }
            break;
        case stDB:
            {
                PROCESS_ERROR(!CountRuningProcessByType(stDB));

				LOG_CHECK_ERROR(g_GuardConfig.nLocalDBCount > 0);
				if(g_GuardConfig.nLocalDBCount > 0)
				{
					nRetCode = StartProcess(stDB, szCmdLine, bView, bRunRelease, bAuto);
					LOG_PROCESS_ERROR(nRetCode);
				}
            }
            break;
        case stBS:
            {
                PROCESS_ERROR(!CountRuningProcessByType(stBS));

				LOG_CHECK_ERROR(g_GuardConfig.nLocalBSCount > 0);
				if (g_GuardConfig.nLocalBSCount > 0)
                {
					nRetCode = StartProcess(stBS, szCmdLine, bView, bRunRelease, bAuto);
                    LOG_PROCESS_ERROR(nRetCode);
                }
            }
            break;
		case stDL:
			{
				PROCESS_ERROR(!CountRuningProcessByType(stDL));

				LOG_CHECK_ERROR(g_GuardConfig.nLocalDLCount > 0);
				if (g_GuardConfig.nLocalDLCount > 0)
				{
					nRetCode = StartProcess(stDL, szCmdLine, bView, bRunRelease, bAuto);
					LOG_PROCESS_ERROR(nRetCode);
				}
			}
			break;
        case stGS:
            {
                INT32 nCurGScount = CountRuningProcessByType(stGS);
				if (nCurGScount > 0)
				{
					CRI("there has been GS count:%d", nCurGScount);
				}

				LOG_CHECK_ERROR(g_GuardConfig.nLocalGSCount > 0);
				for (INT32 j = nCurGScount; j < g_GuardConfig.nLocalGSCount; ++j)
                {
					nRetCode = StartProcess(stGS, szCmdLine, bView, bRunRelease, bAuto);
                    LOG_PROCESS_ERROR(nRetCode);
                }
            }
            break;
        case stGT:
            {
				INT32 nCurGTcount = CountRuningProcessByType(stGT);
				if (nCurGTcount > 0)
				{
					CRI("there has been GT count:%d", nCurGTcount);
				}

				LOG_CHECK_ERROR(g_GuardConfig.nLocalGTCount > 0);
				for (INT32 j = nCurGTcount; j < g_GuardConfig.nLocalGTCount; ++j)
                {
					nRetCode = StartProcess(stGT, szCmdLine, bView, bRunRelease, bAuto);
                    LOG_PROCESS_ERROR(nRetCode);
                }
            }
            break;
        case stGM:
            {
                INT32   nCurGMCount = CountRuningProcessByType(stGM);
				PROCESS_ERROR(nCurGMCount == 0);

				if (g_GuardConfig.nLocalGMCount > 0)
                {
					nRetCode = StartProcess(stGM, szCmdLine, bView, bRunRelease, bAuto);
                    LOG_PROCESS_ERROR(nRetCode);
                }
            }
            break;
		case stMM:
		{
			PROCESS_ERROR(CountRuningProcessByType(stMM) == 0);

			if (g_GuardConfig.nLocalMMCount > 0)
			{
				nRetCode = StartProcess(stMM, szCmdLine, bView, bRunRelease, bAuto);
				LOG_PROCESS_ERROR(nRetCode);
			}

			break;
		}
		case stMG:
		{
			INT32 nCount = CountRuningProcessByType(stMG);
			if (nCount > 0)
			{
				CRI("there has been MG count:%d", nCount);
			}

			LOG_CHECK_ERROR(g_GuardConfig.nLocalMGCount > 0);
			for (INT32 j = nCount; j < g_GuardConfig.nLocalMGCount; ++j)
			{
				nRetCode = StartProcess(stMG, szCmdLine, bView, bRunRelease, bAuto);
				LOG_PROCESS_ERROR(nRetCode);
			}
			break;
		}
        default:
            {
                LOG_PROCESS_ERROR(FALSE);
            }
            break;
        }
    }
    
    return TRUE;
Exit0:
    //nRetCode = StopAllProcess();
    //LOG_CHECK_ERROR(nRetCode);

    return FALSE;
}

BOOL CProcessMgr::CloseAllProcess()
{
	INT32 nRetCode = 0;
	HANDLE hHandle = NULL;

	CSprocessListItr itr = m_listProcess.begin();
	while (itr != m_listProcess.end())
	{
		if (itr->dwIP == 0)
		{
			hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, itr->dwProcessID);
			LOG_PROCESS_ERROR(hHandle);

			nRetCode = TerminateProcess(hHandle, 0);
			LOG_PROCESS_ERROR(nRetCode);

			CloseHandle(hHandle);
			hHandle = NULL;
		}
		else if (itr->dwIP > 0)
		{
			//远程关闭
			CRI("CProcessMgr::CloseAllProcess itr->dwIP > 0");
		}

		//itr = m_listProcess.erase(itr); // operate in mainloop
		++itr;
	}

    return TRUE;
Exit0:
	return FALSE;
}

INT32 CProcessMgr::CountRuningProcessByType(UINT8 byType)
{
    INT32 nProcessCount = 0;

	if(byType == stAll)
    {
        nProcessCount = m_listProcess.size();
    }
	else
	{
		for(CSprocessListItr itr = m_listProcess.begin(); itr != m_listProcess.end(); ++itr)
		{      
			if(itr->byType == byType)
				nProcessCount++;
		}
	}

    return nProcessCount;
}

BOOL CProcessMgr::IsProcessRuningByID(UINT32 dwProcessID)
{
    for(CSprocessListItr itr = m_listProcess.begin(); itr != m_listProcess.end(); ++itr)
    {      
        if(itr->dwProcessID == dwProcessID)
            return TRUE;
    }
    
    return FALSE;
}

static INT64 _CompareFileTime(FILETIME time1, FILETIME time2)
{
	//LARGE_INTEGER a, b;
	//a.LowPart = time1.dwLowDateTime;
	//a.HighPart = time1.dwHighDateTime;

	//b.LowPart = time2.dwLowDateTime;
	//b.HighPart = time2.dwHighDateTime;

	//return a.QuadPart - b.QuadPart;

	INT64 a = ( ((INT64)time1.dwHighDateTime) << 32 ) | time1.dwLowDateTime;
	INT64 b = ( ((INT64)time2.dwHighDateTime) << 32 ) | time2.dwLowDateTime;
	return a - b;
}

BOOL CProcessMgr::UpdateServersStatis(UINT32 dwProcessID)
{
	static FILETIME s_SystemLatestIdelTime[MAX_STATIS_PROCESS_COUNT] = { 0 };
	static FILETIME s_SystemLatestKernelTime[MAX_STATIS_PROCESS_COUNT] = { 0 };
	static FILETIME s_SystemLatestUserTime[MAX_STATIS_PROCESS_COUNT] = { 0 };

	static FILETIME s_ProcessLatestKernelTime[MAX_STATIS_PROCESS_COUNT] = { 0 };
	static FILETIME s_ProcessLatestUserTime[MAX_STATIS_PROCESS_COUNT] = { 0 };

	INT32 nRetCode = FALSE;
	INT32 nProcessIndex = -1;
	INT64 llCpuUsage = 0LL;
	UINT64 qwMemUsage = 0LL;

	HANDLE hProcessHandle = INVALID_HANDLE_VALUE;
		
	hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
	LOG_PROCESS_ERROR(hProcessHandle);

	nProcessIndex = g_GetProcessStatisIndex(dwProcessID);
	if (nProcessIndex < 0 || nProcessIndex >= MAX_STATIS_PROCESS_COUNT)
	{
		CRI("can't find process %d in statis shm", dwProcessID );
		PROCESS_ERROR(FALSE);
	}

	//SYSTEM_INFO siSysInfo;
	//GetSystemInfo(&siSysInfo);
	//INT32 nCoreNum = siSysInfo.dwNumberOfProcessors;
	PROCESS_MEMORY_COUNTERS pmc;

	FILETIME ftProcessCreation = { 0 };
	FILETIME ftProcessExit = { 0 };
	FILETIME ftSystemIdleTime = { 0 };

	FILETIME PreProcessKernelTime = s_ProcessLatestKernelTime[nProcessIndex];
	FILETIME PreProcessUserTime = s_ProcessLatestUserTime[nProcessIndex];
	FILETIME PreSystemKernelTime = s_SystemLatestKernelTime[nProcessIndex];
	FILETIME PreSystemUserTime = s_SystemLatestUserTime[nProcessIndex];

	GetSystemTimes(&ftSystemIdleTime, &s_SystemLatestKernelTime[nProcessIndex], &s_SystemLatestUserTime[nProcessIndex]);
	GetProcessTimes(hProcessHandle, &ftProcessCreation, &ftProcessExit, &s_ProcessLatestKernelTime[nProcessIndex], &s_ProcessLatestUserTime[nProcessIndex]);

	INT64 nSystemKernelDiff = _CompareFileTime(s_SystemLatestKernelTime[nProcessIndex], PreSystemKernelTime);
	INT64 nSystemUserDiff = _CompareFileTime(s_SystemLatestUserTime[nProcessIndex], PreSystemUserTime);

	INT64 nProcessKernelDiff = _CompareFileTime(s_ProcessLatestKernelTime[nProcessIndex], PreProcessKernelTime);
	INT64 nProcessUserDiff = _CompareFileTime(s_ProcessLatestUserTime[nProcessIndex], PreProcessUserTime);

	INT64 nTotalSys = nSystemKernelDiff + nSystemUserDiff;
	INT64 nTotalProc = nProcessKernelDiff + nProcessUserDiff;

	if (nTotalSys > 0)
	{
		llCpuUsage = (INT64)((100.0 * nTotalProc) / nTotalSys);
		LOG_CHECK_ERROR(llCpuUsage >= 0);
	}
	//g_SetStatisInfo(statCpuUsage, (INT32)llCpuUsage);
	nRetCode = g_SetProcessStatisInfo(nProcessIndex, statCpuUsage, llCpuUsage);
	LOG_PROCESS_ERROR( nRetCode );

	//
	nRetCode = GetProcessMemoryInfo(hProcessHandle, &pmc, sizeof(pmc));
	LOG_PROCESS_ERROR( nRetCode );
	/*
	static INT64 s_llOldMemUsage = 0;

	char szImageFileName[COMMON_NAME_LEN] = {0};
	nRetCode = GetProcessImageFileName(hHandle, szImageFileName, COMMON_NAME_LEN);
	if (strstr(szImageFileName,"gameserver64") > 0)
	{
		if (s_llOldMemUsage < pmc.PagefileUsage)
		{
			char szTitle[MAX_PATH];
			snprintf(szTitle, MAX_PATH, "Guard Server, game memory usage old=%d, new=%d", s_llOldMemUsage, pmc.PeakPagefileUsage);
			SetConsoleTitle(szTitle);
			INF(szTitle);
		}
		s_llOldMemUsage = pmc.PagefileUsage;
	}
	*/
	qwMemUsage = pmc.PagefileUsage;// pmc.PeakWorkingSetSize / 1024;
	//g_SetStatisInfo(statMemUsage, (INT32)llMemUsage);
	nRetCode = g_SetProcessStatisInfo(nProcessIndex, statMemUsage, qwMemUsage);
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	if (hProcessHandle != INVALID_HANDLE_VALUE && hProcessHandle != NULL)
	{
		CloseHandle(hProcessHandle);
		hProcessHandle = INVALID_HANDLE_VALUE;
	}
	return nRetCode;
}

BOOL CProcessMgr::MainLoop()
{
	BOOL nRetCode = FALSE;

	UINT64 qwCurrentTick = GetTickCountEx();
	if (qwCurrentTick > m_qwLastStatisTick + 1000)//g_GuardConfig.nServerStatisInterval)
	{
		m_qwLastStatisTick = qwCurrentTick;

		UpdateServersInfo();

		if (CGDSessionMgr::GetInstance().GetMTSession().pSocketSession)
		{
			CGDMessageHandler::GetInstance().DoMTUpdateStatisInfo();
		}
		g_ResetStatisInfo();
	}

	return TRUE;
}

BOOL CProcessMgr::UpdateServersInfo()
{
	BOOL nRetCode = FALSE;
	static FILETIME ftZeroTime = { 0 };
	FILETIME ftProcessCreation = { 0 };
	FILETIME ftProcessExit = { 0 };
	FILETIME ftProcessKernelTime = {0};
	FILETIME ftProcessUserTime = {0};

#if defined(__linux__)
    char szOutput[256*16] = {0};
    char szLine[256] = { 0 };

    char* pCmd = "/bin/ps x | /bin/grep server | /bin/grep -v grep | /bin/awk '{print $1, $5}' ";

    FILE* pFile = popen( pCmd, "r" );
    if( NULL == pFile)
    {
        CRI("can't popen cmd %s", pCmd );
        return FALSE;
    }

    while( fgets( szLine, sizeof(szLine), pFile ) )
    {
        snprintf( szOutput+strlen(szOutput), sizeof(szOutput)-strlen(szOutput), "%s", szLine );
    }

    if ( pFile )
        pclose( pFile );
#endif // __linux__


    CSprocessListItr itr = m_listProcess.begin();
    while(itr != m_listProcess.end())
    {
#if defined(WIN32)
		BOOL bNeedRemoveProcess = FALSE;
		HANDLE hHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, itr->dwProcessID);	// PROCESS_QUERY_INFORMATION   //GetExitCodeProcess() == STILL_ALIVE
        if(hHandle == NULL)
        {
  			bNeedRemoveProcess = TRUE;
        }
		else
		{
			DWORD dwExitCode = STILL_ACTIVE;
			nRetCode = GetExitCodeProcess(hHandle, &dwExitCode);
			if (dwExitCode != STILL_ACTIVE)
			{
				bNeedRemoveProcess = TRUE;

				struct in_addr addr = {0};
				addr.s_addr = itr->dwIP;

				INF("process %d@%s [%s:%d] has exit with exit code %u", itr->dwProcessID, inet_ntoa(addr),
					GetServerShortName(itr->byType), itr->bySessionID, dwExitCode);
			}
			CloseHandle(hHandle);
			hHandle = INVALID_HANDLE_VALUE;
		}

		if ( bNeedRemoveProcess )
		{
			LOG_PROCESS_ERROR(itr->byType >= stMS && itr->byType < stClient);
			INF("process %d[%s] not existed!", itr->dwProcessID, GetServerName(itr->byType) );

			BOOL nRetCode = CGDMessageHandler::GetInstance().DoMTUpdateProcess(InternalMessage::epsDestroy, itr->dwProcessID, 0, 0, FALSE);
			LOG_CHECK_ERROR(nRetCode);

			GD_ALERT_MT("process %d [%s:%d] disappeared!", itr->dwProcessID, GetServerShortName(itr->byType), itr->bySessionID );

			INF("send to MT and erase Process %d[%s] from m_listProcess", itr->dwProcessID, GetServerName(itr->byType) );
			itr = m_listProcess.erase(itr);
		}
		else
		{
			UpdateServersStatis(itr->dwProcessID);

			//// too frequently
			//LOG_PROCESS_ERROR(itr->byType >= stMS && itr->byType < stClient);
			//BOOL bConnected = CGDSessionMgr::GetInstance().CheckSocketConnected(itr->byType, itr->byNum);
			//INT32 nState = bConnected ? InternalMessage::epsNormal : InternalMessage::epsDisconnected;
			//nRetCode = CGDMessageHandler::GetInstance().DoMTUpdateProcess(nState, itr->dwProcessID, itr->byType, itr->byNum, itr->bIsAuto);
			//LOG_CHECK_ERROR(nRetCode);
			++itr;
		}

#elif defined(__linux__)
        {
            char szProcessID[32] = {0};
            snprintf( szProcessID, sizeof(szProcessID), "%d", itr->dwProcessID );
            char* pLine = strstr( szOutput, szProcessID ); // id match
            if ( pLine )
            {
                char szProcessCmd[64] = {0};
                int  nProcessID = 0;
                sscanf( pLine, "%d %s", &nProcessID, szProcessCmd );
                
				if ( strstr( szProcessCmd, GetServerName[itr->byType]) != 0 ) // and name match
                {
                    itr = m_listProcess.erase(itr);
                }
                else
                {
                    CRI("process %s have been restarted, pid %d -> pid %d", 
						GetServerName[itr->byType], itr->dwProcessID, nProcessID);
					++itr;
                }
            }
        }
#endif
    }
Exit0:
    return TRUE;
}

BOOL CProcessMgr::SetProcessInfo(UINT32 dwProcessID, UINT8 byType, UINT8 bySessionID)
{
	INT32 nRetCode = FALSE;

	LOG_PROCESS_ERROR( byType >= stMS && byType < stClient );
	switch (byType)
	{
	case stMS:
	case stDB:
	case stBS:
	case stLS:
	case stDL:
	case stGM:
	case stMM:
		LOG_CHECK_ERROR(bySessionID == 1);
		bySessionID = 1;
		break;
	case stGS:
		LOG_PROCESS_ERROR(bySessionID > 0 && bySessionID < MAX_GS_SESSION_COUNT);
		break;
	case stGT:
		LOG_PROCESS_ERROR(bySessionID > 0 && bySessionID < MAX_GT_SESSION_COUNT);
		break;
	case stMG:
		LOG_PROCESS_ERROR(bySessionID > 0 && bySessionID < MAX_MG_SESSION_COUNT);
		break;
	default:
		LOG_PROCESS_ERROR( FALSE );
		break;
	}

	for (CSprocessListItr itr = m_listProcess.begin(); itr != m_listProcess.end(); ++itr)
	{
		if ( itr->dwProcessID == dwProcessID )
		{
			itr->byType = byType;
			itr->bySessionID = bySessionID;

			break;
		}
	}


	return TRUE;
Exit0:
	return FALSE;
}

BOOL CProcessMgr::SyncProcessInfo(UINT32 nState, UINT32 dwProcessID)
{
	INT32 nRetCode = FALSE;

	for (CSprocessListItr itr = m_listProcess.begin(); itr != m_listProcess.end(); ++itr)
	{
		if (itr->dwProcessID == dwProcessID)
		{
			nRetCode = CGDMessageHandler::GetInstance().DoMTUpdateProcess(nState, itr->dwProcessID,
				itr->byType, itr->bySessionID, itr->bAuto);
			LOG_CHECK_ERROR(nRetCode);

			break;
		}
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CProcessMgr::SyncAllProcessInfo()
{
	INT32 nRetCode = FALSE;

	for (CProcessMgr::CSprocessListItr itr = m_listProcess.begin(); itr != m_listProcess.end(); ++itr)
	{
		LOG_PROCESS_ERROR(itr->byType >= stMS && itr->byType < stClient);

		BOOL bConnected = FALSE;
		if (itr->bySessionID > 0 )
		{
			bConnected = CGDSessionMgr::GetInstance().CheckSocketConnected(itr->byType, itr->bySessionID);
		}
		INT32 nState = bConnected ? InternalMessage::epsNormal : InternalMessage::epsUnonnect;

		nRetCode = CGDMessageHandler::GetInstance().DoMTUpdateProcess(nState, itr->dwProcessID,
			itr->byType, itr->bySessionID, itr->bAuto);
		LOG_CHECK_ERROR(nRetCode);
	}

	return TRUE;
Exit0:
	return FALSE;
}


BOOL CProcessMgr::AddProcessInfo(UINT8 byType, UINT32 dwProcessID, UINT32 dwIP, BOOL bAuto)
{
    INT32 nRetCode = 0;
    SProcessInfo stProcess;
    
    stProcess.byType = byType;
	stProcess.dwProcessID = dwProcessID;
	stProcess.ftProcessCreationTime = { 0 };
    stProcess.dwIP = dwIP;
	stProcess.bAuto = bAuto;
    m_listProcess.push_back(stProcess);

    return TRUE;
Exit0:
    return FALSE;
}




