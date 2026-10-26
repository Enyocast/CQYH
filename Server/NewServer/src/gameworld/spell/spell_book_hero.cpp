#include "stdafx.h"
#include "spell_book_hero.h"
#include "spell_config.h"
#include "spell.h"

CHeroSpellBook::CHeroSpellBook(void)
{

}

CHeroSpellBook::~CHeroSpellBook(void)
{

}

void CHeroSpellBook::UnInit(void)
{

}

CSpell* CHeroSpellBook::GetMainSpell(INT32 nSpellID)
{
	INT32 nLevel = CSpellConfig::GetInstance().GetHighestLevel(nSpellID);

	return CSpellConfig::GetInstance().FindSpellTemplate(nSpellID, nLevel, 0);
}

BOOL CHeroSpellBook::AddSpellSet(CSpellSet* poSet)
{
	return FALSE;
}

CSpellSet* CHeroSpellBook::GetSpellSet(INT32 nSpellID)
{
	return NULL;
}

void CHeroSpellBook::RemoveSpell(INT32 nSpellID)
{

}

void CHeroSpellBook::BeginSpellSet(void)
{

}

CSpellSet* CHeroSpellBook::NextSpellSet(void)
{
	return NULL;
}

BOOL CHeroSpellBook::AddNewAura(CAura* aura)
{
	return FALSE;
}

CAura* CHeroSpellBook::GetAura(INT32 nAuraID)
{
	return NULL;
}

CAura* CHeroSpellBook::ToModifyAura(INT32 nAuraID)
{
	return NULL;
}

void CHeroSpellBook::RemoveAura(INT32 nAuraID)
{

}

void CHeroSpellBook::BeginAura(void)
{

}

CAura* CHeroSpellBook::NextAura(void)
{
	return NULL;
}

//BOOL CHeroSpellBook::EquipRune(INT32 nSpellID, INT32 nRuneSlot, INT32 nRuneLevel)
//{
//	return FALSE;
//}

//BOOL CHeroSpellBook::AddNewRune(CRune* rune)
//{
//	return FALSE;
//}
//
//CRune* CHeroSpellBook::GetRune(INT32 nSpellID, INT32 nRuneSlot)
//{
//	return NULL;
//}
//
//BOOL CHeroSpellBook::DelRune(CRune* rune)
//{
//	return FALSE;
//}
//
//void CHeroSpellBook::BeginRune(void)
//{
//
//}
//
//CRune* CHeroSpellBook::NextRune(void)
//{
//	return NULL;
//}
//