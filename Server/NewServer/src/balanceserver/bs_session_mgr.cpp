#include "stdafx.h"
#include "statis_info.h"

#include "time_ex.h"
#include "server_config.h"
#include "net.h"

#include "bs_session_mgr.h"
#include "internal_message_handler.h"

CBSSessionMgr CBSSessionMgr::ms_Instance;

CBSSessionMgr::CBSSessionMgr()
{
	m_eServerState = sgsInvalid;
    m_nCurPointerIndex = 0;
	m_qwLastPingTick = 0;
	m_qwLastStatisTick = 0;

    m_pExternalNet = NULL;
	m_pInternalNet = NULL;

    memset(&m_GDSession, 0, sizeof(m_GDSession));
    memset(&m_MSSession, 0, sizeof(m_MSSession));
}

CBSSessionMgr::~CBSSessionMgr()
{
	UnInit();
}

BOOL CBSSessionMgr::Init(INet* pExternalNet, INet* pInternalNet)
{
	LOG_PROCESS_ERROR(pExternalNet);
	LOG_PROCESS_ERROR(pInternalNet);

	m_eServerState = sgsInitializing;
	m_nCurPointerIndex = 0;
	m_qwLastPingTick = 0;
	m_qwLastStatisTick = 0;

	m_pExternalNet = pExternalNet;
	m_pInternalNet = pInternalNet;

	memset(&m_MSSession, 0, sizeof(m_MSSession));
	m_MSSession.dwType = stMS;

	memset(&m_GDSession, 0, sizeof(m_GDSession));
	m_GDSession.dwType = stGD;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CBSSessionMgr::UnInit(void)
{
	LOG_CHECK_ERROR(!CheckSession());
	return TRUE;
}

CBSSessionMgr& CBSSessionMgr::GetInstance(void)
{
	return ms_Instance;
}

BOOL CBSSessionMgr::CheckSession()
{
    PROCESS_SUCCESS(m_MSSession.bConnected);
	return FALSE;
Exit1:
	return TRUE;
}

BOOL CBSSessionMgr::CloseAllSession()
{
	if (m_MSSession.bConnected && m_MSSession.pSocketSession)
		m_MSSession.pSocketSession->Close();

	return TRUE;
}

BOOL CBSSessionMgr::MainLoop(void)
{

	UINT64 qwCurrentTick = GetTickCountEx();

	if (qwCurrentTick > m_qwLastPingTick + g_ServerConfig.Common.nServerPingInterval)
	{
		CBSInternalMessageHandler::GetInstance().DoAllPing();
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
            CBSSessionMgr::GetInstance().GetServerState() != sgsClosing)
	{
		INF("try to connect to MS");
		UINT32 dwAddr = inet_addr(g_ServerConfig.MS.szAddress);
		if(dwAddr == 0)
			dwAddr = inet_addr(g_szLocalAddress);
		
		m_MSSession.pSocketSession = m_pInternalNet->Connect(dwAddr, g_ServerConfig.MS.dwBSPort);
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

	return TRUE;

}
