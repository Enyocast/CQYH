#include "stdafx.h"

#include "version.h"
#include "dump.h"
#include "time_ex.h"
#include "report.h"
#include "statis_info.h"
#include "net.h"

#include "global_config.h"	//LoadGuardConfig
#include "guard_config.h"

#include "gd_session_mgr.h"
#include "process_mgr.h"
#include "cmd_mgr.h"
#include "process_option.h"
#include "maintain_tool_version.h"

#include "guardserver.h"

BOOL InstallService();
BOOL UninstallService();
void WINAPI ServiceMain();
void WINAPI ServiceCtrlHandler(DWORD dwOpcode);
char g_szServiceName[] = "guard_cqyh";
SERVICE_STATUS_HANDLE g_hServiceStatus;
SERVICE_STATUS g_status;
BOOL g_bStartFromCmd = FALSE;

void InitServiceState()
{
    g_hServiceStatus = NULL;
    g_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_status.dwCurrentState = SERVICE_STOPPED;
    g_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    g_status.dwWin32ExitCode = 0;
    g_status.dwServiceSpecificExitCode = 0;
    g_status.dwCheckPoint = 0;
    g_status.dwWaitHint = 0;
}

BOOL InstallService(void)
{
    INT32 nRetCode = 0;
    SC_HANDLE hSCM = NULL;
    SC_HANDLE hService = NULL;
	char szFilePath[MAX_PATH] = {0};

    nRetCode = GetModuleFileName(NULL, szFilePath, MAX_PATH);
	LOG_PROCESS_ERROR(nRetCode);

    hSCM = OpenSCManager(
		NULL,					// local computer
		NULL,					// ServicesActive database 
		SC_MANAGER_ALL_ACCESS);	// full access rights 
    LOG_PROCESS_ERROR(hSCM);

    hService = CreateService(
		hSCM,						// SCM database 
		g_szServiceName,			// name of service 
		g_szServiceName,			// service name to display
        SERVICE_ALL_ACCESS,			// desired access
		SERVICE_WIN32_OWN_PROCESS,	// service type //    | SERVICE_INTERACTIVE_PROCESS
        SERVICE_AUTO_START,			// start type
		SERVICE_ERROR_NORMAL,		// error control type
        szFilePath,					// path to service's binary
		NULL,						// no load ordering group
		NULL,						// no tag identifier
		"",							// no dependencies
		NULL,						// LocalSystem account
		NULL);						// no password
    LOG_PROCESS_ERROR(hService);

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    return TRUE;
Exit0:
    if (hService)
        CloseServiceHandle(hService);
    if (hSCM)
        CloseServiceHandle(hSCM);
    return FALSE;
}

BOOL UninstallService()
{
    INT32 nRetCode = 0;
    SC_HANDLE hSCM = NULL;
    SC_HANDLE hService = NULL;

    hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    LOG_PROCESS_ERROR(hSCM);

    hService = OpenService(hSCM, g_szServiceName, SERVICE_STOP | DELETE);
    LOG_PROCESS_ERROR(hService);

    nRetCode = ControlService(hService, SERVICE_CONTROL_STOP, &g_status);
	//LOG_CHECK_ERROR(nRetCode);

    nRetCode = DeleteService(hService);
    LOG_PROCESS_ERROR(nRetCode);

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    return TRUE;
Exit0:
    if (hService)
        CloseServiceHandle(hService);
    if (hSCM)
        CloseServiceHandle(hSCM);

    return FALSE;
}

void WINAPI ServiceCtrlHandler(DWORD dwCtrl)
{
    switch (dwCtrl)
    {
    case SERVICE_CONTROL_STOP:
		CGuardServer::GetInstance().Close();
        break;
    default:
        break;
    }
}


