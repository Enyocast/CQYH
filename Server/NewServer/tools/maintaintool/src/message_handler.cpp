#include "stdafx.h"
//#include "sdtime.h"

#include "common_message.h"

#include <QtWidgets/QMessageBox>

#include "session_mgr.h"
#include "message_handler.h"
#include "maintaintool.h"
#include "transmit_file_mgr.h"
#include "maintain_tool_version.h"

using namespace InternalMessage;
CMTMessageHandler CMTMessageHandler::ms_Instance;

void CMTMessageHandler::OnAccepted(ISocketAcceptor* pSocketAcceptor, ISocketSession* pSocketSession)
{
	LOG_PROCESS_ERROR(pSocketSession);

    return;
Exit0:
    if(pSocketSession)
        pSocketSession->Close();
    return;
}

void CMTMessageHandler::OnConnected(ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	UINT32 dwIP = 0;
	UINT16 wPort = 0;
	struct in_addr addr;
	SRemoteGuardSession* pRemoteGuardSession = NULL;

	LOG_PROCESS_ERROR(pSocketSession);
	
	pRemoteGuardSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pRemoteGuardSession);
	LOG_PROCESS_ERROR(pRemoteGuardSession->pSocketSession == pSocketSession);

	//nRetCode = pSocketSession->GetRemoteAddress(dwIP, wPort);
	//LOG_PROCESS_ERROR( nRetCode );
	//pRemoteGuardSession->dwIp = dwIP;
	
	memset(pRemoteGuardSession->lstProcess, 0, sizeof(pRemoteGuardSession->lstProcess));
	pRemoteGuardSession->dwTimer = GetTickCount() + g_MTConfig.nPingTimeout;
	pRemoteGuardSession->bConnected = TRUE;

	addr.s_addr = pRemoteGuardSession->dwIp;
	INF("an remote guard (%s) is connected", inet_ntoa(addr));

	nRetCode = MaintainTool::GetInstance().UpdateGuardConnectInfo(pRemoteGuardSession, emctConnected, NULL);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = CMTMessageHandler::GetInstance().DoGDRegristerGD(pRemoteGuardSession, MaintainTool::GetInstance().GetUserName(), MaintainTool::GetInstance().GetPassword());
	LOG_PROCESS_ERROR(nRetCode);

    return;
Exit0:
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CMTMessageHandler::OnRecv(ISocketSession* pSocketSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
    MESSAGE_HEADER* pHeader = (MESSAGE_HEADER*)pPacketBuffer;
    LOG_PROCESS_ERROR(pHeader);

    LOG_PROCESS_ERROR(pSocketSession);
    LOG_PROCESS_ERROR(pPacketBuffer);

    LOG_PROCESS_ERROR(m_RemoteGuardMessageFuncList[pHeader->wMsg]);

    (this->*m_RemoteGuardMessageFuncList[pHeader->wMsg])(pPacketBuffer, dwSize, pSocketSession);

	if (pPacketBuffer)
		m_pPacketAllocator->Free(pPacketBuffer);
    return;
Exit0:
    CRI("unknown internal message id %d size %d", pHeader->wMsg, dwSize);
    if (pPacketBuffer)
        m_pPacketAllocator->Free(pPacketBuffer);
    if (pSocketSession)
        pSocketSession->Close();

    return;
}

