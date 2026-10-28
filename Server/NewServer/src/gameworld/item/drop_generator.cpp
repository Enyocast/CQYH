#include "stdafx.h"
#include "drop_generator.h"
#include "item_mgr.h"
#include "game_world.h"
#include "message_handler.h"
#include "drop.h"
#include "server_config.h"
#include "variable_def.h"

CDropGenerator::CDropGenerator()
{
    m_bDropMax = FALSE;
}

CDropGenerator::~CDropGenerator()
{

}

CDropGenerator& CDropGenerator::GetInstance(void)
{
    static CDropGenerator s_DropGen;
    return s_DropGen;
}

BOOL CDropGenerator::GenerateGuildDungeonDrops(INT32 nServerGroup, const DROP_CHANCE_DATA chances[], INT32 chance_count, UINT32 itemID[], INT32 itemCount[], INT32 &nDropCount)
{
	INT32 nRetCode = 0;
    nDropCount = 0;

    for (INT32 nIndex = 0; nIndex < chance_count; ++nIndex)
    {
		DropContent content = { 0 };
		
		nRetCode = GenerateDropContentFromDropChanceData(nServerGroup, chances + nIndex, content, RATE_MAX);
		if (!nRetCode)
			continue;

        if (content.m_type == DropContent::DROP_ITEM)
        {
            itemID[nDropCount] = content.m_item->m_iteminfo.m_nTemplateID;
            itemCount[nDropCount] = content.m_item->m_pTemplate->m_byDurType == DURTYPE_STACK ? content.m_item->m_iteminfo.m_nCurDur : 1;
            BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(content.m_item);
            LOG_CHECK_ERROR(bItemRet);
        }
        else if (content.m_type == DropContent::DROP_MONEY)
        {
            itemID[nDropCount] = content.m_money.moneytype;
            itemCount[nDropCount] = content.m_money.count;
        }

        ++nDropCount;
    }
    return TRUE;
}

