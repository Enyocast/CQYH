#ifndef _ATTRIBUTE_DATA_H_
#define _ATTRIBUTE_DATA_H_

#include "data_manager.h"

struct ATTRIBUTE_DATA
{
    INT32 m_nAttributeID;
    INT32 m_nKey;
    INT32 m_nParam[3];
    INT32 m_nPow;
    char m_szDesc[256];

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ATTRIBUTE_DATA* pData, CTabFile* pTabConfig, INT32 nRow);

    //attr nodes
    INT32 m_nNodeID;
};

#endif // _ATTRIBUTE_DATA_H_
