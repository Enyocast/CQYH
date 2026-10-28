#include "stdafx.h"
#include "cmd_mgr.h"

#include "gd_message_handler.h"
#include "process_mgr.h"
#include "guardserver.h"
#include "gd_session_mgr.h"
#include "time_ex.h"

//m_CMDFuncList[] =
//{
//    { "quit",        &CCmdMgr::QuitQuard,       "quit the guard"}, 
//    { "start",       &CCmdMgr::StartServer,     "start the server"}, 
//    { "stop",        &CCmdMgr::StopServer,      "stop the server group"},
//    { "close",       &CCmdMgr::CloseServer,     "kill the server process"},
//    { "help" ,       &CCmdMgr::CmdHelp,         "cmd: start close."\
//                                      "param: -a(all server) -m(manageserver) -t(gateserver)" \ 
//                                      "-g(gameserver) -d(dbserver) -l(loginserver) -b(bsserver);" \
//                                      "-p(primary)"\
//                                      "cmd: stop"}
//};
const char* g_CmdDescribe = "guard cmd list:\n"\
                            "start [-a -m -t -g -d -l -b -o -q -p -c -r]\n" \
                            "stop [-f]\n" \
                            "close [-a -m -t -g -d -l -b -o -q]\n" \
							"check"	\
                            "quit\n\n";

CCmdMgr CCmdMgr::ms_Instance;

CCmdMgr::CCmdMgr()
{
    memset(m_CmdFuncList, 0, sizeof(m_CmdFuncList));
    m_szCmdParam[0] = 0;
    m_szCmdProc = NULL;
    m_bNeedPrintCmdDes = FALSE;
}

CCmdMgr::~CCmdMgr()
{
    UnInit();
}

CCmdMgr& CCmdMgr::GetInstance(void)
{
    return ms_Instance;
}

BOOL CCmdMgr::Init()
{
    memset(m_szCmdParam, 0, sizeof(m_szCmdParam));
    memset(m_CmdFuncList, 0, sizeof(m_CmdFuncList));
    
    strxcpy(m_CmdFuncList[0].szCommandName, "quit", 32);
    m_CmdFuncList[0].pProc = &CCmdMgr::QuitGuard;

    strxcpy(m_CmdFuncList[1].szCommandName, "start", 32);
    m_CmdFuncList[1].pProc = &CCmdMgr::StartServer;

    strxcpy(m_CmdFuncList[2].szCommandName, "stop", 32);
    m_CmdFuncList[2].pProc = &CCmdMgr::StopServer;

    strxcpy(m_CmdFuncList[3].szCommandName, "close", 32);
    m_CmdFuncList[3].pProc = &CCmdMgr::CloseServer;

	strxcpy(m_CmdFuncList[4].szCommandName, "check", 32);
    m_CmdFuncList[4].pProc = &CCmdMgr::CheckServerConfig;
    
    strxcpy(m_CmdFuncList[5].szCommandName, "reload", 32);
    m_CmdFuncList[5].pProc = &CCmdMgr::ReloadServerConfig;

    m_bNeedPrintCmdDes = FALSE;

    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_INSERT_MODE | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);

    return TRUE;
}

BOOL CCmdMgr::UnInit(void)
{
    memset(m_szCmdParam, 0, sizeof(m_szCmdParam));

    return TRUE;
}

