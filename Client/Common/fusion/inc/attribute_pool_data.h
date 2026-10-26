#ifndef _ATTRIBUTE_POOL_DATA_H_
#define _ATTRIBUTE_POOL_DATA_H_

#include "data_manager.h"

#define MAX_ATTRIBUTE_POOL_DATA_COUNT   (32)

struct ATTRIBUTE_POOL_DATA
{
    INT32 m_nAttributeIDMin;
    INT32 m_nAttributeIDMax;
    INT32 m_nWeight;
};

struct ATTRIBUTE_POOL
{
    INT32 m_nAttributePoolID;
    INT32 m_nDataCount;
    INT32 m_nTotalWeight;
    ATTRIBUTE_POOL_DATA m_PoolData[MAX_ATTRIBUTE_POOL_DATA_COUNT];

    ATTRIBUTE_POOL() { memset(this, 0, sizeof(ATTRIBUTE_POOL)); }
};

class CAttributePoolDataManager
{
public:
    static CAttributePoolDataManager& GetInstance(void) { return ms_Instance; }
    BOOL Init(const char* pcszConfigName, const char* pcszPath);
    BOOL UnInit(void);
    const ATTRIBUTE_POOL* GetPool(INT32 nPoolID);

private:
    BOOL ReadPoolData(INT32& rnID, ATTRIBUTE_POOL_DATA& rData, CTabFile& pTabConfig, INT32 nRow);

    static CAttributePoolDataManager ms_Instance;
    typedef std::map<INT32, ATTRIBUTE_POOL> ATTRIBUTE_POOL_MAP;
    ATTRIBUTE_POOL_MAP m_datamap;
};

#endif // _ATTRIBUTE_POOL_DATA_H_