BOOL _InitServer(void)
{
	INT32 nRetCode = 0;
	CGDMessageHandler& rMessageHandler = CGDMessageHandler::GetInstance();

	CGuardServer& rGuardServer = CGuardServer::GetInstance();

	nRetCode = CLog::GetInstance().Init("guard_server",
		g_GuardConfig.Log.nLogLevelMask,
		g_GuardConfig.Log.nLogOutputMask,
		g_GuardConfig.Log.bEnableLogThread,
		g_GuardConfig.Log.bPrintThreadID,
		g_GuardConfig.Log.bFlushFile);
	LOG_PROCESS_ERROR(nRetCode);
	g_InitReportSetting("GD", 1, g_GuardConfig.szReportAbsolutePath);

	INF("initializing guard server msg %d ver %s", MAINTAIN_TOOLS_MSG_VERSION, MAINTAIN_TOOLS_BUILD_VERSION);

	nRetCode = rGuardServer.Init(&rMessageHandler);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CGDSessionMgr::GetInstance().Init(rGuardServer.GetNetInterface());
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = rMessageHandler.Init(rGuardServer.GetNetInterface(), rGuardServer.GetPacketAllocator());
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CProcessMgr::GetInstance().Init();
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CCmdMgr::GetInstance().Init();
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL _UnInitServer(void)
{
	INT32 nRetCode = 0;

	nRetCode = CCmdMgr::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CProcessMgr::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CGDMessageHandler::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CGDSessionMgr::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CGuardServer::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CLog::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return TRUE;
}

//BOOL _PreRunServer(LPSTR lpCmdLine)
BOOL _PreRunServer(INT32 argc, TCHAR** argv)
{
	INT32 nRetCode = 0;
	INT32 nCmdStartIndex = 1;
	char szDumpFolder[COMMON_NAME_LEN] = {0};
	UINT64 qwCurrentTick = GetTickCountEx();

	/************************************************************************/
	// initialize
	nRetCode = CGuardServer::GetInstance().ReloadConfig();
	LOG_PROCESS_ERROR(nRetCode);

#if defined(WIN32)
	snprintf(szDumpFolder, sizeof(szDumpFolder), "%s\\log",g_GuardConfig.szServerRunPath);
	nRetCode = StartDumpThread(NULL, TRUE, szDumpFolder);
	LOG_PROCESS_ERROR(nRetCode);

	char szTitle[MAX_PATH];
	snprintf(szTitle, MAX_PATH, "guard msg %d ver %s", MAINTAIN_TOOLS_MSG_VERSION, MAINTAIN_TOOLS_BUILD_VERSION);
	SetConsoleTitle(szTitle);
#endif    

	if (!g_bStartFromCmd) // start from SCM
	{
		g_GuardConfig.Log.nLogOutputMask = lotFile;// as a service
	}

	nRetCode = g_InitStatisInfo(GetCurrentProcessId());
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = _InitServer();
	LOG_PROCESS_ERROR(nRetCode);

	// process options
	if (argc > 1)
	{
		nCmdStartIndex = ProcessOption(argc, argv);
		LOG_PROCESS_ERROR(nCmdStartIndex >= 1);
		if (argc > nCmdStartIndex)
		{
			char szCmd[COMMON_NAME_LEN] = { 0 };
			for (INT32 i = nCmdStartIndex; i < argc; ++i)
			{
				strxcat(szCmd, argv[i], sizeof(szCmd));
				strxcat(szCmd, " ", sizeof(szCmd));
			}
			nRetCode = CCmdMgr::GetInstance().ExecOPCmd(szCmd);
			LOG_CHECK_ERROR(nRetCode);
		}
	}

	//nRetCode = CCmdMgr::GetInstance().ExecOPCmd(lpCmdLine);
	//LOG_CHECK_ERROR(nRetCode);

	INF("Guard PreRunServer success!");
	return TRUE;
Exit0:
	INF("Guard PreRunServer failed!");

	nRetCode = _UnInitServer();
	LOG_CHECK_ERROR(nRetCode);

#if defined(WIN32)
	StopDumpThread();
#endif

	return FALSE;
}

INT32 _RunServer()
{
	INT32 nRetCode = 0;
	UINT64 qwCurrentTick = GetTickCountEx();

	/************************************************************************/
	// main loop
	while (CGuardServer::GetInstance().IsRuning())
	{
		nRetCode = CGuardServer::GetInstance().MainLoop();
		LOG_PROCESS_ERROR(nRetCode);

		Sleep(1);
	}

	CGDSessionMgr::GetInstance().CloseAllSocketSession();
	while (CGDSessionMgr::GetInstance().CheckHasSocketSession())
	{
		nRetCode = CGuardServer::GetInstance().MainLoop();
		LOG_PROCESS_ERROR(nRetCode);

		Sleep(1);
	}
	/************************************************************************/
	// exit
	INF("Guard is exiting");
Exit0:
	INF("Guard has exited");

	nRetCode = _UnInitServer();
	LOG_CHECK_ERROR(nRetCode);

#if defined(WIN32)
	StopDumpThread();
#endif

	return nRetCode;
}

void WINAPI ServiceMain()
{
	INT32 nRetCode = 0;

	char szFilePath[MAX_PATH] = { 0 };
	char *pChar = NULL;

	// 1 get right directory
	nRetCode = GetModuleFileName(NULL, szFilePath, MAX_PATH);
	LOG_PROCESS_ERROR(nRetCode);

	pChar = strrchr(szFilePath, '\\');
	LOG_PROCESS_ERROR(pChar);
	*(pChar + 1) = '\0';

	nRetCode = SetCurrentDirectory(szFilePath);
	LOG_PROCESS_ERROR(nRetCode);

	//nRetCode = CLog::GetInstance().Init("guard_server",
	//	lotFile, lltAll, FALSE, FALSE, TRUE);
	//LOG_PROCESS_ERROR(nRetCode);

	// 2 start pending
    g_hServiceStatus = RegisterServiceCtrlHandler(g_szServiceName, ServiceCtrlHandler);
    LOG_PROCESS_ERROR(g_hServiceStatus);

	g_status.dwCurrentState = SERVICE_START_PENDING;
	g_status.dwWaitHint = 3000;
    g_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;//这个要使用，否则你不能控制
    SetServiceStatus(g_hServiceStatus, &g_status);

	nRetCode = _PreRunServer(0, NULL);
	LOG_PROCESS_ERROR(nRetCode);

	// 3 run server
    g_status.dwWin32ExitCode = S_OK;
    g_status.dwCheckPoint = 0;
    g_status.dwWaitHint = 0;
    g_status.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(g_hServiceStatus, &g_status);

	nRetCode = _RunServer();
	LOG_PROCESS_ERROR( nRetCode );

Exit0:
    g_status.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(g_hServiceStatus, &g_status);

    INF("GD exited as a Service");

    return;
}


//int APIENTRY WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR     lpCmdLine,
//	int       nCmdShow)
INT32 main(INT32 argc, TCHAR** argv)
{
	BOOL nRetCode = FALSE;
	const char* CONSOLE_CMD_TAG = "console";

	InitServiceState();

	//if (strlen(lpCmdLine) > 0)
	if ( argc > 1 )// start from cmd
	{
		//if (stricmp(lpCmdLine, "/install") == 0)
		if (stricmp(argv[1], "/install") == 0)
		{
			InstallService();
		}
		//else if (stricmp(lpCmdLine, "/uninstall") == 0)
		else if (stricmp(argv[1], "/uninstall") == 0)
		{
			UninstallService();
		}
		else
		{
			g_bStartFromCmd = TRUE;

			//nRetCode = _PreRunServer(lpCmdLine);
			nRetCode = _PreRunServer(argc, argv);
			LOG_PROCESS_ERROR(nRetCode);

			nRetCode = _RunServer();
			LOG_PROCESS_ERROR(nRetCode);
		}
	}
	else // start from SCM
	{
		SERVICE_TABLE_ENTRY st[] =
		{
			{ g_szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
			{ NULL, NULL }
		};

		StartServiceCtrlDispatcher(st);
	}
Exit0:
    return nRetCode;
}
