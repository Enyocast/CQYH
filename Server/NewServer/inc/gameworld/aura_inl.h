#ifndef _AURA_INL_H_
#define _AURA_INL_H_

inline void CAura::SetID(INT32 nID)
{
	m_Data.m_nID = nID;
}

inline INT32 CAura::GetID(void)
{
	return m_Data.m_nID;
}

inline INT32 CAura::GetAttr(INT32 eAttrType)
{
	LOG_PROCESS_ERROR(eAttrType > aatInvalid && eAttrType < aatTotal);

	return m_Data.m_nAttrTable[eAttrType];
Exit0:
	return 0;
}

inline void CAura::CopyTo(CAura* p)
{
	memcpy(&p->m_Data, &m_Data, sizeof(m_Data));
}

inline void CAura::CopyData(AURA_ENTRY* pData)
{
	memcpy(pData, &m_Data, sizeof(m_Data));
}

inline const AURA_ENTRY* CAura::GetData(void)
{
	return &m_Data;
}

inline INT32 CAura::GetDurationFrm(void)
{
	return CONVERT_TIME(m_Data.m_nAttrTable[aatDuration]);
}

inline INT32 CAura::GetIntervalFrm(void)
{
	return CONVERT_TIME(m_Data.m_nAttrTable[aatInterval]);
}

inline INT32 CAura::GetDelayFrm(void)
{
	return CONVERT_TIME(m_Data.m_nAttrTable[aatDelay]);
}

inline INT32 CAura::GetEffectMinFrm(void)
{
	return CONVERT_TIME(m_Data.m_nAttrTable[aatEffectTimeMin]);
}


inline void CAuraTemplate::InitAttr(INT32 eAttrType, INT32 nVal)
{
	CAura::SetAttr(eAttrType, nVal);
}

inline void CAuraTemplate::InitWithData(AURA_ENTRY* pData)
{
	memcpy(&m_Data, pData, sizeof(m_Data));
}

#endif // _aura_inl_h__
