#include "stdafx.h"
#include "threat_list.h"

#include "game_world.h"
#include "scene_data.h"

CThreatList::CThreatList()
{
	m_ThreatList.Clear();
	m_ThreatenList.Clear();
	m_pOwner = NULL;
}

CThreatList::~CThreatList()
{
	UnInit();
}

BOOL CThreatList::Init(CCharacter* poOwner)
{
	m_ThreatList.Clear();
	m_ThreatenList.Clear();

	m_pOwner = poOwner;
	m_nThreatenFadeTime = CONVERT_TIME(g_GWConfig.nThreatFadeTime);
	m_nThreatFadeTime = CONVERT_TIME(g_GWConfig.nThreatFadeTime);

	return TRUE;
}

BOOL CThreatList::UnInit(void)
{
	Clear();

    m_pOwner = NULL;

	return TRUE;
}

BOOL CThreatList::ModifyThreatValue(CCharacter* poChar, INT32 nValue)
{
	INT32 nRetCode = 0;

	THREAT_NODE* pNode = NULL;
	THREAT_NODE* pPairNode = NULL;
    THREAT_NODE* pTargetNode = NULL;

	LOG_PROCESS_ERROR(poChar);
	PROCESS_SUCCESS(nValue == 0);

	// try to find char in the list
	pNode = (THREAT_NODE*)m_ThreatList.Head().pNext;
	while (pNode != &(m_ThreatList.Rear()))
	{
		if (pNode->dwCharID == poChar->GetObjID())
		{
			// already in threat list, modify threat value of the node.
			pNode->nThreatValue += nValue;
			LOG_PROCESS_ERROR(pNode->pPairNode != NULL);
			pNode->pPairNode->nLastUpdateLoop = (INT32)CGameWorld::GetInstance().GetGameFrame();
			CBaseList::Remove(pNode);
			break;
		}
		pNode = (THREAT_NODE*)pNode->pNext;
	}

	if(pNode == NULL || pNode == &m_ThreatList.Rear())
	{
		// not in threat list, create new node, and insert into list.
		pPairNode = CGameWorld::GetInstance().NewThreatNode();
		LOG_PROCESS_ERROR(pPairNode);
		pPairNode->pPrev = NULL;
		pPairNode->pNext = NULL;

		pPairNode->dwCharID = m_pOwner->GetObjID();
		pPairNode->nLastUpdateLoop = CGameWorld::GetInstance().GetGameFrame();

		pNode = CGameWorld::GetInstance().NewThreatNode();
		LOG_PROCESS_ERROR(pNode);
		pNode->pPrev = NULL;
		pNode->pNext = NULL;

		pNode->nThreatValue = nValue;
		pNode->dwCharID = poChar->GetObjID();
		pNode->pPairNode = pPairNode;

		pPairNode->pPairNode = pNode;

		nRetCode = poChar->GetThreatList().m_ThreatenList.PushRear(pPairNode);
		LOG_PROCESS_ERROR(nRetCode);
	}

	// now move pNode to the right place:

	pTargetNode = (THREAT_NODE*)m_ThreatList.Head().pNext;
	while (pTargetNode != &(m_ThreatList.Rear()))
	{
		if(pTargetNode->nThreatValue <= pNode->nThreatValue && ((THREAT_NODE*)(pTargetNode->pNext))->nThreatValue >= pNode->nThreatValue)
		{
			m_ThreatList.InsertAfter(pNode, pTargetNode);
			return TRUE;
		}

		pTargetNode = (THREAT_NODE*)pTargetNode->pNext;
	}

	m_ThreatList.PushRear(pNode);

Exit1:
	return TRUE;
Exit0:
	return FALSE;
}

