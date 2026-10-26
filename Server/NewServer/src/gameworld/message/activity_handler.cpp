#include "stdafx.h"
#include "message_handler.h"
#include "imessage_notifier.h"
#include "role.h"
#include "game_world.h"
#include "server_def.h"
#include "activity_reward_data.h"
#include "item_bag.h"
#include "g2m_message.h"
#include "anti_cheat.h"

#ifndef _ROBOT

using namespace ExternalMessage;

void CCliMessageHandler::OnActivityReward(CRole *poRole, const char *pData)
{
	INT32 nResult = errUnknownError;
	INT32 nRetCode = 0;
	C2G_ACTIVITY_REWARD* pMsg = (C2G_ACTIVITY_REWARD*)pData;
	const ACTIVITY_REWARD_DATA* pActivityReward = NULL;
	const ITEM_DATA* pItem = NULL;

	LOG_PROCESS_ERROR(pMsg->nIndex >= 0 && pMsg->nIndex <= 32);

	pActivityReward = CDataManager<ACTIVITY_REWARD_DATA>::GetInstance().GetData(pMsg->nIndex);
	LOG_PROCESS_ERROR(pActivityReward);

	pItem = CDataManager<ITEM_DATA>::GetInstance().GetData(pActivityReward->nRewardItemID);
	LOG_PROCESS_ERROR(pItem);

	LOG_PROCESS_ERROR_RET_CODE(poRole->GetActivity() >= pActivityReward->nActivityValue, errLackofActivity);
	LOG_PROCESS_ERROR_RET_CODE(!poRole->GetActivityRewardByIndex(pMsg->nIndex), errActivityRewardAccepted);

	nRetCode = poRole->GetItemBag()->AddItem(pItem->m_nTemplateID, pActivityReward->nRewardItemCount, ITEMLOG_ACTIVITY_REWARD, 0, FALSE);
	LOG_PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nResult);

	poRole->AddActivityReward(pMsg->nIndex);

#ifndef _ROBOT
	CCliMessageHandler::GetInstance().DoActivityReward(poRole, pMsg->nIndex);
#endif

	return;
Exit0:
	if (nResult == errUnknownError)
		KICK_ROLE(poRole, ktLogged);
	else
		poRole->ErrorCodeNotify(nResult, 0, 0);

}

void CCliMessageHandler::OnCheckIn(CRole* poRole, const char *pData)
{
	INT32 nResult = 0;

	PROCESS_ERROR(poRole);

	nResult = poRole->CheckIn();
	PROCESS_ERROR_RET_CODE(nResult, errSuccess);

Exit0:
	if (nResult == errUnknownError)
		KICK_ROLE(poRole, ktLogged);
	else if (nResult != errSuccess)
		poRole->ErrorCodeNotify(nResult, 0, 0);
}

void CCliMessageHandler::OnJigsawAnswer(CRole* poRole, const char *pData)
{
	INT32 nErrCode = 0;
	INT32 nRetCode = 0;

	C2G_JIGSAW_ANSWER* pMsg = (C2G_JIGSAW_ANSWER*)pData;
	LOG_PROCESS_ERROR(poRole);

	if (poRole->GetJigsawAnswerIdx() >= 0)
	{
		PROCESS_ERROR(pMsg->byIndex == poRole->GetJigsawAnswerIdx());
		poRole->SuccessAntiCheat();

		nRetCode = CCliMessageHandler::GetInstance().DoDLAntiCheatInfo(poRole, aclaAnswer, pMsg->byIndex, errSuccess, NULL, NULL);
		LOG_CHECK_ERROR(nRetCode);
	}

	return;
Exit0:
	if (poRole)
	{
		nErrCode = poRole->FailAntiCheat(FALSE, FALSE);

		nRetCode = CCliMessageHandler::GetInstance().DoDLAntiCheatInfo(poRole, aclaAnswer, pMsg->byIndex, nErrCode, NULL, NULL);
		LOG_CHECK_ERROR(nRetCode);
	}
}

BOOL CCliMessageHandler::DoSyncCheckInInfo(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_SYNC_CHECKIN_INFO* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_SYNC_CHECKIN_INFO*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_CHECKIN_INFO));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_checkin_info;
	pMsg->byLastCheckInIndex = poRole->GetLastCheckInIndex();
	pMsg->byCanCheckInToday = poRole->CanCheckInToday();
	pMsg->byCheckInValid = poRole->IsCheckInValid();

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SYNC_CHECKIN_INFO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoCheckIn(CRole* poRole, INT32 nIndex)
{
	INT32 nRetCode = 0;
	G2C_CHECKIN* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_CHECKIN*)m_poPacketAllocator->Alloc(sizeof(G2C_CHECKIN));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_checkin;
	pMsg->byIndex = nIndex;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_CHECKIN));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoAntiCheatJigsaw(CRole* poRole, JigsawImage* pImgData, JigsawAnswer* pAnswerData, UINT32 dwTimeoutInterval)
{
	INT32 nRetCode = 0;
	G2C_JIGSAW* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_JIGSAW*)m_poPacketAllocator->Alloc(sizeof(G2C_JIGSAW));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_jigsaw;
	pMsg->dwTimeoutInterval = dwTimeoutInterval;
	pMsg->byBlockX = pAnswerData->nBlockX;
	pMsg->byBlockY = pAnswerData->nBlockY;

	memcpy(pMsg->cImageData, pImgData->qwBlock, JIGSAW_DATA_SIZE);

	for (INT32 i = 0; i < JIGSAW_ANSWER_COUNT; i++)
	{
		memcpy(&pMsg->AnswerData[i], &pAnswerData->Answer[i], JIGSAW_ANSWER_DATA_SIZE);
	}

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_JIGSAW));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoMSFreezeLogin(CRole* poRole, UINT32 dwFreezeTime)
{
	INT32 nRetCode = 0;
	InternalMessage::G2M_FREEZE_LOGIN* pMsg = (InternalMessage::G2M_FREEZE_LOGIN*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_FREEZE_LOGIN));
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);

	pMsg->wMsg = InternalMessage::g2m_freeze_login;
	pMsg->dwRoleID = poRole->GetObjID();
	pMsg->dwFreezeTime = dwFreezeTime;

	nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_FREEZE_LOGIN));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoMSTemporaryCharge(UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	InternalMessage::G2M_TEMPORARY_CHARGE* pMsg = 
		(InternalMessage::G2M_TEMPORARY_CHARGE*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_TEMPORARY_CHARGE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = InternalMessage::g2m_temporary_charge;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_TEMPORARY_CHARGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

void CCliMessageHandler::OnArenaReward(CRole* poRole, const char* pData)
{

}

#endif //_ROBOT