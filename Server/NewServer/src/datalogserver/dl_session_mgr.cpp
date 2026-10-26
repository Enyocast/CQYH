#include "stdafx.h"
#include "statis_info.h"

#include "linux_compatible.h"

#include "time_ex.h"
#include "server_config.h"
#include "net.h"

#include "dl_session_mgr.h"
#include "dl_message_handler.h"

CDLSessionMgr CDLSessionMgr::ms_Instance;

CDLSessionMgr::CDLSessionMgr()
{
	m_eServerState = sgsInvalid;
	m_pInternalNet = NULL;
	m_qwLastPingTick = 0;
	m_qwLastStatisTick = 0;
	memset(&m_MSSession, 0, sizeof(m_MSSession));
	memset(&m_GDSession, 0, sizeof(m_GDSession));
	memset(m_GSSession, 0, sizeof(m_GSSession));
}

CDLSessionMgr::~CDLSessionMgr()
{
	UnInit();
}

BOOL CDLSessionMgr::Init(INet* pInternalNet)
{
	LOG_PROCESS_ERROR(pInternalNet);

	m_eServerState = sgsInitializing;
	m_qwLastPingTick = 0;
	m_qwLastStatisTick = 0;

	m_pInternalNet = pInternalNet;

	memset(&m_MSSession, 0, sizeof(m_MSSession));
	m_MSSession.byType = stMS;

	memset(&m_GDSession, 0, sizeof(m_GDSession));
	m_GDSession.byType = stGD;

	memset(m_GSSession, 0, sizeof(m_GSSession));
	for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
	{
		m_GSSession[nIndex].byType = stGS;
		m_GSSession[nIndex].dwSessionID = nIndex;
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CDLSessionMgr::UnInit(void)
{
	LOG_CHECK_ERROR(!CheckSession());
	return TRUE;
}

CDLSessionMgr& CDLSessionMgr::GetInstance(void)
{
	return ms_Instance;
}

BOOL CDLSessionMgr::CheckSession()
{
    PROCESS_SUCCESS(m_MSSession.bConnected);

	for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
	{
		GS_SESSION* pGSSession = m_GSSession + nIndex;
		PROCESS_SUCCESS(pGSSession->pSocketSession);
	}

	return FALSE;
Exit1:
	return TRUE;
}

BOOL CDLSessionMgr::CloseAllSession()
{
	if (m_MSSession.bConnected && m_MSSession.pSocketSession)
		m_MSSession.pSocketSession->Close();

	for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
	{
		GS_SESSION* pGSSession = m_GSSession + nIndex;
		if (pGSSession->pSocketSession)
			pGSSession->pSocketSession->Close();
	}

	return TRUE;
}

BOOL CDLSessionMgr::MainLoop(void)
{
	UINT64 qwCurrentTick = GetTickCountEx();

	if (qwCurrentTick > m_qwLastPingTick + g_ServerConfig.Common.nServerPingInterval)
	{
		CDLMessageHandler::GetInstance().DoAllPing();
		m_qwLastPingTick = qwCurrentTick;
	}
	if (qwCurrentTick > m_qwLastStatisTick + 1000)//g_ServerConfig.Common.nServerStatisInterval)
	{
		//g_UpdateProcessStatisInfo();
		m_qwLastStatisTick = qwCurrentTick;
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
	else if(m_MSSession.pSocketSession == NULL && 
            m_MSSession.qwTimer < qwCurrentTick &&
            CDLSessionMgr::GetInstance().GetServerState() != sgsClosing)
	{
		INF("try to connect to MS");

		UINT32 dwAddr = inet_addr(g_ServerConfig.MS.szAddress);
		if(dwAddr == 0)
			dwAddr = inet_addr(g_szLocalAddress);

		m_MSSession.pSocketSession = m_pInternalNet->Connect(dwAddr, g_ServerConfig.MS.dwDLPort);
		if (m_MSSession.pSocketSession)
			m_MSSession.pSocketSession->SetUserData(&m_MSSession);
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
	else if(m_GDSession.pSocketSession == NULL && 
            m_GDSession.qwTimer < qwCurrentTick)
    {
#if defined(WIN32)
		INF("try to connect to GD");
		m_GDSession.pSocketSession = m_pInternalNet->Connect(inet_addr(g_szLocalAddress), g_ServerConfig.Common.dwGuardPort);
		if (m_GDSession.pSocketSession)
			m_GDSession.pSocketSession->SetUserData(&m_GDSession);
#endif
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

	return TRUE;
}