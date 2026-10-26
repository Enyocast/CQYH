#ifndef _SPELL_INSTANCE_INL_H_
#define _SPELL_INSTANCE_INL_H_

inline UINT32 CSpellInstance::GetFromObjID(void)
{
	return m_dwFromObjID;
}

inline INT32 CSpellInstance::GetBulletAttack(void)
{
	return m_nAttackForce;
}

inline INT64 CSpellInstance::GetInitX(void)
{
	return m_llInitX;
}

inline INT64 CSpellInstance::GetInitY(void)
{
	return m_llInitY;
}

inline INT64 CSpellInstance::GetInitZ(void)
{
	return m_llInitZ;
}

inline INT32 CSpellInstance::GetAtkSpeedFactor(void)
{
	return m_nAtkSpeedFactor;
}

inline INT32 CSpellInstance::GetWeaponSpeedFactor(void)
{
	return m_nWeaponSpeedFactor;
}

inline INT32 CSpellInstance::GetWeaponStiffFactor(void)
{
	return m_nWeaponStiffFactor;
}

inline CTargetScanner& CSpellInstance::GetScanner(void)
{
	return m_Scanner;
}

inline INT32 CSpellInstance::GetStartFrm(void)
{
	return m_nStartFrm;
}

inline BOOL CSpellInstance::IsChannelOver(void)
{
	PROCESS_ERROR(!IsSelfCancened());
	PROCESS_ERROR(m_Data.m_nAttrTable[satInterval] > 0);

	if(m_Data.m_nAttrTable[satChannelCount] <= 0)
		return m_nCastSerial >= (m_Data.m_nAttrTable[satPrepareTimeMax] - m_Data.m_nAttrTable[satPrepareTimeMin]) / m_Data.m_nAttrTable[satInterval];

	return m_nCastSerial >= m_Data.m_nAttrTable[satChannelCount];
Exit0:
	return TRUE;
}

inline INT32 CSpellInstance::GetSpellSerial(void)
{
	return m_nSpellSerial;
}

inline INT32 CSpellInstance::GetCastSerial(void)
{
	return m_nCastSerial;
}

inline INT32 CSpellInstance::GetEffectSerial(void)
{
	return m_nEffectSerial;
}

inline INT32 CSpellInstance::GetPrepareTimeMinFrm(void)
{
	PROCESS_ERROR(m_Data.m_nAttrTable[satPrepareTimeMin] > 0);

	return m_nPrepareTimeMinFrm;
Exit0:
	return 0;
}

inline INT32 CSpellInstance::GetPrepareTimeMaxFrm(void)
{
	PROCESS_ERROR(m_Data.m_nAttrTable[satPrepareTimeMax] > 0);

	return m_nPrepareTimeMaxFrm;
Exit0:
	return 0;
}

inline INT32 CSpellInstance::GetIntervalFrm(void)
{
	PROCESS_ERROR(m_Data.m_nAttrTable[satInterval] > 0);

	return m_nIntervalFrm;
Exit0:
	return 0;
}

inline INT32 CSpellInstance::GetHardTimeFrm(void)
{
	PROCESS_ERROR(m_Data.m_nAttrTable[satHardTime] > 0);

	return m_nHardTimeFrm;
Exit0:
	return 0;
}

inline INT32 CSpellInstance::GetResetTimeFrm(void)
{
	return m_nResetTimeFrm;
}

inline INT32 CSpellInstance::GetCacheTimeFrm(void)
{
	return m_nCacheTimeFrm;
}

inline INT32 CSpellInstance::GetAccumulateTimeMaxFrm(void)
{
	return m_nAccumulateTimeMaxFrm;
}

inline INT32 CSpellInstance::GetStiffFrm(void)
{
	PROCESS_ERROR(m_Data.m_nAttrTable[satBaseStiffTime] > 0);

	return m_nStiffFrm;
Exit0:
	return 0;
}

inline INT32 CSpellInstance::GetExCastFrm(INT32 idx)
{
	LOG_PROCESS_ERROR(idx >= 0 && idx < MAX_EX_CAST);

	return m_nExCastFrm[idx];
Exit0:
	return 0;
}


inline void CSpellInstance::HitTarget(BOOL bHit)
{
	m_bHitTarget = bHit;
}

inline BOOL CSpellInstance::HasHitTarget(void)
{
	return m_bHitTarget;
}

inline void CSpellInstance::HitRole(BOOL bHit)
{
	m_bHitRole = bHit;
}

inline BOOL CSpellInstance::HasHitRole(void)
{
	return m_bHitRole;
}

inline void CSpellInstance::SetFastStop(BOOL bFastStop)
{
	m_bFastStop = bFastStop;
}

inline BOOL CSpellInstance::IsFastStop(void)
{
	return m_bFastStop;
}

inline void CSpellInstance::SetSelfCancel(BOOL bCancel)
{
	m_bSelfCanceled = bCancel;
}

inline BOOL CSpellInstance::IsSelfCancened(void)
{
	if(m_bSelfCanceled && m_nCastSerial >= m_Data.m_nAttrTable[satMinEffectCount])
		return TRUE;

	return FALSE;
}

inline INT32 CSpellInstance::GetBulletCount(void)
{
	return (INT32)m_BulletList.size();
}

inline void CSpellInstance::ClearBulletList(void)
{
	m_BulletList.clear();
}

inline void CSpellInstance::BeginBullet(void)
{
	m_BulletItr = m_BulletList.begin();
}

inline CBullet* CSpellInstance::NextBullet(void)
{
	CBullet* poBullet = NULL;

	PROCESS_ERROR(m_BulletItr != m_BulletList.end());

	poBullet = *m_BulletItr;
	++m_BulletItr;

	return poBullet;
Exit0:
	return NULL;
}

inline void CSpellInstance::AddBullet(CBullet* poBullet)
{
	m_BulletList.push_back(poBullet);
}

inline CFlagBits& CSpellInstance::GetFlagBits(void)
{
	return m_FlagBits;
}

inline SimpleListNode& CSpellInstance::GetStackNode(void)
{
	return m_StackNode;
}


#endif // _spell_instance_inl_h__

