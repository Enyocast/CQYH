#include "stdafx.h"
#include "sol_bindings.h"
#include "asimov.h"
#include <QtWidgets/QApplication>

#include "math_ex.h"
#include "asimov_config.h"
#include "script_mgr.h"

#include "net.h"
#include "external_message_size.h"

#include "game_world.h"
#include "robot_message_handler.h"
#include "script_mgr.h"

#include "robot_message_notifier.h"
#include "user_mgr.h"

#include "script/sol_asimov_common.h"
#include "script/sol_asimov_user.h"
#include "script/sol_asimov_user_mgr.h"
#include "script/sol_asimov_message_handler.h"
#include "script/sol_msg.h"

#include "string_ex.h"
#include "dump.h"
#include "sdo/staticlogin.h"
#include "achievement_data.h"
#include "enum_string.h"

QApplication * ASIMOV_APP = NULL;
extern LUA_FUNC g_RobotLuaScriptFuncTable[];

INet* g_pNet;
CPacketAllocator g_PacketAllocator;
CRobotMessageNotifier g_RobotMessageNotifier;

void _InitMathTable(void)
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
}

BOOL _InitAsimov(void)
{
    INT32 nRetCode = 0;
    CLuaScript* poScript = NULL;
    ASIO_INIT_PARAM AsioInitParam;

    nRetCode = CLog::GetInstance().Init("Robot", 
        g_AsimovConfig.Log.nLogLevelMask, 
        g_AsimovConfig.Log.nLogOutputMask, 
        g_AsimovConfig.Log.bEnableLogThread,
        g_AsimovConfig.Log.bPrintThreadID, 
        g_AsimovConfig.Log.bFlushFile);
    LOG_PROCESS_ERROR(nRetCode);

    CLog::GetInstance().SetCustomOutput(&asimov::LogOutput);

    _InitMathTable();
    nRetCode = InitMathEx(NULL);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_PacketAllocator.Init(g_AsimovConfig.Net.nSmallPacketCount,
        g_AsimovConfig.Net.nLargePacketCount);
    LOG_PROCESS_ERROR(nRetCode);

    AsioInitParam.nMaxSessionCount = g_AsimovConfig.nMaxSessionCount;
    AsioInitParam.nThreadCount = g_AsimovConfig.nWorkThreadCount;
    AsioInitParam.pnMessageSizeList = g_nS2CMessageSize;

	AsioInitParam.nMaxOperationPerLoop = g_AsimovConfig.Net.nMaxOperationPerLoop;
	AsioInitParam.nRecvLoopBufferSize = g_AsimovConfig.Net.nRecvLoopBufferSize;
	AsioInitParam.nSendLoopBufferSize = g_AsimovConfig.Net.nSendLoopBufferSize;

    g_pNet = g_CreateNetInterface(netAsio, &g_PacketAllocator, &CAsimovMessageHandler::GetInstance(), &AsioInitParam);
    LOG_PROCESS_ERROR(g_pNet);

    nRetCode = CAsimovMessageHandler::GetInstance().Init(g_pNet, &g_PacketAllocator);
    LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CScriptMgr::GetInstance().RegisterPackage("asimov_common.pkg", sol_asimov_common_open);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CScriptMgr::GetInstance().RegisterPackage("asimov_user.pkg", sol_asimov_user_open);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CScriptMgr::GetInstance().RegisterPackage("asimov_user_mgr.pkg", sol_asimov_user_mgr_open);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CScriptMgr::GetInstance().RegisterPackage("asimov_message_handler.pkg", sol_asimov_message_handler_open);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CScriptMgr::GetInstance().RegisterPackage("msg.pkg", sol_msg_open);
    LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CScriptMgr::GetInstance().RegisterFuncList(g_RobotLuaScriptFuncTable);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = g_InitGameWorldLib(GetTickCountEx(), &g_RobotMessageNotifier, &g_PacketAllocator);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CAchievementIndexData::GetInstance().Init();
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CEnumString::GetInstance().Init();
	LOG_PROCESS_ERROR(nRetCode);

    poScript = CScriptMgr::GetInstance().NewScript(ROBOT_SCRIPT_NAME);
    LOG_PROCESS_ERROR(poScript);

    nRetCode = CUserMgr::GetInstance().Init();
    LOG_PROCESS_ERROR(nRetCode);

	nRetCode = COAStaticLoginMgr::GetInstance().Init();
	LOG_PROCESS_ERROR(nRetCode);

    CGameWorld::GetInstance().PrintMemoryStat();

    return TRUE;
Exit0:
    return FALSE;
}

