#ifndef _REFINE_DATA_H_
#define _REFINE_DATA_H_

#include "data_manager.h"
#include "item_def.h"

struct REFINE_DATA
{
    INT32 m_nRefineLevel;
    INT32 m_nRequireLevel;
    UINT32 m_dwSuccessRate;
    INT32 m_nBasePow;
    INT32 m_nCost;
    BOOL m_nBroadCast;
 
    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, REFINE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

struct ATTRIBUTE_DATA;
struct REFINE_ATTR_DATA
{
    UINT16 m_wRefineLevel;
    UINT8 m_byClass;
    UINT8 m_byEquipSlot;
    INT32 m_nRefineKey;
    INT32 m_nAttrID[MAX_REFINE_ATTR_COUNT];
    INT32 m_nNodeCount;
    const ATTRIBUTE_DATA* m_pAttrData[MAX_REFINE_ATTR_COUNT];

    static UINT32 MakeKey(UINT32 refinelevel, UINT32 cls, UINT32 equipslot) { return refinelevel << 16 | cls << 8 | equipslot; }
    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, REFINE_ATTR_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _REFINE_DATA_H_
