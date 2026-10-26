#include "stdafx.h"
#include "statis_info.h"
#include "gd_session_mgr.h"

#include "time_ex.h"
#include "net.h"

#include "guard_config.h"
#include "gd_message_handler.h"
#include "guardserver.h"
#include "statis_info.h"

CGDSessionMgr CGDSessionMgr::ms_Instance;
CGDSessionMgr::CGDSessionMgr()
{
    m_pNet = NULL;
    m_qwLastPingTick = 0;
    //m_qwLastStatisTick = 0;
    memset(&m_GTSession, 0, sizeof(m_GTSession));
	memset(&m_RemoteGDSession, 0, sizeof(m_RemoteGDSession));
}

CGDSessionMgr::~CGDSessionMgr()
{
    UnInit();
}

BOOL CGDSessionMgr::Init(INet* pNet)
{
    LOG_PROCESS_ERROR(pNet);
    m_qwLastPingTick = 0;
    //m_qwLastStatisTick = 0;

    memset(m_GTSession, 0, sizeof(m_GTSession));
    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        m_GTSession[nIndex].dwType = stGT;
        m_GTSession[nIndex].dwSessionID = nIndex;
    }

    memset(m_GSSession, 0, sizeof(m_GSSession));
    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        m_GSSession[nIndex].dwType = stGS;
        m_GSSession[nIndex].dwSessionID = nIndex;
    }

    memset(&m_DBSession, 0, sizeof(m_DBSession));
    m_DBSession.dwType = stDB;

    memset(&m_LSSession, 0, sizeof(m_LSSession));
    m_LSSession.dwType = stLS;

    memset(&m_MSSession, 0, sizeof(m_MSSession));
    m_MSSession.dwType = stMS;

	memset(&m_BSSession, 0, sizeof(m_BSSession));
	m_BSSession.dwType = stBS;

	memset(&m_DLSession, 0, sizeof(m_DLSession));
	m_DLSession.dwType = stDL;

    memset(&m_GMSession, 0, sizeof(m_GMSession));
    m_GMSession.dwType = stGM;

	memset(&m_MTSession, 0, sizeof(m_MTSession));
	m_MTSession.dwType = stMT;

	memset(&m_MMSession, 0, sizeof(m_MMSession));
	m_MMSession.dwType = stMM;

	memset(m_MGSession, 0, sizeof(m_MGSession));
	for (INT32 nIndex = 1; nIndex < MAX_MG_SESSION_COUNT; nIndex++)
	{
		m_MGSession[nIndex].dwType = stMG;
		m_MGSession[nIndex].dwSessionID = nIndex;
	}

    m_pNet = pNet;

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CGDSessionMgr::UnInit(void)
{
    INT32 nRetCode = 0;

    nRetCode = CloseAllSocketSession();
    LOG_CHECK_ERROR(nRetCode);

    return TRUE;
}

CGDSessionMgr& CGDSessionMgr::GetInstance(void)
{
    return ms_Instance;
}

SRemoteGuardSession* CGDSessionMgr::GetRemoteGDSession(UINT32 dwIp)
{
	for(INT32 nIndex = 1; nIndex < MAX_GUARD_COUNT_PER_AREA; nIndex++)
	{
		if(m_RemoteGDSession[nIndex].dwIp == dwIp)
			return &m_RemoteGDSession[nIndex];
	}

	return NULL;
}

