#include "stdafx.h"

#include "maintaintool.h"
#include <QtWidgets/QApplication>

#include "packet_allocator.h"
#include "message_handler.h"
#include "session_mgr.h"
#include "transmit_file_mgr.h"
#include "global_config.h"	//LoadMTConfig
#include "dir.h"

#include "mt_config.h"

#include <string>
//#include "sdfile.h"
//#include "sddir.h"
//using namespace SGDP;

QApplication* G_MAINTAINTOOL_APP = NULL;

INet* g_pNet;
CPacketAllocator g_PacketAllocator;

BOOL _InitMaintainTool(void)
{
	INT32 nRetCode = 0;
	CLuaScript* poScript = NULL;
	SIMPLE_INIT_PARAM stInitParam;

	nRetCode = CLog::GetInstance().Init("Maintaintool",
		g_MTConfig.nLogLevelMask,
		g_MTConfig.nLogOutputMask,
		g_MTConfig.bEnableLogThread,
		g_MTConfig.bPrintThreadID,
		g_MTConfig.bFlushFile);
	LOG_PROCESS_ERROR(nRetCode);
	INF("initializing maintain tool log");

	CLog::GetInstance().SetCustomOutput(&MaintainTool::LogOutput);

	nRetCode = g_PacketAllocator.Init(g_MTConfig.nSmallPacketCount,
		g_MTConfig.nLargePacketCount);
	LOG_PROCESS_ERROR(nRetCode);

	stInitParam.nMaxAcceptor = g_MTConfig.nMaxAcceptor;
	stInitParam.nMaxConnector = g_MTConfig.nMaxConnector;
	stInitParam.nMaxSessionCount = g_MTConfig.nMaxSessionCount;
	stInitParam.nSendBufSize = g_MTConfig.nSendBufSize;
	stInitParam.nRecvBufSize = g_MTConfig.nRecvBufSize;
	stInitParam.nPacketBufferSize = g_MTConfig.nPacketBufferSize;

	g_pNet = g_CreateNetInterface(netSimple, &g_PacketAllocator, &CMTMessageHandler::GetInstance(), &stInitParam);
	LOG_PROCESS_ERROR(g_pNet);

	nRetCode = MaintainTool::GetInstance().Init();
	LOG_PROCESS_ERROR(nRetCode);


	nRetCode = CMTMessageHandler::GetInstance().Init(g_pNet, &g_PacketAllocator);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CSessionMgr::GetInstance().Init(g_pNet);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CTransmitFileMgr::GetInstance().Reload();
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL _UnInitMaintainTool(void)
{
	INT32 nRetCode = 0;

	nRetCode = CTransmitFileMgr::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = MaintainTool::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = MaintainTool::GetInstance().Cleanup();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CSessionMgr::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	if (g_pNet)
	{
		nRetCode = g_DestroyNetInterface(netSimple, g_pNet);
		LOG_CHECK_ERROR(nRetCode);
		g_pNet = NULL;
	}

	nRetCode = CMTMessageHandler::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = g_PacketAllocator.UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CLog::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	return TRUE;
}

extern QApplication app;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow )
{
	INT32 nRetCode = 0;
	G_MAINTAINTOOL_APP = &app;

	nRetCode = LoadMTConfig("maintaintool_config.lua");
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = _InitMaintainTool();
	LOG_PROCESS_ERROR(nRetCode);
	
	MaintainTool::GetInstance().show();
	MaintainTool::GetInstance().Login();

	nRetCode = app.exec();
	LOG_PROCESS_ERROR(nRetCode);

Exit0:
	nRetCode = _UnInitMaintainTool();
	LOG_CHECK_ERROR(nRetCode);
	
	return 0;
}
