#ifndef _DECOMPOSE_DATA_H_
#define _DECOMPOSE_DATA_H_

#include "drop_group_data.h"
#include "item_def.h"

struct DECOMPOSE_DATA
{
    INT32 m_nTemplateID;
    DROP_CHANCE_DATA m_data[MAX_DECOMPOSE_ITEM_COUNT];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, DECOMPOSE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};


#endif // _DECOMPOSE_DATA_H_
