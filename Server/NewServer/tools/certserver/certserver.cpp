#include "stdafx.h"

#include <math.h>
#include "math_ex.h"
#include "packet_allocator.h"
#include "cert_message_handler.h"

CPacketAllocator        g_PacketAllocator;
INet*                   g_pNet;

BOOL Install();
BOOL Uninstall();
void WINAPI ServiceMain();
void WINAPI ServiceCtrlHandler(DWORD dwOpcode);
char g_szServiceName[] = "certification server";
BOOL g_bStop = FALSE;
SERVICE_STATUS_HANDLE g_hServiceStatus;
SERVICE_STATUS g_status;

static const INT32 s_nAdjacentX[DT_DIRECTION_8_COUNT] =
{
	1,		//	DT_EAST,
	1,		//	DT_SOUTH_EAST,
	0,		//  DT_SOUTH,
	-1,		//  DT_SOUTH_WEST,
	-1,		//  DT_WEST,
	-1,		//  DT_NORTH_WEST,
	0,		//  DT_NORTH,
	1		//  DT_NORTH_EAST,
};

static const INT32 s_nAdjacentY[DT_DIRECTION_8_COUNT] =
{
	0,		//	DT_EAST,
	1,		//	DT_SOUTH_EAST,
	1,		//  DT_SOUTH,
	1,		//  DT_SOUTH_WEST,
	0,		//  DT_WEST,
	-1,		//  DT_NORTH_WEST,
	-1,		//  DT_NORTH,
	-1		//  DT_NORTH_EAST,
};

static const INT32 s_nAdjList[DT_DIRECTION_8_COUNT][6] =
{
	{ 3, DT_NORTH_EAST, DT_EAST, DT_SOUTH_EAST },							// DT_EAST,
	{ 5, DT_NORTH_EAST, DT_EAST, DT_SOUTH_EAST, DT_SOUTH, DT_SOUTH_WEST },	// DT_SOUTH_EAST,
	{ 3, DT_SOUTH_EAST, DT_SOUTH, DT_SOUTH_WEST },							// DT_SOUTH,
	{ 5, DT_SOUTH_EAST, DT_SOUTH, DT_SOUTH_WEST, DT_WEST, DT_NORTH_WEST },	// DT_SOUTH_WEST,
	{ 3, DT_SOUTH_WEST, DT_WEST, DT_NORTH_WEST },							// DT_WEST,
	{ 5, DT_SOUTH_WEST, DT_WEST, DT_NORTH_WEST, DT_NORTH, DT_NORTH_EAST },	// DT_NORTH_WEST,
	{ 3, DT_NORTH_WEST, DT_NORTH, DT_NORTH_EAST },							// DT_NORTH,
	{ 5, DT_NORTH_WEST, DT_NORTH, DT_NORTH_EAST, DT_EAST, DT_SOUTH_EAST },	// DT_NORTH_EAST,
};

void Init()
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

