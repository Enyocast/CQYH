#include "stdafx.h"
#include "statis_info.h"
#include "db_session_mgr.h"

#include "time_ex.h"

#include "server_config.h"

#include "net.h"
#include "db_message_handler.h"

CDBSessionMgr CDBSessionMgr::ms_Instance;

CDBSessionMgr::CDBSessionMgr()
{
    m_pNet = NULL;
    m_eServerState = sgsInvalid;
	m_qwLastPingTick = 0;
	m_qwLastStatisTick = 0;
    memset(m_GSSession, 0, sizeof(m_GSSession));
    memset(m_GTSession, 0, sizeof(m_GTSession));
    memset(&m_MSSession, 0, sizeof(m_MSSession));
    memset(&m_GDSession, 0, sizeof(m_GDSession));
}

CDBSessionMgr::~CDBSessionMgr()
{
    UnInit();
}

BOOL CDBSessionMgr::Init(INet* pInternalNet)
{
    LOG_PROCESS_ERROR(pInternalNet);

    memset(m_GSSession, 0, sizeof(m_GSSession));
    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        m_GSSession[nIndex].dwType = stGS;
        m_GSSession[nIndex].dwSessionID = nIndex;
    }

    memset(m_GTSession, 0, sizeof(m_GTSession));
    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        m_GTSession[nIndex].dwType = stGT;
        m_GTSession[nIndex].dwSessionID = nIndex;
    }

    memset(&m_MSSession, 0,sizeof(m_MSSession));
    m_MSSession.dwType = stMS;

    memset(&m_GDSession, 0,sizeof(m_GDSession));
    m_GDSession.dwType = stGD;

    m_pNet = pInternalNet;
    m_eServerState = sgsInitializing;
	m_qwLastPingTick = 0;
	m_qwLastStatisTick = 0;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CDBSessionMgr::UnInit(void)
{
    LOG_CHECK_ERROR(!CheckSession());    
    return TRUE;
}

CDBSessionMgr& CDBSessionMgr::GetInstance(void)
{
    return ms_Instance;
}

BOOL CDBSessionMgr::CheckSession()
{
    PROCESS_SUCCESS(m_MSSession.bConnected);
        
    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        GS_SESSION* pGSSession = m_GSSession + nIndex;
        PROCESS_SUCCESS(pGSSession->pSocketSession);
    }

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        GT_SESSION* pGTSession = m_GTSession + nIndex;
        PROCESS_SUCCESS(pGTSession->pSocketSession);
    }
    
    return FALSE;
Exit1:
    return TRUE;
}


BOOL CDBSessionMgr::CloseAllSession()
{
    if (m_MSSession.bConnected && m_MSSession.pSocketSession)
        m_MSSession.pSocketSession->Close();

    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        GS_SESSION* pGSSession = m_GSSession + nIndex;
        if (pGSSession->pSocketSession)
            pGSSession->pSocketSession->Close();
    }

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        GT_SESSION* pGTSession = m_GTSession + nIndex;
        if (pGTSession->pSocketSession)
            pGTSession->pSocketSession->Close();
    }

    return TRUE;
}


BOOL CDBSessionMgr::MainLoop(void)
{
    UINT64 qwCurrentTick = GetTickCountEx();

    if (qwCurrentTick > m_qwLastPingTick + g_ServerConfig.Common.nServerPingInterval)
    {
        CDBMessageHandler::GetInstance().DoAllPing();
        m_qwLastPingTick = qwCurrentTick;
	}
	if (qwCurrentTick > m_qwLastStatisTick + 1000)//g_ServerConfig.Common.nServerStatisInterval)
	{
		//g_UpdateProcessStatisInfo();
		m_qwLastStatisTick = qwCurrentTick;
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
        CDBSessionMgr::GetInstance().GetServerState() != sgsClosing)
    {
        INF("try to connect to MS");
		
		UINT32 dwAddr = inet_addr(g_ServerConfig.MS.szAddress);
		if(dwAddr == 0)
			dwAddr = inet_addr(g_szLocalAddress);

        m_MSSession.pSocketSession = m_pNet->Connect(dwAddr, g_ServerConfig.MS.dwDBPort);
        if (m_MSSession.pSocketSession)
            m_MSSession.pSocketSession->SetUserData(&m_MSSession);
    }

    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        GS_SESSION* pGSSession = m_GSSession + nIndex;
        if (pGSSession->pSocketSession == NULL)
            continue;

        if (pGSSession->qwTimer < qwCurrentTick)
        {
            if (pGSSession->pSocketSession)
            {
                CRI("GS %d ping time out", pGSSession->dwSessionID);
                pGSSession->pSocketSession->Close();
                pGSSession->qwTimer = 0xFFFFFFFF;
            }
        }
    }

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        GT_SESSION* pGTSession = m_GTSession + nIndex;
        if (pGTSession->pSocketSession == NULL)
            continue;

        if (pGTSession->qwTimer < qwCurrentTick)
        {
            if (pGTSession->pSocketSession)
            {
                CRI("GT %d ping time out", pGTSession->dwSessionID);
                pGTSession->pSocketSession->Close();
                pGTSession->qwTimer = 0xFFFFFFFF;
            }
        }
    }

    return TRUE;
}