BOOL CGDSessionMgr::MainLoop(void)
{
    UINT64 qwCurrentTick = GetTickCountEx();

    if (qwCurrentTick > m_qwLastPingTick + g_GuardConfig.nServerPingInterval)
    {
        CGDMessageHandler::GetInstance().DoAllPing();

        m_qwLastPingTick = qwCurrentTick;
	}
	//if (qwCurrentTick > m_qwLastStatisTick + 1000)//g_ServerConfig.Common.nServerStatisInterval)
	//{
	//	//g_UpdateSystemStatisInfo();
	//	//g_UpdateProcessStatisInfo();
	//	if (m_MTSession.pSocketSession)
	//	{
	//		CGDMessageHandler::GetInstance().DoMTUpdateStatisInfo();
	//	}
	//	g_ResetStatisInfo();
	//	m_qwLastStatisTick = qwCurrentTick;
	//}

    if (m_DBSession.pSocketSession && m_DBSession.qwTimer < qwCurrentTick)
    {
        CRI("DB ping time out");
        m_DBSession.pSocketSession->Close();
        m_DBSession.qwTimer = (UINT64)(~0);
    }

    if (m_LSSession.pSocketSession && m_LSSession.qwTimer < qwCurrentTick)
    {
        CRI("LS ping time out");
        m_LSSession.pSocketSession->Close();
        m_LSSession.qwTimer = (UINT64)(~0);
    }

    if (m_MSSession.pSocketSession && m_MSSession.qwTimer < qwCurrentTick)
    {
        CRI("MS ping time out");
        m_MSSession.pSocketSession->Close();
        m_MSSession.qwTimer = (UINT64)(~0);
	}

	if (m_BSSession.pSocketSession && m_BSSession.qwTimer < qwCurrentTick)
	{
		CRI("BS ping time out");
		m_BSSession.pSocketSession->Close();
        m_BSSession.qwTimer = (UINT64)(~0);
	}

	if (m_MTSession.pSocketSession && m_MTSession.qwTimer < qwCurrentTick)
	{
		CRI("MT ping time out");
		m_MTSession.pSocketSession->Close();
		m_MTSession.qwTimer = (UINT64)(~0);
    }

    if (m_GMSession.pSocketSession && m_GMSession.qwTimer < qwCurrentTick)
    {
        CRI("GM ping time out");
        m_GMSession.pSocketSession->Close();
        m_GMSession.qwTimer = (UINT64)(~0);
    }

	if (m_MMSession.pSocketSession && m_MMSession.qwTimer < qwCurrentTick)
	{
		CRI("MM ping time out");
		m_MMSession.pSocketSession->Close();
		m_MMSession.qwTimer = (UINT64)(~0);
	}

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        SGTSession& rGTSession = m_GTSession[nIndex];

        if (rGTSession.pSocketSession && rGTSession.qwTimer < qwCurrentTick)
        {
            CRI("GT %d ping time out", rGTSession.dwSessionID);
            rGTSession.pSocketSession->Close();
            rGTSession.qwTimer = (UINT64)(~0);
        }
    }

    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        SGSSession& rGSSession = m_GSSession[nIndex];

        if (rGSSession.pSocketSession && rGSSession.qwTimer < qwCurrentTick)
        {
            CRI("GS %d ping time out", rGSSession.dwSessionID);
            rGSSession.pSocketSession->Close();
            rGSSession.qwTimer = (UINT64)(~0);
        }
    }

	for (INT32 nIndex = 1; nIndex < MAX_MG_SESSION_COUNT; nIndex++)
	{
		SMGSession& rMGSession = m_MGSession[nIndex];

		if (rMGSession.pSocketSession && rMGSession.qwTimer < qwCurrentTick)
		{
			CRI("MG %d ping time out", rMGSession.dwSessionID);
			rMGSession.pSocketSession->Close();
			rMGSession.qwTimer = (UINT64)(~0);
		}
	}

    for(CServerSessionListItr itr = m_ServerSessionList.begin(); itr != m_ServerSessionList.end(); ++itr)
    {
        if(itr->pSocketSession && itr->qwTimer < qwCurrentTick)
        {
            CRI("Temp Session regrister time out");
            itr->pSocketSession->Close();
        }
    }

    return TRUE;
}


BOOL CGDSessionMgr::CheckHasSocketSession()
{
    PROCESS_SUCCESS(m_DBSession.pSocketSession);
    PROCESS_SUCCESS(m_LSSession.pSocketSession);
	PROCESS_SUCCESS(m_BSSession.pSocketSession);
    PROCESS_SUCCESS(m_MSSession.pSocketSession);
    PROCESS_SUCCESS(m_GMSession.pSocketSession);
	PROCESS_SUCCESS(m_MMSession.pSocketSession);
    PROCESS_SUCCESS(m_ServerSessionList.size() > 0);

    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        SGSSession* pGSSession = m_GSSession + nIndex;
        PROCESS_SUCCESS(pGSSession->pSocketSession);
    }

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        SGTSession* pGTSession = m_GTSession + nIndex;
        PROCESS_SUCCESS(pGTSession->pSocketSession);
    }

	for (INT32 nIndex = 1; nIndex < MAX_MG_SESSION_COUNT; nIndex++)
	{
		SMGSession* pMGSession = m_MGSession + nIndex;
		PROCESS_SUCCESS(pMGSession->pSocketSession);
	}

    return FALSE;
Exit1:
    return TRUE;
}


BOOL CGDSessionMgr::CloseAllSocketSession()
{
    if (m_LSSession.pSocketSession)
        m_LSSession.pSocketSession->Close();

    if (m_DBSession.pSocketSession)
        m_DBSession.pSocketSession->Close();

    if(m_MSSession.pSocketSession)
        m_MSSession.pSocketSession->Close();

	if(m_BSSession.pSocketSession)
		m_BSSession.pSocketSession->Close();

    if (m_GMSession.pSocketSession)
        m_GMSession.pSocketSession->Close();

	if (m_MMSession.pSocketSession)
		m_MMSession.pSocketSession->Close();

    for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
    {
        SGSSession* pGSSession = m_GSSession + nIndex;
        if (pGSSession->pSocketSession)
            pGSSession->pSocketSession->Close();
    }

    for (INT32 nIndex = 1; nIndex < MAX_GT_SESSION_COUNT; nIndex++)
    {
        SGTSession* pGTSession = m_GTSession + nIndex;
        if (pGTSession->pSocketSession)
            pGTSession->pSocketSession->Close();
    }

	for (INT32 nIndex = 1; nIndex < MAX_MG_SESSION_COUNT; nIndex++)
	{
		SMGSession* pMGSession = m_MGSession + nIndex;
		if (pMGSession->pSocketSession)
			pMGSession->pSocketSession->Close();
	}

    for(CServerSessionListItr itr = m_ServerSessionList.begin(); itr != m_ServerSessionList.end(); ++itr)
    {
        if(itr->pSocketSession)
            itr->pSocketSession->Close();
    }

    return TRUE;
}
BOOL CGDSessionMgr::CheckSocketConnected(UINT8 byType, UINT8 byNum)
{
	switch (byType)
	{
	case stMS:
		LOG_PROCESS_ERROR( byNum == 1 );
		return m_MSSession.pSocketSession == NULL ? FALSE : TRUE;
		break;
	case stDB:
		LOG_PROCESS_ERROR(byNum == 1);
		return m_DBSession.pSocketSession == NULL ? FALSE : TRUE;
		break;
	case stBS:
		LOG_PROCESS_ERROR(byNum == 1);
		return m_BSSession.pSocketSession == NULL ? FALSE : TRUE;
		break;
	case stLS:
		LOG_PROCESS_ERROR(byNum == 1);
		return m_LSSession.pSocketSession == NULL ? FALSE : TRUE;
		break;
	case stGM:
        LOG_PROCESS_ERROR(byNum == 1);
        return m_GMSession.pSocketSession == NULL ? FALSE : TRUE;
		break;
	case stDL:
		LOG_PROCESS_ERROR(byNum == 1);
		return m_DLSession.pSocketSession == NULL ? FALSE : TRUE;
		break;

	case stGT:
		LOG_PROCESS_ERROR(byNum > 0 && byNum < MAX_GT_SESSION_COUNT);
		return GetGTSession(byNum)->pSocketSession == NULL ? FALSE : TRUE;
		break;
	case stGS:
		LOG_PROCESS_ERROR(byNum > 0 && byNum < MAX_GS_SESSION_COUNT);
		return GetGSSession(byNum)->pSocketSession == NULL ? FALSE : TRUE;
		break;
	case stMM:
		LOG_PROCESS_ERROR(byNum == 1);
		return m_MMSession.pSocketSession == NULL ? FALSE : TRUE;
		break;
	case stMG:
		LOG_PROCESS_ERROR(byNum > 0 && byNum < MAX_MG_SESSION_COUNT);
		return GetGSSession(byNum)->pSocketSession == NULL ? FALSE : TRUE;
		break;
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}
	return TRUE;
Exit0:
	return FALSE;
}
BOOL CGDSessionMgr::AddServerSession(ISocketSession* poSession)
{
    ServerSession stSession;

    stSession.dwType = stInvalid;
    stSession.pSocketSession = poSession;
	stSession.eState = InternalMessage::epsUnonnect;
    stSession.qwTimer = GetTickCountEx() + g_GuardConfig.nRegisterGuardTimeout;
	stSession.dwSessionID = 1;
    
    m_ServerSessionList.push_back(stSession);

    return TRUE;
}

BOOL CGDSessionMgr::RemoveServerSession(ISocketSession* poSession)
{
    for(CServerSessionListItr itr = m_ServerSessionList.begin(); itr != m_ServerSessionList.end(); ++itr)
    {
        if(itr->pSocketSession == poSession)
        {
            m_ServerSessionList.erase(itr);
            return TRUE;
        }
    }

    return FALSE;
}

