#include "stdafx.h"
#include "spell_book_npc.h"
#include "spell_config.h"
#include "spell.h"

CNpcSpellBook::CNpcSpellBook(void)
{
	m_nHighestSpellLevel = 0;
}

CNpcSpellBook::~CNpcSpellBook(void)
{

}

void CNpcSpellBook::UnInit(void)
{

}

CSpell* CNpcSpellBook::GetMainSpell(INT32 nSpellID)
{
	return CSpellConfig::GetInstance().FindSpellTemplate(nSpellID, m_nHighestSpellLevel, 0);
}

BOOL CNpcSpellBook::AddSpellSet(CSpellSet* poSet)
{
	return FALSE;
}

CSpellSet* CNpcSpellBook::GetSpellSet(INT32 nSpellID)
{
	return NULL;
}

void CNpcSpellBook::RemoveSpell(INT32 nSpellID)
{

}

void CNpcSpellBook::BeginSpellSet(void)
{

}

CSpellSet* CNpcSpellBook::NextSpellSet(void)
{
	return NULL;
}

BOOL CNpcSpellBook::AddNewAura(CAura* aura)
{
	return FALSE;
}

CAura* CNpcSpellBook::GetAura(INT32 nAuraID)
{
	return NULL;
}

CAura* CNpcSpellBook::ToModifyAura(INT32 nAuraID)
{
	return NULL;
}

void CNpcSpellBook::RemoveAura(INT32 nAuraID)
{

}

void CNpcSpellBook::BeginAura(void)
{

}

CAura* CNpcSpellBook::NextAura(void)
{
	return NULL;
}
