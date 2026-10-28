#include "stdafx.h"
#include "ms_drop_mgr.h"
#include <time.h>
#include "item_data.h"
#include "manageserver.h"

CMsDropMgr CMsDropMgr::ms_Instance;

BOOL CMsDropMgr::Init()
{
    INT32 nRetCode = 0;
    char szFileName[MAX_PATH];
    INT32 cur_time = CManageServer::GetInstance().GetGameTime();
    const ITEM_DATA* item_data = NULL;

    item_data = CDataManager<ITEM_DATA>::GetInstance().GetFirstData();
    while (item_data)
    {
        if (item_data->m_nTemplateID && item_data->m_nDropLimitDuration[0] > 0 && item_data->m_nDropLimitCount[0] > 0)
        {
            DROP_LIMIT& drop_limit = m_drop_limit_map[item_data->m_nTemplateID];
            drop_limit.dwStartTime = cur_time;
            drop_limit.nLimitDuration = item_data->m_nDropLimitDuration[0] * 3600; // hour -> second
            drop_limit.nLimitCount = item_data->m_nDropLimitCount[0];
            drop_limit.nCurCount = 0;
        }
        item_data = CDataManager<ITEM_DATA>::GetInstance().GetNextData();
    }

    item_data = CDataManager<EQUIP_DATA>::GetInstance().GetFirstData();
    while (item_data)
    {
        if (item_data->m_nTemplateID && item_data->m_nDropLimitDuration[0] > 0 && item_data->m_nDropLimitCount[0] > 0)
        {
            DROP_LIMIT& drop_limit = m_drop_limit_map[item_data->m_nTemplateID];
            drop_limit.dwStartTime = cur_time;
            drop_limit.nLimitDuration = item_data->m_nDropLimitDuration[0] * 3600; // hour -> second
            drop_limit.nLimitCount = item_data->m_nDropLimitCount[0];
            drop_limit.nCurCount = 0;
        }
        item_data = CDataManager<EQUIP_DATA>::GetInstance().GetNextData();
    }

    return TRUE;
}

BOOL CMsDropMgr::UnInit()
{
    m_drop_limit_map.clear();
    return TRUE;
}

BOOL CMsDropMgr::MainLoop(void)
{
    //每分钟检查一次就够了
    UINT32 dwCurrentTime = CManageServer::GetInstance().GetGameTime();

    if (dwCurrentTime - m_last_check_time < 60)
        return TRUE;

    m_last_check_time = dwCurrentTime;

    for (DROP_LIMIT_MAP::iterator it=m_drop_limit_map.begin(); it!=m_drop_limit_map.end(); it++)
    {
        DROP_LIMIT& drop_limit = it->second;
        if (drop_limit.dwStartTime + drop_limit.nLimitDuration <= dwCurrentTime)
        {
            drop_limit.dwStartTime = dwCurrentTime;
            if (drop_limit.nCurCount != 0)
            {
                drop_limit.nCurCount = 0;
                CMessageHandler::GetInstance().BroadcastGSDropLimit(it->first, drop_limit.nLimitCount);
            }
        }
    }

    return TRUE;
}

void CMsDropMgr::OnDrop(INT32 itemid, INT32 itemcount)
{
    DROP_LIMIT_MAP::iterator it = m_drop_limit_map.find(itemid);
    LOG_PROCESS_ERROR(it != m_drop_limit_map.end());

    if (it != m_drop_limit_map.end())
    {
        INT32 remain_count = 0;

        DROP_LIMIT& dl = it->second;
        _CheckExpire(dl);

        dl.nCurCount += itemcount;
        remain_count = dl.nLimitCount - dl.nCurCount;
        if (remain_count < 0)
            remain_count = 0;

        CMessageHandler::GetInstance().BroadcastGSDropLimit(itemid, remain_count);
    }

Exit0:
    return;
}

BOOL CMsDropMgr::SendAllDropLimits(UINT32 dwGSSessionID)
{
    BOOL bRet = FALSE;
    for (DROP_LIMIT_MAP::iterator it=m_drop_limit_map.begin(); it!=m_drop_limit_map.end(); it++)
    {
        DROP_LIMIT& drop_limit = it->second;
        bRet = CMessageHandler::GetInstance().DoGSDropLimit(dwGSSessionID, it->first, drop_limit.nLimitCount - drop_limit.nCurCount);
        LOG_PROCESS_ERROR(bRet);
    }

    return TRUE;

Exit0:
    return FALSE;
}

void CMsDropMgr::_CheckExpire(DROP_LIMIT& droplimit)
{
    INT32 nCurTime = CManageServer::GetInstance().GetGameTime();
    if (nCurTime > droplimit.dwStartTime + droplimit.nLimitDuration)
    {
        droplimit.dwStartTime = nCurTime;
        droplimit.nCurCount = 0;
    }
}

void CMsDropMgr::PrintLimitInfo() const
{
    INT32 i = 0;
    for (DROP_LIMIT_MAP::const_iterator it = m_drop_limit_map.begin(); it != m_drop_limit_map.end(); ++it)
    {
        const DROP_LIMIT& dl = it->second;
        DBG("MsDropMgr: ItemID:%d, Count:%d/%d", it->first, dl.nCurCount, dl.nLimitCount);
        i++;
    }
    DBG("MsDropMgr: %d Items Total", i);
}
