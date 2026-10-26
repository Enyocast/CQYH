#ifndef _AURA_INSTANCE_INL_H_
#define _AURA_INSTANCE_INL_H_

inline UINT32 CAuraInstance::GetInstanceID(void)
{
	return m_dwInstanceID;
}

inline void CAuraInstance::AddEventID(UINT64 qwEventID)
{
	m_EventIdList.push_back(qwEventID);
}

inline CAuraInstance::TEventIdList& CAuraInstance::GetEventIdList(void)
{
	return m_EventIdList;
}

inline void CAuraInstance::SetStackCount(INT32 nCount)
{
	m_nStackCount = nCount;
	m_bNeedSync = TRUE;
}

inline INT32 CAuraInstance::GetStackCount(void)
{
	return m_nStackCount;
}

inline void CAuraInstance::SetSpellID(INT32 nID)
{
	m_nSpellID = nID;
}

inline INT32 CAuraInstance::GetSpellID(void)
{
	return m_nSpellID;
}

inline void CAuraInstance::SetSpellLevel(INT32 nLevel)
{
	m_nSpellLevel = nLevel;
}

inline INT32 CAuraInstance::GetSpellLevel(void)
{
	return m_nSpellLevel;
}

inline void CAuraInstance::SetCharLevel(INT32 nLevel)
{
	m_nCharLevel = nLevel;
}

inline INT32 CAuraInstance::GetCharLevel(void)
{
	return m_nCharLevel;
}

inline BASE_LIST_NODE& CAuraInstance::GetListNode(void)
{
	return m_ListNode;
}

inline SimpleListNode& CAuraInstance::GetStackNode(void)
{
	return m_StackNode;
}

inline void CAuraInstance::ResetSync(void)
{
	m_bNeedSync = FALSE;
}

inline BOOL CAuraInstance::NeedSync(void)
{
	return m_bNeedSync;
}

inline void CAuraInstance::SetRemoveFlag(BOOL bRemove)
{
	m_bNeedRemove = bRemove;
}

inline BOOL CAuraInstance::NeedRemove(void)
{
	return m_bNeedRemove;
}

inline UINT32 CAuraInstance::GetCasterID(void)
{
	return m_dwCasterID;
}

inline UINT32 CAuraInstance::GetFromObjID(void)
{
	return m_dwFromObjID;
}

inline void CAuraInstance::SetStrengthLevel(INT32 nValue)
{
	m_nStrengthLevel = nValue;
}

inline INT32 CAuraInstance::GetStrengthLevel(void)
{
	return m_nStrengthLevel;
}


inline void CAuraInstance::SetTotalEffectValue(INT32 nValue)
{
	m_nTotalEffectValue = nValue;
}

inline INT32 CAuraInstance::GetTotalEffectValue(void)
{
	return m_nTotalEffectValue;
}

inline void CAuraInstance::SetEffectPct(INT32 nValue)
{
	m_nEffectPct = nValue;
}

inline INT32 CAuraInstance::GetEffectPct(void)
{
	return m_nEffectPct;
}

inline void CAuraInstance::SetEffectValue(INT32 nValue)
{
	m_nEffectValue = nValue;
}

inline INT32 CAuraInstance::GetEffectValue(void)
{
	return m_nEffectValue;
}

inline ExtraParam* CAuraInstance::GetExtraParam(void)
{
	return &m_ExtraParam;
}

inline BOOL CAuraInstance::SetExtraData(INT32 idx, INT32 nValue)
{
	LOG_PROCESS_ERROR(idx >= 0 && idx < MAX_AURA_EXTRA_DATA);
	LOG_PROCESS_ERROR(!m_ExtraData[idx].m_bSet);

	m_ExtraData[idx].m_bSet = TRUE;
	m_ExtraData[idx].m_nValue = nValue;

	return TRUE;
Exit0:
	return FALSE;
}

inline void CAuraInstance::ResetExtraData(INT32 idx)
{
	LOG_PROCESS_ERROR(idx >= 0 && idx < MAX_AURA_EXTRA_DATA);

	m_ExtraData[idx].m_bSet = FALSE;
	m_ExtraData[idx].m_nValue = 0;

Exit0:
	return;
}

inline BOOL CAuraInstance::GetExtraData(INT32 idx, INT32& nValue)
{
	LOG_PROCESS_ERROR(idx >= 0 && idx < MAX_AURA_EXTRA_DATA);
	PROCESS_ERROR(m_ExtraData[idx].m_bSet);

	nValue = m_ExtraData[idx].m_nValue;

	return TRUE;
Exit0:
	return FALSE;
}

inline void CAuraInstance::SetAtk(INT32 nAtk)
{
	m_llAtk = nAtk;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//inline CAuraInstance* CAuraList::GetStaticAura(INT32 nEffectType)
//{
//	PROCESS_ERROR(nEffectType > auetNone && nEffectType < auetTotal);
//
//	if(m_pStaticAura[nEffectType] != NULL)
//	{
//		if(m_pStaticAura[nEffectType]->NeedRemove())
//			return NULL;
//	}
//
//	return m_pStaticAura[nEffectType];
//Exit0:
//	return NULL;
//}

inline INT32 CAuraList::GetTopDisplayAuraID(INT32 nGroup)
{
	LOG_PROCESS_ERROR(nGroup > adgInvalid && nGroup < adgTotal);

	return m_TopAuraDisplay[nGroup].nAuraID;
Exit0:
	return 0;
}

inline UINT32 CAuraList::GetTopDisplayAuraInstanceID(INT32 nGroup)
{
	LOG_PROCESS_ERROR(nGroup > adgInvalid && nGroup < adgTotal);

	return m_TopAuraDisplay[nGroup].nInstanceID;
Exit0:
	return 0;
}

#endif // _aura_instance_inl_h__
