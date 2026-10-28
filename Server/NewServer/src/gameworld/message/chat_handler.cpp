#include "stdafx.h"
#include "message_handler.h"

#include "g2c_message.h"
#include "g2m_message.h"

#include "imessage_notifier.h"
#include "game_world.h"
#include "chat_def.h"
#include "server_config.h"
#include "scene_data.h"

#ifndef _ROBOT

using namespace ExternalMessage;

void CCliMessageHandler::OnChatMessage(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	INT32 nMessageSize = 0;
	INT32 nResult = errUnknownError;
	INT32 nChannelType = 0;
	INT32 nLocation = cltNormal;
	const SCENE_DATA* pcSceneData = NULL;

	C2G_CHAT_MESSAGE* pMsg = (C2G_CHAT_MESSAGE*)pData;
	LOG_PROCESS_ERROR(pMsg);

    LOG_PROCESS_ERROR_RET_CODE(!poRole->IsFreeMode(), errFreeMode);

	nMessageSize = pMsg->wSize - sizeof(C2G_CHAT_MESSAGE);
	LOG_PROCESS_ERROR(pMsg->szMessage[nMessageSize - 1] == '\0');
	LOG_PROCESS_ERROR((nMessageSize > 1) && (nMessageSize <= MAX_CHAT_MESSAGE_LEN + 1)); // empty message not allowed
   
	LOG_PROCESS_ERROR(poRole->GetScene());
	pcSceneData = poRole->GetScene()->GetSceneData();
	LOG_PROCESS_ERROR(pcSceneData);

	switch (pMsg->dwTargetID)
	{
	case cctGroup:
		PROCESS_ERROR_RET_CODE(!pcSceneData->bCannotGroupChat, errChatSceneForbidden);
		switch (pMsg->byLocation)
		{
		case cltNormal:    // World
			PROCESS_ERROR_RET_CODE(CGameWorld::GetInstance().GetGameFrame() > poRole->GetGroupChatTimer(), errChatTooFrequent);

			//Remove the world-channel message limit and add level and gold cost requirements
			PROCESS_ERROR_RET_CODE(poRole->GetLevel() >= g_GWConfig.ChatConfig.nGroupChatLevel, errChatLevelTooLow);
			PROCESS_ERROR_RET_CODE(poRole->GetItemBag()->GetMoney(MONEYTYPE_02) >= g_GWConfig.ChatConfig.nGroupChatCost, errChatMoneyNotEnough);

			nRetCode = poRole->GetItemBag()->SubMoney(MONEYTYPE_02, g_GWConfig.ChatConfig.nGroupChatCost, MONEYLOG_CHAT_COST, 0);
			LOG_CHECK_ERROR(nRetCode);

			poRole->SetGroupChatTimer(CGameWorld::GetInstance().GetGameFrame() + CONVERT_TIME(g_GWConfig.ChatConfig.nGroupMsgInterval));

			break;
		case cltTrumpet:    // Trumpet
			if (g_GWConfig.ChatConfig.nTrumpetItemID > 0)
			{
				nRetCode = poRole->GetItemBag()->DeleteItemId(g_GWConfig.ChatConfig.nTrumpetItemID, 1, ITEMLOG_TRUMPET, FALSE, 0);
				LOG_PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, errGroupChatWithItem);
			}
			nLocation = cltTrumpet;
			break;
		default:
			LOG_PROCESS_ERROR(FALSE);
		}
		break;
	case cctScene:
		{	
			PROCESS_ERROR_RET_CODE(!pcSceneData->bCannotSceneChat, errChatSceneForbidden);
		}
		break;
	case cctScreen:
		{
			PROCESS_ERROR_RET_CODE(!pcSceneData->bCannotScreenChat, errChatSceneForbidden);
			PROCESS_ERROR_RET_CODE(CGameWorld::GetInstance().GetGameFrame() >= poRole->GetNormalChatTimer(), errChatTooFrequent);
			poRole->SetNormalChatTimer(CGameWorld::GetInstance().GetGameFrame() + CONVERT_TIME(g_GWConfig.ChatConfig.nNormalMsgInterval));
		}
		break;
	default:
		{
			LOG_PROCESS_ERROR(FALSE);
		}
		break;
	}

	if (CGameWorld::GetInstance().GetGameTime() <= poRole->GetForbidChatTime())
	{
		nRetCode = CCliMessageHandler::GetInstance().DoChatMessage(poRole->GetSessionID(), poRole->GetName(), 
			poRole->GetObjID(), pMsg->dwTargetID, cltNormal, pMsg->szMessage, nMessageSize);
		LOG_PROCESS_ERROR_RET_CODE(nRetCode, errChatServiceUnavaible);
	}
	else
	{
		nRetCode = poRole->Say(pMsg->dwTargetID, nLocation, pMsg->szMessage);
		LOG_PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);
	}

	nRetCode = CCliMessageHandler::GetInstance().DoDLChatMessage(poRole, pMsg->dwTargetID, pMsg->szMessage, nMessageSize);
	LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	if (nResult == errUnknownError)
        KICK_ROLE(poRole, ktLogged);
	else
		poRole->ErrorCodeNotify(nResult, 0, 0);
	return;
}

