#include "stdafx.h"
#include "statis_info.h"
#include "gt_session_mgr.h"

//#include <winsock2.h>

#include "time_ex.h"

#include "server_config.h"

#include "net.h"

#include "internal_message_handler.h"
#include "external_message_handler.h"

CGTSessionMgr CGTSessionMgr::ms_Instance;

static UINT64 s_qwLastTick = 0;
extern INT32 s_nDownMsgCount[ExternalMessage::max_message_count];
extern INT32 s_nDownMsgSize[ExternalMessage::max_message_count];
extern INT32 s_nUpMsgCount[ExternalMessage::max_message_count];
extern INT32 s_nUpMsgSize[ExternalMessage::max_message_count];

CGTSessionMgr::CGTSessionMgr()
{
	m_eServerState = sgsInvalid;
	m_dwGTSessionID = 0;
	m_qwLastPingTick = 0;
	m_qwLastStatisTick = 0;
	m_pExternalNet = NULL;
	m_pInternalNet = NULL;
	memset(m_ClientSessionPool, 0, sizeof(m_ClientSessionPool));
	memset(m_GSSession, 0, sizeof(m_GSSession));
	memset(&m_LSSession, 0, sizeof(m_LSSession));
	memset(&m_DBSession, 0, sizeof(m_DBSession));
	memset(&m_MSSession, 0, sizeof(m_MSSession));
	memset(&m_bOpened, 0, sizeof(m_bOpened));
}

CGTSessionMgr::~CGTSessionMgr()
{
	UnInit();
}

