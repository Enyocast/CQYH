#ifndef checkin_data_h__
#define checkin_data_h__

#include "string_def.h"
#include "data_manager.h"

struct CHECKIN_DATA
{
	INT32 nDay;
	INT32 nLevelLimit;
	INT32 nAwardItemID;
	INT32 nAwardItemCount;
	INT32 nSupplementCost;

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, CHECKIN_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // checkin_data_h__
