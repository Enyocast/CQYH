#ifndef _SPELL_SET_H_
#define _SPELL_SET_H_

#include "spell_def.h"
#include "base_list.h"

class CSpell;
struct RUNE_DATA;
class CCharacter;


struct NextSpell
{
	INT32 dwNextResetFrm;
	INT32 nSpellID;
};

struct ItemSpellLevelNode : public BASE_LIST_NODE
{
	INT32 nLevel;
	INT32 nPts;
	UINT64 qwItemGuid;
};

struct ItemSpellRuneNode : public BASE_LIST_NODE
{
	INT32 nRuneSlot;
	INT32 nRunePriority;
	UINT64 qwItemGuid;
};

class CSpellSet
{
public:
	CSpellSet(void);
	virtual ~CSpellSet(void);
	void Release(void);

	void Init(INT32 nID, INT32 nLevel, BOOL bNeedSave);
	void Clear(void);

	inline void SetLevel(INT32 nLevel);
	inline void SetRuneSlot(INT32 nRuneSlot);
	inline void Enable(BOOL bVal);
	inline BOOL SetEquipSlot(INT32 nSlot);

	inline INT32 GetID(void);
	inline INT32 GetActualLevel(void);
	inline INT32 GetActualRuneSlot(void);

	// not inline: these are defined in spell_set.cpp, so they have to be real (externally visible) functions
	INT32 GetLevel(void);
	INT32 GetRuneSlot(void);

	inline INT32 GetRefCount(void);

	inline INT32 GetEquipSlot(void);
	inline BOOL IsEnabled(void);
	inline BOOL NeedSave(void);
	inline void SetNeedSave(BOOL bNeedSave);

	inline void SetPts(INT32 nValue);
	INT32 GetPts(void);

	CSpell* GetSpell(void);
	inline INT32 GetNextSpell(void);

	void AddPts(INT32 nValue);
	void LevelUp(void);

	void RecordNextSpell(CCharacter* poOwner, INT32 nNextSpellID, INT32 nResetFrm);
	void ClearNextSpell(void);
	inline UINT32 GetResetFrm(void);

	BOOL RecordEvt(INT32 eOccasionID, UINT64 qwEventID);
	UINT64 GetEvtID(INT32 eOccasionID);
	void RemoveEvt(INT32 eOccasionID);

	BOOL AddItemSpellLevelNode(UINT64 qwItemGuid, INT32 nLevel);
	BOOL AddItemSpellRuneNode(UINT64 qwItemGuid, INT32 nItemRuneID);

	BOOL RemoveItemSpellLevelNode(UINT64 qwItemGuid);
	BOOL RemoveItemSpellRuneNode(UINT64 qwItemGuid);

private:
	BOOL m_bEnabled;
	BOOL m_bNeedSave;
	INT32 m_nSpellID;
	INT32 m_nLevel;
	INT32 m_nRuneSlot;
	INT32 m_nEquipSlot;
	INT32 m_nCurrentPts;
	INT32 m_nRefCount;

	UINT32 m_dwNextTargetID;
	NextSpell m_NextSpell;

	typedef std::map<INT32, UINT64> TEvtMap;
	TEvtMap m_EvtMap;

	CBaseList m_ItemLevelList;
	CBaseList m_ItemRuneList;

};

inline INT32 CSpellSet::GetID(void)
{
	return m_nSpellID;
}

inline INT32 CSpellSet::GetActualLevel(void)
{
	return m_nLevel;
}

inline INT32 CSpellSet::GetActualRuneSlot(void)
{
	return m_nRuneSlot;
}

inline void CSpellSet::SetLevel(INT32 nLevel)
{
	m_nLevel = nLevel;
}

inline void CSpellSet::SetRuneSlot(INT32 nRuneSlot)
{
	m_nRuneSlot = nRuneSlot;
}

inline void CSpellSet::Enable(BOOL bVal)
{
	m_bEnabled = bVal;
}

inline BOOL CSpellSet::IsEnabled(void)
{
	return m_bEnabled;
}

inline BOOL CSpellSet::NeedSave(void)
{
	return m_bNeedSave;
}

inline void CSpellSet::SetNeedSave(BOOL bNeedSave)
{
	m_bNeedSave = bNeedSave;
}

inline BOOL CSpellSet::SetEquipSlot(INT32 nSlot)
{
	LOG_PROCESS_ERROR(nSlot >= qssSlotInvalid && nSlot < qssSlotCount);
	m_nEquipSlot = nSlot;

	return TRUE;
Exit0:
	return FALSE;
}

inline INT32 CSpellSet::GetEquipSlot(void)
{
	return m_nEquipSlot;
}

inline void CSpellSet::SetPts(INT32 nValue)
{
	m_nCurrentPts = nValue;
}

inline INT32 CSpellSet::GetNextSpell(void)
{
	return m_NextSpell.nSpellID;
}

inline UINT32 CSpellSet::GetResetFrm(void)
{
	return m_NextSpell.dwNextResetFrm;
}

inline INT32 CSpellSet::GetRefCount(void)
{
	return m_nRefCount;
}

#endif	// _SPELL_SET_H_
