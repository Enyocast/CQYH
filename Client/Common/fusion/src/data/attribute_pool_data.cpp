#include "stdafx.h"
#include "attribute_pool_data.h"
#include "attribute_data.h"

CAttributePoolDataManager CAttributePoolDataManager::ms_Instance;

BOOL CAttributePoolDataManager::Init(const char* pcszConfigName, const char* pcszPath)
{
    BOOL bRet = FALSE;
    char szFileName[MAX_PATH];
    CTabFile oTabFile;
    INT32 nRowIndex = 0;
    INT32 nCounter = 0;
    UINT64 qwStartTick = GetTickCountEx();

    INT32 nID = 0;
    ATTRIBUTE_POOL_DATA pool_data;
    ATTRIBUTE_POOL* pool = NULL;

    LOG_PROCESS_ERROR(pcszConfigName);

    snprintf(szFileName, MAX_PATH, "%s/%s.txt", pcszPath, pcszConfigName);
    bRet = oTabFile.Init(szFileName, 1);
    LOG_PROCESS_ERROR(bRet);

    for (nRowIndex = 0; nRowIndex < oTabFile.GetRowCount(); nRowIndex++)
    {
        bRet = ReadPoolData(nID, pool_data, oTabFile, nRowIndex);
        if (!bRet)
        {
            WRN("Failed to read data at row %d in %s data file", nRowIndex, pcszConfigName);
            continue;
        }
        if (nID == 0)
        {
            nCounter++;
            continue;
        }

        pool = &m_datamap[nID];
        if (pool->m_nAttributePoolID == 0)
        {
            pool->m_nAttributePoolID = nID;
        }

        LOG_PROCESS_ERROR(pool->m_nDataCount < MAX_ATTRIBUTE_POOL_DATA_COUNT);

        pool->m_PoolData[pool->m_nDataCount] = pool_data;
        pool->m_nDataCount++;
        pool->m_nTotalWeight += pool_data.m_nWeight;

        nCounter++;
    }

    INF("read %d / %d data in %s successfully (cost %d ms %.2f MB)", nCounter, oTabFile.GetRowCount(), pcszConfigName,
        (INT32)(GetTickCountEx() - qwStartTick), sizeof(ATTRIBUTE_POOL_DATA) * nCounter / (1024.0f * 1024.0f));

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CAttributePoolDataManager::UnInit(void)
{
    m_datamap.clear();
    return TRUE;
}

const ATTRIBUTE_POOL* CAttributePoolDataManager::GetPool(INT32 nPoolID)
{
    ATTRIBUTE_POOL_MAP::const_iterator it = m_datamap.find(nPoolID);
    if (it == m_datamap.end())
        return NULL;
    else
        return &it->second;
}

BOOL CAttributePoolDataManager::ReadPoolData(INT32& rnID, ATTRIBUTE_POOL_DATA& rData, CTabFile& rTabConfig, INT32 nRow)
{
    INT32 nRetCode = 0;
    INT32 nValue = 0;

    memset(&rData, 0, sizeof(ATTRIBUTE_POOL_DATA));

    nRetCode = rTabConfig.ReadData("AttributePoolID", nRow, rnID);
    LOG_PROCESS_ERROR(nRetCode);
    if (rnID == 0)
        return TRUE;

    nRetCode = rTabConfig.ReadData("AttributeIDMin", nRow, rData.m_nAttributeIDMin);
    LOG_PROCESS_ERROR(nRetCode);
    LOG_PROCESS_ERROR(rData.m_nAttributeIDMin > 0);

    nRetCode = rTabConfig.ReadData("AttributeIDMax", nRow, rData.m_nAttributeIDMax);
    LOG_PROCESS_ERROR(nRetCode);
    LOG_PROCESS_ERROR(rData.m_nAttributeIDMax >= rData.m_nAttributeIDMin);

    for (INT32 i = rData.m_nAttributeIDMin; i <= rData.m_nAttributeIDMax; i++)
    {
        LOG_PROCESS_ERROR(CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(i));
    }

    nRetCode = rTabConfig.ReadData("Weight", nRow, rData.m_nWeight);
    LOG_PROCESS_ERROR(nRetCode);
    LOG_PROCESS_ERROR(rData.m_nWeight > 0);

    return TRUE;

Exit0:
    return FALSE;
}