BOOL CCmdMgr::QuitGuard(INT32 nCount, const char* pcszParam)
{
    INT32 nRetCode = 0;
    
    nRetCode = CGuardServer::GetInstance().Close();
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCmdMgr::StartServer(INT32 nCount, const char* pcszParam)
{
	INT32 nRetCode = 0;
	BOOL bRunRelease = FALSE;	// Start the debug version by default; -r starts the release version
	if (nCount == 0)
	{
        nRetCode = CProcessMgr::GetInstance().StartAllProcess(NULL, FALSE, bRunRelease);
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {
        char pStartParam[128] = {0};
        BOOL bView = FALSE;
        for(INT32 i = 0; i < nCount; ++i)
		{
			if (pcszParam[i] == ' ' || pcszParam[i] == '-')
			{
				continue;
			}
			
            if(pcszParam[i] == 'p')
            {
                bView = TRUE;
            }
            //else if(pcszParam[i] == 'c')
            //{
            //    strxcat(pStartParam, "config global_config_pftest.lua", sizeof(pStartParam));
            //}
            else if(pcszParam[i] == 'c')
            {
                strxcat(pStartParam, "config global_config_final.lua", sizeof(pStartParam));
            }
            else if(pcszParam[i] == 'r')
            {
                bRunRelease = TRUE;
            }
        }

        for(INT32 i = 0; i < nCount; ++i)
        {
            switch(pcszParam[i])
            {
            case 'a':
            case 'A':
                {
                    nRetCode = CProcessMgr::GetInstance().StartAllProcess(pStartParam, bView, bRunRelease);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'm':
            case 'M':
                {
                    nRetCode = CProcessMgr::GetInstance().StartProcess(stMS, pStartParam, bView, bRunRelease);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 't':
            case 'T':
                {
                    nRetCode = CProcessMgr::GetInstance().StartProcess(stGT, pStartParam, bView, bRunRelease);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'g':
            case 'G':
                {
                    nRetCode = CProcessMgr::GetInstance().StartProcess(stGS, pStartParam, bView, bRunRelease);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'd':
            case 'D':
                {
                    nRetCode = CProcessMgr::GetInstance().StartProcess(stDB, pStartParam, bView, bRunRelease);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'l':
            case 'L':
                {
                    nRetCode = CProcessMgr::GetInstance().StartProcess(stLS, pStartParam, bView, bRunRelease);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'b':
            case 'B':
                {
                    nRetCode = CProcessMgr::GetInstance().StartProcess(stBS, pStartParam, bView, bRunRelease);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
			case 'o':
			case 'O':
				{
					nRetCode = CProcessMgr::GetInstance().StartProcess(stDL, pStartParam, bView, bRunRelease);
					LOG_PROCESS_ERROR(nRetCode);
				}
				break;
			case 'q':
			case 'Q':
			{
				nRetCode = CProcessMgr::GetInstance().StartProcess(stGM, pStartParam, bView, bRunRelease);
				LOG_PROCESS_ERROR(nRetCode);
			}
				break;
            default:
                break;
            }
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCmdMgr::StopServer(INT32 nCount, const char* pcszParam)
{
    INT32 nRetCode = 0;

    BOOL bMSRuning = CProcessMgr::GetInstance().CountRuningProcessByType(stMS);
    UINT64 qwCurrentTick = GetTickCountEx();
    while(bMSRuning)
    {
        nRetCode = CGuardServer::GetInstance().MainLoop();
        LOG_PROCESS_ERROR(nRetCode);

        if(CGDSessionMgr::GetInstance().GetMSSession().pSocketSession)
        {
            nRetCode = CGDMessageHandler::GetInstance().DoMSClose();
            LOG_CHECK_ERROR(nRetCode);
        }
		else
		{
			LOG_CHECK_ERROR(FALSE);
			break;
		}

        Sleep(1);
        bMSRuning = CProcessMgr::GetInstance().CountRuningProcessByType(stMS);

        if (GetTickCountEx() - qwCurrentTick > 10 * 1000)
        {
            CRI("stop ms failed after waiting 10s, now no wait");
			LOG_PROCESS_ERROR(FALSE);
            break;
        }
    }

    //if(nCount == 1 && pcszParam[0] == 'f' && bMSRuning)
    //{
    //    nRetCode = CProcessMgr::GetInstance().CloseAllProcess();
    //    LOG_PROCESS_ERROR(nRetCode);
    //    INF("killed all process");
    //}

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCmdMgr::CloseServer(INT32 nCount, const char* pcszParam)
{
    INT32 nRetCode = 0;
    if(nCount == 0)
    {
        nRetCode = CProcessMgr::GetInstance().CloseAllProcess();
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {
        for(INT32 i = 0; i < nCount; ++i)
        {
            switch(pcszParam[i])
            {
            case 'a':
            case 'A':
                {
                    nRetCode = CProcessMgr::GetInstance().CloseAllProcess();
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'm':
            case 'M':
                {
                    nRetCode = CProcessMgr::GetInstance().CloseProcess(stMS);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 't':
            case 'T':
                {
                    nRetCode = CProcessMgr::GetInstance().CloseProcess(stGT);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'g':
            case 'G':
                {
                    nRetCode = CProcessMgr::GetInstance().CloseProcess(stGS);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'd':
            case 'D':
                {
                    nRetCode = CProcessMgr::GetInstance().CloseProcess(stDB);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'l':
            case 'L':
                {
                    nRetCode = CProcessMgr::GetInstance().CloseProcess(stLS);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
            case 'b':
            case 'B':
                {
                    nRetCode = CProcessMgr::GetInstance().CloseProcess(stBS);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                break;
			case 'o':
			case 'O':
				{
					nRetCode = CProcessMgr::GetInstance().CloseProcess(stDL);
					LOG_PROCESS_ERROR(nRetCode);
				}
				break;
			case 'q':
			case 'Q':
			{
				nRetCode = CProcessMgr::GetInstance().CloseProcess(stGM);
				LOG_PROCESS_ERROR(nRetCode);
			}
				break;
            default:
                break;
            }
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCmdMgr::CheckServerConfig(INT32 nCount, const char* pcszParam)
{
	INT32 nRetCode = 0;
	char pStartParam[64] = {0};
	BOOL bView = FALSE;
	snprintf(pStartParam, 64, "%s", "check");

	nRetCode = CProcessMgr::GetInstance().StartProcess(stGS, pStartParam, bView);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CCmdMgr::ReloadServerConfig(INT32 nCount, const char* pcszParam)
{
    INT32 nRetCode = 0;
    char szGmCommand[256] = {0};
    BOOL bView = FALSE;
    snprintf(szGmCommand, sizeof(szGmCommand), ".reload %s", pcszParam);

    BOOL bMSRuning = CProcessMgr::GetInstance().CountRuningProcessByType(stMS);
    LOG_PROCESS_ERROR( bMSRuning );

    nRetCode = CGDMessageHandler::GetInstance().DoMSCommand(szGmCommand);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CCmdMgr::ParseCmd(const char* szFullCmd)
{
    INT32 nRetCode = 0;
    INT32 nIndex = 0;
  
	m_szCmdParam[0] = '\0';
	m_szParamCount = 0;

	LOG_PROCESS_ERROR(szFullCmd);
	LOG_PROCESS_ERROR(szFullCmd[0] != '.');

	{
		char* pCmd = NULL;
		char* pNextToken = NULL;

		pCmd = strtok_s((char*)szFullCmd, " ", &pNextToken);
		if (pCmd)
		{
			for (INT32 i = 0; i < MAX_GUARD_CMD_COUNT; ++i)
			{
				if (strnicmp(m_CmdFuncList[i].szCommandName, pCmd, strlen(m_CmdFuncList[i].szCommandName)) == 0)
				{
					m_szCmdProc = m_CmdFuncList[i].pProc;
					break;
				}
			}
		}

		if (pNextToken)
		{
			strxcpy(m_szCmdParam, pNextToken, sizeof(m_szCmdParam));
			m_szParamCount = strlen(m_szCmdParam);
		}
	}

	return TRUE;
Exit0:
	return FALSE;
}

INT32 CCmdMgr::ExecGMCmd(const char* szFullCmd)
{
    INT32 nRetCode = 0;
	LOG_PROCESS_ERROR(szFullCmd);
	LOG_PROCESS_ERROR(szFullCmd[0] == '.' );

	BOOL bMSRuning = CProcessMgr::GetInstance().CountRuningProcessByType(stMS);
	LOG_PROCESS_ERROR(bMSRuning);

	nRetCode = CGDMessageHandler::GetInstance().DoMSCommand(szFullCmd);
	LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

INT32 CCmdMgr::ExecOPCmd(const char* szFullCmd)
{
	INT32 nRetCode = 0;
	m_bNeedPrintCmdDes = FALSE;
	LOG_PROCESS_ERROR(szFullCmd);

	nRetCode = ParseCmd(szFullCmd);// set m_szCmdProc
	LOG_PROCESS_ERROR(nRetCode);

	LOG_PROCESS_ERROR(m_szCmdProc != NULL);
	nRetCode = (this->*m_szCmdProc)(m_szParamCount, m_szCmdParam);
	LOG_PROCESS_ERROR(nRetCode);

	m_szCmdProc = NULL;
	m_szParamCount = 0;

	return TRUE;
Exit0:
	m_bNeedPrintCmdDes = TRUE;
	m_szCmdProc = NULL;
	m_szParamCount = 0;

	return FALSE;
}

BOOL CCmdMgr::PrintCmdDescribe()
{
    if(m_bNeedPrintCmdDes)
        printf("\r%s", g_CmdDescribe);
    
    return TRUE;
}

