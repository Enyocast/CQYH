#include "stdafx.h"
#include "statis_info.h"
#include "gs_session_mgr.h"

//#include <winsock2.h>

#include "time_ex.h"
#include "server_config.h"
#include "net.h"
#include "gs_message_handler.h"
#include "game_world.h"

CGSSessionMgr CGSSessionMgr::ms_Instance;

CGSSessionMgr::CGSSessionMgr()
{
    m_pNet = NULL;
    m_dwGSSessionID = 0;
	m_qwLastPingTick = 0;
    m_eServerState = sgsInvalid;
	memset(m_GTSession, 0, sizeof(m_GTSession));
	memset(&m_MSSession, 0, sizeof(m_MSSession));
	memset(&m_DBSession, 0, sizeof(m_DBSession));
	memset(&m_GDSession, 0, sizeof(m_GDSession));
	memset(&m_DLSession, 0, sizeof(m_DLSession));
}

CGSSessionMgr::~CGSSessionMgr()
{
    UnInit();
}

BOOL CGSSessionMgr::Init(INet* pNet)
{
    LOG_PROCESS_ERROR(pNet);

    memset(m_GTSession, 0, sizeof(m_GTSession));
    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        m_GTSession[nIndex].byType = stGT;
        m_GTSession[nIndex].dwSessionID = nIndex;
    }

    memset(&m_MSSession, 0, sizeof(m_MSSession));
    m_MSSession.byType = stMS;

    memset(&m_DBSession, 0, sizeof(m_DBSession));
    m_DBSession.byType = stDB;
    
    memset(&m_GDSession, 0, sizeof(m_GDSession));
    m_GDSession.byType = stGD;

	memset(&m_DLSession, 0, sizeof(m_DLSession));
	m_DLSession.byType = stDL;

    m_pNet = pNet;
    m_dwGSSessionID = 0;
	m_qwLastPingTick = 0;
    m_eServerState = sgsInitializing;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGSSessionMgr::UnInit(void)
{
    LOG_CHECK_ERROR(m_mapSession2Role.empty());
    m_mapSession2Role.clear();
    
    LOG_CHECK_ERROR(!CheckSession());
    return TRUE;
}

CGSSessionMgr& CGSSessionMgr::GetInstance(void)
{
    return ms_Instance;
}

INT32 CGSSessionMgr::GetServerState(void)
{
    return m_eServerState;
}

void CGSSessionMgr::SetServerState(INT32 eServerState)
{
    m_eServerState = eServerState;
}

UINT32 CGSSessionMgr::GetSelfSessionID(void)
{
    return m_dwGSSessionID;
}

void CGSSessionMgr::SetSelfSessionID(UINT32 dwGSSessionID)
{
    m_dwGSSessionID = dwGSSessionID;
}