BOOL Install(void)
{
    INT32 nRetCode = 0;
    SC_HANDLE hSCM = NULL;
    SC_HANDLE hService = NULL;
    char szFilePath[MAX_PATH];

    nRetCode = GetModuleFileName(NULL, szFilePath, MAX_PATH);
    LOG_PROCESS_ERROR(nRetCode);

    hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    LOG_PROCESS_ERROR(hSCM);

    hService = CreateService(hSCM, g_szServiceName, g_szServiceName,
        SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
        szFilePath, NULL, NULL, "", NULL, NULL);
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

BOOL Uninstall()
{
    INT32 nRetCode = 0;
    SC_HANDLE hSCM = NULL;
    SC_HANDLE hService = NULL;

    hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    LOG_PROCESS_ERROR(hSCM);

    hService = OpenService(hSCM, g_szServiceName, SERVICE_STOP | DELETE);
    LOG_PROCESS_ERROR(hService);

    nRetCode = ControlService(hService, SERVICE_CONTROL_STOP, &g_status);
    LOG_PROCESS_ERROR(nRetCode);

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

void init_math_table(void)
{
    memset(&g_MathTable, 0, sizeof(g_MathTable));

    for (int nDirection = 0; nDirection < MAX_DIRECTION_COUNT; nDirection++)
    {
        g_MathTable.nSinTable[nDirection] = (INT32)floor(sin((double)nDirection * 2 * PI / MAX_DIRECTION_COUNT) * SIN_COS_NUMBER + 0.5f);
        g_MathTable.nCosTable[nDirection] = (INT32)floor(cos((double)nDirection * 2 * PI / MAX_DIRECTION_COUNT) * SIN_COS_NUMBER + 0.5f);
    }

    for (int nDirection = 0; nDirection < MAX_DIRECTION_COUNT/4; nDirection++)
    {
        g_MathTable.nSinSquareTable[nDirection] = g_MathTable.nSinTable[nDirection] * g_MathTable.nSinTable[nDirection];
    }

    for(int i = 0; i < MAX_SQUARE; i++)
    {
        g_MathTable.wSqrtTable[i] = (UINT16)floor(sqrt((double)i) + 0.5f);
    }

	memcpy(g_MathTable.nAdjacentX, s_nAdjacentX, sizeof(g_MathTable.nAdjacentX));
	memcpy(g_MathTable.nAdjacentY, s_nAdjacentY, sizeof(g_MathTable.nAdjacentY));
	memcpy(g_MathTable.nAdjList, s_nAdjList, sizeof(g_MathTable.nAdjList));
}

void WINAPI ServiceCtrlHandler(DWORD dwCtrl)
{
    switch (dwCtrl)
    {
    case SERVICE_CONTROL_STOP:
        g_bStop = TRUE;
        break;
    default:
        break;
    }
}

void WINAPI ServiceMain()
{
    INT32 nRetCode = 0;
    SIMPLE_INIT_PARAM SimpleInitParam;
    ISocketAcceptor* pAcceptor = NULL;

    nRetCode = CLog::GetInstance().Init("cert_server", 
        lotAll, lltAll, FALSE, FALSE, TRUE);
    LOG_PROCESS_ERROR(nRetCode);

    g_hServiceStatus = RegisterServiceCtrlHandler(g_szServiceName, ServiceCtrlHandler);
    LOG_PROCESS_ERROR(g_hServiceStatus);

    g_status.dwCurrentState = SERVICE_START_PENDING;
    g_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;//这个要使用，否则你不能控制

    SetServiceStatus(g_hServiceStatus, &g_status);

    g_status.dwWin32ExitCode = S_OK;
    g_status.dwCheckPoint = 0;
    g_status.dwWaitHint = 0;
    g_status.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(g_hServiceStatus, &g_status);

    init_math_table();

    nRetCode = g_PacketAllocator.Init(1024, 256);
    LOG_PROCESS_ERROR(nRetCode);

    SimpleInitParam.nMaxAcceptor = 1;
    SimpleInitParam.nMaxConnector = 1;
    SimpleInitParam.nMaxSessionCount = 32;
    SimpleInitParam.nSendBufSize = 1024 * 1024 * 1;
    SimpleInitParam.nRecvBufSize = 1024 * 1024 * 1;
    SimpleInitParam.nPacketBufferSize = 4;

    g_pNet = g_CreateNetInterface(netSimple, &g_PacketAllocator, &g_MessageHandler, &SimpleInitParam);
    LOG_PROCESS_ERROR(g_pNet);

    nRetCode = g_MessageHandler.Init(g_pNet, &g_PacketAllocator);
    LOG_PROCESS_ERROR(nRetCode);

    pAcceptor = g_pNet->CreateAcceptor();
    LOG_PROCESS_ERROR(pAcceptor);

    nRetCode = pAcceptor->Open(0, 8111);
    LOG_PROCESS_ERROR(nRetCode);

    INF("opened CS listen port at 0.0.0.0:8111");
    INF("CS initialized successfully");

    while (!g_bStop)
    {
        g_pNet->MainLoop();
        Sleep(1);
    }

Exit0:
    g_status.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(g_hServiceStatus, &g_status);

    INF("CS exited");

    CLog::GetInstance().UnInit();

    return;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    Init();

    SERVICE_TABLE_ENTRY st[] =
    {
        { g_szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
        { NULL, NULL }
    };

    if (stricmp(lpCmdLine, "/install") == 0)
    {
        Install();
    }
    else if (stricmp(lpCmdLine, "/uninstall") == 0)
    {
        Uninstall();
    }
    else
    {
        StartServiceCtrlDispatcher(st);
    }

    return 0;
}
