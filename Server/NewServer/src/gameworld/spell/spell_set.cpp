#include "stdafx.h"
#include "spell_set.h"
#include "spell.h"
#include "spell_data.h"
#include "game_world.h"
#include "spell_config.h"
#include "rune_data.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CSpellSet::CSpellSet(void)
{
	m_nSpellID = 0;
	m_nLevel = 0;
	m_nRuneSlot = 0;
	m_bEnabled = FALSE;
	m_nCurrentPts = 0;
	m_nRefCount = 0;
}

CSpellSet::~CSpellSet(void)
{

}

void CSpellSet::Init(INT32 nID, INT32 nLevel, BOOL bNeedSave)
{
	Clear();
	m_nSpellID = nID;
	m_nLevel = nLevel;

	m_bNeedSave = bNeedSave;
	m_nCurrentPts = 0;

	if (nLevel >= 0)
		m_nRefCount++;
}

CSpell* CSpellSet::GetSpell(void)
{
	INT32 nLevel = GetLevel();
	INT32 nRuneSlot = GetRuneSlot();

	CSpellTemplate* poSpell = CSpellConfig::GetInstance().FindSpellTemplate(m_nSpellID, nLevel, nRuneSlot);
	PROCESS_ERROR(poSpell);

	return poSpell;
Exit0:
	return NULL;
}

void CSpellSet::Clear(void)
{
	m_nSpellID = 0;
	m_nLevel = -1;
	m_bEnabled = FALSE;
	m_bNeedSave = FALSE; 
	m_nCurrentPts = 0;
	m_nRefCount = 0;

	m_nRuneSlot = 0;
	m_nEquipSlot = qssSlotInvalid;
	m_EvtMap.clear();

	ClearNextSpell();

}

void CSpellSet::Release(void)
{
	Clear();

	ItemSpellLevelNode* pLevelNode = NULL;
	pLevelNode = (ItemSpellLevelNode*)m_ItemLevelList.Head().pNext;
	while (pLevelNode != &(m_ItemLevelList.Rear()))
	{
		ItemSpellLevelNode* pRemoveNode = pLevelNode;
		pLevelNode = (ItemSpellLevelNode*)pLevelNode->pNext;

		CBaseList::Remove(pRemoveNode);
		CGameWorld::GetInstance().DelItemSpellLevelNode(pRemoveNode);
	}

	m_ItemLevelList.Clear();

	ItemSpellRuneNode* pRuneNode = NULL;
	pRuneNode = (ItemSpellRuneNode*)m_ItemRuneList.Head().pNext;
	while (pRuneNode != &(m_ItemRuneList.Rear()))
	{
		ItemSpellRuneNode* pRemoveNode = pRuneNode;
		pRuneNode = (ItemSpellRuneNode*)pRuneNode->pNext;

		CBaseList::Remove(pRemoveNode);
		CGameWorld::GetInstance().DelItemSpellRuneNode(pRemoveNode);
	}

	m_ItemRuneList.Clear();

	CGameWorld::GetInstance().DelSpellSet(this);
}

void CSpellSet::RecordNextSpell(CCharacter* poOwner, INT32 nNextSpellID, INT32 nResetFrm)
{
	if(nNextSpellID != 0)
	{
		m_NextSpell.nSpellID = nNextSpellID;
		m_NextSpell.dwNextResetFrm = CGameWorld::GetInstance().GetGameFrame() + nResetFrm;
	}
	else
	{
		ClearNextSpell();
	}
}

void CSpellSet::ClearNextSpell(void)
{
	memset(&m_NextSpell, 0, sizeof(m_NextSpell));
}

BOOL CSpellSet::RecordEvt(INT32 eOccasionID, UINT64 qwEventID)
{
	INT32 nRetCode = 0;
	UINT64 qwCheckID = GetEvtID(eOccasionID);
	LOG_PROCESS_ERROR(qwCheckID == 0);

	nRetCode = m_EvtMap.insert(std::make_pair(eOccasionID, qwEventID)).second;
	LOG_PROCESS_ERROR(nRetCode);

	return nRetCode;
Exit0:
	return 0;
}

