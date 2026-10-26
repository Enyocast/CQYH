#ifndef _AURA_INSTANCE_H_
#define _AURA_INSTANCE_H_

#include "aura.h"
#include "simple_timer.h"
#include "aura_def.h"
#include "spell_def.h"
#include "base_list.h"

#define MAX_AURA_EXTRA_DATA 2

class CCharacter;

class CAuraInstance : public CAura
{
public:
	CAuraInstance(void);
	virtual ~CAuraInstance(void);
	virtual void UnInit(void);

	inline UINT32 GetInstanceID(void);
	inline void AddEventID(UINT64 qwEventID);

	inline void SetStackCount(INT32 nCount);
	inline INT32 GetStackCount(void);

	inline void ResetSync(void);
	inline BOOL NeedSync(void);

	inline void SetRemoveFlag(BOOL bRemove);
	inline BOOL NeedRemove(void);

	inline UINT32 GetCasterID(void);
	inline UINT32 GetFromObjID(void);

	inline void SetStrengthLevel(INT32 nValue);
	inline INT32 GetStrengthLevel(void);

	inline void SetTotalEffectValue(INT32 nValue);
	inline INT32 GetTotalEffectValue(void);

	inline void SetEffectPct(INT32 nValue);
	inline INT32 GetEffectPct(void);

	inline void SetEffectValue(INT32 nValue);
	inline INT32 GetEffectValue(void);

	inline void SetSpellID(INT32 nID);
	inline INT32 GetSpellID(void);

	inline void SetSpellLevel(INT32 nLevel);
	inline INT32 GetSpellLevel(void);

	inline BASE_LIST_NODE& GetListNode(void);
	inline SimpleListNode& GetStackNode(void);

	inline BOOL SetExtraData(INT32 idx, INT32 nValue);
	inline void ResetExtraData(INT32 idx);
	inline BOOL GetExtraData(INT32 idx, INT32& nValue);

	inline void SetCharLevel(INT32 nLevel);
	inline INT32 GetCharLevel(void);

	inline void SetAtk(INT32 nAtk);

	BOOL Init(CAura* pInfo, ExtraParam* pExParam, CCharacter* poCaster, UINT32 dwFromObjID, UINT32 dwUniqueID, INT32 nNewStackCount);

	void ResetFrm(INT32 nDurationFrm, INT32 nIntervalFrm, BOOL bNeedSync);
	void ResetIntervalFrm(INT32 nInterval, BOOL bNeedSync);

	UINT32 GetRemainFrm(void);

	BOOL OnAppend(CCharacter* poCaster, CCharacter* pChar);
	BOOL AfterStack(CCharacter* pChar);
	BOOL OnUnStack(CCharacter* pChar);
	BOOL OnTimeup(CCharacter* pChar);
	BOOL OnRemove(CCharacter* pChar, BOOL bTrigOnRemove);
	BOOL OnDispel(CCharacter* pChar);

	BOOL Update(CCharacter* pChar, INT32 nFrm, BOOL& bTimeOut);

	typedef std::list<UINT64> TEventIdList;
	inline TEventIdList& GetEventIdList(void);

	void DoTimeupEffect(CCharacter* poTarget, BOOL bRunFormular);

	inline ExtraParam* GetExtraParam(void); 

protected:
	typedef void (CAuraInstance::*OnTimeupEffectFunc)(CCharacter* poTarget);

	void _DotEffect(CCharacter* poTarget);
	void _HotEffect(CCharacter* poTarget);

private:

	CSimpleTimer m_IntervalTimer;
	INT32 m_nDestroyFrm;
	ExtraParam m_ExtraParam;

	BASE_LIST_NODE m_ListNode;
	BASE_LIST_NODE m_DisplayListNode;
	SimpleListNode m_StackNode;

	BOOL m_bNeedSync;
	BOOL m_bNeedRemove;

	UINT32 m_dwCasterID;
	UINT32 m_dwFromObjID;
	UINT32 m_dwInstanceID;
	INT32 m_nStackCount;
	INT32 m_nStrengthLevel;
	INT32 m_nCharLevel;

	INT64 m_llAtk;

	INT32 m_nSpellID;
	INT32 m_nSpellLevel;

	INT32 m_nTotalEffectValue;

	INT32 m_nEffectPct;
	INT32 m_nEffectValue;

	struct AuraExtraData
	{
		BOOL m_bSet;
		INT32 m_nValue;
	};

	AuraExtraData m_ExtraData[MAX_AURA_EXTRA_DATA];

	TEventIdList m_EventIdList;

	INT32 m_nExEvtFrm[MAX_AURA_EX_EVT];

	static OnTimeupEffectFunc m_TimeupFunc[acTotal];
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class CAuraList
{
public:
	CAuraList(void);
	virtual ~CAuraList(void);

	void Init(void);
	void UnInit(void);

	CAuraInstance* BeginAura(INT32 nEffectType);
	CAuraInstance* NextAura(INT32 nEffectType, CAuraInstance* poPrevAura);

	BOOL AddNewAura(CAuraInstance* poAura);
	void RemoveAura(CAuraInstance* poAura);
	void Update(CCharacter* poOwner);

	inline INT32 GetTopDisplayAuraID(INT32 nGroup);
	inline UINT32 GetTopDisplayAuraInstanceID(INT32 nGroup);

private:
	CBaseList m_AuraList[auetTotal];

	struct AuraDisplay
	{
		INT32 nAuraID;
		UINT32 nInstanceID;
		INT32 nAuraDisplayValue;
	};

	AuraDisplay m_TopAuraDisplay[adgTotal];
};


#include "aura_instance_inl.h"

#endif // _aura_instance_h__

