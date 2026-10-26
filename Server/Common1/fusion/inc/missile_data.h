#ifndef _MISSILE_DATA_H_
#define _MISSILE_DATA_H_

#include "attribute_def.h"
#include "missile_def.h"
#include "data_manager.h"

//tolua_begin

struct MISSILE_DATA
{
	INT32 m_nTemplateID;
	INT32 m_nAttr[matTotal];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, MISSILE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};
//tolua_end

#endif	// _MISSILE_DATA_H_