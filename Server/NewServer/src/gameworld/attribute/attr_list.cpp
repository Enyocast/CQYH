#include "stdafx.h"
#include "attr_list.h"
#include "attr_conversion_data.h"
#include "attr_modifier.h"
#include "character.h"
#include "id_def.h"

CAttrList::CAttrList(void)
{
	Init();
}

void CAttrList::Init(void)
{
	memset(m_bAttrEnabled, TRUE, sizeof(m_bAttrEnabled));
	memset(m_nAttrList, 0, sizeof(m_nAttrList));
	memset(m_nAttrListBase, 0, sizeof(m_nAttrListBase));
	memset(m_nAttrListA, 0, sizeof(m_nAttrListA));
	memset(m_nAttrListB, 0, sizeof(m_nAttrListB));
}

void CAttrList::ResetExAttrBase(void)
{
}


void CAttrList::ReCalculateAttr(CCharacter* pSelf, INT32 eAttrType)
{
    INT64 nAttrA = 0;
    INT64 nAttrB = 0;
    
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	nAttrA = m_nAttrListBase[eAttrType] + m_nAttrListA[eAttrType];

	nAttrB = GetAttrB(eAttrType);

	m_nAttrList[eAttrType] = nAttrA * (RATE_MAX + nAttrB) / RATE_MAX;

	if (eAttrType == catMaxMp)
	{
		INT32 nMpLimit = m_nAttrList[catMaxMp] - 1;

		if (m_nAttrList[catMpToHpRemain] >= nMpLimit)
		{
			pSelf->MpToHp(nMpLimit);
		}
		else
		{
			pSelf->MpToHp(m_nAttrList[catMpToHpRemain]);
		}
	}

	pSelf->DoSyncAttrChange(eAttrType);
Exit0:
	return;
}

void CAttrList::CalculateAll(CCharacter* pSelf)
{
	for(INT32 i = catDefault; i < catTotal; ++i)
		ReCalculateAttr(pSelf, i);
}
