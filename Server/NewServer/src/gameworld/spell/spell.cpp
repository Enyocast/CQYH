#include "stdafx.h"
#include "spell.h"
#include "spell_data.h"
#include "game_world.h"
#include "spell_config.h"

CSpell::CSpell(void)
{
	m_Data.m_nID = 0;
	m_Data.m_nLevel = 0;
	memset(&m_Data, 0, sizeof(m_Data));
	memset(&m_Param, 0, sizeof(m_Param));
}

CSpell::~CSpell(void)
{

}

void CSpell::SetAttr(INT32 eAttrType, INT32 nVal)
{
	LOG_PROCESS_ERROR(eAttrType > satInvalid && eAttrType < satTotal);

	m_Data.m_nAttrTable[eAttrType] = nVal;
Exit0:
	return;
}

INT32 CSpell::GetConsumeAttr(INT32 eAttrType)
{
	LOG_PROCESS_ERROR(eAttrType > satInvalid && eAttrType < satTotal);

	if(CGameWorld::GetInstance().CheckConsume())
		return m_Data.m_nAttrTable[eAttrType];

Exit0:
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CSpellTemplate::CSpellTemplate(void)
{
	m_bInited = FALSE;
}

void CSpellTemplate::SetAttr(INT32 eAttrType, INT32 nVal)
{

}

void CSpellTemplate::InitWithData(const SPELL_ENTRY* pData)
{
	memcpy(&m_Data, pData, sizeof(m_Data));
	m_bInited = TRUE;
}


CSpell* CSpellTemplate::MakeCopy(void)
{
	CSpellCopy* cp = CGameWorld::GetInstance().NewSpellCopy();
	LOG_PROCESS_ERROR(cp);

	CopyTo(cp);
	return cp;
Exit0:
	return NULL;
}




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CSpellCopy::CSpellCopy(void)
{
}

CSpell* CSpellCopy::MakeCopy(void)
{
	return this;
}
