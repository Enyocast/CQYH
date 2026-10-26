#ifndef _TARGET_SCANNER_INL_H_
#define _TARGET_SCANNER_INL_H_

inline UINT32 CTargetScanner::GetLockedTarget(void)
{
	PROCESS_ERROR(m_pLockedTargetNode != NULL);

	return m_pLockedTargetNode->dwTargetID;
Exit0:
	return 0;
}

inline void CTargetScanner::SetDirection(INT32 nDirection)
{
	m_nDirection = nDirection;
}

inline INT32 CTargetScanner::GetDirection(void)
{
	return m_nDirection;
}

inline INT32 CTargetScanner::GetTargetObjTypeLimit(void)
{
	return m_nTargetObjTypeLimit;
}

inline INT32 CTargetScanner::GetRelationshipLimit(void)
{
	return m_nRelationshipLimit;
}

inline INT32 CTargetScanner::GetStanceLimit(void)
{
	return m_nStanceLimit;
}

inline BOOL CTargetScanner::IsCorpseValid(void)
{
	return m_bCorpseValid;
}

inline BOOL CTargetScanner::IgnoreTargetRadius(void)
{
	return m_bIgnoreTargetRadius;
}

inline void CTargetScanner::SetCenterPt(INT64 x, INT64 y, INT64 z)
{
	m_llCenterX = x;
	m_llCenterY = y;
	m_llCenterZ = z;
}

inline void CTargetScanner::GetCenterPt(INT64& x ,INT64& y, INT64& z)
{
	x = m_llCenterX;
	y = m_llCenterY;
	z = m_llCenterZ;
}

inline void CTargetScanner::SetTargetPt(INT64 x, INT64 y, INT64 z)
{
	m_llTargetX = x;
	m_llTargetY = y;
	m_llTargetZ = z;
}

inline void CTargetScanner::GetTargetPt(INT64& x ,INT64& y, INT64& z)
{
	x = m_llTargetX;
	y = m_llTargetY;
	z = m_llTargetZ;
}

inline INT64 CTargetScanner::GetTargetX(void)
{
	return m_llTargetX;
}

inline INT64 CTargetScanner::GetTargetY(void)
{
	return m_llTargetY;
}

inline INT64 CTargetScanner::GetTargetZ(void)
{
	return m_llTargetZ;
}

inline INT64 CTargetScanner::GetCenterX(void)
{
	return m_llCenterX;
}

inline INT64 CTargetScanner::GetCenterY(void)
{
	return m_llCenterY;
}

inline INT64 CTargetScanner::GetCenterZ(void)
{
	return m_llCenterZ;
}

inline BOOL CTargetScanner::UseWeaponRange(void)
{
	return m_bUseWeaponRange;
}

inline INT32 CTargetScanner::GetRangeType(void)
{
	return m_eRangeType;
}

inline INT32 CTargetScanner::GetConvertedParam1(void)
{
	return CONVERT_LENGTH(m_nParam1);
}

inline INT32 CTargetScanner::GetConvertedParam2(void)
{
	return CONVERT_LENGTH(m_nParam2);
}

inline INT32 CTargetScanner::GetParam1(void)
{
	return m_nParam1;
}

inline INT32 CTargetScanner::GetParam2(void)
{
	return m_nParam2;
}

inline INT32 CTargetScanner::GetParam3(void)
{
	return m_nParam3;
}

inline INT32 CTargetScanner::GetTargetCount(void)
{
	return m_nTargetCount;
}

inline INT32 CTargetScanner::GetTargetCheckNode(void)
{
	return m_nTargetCheckNode;
}


#endif // _target_scanner_inl_h__
