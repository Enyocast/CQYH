#ifndef _SPELL_BOOK_HERO_H_
#define _SPELL_BOOK_HERO_H_


#include "spell_book.h"

class CHeroSpellBook : public ISpellBook
{
public:
	CHeroSpellBook(void);
	virtual ~CHeroSpellBook(void);

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

//	virtual BOOL AddNewRune(CRune* rune);
//
//	virtual CRune* GetRune(INT32 nSpellID, INT32 nRuneSlot);
//
//	virtual BOOL DelRune(CRune* rune);
//
//	virtual void BeginRune(void);
//
//	virtual CRune* NextRune(void);
};

#endif // _spell_book_hero_h__
