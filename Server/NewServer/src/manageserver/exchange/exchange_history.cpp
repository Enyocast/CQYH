#include "stdafx.h"
#include "exchange_history.h"
#include "manageserver.h"
#include "db/ms_sql_stmt_list.h"
#include "server_config.h"

CExchangeHistory CExchangeHistory::ms_Instance;

void Bar::AddPrice(INT32 price, INT32 count)
{
    LOG_PROCESS_ERROR(price > 0);
    LOG_PROCESS_ERROR(count > 0);

    if (m_nOpen == 0)
        m_nOpen = price;

    m_nClose = price;

    if (m_nHigh < price)
        m_nHigh = price;

    if (m_nLow == 0 || m_nLow > price)
        m_nLow = price;

    m_nVolume += count;
    m_llTotalPrice += price * count;

Exit0:
    return;
}

BOOL CExchangeHistory::Init(void)
{
    BOOL bRet = FALSE;
    UINT64 qwStartTick = GetTickCountEx();
    m_nLoadedCount = 0;

    INF("Loading Exchange History Data...");

    bRet = CManageServer::GetInstance().GetSqlMgr().SyncExecSqlStmt(msqlSelectExchangeHistory, _Load, NULL, "");
    LOG_PROCESS_ERROR(bRet);

    INF("Loaded %d Exchange History Data in (%d ms)", m_nLoadedCount, (INT32)(GetTickCountEx() - qwStartTick));

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CExchangeHistory::UnInit(void)
{
    return TRUE;
}

BOOL CExchangeHistory::AddPrice(UINT8 groupid, INT32 price, INT32 count, UINT32 curtime)
{
    BOOL is_new_bar = FALSE;
    BOOL bRet = FALSE;
    
    LOG_PROCESS_ERROR(IsValidGroup(groupid));
    LOG_PROCESS_ERROR(price > 0);
    LOG_PROCESS_ERROR(count > 0);

    curtime = curtime / 3600 * 3600;

    is_new_bar = charts[groupid].find(curtime) == charts[groupid].end();

    {
        Bar& bar = charts[groupid][curtime];
        bar.AddPrice(price, count);

        if (is_new_bar)
        {
            bRet = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlInsertExchangeHistory, NULL, NULL, "ucuddddddl",
                groupid, curtime, bar.m_nOpen, bar.m_nClose, bar.m_nHigh, bar.m_nLow, bar.m_nVolume, bar.m_llTotalPrice);
            LOG_CHECK_ERROR(bRet);
        }
        else
        {
            bRet = CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlUpdateExchangeHistory, NULL, NULL, "dddddlucud",
                bar.m_nOpen, bar.m_nClose, bar.m_nHigh, bar.m_nLow, bar.m_nVolume, bar.m_llTotalPrice, groupid, curtime);
            LOG_CHECK_ERROR(bRet);
        }
    }

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CExchangeHistory::_Load(std::list<void*>& rResult, void* pUserData)
{
    BOOL bRet = FALSE;

#pragma pack(push, 1)
    struct LOAD_RESULT
    {
        UINT8 byGroupID;
        UINT32 dwHistoryTime;
        INT32 nOpen;
        INT32 nClose;
        INT32 nHight;
        INT32 nLow;
        INT32 nVolume;
        INT64 llTotalPrice;
    };
#pragma pack(pop)

    for (std::list<void*>::iterator it = rResult.begin();
        it != rResult.end(); ++it)
    {
        LOAD_RESULT* pLoadResult = (LOAD_RESULT*)*it;

        LOG_PROCESS_ERROR(IsValidGroup(pLoadResult->byGroupID));

        bRet = CExchangeHistory::GetInstance()._LoadHistory(
            pLoadResult->byGroupID,
            pLoadResult->dwHistoryTime,
            pLoadResult->nOpen,
            pLoadResult->nClose,
            pLoadResult->nHight,
            pLoadResult->nLow,
            pLoadResult->nVolume,
            pLoadResult->llTotalPrice);
        LOG_PROCESS_ERROR(bRet);
    }

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CExchangeHistory::_LoadHistory(UINT8 byGroupID, UINT32 dwHistoryTime, INT32 nOpen, INT32 nClose, INT32 nHigh, INT32 nLow, INT32 nVolume, INT64 llTotalPrice)
{
    Bar bar;

    LOG_PROCESS_ERROR(byGroupID < MAX_SERVER_GROUP_COUNT);
    LOG_PROCESS_ERROR(dwHistoryTime % 3600 == 0);
    LOG_PROCESS_ERROR(nOpen >= 0);
    LOG_PROCESS_ERROR(nClose >= 0);
    LOG_PROCESS_ERROR(nHigh >= 0);
    LOG_PROCESS_ERROR(nLow >= 0);
    LOG_PROCESS_ERROR(nVolume >= 0);
    LOG_PROCESS_ERROR(llTotalPrice >= 0);

    bar.m_nOpen = nOpen;
    bar.m_nClose = nClose;
    bar.m_nHigh = nHigh;
    bar.m_nLow = nLow;
    bar.m_nVolume = nVolume;
    bar.m_llTotalPrice = llTotalPrice;

    charts[byGroupID][dwHistoryTime] = bar;

    m_nLoadedCount++;

    return TRUE;

Exit0:
    return FALSE;
}