void CMTMessageHandler::OnDisconnected(ISocketSession* pSocketSession, BOOL bRemoteShutdown)
{
    INT32 nRetCode = 0;
    SRemoteGuardSession* pRemoteGuardSession = NULL;

    LOG_PROCESS_ERROR(pSocketSession);

    pRemoteGuardSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pRemoteGuardSession);
	LOG_PROCESS_ERROR(pRemoteGuardSession->pSocketSession == pSocketSession);

    struct in_addr addr;
    addr.s_addr = pRemoteGuardSession->dwIp;
    INF("Guard %s:%d disconnected", inet_ntoa(addr), pRemoteGuardSession->wPort);

	pRemoteGuardSession->pSocketSession->SetUserData(NULL);

	pRemoteGuardSession->pSocketSession = NULL;
	pRemoteGuardSession->bConnected = FALSE;
	pRemoteGuardSession->dwTimer = GetTickCount() + g_MTConfig.nReconnectTime;

	for (INT32 i = 0; i < MAX_REMOTE_SESSION_COUNT; ++i)
	{
		if (pRemoteGuardSession->lstProcess[i].poHibernateStatisFileHandle)
		{
			INF("fclose hibernate file for %s-%d=%d@%s", 
				pRemoteGuardSession->lstProcess[i].byType, pRemoteGuardSession->lstProcess[i].dwSessionID,
				pRemoteGuardSession->lstProcess[i].dwProcessID, inet_ntoa(addr));
			fclose(pRemoteGuardSession->lstProcess[i].poHibernateStatisFileHandle);
			pRemoteGuardSession->lstProcess[i].poHibernateStatisFileHandle = NULL;
		}
	}
	memset(pRemoteGuardSession->lstProcess, 0, sizeof(pRemoteGuardSession->lstProcess));

	nRetCode = MaintainTool::GetInstance().UpdateGuardConnectInfo(pRemoteGuardSession, emctUnConnect, NULL);
	LOG_PROCESS_ERROR(nRetCode);

    CTransmitFileMgr::GetInstance().StopSending(pRemoteGuardSession->dwArea, pRemoteGuardSession->dwIp);
    return;
Exit0:
    return;
}

CMTMessageHandler::CMTMessageHandler()
{
    m_pNet = NULL;
    m_pPacketAllocator = NULL;
}

CMTMessageHandler::~CMTMessageHandler()
{
    UnInit();
}

BOOL CMTMessageHandler::Init(INet* pNet, IPacketAllocator* pPacketAllocator)
{
    LOG_PROCESS_ERROR(pNet);
    LOG_PROCESS_ERROR(pPacketAllocator);

    m_pNet = pNet;
    m_pPacketAllocator = pPacketAllocator;

    //All
    //////////////////////////////////////////////////////////////////////////////////////
    m_RemoteGuardMessageFuncList[a2a_ping] = &CMTMessageHandler::OnAllPing;
	m_RemoteGuardMessageFuncList[u2n_regrister_ack] = &CMTMessageHandler::OnGDRegristerAck;
	m_RemoteGuardMessageFuncList[u2n_sync_processes_summary] = &CMTMessageHandler::OnGDSyncProcessSummary;
	m_RemoteGuardMessageFuncList[n2u_update_process_info] = &CMTMessageHandler::OnGDUpdateProcess;
	m_RemoteGuardMessageFuncList[u2n_exec_cmd_ack] = &CMTMessageHandler::OnGDExecCmdAck;
    m_RemoteGuardMessageFuncList[u2n_send_files_ack] = &CMTMessageHandler::OnGDSendFilesAck;
	m_RemoteGuardMessageFuncList[u2n_deploy_server_version_ack] = &CMTMessageHandler::OnGDDeployServerVersionAck;
	m_RemoteGuardMessageFuncList[u2n_hot_update_patch_ack] = &CMTMessageHandler::OnGDHotUpdatePatchAck;
	m_RemoteGuardMessageFuncList[u2n_update_statis_info] = &CMTMessageHandler::OnGDUpdateStatisInfo;
	m_RemoteGuardMessageFuncList[u2n_notify] = &CMTMessageHandler::OnGDNotify;
	m_RemoteGuardMessageFuncList[u2n_error] = &CMTMessageHandler::OnGDError;
    /////////////////////////////////////////////////////////////////////////////////////
    return TRUE;
Exit0:
    return FALSE;
}

BOOL CMTMessageHandler::UnInit(void)
{
    return TRUE;
}

CMTMessageHandler& CMTMessageHandler::GetInstance(void)
{
    return ms_Instance;
}

//BOOL CMessageHandler::_SendRemoteGD(UINT32 dwIp, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
//{
//	INT32 nRetCode = 0;
//
//	SRemoteGuardSession* pRemoteGDSession = CSessionMgr::GetInstance().GetRemoteGDSession(dwIp);
//	LOG_PROCESS_ERROR(pRemoteGDSession);
//	LOG_PROCESS_ERROR(pRemoteGDSession->pSocketSession&& pRemoteGDSession->bConnected);
//
//	nRetCode = pRemoteGDSession->pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
//	LOG_PROCESS_ERROR(nRetCode == dwSize);
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}

