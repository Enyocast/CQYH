#ifndef _SET_DATA_H_
#define _SET_DATA_H_

#include "item_def.h"
#include "data_manager.h"

struct ATTRIBUTE_DATA;
struct SET_DATA
{
    INT32 m_nSetID;
    INT32 m_nItemID[MAX_SET_PART_COUNT];
    INT32 m_nCount[MAX_SET_ATTR_COUNT];
    INT32 m_nAttrID[MAX_SET_ATTR_COUNT];
    const ATTRIBUTE_DATA* m_pAttrData[MAX_SET_ATTR_COUNT];
	INT32 m_nHandbookType;
	INT32 m_nHankbookIndex;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SET_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _SET_DATA_H_
