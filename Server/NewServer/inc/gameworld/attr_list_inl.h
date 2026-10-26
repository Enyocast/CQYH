#ifndef _ATTR_LIST_INL_H_
#define _ATTR_LIST_INL_H_

inline INT32 CAttrList::ForceGetAttr(INT32 eAttrType)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	return m_nAttrList[eAttrType];
Exit0:
	return 0;
}

inline INT32 CAttrList::GetAttrA(INT32 eAttrType)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	return m_nAttrListA[eAttrType];
Exit0:
	return 0;
}

inline INT32 CAttrList::GetAttrB(INT32 eAttrType)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	return m_nAttrListB[eAttrType];
Exit0:
	return 0;
}

inline void CAttrList::SetAttrA(CCharacter* pSelf, INT32 eAttrType, INT32 nValue)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	m_nAttrListA[eAttrType] = nValue;

	ReCalculateAttr(pSelf, eAttrType);
Exit0:
	return;
}

inline void CAttrList::AddAttrA(CCharacter* pSelf, INT32 eAttrType, INT32 nValue)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	m_nAttrListA[eAttrType] += nValue;

	ReCalculateAttr(pSelf, eAttrType);

Exit0:
	return;
}

inline void CAttrList::SetAttrB(CCharacter* pSelf, INT32 eAttrType, INT32 nValue)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	m_nAttrListB[eAttrType] = nValue;

	ReCalculateAttr(pSelf, eAttrType);
Exit0:
	return;
}

inline void CAttrList::AddAttrB(CCharacter* pSelf, INT32 eAttrType, INT32 nValue)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	m_nAttrListB[eAttrType] += nValue;

	ReCalculateAttr(pSelf, eAttrType);

Exit0:
	return;
}

inline INT32 CAttrList::GetAttrBase(INT32 eAttrType)
{
    LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

    return m_nAttrListBase[eAttrType];
Exit0:
    return 0;
}

inline void CAttrList::SetAttrBase(CCharacter* pSelf, INT32 eAttrType, INT32 nValue)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	m_nAttrListBase[eAttrType] = nValue;

	ReCalculateAttr(pSelf, eAttrType);
Exit0:
	return;

}

inline void CAttrList::AddAttrBase(CCharacter* pSelf, INT32 eAttrType, INT32 nValue)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);

	m_nAttrListBase[eAttrType] += nValue;

	ReCalculateAttr(pSelf, eAttrType);

Exit0:
	return;
}

inline INT32 CAttrList::GetAttr(INT32 eAttrType)
{
	LOG_PROCESS_ERROR(eAttrType >= catDefault && eAttrType < catTotal);

	if(!m_bAttrEnabled[eAttrType])
		return 0;

	return m_nAttrList[eAttrType];

Exit0:
	return 0;
}

inline void CAttrList::CopyAttr(INT32 nList[], INT32 nCount)
{
	LOG_PROCESS_ERROR(nCount*sizeof(nList[0]) >= sizeof(m_nAttrList));

	memcpy(nList, m_nAttrList, sizeof(m_nAttrList));

Exit0:
	return;
}

inline void CAttrList::CopyTo(CAttrList* pList)
{
	LOG_PROCESS_ERROR(pList);

	memcpy(pList->m_nAttrList, m_nAttrList, sizeof(m_nAttrList));
	memcpy(pList->m_nAttrListA, m_nAttrListA, sizeof(m_nAttrListA));
	memcpy(pList->m_nAttrListB, m_nAttrListB, sizeof(m_nAttrListB));

Exit0:
	return;
}

inline void CAttrList::EnableAttr(INT32 eAttrType, BOOL bEnable)
{
	LOG_PROCESS_ERROR(eAttrType > catDefault && eAttrType < catTotal);
	
	m_bAttrEnabled[eAttrType] = bEnable;

Exit0:
	return;
}

#endif // _attr_list_inl_h__