BOOL CMTMessageHandler::_SendRemoteGD(SRemoteGuardSession* pRemoteGDSession, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, INT32 nOffset)
{
	INT32 nRetCode = 0;

	LOG_PROCESS_ERROR(pRemoteGDSession);
	LOG_PROCESS_ERROR(pRemoteGDSession->pSocketSession&& pRemoteGDSession->bConnected);

	nRetCode = pRemoteGDSession->pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, nOffset);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMTMessageHandler::DoPing(SRemoteGuardSession* pRemoteGDSession)
{
    INT32 nRetCode = 0;
    A2A_PING* pMsg = NULL;
    CSessionMgr &rSessionMgr = CSessionMgr::GetInstance();

	pMsg = (A2A_PING*)m_pPacketAllocator->Alloc(sizeof(A2A_PING));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = a2a_ping;
	nRetCode = _SendRemoteGD(pRemoteGDSession, (PACKET_BUFFER*)pMsg, sizeof(A2A_PING));
	LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}


BOOL CMTMessageHandler::DoGDRegristerGD(SRemoteGuardSession* pRemoteGDSession, const char* pcszUserName, const char* pcszPassword)
{
	INT32 nRetCode = 0;
	N2U_REGRISTER* pMsg = NULL;
	CSessionMgr &rSessionMgr = CSessionMgr::GetInstance();

	pMsg = (N2U_REGRISTER*)m_pPacketAllocator->Alloc(sizeof(N2U_REGRISTER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = n2u_regrister;
	strxcpy(pMsg->szName, pcszUserName, 32);
	strxcpy(pMsg->szPwd, pcszPassword, 32);

	nRetCode = _SendRemoteGD(pRemoteGDSession, (PACKET_BUFFER*)pMsg, sizeof(N2U_REGRISTER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}


BOOL CMTMessageHandler::DoGDExecCmd(INT32 nAreaID, UINT32 dwIP, const char* pcszCmd)
{
	INT32 nRetCode = 0;
	N2U_UPDATE_CMD* pMsg = NULL;
	SRemoteGuardSession* pRemoteGDSession = NULL;

	INT32 nSize = sizeof(N2U_UPDATE_CMD) + strlen(pcszCmd) + 1;

	CSessionMgr &rSessionMgr = CSessionMgr::GetInstance();

	pMsg = (N2U_UPDATE_CMD*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = n2u_exec_cmd;
	strxcpy(pMsg->szCmd, pcszCmd, strlen(pcszCmd) + 1);

	pRemoteGDSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIP);
	LOG_PROCESS_ERROR(pRemoteGDSession);

	nRetCode = _SendRemoteGD(pRemoteGDSession, (PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CMTMessageHandler::DoGDSendFiles(INT32 nAreaID, UINT32 dwIP, BOOL nFileType,
								  const char* szFileName,
                                  UINT16 wBufferIndex, UINT16 wBufferTotal,  
                                  UINT16 wBufferSize, char szBuffer[],
                                  UINT16 wFileIndex, UINT16 wFileTotal)
{
    INT32 nRetCode = 0;
	N2U_SEND_FILES* pMsg = NULL;
	SRemoteGuardSession* pRemoteGDSession = NULL;
    CSessionMgr &rSessionMgr = CSessionMgr::GetInstance();

    pMsg = (N2U_SEND_FILES*)m_pPacketAllocator->Alloc(sizeof(N2U_SEND_FILES));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = n2u_send_files;
	pMsg->nFileType = nFileType;
    strxcpy(pMsg->szFileName, szFileName, sizeof(pMsg->szFileName) );
    pMsg->wBufferIndex = wBufferIndex;
    pMsg->wBufferTotal = wBufferTotal;
    pMsg->wFileIndex = wFileIndex;
    pMsg->wFileTotal = wFileTotal;
    pMsg->wBufferSize = wBufferSize;
    memcpy(pMsg->szBuffer, szBuffer, wBufferSize);

	pRemoteGDSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIP);
	LOG_PROCESS_ERROR(pRemoteGDSession);

	nRetCode = _SendRemoteGD(pRemoteGDSession, (PACKET_BUFFER*)pMsg, sizeof(N2U_SEND_FILES));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CMTMessageHandler::DoGDDeployServerVersion(INT32 nAreaID, UINT32 dwIP, const char* pcszVersion)
{
	INT32 nRetCode = 0;
	N2U_DEPLOY_SERVER_VERSION* pMsg = NULL;
	SRemoteGuardSession* pRemoteGDSession = NULL;
	CSessionMgr &rSessionMgr = CSessionMgr::GetInstance();

	pMsg = (N2U_DEPLOY_SERVER_VERSION*)m_pPacketAllocator->Alloc(sizeof(N2U_DEPLOY_SERVER_VERSION));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = n2u_deploy_server_version;
	strxcpy(pMsg->szVersion, pcszVersion, sizeof(pMsg->szVersion));

	pRemoteGDSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIP);
	LOG_PROCESS_ERROR(pRemoteGDSession);

	nRetCode = _SendRemoteGD(pRemoteGDSession, (PACKET_BUFFER*)pMsg, sizeof(N2U_DEPLOY_SERVER_VERSION));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CMTMessageHandler::DoGDHotUpdatePatch(INT32 nAreaID, UINT32 dwIP, const char* pcszPatch)
{
	INT32 nRetCode = 0;
	N2U_HOT_UPDATE_PATCH* pMsg = NULL;
	SRemoteGuardSession* pRemoteGDSession = NULL;
	CSessionMgr &rSessionMgr = CSessionMgr::GetInstance();

	pMsg = (N2U_HOT_UPDATE_PATCH*)m_pPacketAllocator->Alloc(sizeof(N2U_HOT_UPDATE_PATCH));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = n2u_hot_update_patch;
	strxcpy(pMsg->szPatch, pcszPatch, sizeof(pMsg->szPatch));

	pRemoteGDSession = CSessionMgr::GetInstance().GetRemoteGDSession(nAreaID, dwIP);
	LOG_PROCESS_ERROR(pRemoteGDSession);

	nRetCode = _SendRemoteGD(pRemoteGDSession, (PACKET_BUFFER*)pMsg, sizeof(N2U_HOT_UPDATE_PATCH));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

void CMTMessageHandler::OnAllPing(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
    if(pSession)
        pSession->dwTimer = GetTickCount() + g_MTConfig.nPingTimeout;

    return;
}

void CMTMessageHandler::OnGDRegristerAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	char szLog[256] = {0};
    U2N_REGRISTER_ACK* pMsg = (U2N_REGRISTER_ACK*)pPacketBuffer;
    LOG_PROCESS_ERROR( pSocketSession );

	struct in_addr stRemoteAddr = { 0 };
	UINT32 dwRemoteAddr = 0;
	UINT16 wRemotePort = 0;
	nRetCode = pSocketSession->GetRemoteAddress(dwRemoteAddr, wRemotePort);
	LOG_CHECK_ERROR(nRetCode);
	stRemoteAddr.s_addr = dwRemoteAddr;

	if (pMsg->nMsgVersion != MAINTAIN_TOOLS_MSG_VERSION)
	{
		snprintf(szLog, sizeof(szLog), "guard on %s msg version don't match, expecting %d, but got %d", inet_ntoa(stRemoteAddr), MAINTAIN_TOOLS_MSG_VERSION, pMsg->nMsgVersion);
		INF(szLog);
		QMessageBox msgBox;
		msgBox.setText(szLog);
		msgBox.exec();

		CRI(szLog);
		MaintainTool::GetInstance().UpdateNotifyInfo(szLog);

		pSocketSession->Close();

		LOG_PROCESS_ERROR(FALSE);
	}
	if (strcmp(pMsg->szBuildVersion, MAINTAIN_TOOLS_BUILD_VERSION) != 0)
	{
		snprintf(szLog, sizeof(szLog), "guard on %s build version don't match, expecting %s, but got %s", inet_ntoa(stRemoteAddr), MAINTAIN_TOOLS_BUILD_VERSION, pMsg->szBuildVersion);
		INF(szLog);
		//QMessageBox msgBox;
		//msgBox.setText(szLog);
		//msgBox.exec();

		CRI(szLog);
		//MaintainTool::GetInstance().UpdateNotifyInfo(szLog);

		//pSocketSession->Close();
		//LOG_PROCESS_ERROR(FALSE);
	}

    if ( pMsg->nErrorCode == errSuccess )
    {
        SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
        if(pSession)
		{
			nRetCode = strlen(pMsg->szVersion);
			for (int i = 0; i < nRetCode; ++i)
			{
				if (pMsg->szVersion[i] == '\n' || pMsg->szVersion[i] == '\r' || pMsg->szVersion[i] == ' ')
				{
					pMsg->szVersion[i] = '\0';
					break;
				}
			}

            nRetCode = MaintainTool::GetInstance().SetAreaVersion(pSession->dwArea, pMsg->szVersion );
            LOG_PROCESS_ERROR(nRetCode);

            nRetCode = MaintainTool::GetInstance().UpdateGuardConnectInfo(pSession, emctNormal, NULL);
            LOG_PROCESS_ERROR(nRetCode);
        }
    }
	else if (pMsg->nErrorCode == errLoginRepeat )
	{
		INF("kicked off! %s", pMsg->szVersion);

		QMessageBox msgBox;
		msgBox.setText(pMsg->szVersion);
		msgBox.exec();
	}
    else
    {
        struct in_addr stRemoteAddr = {0}; 
        UINT32 dwRemoteAddr = 0; 
        UINT16 wRemotePort = 0; 
        nRetCode = pSocketSession->GetRemoteAddress(dwRemoteAddr, wRemotePort);
        LOG_CHECK_ERROR( nRetCode ); 
        stRemoteAddr.s_addr = dwRemoteAddr;
        
        INF("register %s failed!: reason %s", inet_ntoa(stRemoteAddr), pMsg->szVersion );
    }

Exit0:
	return;
}

void CMTMessageHandler::OnGDSyncProcessSummary(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	U2N_SYNC_DEFAULT_INFO* pMsg = (U2N_SYNC_DEFAULT_INFO*)pPacketBuffer;

	SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
	if(pSession)
	{
		nRetCode = MaintainTool::GetInstance().UpdateGuardConnectInfo(pSession, emctNormal, pMsg->nDefaultCount );
		LOG_PROCESS_ERROR(nRetCode);
	}
Exit0:
	return;
}

void CMTMessageHandler::OnGDUpdateProcess(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	BOOL bDone = FALSE;
	SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
	N2U_UPDATE_SESSION* pMsg = (N2U_UPDATE_SESSION*)pPacketBuffer;

	if(pSession)
	{
		for (INT32 i = 0; i < MAX_REMOTE_SESSION_COUNT; ++i)
		{
			if (pSession->lstProcess[i].dwProcessID == pMsg->dwProcessID)
			{
				if (pMsg->nState != epsDestroy)
				{
					pSession->lstProcess[i].bAuto = pMsg->bAuto;
					pSession->lstProcess[i].byType = pMsg->byType;
					pSession->lstProcess[i].nState = pMsg->nState;
					pSession->lstProcess[i].dwProcessID = pMsg->dwProcessID;
					pSession->lstProcess[i].dwSessionID = pMsg->dwSessionID;
				}
				else
				{
					pSession->lstProcess[i].dwProcessID = 0;
				}

				bDone = TRUE;
				break;
			}
		}


		if (!bDone && pMsg->nState != epsDestroy)
		{
			for(INT32 i = 0; i < MAX_REMOTE_SESSION_COUNT; ++i)
			{
				if(pSession->lstProcess[i].dwProcessID == 0)
				{
					pSession->lstProcess[i].bAuto = pMsg->bAuto;
					pSession->lstProcess[i].byType = pMsg->byType;
					pSession->lstProcess[i].nState = pMsg->nState;
					pSession->lstProcess[i].dwProcessID = pMsg->dwProcessID;
					pSession->lstProcess[i].dwSessionID = pMsg->dwSessionID;
					break;
				}
			}
		}
	}

	nRetCode = MaintainTool::GetInstance().UpdateGuardProcessesInfo();
	LOG_CHECK_ERROR(nRetCode);

Exit0:
	return;
}

void CMTMessageHandler::OnGDNotify(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	UINT32	dwIP = 0;
	UINT16  wPort = 0;

	SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->poStatisInfo);

	U2N_NOTIFY* pMsg = (U2N_NOTIFY*)pPacketBuffer;
	LOG_PROCESS_ERROR(pMsg);

	nRetCode = pSocketSession->GetRemoteAddress(dwIP, wPort);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = MaintainTool::GetInstance().UpdateNotifyInfo(dwIP, pMsg->bySvrType, pMsg->bySvrID, pMsg->byLevel, pMsg->nErrorCode, pMsg->szContent);
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CMTMessageHandler::OnGDError(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	UINT32 dwRemoteAddr = 0;
	UINT16 wRemotePort = 0;
	struct in_addr stRemoteAddr = { 0 };

	SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pSession);
	LOG_PROCESS_ERROR(pSession->poStatisInfo);

	U2N_ERROR* pMsg = (U2N_ERROR*)pPacketBuffer;
	LOG_PROCESS_ERROR(pMsg);

	nRetCode = pSocketSession->GetRemoteAddress(dwRemoteAddr, wRemotePort);
	LOG_CHECK_ERROR(nRetCode);
	stRemoteAddr.s_addr = dwRemoteAddr;

	nRetCode = CRI("error from guard on %s: %s",inet_ntoa(stRemoteAddr), pMsg->szErrorInfo);
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	return;
}
void CMTMessageHandler::OnGDUpdateStatisInfo(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	INT32 nProcessIndex = -1;

    SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR( pSession );
    LOG_PROCESS_ERROR( pSession->poStatisInfo );

    U2N_UPDATE_STATIS_INFO* pMsg = (U2N_UPDATE_STATIS_INFO*)pPacketBuffer;
    LOG_PROCESS_ERROR( pMsg );

    //LOG_PROCESS_ERROR( pMsg->bConnected == TRUE );

    memcpy( pSession->poStatisInfo->ProcessInfo, pMsg->oStatisInfo.ProcessInfo, sizeof(pSession->poStatisInfo->ProcessInfo));

    memcpy( &pSession->poStatisInfo->oAccumuStatis[pSession->poStatisInfo->nAccumuIndex], &pMsg->oStatisInfo, 
        sizeof(pSession->poStatisInfo->oAccumuStatis[pSession->poStatisInfo->nAccumuIndex]));
    pSession->poStatisInfo->nAccumuIndex = (pSession->poStatisInfo->nAccumuIndex + 1) % ACCUMU_MAX_TIMES;

	nRetCode = MaintainTool::GetInstance().UpdateGuardStatisInfo(pSession->dwArea, pSession->dwIp);
    LOG_CHECK_ERROR(nRetCode);

	for (INT32 s = 0; s < MAX_REMOTE_SESSION_COUNT; ++s)
	{
		//if (pSession->lstRemoteSession[s].dwProcessID > 0)
		if (pSession->lstProcess[s].poHibernateStatisFileHandle)
		{
			LOG_PROCESS_ERROR(pSession->lstProcess[s].dwProcessID > 0);

			for (INT32 p = 0; p < MAX_STATIS_PROCESS_COUNT; ++p)
			{
				if (pSession->lstProcess[s].dwProcessID == pSession->poStatisInfo->ProcessInfo[p].dwProcessID)
				{
					nProcessIndex = p;
					break;
				}
			}
			PROCESS_ERROR(nProcessIndex > -1);

			MaintainTool::GetInstance().ProcessHibernateGuardStatisInfoByIp(&pSession->poStatisInfo->ProcessInfo[nProcessIndex], &pSession->lstProcess[s]);
		}
	}
	return;
Exit0:
    return;
}

void CMTMessageHandler::OnGDExecCmdAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	UINT32	dwIP = 0;
	UINT16  wPort = 0;

	U2N_UPDATE_CMD_ACK* pMsg = (U2N_UPDATE_CMD_ACK*)pPacketBuffer;

	SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
	LOG_PROCESS_ERROR(pSession);

	nRetCode = pSocketSession->GetRemoteAddress(dwIP, wPort);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = MaintainTool::GetInstance().UpdateCmdResult(dwIP, pMsg->nErrorCode, pMsg->szResult);
	LOG_PROCESS_ERROR(nRetCode);
Exit0:
	return;
}

void CMTMessageHandler::OnGDDeployServerVersionAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
	U2N_DEPLOY_SERVER_VERSION_ACK* pMsg = (U2N_DEPLOY_SERVER_VERSION_ACK*)pPacketBuffer;
	
	LOG_PROCESS_ERROR(pSession);
	
	nRetCode = MaintainTool::GetInstance().DeployVersionResultByIp(pSession->dwArea, 
		pSession->dwIp, pMsg->szInfo, pMsg->nErrorCode);
	PROCESS_ERROR(nRetCode);
	
	return;

Exit0:
	return;
}

void CMTMessageHandler::OnGDHotUpdatePatchAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
	INT32 nRetCode = 0;
	SRemoteGuardSession* pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
	U2N_HOT_UPDATE_PATCH_ACK* pMsg = (U2N_HOT_UPDATE_PATCH_ACK*)pPacketBuffer;

	LOG_PROCESS_ERROR(pSession);

	nRetCode = MaintainTool::GetInstance().HotUpdatePatchResultByIp(pSession->dwArea,
		pSession->dwIp, pMsg->szInfo, pMsg->nErrorCode);
	PROCESS_ERROR(nRetCode);

	return;

Exit0:
	return;
}

void CMTMessageHandler::OnGDSendFilesAck(PACKET_BUFFER* pPacketBuffer, UINT32 dwSize, ISocketSession* pSocketSession)
{
    INT32 nRetCode = 0;

    U2N_SEND_FILES_ACK* pMsg = NULL;
    SRemoteGuardSession* pSession = NULL;
    STransmitFileCtx*	pCurBaseSend = NULL;

    struct in_addr stRemoteAddr = {0}; 
    //UINT32 dwRemoteAddr = 0; 
    //UINT16 wRemotePort = 0; 
    //LOG_PROCESS_ERROR( pSocketSession );
    //nRetCode = pSocketSession->GetRemoteAddress(dwRemoteAddr, wRemotePort);
    //LOG_CHECK_ERROR( nRetCode ); 
    //stRemoteAddr.s_addr = dwRemoteAddr;

    pMsg = (U2N_SEND_FILES_ACK*)pPacketBuffer;
    pSession = (SRemoteGuardSession*)pSocketSession->GetUserData();
    LOG_PROCESS_ERROR(pSession);

	pCurBaseSend = CTransmitFileMgr::GetInstance().GetPendingSending(pSession->dwArea, pSession->dwIp);
    LOG_PROCESS_ERROR(pCurBaseSend);

    LOG_PROCESS_ERROR(pMsg->nErrorCode == errSuccess);
    LOG_PROCESS_ERROR(pCurBaseSend->wBufferIndex == pCurBaseSend->wBufferTotal);

    //strxcpy(szVersion, pCurBaseSend->szVersionName, sizeof(szVersion));

    if (pMsg->wBufferIndex + 1 == pMsg->wBufferTotal &&
        pMsg->wFileIndex + 1 == pMsg->wFileTotal )
    {
        CTransmitFileMgr::GetInstance().StopSending( pSession->dwArea, pSession->dwIp );

        MaintainTool::GetInstance().UpdateGuardSendProgress(pCurBaseSend->nAreaID, pCurBaseSend->dwIp, 101);
    }

    stRemoteAddr.s_addr = pCurBaseSend->dwIp;
    INF("send file:%s to ip:%s success", pMsg->szFileName, inet_ntoa(stRemoteAddr));

    return;
Exit0:

    if(pCurBaseSend)
    {
        stRemoteAddr.s_addr = pCurBaseSend->dwIp;
        INF("send file:%s to ip:%s failed, ErrorCode = %d", pMsg->szFileName, inet_ntoa(stRemoteAddr), pMsg->nErrorCode);

		MaintainTool::GetInstance().UpdateGuardSendProgress(pCurBaseSend->nAreaID, pCurBaseSend->dwIp, pMsg->nErrorCode);
    }

    if(pSession)
        CTransmitFileMgr::GetInstance().StopSending( pSession->dwArea, pSession->dwIp );

    return;
}


