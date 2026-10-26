#include "stdafx.h"
#include "message_handler.h"
#include "imessage_notifier.h"
#include "role.h"
#include "game_world.h"
#include "server_def.h"

#ifndef _ROBOT

using namespace ExternalMessage;


void CCliMessageHandler::OnCompleteAchievement(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	INT32 nResult = errUnknownError;
	C2G_COMPLETE_ACHIEVEMENT* pMsg = (C2G_COMPLETE_ACHIEVEMENT*)pData;

	nRetCode = pRole->GetAchievementList().CanComplete(pMsg->nAchievementID);
	PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

	nRetCode = pRole->GetAchievementList().Complete(pMsg->nAchievementID);
	LOG_PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

	return;

Exit0:
	CRI("failed to complete achievement %d", pMsg->nAchievementID);

    if (nResult == errUnknownError)
        KICK_ROLE(pRole, ktLogged);
    else
		pRole->ErrorCodeNotify(nResult, 0, 0);

	return;

}

void CCliMessageHandler::OnCompareAchievement(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	INT32 nResult = errUnknownError;

	INT64 llDistance = 0;
	CRole* pTarget = NULL;

	C2G_COMPARE_ACHIEVEMENT* pMsg = (C2G_COMPARE_ACHIEVEMENT*)pData;
	LOG_PROCESS_ERROR(pMsg);

	pTarget = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
	PROCESS_ERROR_RET_CODE(pTarget, errAchievementPlayerNotFound);

	LOG_PROCESS_ERROR_RET_CODE((pRole->GetSceneTempID() == pTarget->GetSceneTempID()), errAchievementPlayerNotInSameScene);
	LOG_PROCESS_ERROR_RET_CODE((pRole->GetSceneID() == pTarget->GetSceneID()), errAchievementPlayerNotInSameScene);

	llDistance = g_GWConfig.nCompareAchievementDistance * POINT_PER_CM;
	llDistance *= llDistance;

	llDistance = pRole->GetDistance3D(pTarget);
	PROCESS_ERROR_RET_CODE((llDistance <= llDistance), errAchievementPlayerTooFar);

	nRetCode = CCliMessageHandler::GetInstance().DoCompareAchievement(pRole, pTarget);
	LOG_PROCESS_ERROR(nRetCode);

	return;

Exit0:
	if (nResult == errUnknownError)
        KICK_ROLE(pRole, ktLogged);
    else
		pRole->ErrorCodeNotify(nResult, 0, 0);
	return;
}

void CCliMessageHandler::OnRewardAchievement(CRole* poRole, const char* pData)
{
	INT32 nResult = errUnknownError;
	INT32 nRetCode = 0;

	C2G_REWARD_ACHIEVEMENT* pMsg = (C2G_REWARD_ACHIEVEMENT*)pData;
	LOG_PROCESS_ERROR(pMsg);

	nRetCode = poRole->GetAchievementList().CanReward(pMsg->nAchievementID);
	PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

	nRetCode = poRole->GetAchievementList().Reward(pMsg->nAchievementID);
	LOG_PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

	return;

Exit0:
	CRI("failed to get achievement %d reward", pMsg->nAchievementID);

	if (nResult == errUnknownError)
        KICK_ROLE(poRole, ktLogged);
    else
		poRole->ErrorCodeNotify(nResult, 0, 0);
	return;
	
}

BOOL CCliMessageHandler::DoCompleteAchievement(CRole* pRole, INT32 nAchievementID, UINT32 dwCompleteTime)
{
	INT32 nRetCode = 0;

	G2C_COMPLETE_ACHIEVEMENT* pMsg = (G2C_COMPLETE_ACHIEVEMENT*)m_poPacketAllocator->Alloc(sizeof(G2C_COMPLETE_ACHIEVEMENT));
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	pMsg->wMsg = g2c_complete_achievement;
	pMsg->nAchievementID = nAchievementID;
	pMsg->dwCompleteTime = dwCompleteTime;

	nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_COMPLETE_ACHIEVEMENT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoCompareAchievement(CRole* pRole, CRole* pTargetRole)
{
	INT32 nRetCode = 0;
	UINT32 dwSize = 0;

	G2C_COMPARE_ACHIEVEMENT* pMsg = (G2C_COMPARE_ACHIEVEMENT*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);
	LOG_PROCESS_ERROR(pTargetRole);

	pMsg->wMsg = g2c_compare_achievement;
	pMsg->dwRoleID = pTargetRole->GetObjID();
	
	pTargetRole->GetAchievementList().Save(pMsg->acAchievement, dwSize);

	pMsg->nCount = pTargetRole->GetAchievementList().GetCompletedCount();
	pMsg->wSize = (UINT16)(sizeof(G2C_COMPARE_ACHIEVEMENT) + dwSize);

	nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoRewardAchievement(CRole* poRole, INT32 nAchievementID)
{
	INT32 nRetCode = 0;

	G2C_REWARD_ACHIEVEMENT* pMsg = (G2C_REWARD_ACHIEVEMENT*)m_poPacketAllocator->Alloc(sizeof(G2C_REWARD_ACHIEVEMENT));
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);

	pMsg->wMsg = g2c_reward_achievement;
	pMsg->nAchievementID = nAchievementID;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_REWARD_ACHIEVEMENT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoUpdateAchievementVariable(CRole* poRole, INT32 nIndex, INT32 nValue)
{
	INT32 nRetCode = 0;

	G2C_UPDATE_ACHIEVEMENT_VARIABLE* pMsg = (G2C_UPDATE_ACHIEVEMENT_VARIABLE*)m_poPacketAllocator->Alloc(sizeof(G2C_UPDATE_ACHIEVEMENT_VARIABLE));
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);

	pMsg->wMsg = g2c_update_achievement_variable;
	pMsg->nIndex = nIndex;
	pMsg->nValue = nValue;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_UPDATE_ACHIEVEMENT_VARIABLE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;

Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoActivateHankbook(CRole* poRole, INT32 nType, INT32 nIndex)
{
	INT32 nRetCode = 0;

	G2C_ACTIVATE_HANKBOOK* pMsg = (G2C_ACTIVATE_HANKBOOK*)m_poPacketAllocator->Alloc(sizeof(G2C_ACTIVATE_HANKBOOK));
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);

	pMsg->wMsg = g2c_activate_hankbook;
	pMsg->nIndex = nIndex;
	pMsg->nType = nType;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_ACTIVATE_HANKBOOK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;

Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSyncAchievementList(CRole* pRole)
{
	INT32 nRetCode = 0;
	G2C_SYNC_ACHIEVEMENT_LIST* pMsg = NULL;
	CAchievementsList& rAchievementList = pRole->GetAchievementList();
	UINT32 dwSize = 0;

	LOG_PROCESS_ERROR(pRole);

	pMsg = (G2C_SYNC_ACHIEVEMENT_LIST*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_achievement_list;

	nRetCode = rAchievementList.Save(pMsg->szData, dwSize);
	LOG_PROCESS_ERROR(nRetCode);

	pMsg->wSize = (UINT16)dwSize + sizeof(G2C_SYNC_ACHIEVEMENT_LIST);
	pMsg->nCount = rAchievementList.GetCompletedCount();

	nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

#endif  // _ROBOT