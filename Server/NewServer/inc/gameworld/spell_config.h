#ifndef _SPELL_CONFIG_H_
#define _SPELL_CONFIG_H_

#include "base_config.h"
#include "spell.h"

class CAuraTemplate;

class CSpellConfig
{
public:
	CSpellConfig(void);
	virtual ~CSpellConfig(void);

    BOOL Init(void);
    BOOL UnInit(void);
	static CSpellConfig& GetInstance(void);

	void ReleaseAll(void);

	CAuraTemplate* FindAuraTemplate(INT32 nAuraID);

	CAuraTemplate* NewAuraTemplate(INT32 nAuraID);

	INT32 GetHighestLevel(INT32 nSpellID);

	CSpellTemplate* FindSpellTemplate(INT32 nSpellID, INT32 nSpellLevel, INT32 nRuneID);

	CSpellTemplate* SetSpellTemplate(INT32 nSpellID, INT32 nSpellLevel, INT32 nRuneID, const SPELL_ENTRY* pData);

	BOOL SetSpellMaxProgress(INT32 nSpellID, INT32 nSpellLevel, INT32 nConsumePts);

	BOOL GetMaxProgress(INT32 nSpellID, INT32 nSpellLevel, INT32& nConsumePts);

	void BeginSpell(void);

	CSpellTemplate* NextSpell(void);

protected:
	typedef std::map<INT32, CSpellTemplate*> TSpellMap;
	TSpellMap m_SpellMap;
	TSpellMap::iterator m_SpellItr;

	typedef std::map<INT32, CAuraTemplate*> TAuraMap;
	TAuraMap m_AuraMap;

	typedef std::map<INT32, INT32> TSpellLevelMap;
	TSpellLevelMap m_SpellLevelMap;

	typedef std::map<INT32, INT32> TSpellProgressMap;
	TSpellProgressMap m_SpellProgressMap;

	static CSpellConfig m_sInstance;
};

#endif // _spell_config_h__
