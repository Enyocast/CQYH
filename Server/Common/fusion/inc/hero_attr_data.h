#ifndef _HERO_ATTR_DATA_H_
#define _HERO_ATTR_DATA_H_

#include "data_manager.h"
#include "attribute_def.h"

class CTabFile;
struct HERO_ATTR_DATA
{
	INT32 m_nLevel;
	INT32 m_nClass;

	INT32 m_nMainAttr[catTotal];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, HERO_ATTR_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

inline INT32 MakeHeroAttrKey(INT32 nLevel, INT32 nClass)
{
	return (nLevel << 16) + nClass;
}

#endif // _hero_attr_data_h__
