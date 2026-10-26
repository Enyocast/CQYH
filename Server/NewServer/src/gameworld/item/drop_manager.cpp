#include "stdafx.h"
#include "drop_manager.h"
#include "drop_group_data.h"
#include "item_data.h"
#include "npc_def.h"
#include "doodad_def.h"
#include "npc_data.h"

CDropManager CDropManager::ms_Instance;

BOOL CDropManager::Init()
{
    return Reload();
}

BOOL CDropManager::UnInit()
{
    m_datamap.clear();
    return TRUE;
}

BOOL CDropManager::Reload()
{
    INT32 nRetCode = 0;

    nRetCode = UnInit();
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = InitDropGroupData();
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDropManager::IsBigDrop(INT32 templateid)
{
    const NPC_DATA* data = CDataManager<NPC_DATA>::GetInstance().GetData(templateid);
    LOG_PROCESS_ERROR(data);

    if (data->nBigDropInterval > 0)
    {
        INT32& die_time = m_npc_die_time_map[templateid];
        die_time++;
        if (die_time >= data->nBigDropInterval)
        {
            DBG("Big Drop !! Npc:%d", templateid);
            die_time = 0;
            return TRUE;
        }
    }

Exit0:
    return FALSE;
}

const DROP_GROUP_DATA* CDropManager::GetData(INT32 nDropGroupID)
{
    DROP_GROUP_DATA_MAP::const_iterator it = m_datamap.find(nDropGroupID);
    if (it == m_datamap.end())
        return NULL;
    else
        return &it->second;
}

BOOL CDropManager::InitDropGroupData()
{
    INT32 nSuccess = 0;
    for (const DROP_GROUP_DATA_RAW* data = CDataManager<DROP_GROUP_DATA_RAW>::GetInstance().GetFirstData();
        data; data = CDataManager<DROP_GROUP_DATA_RAW>::GetInstance().GetNextData())
    {
        DROP_GROUP_DATA* group = NULL;
        const ITEM_DATA* item_data = GetItemData(data->m_nItemID);

        if (data->m_nDropGroupID == 0)
            continue;

        if (item_data == NULL)
        {
            CRI("Unknown ItemID:%d In DropGroup:%d", data->m_nItemID, data->m_nDropGroupID);
            continue;
        }

        group = &m_datamap[data->m_nDropGroupID];
        if (group->m_nDataCount >= MAX_DROP_DATA_COUNT)
        {
            LOG_CHECK_ERROR(group->m_nDataCount < MAX_DROP_DATA_COUNT);
            continue;
        }

        if (group->m_nDropGroupID == 0)
        {
            group->m_nDropGroupID = data->m_nDropGroupID;
            group->m_bEnabled = data->m_bEnabled;
            group->m_bModChanceByLevel = data->m_bModChanceByLevel;
            group->m_bRandomDur = data->m_bRandomDur;
        }

        group->m_DropData[group->m_nDataCount].m_nItemID = data->m_nItemID;
        group->m_DropData[group->m_nDataCount].m_pItemData = item_data;
        group->m_DropData[group->m_nDataCount].m_nCountMin = data->m_nCountMin;
        group->m_DropData[group->m_nDataCount].m_nCountMax = data->m_nCountMax;
        group->m_DropData[group->m_nDataCount].m_nWeight = data->m_nWeight;
        group->m_nDataCount++;
        group->m_nTotalWeight += data->m_nWeight;

        ++nSuccess;
    }

    INF("read %d / %d drop group data successfully", nSuccess, CDataManager<DROP_GROUP_DATA_RAW>::GetInstance().GetDataCount() - 1);

    return TRUE;
}
