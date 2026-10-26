#include "stdafx.h"
#include "ms_black_market_mgr.h"
#include "black_market_data.h"
#include "manageserver.h"
#include "error_def.h"

CMSBlackMarketMgr CMSBlackMarketMgr::ms_Instance;

CMSBlackMarketMgr& CMSBlackMarketMgr::GetInstance()
{
    return ms_Instance;
}

INT32 CMSBlackMarketMgr::CheckProduct(INT32 nProductID, INT32& nCount)
{
    std::map<INT32, BMServerLimitInfo>::iterator it;

    const BLACK_MARKET_DATA* data = CDataManager<BLACK_MARKET_DATA>::GetInstance().GetData(nProductID);
    LOG_PROCESS_ERROR(data);

    it = m_BlackMarketLimitMap.find(nProductID);
    if (it == m_BlackMarketLimitMap.end())
    {
        m_BlackMarketLimitMap[nProductID].nCount = data->nLimit;
        m_BlackMarketLimitMap[nProductID].dwNextRefreshTime = CManageServer::GetInstance().GetGameTime() + data->dwRefreshTime;
    }

    {
        BMServerLimitInfo& limitinfo = m_BlackMarketLimitMap[nProductID];
        if (limitinfo.nCount > 0)
        {
            limitinfo.nCount--;
            nCount = limitinfo.nCount;
            return errSuccess;
        }
        else
        {
            return errItemBlackMarketSold;
        }
    }

Exit0:
    return errItemBlackMarketItemNotFound;
}

BOOL CMSBlackMarketMgr::MainLoop()
{
    BOOL static init = FALSE;
    UINT32 cur_time = CManageServer::GetInstance().GetGameTime();

    if (!init)
    {
        const BLACK_MARKET_DATA* data = CDataManager<BLACK_MARKET_DATA>::GetInstance().GetFirstData();
        while (data)
        {
            if (data->nLimitType == ebmltServer)
            {
                BMServerLimitInfo& limitinfo = m_BlackMarketLimitMap[data->nBMProductID];
                limitinfo.nCount = data->nLimit;
                limitinfo.dwNextRefreshTime = cur_time + data->dwRefreshTime;
            }
            data = CDataManager<BLACK_MARKET_DATA>::GetInstance().GetNextData();
        }
        init = TRUE;
    }

    for (std::map<INT32, BMServerLimitInfo>::iterator it = m_BlackMarketLimitMap.begin(); it != m_BlackMarketLimitMap.end(); ++it)
    {
        if (it->second.dwNextRefreshTime <= cur_time)
        {
            BMServerLimitInfo& limitinfo = it->second;

            const BLACK_MARKET_DATA* data = CDataManager<BLACK_MARKET_DATA>::GetInstance().GetData(it->first);
            LOG_PROCESS_ERROR(data);

            limitinfo.nCount = data->nLimit;
            limitinfo.dwNextRefreshTime = cur_time + data->dwRefreshTime;
        }

    }

    return TRUE;

Exit0:
    return FALSE;
}
