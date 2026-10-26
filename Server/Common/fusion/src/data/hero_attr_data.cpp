#include "stdafx.h"
#include "hero_attr_data.h"

BOOL HERO_ATTR_DATA::ReadLine(INT32& rnID, const char*& rpcszName, HERO_ATTR_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("Level", m_nLevel);
	READ_INT("Class", m_nClass);
//	READ_INT("catStrength", m_nMainAttr[catStrength]);
//	READ_INT("catAgility", m_nMainAttr[catAgility]);
//	READ_INT("catIntellect", m_nMainAttr[catIntellect]);
//	READ_INT("catStamina", m_nMainAttr[catStamina]);
//	READ_INT("catSpirit", m_nMainAttr[catSpirit]);
//	READ_INT("catValue", m_nMainAttr[catValue]);
//	READ_INT("catCombatParam", m_nMainAttr[catCombatParam]);

	rnID = MakeHeroAttrKey(pData->m_nLevel, pData->m_nClass);

	return TRUE;
Exit0:
	return FALSE;
}