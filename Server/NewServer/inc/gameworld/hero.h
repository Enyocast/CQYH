#ifndef _HERO_H_
#define _HERO_H_

#include "hero_def.h"
#include "character.h"
#include "spell_book_hero.h"

class CRole;
class CReputation;
struct HERO_ATTR_DATA;

class CHero : public CCharacter
{
public:
	CHero(void);
	virtual ~CHero(void);

	virtual INT32 GetObjType(void);
	virtual const TCHAR* GetName(void);
	virtual INT32 GetSpecies(void);
	virtual ISpellBook& GetSpellBook(void);
	virtual BOOL MainLoop(void);
	virtual BOOL SetLevel(INT32 nNewLevel);
	virtual BOOL DoSyncAttrChange(INT32 eAttrType);

	virtual BOOL JumpTo(INT64 llX, INT64 llY, INT64 llZ, INT32 nFaceDirection);

	virtual BOOL Die(INT32 nParam);

	virtual INT32 CastSpell(CSpell* poSpell, CCharacter* poTarget, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ);

public:
	BOOL Init(CRole* poOwner, UINT32 dwHeroID, UINT32 dwExp, INT32 nSex, const HERO_ATTR_DATA* pHeroData);
	BOOL UnInit(void);

	inline void SetSummoned(BOOL bVal);
	inline BOOL IsSummoned(void);

	inline void SetGrowth(INT32 nValue);
	inline INT32 GetGrowth(void);

	inline BOOL IsNameChanged(void);

	void AddExp(UINT32 nExp);
	void SubExp(UINT32 nExp);
    inline UINT32 GetExp(void);

	BOOL SetAiType(INT32 nAiType);
	inline INT32 GetAiType(void);

	BOOL ChangeName(TCHAR* szNewName);

	CRole* GetHostRole(void);

    BOOL ReachMaxExp();

    void SetFaction(INT32 nFaction);

protected:
	virtual BOOL _GridMove(INT64 llDestX, INT64 llDestY);

	virtual BOOL _ChangeRegion(CRegion* poDestRegion);

	virtual BOOL _ComputeAttribute(INT32 nNewLevel);

protected:
	CHeroSpellBook	m_SpellBook;

	INT32			m_nGrowth;
	INT32			m_nExp;
	INT32			m_nAiType;

	BOOL			m_bIsNameChanged;
	BOOL			m_bIsSummoned;
	TCHAR	        m_szName[ROLE_NAME_LEN];

	INT32					m_nFindState;
	INT32					m_nFindTimer;
	INT32					m_nFindTimes;
	INT32					m_nPathSide;
};

inline void CHero::SetGrowth(INT32 nValue)
{
	m_nGrowth = nValue;
}

inline INT32 CHero::GetGrowth(void)
{
	return m_nGrowth;
}

inline UINT32 CHero::GetExp(void)
{
	return m_nExp;
}

inline BOOL CHero::IsNameChanged(void)
{
	return m_bIsNameChanged;
}

inline INT32 CHero::GetAiType(void)
{
	return m_nAiType;
}

inline void CHero::SetSummoned(BOOL bVal)
{
	m_bIsSummoned = bVal;
}

inline BOOL CHero::IsSummoned(void)
{
	return m_bIsSummoned;
}


#endif // _hero_h__