UINT64 CSpellSet::GetEvtID(INT32 eOccasionID)
{
	TEvtMap::iterator itr = m_EvtMap.find(eOccasionID);
	PROCESS_ERROR(itr != m_EvtMap.end());

	return itr->second;
Exit0:
	return 0;
}

void CSpellSet::RemoveEvt(INT32 eOccasionID)
{
	m_EvtMap.erase(eOccasionID);
}

BOOL CSpellSet::AddItemSpellLevelNode(UINT64 qwItemGuid, INT32 nLevel)
{
	ItemSpellLevelNode* pLevelNode = NULL;
	BOOL bFindPlace = FALSE;

	pLevelNode = CGameWorld::GetInstance().NewItemSpellLevelNode();
	LOG_PROCESS_ERROR(pLevelNode);

	memset(pLevelNode, 0, sizeof(ItemSpellLevelNode));

	pLevelNode->qwItemGuid = qwItemGuid;
	pLevelNode->nLevel = nLevel;

	for (BASE_LIST_NODE* pNode = m_ItemLevelList.Head().pNext; pNode != &m_ItemLevelList.Rear(); pNode = pNode->pNext)
	{
		ItemSpellLevelNode* pItemSpellNode = (ItemSpellLevelNode*)pNode;
		if (pItemSpellNode->nLevel < nLevel)
		{
			m_ItemLevelList.InsertBefore(pLevelNode, pNode);
			bFindPlace = TRUE;
			break;
		}
	}

	if (!bFindPlace)
	{
		m_ItemLevelList.PushRear(pLevelNode);
	}

	m_nRefCount++;

	return TRUE;

Exit0:
	if (pLevelNode)
	{
		CBaseList::Remove(pLevelNode);
		CGameWorld::GetInstance().DelItemSpellLevelNode(pLevelNode);
	}

	return FALSE;
}

BOOL CSpellSet::AddItemSpellRuneNode(UINT64 qwItemGuid, INT32 nItemRuneID)
{
	ItemSpellRuneNode* pRuneNode = NULL;
	BOOL bFindPlace = FALSE;
	INT32 nRuneSlot = 0;
	INT32 nRunePriority = 0;

	{
		const RUNE_DATA* pRuneData = CDataManager<RUNE_DATA>::GetInstance().GetData(nItemRuneID);
		if (pRuneData)
		{
			nRuneSlot = pRuneData->nRuneSlot;
			nRunePriority = pRuneData->nPriority;
		}
	}

	pRuneNode = CGameWorld::GetInstance().NewItemSpellRuneNode();
	LOG_PROCESS_ERROR(pRuneNode);

	memset(pRuneNode, 0, sizeof(ItemSpellRuneNode));

	bFindPlace = FALSE;

	pRuneNode->qwItemGuid = qwItemGuid;
	pRuneNode->nRuneSlot = nRuneSlot;
	pRuneNode->nRunePriority = nRunePriority;

	for (BASE_LIST_NODE* pNode = m_ItemRuneList.Head().pNext; pNode != &m_ItemRuneList.Rear(); pNode = pNode->pNext)
	{
		ItemSpellRuneNode* pItemSpellNode = (ItemSpellRuneNode*)pNode;

		if (nRunePriority >= pItemSpellNode->nRunePriority)
		{
			m_ItemRuneList.InsertBefore(pRuneNode, pNode);
			bFindPlace = TRUE;
			break;
		}
	}
	if (!bFindPlace)
	{
		m_ItemRuneList.PushRear(pRuneNode);
	}

	return TRUE;

Exit0:
	if (pRuneNode)
	{
		CBaseList::Remove(pRuneNode);
		CGameWorld::GetInstance().DelItemSpellRuneNode(pRuneNode);
	}

	return FALSE;

}

