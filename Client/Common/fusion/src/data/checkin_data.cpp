#include "stdafx.h"
#include "checkin_data.h"


BOOL CHECKIN_DATA::ReadLine(INT32& rnID, const char*& rpcszName, CHECKIN_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();
	READ_INT("Day", nDay);
	READ_INT("LevelLimit", nLevelLimit);
	READ_INT("AwardItemID", nAwardItemID);
	READ_INT("AwardItemCount", nAwardItemCount);
	READ_INT("SupplementCost", nSupplementCost);

	READ_END(nDay);
}
