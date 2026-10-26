#ifndef _SPELL_BULLET_INL_H_
#define _SPELL_BULLET_INL_H_

inline void CBullet::SetFromObjID(UINT32 dwID)
{
	m_dwFromObjID = dwID;
}

inline UINT32 CBullet::GetFromObjID(void)
{
	return m_dwFromObjID;
}

inline UINT32 CBullet::GetCasterID(void)
{
	return m_dwCasterCharID;
}

inline INT32 CBullet::GetSpellID(void)
{
	return m_SpellData.m_nID;
}

inline INT32 CBullet::GetSpellLevel(void)
{
	return m_SpellData.m_nLevel;
}

inline INT32 CBullet::GetSpellRuneSlot(void)
{
	return m_SpellData.m_nRuneSlotID;
}

inline INT32 CBullet::GetBulletType(void)
{
	return m_eBulletType;
}

inline INT32 CBullet::GetParam1(void)
{
	return m_nParam1;
}

inline INT32 CBullet::GetParam2(void)
{
	return m_nParam2;
}

inline BOOL CBullet::IsFromMissile(void)
{
	return m_bFromMissile;
}

inline BOOL CBullet::IsTargetLocked(void)
{
	return m_bTargetLocked;
}


inline INT32 CBullet::GetEffectValue(void)
{
	return (INT32)m_llEffectValue;
}

inline void CBullet::SetTargetHpChangeValue(INT32 nValue)
{
	m_nTargetHpChangeValue = nValue;
}

inline INT32 CBullet::GetTargetHpChangeValue(void)
{
	return m_nTargetHpChangeValue;
}


inline void CBullet::SetEffectValue(INT32 nEffectValue)
{
	m_llEffectValue = nEffectValue;
}

inline CFlagBits& CBullet::GetEffectFlag(void)
{
	return m_oEffectFlag;
}

inline CFlagBits& CBullet::GetSpellFlag(void)
{
	return m_oSpellFlag;
}

inline void CBullet::SetSpellSerial(INT32 nSerial)
{
	m_nSpellSerial = nSerial;
}

inline INT32 CBullet::GetSpellSerial(void)
{
	return m_nSpellSerial;
}

inline void CBullet::SetX(INT64 nValue)
{
	m_llAttackX = nValue;
}

inline INT64 CBullet::GetX(void)
{
	return m_llAttackX;
}

inline INT32 CBullet::GetAtkHi(void)
{
	return m_nAtkHi;
}

inline INT32 CBullet::GetAtkLo(void)
{
	return m_nAtkLo;
}

inline INT64 CBullet::GetAttackRandom(void)
{
	return m_llAtkRandom;
}

inline ExtraParam* CBullet::GetSpellExParam(void)
{
	return &m_ExParam;
}

inline SPELL_ENTRY* CBullet::GetSpellData(void)
{
	return &m_SpellData;
}

inline INT32 CBullet::GetStiffFrm(void)
{
	return m_nStiffFrm;
}

inline INT32 CBullet::GetStiffRandomNum(void)
{
	return m_nStiffRandomNum;
}

inline CCharacter* CBullet::GetTarget(void)
{
	return m_poTarget;
}

inline INT32 CBullet::GetDelayFrame(void)
{
	return m_nDelayFrm;
}

inline INT32 CBullet::GetSpellAttr(INT32 eAttrType)
{
	LOG_PROCESS_ERROR(eAttrType > satInvalid && eAttrType < satTotal);

	return m_SpellData.m_nAttrTable[eAttrType];

Exit0:
	return 0;
}

inline BOOL CBullet::SetSpellAttr(INT32 eAttrType, INT32 nValue)
{
	LOG_PROCESS_ERROR(eAttrType > satInvalid && eAttrType < satTotal);

	m_SpellData.m_nAttrTable[eAttrType] = nValue;

	return TRUE;
Exit0:
	return FALSE;
}

inline void CBullet::SetRemoveFlag(BOOL bRemove)
{
	m_bRemoveFlag = bRemove;
}

inline BOOL CBullet::NeedRemove(void)
{
	return m_bRemoveFlag;
}

inline INT32 CBullet::GetCastSerial(void)
{
	return m_nCastSerial;
}
inline INT32 CBullet::GetEffectSerial(void)
{
	return m_nEffectSerial;
}

inline BASE_LIST_NODE& CBullet::GetListNode(void)
{
	return m_ListNode;
}

inline INT32 CBullet::GetIndex(void)
{
	return m_nIndex;
}

inline INT64 CBullet::GetTargetX(void)
{
	return m_llTargetX;
}

inline INT64 CBullet::GetTargetY(void)
{
	return m_llTargetY;
}

inline INT64 CBullet::GetTargetZ(void)
{
	return m_llTargetZ;
}

inline void CBullet::SetEventOwner(CCharacter* poOwner)
{
	m_poEventOwner = poOwner;
}

inline CCharacter* CBullet::GetEventOwner(void)
{
	return m_poEventOwner;
}



#endif // _spell_bullet_inl_h__
