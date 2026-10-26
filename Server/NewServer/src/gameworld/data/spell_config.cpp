#include "stdafx.h"
#include "spell_config.h"
#include "spell.h"
#include "aura.h"
#include "common.h"

CSpellConfig CSpellConfig::m_sInstance;

CSpellConfig::CSpellConfig(void)
{

}

CSpellConfig::~CSpellConfig(void)
{
    UnInit();
}

BOOL CSpellConfig::Init(void)
{
    m_SpellMap.clear();
    m_SpellLevelMap.clear();
    m_SpellProgressMap.clear();
    m_AuraMap.clear();

    return TRUE;
}

BOOL CSpellConfig::UnInit(void)
{
    for (TSpellMap::iterator it = m_SpellMap.begin();
        it != m_SpellMap.end(); ++it)
    {
        CSpellTemplate* pSpellTemplate = it->second;
        SAFE_DELETE(pSpellTemplate);
    }

    for (TAuraMap::iterator it = m_AuraMap.begin();
        it != m_AuraMap.end(); ++it)
    {
        CAuraTemplate* pAuraTemplate = it->second;
        SAFE_DELETE(pAuraTemplate);
    }

    m_SpellMap.clear();
    m_SpellLevelMap.clear();
    m_SpellProgressMap.clear();
    m_AuraMap.clear();

    return TRUE;
}

CSpellConfig& CSpellConfig::GetInstance(void)
{
	return m_sInstance;
}

CSpellTemplate* CSpellConfig::FindSpellTemplate(INT32 nSpellID, INT32 nSpellLevel, INT32 nRuneID)
{
	INT32 nKey = MakeSpellKey(nSpellID, nSpellLevel, nRuneID);

	TSpellMap::iterator itr = m_SpellMap.find(nKey);
	if(itr == m_SpellMap.end())
		return NULL;

	return itr->second;
}

CSpellTemplate* CSpellConfig::SetSpellTemplate(INT32 nSpellID, INT32 nSpellLevel, INT32 nRuneID, const SPELL_ENTRY* pData)
{
	INT32 nHighestLevel = 0;
	INT32 nRetCode = 0;

	CSpellTemplate* t = FindSpellTemplate(nSpellID, nSpellLevel, nRuneID);
	if(t == NULL)
	{
		t = new CSpellTemplate();
		LOG_PROCESS_ERROR(t);

		nRetCode = m_SpellMap.insert(std::make_pair(MakeSpellKey(nSpellID, nSpellLevel, nRuneID), t)).second;
		LOG_PROCESS_ERROR(nRetCode);
	}

	t->InitWithData(pData);

	t->SetIDLevelRune(nSpellID, nSpellLevel, nRuneID);

	nHighestLevel = GetHighestLevel(nSpellID);

	if(nHighestLevel = 0 || nHighestLevel < nSpellLevel)
		m_SpellLevelMap[nSpellID] = nSpellLevel;

	return t;
Exit0:
	return NULL;

}

CAuraTemplate* CSpellConfig::FindAuraTemplate(INT32 nAuraID)
{
	TAuraMap::iterator itr = m_AuraMap.find(nAuraID);
	if(itr == m_AuraMap.end())
		return NULL;

	return itr->second;
}

CAuraTemplate* CSpellConfig::NewAuraTemplate(INT32 nAuraID)
{
	CAuraTemplate* t = new CAuraTemplate();
	LOG_PROCESS_ERROR(t);

	t->SetID(nAuraID);

	m_AuraMap[nAuraID] = t;

	return t;
Exit0:
	return NULL;
}

INT32 CSpellConfig::GetHighestLevel(INT32 nSpellID)
{
	TSpellLevelMap::iterator itr = m_SpellLevelMap.find(nSpellID);
	PROCESS_ERROR(itr != m_SpellLevelMap.end());

	return itr->second;
Exit0:
	return 1;
}

BOOL CSpellConfig::SetSpellMaxProgress(INT32 nSpellID, INT32 nSpellLevel, INT32 nConsumtPts)
{
	INT32 nRetCode = 0;
	INT32 nOldValue = 0;

	{
		TSpellProgressMap::iterator itr = m_SpellProgressMap.find(MakeSpellProgressKey(nSpellID, nSpellLevel));
		if(itr != m_SpellProgressMap.end())
		{
			itr->second = nConsumtPts;
		}
		else
		{
			m_SpellProgressMap.insert(std::make_pair(MakeSpellProgressKey(nSpellID, nSpellLevel), nConsumtPts)).second;
		}
	}

	return TRUE;
}

BOOL CSpellConfig::GetMaxProgress(INT32 nSpellID, INT32 nSpellLevel, INT32& nConsumtPts)
{
	TSpellProgressMap::iterator itr = m_SpellProgressMap.find(MakeSpellProgressKey(nSpellID, nSpellLevel));
	LOG_PROCESS_ERROR(itr != m_SpellProgressMap.end());

	nConsumtPts = itr->second;

	return TRUE;
Exit0:
	return FALSE;
}

void CSpellConfig::ReleaseAll(void)
{
	for(TSpellMap::iterator itr = m_SpellMap.begin(); itr != m_SpellMap.end(); ++itr)
	{
		itr->second->ResetFlag();
	}

	//for(TAuraMap::iterator itr = m_AuraMap.begin(); itr != m_AuraMap.end(); ++itr)
	//{
	//	delete itr->second;
	//}

	//m_SpellMap.clear();
	//m_AuraMap.clear();

	//m_SpellLevelMap.clear();
	//m_SpellProgressMap.clear();
}

void CSpellConfig::BeginSpell(void)
{
	m_SpellItr = m_SpellMap.begin();
}

CSpellTemplate* CSpellConfig::NextSpell(void)
{
	CSpellTemplate* t = NULL;
	PROCESS_ERROR(m_SpellItr != m_SpellMap.end());

	t = m_SpellItr->second;

	m_SpellItr++;

	return t;
Exit0:
	return NULL;
}
