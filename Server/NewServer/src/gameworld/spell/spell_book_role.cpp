#include "stdafx.h"
#include "spell_book_role.h"
#include "data_manager.h"
#include "spell_data.h"
#include "spell.h"
#include "aura.h"
#include "spell_config.h"
#include "role.h"
#include "game_world.h"
#include "message_handler.h"


CRoleSpellBook::CRoleSpellBook()
{
	m_poRole = NULL;
}

CRoleSpellBook::~CRoleSpellBook()
{

}

void CRoleSpellBook::UnInit(void)
{
	for(TSpellSetMap::iterator itr = m_SpellSetMap.begin(); itr != m_SpellSetMap.end(); ++itr)
	{
		CSpellSet* pSet = itr->second;
		pSet->Release();
	}

	for(TAuraMap::iterator itr = m_AuraMap.begin(); itr != m_AuraMap.end(); ++itr)
	{
		CAura* aura = itr->second;
		aura->UnInit();
	}

	m_SpellSetMap.clear();
	m_AuraMap.clear();
	m_poRole = NULL;
}

CSpell* CRoleSpellBook::GetMainSpell(INT32 nSpellID)
{
	CSpellSet* poSet = GetSpellSet(nSpellID);
	PROCESS_ERROR(poSet);

	return poSet->GetSpell();
Exit0:
	return NULL;
}

BOOL CRoleSpellBook::AddSpellSet(CSpellSet* poSet)
{
	INT32 nRetCode = 0;
	INT32 nResult = errUnknownError;

	CSpellSet* poOldSet = GetSpellSet(poSet->GetID());
	PROCESS_ERROR(poOldSet == NULL);

	m_SpellSetMap[poSet->GetID()] = poSet;

	return TRUE;
Exit0:
	return FALSE;
}

//CSpell* CSpellBook::ToModifySpell(INT32 nSpellID)
//{
//	CSpell* e = NULL;
//	CSpell* cp = NULL;
//	BOOL bRet = FALSE;
//
//	e = GetSpell(nSpellID);
//	LOG_PROCESS_ERROR(e);
//
//	cp = e->MakeCopy();
//	LOG_PROCESS_ERROR(cp);
//
//	RemoveSpell(nSpellID);
//
//	bRet = _AddNewSpell(cp);
//	LOG_PROCESS_ERROR(bRet);
//
//	return cp;
//Exit0:
//	return NULL;
//
//}

void CRoleSpellBook::BeginSpellSet(void)
{
	m_SpellSetItr = m_SpellSetMap.begin();
}

CSpellSet* CRoleSpellBook::NextSpellSet(void)
{
	if(m_SpellSetItr == m_SpellSetMap.end())
		return NULL;

	CSpellSet* e = m_SpellSetItr->second;
	++m_SpellSetItr;

	return e;
}

void CRoleSpellBook::RemoveSpell(INT32 nSpellID)
{
	CSpellSet* poSet = GetSpellSet(nSpellID);
	LOG_PROCESS_ERROR(poSet);

	poSet->Release();
	m_SpellSetMap.erase(nSpellID);

Exit0:
	return;
}

BOOL CRoleSpellBook::AddNewAura(CAura* aura)
{
	CAura* target = GetAura(aura->GetID());
	LOG_PROCESS_ERROR(target == NULL);

	return m_AuraMap.insert(std::make_pair(aura->GetID(), aura)).second;
Exit0:
	return FALSE;
}

CAura* CRoleSpellBook::GetAura(INT32 nAuraID)
{
	TAuraMap::iterator itr = m_AuraMap.find(nAuraID);
	PROCESS_ERROR(itr != m_AuraMap.end());

	return itr->second;
Exit0:
	return FALSE;
}

CAura* CRoleSpellBook::ToModifyAura(INT32 nAuraID)
{
	CAura* e = NULL;
	CAura* cp = NULL;
	BOOL bRet = FALSE;

	e = GetAura(nAuraID);
	LOG_PROCESS_ERROR(e);

	cp = e->MakeCopy();
	LOG_PROCESS_ERROR(cp);

	RemoveAura(nAuraID);

	bRet = AddNewAura(cp);
	LOG_PROCESS_ERROR(bRet);

	return cp;
Exit0:
	return NULL;
}

void CRoleSpellBook::RemoveAura(INT32 nAuraID)
{
	m_AuraMap.erase(nAuraID);
}

void CRoleSpellBook::BeginAura(void)
{
	m_AuraIter = m_AuraMap.begin();
}

CAura* CRoleSpellBook::NextAura(void)
{
	if(m_AuraIter == m_AuraMap.end())
		return NULL;

	CAura* e = m_AuraIter->second;
	++m_AuraIter;

	return e;
}

CSpellSet* CRoleSpellBook::GetSpellSet(INT32 nSpellID)
{
	TSpellSetMap::iterator itr = m_SpellSetMap.find(nSpellID);
	PROCESS_ERROR(itr != m_SpellSetMap.end());

	return itr->second;
Exit0:
	return NULL;
}

INT32 CRoleSpellBook::GetPow(void)
{
	INT32 nPow = 0;

	BeginSpellSet();

	CSpellSet* poSet = NULL;

	while((poSet = NextSpellSet()) != NULL)
	{
		const SPELL_PROGRESS_DATA* pData = CDataManager<SPELL_PROGRESS_DATA>::GetInstance().GetData(MakeSpellProgressKey(poSet->GetID(), poSet->GetLevel()));
		if(pData == NULL)
			continue;

		nPow += pData->m_nPow;
	}

	return nPow;
}