struct AsimovUnitRoleClean
{
	BOOL operator()(UINT32 dwRoleID, CRole* pRole)
	{
		INT32 nRetCode = 0;
		PROCESS_ERROR(pRole);
		
		if (pRole->GetScene())
        {
            nRetCode = pRole->GetScene()->RemoveRole(pRole);
            LOG_CHECK_ERROR(nRetCode);
        }

		nRetCode = pRole->UnInit();
		LOG_CHECK_ERROR(nRetCode);

		nRetCode = CGameWorld::GetInstance().DelRole(pRole);
		LOG_CHECK_ERROR(nRetCode);

		return TRUE;
Exit0:
		return TRUE;
	}
};

BOOL _UnInitAsimov(void)
{
    INT32 nRetCode = 0;

	//CRI("_UnInitAsimov, now CGameWorld clean up role");
	//AsimovUnitRoleClean stRoleClean;
	//nRetCode = CGameWorld::GetInstance().TraverseRole(stRoleClean);
	//LOG_CHECK_ERROR(nRetCode);

	CRI("_UnInitAsimov, now CGameWorld clean up scene");
	CGameWorld::GetInstance().CleanUpScenes();

    if (g_pNet)
    {
        nRetCode = g_DestroyNetInterface(netAsio, g_pNet);
        LOG_CHECK_ERROR(nRetCode);
        g_pNet = NULL;
    }

	nRetCode = CUserMgr::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	asimov::GetInstance().Cleanup();

	nRetCode = CEnumString::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

	nRetCode = CAchievementIndexData::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

    nRetCode = g_UnInitGameWorldLib();
    LOG_CHECK_ERROR(nRetCode);

	nRetCode = CAsimovMessageHandler::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

    nRetCode = g_PacketAllocator.UnInit();
    LOG_CHECK_ERROR(nRetCode);

    nRetCode = UnInitMathEx();
    LOG_CHECK_ERROR(nRetCode);

	nRetCode = COAStaticLoginMgr::GetInstance().UnInit();
	LOG_CHECK_ERROR(nRetCode);

    nRetCode = CLog::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}

BOOL CheckGameFrame(void)
{
    static UINT32 s_qwLastDumpTick = 0;

	return FALSE;   // won't dump

    if (g_pNet == NULL ||
        CGameWorld::GetInstance().GetGameFrame() < GAME_FPS * 60 ||
            IsDebuggerPresent())
        return FALSE;   // won't dump

    UINT64 qwCurrentTick = GetTickCountEx();
    UINT64 qwStartTick = asimov::GetInstance().GetStartTick();
	INT64 llCurrentFrame = CGameWorld::GetInstance().GetGameFrame();

    if ((qwCurrentTick - qwStartTick > (llCurrentFrame + GAME_FPS / 2) * 1000LL / GAME_FPS) && 
        (qwCurrentTick - s_qwLastDumpTick > 1000 * 60))
	{
		CRI("check game frame %I64d tick diff %I64d ", llCurrentFrame, qwCurrentTick - qwStartTick - llCurrentFrame * 1000 / GAME_FPS);
        s_qwLastDumpTick = qwCurrentTick;
        return TRUE;
    }

    return FALSE;
}

