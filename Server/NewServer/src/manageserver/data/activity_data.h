#ifndef _H_ACTIVITY_DATA_H_
#define _H_ACTIVITY_DATA_H_


#include "string_def.h"
#include "data_manager.h"

struct ACTIVITY_DATA 
{
	UINT32      dwActivityID;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ACTIVITY_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif