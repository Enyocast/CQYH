#include "stdafx.h"
#include "mm_session_mgr.h"

#include "time_ex.h"
#include "net.h"
#include "server_config.h"
#include "mm_message_handler.h"

CMMSessionMgr CMMSessionMgr::ms_Instance;

CMMSessionMgr::CMMSessionMgr()
{
	m_pNet = NULL;
	m_eServerState = sgsInvalid;
	m_qwLastPingTick = 0;

	memset(&m_MGSession, 0, sizeof(m_MGSession));
	memset(&m_MSSession, 0, sizeof(m_MSSession));
	memset(&m_GDSession, 0, sizeof(m_GDSession));
}

CMMSessionMgr::~CMMSessionMgr()
{
	UnInit();
}

BOOL CMMSessionMgr::Init(INet* pNet)
{
	LOG_PROCESS_ERROR(pNet);

	memset(m_MGSession, 0, sizeof(m_MGSession));
	for (INT32 nIndex = 1; nIndex < MAX_MG_SESSION_COUNT; nIndex++)
	{
		m_MGSession[nIndex].dwType = stMG;
		m_MGSession[nIndex].dwSessionID = nIndex;
	}

	memset(&m_MSSession, 0, sizeof(m_MSSession));
	m_MSSession.dwType = stMS;

	memset(&m_GDSession, 0, sizeof(m_GDSession));
	m_GDSession.dwType = stGD;

	m_pNet = pNet;
	m_eServerState = sgsInitializing;
	m_qwLastPingTick = 0;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMMSessionMgr::UnInit(void)
{
	LOG_CHECK_ERROR(!CheckSession());
	return TRUE;
}

CMMSessionMgr& CMMSessionMgr::GetInstance(void)
{
	return ms_Instance;
}

BOOL CMMSessionMgr::CheckSession()
{
	PROCESS_SUCCESS(m_MSSession.bConnected);

	for (INT32 nIndex = 1; nIndex < MAX_MG_SESSION_COUNT; nIndex++)
	{
		MG_SESSION* pMGSession = m_MGSession + nIndex;
		PROCESS_SUCCESS(pMGSession->pSocketSession);
	}

	return FALSE;
Exit1:
	return TRUE;
}

BOOL CMMSessionMgr::CloseAllSession()
{
	if (m_MSSession.bConnected && m_MSSession.pSocketSession)
		m_MSSession.pSocketSession->Close();

	for (INT32 nIndex = 1; nIndex < MAX_MG_SESSION_COUNT; nIndex++)
	{
		MG_SESSION* pMGSession = m_MGSession + nIndex;
		if (pMGSession->pSocketSession)
			pMGSession->pSocketSession->Close();
	}

	return TRUE;
}

BOOL CMMSessionMgr::MainLoop(void)
{
	UINT64 qwCurrentTick = GetTickCountEx();

	if (qwCurrentTick > m_qwLastPingTick + g_ServerConfig.Common.nServerPingInterval)
	{
		CMMMesageHandler::GetInstance().DoAllPing();
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
	else if (m_GDSession.pSocketSession == NULL && m_GDSession.qwTimer < qwCurrentTick)
	{
#if defined(WIN32) | defined (WIN64)
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
		CMMSessionMgr::GetInstance().GetServerState() != sgsClosing)
	{
		INF("try to connect to MM");

		UINT32 dwAddr = inet_addr(g_ServerConfig.MS.szAddress);
		if (dwAddr == 0)
			dwAddr = inet_addr(g_szLocalAddress);

		m_MSSession.pSocketSession = m_pNet->Connect(dwAddr, g_ServerConfig.MS.dwMMPort);
		if (m_MSSession.pSocketSession)
			m_MSSession.pSocketSession->SetUserData(&m_MSSession);
	}

	for (INT32 nIndex = 1; nIndex < MAX_MG_SESSION_COUNT; nIndex++)
	{
		MG_SESSION* pMGSession = m_MGSession + nIndex;
		if (pMGSession->pSocketSession == NULL)
			continue;

		if (pMGSession->qwTimer < qwCurrentTick)
		{
			if (pMGSession->pSocketSession)
			{
				CRI("MG %d ping time out", pMGSession->dwSessionID);
				pMGSession->pSocketSession->Close();
				pMGSession->qwTimer = 0xFFFFFFFF;
			}
		}
	}

	return TRUE;
}
