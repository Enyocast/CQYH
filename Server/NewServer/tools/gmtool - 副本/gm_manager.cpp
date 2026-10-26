/********************************************************************
	created:	5:8:2013   15:54
	file:		gm_manager.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#include "stdafx.h"
#include "gm_manager.h"
#include "log.h"
#include "tl_config.h"
#include "session_mgr.h"
#include "message_handler.h"
#include "string_ex.h"

//#include <QtGui/QApplication>
#include "gmtool.h"
#include "loader.h"

#include "cmd_manager.h"
#include "time_ex.h"
#include "global_config.h"
//#include "game_world.h"
#include "server_list.h"

#include "zlib.h"
#include "../gmtool-encrypt/encrypt/encrypt/base.h"
#include "data_mgr.h"


using namespace std;


BOOL IsRoleDataEqual(ROLE_DATA &data1, ROLE_DATA &data2)
{
    return data1.nSvrID == data2.nSvrID;
}




BOOL g_InitServerList()
{
    INT32       nRetCode = 0;
    BOOL        bRet = FALSE;
    char        szFinalFile[128] = { 0 };
    char        szFile[128] = { 0 };
    char        *pBuffer = NULL;
    INT32       nLength = 0;
    char        *pOBuffer = NULL;
    INT32       nOLength = 1024 * 1024;

    memset(&g_ServerList, 0, sizeof(g_ServerList));

    UINT32  dwcrc = crc32(0, (Bytef*)"gmtool_config", strlen("gmtool_config"));
    sprintf_s(szFinalFile, 128, "%u", dwcrc);

    sprintf(szFile, "./config/%s", szFinalFile);

    FILE *pf = fopen(szFile, "rb");
    LOG_PROCESS_ERROR(pf);

    pBuffer = new char[1024 * 1024];
    LOG_PROCESS_ERROR(pBuffer);

    fseek(pf, 0, SEEK_END);
    nLength = ftell(pf);
    fseek(pf, 0, SEEK_SET);
    fread(pBuffer, 1, nLength, pf);
    fclose(pf);
    pf = NULL;

#ifdef DEBUG
    nRetCode = LoadTLConfig("./config/gmtool_config.lua");
    LOG_PROCESS_ERROR(nRetCode);
#else
    pOBuffer = new char[1024 * 1024];
    LOG_PROCESS_ERROR(pOBuffer);
    memset(pOBuffer, 0, 1024 * 1024);

    bRet = Decrypt(nLength, pBuffer, nOLength, pOBuffer);
    LOG_PROCESS_ERROR(bRet);

    nRetCode = LoadTLConfigFromBuffer(szFile, pOBuffer + 3, nOLength - 3);
    LOG_PROCESS_ERROR(nRetCode);

    delete[] pBuffer;
    delete[] pOBuffer;
#endif

    //nRetCode = CDataManager<SERVER_LIST_DATA>::GetInstance().Init(szFinalFile, "./config", NULL);
    //LOG_PROCESS_ERROR(nRetCode);

    //bRet = DeleteFile(szOutName);
    //LOG_PROCESS_ERROR(bRet);

    //pData = CDataManager<SERVER_LIST_DATA>::GetInstance().GetFirstData();
    //LOG_PROCESS_ERROR(pData);
    //while (pData)
    //{
    //    g_ServerList.svrList[g_ServerList.nSvrNum].nServerID = pData->nServerID;
    //    g_ServerList.svrList[g_ServerList.nSvrNum].dwPort = pData->dwPort;
    //    strxcpy(g_ServerList.svrList[g_ServerList.nSvrNum].szName, pData->szName, sizeof(g_ServerList.svrList[g_ServerList.nSvrNum].szName));
    //    strxcpy(g_ServerList.svrList[g_ServerList.nSvrNum].szAddr, pData->szAddr, sizeof(g_ServerList.svrList[g_ServerList.nSvrNum].szAddr));
    //    ++g_ServerList.nSvrNum;

    //    pData = CDataManager<SERVER_LIST_DATA>::GetInstance().GetNextData();
    //}

    return TRUE;
Exit0:
    return FALSE;
}



CGMManager CGMManager::m_Instance;

CGMManager &CGMManager::GetInstance()
{
    return m_Instance;
}


CGMManager::CGMManager() 
{

}

CGMManager::~CGMManager()
{

}


BOOL CGMManager::Init()
{
    INT32   nRetCode = 0;

    m_LoginList.clear();
    m_ReloginList.clear();
    m_PreloginList.clear();
    m_PreExecuteList.clear();
    m_PreExecuteRoleList.clear();

    SIMPLE_INIT_PARAM SimpleInitParam;
    CMessageHandler &rMessageHandler = CMessageHandler::GetInstance();

    //nRetCode = LoadTLConfig("./config/gmtool_config.lua");
    //PROCESS_ERROR(nRetCode);

    nRetCode = CLog::GetInstance().Init("gm_tool",
        0xFFFFFFFF,
        0xFFFFFFFF,
        FALSE,
        FALSE,
        TRUE);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = g_InitServerList();
    LOG_PROCESS_ERROR(nRetCode);

    //nRetCode = LoadGlobalConfig("global_config.lua");
    //LOG_PROCESS_ERROR(nRetCode);

    //nRetCode = LoadTLConfig("server_list.lua");
    //PROCESS_ERROR(nRetCode);

    //nRetCode = _CheckGMConfig();
    //LOG_PROCESS_ERROR(nRetCode);

    nRetCode = m_PacketAllocator.Init(SMALL_PACKET_COUNT, LARGE_PACKET_COUNT);
    LOG_PROCESS_ERROR(nRetCode);

    SimpleInitParam.nMaxAcceptor = MAX_ACCEPTOR;
    SimpleInitParam.nMaxConnector = MAX_CONNECTOR;
    SimpleInitParam.nMaxSessionCount = MAX_SESSION_COUNT;
    SimpleInitParam.nSendBufSize = SEND_BUF_SIZE;
    SimpleInitParam.nRecvBufSize = RECV_BUF_SIZE;
    SimpleInitParam.nPacketBufferSize = PACKET_BUFFER_SIZE;
    m_pNet = g_CreateNetInterface(netSimple, &m_PacketAllocator, &rMessageHandler, &SimpleInitParam);
    LOG_PROCESS_ERROR(m_pNet);

    nRetCode = CSessionMgr::GetInstance().Init(m_pNet);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CMessageHandler::GetInstance().Init(m_pNet, &m_PacketAllocator);
    LOG_PROCESS_ERROR(nRetCode);

    //nRetCode = g_InitGameWorldLib(0, &m_Notifier, &m_PacketAllocator);
    //LOG_PROCESS_ERROR(nRetCode);

    // 
    nRetCode = CCmdManager::GetInstance().Init();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CDataMgr::GetInstance().Init();
    LOG_PROCESS_ERROR(nRetCode);


    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGMManager::UnInit()
{
    INT32       nRetCode = 0;

    if (m_pNet)
    {
        nRetCode = m_pNet->UnInit();
        LOG_CHECK_ERROR(nRetCode);

        nRetCode = g_DestroyNetInterface(netSimple, m_pNet);
        LOG_CHECK_ERROR(nRetCode);
        m_pNet = NULL;
    }

    nRetCode = m_PacketAllocator.UnInit();
    LOG_CHECK_ERROR(nRetCode);

    m_LoginList.clear();
    m_ReloginList.clear();
    m_PreloginList.clear();
    m_PreExecuteList.clear();
    m_PreExecuteRoleList.clear();

    nRetCode = CCmdManager::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

    nRetCode = CDataMgr::GetInstance().UnInit();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}

BOOL CGMManager::MainLoop()
{
    INT32       nRetCode = 0;
    INT32       nCondition = 0;

    nRetCode = m_pNet->MainLoop();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CSessionMgr::GetInstance().MainLoop();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = CCmdManager::GetInstance().MainLoop();
    LOG_PROCESS_ERROR(nRetCode);

Exit1:
    return TRUE;
Exit0:
    return FALSE;
}

void CGMManager::SetGMDialogState(GM_DIALOG_STATE eGMDialogState)
{
    m_eGMDialogState = eGMDialogState;
}

GM_DIALOG_STATE CGMManager::GetGMDialogState()
{
    return m_eGMDialogState;
}

const char *CGMManager::GetUserName()
{
    return m_szUserName;
}

const char *CGMManager::GetUserPwd()
{
    return m_szUserPwd;
}

void CGMManager::SetUserName(const char *pcszName)
{
    LOG_PROCESS_ERROR(pcszName);
    strxcpy(m_szUserName, pcszName, sizeof(m_szUserName));
Exit0:
    return ;
}

void CGMManager::SetUserPwd(const char *pcszPwd)
{
    LOG_PROCESS_ERROR(pcszPwd);
    strxcpy(m_szUserPwd, pcszPwd, sizeof(m_szUserPwd));

Exit0:
    return ;
}











//BOOL CGMManager::_CheckGMConfig()
//{
//    LOG_PROCESS_ERROR(g_SvrList.GMList.nSvrNum <= MAX_GM_SESSION_COUNT);
//
//    for (INT32 i = 1; i <= g_SvrList.GMList.nSvrNum; ++i)
//    {
//        LOG_PROCESS_ERROR(i == g_SvrList.GMList.arrSvrList[i].nSvrID);
//    }
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}