BOOL CCliMessageHandler::DoChatMessage(UINT32 dwSessionID, const char* pSrcName, 
	UINT32 dwSrcID, UINT32 dwTargetID, UINT32 dwLocation, const char* pcszMessage, INT32 nMessageSize)
{
    INT32	nRetCode = 0;
    INT32	nSrcNameSize = 0;
    INT32	nSize = 0;
    G2C_CHAT_MESSAGE* pMsg = NULL;

    LOG_PROCESS_ERROR(pcszMessage);
    LOG_PROCESS_ERROR(pSrcName);

    nSrcNameSize = (INT32)strnlen(pSrcName, USER_NAME_LEN) + 1;
    LOG_PROCESS_ERROR(pSrcName[nSrcNameSize - 1] == '\0');

    nSize = nMessageSize + nSrcNameSize + sizeof(G2C_CHAT_MESSAGE);

    pMsg = (G2C_CHAT_MESSAGE*)m_poPacketAllocator->Alloc(nSize);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_chat_message;
    pMsg->wSize = nSize;
    pMsg->dwTargetID = dwTargetID;
    pMsg->dwSrcID = dwSrcID;
    pMsg->uLocation = dwLocation;
	pMsg->uReserved = 0;
    strxcpy(pMsg->szMessage, pcszMessage, nMessageSize);
    strxcpy(pMsg->szMessage + nMessageSize, pSrcName, nSrcNameSize);

    if (g_GWConfig.bFilterCensoredWord)
    {
        nRetCode = CGameWorld::GetInstance().ReplaceCensoredWord(pMsg->szMessage);
        LOG_CHECK_ERROR(nRetCode);
    }

    nRetCode = m_poNotifier->SendToUser(dwSessionID, (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoChatMessage(CScene* pScene, const char* pSrcName, UINT32 dwSrcID, UINT32 dwTargetID, 
	UINT32 dwLocation, const char* pcszMessage, INT32 nMessageSize)
{
	INT32	nRetCode = 0;
	INT32	nSrcNameSize = 0;
	INT32	nSize = 0;
	G2C_CHAT_MESSAGE* pMsg = NULL;

	LOG_PROCESS_ERROR(pScene);
	LOG_PROCESS_ERROR(pcszMessage);
	LOG_PROCESS_ERROR(pSrcName);

	nSrcNameSize = (INT32)strnlen(pSrcName, USER_NAME_LEN) + 1;
	LOG_PROCESS_ERROR(pSrcName[nSrcNameSize - 1] == '\0');

	nSize = nMessageSize + nSrcNameSize + sizeof(G2C_CHAT_MESSAGE);

	pMsg = (G2C_CHAT_MESSAGE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg		 = g2c_chat_message;
	pMsg->wSize		 = nSize;
	pMsg->dwTargetID = dwTargetID;
	pMsg->dwSrcID = dwSrcID;
	pMsg->uLocation = dwLocation;
	pMsg->uReserved = 0;
	strxcpy(pMsg->szMessage, pcszMessage, nMessageSize);
	strxcpy(pMsg->szMessage + nMessageSize, pSrcName, nSrcNameSize);

	if (g_GWConfig.bFilterCensoredWord)
	{
		nRetCode = CGameWorld::GetInstance().ReplaceCensoredWord(pMsg->szMessage);
		LOG_CHECK_ERROR(nRetCode);
	}

	nRetCode = _BroadcastScene(pScene, (PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoChatMessage(CRegion* pRegion, const char* pSrcName, UINT32 dwSrcID, UINT32 dwTargetID, 
	UINT32 dwLocation, const char* pcszMessage, INT32 nMessageSize)
{
	INT32	nRetCode = 0;
	INT32	nSrcNameSize = 0;
	INT32	nSize = 0;
	G2C_CHAT_MESSAGE* pMsg = NULL;


	LOG_PROCESS_ERROR(pRegion);
	LOG_PROCESS_ERROR(pcszMessage);
	LOG_PROCESS_ERROR(pSrcName);

	nSrcNameSize = (INT32)strnlen(pSrcName, USER_NAME_LEN) + 1;
	LOG_PROCESS_ERROR(pSrcName[nSrcNameSize - 1] == '\0');

	nSize = nMessageSize + nSrcNameSize + sizeof(G2C_CHAT_MESSAGE);

    pMsg = (G2C_CHAT_MESSAGE*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg		 = g2c_chat_message;
	pMsg->wSize		 = nSize;
	pMsg->dwSrcID = dwSrcID;
	pMsg->dwTargetID = dwTargetID;
	pMsg->uLocation = dwLocation;
	pMsg->uReserved = 0;
	strxcpy(pMsg->szMessage, pcszMessage, nMessageSize);
	strxcpy(pMsg->szMessage + nMessageSize, pSrcName, nSrcNameSize);

	if (g_GWConfig.bFilterCensoredWord)
	{
		nRetCode = CGameWorld::GetInstance().ReplaceCensoredWord(pMsg->szMessage);
		LOG_CHECK_ERROR(nRetCode);
	}

	nRetCode = _Broadcast9Region(pRegion, (PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);
	
	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoMSChatMessage(UINT32 dwSrcID, const char* pSrcName, UINT32 dwTargetID, UINT32 dwLocation, INT32 nServerGroupID,
	BOOL bGM, const char* pcszMessage, INT32 nMessageSize)
{
	INT32  nRetCode = 0;

    InternalMessage::G2M_CHAT_MESSAGE* pMsg = (InternalMessage::G2M_CHAT_MESSAGE*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_CHAT_MESSAGE) + nMessageSize);
    LOG_PROCESS_ERROR(pMsg);

	LOG_PROCESS_ERROR(pcszMessage);
	LOG_PROCESS_ERROR(pSrcName);

	pMsg->wMsg = InternalMessage::g2m_chat_message;
	pMsg->dwSourceID = dwSrcID;
	pMsg->dwTargetID = dwTargetID;
	pMsg->byLocation = (UINT8)dwLocation;
	pMsg->byServerGroupID = (UINT8)nServerGroupID;
	pMsg->bGM = (UINT8)bGM;
	strxcpy(pMsg->szName, pSrcName, USER_NAME_LEN);
	strxcpy(pMsg->szMessage, pcszMessage, nMessageSize);

	nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_CHAT_MESSAGE) + nMessageSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

#endif
