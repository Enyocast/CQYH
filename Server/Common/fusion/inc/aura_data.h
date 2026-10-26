#ifndef _AURA_DATA_H_
#define _AURA_DATA_H_

#include "string_def.h"
#include "attribute_def.h"
#include "data_manager.h"
#include "aura_def.h"

//tolua_begin
struct AURA_ENTRY
{
	INT32 m_nID;
    //char  m_szName[MAX_AURA_NAME_LEN];
	INT32 m_nAttrTable[aatTotal];

	struct EX_EVT_POINT
	{
		INT32 m_nExEvtTime;
		INT32 m_nExOnEvt;
	};
	EX_EVT_POINT m_ExEvtPoint[MAX_AURA_EX_EVT];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, AURA_ENTRY* pData, CTabFile* pTabConfig, INT32 nRow);
};
//tolua_end


#endif // _aura_data_h__
