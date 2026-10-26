#include "stdafx.h"
#include "message_notifier.h"

#include "gs_message_handler.h"
#include "gs_session_mgr.h"
#include "statis_info.h"
#include "server_config.h"
#include "gameserver.h"
#include "g2t_message.h"

BOOL CMessageNotifier::SendToUser(UINT32 dwClientSessionID, PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	UINT32 dwGTSessionID = GET_GT_INDEX_FROM_SESSION_ID(dwClientSessionID);
	InternalMessage::G2T_CLIENT_MSG* pMsg = (InternalMessage::G2T_CLIENT_MSG*)(pPacketBuffer - sizeof(InternalMessage::G2T_CLIENT_MSG));

	pMsg->wMsg = InternalMessage::g2t_client_msg;
	pMsg->dwSessionID = dwClientSessionID;
	dwSize += sizeof(InternalMessage::G2T_CLIENT_MSG);

	GT_SESSION* pGTSession = CGSSessionMgr::GetInstance().GetGTSession(dwGTSessionID);
	LOG_PROCESS_ERROR(pGTSession && pGTSession->bConnected && pGTSession->pSocketSession);

	nRetCode = pGTSession->pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, dwSize, -sizeof(InternalMessage::G2T_CLIENT_MSG));
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
	g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMessageNotifier::SendToUsers(UINT32 dwGTSessionID, UINT32 dwClientSessionIDList[], INT32 nSessionCount, 
	PACKET_BUFFER* pPacketBuffer, UINT32 dwSize)
{
	INT32 nRetCode = 0;
	INT32 nSize = dwSize + sizeof(InternalMessage::G2T_BROADCAST_CLIENT_MSG) + sizeof(UINT32) * nSessionCount;
	InternalMessage::G2T_BROADCAST_CLIENT_MSG* pNewMsg = NULL;
	InternalMessage::G2T_BROADCAST_CLIENT_MSG* pOldMsg;
	GT_SESSION* pGTSession;

	LOG_PROCESS_ERROR(nSessionCount > 0);

	pGTSession = CGSSessionMgr::GetInstance().GetGTSession(dwGTSessionID);
	LOG_PROCESS_ERROR(pGTSession && pGTSession->bConnected && pGTSession->pSocketSession);

	if (nSessionCount > (PACKET_OVERHEAD_SIZE - sizeof(InternalMessage::G2T_BROADCAST_CLIENT_MSG)) / 2 / sizeof(UINT32))
	{
		pNewMsg = (InternalMessage::G2T_BROADCAST_CLIENT_MSG*)CGameServer::GetInstance().GetPacketAllocator()->Alloc(nSize);
		LOG_PROCESS_ERROR(pNewMsg);

		pNewMsg->wMsg = InternalMessage::g2t_broadcast_client_msg;
		pNewMsg->wSessionCount = nSessionCount;
		memcpy(pNewMsg->dwSessionIDList, dwClientSessionIDList, sizeof(dwClientSessionIDList[0]) * nSessionCount);
		memcpy(pNewMsg->dwSessionIDList + nSessionCount, pPacketBuffer, dwSize);

		nRetCode = pGTSession->pSocketSession->Send((PACKET_BUFFER*)pNewMsg, nSize, 0);
		LOG_PROCESS_ERROR(nRetCode == nSize);

		CGameServer::GetInstance().GetPacketAllocator()->Free(pPacketBuffer);
	}
	else
	{
		pOldMsg = (InternalMessage::G2T_BROADCAST_CLIENT_MSG*)
			(pPacketBuffer - sizeof(InternalMessage::G2T_BROADCAST_CLIENT_MSG) - sizeof(UINT32) * nSessionCount);
		pOldMsg->wMsg = InternalMessage::g2t_broadcast_client_msg;
		pOldMsg->wSessionCount = nSessionCount;
		memcpy(pOldMsg->dwSessionIDList, dwClientSessionIDList, sizeof(dwClientSessionIDList[0]) * nSessionCount);

		nRetCode = pGTSession->pSocketSession->Send((PACKET_BUFFER*)pPacketBuffer, nSize, 
			-sizeof(InternalMessage::G2T_BROADCAST_CLIENT_MSG) - sizeof(UINT32) * nSessionCount);
		LOG_PROCESS_ERROR(nRetCode == nSize);
	}

	g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)nSize);
	g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	if (pNewMsg)
		CGameServer::GetInstance().GetPacketAllocator()->Free((PACKET_BUFFER*)pNewMsg);

	return FALSE;
}

BOOL CMessageNotifier::SendToMS(PACKET_BUFFER* pData, UINT32 dwSize)
{
	INT32 nRetCode = 0;

	MS_SESSION& rMSSession = CGSSessionMgr::GetInstance().GetMSSession();
	LOG_PROCESS_ERROR(rMSSession.bConnected);
	LOG_PROCESS_ERROR(rMSSession.pSocketSession);

	nRetCode = rMSSession.pSocketSession->Send((PACKET_BUFFER*)pData, dwSize, 0);
	LOG_PROCESS_ERROR(nRetCode == dwSize);

	g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
	g_ChangeStatisInfo(statInternalPacketOutgoing, 1);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMessageNotifier::SendToDL(PACKET_BUFFER* pData, UINT32 dwSize)
{
	INT32 nRetCode = 0;

	if (g_ServerConfig.MS.nInitDLCount > 0)
	{
		DL_SESSION& rDLSession = CGSSessionMgr::GetInstance().GetDLSession();
		LOG_PROCESS_ERROR(rDLSession.bConnected);
		LOG_PROCESS_ERROR(rDLSession.pSocketSession);

		nRetCode = rDLSession.pSocketSession->Send((PACKET_BUFFER*)pData, dwSize, 0);
		LOG_PROCESS_ERROR(nRetCode == dwSize);

		g_ChangeStatisInfo(statInternalNetflowOutgoing, (INT32)dwSize);
		g_ChangeStatisInfo(statInternalPacketOutgoing, 1);
	}
	else
	{
		if (pData)
			CGameServer::GetInstance().GetPacketAllocator()->Free(pData);
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CMessageNotifier::ReturnSelectRole(UINT32 dwClientSessionID)
{
    return CGSMessageHandler::GetInstance().DoGTReturnSelectRole(dwClientSessionID);
}

BOOL CMessageNotifier::SaveRoleData(CRole* poRole, BOOL bSaveFile)
{
    return CGSMessageHandler::GetInstance().DoDBSaveRoleData(poRole, bSaveFile);
}

BOOL CMessageNotifier::UnlockRole(CRole* poRole)
{
	return CGSMessageHandler::GetInstance().DoDBUnlockRoleData(poRole);
}

BOOL CMessageNotifier::_KickUser(UINT32 dwClientSessionID)
{
    INT32 nRetCode = 0;

    nRetCode = CGSMessageHandler::GetInstance().DoGTCloseClientSession(dwClientSessionID);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CMessageNotifier::Logout(UINT32 dwClientSessionID)
{
	return CGSMessageHandler::GetInstance().DoGTCloseClientSession(dwClientSessionID, TRUE);
}