int main(int argc, char *argv[])
{
    INT32 nRetCode = 0;
	BOOL bAutoCase = FALSE;
	BOOL bSpecifyCase = FALSE;
	char szCaseName[COMMON_NAME_LEN] = {0};
    QApplication app(argc, argv);

#if defined(WIN32)
	nRetCode = StartDumpThread(CheckGameFrame, FALSE, "log");
    PROCESS_ERROR(nRetCode);
#endif

	nRetCode = g_OpenPakFolder(DEFAULT_PAK_PATH);
	if (nRetCode)
		INF("open pak folder %s successfully", DEFAULT_PAK_PATH);
	else
		INF("cannot open pak folder %s", DEFAULT_PAK_PATH);

    /************************************************************************/
    // process options
    for (INT32 nIdx=0; nIdx < argc; ++nIdx)
    {
        if (strcmp(argv[nIdx], "--runcase") == 0)
        {
            bAutoCase = TRUE;
            break;
		}
		else if (strcmp(argv[nIdx], "--casename") == 0)
		{
			LOG_PROCESS_ERROR(nIdx + 1 < argc);
			bSpecifyCase = TRUE;

			++nIdx;
			snprintf(szCaseName, sizeof(szCaseName), "%s", argv[nIdx]);

			break;
		}
    }

    ASIMOV_APP = &app;

    asimov::GetInstance().setAutoCase(bAutoCase);

    nRetCode = LoadGlobalConfig(g_szGlobalConfigFileName);
    LOG_PROCESS_ERROR(nRetCode);


    nRetCode = _InitAsimov();
    LOG_PROCESS_ERROR(nRetCode);

    asimov::GetInstance().RefreshTestCaseList();
    asimov::GetInstance().RefreshCoverageTestCaseList();
    asimov::GetInstance().RefreshPerfTestCaseList();
    asimov::GetInstance().RefreshCommandList();
    asimov::GetInstance().show();

    if (bAutoCase)
    {
        asimov::GetInstance().AutoCase();
    }

	if (bSpecifyCase)
	{
		UINT64 qwStartTime = asimov::GetInstance().GetStartTick();
		UINT64 qwGameLoop = 0;

		CLuaScript* poScript = CScriptMgr::GetInstance().FindScript(ROBOT_SCRIPT_NAME);
		LOG_PROCESS_ERROR(poScript);

		char szCommand[COMMON_NAME_LEN] = {0};
		if (szCaseName[0] == '\0')
		{
			strcpy(szCaseName, "PerfTestCase.GameLogic");
		}
		snprintf(szCommand, sizeof(szCommand), "addco(\"GameLogic\", %s);", szCaseName);

		nRetCode = poScript->LoadFromBuffer(poScript->GetScriptName(), szCommand, strlen(szCommand));
		LOG_PROCESS_ERROR(nRetCode);

		while (1)
		{
			INT32 nRetCode = 0;
			CGameWorld& rGameWorld = CGameWorld::GetInstance();
			UINT64 qwCurrentTime = GetTickCountEx();

			if ((qwCurrentTime - qwStartTime) * GAME_FPS > qwGameLoop * 1000)
			{
				rGameWorld.SetGameTime(time(NULL));
				rGameWorld.SetGameTick(qwCurrentTime);

				nRetCode = rGameWorld.MainLoop();
				LOG_CHECK_ERROR(nRetCode);

				qwGameLoop++;
			}

			CUserMgr::GetInstance().MainLoop(poScript);
			poScript->CallFunction("MainLoop", "");

			UINT64 qwEndTime = GetTickCountEx();
			if (qwEndTime - qwCurrentTime > 500)
				CRI("too slow in loop %I64d", qwEndTime - qwCurrentTime);
			else
				Sleep(1);
		}
	}

    nRetCode = app.exec();
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    nRetCode = _UnInitAsimov();
    LOG_CHECK_ERROR(nRetCode);

#if defined(WIN32)
    StopDumpThread();
#endif

    _CrtDumpMemoryLeaks();

    return 0;
}
