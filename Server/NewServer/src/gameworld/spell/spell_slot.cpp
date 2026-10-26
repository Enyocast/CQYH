#include "stdafx.h"
#include "spell_slot.h"
#include "game_world.h"
#include "spell.h"
#include "character.h"

CSpellSlot::CSpellSlot(void)
{
	m_dwNextTargetID = 0;
	m_bLocked = TRUE;
	m_nMainSpellID = 0;
}

CSpellSlot::~CSpellSlot(void)
{

}

void CSpellSlot::Clear(void)
{
	m_nMainSpellID = 0;

}

BOOL CSpellSlot::Equip(CCharacter* poOwner, INT32 nSpellID)
{
	Clear();

	PROCESS_ERROR(nSpellID != 0);

	m_nMainSpellID = nSpellID;

	return TRUE;
Exit0:
	return FALSE;
}

INT32 CSpellSlot::GetMainSpellID(void)
{
	return m_nMainSpellID;
}

