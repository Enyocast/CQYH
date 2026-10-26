#include "stdafx.h"
#include "ms_adventure.h"

#include "math_ex.h"
#include "server_config.h"
#include "game_world_config.h"

#include "manageserver.h"
#include "adventure_data.h"
#include "guild/ms_guild_mgr.h"
#include "server_var.h"
#include "onlinerole/online_role_data_mgr.h"
#include "role_data.h"

CMSAdventure CMSAdventure::ms_Instance;

CMSAdventure::CMSAdventure()
{

}

CMSAdventure::~CMSAdventure()
{
    UnInit();
}

BOOL CMSAdventure::Init(void)
{
    const ADVENTURE_DATA* pAdventureData = CDataManager<ADVENTURE_DATA>::GetInstance().GetFirstData();
    while (pAdventureData)
    {
        switch (pAdventureData->nTriggerType)
        {
        case attKillNpc:
        case attDestoryDoodad:
        case attRefineEquip:
        case attAddSoul:
        case attRandomizeEquip:
        case att5MinOnlineTime:
            break;
        case attServerTime:
            m_ServerTimeList.push_back(pAdventureData);
            break;
        default:
            LOG_PROCESS_ERROR(FALSE);
            break;
        }

        pAdventureData = CDataManager<ADVENTURE_DATA>::GetInstance().GetNextData();
    }

    return TRUE;
Exit0:

    return FALSE;
}

BOOL CMSAdventure::UnInit(void)
{
    m_ServerTimeList.clear();

    return TRUE;
}

BOOL CMSAdventure::MainLoop(void)
{
    INT32 nRetCode = 0;
    UINT32 dwCurrentTime = CManageServer::GetInstance().GetGameTime();
    PROCESS_SUCCESS(dwCurrentTime % (5 * 60) != 0);

    for (ADVENTURE_DATA_LIST::iterator it = m_ServerTimeList.begin();
        it != m_ServerTimeList.end(); ++it)
    {
        const ADVENTURE_DATA* pAdventureData = *it;
        LOG_PROCESS_ERROR(pAdventureData);

        if ((dwCurrentTime % 86400 % (pAdventureData->ServerTime.nMaxDuration / GAME_FPS)) == 0)
        {
            for (INT32 nServerGroup = 0; nServerGroup < MAX_SERVER_GROUP_COUNT; nServerGroup++)
            {
                if (IsValidGroup(nServerGroup) &&
                    (g_Random(RATE_MAX) < pAdventureData->ServerTime.nChance))
                {
                    nRetCode = CMessageHandler::GetInstance().DoGSAdventureAward(
                        0, nServerGroup, 0, pAdventureData->nID);
                    LOG_CHECK_ERROR(nRetCode);
                }
            }
        }
    }

Exit1:
    return TRUE;
Exit0:
    return FALSE;
}

void CMSAdventure::CheckTrigger(MS_ONLINE_ROLE_DATA* pOnlineRole, INT32 nAdventureID, INT32 nVarID, INT32 nMaxCount, INT32 nChance)
{
    INT32 nRetCode = 0;
    INT32 nVarIndex = 0;
    INT32 nVarValue = 0;

    LOG_PROCESS_ERROR(pOnlineRole);

    switch (GetVarTypeFromID(nVarID))
    {
    case vtGuild:
        {
            CMsGuild* pMsGuild = CMsGuildMgr::GetInstance().FindGuildByID(pOnlineRole->pRoleData->dwGuildID);
            LOG_PROCESS_ERROR(pMsGuild);

            nVarIndex = GetVarIndexFromID(nVarID);
            nVarValue = pMsGuild->GetVariable(nVarIndex) + 1;
            if (nVarValue >= nMaxCount)
            {
                if (g_Random(RATE_MAX) < nChance)
                {
                    nRetCode = CMessageHandler::GetInstance().DoGSAdventureAward(
                        pOnlineRole->dwGSSessionID, pOnlineRole->pRoleData->byGroup, pOnlineRole->pRoleData->dwRoleID, nAdventureID);
                    LOG_CHECK_ERROR(nRetCode);
                }
                nVarValue = 0;
            }

            pMsGuild->SetVariable(nVarIndex, nVarValue);
        }
        break;
    case vtServer:
        {
            nVarIndex = GetVarIndexFromID(nVarID);
            nVarValue = CServerVar::GetInstance().GetVariable(pOnlineRole->pRoleData->byGroup, nVarIndex) + 1;
            if (nVarValue >= nMaxCount)
            {
                if (g_Random(RATE_MAX) < nChance)
                {
                    nRetCode = CMessageHandler::GetInstance().DoGSAdventureAward(
                        pOnlineRole->dwGSSessionID, pOnlineRole->pRoleData->byGroup, pOnlineRole->pRoleData->dwRoleID, nAdventureID);
                    LOG_CHECK_ERROR(nRetCode);
                }
                nVarValue = 0;
            }

            CServerVar::GetInstance().SetVariable(pOnlineRole->pRoleData->byGroup, nVarIndex, nVarValue);
        }
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

Exit0:
    return;
}