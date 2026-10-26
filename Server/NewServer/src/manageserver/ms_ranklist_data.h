#ifndef _RANKLIST_DATA_H_
#define _RANKLIST_DATA_H_

#include "ranklist/ranklist.h"
#include "ranklist_def.h"

// db data

struct RANKLIST_RIGHT_DATA_DB
{
	INT64 llKey[NUM_PER_RANKING];
	INT64 llValue[NUM_PER_RANKING];
};

struct RANKLIST_DATA_DB
{
	INT32 nServerGroupID;
	INT32 nRankListID;

	RANKLIST_RIGHT_DATA_DB stRightData;
};

struct RANKLIST_DATA_CLIENT
{
	INT32 nServerGroupID;
	INT32 nRankListID;

	INT32	nSelfRank;
	INT32	nTotalPage;

	INT64	llKey[MAX_NUM_PER_PAGE];
	INT64	llValue[MAX_NUM_PER_PAGE];
};

#endif //_RANKLIST_DATA_H_
