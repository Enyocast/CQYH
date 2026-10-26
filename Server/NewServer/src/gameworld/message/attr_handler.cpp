#include "stdafx.h"
#include "message_handler.h"
#include "imessage_notifier.h"
#include "external_message_header.h"
#include "g2c_message.h"

#include "game_world.h"
#include "role.h"

#ifndef _ROBOT

using namespace ExternalMessage;

BOOL CCliMessageHandler::DoSyncHp(CCharacter* poChar)
{
	INT32 nRetCode = 0;
	G2C_SYNC_HP* pMsg = NULL;

	LOG_PROCESS_ERROR(poChar);

	pMsg = (G2C_SYNC_HP*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_HP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_hp;
	pMsg->dwCharID = poChar->GetObjID();
	pMsg->nCurrentHp = poChar->GetHp();
	pMsg->nMaxHp = poChar->GetAttr(catMaxHp);

	nRetCode = _Broadcast9Region(poChar->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SYNC_HP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSyncMp(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_SYNC_MP* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_SYNC_MP*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_MP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_mp;
	pMsg->nCurrentMp = poRole->GetMp();

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SYNC_MP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoCharDie(CCharacter* poChar, INT32 nType)
{
	INT32 nRetCode = 0;
	G2C_CHAR_DIE* pMsg = NULL;

	LOG_PROCESS_ERROR(poChar);

	pMsg = (G2C_CHAR_DIE*)m_poPacketAllocator->Alloc(sizeof(G2C_CHAR_DIE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_char_die;
	pMsg->dwCharID = poChar->GetObjID();
	pMsg->byType = (INT32)nType;

	nRetCode = _Broadcast9Region(poChar->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_CHAR_DIE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoCharRevive(CCharacter* poChar, INT32 nType)
{
	INT32 nRetCode = 0;
	G2C_CHAR_REVIVE* pMsg= NULL;

	LOG_PROCESS_ERROR(poChar);

	pMsg = (G2C_CHAR_REVIVE*)m_poPacketAllocator->Alloc(sizeof(G2C_CHAR_REVIVE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_char_revive;
	pMsg->dwCharID = poChar->GetObjID();
	pMsg->byType = nType;

	nRetCode = _Broadcast9Region(poChar->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_CHAR_REVIVE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoReviveInfo(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_REVIVE_INFO* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_REVIVE_INFO*)m_poPacketAllocator->Alloc(sizeof(G2C_REVIVE_INFO));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_revive_info;
	pMsg->dwKillerID = poRole->GetLastCasterID();
	pMsg->nWaitTime = (poRole->GetNextReviveFrm() - CGameWorld::GetInstance().GetGameFrame()) * 1000 / GAME_FPS;

	for(INT32 i = crtInvalid; i < crtTotal; i++)
	{
		pMsg->ReviveInfo[i].byReviveType = i;
		pMsg->ReviveInfo[i].nRequireItemID = g_GWConfig.ReviveParam[i].nRequireItemID;
		pMsg->ReviveInfo[i].nRequireItemCount = g_GWConfig.ReviveParam[i].nRequireItemCount;

		if(i == crtAtCurrentPos)
		{
//			INT32 nTryReviveFrm = poRole->GetTryReviveFrm(crtAtCurrentPos);
//			INT32 nTryReviveCount = poRole->GetTryReviveCount(crtAtCurrentPos);
//
//			if(CGameWorld::GetInstance().GetGameFrame() - nTryReviveFrm > CONVERT_TIME(g_GWConfig.nInstantReviveResetTime))
//				nTryReviveCount = 0;

//			pMsg->ReviveInfo[i].nRequireItemCount = g_GWConfig.ReviveParam[i].nRequireItemCount * (nTryReviveCount + 1);
//			pMsg->ReviveInfo[i].nRequireItemCount = pMsg->ReviveInfo[i].nRequireItemCount < g_GWConfig.ReviveParam[i].nRequireItemMaxCount ? pMsg->ReviveInfo[i].nRequireItemCount : g_GWConfig.ReviveParam[i].nRequireItemMaxCount;
			pMsg->ReviveInfo[i].nRequireItemID = g_GWConfig.ReviveParam[i].nRequireItemID;
			pMsg->ReviveInfo[i].nRequireItemCount = g_GWConfig.ReviveParam[i].nRequireItemCount;
		}
	}

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_REVIVE_INFO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CCliMessageHandler::DoActivateRevivePt(CRole* poRole, INT32 nX, INT32 nY, INT32 nZ)
{
	INT32 nRetCode = 0;
	G2C_ACTIVATE_REVIVE_PT* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_ACTIVATE_REVIVE_PT*)m_poPacketAllocator->Alloc(sizeof(G2C_ACTIVATE_REVIVE_PT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_activate_revive_pt;
	pMsg->nX = nX;
	pMsg->nY = nY;
	pMsg->nZ = nZ;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_ACTIVATE_REVIVE_PT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CCliMessageHandler::DoRoleLevelUp(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_ROLE_LEVEL_UP* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_ROLE_LEVEL_UP*)m_poPacketAllocator->Alloc(sizeof(G2C_ROLE_LEVEL_UP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_role_level_up;
	pMsg->dwRoleID = poRole->GetObjID();
	pMsg->byLevel = (UINT8)poRole->GetLevel();

	nRetCode = _Broadcast9Region(poRole->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_ROLE_LEVEL_UP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoExpChange(CRole* poRole, INT32 nExpChange, INT32 nMaxExp, 
	INT32 nTodayExp, INT32 nTodayMaxExp, INT32 nExtraExp)
{
	INT32 nRetCode = 0;
	G2C_EXP_CHANGE* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_EXP_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_EXP_CHANGE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_exp_change;
	pMsg->nExp = poRole->GetExp();
	pMsg->nExpChange = nExpChange;
	pMsg->nMaxExp = nMaxExp;
    pMsg->nTodayExp = nTodayExp;
    pMsg->nTodayMaxExp = nTodayMaxExp;
	pMsg->nExtraExp = nExtraExp;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_EXP_CHANGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoExtraExpChange(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_EXTRA_EXP_CHANGE* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_EXTRA_EXP_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_EXTRA_EXP_CHANGE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_extra_exp_change;
	pMsg->nExtraExp = poRole->GetExtraExp();

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_EXTRA_EXP_CHANGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoSyncAttrList(CRole* poRole)
{
	INT32 nRetCode = 0;
	INT32 nSize;
	G2C_SYNC_ATTR_LIST* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	nSize = sizeof(G2C_SYNC_ATTR_LIST) + catTotal * sizeof(ATTR_DATA);
	pMsg = (G2C_SYNC_ATTR_LIST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_attr_list;
	pMsg->wSize = nSize;

	for (INT32 i = catDefault; i < catTotal; i++)
	{
		pMsg->astAttrData[i].byAttrID = i;
		pMsg->astAttrData[i].nAttrValue = poRole->GetAttrList().GetAttr(i);
	}

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoAttrChange(CRole* poRole, INT32 eAttrType)
{
	INT32 nRetCode = 0;
	G2C_SYNC_ATTR_CHANGE* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_SYNC_ATTR_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_ATTR_CHANGE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_attr_change;
	pMsg->byAttrID = eAttrType;
	pMsg->nAttrValue = poRole->GetAttr(eAttrType);

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_SYNC_ATTR_CHANGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoSyncPkValueChange(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_SYNC_PK_VALUE* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_SYNC_PK_VALUE*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_PK_VALUE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_pk_value;
	pMsg->dwPkValue = poRole->GetPkValue();
	pMsg->dwRoleID = poRole->GetObjID();

	nRetCode = _Broadcast9Region(poRole->GetRegion(), (char*)pMsg, sizeof(G2C_SYNC_PK_VALUE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoSyncPkResult(CRole* poKiller, CRole* poVictim, INT32 nChangePkValue, INT32 nResult)
{
    INT32 nRetCode = 0;
    G2C_SYNC_PK_RESULT* pMsg = NULL;

    LOG_PROCESS_ERROR(poKiller);
    LOG_PROCESS_ERROR(poVictim);

    pMsg = (G2C_SYNC_PK_RESULT*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_PK_RESULT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_pk_result;
    pMsg->byPKResult = nResult;
    pMsg->dwKillerRoleID = poKiller->GetObjID();
    pMsg->dwVictimRoleID = poVictim->GetObjID();
    pMsg->shChangePkValue = nChangePkValue;

    nRetCode = m_poNotifier->SendToUser(poKiller->GetSessionID(), (char*)pMsg, sizeof(G2C_SYNC_PK_RESULT));
    LOG_PROCESS_ERROR(nRetCode);

	pMsg = (G2C_SYNC_PK_RESULT*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_PK_RESULT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_pk_result;
	pMsg->byPKResult = nResult;
	pMsg->dwKillerRoleID = poKiller->GetObjID();
	pMsg->dwVictimRoleID = poVictim->GetObjID();
	pMsg->shChangePkValue = nChangePkValue;

    nRetCode = m_poNotifier->SendToUser(poVictim->GetSessionID(), (char*)pMsg, sizeof(G2C_SYNC_PK_RESULT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoSyncGreyName(CRole* poRole, BOOL bGreyName)
{
	INT32 nRetCode = 0;
	G2C_SYNC_GREY_NAME* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_SYNC_GREY_NAME*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_GREY_NAME));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_sync_grey_name;
	pMsg->dwRoleID = poRole->GetObjID();
	pMsg->bGreyName = bGreyName;

	nRetCode = _Broadcast9Region(poRole->GetRegion(), (char*)pMsg, sizeof(G2C_SYNC_GREY_NAME));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoSyncEquipTitle(CRole* poRole)
{
    INT32 nRetCode = 0;
    G2C_SYNC_EQUIP_TITLE* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_SYNC_EQUIP_TITLE*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_EQUIP_TITLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_equip_title;
    pMsg->byTitleID = poRole->GetTitle().GetEquipedTitleID();
    pMsg->dwRoleID = poRole->GetObjID();

    nRetCode = _Broadcast9Region(poRole->GetRegion(), (char*)pMsg, sizeof(G2C_SYNC_EQUIP_TITLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoSyncComboKill(CRole* poRole)
{
    INT32 nRetCode = 0;
    G2C_SYNC_COMBO_KILL* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_SYNC_COMBO_KILL*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_COMBO_KILL));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_combo_kill;
	pMsg->dwRoleID = poRole->GetObjID();
	pMsg->byFaction = poRole->GetFaction();
	strxcpy(pMsg->szName, poRole->GetName(), ROLE_NAME_LEN);
	pMsg->nComboKill = poRole->GetComboKill();

    nRetCode = _BroadcastScene(poRole->GetScene(), (char*)pMsg, sizeof(G2C_SYNC_COMBO_KILL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;

}


#endif  // _ROBOT
