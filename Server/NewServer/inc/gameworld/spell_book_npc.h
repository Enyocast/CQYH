#ifndef _SPELL_BOOK_NPC_H_
#define _SPELL_BOOK_NPC_H_


#include "spell_book.h"

class CNpcSpellBook : public ISpellBook
{
public:
	CNpcSpellBook(void);
	virtual ~CNpcSpellBook(void);

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

	inline void SetHighestSpellLevel(INT32 nLevel);

private:
	INT32 m_nHighestSpellLevel;
};

inline void CNpcSpellBook::SetHighestSpellLevel(INT32 nLevel)
{
	m_nHighestSpellLevel = nLevel;
}

#endif // _spell_book_npc_h__
