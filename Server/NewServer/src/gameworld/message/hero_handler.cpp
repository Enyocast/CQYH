#include "stdafx.h"
#include "message_handler.h"
#include "imessage_notifier.h"
#include "server_def.h"
#include "role.h"
#include "hero.h"

#ifndef _ROBOT

using namespace ExternalMessage;

void CCliMessageHandler::OnHireHero(CRole* poRole, const char* pData)
{
	INT32 nResult = errUnknownError;
	C2G_HIRE_HERO* pMsg = (C2G_HIRE_HERO*)pData;

	LOG_PROCESS_ERROR(poRole);

	nResult = poRole->HireHero(1, pMsg->byClass, pMsg->bySex, 0, hatPassive, TRUE);
	LOG_PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);

	return;

Exit0:
	if (nResult == errUnknownError)
		KICK_ROLE(poRole, ktLogged);
	else
		poRole->ErrorCodeNotify(nResult, 0, 0);
	return;
}

void CCliMessageHandler::OnFireHero(CRole* poRole, const char* pData)
{
	INT32 nResult = errUnknownError;
	LOG_PROCESS_ERROR(poRole);

	nResult = poRole->FireHero();
	LOG_PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);

	return;

Exit0:
	if (nResult == errUnknownError)
        KICK_ROLE(poRole, ktLogged);
	else
		poRole->ErrorCodeNotify(nResult, 0, 0);
	return;
}

void CCliMessageHandler::OnSummonHero(CRole* poRole, const char* pData)
{
	CHero* poHero = NULL;

	INT32 nResult = errUnknownError;
	LOG_PROCESS_ERROR(poRole);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR_RET_CODE(poHero, errHeroNotExist);

	PROCESS_ERROR_RET_CODE(!poHero->IsSummoned(), errHeroAlreadySummoned);

	nResult = poRole->SummonHero();
	LOG_PROCESS_ERROR(nResult == errSuccess);

	return;

Exit0:
	if (nResult == errUnknownError)
        KICK_ROLE(poRole, ktLogged);
	else
		poRole->ErrorCodeNotify(nResult, 0, 0);
	return;
}

void CCliMessageHandler::OnRecallHero(CRole* poRole, const char* pData)
{
	CHero* poHero = NULL;

	INT32 nResult = errUnknownError;
	LOG_PROCESS_ERROR(poRole);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR_RET_CODE(poHero, errHeroNotExist);

	PROCESS_ERROR_RET_CODE(poHero->IsSummoned(), errHeroAlreadyRecalled);

	nResult = poRole->RecallHero(TRUE);
	LOG_PROCESS_ERROR_RET_CODE(nResult == errSuccess, nResult);

	return;
Exit0:
	if (nResult == errUnknownError)
        KICK_ROLE(poRole, ktLogged);
	else
		poRole->ErrorCodeNotify(nResult, 0, 0);
	return;
}

void CCliMessageHandler::OnQueryHeroAttrList(CRole* poRole, const char* pData)
{
	CHero* poHero = NULL;
	LOG_PROCESS_ERROR(poRole);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	DoSyncHeroAttrList(poRole);

	return;
Exit0:
    KICK_ROLE(poRole, ktLogged);
}


void CCliMessageHandler::OnChangeHeroAi(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	INT32 nResult = errUnknownError;
	C2G_CHANGE_HERO_AI* pMsg = (C2G_CHANGE_HERO_AI*)pData;
	CHero* poHero = NULL;

	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR_RET_CODE(pMsg->byAiType > hatInvalid && pMsg->byAiType < hatTotal, errHeroAiInvalid);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	nRetCode = poHero->SetAiType(pMsg->byAiType);
	LOG_PROCESS_ERROR_RET_CODE(nRetCode, errHeroAiInvalid);

	nResult = errSuccess;

	return;

Exit0:
	if (nResult == errUnknownError)
        KICK_ROLE(poRole, ktLogged);
	else
		poRole->ErrorCodeNotify(nResult, 0, 0);
	return;
}

void CCliMessageHandler::OnChangeHeroName(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	INT32 nResult = errUnknownError;
	C2G_CHANGE_HERO_NAME* pMsg = (C2G_CHANGE_HERO_NAME*)pData;
	CHero* poHero = NULL;

	LOG_PROCESS_ERROR(poRole);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	nRetCode = poHero->ChangeName(pMsg->szNewName);
	LOG_PROCESS_ERROR_RET_CODE(nRetCode, errHeroAlreadyHaveName);

	nResult = errSuccess;

	return;

Exit0:
	if (nResult == errUnknownError)
        KICK_ROLE(poRole, ktLogged);
	else
		poRole->ErrorCodeNotify(nResult, 0, 0);
	return;

}