BOOL CDropGenerator::GenerateDrop(INT32 nServerGroup, INT32 itemid, INT32 itemcount, CScene* scene, INT64 llX, INT64 llY, INT64 llZ, UINT32 srcid, BOOL instantpick)
{
    DropContent content;
    BOOL bRet = FALSE;
    CDrop::DropState dropstate = instantpick ? CDrop::DS_PUBLIC : CDrop::DS_PROTECT;

    LOG_PROCESS_ERROR(scene);
    LOG_PROCESS_ERROR(itemid > 0);
    LOG_PROCESS_ERROR(itemcount > 0);

    if (itemid < 100)
    {
        content.m_type = DropContent::DROP_MONEY;
        content.m_money.moneytype = itemid;
        content.m_money.count = itemcount;
    }
    else
    {
        bRet = _CheckDropLimit(nServerGroup, itemid, itemcount);
        LOG_PROCESS_ERROR(bRet);

        const ITEM_DATA* item_data = GetItemData(itemid);
        LOG_PROCESS_ERROR(item_data &&
            g_ServerConfig.GroupConfig[nServerGroup].dwStartDate + item_data->m_nDropFromServerStart * 3600 < CGameWorld::GetInstance().GetGameTime());


        content.m_type = DropContent::DROP_ITEM;
        content.m_item = CItemMgr::GetInstance().GenerateItem(item_data, itemcount);
        LOG_PROCESS_ERROR(content.m_item);
    }

    bRet = _GenerateDrop(content, scene, llX, llY, llZ, srcid, dropstate);
    LOG_PROCESS_ERROR(bRet);

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDropGenerator::GenerateDrops(INT32 nServerGroup, const DROP_CHANCE_DATA chances[], INT32 chance_count,
    CScene* scene, INT64 llX, INT64 llY, INT64 llZ,
    UINT32 ownerid, UINT32 srcid, INT32 srclevel,
    BOOL bUniqueOrBoss, BOOL bBigDrop)
{
    INT32 nRetCode = 0;
    CDrop* drops[MAX_NPC_DROP_CHANCE];
    INT32 drop_count = 0;
    BOOL bRet = FALSE;
    CCharacter* pChar = CGameWorld::GetInstance().FindValidCharacter(ownerid);
    CRole* pOwnerRole = NULL;
    CTeamInGS* pTeam = NULL;
    INT32 loop_times = bBigDrop ? 10 : 1;

    std::list<CRole*> gold_pool_list;
    INT32 gold_pool_rate = RATE_MAX;     // Gold pool reduction rate

    std::list<CRole*> owner_list;
    INT32 level_diff_rate = RATE_MAX;    // Item drop adjustment for lower-level NPCs, based on level difference
    INT32 fcm_rate = RATE_MAX;           // Anti-addiction reduction rate

    INT32 final_rate = RATE_MAX;         // Final probability
    const static INT64 llMaxLootDistance = (g_GWConfig.nLootDistance * POINT_PER_CM) * (g_GWConfig.nLootDistance * POINT_PER_CM);

    LOG_PROCESS_ERROR(chances);
    LOG_PROCESS_ERROR(scene);
    LOG_PROCESS_ERROR(chance_count <= MAX_NPC_DROP_CHANCE);

    if (pChar && pChar->GetHostID())
    {
        pOwnerRole = CGameWorld::GetInstance().FindValidRole(pChar->GetHostID());
    }
    else
    {
        pOwnerRole = CGameWorld::GetInstance().FindValidRole(ownerid);
    }

    if (pOwnerRole)
    {
        pTeam = CGameWorld::GetInstance().FindTeam(pOwnerRole->GetTeamID());

        // Team
        if (pTeam && pOwnerRole->GetLevel() > g_GWConfig.nFreeRoleLevel)
        {
            gold_pool_rate = 0;
            for (UINT32 i = 0; i < pTeam->GetMaxMemberCount(); i++)
            {
                CRole* pRole = CGameWorld::GetInstance().FindValidRole(pTeam->GetMemberTable(i).dwRoleID);
                if (pRole && pRole->GetLevel() > g_GWConfig.nFreeRoleLevel &&
                    pRole->GetMoveState() != CMS_DIE &&
                    pRole->GetScene() == pOwnerRole->GetScene() &&
                    g_GetDistance3D(llX, llY, llZ, pRole->GetX(), pRole->GetY(), pRole->GetZ()) < llMaxLootDistance)
                {
                    gold_pool_list.push_back(pRole);
                    gold_pool_rate += pRole->GetItemBag()->GetChanceByGoldPool();
                }
            }
            if (gold_pool_list.size() > 0)
                gold_pool_rate /= gold_pool_list.size();
            else
                gold_pool_rate = RATE_MAX;
        }
        // Individual
        else
        {
            gold_pool_list.push_back(pOwnerRole);
            gold_pool_rate = pOwnerRole->GetItemBag()->GetChanceByGoldPool();
        }

        // Team - calculate level-difference drop reduction
        if (pTeam)
        {
            INT32 total_role_level = 0;
            INT32 average_role_level = 0;
            fcm_rate = RATE_MAX;
            for (INT32 nMemberIndex = 0; nMemberIndex < pTeam->GetMaxMemberCount(); nMemberIndex++)
            {
                CRole* pRole = CGameWorld::GetInstance().FindValidRole(pTeam->GetMemberTable(nMemberIndex).dwRoleID);
                if (pRole &&
                    pRole->GetMoveState() != CMS_DIE &&
                    pRole->GetScene() == pOwnerRole->GetScene() &&
                    g_GetDistance3D(llX, llY, llZ, pRole->GetX(), pRole->GetY(), pRole->GetZ()) < llMaxLootDistance)
                {
                    if (fcm_rate > pRole->GetFcmRate())
                        fcm_rate = pRole->GetFcmRate();

                    total_role_level += pRole->GetLevel();
                    owner_list.push_back(pRole);
                }
            }
            if (owner_list.size() > 0)
                average_role_level = total_role_level / owner_list.size();
            else
                average_role_level = pOwnerRole->GetLevel();

            if (average_role_level > srclevel)
            {
                INT32 level_diff = average_role_level - srclevel;
                LOG_PROCESS_ERROR(level_diff < MAX_ROLE_LEVEL);

                level_diff_rate = g_GWConfig.nDropChanceRate[level_diff];
            }
        }
        // Individual
        else
        {
            owner_list.push_back(pOwnerRole);
            if (pOwnerRole->GetLevel() > srclevel)
            {
                INT32 level_diff = pOwnerRole->GetLevel() - srclevel;
                LOG_PROCESS_ERROR(level_diff < MAX_ROLE_LEVEL);

                level_diff_rate = g_GWConfig.nDropChanceRate[level_diff];
            }
        }
    }
    else
    {
        gold_pool_rate = RATE_MAX;
        level_diff_rate = RATE_MAX;
        fcm_rate = RATE_MAX;
    }

    memset(drops, 0, sizeof(drops));

    // Calculate final probability
    if (!bUniqueOrBoss)
        final_rate = level_diff_rate;
    final_rate = final_rate * gold_pool_rate / RATE_MAX;
    final_rate = final_rate * fcm_rate / RATE_MAX;
    //final_rate = final_rate * g_GWConfig.nGlobalDropRate / RATE_MAX;  // Default code: gameworldconfig.lua specifies 100000
    final_rate = final_rate * 10000 / RATE_MAX;  // Currently fixed at 10000

    for (INT32 i = 0; i < loop_times; i++)
    {
        for (INT32 nIndex = 0; nIndex < chance_count; nIndex++)
        {
            if (chances[nIndex].nDropGroupID > 0 && chances[nIndex].nDropChance > 0)
            {
                CDrop* pDrop = _GenerateOneDrop(nServerGroup, chances + nIndex, final_rate);
                if (pDrop == NULL)
                    continue;

                drops[drop_count++] = pDrop;

                if (drop_count >= MAX_NPC_DROP_CHANCE)
                    break;
            }
        }

        if (drop_count >= MAX_NPC_DROP_CHANCE)
            break;
    }

    if (drop_count > 0)
    {
        for (INT32 i = 0; i < drop_count; i++)
        {
            CDrop* drop = drops[i];

            // Update the gold pool
            if (!gold_pool_list.empty())
            {
                INT32 sub_gold = 0;
                if (drop->m_content.m_type == DropContent::DROP_MONEY && drop->m_content.m_money.moneytype == MONEYTYPE_02)
                    sub_gold = drop->m_content.m_money.count;
                else if (drop->m_content.m_type == DropContent::DROP_ITEM)
                    sub_gold = drop->m_content.m_item->m_pTemplate->m_nSellPrice;
                sub_gold /= gold_pool_list.size();
                if (sub_gold > 0)
                {
                    for (std::list<CRole*>::iterator it = gold_pool_list.begin(); it != gold_pool_list.end(); ++it)
                        (*it)->GetItemBag()->SubGoldPool(sub_gold);
                }
            }

            // Add characters eligible to loot
            if (!owner_list.empty())
            {
                for (std::list<CRole*>::iterator it = owner_list.begin(); it != owner_list.end(); ++it)
                {
                    drop->AddOwner((*it)->GetObjID());
                }
            }

            // Add a ground item object to the map
            bRet = scene->AddDrop(drop, llX, llY, llZ, srcid);
            LOG_CHECK_ERROR(bRet);

            // Delete the object if insertion fails
            if (!bRet)
            {
                bRet = drop->UnInit();
                LOG_CHECK_ERROR(bRet);

                bRet = CGameWorld::GetInstance().DelDrop(drop);
                LOG_CHECK_ERROR(bRet);
            }
        }
    }

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDropGenerator::GeneratePKDrops(Item* items[], INT32 itemcount, CScene* scene, INT64 llX, INT64 llY, INT64 llZ, UINT32 ownerid)
{
    BOOL bRet = FALSE;

    LOG_PROCESS_ERROR(itemcount > 0 && itemcount <= 256);

    for (INT32 i=0; i<itemcount; i++)
    {
        DropContent content;
        content.m_type = DropContent::DROP_ITEM;
        content.m_item = items[i];

        _GenerateDrop(content, scene, llX, llY, llZ, ownerid, CDrop::DS_PUBLIC);
    }

    return TRUE;

Exit0:
    return FALSE;
}

BOOL CDropGenerator::GenerateDropContentFromDropGroupData(INT32 nServerGroup, const DROP_GROUP_DATA* data, DropContent& content)
{
    INT32 random_number;

    LOG_PROCESS_ERROR(data);
    LOG_PROCESS_ERROR(data->m_bEnabled);
    LOG_PROCESS_ERROR(data->m_nDataCount > 0 && data->m_nDataCount <= MAX_DROP_DATA_COUNT);
    LOG_PROCESS_ERROR(data->m_nTotalWeight > 0);

    random_number = g_Random(data->m_nTotalWeight);

    for (INT32 i = 0; i < data->m_nDataCount; i++)
    {
        if (random_number < data->m_DropData[i].m_nWeight)
        {
            if (data->m_DropData[i].m_nItemID < MONEYTYPE_COUNT)
            {
                content.m_type = DropContent::DROP_MONEY;
                content.m_money.moneytype = data->m_DropData[i].m_nItemID;
                content.m_money.count = g_Random(data->m_DropData[i].m_nCountMin, data->m_DropData[i].m_nCountMax);
            }
            else
            {
                INT32 itemcount = g_Random(data->m_DropData[i].m_nCountMin, data->m_DropData[i].m_nCountMax);
                BOOL bRet = _CheckDropLimit(nServerGroup, data->m_DropData[i].m_pItemData->m_nTemplateID, itemcount);
                LOG_PROCESS_ERROR(bRet);

                LOG_PROCESS_ERROR(data->m_DropData[i].m_pItemData &&
					g_ServerConfig.GroupConfig[nServerGroup].dwStartDate + data->m_DropData[i].m_pItemData->m_nDropFromServerStart * 3600 < CGameWorld::GetInstance().GetGameTime());

                content.m_type = DropContent::DROP_ITEM;

                // Check whether it is a necklace
                if (data->m_DropData[i].m_pItemData->m_bySubType == ITEMSUBTYPE_EQUIP_NECKLACE)
                {
                    content.m_item = CItemMgr::GetInstance().GenerateItem(nServerGroup, data->m_DropData[i].m_pItemData, itemcount, data->m_bRandomDur);
                    LOG_PROCESS_ERROR(content.m_item);
                }
                else
                {
                    content.m_item = CItemMgr::GetInstance().GenerateItem(data->m_DropData[i].m_pItemData, itemcount, data->m_bRandomDur);
                    LOG_PROCESS_ERROR(content.m_item);
                }
            }

            return TRUE;
        }
        else
        {
            random_number -= data->m_DropData[i].m_nWeight;
        }
    }

Exit0:
    return FALSE;
}

BOOL CDropGenerator::GenerateDropContentFromDropChanceData(
    INT32 nServerGroup, const DROP_CHANCE_DATA* pcDropChance, DropContent& rDropContent, INT32 nModifiedRate)
{
	INT32 nRetCode = 0;
	const DROP_GROUP_DATA* pcDropData = NULL;
	INT64 llDropChance = pcDropChance->nDropChance;
	UINT32 dwRandomNumber = 0;

	LOG_PROCESS_ERROR(pcDropChance);
	PROCESS_ERROR(pcDropChance->nDropGroupID > 0);
	PROCESS_ERROR(pcDropChance->nDropChance > 0);

	pcDropData = CDropManager::GetInstance().GetData(pcDropChance->nDropGroupID);
	LOG_PROCESS_ERROR(pcDropData);
	PROCESS_ERROR(pcDropData->m_bEnabled);

	llDropChance = llDropChance * nModifiedRate / RATE_MAX;

	dwRandomNumber = g_Random(1000000);
    PROCESS_ERROR(dwRandomNumber < llDropChance || m_bDropMax);

    nRetCode = GenerateDropContentFromDropGroupData(nServerGroup, pcDropData, rDropContent);
	PROCESS_ERROR(nRetCode);

	if (g_GWConfig.DebugOption.dropstat)
	{
		if (rDropContent.m_type == DropContent::DROP_ITEM)
			DBG("drop item %d from group %d chance %d, modified rate %d, total chance %lld, random number %u",
				rDropContent.m_item->m_pTemplate->m_nTemplateID,
				pcDropChance->nDropGroupID, pcDropChance->nDropChance, nModifiedRate, llDropChance, dwRandomNumber);
		else if (rDropContent.m_type == DropContent::DROP_MONEY)
			DBG("drop money %d %d from group %d chance %d, modified rate %d, total chance %lld, random number %u",
				rDropContent.m_money.moneytype, rDropContent.m_money.count, pcDropChance->nDropGroupID, pcDropChance->nDropChance,
				nModifiedRate, llDropChance, dwRandomNumber);
	}

	return TRUE;

Exit0:
    if (g_GWConfig.DebugOption.dropstat && pcDropChance)
    {
        DBG("failed to drop from group %d chance %d, modified rate %d, total chance %lld, random number %u",
            pcDropChance->nDropGroupID, pcDropChance->nDropChance,
            nModifiedRate, llDropChance, dwRandomNumber);
    }

	return FALSE;
}

void CDropGenerator::SetDropLimit(INT32 itemid, INT32 itemcount)
{
    m_drop_limit_map[itemid] = itemcount;
}

void CDropGenerator::ToggleGlobalDropMax()
{
    m_bDropMax = !m_bDropMax;
}

CDrop* CDropGenerator::_GenerateOneDrop(INT32 nServerGroup, const DROP_CHANCE_DATA* pcDropChance, INT32 nModifiedRate)
{
	CDrop* pResult = NULL;
	INT32 nRetCode = 0;
    DropContent drop_content;
    memset(&drop_content, 0, sizeof(drop_content));

    nRetCode = GenerateDropContentFromDropChanceData(nServerGroup, pcDropChance, drop_content, nModifiedRate);
	PROCESS_ERROR(nRetCode);

	pResult = CGameWorld::GetInstance().NewDrop(0);
	LOG_PROCESS_ERROR(pResult);

    nRetCode = pResult->Init(CGameWorld::GetInstance().GetDropID(pResult), drop_content, CDrop::DS_PROTECT);
	LOG_PROCESS_ERROR(nRetCode);

	return pResult;
Exit0:
	if (pResult)
	{
		pResult->UnInit();
		CGameWorld::GetInstance().DelDrop(pResult);
	}
    else if (drop_content.m_type == DropContent::DROP_ITEM && drop_content.m_item)
	{
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(drop_content.m_item);
        LOG_CHECK_ERROR(bItemRet);
	}

	return NULL;
}

// Check drop limit
BOOL CDropGenerator::_CheckDropLimit(INT32 nServerGroup, INT32 itemid, INT32 itemcount)
{
    // Get the current server-wide limit for itemid
    INT32 drop_count = CGameWorld::GetInstance().GetServerVariable(nServerGroup, MakeServerKey(esvtItemDropLimitType0, itemid));

    const ITEM_DATA* data = GetItemData(itemid);
    LOG_PROCESS_ERROR(data);

    if (data->m_nDropLimitCount[0] == 0)
        return TRUE;

    // Check whether the quantity exceeds the limit
    if (drop_count >= data->m_nDropLimitCount[0])
    {
        INF("Drop Limit Exceeded: ServerGroup:%d, ItemID:%d, CurItemCount:%d", nServerGroup, itemid, drop_count);
        return FALSE;
    }
    // Below the limit
    else
    {
        INT32 inc_count = data->m_byDurType == DURTYPE_STACK ? itemcount : 1;

        // Tell MS to increase the limited count
        CGameWorld::GetInstance().SetServerVariable(nServerGroup, MakeServerKey(esvtItemDropLimitType0, itemid), FALSE, inc_count);

        return TRUE;
    }

Exit0:
    return FALSE;
}

BOOL CDropGenerator::_GenerateDrop(DropContent& content, CScene* scene, INT64 llX, INT64 llY, INT64 llZ, UINT32 srcid, CDrop::DropState state)
{
    BOOL bRet = FALSE;

    CDrop* drop = CGameWorld::GetInstance().NewDrop(0);
    LOG_PROCESS_ERROR(drop);

    bRet = drop->Init(CGameWorld::GetInstance().GetDropID(drop), content, state);
    LOG_PROCESS_ERROR(bRet);

    bRet = scene->AddDrop(drop, llX, llY, llZ, srcid);
    LOG_PROCESS_ERROR(bRet);

    return TRUE;

Exit0:
    if (drop)
    {
        bRet = drop->UnInit();
        LOG_CHECK_ERROR(bRet);

        bRet = CGameWorld::GetInstance().DelDrop(drop);
        LOG_CHECK_ERROR(bRet);
    }
    return FALSE;
}