BOOL CThreatList::ModifyChainThreatValue(CCharacter* poCharacter, INT32 nValue)
{
	INT32 nRetCode = 0;

	THREAT_NODE* pNode = NULL;
	LOG_PROCESS_ERROR(poCharacter);

	pNode = (THREAT_NODE*)m_ThreatenList.Head().pNext;
	while (pNode != &(m_ThreatenList.Rear()))
	{
		CCharacter* poAffectedChar = CGameWorld::GetInstance().FindValidCharacter(pNode->dwCharID);
		if(poAffectedChar != NULL)
		{
			CThreatList& AffectedThreatList = poAffectedChar->GetThreatList();
			nRetCode = AffectedThreatList.ModifyThreatValue(poCharacter, nValue);
			LOG_PROCESS_ERROR(nRetCode);
		}

		pNode = (THREAT_NODE*)pNode->pNext;
	}

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CThreatList::Clear(void)
{
	THREAT_NODE* pNode = NULL;

	pNode = (THREAT_NODE*)m_ThreatList.Head().pNext;
	while (pNode != &(m_ThreatList.Rear()))
	{
		CBaseList::Remove(pNode->pPairNode);
		CGameWorld::GetInstance().DelThreatNode(pNode->pPairNode);

		THREAT_NODE* pRemoveNode = pNode;
		pNode = (THREAT_NODE*)pNode->pNext;

		CBaseList::Remove(pRemoveNode);
		CGameWorld::GetInstance().DelThreatNode(pRemoveNode);
	}

	m_ThreatList.Clear();

	pNode = (THREAT_NODE*)m_ThreatenList.Head().pNext;
	while (pNode != &(m_ThreatenList.Rear()))
	{
		CBaseList::Remove(pNode->pPairNode);
		CGameWorld::GetInstance().DelThreatNode(pNode->pPairNode);

		THREAT_NODE* pRemoveNode = pNode;
		pNode = (THREAT_NODE*)pNode->pNext;

		CBaseList::Remove(pRemoveNode);
		CGameWorld::GetInstance().DelThreatNode(pRemoveNode);
	}

	m_ThreatenList.Clear();

	return TRUE;
Exit0:
    return FALSE;
}

CCharacter* CThreatList::GetFirstTarget(void)
{
	CCharacter* poChar = NULL;
	THREAT_NODE* pFirstNode = NULL;

	PROCESS_ERROR(!m_ThreatList.IsEmpty());

	pFirstNode = (THREAT_NODE*)m_ThreatList.Head().pNext;

	poChar = CGameWorld::GetInstance().FindValidCharacter(pFirstNode->dwCharID);
	PROCESS_ERROR(poChar);

	return poChar;
Exit0:
	return NULL;
}

BOOL CThreatList::MainLoop(void)
{
	THREAT_NODE* pNode = (THREAT_NODE*)m_ThreatenList.Head().pNext;
	while (pNode != &(m_ThreatenList.Rear()))
	{
		if (pNode->nLastUpdateLoop + m_nThreatenFadeTime < CGameWorld::GetInstance().GetGameFrame())
		{
			CBaseList::Remove(pNode->pPairNode);
			CGameWorld::GetInstance().DelThreatNode(pNode->pPairNode);

			THREAT_NODE* pRemoveNode = pNode;
			pNode = (THREAT_NODE*)pNode->pNext;
	
			CBaseList::Remove(pRemoveNode);
			CGameWorld::GetInstance().DelThreatNode(pRemoveNode);
		}
		else
			pNode = (THREAT_NODE*)pNode->pNext;
	}

	pNode = (THREAT_NODE*)m_ThreatList.Head().pNext;
	while (pNode != &(m_ThreatList.Rear()))
	{
		THREAT_NODE* pPairNode = pNode->pPairNode;

		if (pPairNode->nLastUpdateLoop + m_nThreatFadeTime < CGameWorld::GetInstance().GetGameFrame())
		{
			CBaseList::Remove(pPairNode);
			CGameWorld::GetInstance().DelThreatNode(pPairNode);

			THREAT_NODE* pRemoveNode = pNode;
			pNode = (THREAT_NODE*)pNode->pNext;
    	
			CBaseList::Remove(pRemoveNode);
			CGameWorld::GetInstance().DelThreatNode(pRemoveNode);
		}
		else
			pNode = (THREAT_NODE*)pNode->pNext;
	}

	return TRUE;
}

BOOL CThreatList::CheckThreat(UINT32 dwCharID)
{
    THREAT_NODE* pNode = NULL;

	pNode = (THREAT_NODE*)m_ThreatList.Head().pNext;
	while (pNode != &(m_ThreatList.Rear()))
	{
		LOG_PROCESS_ERROR(pNode);

		if (pNode->dwCharID == dwCharID)
            return TRUE;
        pNode = (THREAT_NODE*)pNode->pNext;
	}
Exit0:
	return FALSE;
}

BOOL CThreatList::CheckThreaten(UINT32 dwCharID)
{
    THREAT_NODE* pNode = NULL;

    pNode = (THREAT_NODE*)m_ThreatenList.Head().pNext;
    while (pNode != &(m_ThreatenList.Rear()))
    {
        LOG_PROCESS_ERROR(pNode);

        if (pNode->dwCharID == dwCharID)
            return TRUE;
        pNode = (THREAT_NODE*)pNode->pNext;
    }
Exit0:
    return FALSE;
}

BOOL CThreatList::IsEmpty(void)
{
	return m_ThreatList.IsEmpty() && m_ThreatenList.IsEmpty();
Exit0:
    return TRUE;
}

void CThreatList::RemoveThreatNode(UINT32 dwCharID)
{
	THREAT_NODE* pNode = NULL;

	pNode = (THREAT_NODE*)m_ThreatList.Head().pNext;
	while (pNode != &(m_ThreatList.Rear()))
	{
		if (pNode->dwCharID == dwCharID)
		{
			CBaseList::Remove(pNode->pPairNode);
			CGameWorld::GetInstance().DelThreatNode(pNode->pPairNode);

			THREAT_NODE* pRemoveNode = pNode;
			pNode = (THREAT_NODE*)pNode->pNext;

			CBaseList::Remove(pRemoveNode);
			CGameWorld::GetInstance().DelThreatNode(pRemoveNode);
		}
		else
			pNode = (THREAT_NODE*)pNode->pNext;
	}
}
