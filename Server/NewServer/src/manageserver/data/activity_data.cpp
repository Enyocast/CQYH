#include "stdafx.h"
#include "activity_data.h"

BOOL ACTIVITY_DATA::ReadLine(INT32& rnID, const char*& rpcszName, ACTIVITY_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("activityID", dwActivityID);

	READ_END(dwActivityID);
}
