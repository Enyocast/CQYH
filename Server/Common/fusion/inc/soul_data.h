#ifndef _SOUL_DATA_H_
#define _SOUL_DATA_H_

#include "data_manager.h"

struct ATTRIBUTE_DATA;
struct SOUL_DATA
{
    INT32 m_nTemplateID;
    INT32 m_nAttrID;
    INT32 m_nMatchSocket;
    INT32 m_nSoulLevel;
    INT32 m_nPriceValue;
    INT32 m_nUpgradeSoulID;
    INT32 m_nRemovePrice;
    const ATTRIBUTE_DATA* m_pAttrData;

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, SOUL_DATA* pData, CTabFile* pTabConfig, INT32 nRow);
};

#endif // _SOUL_DATA_H_
