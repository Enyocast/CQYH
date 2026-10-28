#ifndef _ROLE_RELATION_H_
#define _ROLE_RELATION_H_

#include "data_manager.h"
#include "role_def.h"
struct ROLE_RELATION_DATA
{
    INT32 nFactionID;
    INT32 nRelation[MAX_ROLE_FRACTION_ID];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ROLE_RELATION_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif  // _ROLE_RELATION_H_