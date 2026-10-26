#ifndef _SPELL_BOOK_ROLE_H_
#define _SPELL_BOOK_ROLE_H_

#include "spell_book.h"

class CRole;

class CRoleSpellBook : public ISpellBook
{
public:
	CRoleSpellBook(void);
	virtual ~CRoleSpellBook(void);

	virtual void UnInit(void);

	virtual CSpell* GetMainSpell(INT32 nSpellID);

	virtual BOOL AddSpellSet(CSpellSet* poSet);

	virtual CSpellSet* GetSpellSet(INT32 nSpellID);

//	CSpell* ToModifySpell(INT32 nSpellID);

	virtual void RemoveSpell(INT32 nSpellID);

	virtual void BeginSpellSet(void);

	virtual CSpellSet* NextSpellSet(void);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	virtual BOOL AddNewAura(CAura* aura);

	virtual CAura* GetAura(INT32 nAuraID);

	virtual CAura* ToModifyAura(INT32 nAuraID);

	virtual void RemoveAura(INT32 nAuraID);

	virtual void BeginAura(void);

	virtual CAura* NextAura(void);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	inline void SetRole(CRole* poRole);

	INT32 GetPow(void);

private:
	typedef std::map<INT32, CSpellSet*> TSpellSetMap;
	TSpellSetMap m_SpellSetMap;
	TSpellSetMap::iterator m_SpellSetItr;

	typedef std::map<INT32, CAura*> TAuraMap;
	TAuraMap m_AuraMap;
	TAuraMap::iterator m_AuraIter;

	CRole* m_poRole;
};

inline void CRoleSpellBook::SetRole(CRole* poRole)
{
	m_poRole = poRole; 
}
#endif // _spell_book_role_h__
