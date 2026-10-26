#ifndef _SPELL_BOOK_H_
#define _SPELL_BOOK_H_

#include "spell_def.h"

class CSpell;
class CAura;
class CCharacter;
//class CRune;
class CSpellSet;

class ISpellBook
{
public:
	ISpellBook(void);
	virtual ~ISpellBook(void);

	virtual void UnInit(void) = 0;

	virtual CSpell* GetMainSpell(INT32 nSpellID) = 0;

	virtual BOOL AddSpellSet(CSpellSet* poSet) = 0;

	virtual CSpellSet* GetSpellSet(INT32 nSpellID) = 0;

//	virtual BOOL EquipRune(INT32 nSpellID, INT32 nRuneSlot, INT32 nRuneLevel) = 0;

//	CSpell* ToModifySpell(INT32 nSpellID);

	virtual void RemoveSpell(INT32 nSpellID) = 0;

	virtual void BeginSpellSet(void) = 0;

	virtual CSpellSet* NextSpellSet(void) = 0;

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	virtual BOOL AddNewAura(CAura* aura) = 0;

	virtual CAura* GetAura(INT32 nAuraID) = 0;

	virtual CAura* ToModifyAura(INT32 nAuraID) = 0;

	virtual void RemoveAura(INT32 nAuraID) = 0;

	virtual void BeginAura(void) = 0;

	virtual CAura* NextAura(void) = 0;

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

//	virtual BOOL AddNewRune(CRune* rune) = 0;
//
//	virtual CRune* GetRune(INT32 nSpellID, INT32 nRuneSlot) = 0;
//
//	virtual BOOL DelRune(CRune* rune) = 0;
//
//	virtual void BeginRune(void) = 0;
//
//	virtual CRune* NextRune(void) = 0;
};



#endif	// _SPELL_BOOK_H_
