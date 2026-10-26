/********************************************************************
	created:	6:8:2013   10:55
	file:		session_mgr.cpp
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#include "stdafx.h"
#include "session_mgr.h"
#include "net.h"
#include "tl_config.h"
#include "string_ex.h"
#include "message_handler.h"
#include "server_list.h"

CSessionMgr  CSessionMgr::m_Instance;

CSessionMgr &CSessionMgr::GetInstance()
{
    return m_Instance;
}

CSessionMgr::CSessionMgr()
{

}

CSessionMgr::~CSessionMgr()
{

}


BOOL CSessionMgr::Init(INet *pNet)
{
    LOG_PROCESS_ERROR(pNet);
    LOG_PROCESS_ERROR(128 >= MAX_GM_SESSION_COUNT);

    m_pNet = pNet;
    m_dwLastPingTick = 0;

    memset(m_GMSession, 0, sizeof(m_GMSession));
    for (INT32 nIndex = 0; nIndex < MAX_GM_SESSION_COUNT; nIndex++)
    {
        m_GMSession[nIndex].dwType = stGM;
        m_GMSession[nIndex].dwSessionID = nIndex;
        m_GMSession[nIndex].nConnectState = SESSION_DISCONNECTED;
        m_GMSession[nIndex].nSvrID = g_TLConfig.ServerList.arrGMList[nIndex].nSvrID;
        strxcpy(m_GMSession[nIndex].szGMName, g_TLConfig.ServerList.arrGMList[nIndex].szName, sizeof(m_GMSession[nIndex].szGMName));
        m_GMSession[nIndex].eState = GM_SVR_STATE_NONE;
    }


    return TRUE;
Exit0:
    return FALSE;
}

BOOL CSessionMgr::UnInit()
{
    LOG_CHECK_ERROR(!CheckSession());

    m_pNet = NULL;
    m_dwLastPingTick = 0;

    memset(m_GMSession, 0, sizeof(m_GMSession));
    for (INT32 nIndex = 0; nIndex < MAX_GM_SESSION_COUNT; nIndex++)
    {
        m_GMSession[nIndex].dwType = stGM;
        m_GMSession[nIndex].dwSessionID = nIndex;
        m_GMSession[nIndex].nConnectState = SESSION_DISCONNECTED;
    }

    return TRUE;
}


//GM_SESSION *CSessionMgr::NewGMSession()
//{
//    for (UINT32 i = m_GMSessionIndex; i < MAX_GM_SESSION_COUNT + m_GMSessionIndex; ++i)
//    {
//        INT32   nIndex = i % MAX_GM_SESSION_COUNT;
//        if (0 == nIndex)
//            ++nIndex;
//
//        if (NULL == m_GMSession[nIndex].pSocketSession)
//        {
//            m_GMSessionIndex = nIndex + 1;
//            return m_GMSession + nIndex;
//        }
//    }
//    return m_GMSession;
//}
//
//void CSessionMgr::DeleteGMSession(GM_SESSION *pSession)
//{
//    LOG_PROCESS_ERROR(pSession);
//    pSession->pSocketSession = NULL;
//Exit0:
//    return;
//}

GM_SESSION* CSessionMgr::GetGMSession(UINT32 dwSessionID)
{
    PROCESS_ERROR(dwSessionID < MAX_GM_SESSION_COUNT);
    PROCESS_ERROR(m_GMSession[dwSessionID].nSvrID != 0);

    return m_GMSession + dwSessionID;
Exit0:
    return NULL;
}

//GM_SESSION &CSessionMgr::GetGMSession()
//{
//    return m_GMSession;
//}

BOOL CSessionMgr::CheckSession()
{
    //PROCESS_SUCCESS(m_GMSession.pSocketSession);

    for (INT32 nIndex = 0; nIndex < MAX_GM_SESSION_COUNT; nIndex++)
    {
        GM_SESSION* pGMSession = m_GMSession + nIndex;
        if (pGMSession->nSvrID == 0)
            continue;
        PROCESS_SUCCESS(pGMSession->pSocketSession);
    }

    return FALSE;
Exit1:
    return TRUE;
}

BOOL CSessionMgr::CloseAllSession()
{
    for (INT32 nIndex = 0; nIndex < MAX_GM_SESSION_COUNT; nIndex++)
    {
        GM_SESSION* pGMSession = m_GMSession + nIndex;
        if (pGMSession->nSvrID == 0)
            continue;
        if (pGMSession->pSocketSession)
            pGMSession->pSocketSession->Close();
    }

    return TRUE;
}

BOOL CSessionMgr::MainLoop(void)
{
    UINT32  dwCurrentTick = GetTickCount();

    if (dwCurrentTick > m_dwLastPingTick + PING_SVR_INTERNAL)    // todo_tq Allan Tao[7.8.2013] 
    {
        CMessageHandler::GetInstance().DoAllPing();
        m_dwLastPingTick = dwCurrentTick;
    }

    for (INT32 nIndex = 0; nIndex < MAX_GM_SESSION_COUNT; nIndex++)
    {
        GM_SESSION& rGMSession = m_GMSession[nIndex];
        if (rGMSession.nSvrID == 0)
            continue;

        if (rGMSession.pSocketSession)
        {
            if (SESSION_CONNECTED == rGMSession.nConnectState && rGMSession.qwTimer < dwCurrentTick)
            {
                CRI("GM server ping time out");
                rGMSession.pSocketSession->Close();
                rGMSession.qwTimer = GetTickCount() + RECONNECT_TIME;
                rGMSession.nConnectState = SESSION_DISCONNECTED;
            }
        }
        else 
        {
            if (SESSION_DISCONNECTED == rGMSession.nConnectState && rGMSession.qwTimer < dwCurrentTick)
            {
                GM_SVR  *pSvr = GetServer(rGMSession.nSvrID);
                if (pSvr == NULL)
                    continue;

                UINT32  dwAddr = inet_addr(pSvr->szAddr);
                LOG_PROCESS_ERROR(0xFFFFFFFF != dwAddr);
                if (0 == dwAddr)
                    dwAddr = inet_addr(g_szLocalAddress);

                INF("Try to connect gm server");

                rGMSession.nConnectState = SESSION_CONNECTING;
                rGMSession.pSocketSession = m_pNet->Connect(dwAddr, pSvr->dwPort);
                if (rGMSession.pSocketSession)
                    rGMSession.pSocketSession->SetUserData(&rGMSession);
            }
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}