BOOL CSpellSet::RemoveItemSpellLevelNode(UINT64 qwItemGuid)
{
	ItemSpellLevelNode* pLevelNode = (ItemSpellLevelNode*)m_ItemLevelList.Head().pNext;
	while(pLevelNode != &(m_ItemLevelList.Rear()))
	{
		ItemSpellLevelNode* pItemSpellNode = (ItemSpellLevelNode*)pLevelNode;
		if (pItemSpellNode->qwItemGuid != qwItemGuid)
		{
			pLevelNode = (ItemSpellLevelNode*)pLevelNode->pNext;
			continue;
		}

		ItemSpellLevelNode* pRemoveNode = pLevelNode;
		pLevelNode = (ItemSpellLevelNode*)pLevelNode->pNext;
		{
			CBaseList::Remove(pRemoveNode);
			CGameWorld::GetInstance().DelItemSpellLevelNode(pRemoveNode);

			if (m_nLevel < 0)
				m_nCurrentPts = 0;
		}
	}

	m_nRefCount--;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CSpellSet::RemoveItemSpellRuneNode(UINT64 qwItemGuid)
{
	ItemSpellRuneNode* pRuneNode = (ItemSpellRuneNode*)m_ItemRuneList.Head().pNext;
	while(pRuneNode != &(m_ItemRuneList.Rear()))
	{
		ItemSpellRuneNode* pItemSpellNode = (ItemSpellRuneNode*)pRuneNode;
		if (pItemSpellNode->qwItemGuid != qwItemGuid)
		{
			pRuneNode = (ItemSpellRuneNode*)pRuneNode->pNext;
			continue;
		}

		ItemSpellRuneNode* pRemoveNode = pRuneNode;
		pRuneNode = (ItemSpellRuneNode*)pRuneNode->pNext;
		{
			CBaseList::Remove(pRemoveNode);
			CGameWorld::GetInstance().DelItemSpellRuneNode(pRemoveNode);
		}
	}
	return TRUE;
Exit0:
	return FALSE;
}

INT32 CSpellSet::GetLevel(void)
{
	INT32 nSpellLevel = m_nLevel;

	if (m_nLevel <= 0)
	{
		ItemSpellLevelNode* pLevelNode = NULL;

		pLevelNode = (ItemSpellLevelNode*)m_ItemLevelList.Head().pNext;
		if (pLevelNode && pLevelNode != &m_ItemLevelList.Rear())
		{
			nSpellLevel = pLevelNode->nLevel;
		}
	}

	return nSpellLevel;
}

INT32 CSpellSet::GetRuneSlot(void)
{
	INT32 nRuneSlot = m_nRuneSlot;

	if (m_nRuneSlot <= 0)
	{
		ItemSpellRuneNode* pRuneNode = NULL;

		pRuneNode = (ItemSpellRuneNode*)m_ItemRuneList.Head().pNext;
		if(pRuneNode && pRuneNode != &m_ItemRuneList.Rear())
		{
			nRuneSlot = pRuneNode->nRuneSlot;
		}
	}

	return nRuneSlot;
}

void CSpellSet::LevelUp(void)
{
	if (m_nLevel < 0)
	{
		ItemSpellLevelNode* pLevelNode = NULL;

		pLevelNode = (ItemSpellLevelNode*)m_ItemLevelList.Head().pNext;
		if (pLevelNode && pLevelNode != &m_ItemLevelList.Rear())
		{
			pLevelNode->nLevel++;
		}
	}
	else
		m_nLevel++;
}

void CSpellSet::AddPts(INT32 nValue)
{
	if (m_nLevel < 0)
	{
		ItemSpellLevelNode* pLevelNode = NULL;

		pLevelNode = (ItemSpellLevelNode*)m_ItemLevelList.Head().pNext;
		if (pLevelNode && pLevelNode != &m_ItemLevelList.Rear())
		{
			pLevelNode->nPts += nValue;
		}
	}
	else
		m_nCurrentPts += nValue;
}

INT32 CSpellSet::GetPts(void)
{
	if (m_nLevel < 0)
	{
		ItemSpellLevelNode* pLevelNode = NULL;

		pLevelNode = (ItemSpellLevelNode*)m_ItemLevelList.Head().pNext;
		if (pLevelNode && pLevelNode != &m_ItemLevelList.Rear())
		{
			return pLevelNode->nPts;
		}
	}

	return m_nCurrentPts;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
