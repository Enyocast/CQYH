#include "stdafx.h"
#include "session_mgr.h"

//#include "sdtime.h"
#include "net.h"

#include "message_handler.h"
#include "maintaintool.h"

CSessionMgr CSessionMgr::ms_Instance;
CSessionMgr::CSessionMgr()
{
    m_pNet = NULL;
}

CSessionMgr::~CSessionMgr()
{
    UnInit();
}

BOOL CSessionMgr::Init(INet* pNet)
{
    LOG_PROCESS_ERROR(pNet);
    m_dwLastPingTick = 0;

    m_pNet = pNet;

	return Reload();
Exit0:
    return FALSE;
}

BOOL CSessionMgr::Reload()
{
	CloseAllSession();

	memset(&m_RemoteGDSession, 0, sizeof(m_RemoteGDSession));
	for (INT32 i = 1; i < MAX_AREA_COUNT; ++i)
	{
		if (g_MTConfig.AreaConfig[i].areaID > 0)
		{
			LOG_PROCESS_ERROR(g_MTConfig.AreaConfig[i].areaID == i);
			for (INT32 j = 1; j < MAX_GUARD_COUNT_PER_AREA; ++j)
			{
				if (g_MTConfig.AreaConfig[i].guardList[j].szAddress[0] == 0)
				{
					break;
				}
				else
				{
					UINT32 dwTargetIP = inet_addr(g_MTConfig.AreaConfig[i].guardList[j].szAddress);
					LOG_PROCESS_ERROR(dwTargetIP != 0);

					m_RemoteGDSession[i][j].dwIp = dwTargetIP;

					m_RemoteGDSession[i][j].wPort = g_MTConfig.AreaConfig[i].guardList[j].nPort;
					m_RemoteGDSession[i][j].dwArea = g_MTConfig.AreaConfig[i].areaID;

					m_RemoteGDSession[i][j].pSocketSession = NULL;
					m_RemoteGDSession[i][j].dwTimer = 0;

					LOG_PROCESS_ERROR(m_RemoteGDSession[i][j].poStatisInfo == NULL);
					m_RemoteGDSession[i][j].poStatisInfo = new stProcessStatisInfo;
					LOG_PROCESS_ERROR(m_RemoteGDSession[i][j].poStatisInfo);
					memset(m_RemoteGDSession[i][j].poStatisInfo, 0, sizeof(stProcessStatisInfo));

					memset(m_RemoteGDSession[i][j].lstProcess, 0, sizeof(m_RemoteGDSession[i][j].lstProcess));
				}
			}
		}
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CSessionMgr::UnInit(void)
{
    INT32 nRetCode = 0;

    return TRUE;
}

CSessionMgr& CSessionMgr::GetInstance(void)
{
    return ms_Instance;
}

SRemoteGuardSession* CSessionMgr::GetRemoteGDSession(INT32 nAreaID, UINT32 dwIp)
{
	LOG_PROCESS_ERROR( nAreaID > 0 && nAreaID < MAX_AREA_COUNT );

	if(g_MTConfig.AreaConfig[nAreaID].areaID > 0)
	{
		for(INT32 j = 1; j < MAX_GUARD_COUNT_PER_AREA; ++j)
		{
			if(m_RemoteGDSession[nAreaID][j].dwIp == dwIp)
				return &m_RemoteGDSession[nAreaID][j];
		}
	}

Exit0:
	return NULL;
}

BOOL CSessionMgr::MainLoop(void)
{
	UINT32 dwCurrentTick = GetTickCount();

    if (dwCurrentTick > m_dwLastPingTick + g_MTConfig.nServerPingInterval)
    {
		//CMessageHandler::GetInstance().DoAllPing();
		DoAllPing();

        m_dwLastPingTick = dwCurrentTick;
    }

	for(INT32 nAreaID = 1; nAreaID < MAX_AREA_COUNT; ++nAreaID)
	{
		for(INT32 nGuardIndex = 1; nGuardIndex < MAX_GUARD_COUNT_PER_AREA; ++nGuardIndex)
		{
			SRemoteGuardSession& rSession = m_RemoteGDSession[nAreaID][nGuardIndex];
			if (rSession.pSocketSession && rSession.bConnected && rSession.dwTimer < dwCurrentTick)
			{
				struct in_addr addr;
				addr.s_addr = rSession.dwIp;
				CRI("remote guard (%s) ping time out", inet_ntoa(addr));
				
				rSession.pSocketSession->Close();
				rSession.dwTimer = 0xFFFFFFFF;
			}
			else if(rSession.dwIp > 0 && rSession.dwTimer < dwCurrentTick && rSession.pSocketSession == NULL)
			{
                if ( MaintainTool::GetInstance().CheckAreaExpanded( nAreaID ))
                {
                    struct in_addr addr;
                    addr.s_addr = rSession.dwIp;
                    CRI("try to connect guard (%s)", inet_ntoa(addr));

                    rSession.pSocketSession = m_pNet->Connect(rSession.dwIp, rSession.wPort);
                    LOG_PROCESS_ERROR(rSession.pSocketSession);

                    rSession.pSocketSession->SetUserData((VOID*)&rSession);
                    rSession.dwTimer = GetTickCount() + g_MTConfig.nPingTimeout;

                    MaintainTool::GetInstance().UpdateGuardConnectInfo(&rSession, emctConnecting, NULL);
                }
			}
		}
		
	}

Exit0:
    return TRUE;
}

BOOL CSessionMgr::CloseAllSession()
{
	INT32 nRetCode = 0;

	CRI("close all guard session");
	for(INT32 i = 1; i < MAX_AREA_COUNT; ++i)
	{
		for(INT32 j = 1; j < MAX_GUARD_COUNT_PER_AREA; ++j)
		{
			SRemoteGuardSession& rSession = m_RemoteGDSession[i][j];
			if (rSession.pSocketSession)
			{
				struct in_addr addr;
				addr.s_addr = rSession.dwIp;
				CRI("close guard (%s) session", inet_ntoa(addr));

				rSession.pSocketSession->Close();
				rSession.dwTimer = 0xFFFFFFFF;
			}
		}
	}
	
	return TRUE;
Exit0:
	return FALSE;
}

BOOL CSessionMgr::DoAllPing()
{
	INT32 nRetCode = 0;
	PACKET_BUFFER* pMsg = NULL;
	CSessionMgr &rSessionMgr = CSessionMgr::GetInstance();

	for (INT32 i = 1; i < MAX_AREA_COUNT; ++i)
	{
		for (INT32 j = 1; j < MAX_GUARD_COUNT_PER_AREA; ++j)
		{
			SRemoteGuardSession* pRemoteGuardSession = &m_RemoteGDSession[i][j];
			if (pRemoteGuardSession && pRemoteGuardSession->pSocketSession && pRemoteGuardSession->bConnected)
			{
				nRetCode = CMTMessageHandler::GetInstance().DoPing(pRemoteGuardSession);
				LOG_CHECK_ERROR(nRetCode);
			}
		}
	}

	return TRUE;
}