BOOL CGSSessionMgr::AttachRoleToSession(UINT32 dwClientSessionID, CRole* poRole)
{
    std::pair<MAP_SESSION_2_ROLE::iterator, bool> InsRet;

    InsRet = m_mapSession2Role.insert(std::make_pair(dwClientSessionID, poRole));
    LOG_PROCESS_ERROR(InsRet.second);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGSSessionMgr::DetachRoleFromSession(UINT32 dwClientSessionID)
{
    MAP_SESSION_2_ROLE::iterator it;

    it = m_mapSession2Role.find(dwClientSessionID);
    PROCESS_ERROR(it != m_mapSession2Role.end());

    m_mapSession2Role.erase(it);

    return TRUE;
Exit0:
    return FALSE;
}

CRole* CGSSessionMgr::FindRoleBySessionID(UINT32 dwClientSessionID)
{
    MAP_SESSION_2_ROLE::iterator it;
    
    it = m_mapSession2Role.find(dwClientSessionID);
    PROCESS_ERROR(it != m_mapSession2Role.end());

    return it->second;
Exit0:
    return NULL;
}

BOOL CGSSessionMgr::MainLoop(void)
{
    UINT64 qwCurrentTick = GetTickCountEx();

    if (qwCurrentTick > m_qwLastPingTick + g_ServerConfig.Common.nServerPingInterval)
    {
        CGSMessageHandler::GetInstance().DoAllPing();
        m_qwLastPingTick = qwCurrentTick;
	}

    if (m_GDSession.bConnected && m_GDSession.pSocketSession)
    {
        if (m_GDSession.qwTimer < qwCurrentTick)
        {
            CRI("GD ping time out");
            m_GDSession.pSocketSession->Close();
            m_GDSession.qwTimer = 0xFFFFFFFF;
        }
    }
    else if(m_GDSession.pSocketSession == NULL && m_GDSession.qwTimer < qwCurrentTick)
    {
#if defined(WIN32)
        INF("try to connect to GD");
        m_GDSession.pSocketSession = m_pNet->Connect(inet_addr(g_szLocalAddress), g_ServerConfig.Common.dwGuardPort);
        if (m_GDSession.pSocketSession)
            m_GDSession.pSocketSession->SetUserData(&m_GDSession);
#endif
    }

    if (m_MSSession.bConnected && m_MSSession.pSocketSession)
    {
        if (m_MSSession.qwTimer < qwCurrentTick)
        {
            CRI("MS ping time out");
            m_MSSession.pSocketSession->Close();
            m_MSSession.qwTimer = 0xFFFFFFFF;
        }
    }
    else if (m_MSSession.pSocketSession == NULL && 
        m_MSSession.qwTimer < qwCurrentTick &&
        CGSSessionMgr::GetInstance().GetServerState() != sgsClosing )
    {
        INF("try to connect to MS");
		
		UINT32 dwAddr = inet_addr(g_ServerConfig.MS.szAddress);
		if(dwAddr == 0)
			dwAddr = inet_addr(g_szLocalAddress);

        m_MSSession.pSocketSession = m_pNet->Connect(dwAddr, g_ServerConfig.MS.dwGSPort);
        if (m_MSSession.pSocketSession)
            m_MSSession.pSocketSession->SetUserData(&m_MSSession);
    }

    if (m_DBSession.bConnected && m_DBSession.pSocketSession)
    {
        if (m_DBSession.qwTimer < qwCurrentTick)
        {
            CRI("DB ping time out");
            m_DBSession.pSocketSession->Close();
            m_DBSession.qwTimer = 0xFFFFFFFF;
        }
    }
    else if (m_DBSession.pSocketSession == NULL && 
        m_DBSession.dwAddr && m_dwGSSessionID != 0 &&
        m_DBSession.qwTimer < qwCurrentTick &&
        CGSSessionMgr::GetInstance().GetServerState() != sgsClosing)
    {
        INF("try to connect to DB");
        m_DBSession.pSocketSession = m_pNet->Connect(m_DBSession.dwAddr, m_DBSession.wPort);
        if (m_DBSession.pSocketSession)
            m_DBSession.pSocketSession->SetUserData(&m_DBSession);
    }

	if (m_DLSession.bConnected && m_DLSession.pSocketSession)
	{
		if (m_DLSession.qwTimer < qwCurrentTick)
		{
			CRI("DL ping time out");
			m_DLSession.pSocketSession->Close();
			m_DLSession.qwTimer = 0xFFFFFFFF;
		}
	}
	else if (m_DLSession.pSocketSession == NULL && 
		m_DLSession.dwAddr && m_dwGSSessionID != 0 &&
        m_DLSession.qwTimer < qwCurrentTick &&
        CGSSessionMgr::GetInstance().GetServerState() != sgsClosing)
	{
		INF("try to connect to DL");
		m_DLSession.pSocketSession = m_pNet->Connect(m_DLSession.dwAddr, m_DLSession.wPort);
		if (m_DLSession.pSocketSession)
			m_DLSession.pSocketSession->SetUserData(&m_DLSession);
	}

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        GT_SESSION* pGTSession = GetGTSession(nIndex);
        LOG_PROCESS_ERROR(pGTSession);

        if (pGTSession->bConnected && pGTSession->pSocketSession)
        {
            if (pGTSession->qwTimer < qwCurrentTick)
            {
                CRI("GT %d ping time out", pGTSession->dwSessionID);
                pGTSession->pSocketSession->Close();
                pGTSession->qwTimer = 0xFFFFFFFF;
            }
        }
        else if (pGTSession->pSocketSession == NULL &&
            pGTSession->dwAddr && m_dwGSSessionID != 0 &&
            pGTSession->qwTimer < qwCurrentTick &&
            CGSSessionMgr::GetInstance().GetServerState() != sgsClosing)
        {
            INF("try to connect to GT %d", pGTSession->dwSessionID);
            pGTSession->pSocketSession = m_pNet->Connect(pGTSession->dwAddr, pGTSession->wPort);
            if (pGTSession->pSocketSession)
                pGTSession->pSocketSession->SetUserData(pGTSession);
        }
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGSSessionMgr::CheckSession()
{
    PROCESS_SUCCESS(m_MSSession.bConnected);
    PROCESS_SUCCESS(m_DBSession.bConnected);
	PROCESS_SUCCESS(m_DLSession.bConnected);

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        GT_SESSION* pGTSession = m_GTSession + nIndex;
        PROCESS_SUCCESS(pGTSession->pSocketSession);
    }

    return FALSE;
Exit1:
    return TRUE;
}


BOOL CGSSessionMgr::CloseAllSession()
{
    if (m_MSSession.bConnected && m_MSSession.pSocketSession)
        m_MSSession.pSocketSession->Close();

    if (m_DBSession.bConnected && m_DBSession.pSocketSession)
        m_DBSession.pSocketSession->Close();

	if (m_DLSession.bConnected && m_DLSession.pSocketSession)
		m_DLSession.pSocketSession->Close();

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        GT_SESSION* pGTSession = GetGTSession(nIndex);
        if (pGTSession && pGTSession->bConnected && pGTSession->pSocketSession)
            pGTSession->pSocketSession->Close();     
    }

    return TRUE;
}