BOOL CGTSessionMgr::Init(INet* pExternalNet, INet* pInternalNet)
{
	LOG_PROCESS_ERROR(pExternalNet);
	LOG_PROCESS_ERROR(pInternalNet);

	memset(m_ClientSessionPool, 0, sizeof(m_ClientSessionPool));
	for (INT32 nIndex = 1; nIndex < MAX_CLIENT_SESSION_COUNT; nIndex++)
	{
		m_ClientSessionPool[nIndex].byType = stClient;
		m_ClientSessionPool[nIndex].dwSessionID = 0;
		m_FreeClientSessionList.push_back(m_ClientSessionPool + nIndex);
	}
	m_UsedClientSessionList.Clear();

	memset(m_GSSession, 0, sizeof(m_GSSession));
	for (INT32 nIndex = 0; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
	{
		m_GSSession[nIndex].byType = stGS;
		m_GSSession[nIndex].dwSessionID = nIndex;
	}

	for (INT32 nIndex = 0; nIndex < MAX_SERVER_GROUP_COUNT; nIndex++)
	{
#if !defined(_FINAL) | defined(_DEBUG)
		if (IsValidGroup(nIndex))
			m_bOpened[nIndex] = TRUE;
#endif // _FINAL
	}

	memset(&m_DBSession, 0, sizeof(m_DBSession));
	m_DBSession.byType = stDB;

	memset(&m_LSSession, 0, sizeof(m_LSSession));
	m_LSSession.byType = stLS;

	memset(&m_MSSession, 0, sizeof(m_MSSession));
	m_MSSession.byType = stMS;

	memset(&m_GDSession, 0, sizeof(m_GDSession));
	m_GDSession.byType = stGD;

	m_dwGTSessionID = 0;
	m_qwLastPingTick = 0;
	m_qwLastStatisTick = 0;
	m_eServerState = sgsInitializing;

	m_pExternalNet = pExternalNet;
	m_pInternalNet = pInternalNet;

	s_qwLastTick = GetTickCountEx();

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CGTSessionMgr::UnInit(void)
{
	LOG_CHECK_ERROR(m_FreeClientSessionList.size() == MAX_CLIENT_SESSION_COUNT - 1);
	LOG_CHECK_ERROR(m_UsedClientSessionList.IsEmpty());

	m_FreeClientSessionList.clear();
	m_UsedClientSessionList.Clear();

	LOG_CHECK_ERROR(!CheckSession());
	return TRUE;
}

CGTSessionMgr& CGTSessionMgr::GetInstance(void)
{
	return ms_Instance;
}

CLIENT_SESSION* CGTSessionMgr::NewClientSession(void)
{
	CLIENT_SESSION* pResult = NULL;

	pResult = m_FreeClientSessionList.front();
	PROCESS_ERROR(pResult);
	LOG_PROCESS_ERROR(!pResult->bConnected);

	pResult->bConnected = true;
	m_FreeClientSessionList.pop_front();
	m_UsedClientSessionList.PushRear(pResult);

Exit0:
	return pResult;
}

void CGTSessionMgr::DelClientSession(CLIENT_SESSION* pClientSession)
{
	LOG_PROCESS_ERROR(pClientSession);
	LOG_PROCESS_ERROR(!pClientSession->bConnected);

	SET_GROUP_INDEX_TO_SESSION_ID(pClientSession->dwSessionID, 0);
	CBaseList::Remove(pClientSession);
	m_FreeClientSessionList.push_back(pClientSession);

Exit0:
	return;
}

CLIENT_SESSION* CGTSessionMgr::FindClientSession(UINT32 dwSessionID)
{
	UINT32 dwSessionIndex = dwSessionID & 0xFFFF;
	PROCESS_ERROR(m_ClientSessionPool[dwSessionIndex].bConnected);

	return m_ClientSessionPool + dwSessionIndex;
Exit0:
	return NULL;
}

INT32 CGTSessionMgr::GetClientSessionCount(void)
{
	return static_cast<INT32>(MAX_CLIENT_SESSION_COUNT - 1 - m_FreeClientSessionList.size());
}

BOOL CGTSessionMgr::CloseAllClientSession(void)
{
	CLIENT_SESSION* pClientSession = (CLIENT_SESSION*)m_UsedClientSessionList.Head().pNext;
	while (pClientSession)
	{
		if (pClientSession->pSocketSession)
		{
			pClientSession->pSocketSession->Close();
			pClientSession->byShutDownType = csdtGT;
		}

		pClientSession = (CLIENT_SESSION*)pClientSession->pNext;
	}

	return TRUE;
}

BOOL CGTSessionMgr::IsAllClientSessionClosed(void)
{
	return m_UsedClientSessionList.IsEmpty();
}

BOOL CGTSessionMgr::MainLoop(void)
{
	UINT64 qwCurrentTick = GetTickCountEx();

	if (g_ServerConfig.GT.bLogMessage)
	{
		if (qwCurrentTick - s_qwLastTick > 10 * 60 * 1000)
		{
			s_qwLastTick = qwCurrentTick;
			INF("========================download================================");
			for (INT32 i = 0; i < sizeof(s_nDownMsgCount) / sizeof(s_nDownMsgCount[0]); i++)
			{
				//if (s_nDownMsgCount[i] != 0)
				if (g_szS2CMessageName[i][1] != 'n')	//"undefined s2c message"
					INF("%s\t%d\t%d\t%d", g_szS2CMessageName[i], i, s_nDownMsgCount[i], s_nDownMsgSize[i]);
			}
			memset(s_nDownMsgCount, 0, sizeof(s_nDownMsgCount));
			memset(s_nDownMsgSize, 0, sizeof(s_nDownMsgSize));

			INF("========================upload================================");
			for (INT32 i = 0; i < sizeof(s_nUpMsgCount) / sizeof(s_nUpMsgCount[0]); i++)
			{
				//if (s_nUpMsgCount[i] != 0)
				if (g_szS2CMessageName[i][1] != 'n')	//"undefined c2s message"
					INF("%s\t%d\t%d\t%d", g_szC2SMessageName[i], i, s_nUpMsgCount[i], s_nUpMsgSize[i]);
			}
			memset(s_nUpMsgCount, 0, sizeof(s_nUpMsgCount));
			memset(s_nUpMsgSize, 0, sizeof(s_nUpMsgSize));
		}
	}

	if (qwCurrentTick > m_qwLastPingTick + g_ServerConfig.Common.nServerPingInterval)
	{
		CInternalMessageHandler::GetInstance().DoAllPing();
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
	else if (m_GDSession.pSocketSession == NULL && m_GDSession.qwTimer < qwCurrentTick)
	{
#if defined(WIN32)
		INF("try to connect to GD");
		m_GDSession.pSocketSession = m_pInternalNet->Connect(inet_addr(g_szLocalAddress), g_ServerConfig.Common.dwGuardPort);
		if (m_GDSession.pSocketSession)
			m_GDSession.pSocketSession->SetUserData(&m_GDSession);
#endif
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
		m_DBSession.dwAddr && m_dwGTSessionID != 0 &&
		m_DBSession.qwTimer < qwCurrentTick &&
		CGTSessionMgr::GetInstance().GetServerState() != sgsClosing)
	{
		INF("try to connect to DB");
		m_DBSession.pSocketSession = m_pInternalNet->Connect(m_DBSession.dwAddr, m_DBSession.wPort);
		if (m_DBSession.pSocketSession)
			m_DBSession.pSocketSession->SetUserData(&m_DBSession);
	}

	if (m_LSSession.bConnected && m_LSSession.pSocketSession)
	{
		if (m_LSSession.qwTimer < qwCurrentTick)
		{
			CRI("LS ping time out");
			m_LSSession.pSocketSession->Close();
			m_LSSession.qwTimer = 0xFFFFFFFF;
		}
	}
	else if (m_LSSession.pSocketSession == NULL &&
		m_LSSession.dwAddr && m_dwGTSessionID != 0 &&
		m_LSSession.qwTimer < qwCurrentTick &&
		CGTSessionMgr::GetInstance().GetServerState() != sgsClosing)
	{
		INF("try to connect to LS");
		m_LSSession.pSocketSession = m_pInternalNet->Connect(m_LSSession.dwAddr, m_LSSession.wPort);
		if (m_LSSession.pSocketSession)
			m_LSSession.pSocketSession->SetUserData(&m_LSSession);
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
		CGTSessionMgr::GetInstance().GetServerState() != sgsClosing)
	{
		INF("try to connect to MS");

		UINT32 dwAddr = inet_addr(g_ServerConfig.MS.szAddress);
		if (dwAddr == 0)
			dwAddr = inet_addr(g_szLocalAddress);

		m_MSSession.pSocketSession = m_pInternalNet->Connect(dwAddr, g_ServerConfig.MS.dwGTPort);
		if (m_MSSession.pSocketSession)
			m_MSSession.pSocketSession->SetUserData(&m_MSSession);
	}

	for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
	{
		GS_SESSION* pGSSession = m_GSSession + nIndex;
		if (pGSSession->pSocketSession)
		{
			if (pGSSession->qwTimer < qwCurrentTick)
			{
				CRI("GS %d ping time out", pGSSession->dwSessionID);
				pGSSession->pSocketSession->Close();
				pGSSession->qwTimer = 0xFFFFFFFF;
			}
		}
	}

	CLIENT_SESSION* pClientSession = (CLIENT_SESSION*)m_UsedClientSessionList.Head().pNext;
	while (pClientSession)
	{
		if (pClientSession->qwTimer < qwCurrentTick)
		{
			if (pClientSession->pSocketSession)
			{
				CExternalMessageHandler::GetInstance().DoErrorNotify(pClientSession->dwSessionID, errDisconnectTimeOut, 0, 0);
				CRI("client %08x ping time out, clientSession eState[%d]", pClientSession->dwSessionID, pClientSession->eState);
				pClientSession->pSocketSession->Close();
				pClientSession->byShutDownType = csdtTimeout;
				pClientSession->qwTimer = 0xFFFFFFFF;
			}
		}
		pClientSession = (CLIENT_SESSION*)pClientSession->pNext;
	}

	return TRUE;
}

BOOL CGTSessionMgr::CheckSession()
{
	PROCESS_SUCCESS(m_MSSession.bConnected);
	PROCESS_SUCCESS(m_DBSession.bConnected);
	PROCESS_SUCCESS(m_LSSession.bConnected);

	for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
	{
		GS_SESSION* pGSSession = m_GSSession + nIndex;
		PROCESS_SUCCESS(pGSSession->pSocketSession);
	}

	return FALSE;
Exit1:
	return TRUE;
}

BOOL CGTSessionMgr::CloseAllSession()
{
	if (m_MSSession.bConnected && m_MSSession.pSocketSession)
		m_MSSession.pSocketSession->Close();

	if (m_DBSession.bConnected && m_DBSession.pSocketSession)
		m_DBSession.pSocketSession->Close();

	if (m_LSSession.bConnected && m_LSSession.pSocketSession)
		m_LSSession.pSocketSession->Close();

	for (INT32 nIndex = 1; nIndex < MAX_GS_SESSION_COUNT; nIndex++)
	{
		GS_SESSION* pGSSession = m_GSSession + nIndex;
		if (pGSSession->pSocketSession)
			pGSSession->pSocketSession->Close();
	}

	return TRUE;
}