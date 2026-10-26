#ifndef _SPELL_SLOT_H_
#define _SPELL_SLOT_H_

class CSpellSet;
class CCharacter;

class CSpellSlot
{
public:
	CSpellSlot(void);
	virtual ~CSpellSlot(void);

	void Clear(void);

	BOOL Equip(CCharacter* poOwner, INT32 nSpellID);

	INT32 GetMainSpellID(void);

	inline void SetNextTargetID(UINT32 dwTargetID);
	inline UINT32 GetNextTargetID(void);

	inline void Lock(BOOL bLock);
	inline BOOL IsLocked(void);

private:
	BOOL  m_bLocked;
	UINT32 m_dwNextTargetID;
	INT32 m_nMainSpellID;
};

inline void CSpellSlot::SetNextTargetID(UINT32 dwTargetID)
{
	m_dwNextTargetID = dwTargetID;
}

inline UINT32 CSpellSlot::GetNextTargetID(void)
{
	return m_dwNextTargetID;
}

inline void CSpellSlot::Lock(BOOL bLock)
{
	m_bLocked = bLock;
}

inline BOOL CSpellSlot::IsLocked(void)
{
	return m_bLocked;
}

#endif // _spell_slot_h__