BOOL CCliMessageHandler::DoHeroExpChange(CRole* poRole, INT32 nExpChange, UINT32 dwMaxExp)
{
	INT32 nRetCode = 0;
	G2C_HERO_EXP_CHANGE* pMsg = NULL;
	CHero* poHero = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_HERO_EXP_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_HERO_EXP_CHANGE));
	LOG_PROCESS_ERROR(pMsg);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	pMsg->wMsg = g2c_hero_exp_change;
	pMsg->dwHeroID = poHero->GetObjID();
	pMsg->dwExp = poHero->GetExp();
	pMsg->dwMaxExp = dwMaxExp;
	pMsg->nExpChange = nExpChange;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_HERO_EXP_CHANGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CCliMessageHandler::DoHeroLevelUp(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_HERO_LEVEL_UP* pMsg = NULL;
	CHero* poHero = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_HERO_LEVEL_UP*)m_poPacketAllocator->Alloc(sizeof(G2C_HERO_LEVEL_UP));
	LOG_PROCESS_ERROR(pMsg);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	pMsg->wMsg = g2c_hero_level_up;
	pMsg->dwHeroID = poHero->GetObjID();
	pMsg->byLevel = poHero->GetLevel();

	nRetCode = _Broadcast9Region(poRole->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_HERO_LEVEL_UP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSyncHeroAttrList(CRole* poRole)
{
	INT32 nRetCode = 0;
	INT32 nSize;
	G2C_SYNC_HERO_ATTR_LIST* pMsg = NULL;
	CHero* poHero = NULL;

	LOG_PROCESS_ERROR(poRole);

	nSize = sizeof(G2C_SYNC_HERO_ATTR_LIST) + catTotal * sizeof(ATTR_DATA);
	pMsg = (G2C_SYNC_HERO_ATTR_LIST*)m_poPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	pMsg->wMsg = g2c_sync_hero_attr_list;
	pMsg->wSize = nSize;
	pMsg->dwHeroID = poHero->GetObjID();

	for (INT32 i = catDefault; i < catTotal; i++)
	{
		pMsg->astAttrData[i].byAttrID = i;
		pMsg->astAttrData[i].nAttrValue = poHero->GetAttrList().GetAttr(i);
	}

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoHeroAttrChange(CRole* poRole, INT32 eAttrType)
{
	INT32 nRetCode = 0;
	G2C_HERO_ATTR_CHANGE* pMsg = NULL;
	CHero* poHero = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_HERO_ATTR_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_HERO_ATTR_CHANGE));
	LOG_PROCESS_ERROR(pMsg);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	pMsg->wMsg = g2c_hero_attr_change;
	pMsg->byAttrID = eAttrType;
	pMsg->nAttrValue = poHero->GetAttr(eAttrType);

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_HERO_ATTR_CHANGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoChangeHeroAi(CRole* poRole, INT32 nAiType)
{
	INT32 nRetCode = 0;
	G2C_CHANGE_HERO_AI* pMsg = NULL;
	CHero* poHero = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_CHANGE_HERO_AI*)m_poPacketAllocator->Alloc(sizeof(G2C_CHANGE_HERO_AI));
	LOG_PROCESS_ERROR(pMsg);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	pMsg->wMsg = g2c_change_hero_ai;
	pMsg->dwHeroID = poHero->GetObjID();
	pMsg->nAiType = nAiType;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_CHANGE_HERO_AI));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoHireHero(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_HIRE_HERO* pMsg = NULL;
	CHero* poHero = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_HIRE_HERO*)m_poPacketAllocator->Alloc(sizeof(G2C_HIRE_HERO));
	LOG_PROCESS_ERROR(pMsg);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	pMsg->wMsg = g2c_hire_hero;
	pMsg->dwHeroID = poHero->GetObjID();
	pMsg->byHeroClass = poHero->GetClass();
	pMsg->byHeroSex = poHero->GetSex();
	pMsg->byHeroLevel = poHero->GetLevel();
	pMsg->nGrowth = poHero->GetGrowth();
	pMsg->byHeroAiType = poHero->GetAiType();

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_HIRE_HERO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CCliMessageHandler::DoFireHero(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_FIRE_HERO* pMsg = NULL;
	CHero* poHero = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_FIRE_HERO*)m_poPacketAllocator->Alloc(sizeof(G2C_FIRE_HERO));
	LOG_PROCESS_ERROR(pMsg);

	poHero = poRole->GetHero();
	LOG_PROCESS_ERROR(poHero);

	pMsg->wMsg = g2c_fire_hero;
	pMsg->dwHeroID = poHero->GetObjID();

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_FIRE_HERO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CCliMessageHandler::DoSummonHero(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_SUMMON_HERO* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_SUMMON_HERO*)m_poPacketAllocator->Alloc(sizeof(G2C_SUMMON_HERO));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_summon_hero;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SUMMON_HERO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CCliMessageHandler::DoRecallHero(CRole* poRole)
{
	INT32 nRetCode = 0;
	G2C_RECALL_HERO* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (G2C_RECALL_HERO*)m_poPacketAllocator->Alloc(sizeof(G2C_RECALL_HERO));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = g2c_recall_hero;

	nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_RECALL_HERO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}


#endif  // _ROBOT
