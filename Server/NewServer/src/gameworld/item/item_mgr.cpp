#include "stdafx.h"
#include "item_mgr.h"
#include "server_config.h"
#include "data_manager.h"
#include "item.h"
#include "game_world.h"
#include "attribute_pool_data.h"
#include "rune_data.h"
#include "spell_config.h"
#include "spell.h"

UINT64 CreateItemGuid()
{
    //ItemGuid共8字节，从左至右说明：
    //1-4:  时间
    //5:    大区ID
    //6:    GameServer ID
    //7-8:  流水号

    static UINT16 item_seed = 0;
    static UINT64 last_game_time = 0;
    static UINT32 area_id = g_ServerConfig.Common.nAreaID;
    static UINT32 gs_id = CGameWorld::GetInstance().GetGsSessionID();
    UINT64 cur_game_time = CGameWorld::GetInstance().GetGameTime();

    if (last_game_time < cur_game_time)
    {
        item_seed = 0;
        last_game_time = cur_game_time;
    }
    else
    {
        if (item_seed < 0xFFFF)
            item_seed++;
        else
            CRI("Create Item GUID Error!!! GameTime:%I64d, AreaID: %u, GsID: %u, ItemSeed: FFFF", (UINT32)cur_game_time, area_id, gs_id);
    }

    return (cur_game_time << 32) | (area_id << 22) | (gs_id << 16) | item_seed;
}

CItemMgr::CItemMgr()
{
}

CItemMgr& CItemMgr::GetInstance(void)
{
    static CItemMgr s_ItemMgr;

    return s_ItemMgr;
}

Item* CItemMgr::GenerateItem(INT32 nTemplateID, INT32 nItemCount)
{
    const ITEM_DATA* itemdata = NULL;

    LOG_PROCESS_ERROR(nTemplateID >= 99);

    itemdata = GetItemData(nTemplateID);
    LOG_PROCESS_ERROR(itemdata);

    return GenerateItem(itemdata, nItemCount);

Exit0:
	CRI("failed to generate item %d count %d", nTemplateID, nItemCount);

    return NULL;
}

Item* CItemMgr::GenerateItem(const ITEM_DATA* itemdata, INT32 nItemCount, BOOL bRandomDur/*=FALSE*/)
{
    Item* item = NULL;
    UINT64 guid = 0;
    LOG_PROCESS_ERROR(itemdata);
    LOG_PROCESS_ERROR(itemdata->m_nTemplateID >= 99);

    guid = CreateItemGuid();
    item = CGameWorld::GetInstance().NewItem(guid);
    LOG_PROCESS_ERROR(item);

    item->m_pTemplate = itemdata;
    item->m_bAttrEffective = FALSE;
    memset(&item->m_iteminfo, 0, sizeof(ItemInfo));

    item->m_iteminfo.m_llGuid = guid;
    item->m_iteminfo.m_nTemplateID = itemdata->m_nTemplateID;
    item->m_iteminfo.m_nMaxDur = itemdata->m_nDur;
    switch (itemdata->m_byDurType)
    {
    case DURTYPE_STACK:
        if (nItemCount > itemdata->m_nDur)
            item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
        else
            item->m_iteminfo.m_nCurDur = nItemCount;
        break;
    case DURTYPE_EQUIP:
        if (bRandomDur)
        {
            item->m_iteminfo.m_nMaxDur = itemdata->m_nDur * g_Random(EQUIP_MAX_DUR_RANDOM_MIN, EQUIP_MAX_DUR_RANDOM_MAX) / RATE_MAX;
            item->m_iteminfo.m_nCurDur = item->m_iteminfo.m_nMaxDur * g_Random(EQUIP_MAX_DUR_RANDOM_MIN, RATE_MAX) / RATE_MAX;
        }
        else
        {
            item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
            item->m_iteminfo.m_nMaxDur = itemdata->m_nDur;
        }
        break;
    case DURTYPE_USE:
        item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
        break;
    case DURTYPE_DEPOSIT:
        item->m_iteminfo.m_nCurDur = 0;
        break;
    case DURTYPE_RECOVER:
        item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
        item->m_iteminfo.m_nMaxDur = itemdata->m_nDur;
        break;
    case DURTYPE_PURITY:
        item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
        item->m_iteminfo.m_nMaxDur = itemdata->m_nDur;
        break;
    case DURTYPE_NONE:
        item->m_iteminfo.m_nCurDur = 1;
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
    }
    item->m_iteminfo.m_byBindType = itemdata->m_byBindType;

    // 生成 随机属性/孔位
    if (itemdata->m_byType == ITEMTYPE_EQUIP)
    {
        const EQUIP_DATA* equipdata = (const EQUIP_DATA*)itemdata;

        item->m_iteminfo.m_byIdentified = equipdata->m_byIdentified;

        if (equipdata->m_byIdentified)
        {
            GenerateRandomAttributes(item);  // 随机属性
        }

        // 孔位, 暂时屏蔽
        //_GenerateSockets(item->m_iteminfo, equipdata->m_nSocketChance, equipdata->m_bySocketCountMin, equipdata->m_bySocketCountMax, equipdata->m_nColorSocketRate);
    }

    return item;

Exit0:
	if (itemdata)
		CRI("failed to generate item %d count %d", itemdata->m_nTemplateID, nItemCount);

    if (item)
        CGameWorld::GetInstance().DelItem(item);

    return NULL;
}

Item* CItemMgr::LoadItem(const ItemInfo& iteminfo)
{
    Item* item = NULL;
    const ITEM_DATA* itemdata = GetItemData(iteminfo.m_nTemplateID);
    LOG_PROCESS_ERROR(itemdata);

    item = CGameWorld::GetInstance().NewItem(iteminfo.m_llGuid);
    if (item == NULL)
    {
        Item* existing_item = CGameWorld::GetInstance().FindItem(iteminfo.m_llGuid);
        if (existing_item)
            CRI("Dupe Item Found: GUID:%I64u, [New: TemplateID:%d, Dur:%d] [Existing: TemplateID:%d, Dur:%d]",
            iteminfo.m_llGuid, iteminfo.m_nTemplateID, iteminfo.m_nCurDur,
            existing_item->m_iteminfo.m_nTemplateID, existing_item->m_iteminfo.m_nCurDur);
        else
            CRI("NewItem Failed");
    }
    LOG_PROCESS_ERROR(item);

    item->m_pTemplate = itemdata;
    item->m_iteminfo = iteminfo;
    item->m_bAttrEffective = FALSE;

    return item;

Exit0:
    return NULL;
}

Item* CItemMgr::CopyItem(const Item* item)
{
    Item* newitem = NULL;
    UINT64 guid = 0;

    LOG_PROCESS_ERROR(item);

    guid = CreateItemGuid();
    newitem = CGameWorld::GetInstance().NewItem(guid);
    LOG_PROCESS_ERROR(newitem);

    *newitem = *item;
    newitem->m_iteminfo.m_llGuid = guid;

    return newitem;

Exit0:
    return NULL;
}

BOOL CItemMgr::DestroyItem(Item* item)
{
    BOOL bRet = CGameWorld::GetInstance().DelItem(item);
    if (!bRet)
    {
        CRI("CItemMgr::DestroyItem Failed: Guid:%I64u, ItemID:%d", item->m_iteminfo.m_llGuid, item->m_iteminfo.m_nTemplateID);
    }
    return bRet;
}

// 生成 随机孔位
void CItemMgr::_GenerateSockets(ItemInfo& iteminfo, INT32 chance, UINT8 countmin, UINT8 countmax, INT32 colorrate)
{
    //随机孔的个数，0-count
    //随机孔的颜色（不包含彩色孔，其他颜色概率平均）
    //由装备模板数据决定彩色孔出现的概率，出现则将最后一个孔修改为彩色孔
    //因此，如果第一次随机到0个孔，则彩色孔也不会出现

    UINT32 temp_socket_type = SOCKET_NONE;
    INT32 actual_socket_count = 0;

    iteminfo.m_dwSocketCombination = 0;

    LOG_PROCESS_ERROR(chance >= 0 && chance <= RATE_MAX);

    //if (g_Random(RATE_MAX) >= chance)    // 默认代码 (概率高)
    if (g_Random(RATE_MAX) < chance)    // 修改代码 (概率低)
        return;

    LOG_PROCESS_ERROR(countmin <= countmax);
    LOG_PROCESS_ERROR(countmax <= MAX_SOCKET_COUNT);
    PROCESS_ERROR(countmax > 0);

    actual_socket_count = g_Random(countmin, countmax + 1);

    if (actual_socket_count == 0)
        return;

    for (UINT8 i = 0; i < actual_socket_count; i++)
    {
        if (i == actual_socket_count - 1 && g_Random(RATE_MAX) < colorrate)
        {
            temp_socket_type = SOCKET_COLORFUL;
        }
        else
        {
            temp_socket_type = g_Random(SOCKET_COLORFUL - 1) + 1;
        }

        iteminfo.m_dwSocketCombination |= temp_socket_type << (i * 8);
    }

Exit0:
    return;
}

// 生成 随机属性
void CItemMgr::GenerateRandomAttributes(Item* item, INT32 modifyrate/* = RATE_MAX*/, INT32 nServerGroup/* = 0*/)
{
    const EQUIP_DATA* equip_data = (const EQUIP_DATA*)item->m_pTemplate;
    INT32 attr_count = 0;

    // 计算概率
    //INT32 final_rate = (INT32)((INT64)equip_data->m_nRandomAttributeChance * modifyrate / RATE_MAX);  默认代码
    INT32 final_rate = equip_data->m_nRandomAttributeChance;  // 修改代码, 去掉计算

    // 默认代码
    if (g_Random(RATE_MAX) >= final_rate)
        return;

    // 判断 运2项链产出限制
    BOOL bIsLuck2Equip = FALSE;
    BOOL bIsLuck2NecklaceLimit = FALSE;
    if (equip_data->m_bySubType == ITEMSUBTYPE_EQUIP_NECKLACE)
    {
        if (CheckEquipIsLuck2Item(equip_data->m_nTemplateID) == TRUE)
        {
            INT32 total = 0;
            for (const auto ItemID : g_ServerConfig.CC.nLuck2NecklaceItemID)
            {
                total += CGameWorld::GetInstance().GetServerVariable(nServerGroup, MakeServerKey(esvtItemDropLimitLuck2Necklace, ItemID));
            }

            if (total >= g_ServerConfig.CC.nItemDropLimitLuck2NecklaceCount)
            {
                bIsLuck2NecklaceLimit = TRUE;
            }
        }
    }

    // 不是 [运2项链物品] 或者 是 [运2项链物品, 但是还没达到限制数量], 还是走默认代码流程 不变
    if (bIsLuck2NecklaceLimit == FALSE)
    {
        for (INT32 i = 0; i < MAX_RANDOM_ATTR_COUNT; i++)
        {
            if (equip_data->m_nAttributePoolID[i] && g_Random(RATE_MAX) < equip_data->m_nAttributePoolChance[i])
            {
                INT32 random_number;
                const ATTRIBUTE_POOL* pool = CAttributePoolDataManager::GetInstance().GetPool(equip_data->m_nAttributePoolID[i]);
                LOG_PROCESS_ERROR(pool);

                random_number = g_Random(pool->m_nTotalWeight);

                for (INT32 j = 0; j < pool->m_nDataCount; j++)
                {
                    if (random_number < pool->m_PoolData[j].m_nWeight)
                    {
                        UINT16 tmpRandomAttrID = g_Random(pool->m_PoolData[j].m_nAttributeIDMin, pool->m_PoolData[j].m_nAttributeIDMax + 1);

                        item->m_iteminfo.m_wRandomAttrID[attr_count++] = tmpRandomAttrID;

                        // 是项链, 并且是运2属性, 则增加变量
                        if (equip_data->m_bySubType == ITEMSUBTYPE_EQUIP_NECKLACE &&
                            tmpRandomAttrID >= g_ServerConfig.CC.nMinLuck2AttributelID && 
                            tmpRandomAttrID <= g_ServerConfig.CC.nMaxLuck2AttributelID)
                        {
                            CGameWorld::GetInstance().SetServerVariable(nServerGroup, MakeServerKey(esvtItemDropLimitLuck2Necklace, equip_data->m_nTemplateID), FALSE, 1);
                        }

                        break;
                    }
                    else
                    {
                        random_number -= pool->m_PoolData[j].m_nWeight;
                    }
                }
            }
        }
    }
    // 是 [运2项链物品] , 并且达到限制数量了, 只有[运2项链物品] 才会走这里
    else
    {
        for (INT32 i = 0; i < MAX_RANDOM_ATTR_COUNT; i++)
        {
            if (equip_data->m_nAttributePoolID[i] && g_Random(RATE_MAX) < equip_data->m_nAttributePoolChance[i])
            {
                INT32 random_number;
                const ATTRIBUTE_POOL* pool = CAttributePoolDataManager::GetInstance().GetPool(equip_data->m_nAttributePoolID[i]);
                LOG_PROCESS_ERROR(pool);

                random_number = g_Random(pool->m_nTotalWeight);

                for (INT32 j = 0; j < pool->m_nDataCount; j++)
                {
                    if (random_number < pool->m_PoolData[j].m_nWeight)
                    {
                        // 随机一个属性ID
                        UINT16 tmpRandomAttrID = g_Random(pool->m_PoolData[j].m_nAttributeIDMin, pool->m_PoolData[j].m_nAttributeIDMax + 1);

                        // 如果是 [运2属性] 则直接跳过, 否则 赋值属性
                        if (tmpRandomAttrID >= g_ServerConfig.CC.nMinLuck2AttributelID && tmpRandomAttrID <= g_ServerConfig.CC.nMaxLuck2AttributelID)
                        {
                            random_number -= pool->m_PoolData[j].m_nWeight;
                        }
                        else
                        {
                            item->m_iteminfo.m_wRandomAttrID[attr_count++] = tmpRandomAttrID;
                            break;
                        }
                    }
                    else
                    {
                        random_number -= pool->m_PoolData[j].m_nWeight;
                    }
                }
            }
        }
    }

    // 默认代码
    //for (INT32 i = 0; i < MAX_RANDOM_ATTR_COUNT; i++)
    //{
    //    if (equip_data->m_nAttributePoolID[i] && g_Random(RATE_MAX) < equip_data->m_nAttributePoolChance[i])
    //    {
    //        INT32 random_number;
    //        const ATTRIBUTE_POOL* pool = CAttributePoolDataManager::GetInstance().GetPool(equip_data->m_nAttributePoolID[i]);
    //        LOG_PROCESS_ERROR(pool);
    //
    //        random_number = g_Random(pool->m_nTotalWeight);
    //
    //        for (INT32 j = 0; j < pool->m_nDataCount; j++)
    //        {
    //            if (random_number < pool->m_PoolData[j].m_nWeight)
    //            {
    //                item->m_iteminfo.m_wRandomAttrID[attr_count++] = g_Random(pool->m_PoolData[j].m_nAttributeIDMin, pool->m_PoolData[j].m_nAttributeIDMax + 1);
    //                break;
    //            }
    //            else
    //            {
    //                random_number -= pool->m_PoolData[j].m_nWeight;
    //            }
    //        }
    //    }
    //}

Exit0:
    return;
}

void CItemMgr::GenerateRandomSockets(Item* item, INT32 modifyrate/* = RATE_MAX*/)
{
    const EQUIP_DATA* equip_data = (const EQUIP_DATA*)item->m_pTemplate;
    INT32 final_chance = (INT32)((INT64)equip_data->m_nSocketChance * modifyrate / RATE_MAX);
    if (final_chance > RATE_MAX)
        final_chance = RATE_MAX;

    _GenerateSockets(item->m_iteminfo, final_chance, equip_data->m_bySocketCountMin, equip_data->m_bySocketCountMax, equip_data->m_nColorSocketRate);
}

BOOL CItemMgr::RegisterRuneData(const RUNE_DATA* data)
{
    LOG_PROCESS_ERROR(data);

    if (data->nRuneID)
    {
        LOG_PROCESS_ERROR(data->dwWeight > 0);
        //LOG_PROCESS_ERROR(data->dwWeight <= 1000000);
        LOG_PROCESS_ERROR(data->dwWeight[0][0] <= 1000000);    // 暂时固定使用 下标[0][0]
        LOG_PROCESS_ERROR(CSpellConfig::GetInstance().FindSpellTemplate(data->nSpellID, 0, 0));
        LOG_PROCESS_ERROR(data->nClass >= clsPlayerBegin && data->nClass < clsPlayerEnd);

        m_vec_rune_data[data->nClass].push_back(data);
    }

    return TRUE;

Exit0:
    return FALSE;
}

// 普通铭文洗练
INT32 CItemMgr::GenerateRandomRuneData(INT32 nServerGroup, Item* item, INT32 cls, INT32 level, INT32 runegroup)
{
    UINT16* p_this_random_rune_id = NULL;  // 当前要洗练的铭文
    UINT16* p_another_rune_id = NULL;      // 另一个要保留的铭文
    const RUNE_DATA* another_rune_data = NULL;
    const EQUIP_DATA* equip_data = NULL;

    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);

    equip_data = (const EQUIP_DATA*)item->m_pTemplate;

    // 默认代码
    {
        // 随机洗哪个卡槽, 判断 开启第二卡槽是否有数值, 并且当前消费数量 是否已经大于 m_dwSecondRuneCost, 都是判断 1200 次
        //if (item->m_iteminfo.m_wRune[1] || (item->m_iteminfo.m_dwCostMoney >= equip_data->m_dwSecondRuneCostMax))
        //{
        //    if (g_Random(2) == 0)
        //    {
        //        p_this_random_rune_id = &item->m_iteminfo.m_wRune[0];  // 指针
        //        p_another_rune_id = &item->m_iteminfo.m_wRune[1];
        //        another_rune_data = CDataManager<RUNE_DATA>::GetInstance().GetData(*p_another_rune_id);
        //    }
        //    else
        //    {
        //        p_this_random_rune_id = &item->m_iteminfo.m_wRune[1];
        //        p_another_rune_id = &item->m_iteminfo.m_wRune[0];
        //        another_rune_data = CDataManager<RUNE_DATA>::GetInstance().GetData(*p_another_rune_id);
        //    }
        //}
        //else
        //{
        //    p_this_random_rune_id = &item->m_iteminfo.m_wRune[0];
        //}
    }

    // 自己改的代码
    {
        // 有卡槽1, 有卡槽2, 同时满足开双卡槽条件, 洗[卡槽1]
        if (item->m_iteminfo.m_wRune[0] > 0 &&                                    // 有卡槽1
            item->m_iteminfo.m_wRune[1] > 0 &&                                    // 有卡槽2
            equip_data->m_dwSecondRuneCostMax > 0 &&                              // 开启卡槽2有条件
            item->m_iteminfo.m_dwCostMoney >= equip_data->m_dwSecondRuneCostMax)  // 满足开双卡槽条件
        {
            p_this_random_rune_id = &item->m_iteminfo.m_wRune[0];  // 指针
            p_another_rune_id = &item->m_iteminfo.m_wRune[1];
            another_rune_data = CDataManager<RUNE_DATA>::GetInstance().GetData(*p_another_rune_id);
        }
        // 有卡槽1, 同时满足开双卡槽条件, 洗[卡槽2]
        else if (item->m_iteminfo.m_wRune[0] > 0 &&                               // 有卡槽1
            equip_data->m_dwSecondRuneCostMax > 0 &&                              // 开启卡槽2有条件
            item->m_iteminfo.m_dwCostMoney >= equip_data->m_dwSecondRuneCostMax)  // 满足开双卡槽条件
        {
            p_this_random_rune_id = &item->m_iteminfo.m_wRune[1];  // 指针
            p_another_rune_id = &item->m_iteminfo.m_wRune[0];
            another_rune_data = CDataManager<RUNE_DATA>::GetInstance().GetData(*p_another_rune_id);
        }
        // 没有铭文, 洗[卡槽1]
        else
        {
            p_this_random_rune_id = &item->m_iteminfo.m_wRune[0];
        }
    }


    // 循环10次
    for (INT32 loop_times = 0; loop_times < 10; loop_times++)
    {
        // 生成一个对应职业的铭文
        UINT16 temp_rune_id = _GenerateRuneID(cls, level, runegroup);
        LOG_PROCESS_ERROR(temp_rune_id);

        // 获取铭文模板
        const RUNE_DATA* temp_rune_data = CDataManager<RUNE_DATA>::GetInstance().GetData(temp_rune_id);
        LOG_PROCESS_ERROR(temp_rune_data);

        // 查询铭文洗练限制
        INT32 rune_count = CGameWorld::GetInstance().GetServerVariable(nServerGroup, MakeServerKey(esvtRune, temp_rune_id));
        if (temp_rune_data->nDropLimitCount && rune_count >= temp_rune_data->nDropLimitCount)
        {
            INF("Rune Limit Exceeded: ServerGroup:%d, RuneID:%d, CurRuneCount:%d", nServerGroup, temp_rune_id, rune_count);
            continue;
        }

        if (another_rune_data == NULL ||
            (temp_rune_data->nSpellID != another_rune_data->nSpellID))
        {
            *p_this_random_rune_id = temp_rune_id;  // 赋值, 修改卡槽里的铭文
            return temp_rune_id;
        }
    }

    LOG_PROCESS_ERROR(FALSE);

Exit0:
    return 0;
}

INT32 CItemMgr::GenerateRandomRuneDataAdvanced(INT32 nServerGroup, Item* item, INT32 cls, INT32 level, INT32 runegroup)
{
    UINT16* p_another_rune_id = NULL;      // 另一个要保留的铭文
    const RUNE_DATA* another_rune_data = NULL;
    const EQUIP_DATA* equip_data = NULL;

    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);

    equip_data = (const EQUIP_DATA*)item->m_pTemplate;

    // 判断, 当前装备是否开启第二卡槽
    if (item->m_iteminfo.m_wRune[1] > 0 || 
        item->m_iteminfo.m_dwCostMoney >= equip_data->m_dwSecondRuneCostMax)
    {
        // 固定洗第二卡槽, 获取第一卡槽的铭文信息
        p_another_rune_id = &item->m_iteminfo.m_wRune[0];
        another_rune_data = CDataManager<RUNE_DATA>::GetInstance().GetData(*p_another_rune_id);
    }
    else
    {
        return 0;  // 按理说没开2个卡槽的武器, 客户端不让发包的, 强行发包肯定是调Call了
    }

    // 循环10次
    for (INT32 loop_times = 0; loop_times < 10; loop_times++)
    {
        // 生成一个对应职业的铭文
        UINT16 temp_rune_id = _GenerateRuneID(cls, level, runegroup);
        LOG_PROCESS_ERROR(temp_rune_id);

        // 获取铭文模板
        const RUNE_DATA* temp_rune_data = CDataManager<RUNE_DATA>::GetInstance().GetData(temp_rune_id);
        LOG_PROCESS_ERROR(temp_rune_data);

        // 查询铭文洗练限制
        INT32 rune_count = CGameWorld::GetInstance().GetServerVariable(nServerGroup, MakeServerKey(esvtRune, temp_rune_id));
        if (temp_rune_data->nDropLimitCount && rune_count >= temp_rune_data->nDropLimitCount)
        {
            INF("Rune Limit Exceeded: ServerGroup:%d, RuneID:%d, CurRuneCount:%d", nServerGroup, temp_rune_id, rune_count);
            continue;
        }

        if (another_rune_data == NULL ||
            (temp_rune_data->nSpellID != another_rune_data->nSpellID))
        {
            return temp_rune_id;  // // 高级洗练, 先不修改铭文数据, 只把结果返回
        }
    }

    LOG_PROCESS_ERROR(FALSE);

Exit0:
    return 0;
}

// 参数 (职业, Vip等级, 铭文分组)
UINT16 CItemMgr::_GenerateRuneID(INT32 cls, INT32 level, INT32 runegroup)
{
    UINT32 random_number;
    UINT32 weight = 0;
    std::vector<const RUNE_DATA*> temp_vec_rune_data;

    LOG_PROCESS_ERROR(cls >= 0 && cls <clsPlayerTotal);

    // 根据职业, 计算权重总和
    for (std::vector<const RUNE_DATA*>::iterator it = m_vec_rune_data[cls].begin(); it != m_vec_rune_data[cls].end(); ++it)
    {
        const RUNE_DATA* data = *it;
        if (level >= data->nLevel && runegroup >= data->nGroup)
        {
            temp_vec_rune_data.push_back(data);
            //weight += data->dwWeight;
            weight += data->dwWeight[0][0];    // 暂时固定使用 下标[0][0]
        }
    }
    LOG_PROCESS_ERROR(!temp_vec_rune_data.empty());

    // 随机权重数值
    random_number = g_Random(weight);

    // 权重算法
    for (INT32 i = 0; i < temp_vec_rune_data.size(); i++)
    {
        //if (random_number < temp_vec_rune_data[i]->dwWeight)
        if (random_number < temp_vec_rune_data[i]->dwWeight[0][0])    // 暂时固定使用 下标[0][0]
            return (UINT16)temp_vec_rune_data[i]->nRuneID;

        //random_number -= temp_vec_rune_data[i]->dwWeight;
        random_number -= temp_vec_rune_data[i]->dwWeight[0][0];    // 暂时固定使用 下标[0][0]
    }

    LOG_PROCESS_ERROR(FALSE);

Exit0:
    return 0;
}


// ========== 下面全是自己新增加的代码 begin

// 判断装备是不是运2项链装备
BOOL CItemMgr::CheckEquipIsLuck2Item(INT32 itemID)
{
    for (const auto id : g_ServerConfig.CC.nLuck2NecklaceItemID)
    {
        if (id == itemID)
        {
            return TRUE;
        }
    }
    return FALSE;
}

// 自己新加函数, 专门用于运2
Item* CItemMgr::GenerateItem(INT32 nServerGroup, const ITEM_DATA* itemdata, INT32 nItemCount, BOOL bRandomDur)
{
    Item* item = NULL;
    UINT64 guid = 0;
    LOG_PROCESS_ERROR(itemdata);
    LOG_PROCESS_ERROR(itemdata->m_nTemplateID >= 99);

    guid = CreateItemGuid();
    item = CGameWorld::GetInstance().NewItem(guid);
    LOG_PROCESS_ERROR(item);

    item->m_pTemplate = itemdata;
    item->m_bAttrEffective = FALSE;
    memset(&item->m_iteminfo, 0, sizeof(ItemInfo));

    item->m_iteminfo.m_llGuid = guid;
    item->m_iteminfo.m_nTemplateID = itemdata->m_nTemplateID;
    item->m_iteminfo.m_nMaxDur = itemdata->m_nDur;
    switch (itemdata->m_byDurType)
    {
        case DURTYPE_STACK:
            if (nItemCount > itemdata->m_nDur)
                item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
            else
                item->m_iteminfo.m_nCurDur = nItemCount;
            break;
        case DURTYPE_EQUIP:
            if (bRandomDur)
            {
                item->m_iteminfo.m_nMaxDur = itemdata->m_nDur * g_Random(EQUIP_MAX_DUR_RANDOM_MIN, EQUIP_MAX_DUR_RANDOM_MAX) / RATE_MAX;
                item->m_iteminfo.m_nCurDur = item->m_iteminfo.m_nMaxDur * g_Random(EQUIP_MAX_DUR_RANDOM_MIN, RATE_MAX) / RATE_MAX;
            }
            else
            {
                item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
                item->m_iteminfo.m_nMaxDur = itemdata->m_nDur;
            }
            break;
        case DURTYPE_USE:
            item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
            break;
        case DURTYPE_DEPOSIT:
            item->m_iteminfo.m_nCurDur = 0;
            break;
        case DURTYPE_RECOVER:
            item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
            item->m_iteminfo.m_nMaxDur = itemdata->m_nDur;
            break;
        case DURTYPE_PURITY:
            item->m_iteminfo.m_nCurDur = itemdata->m_nDur;
            item->m_iteminfo.m_nMaxDur = itemdata->m_nDur;
            break;
        case DURTYPE_NONE:
            item->m_iteminfo.m_nCurDur = 1;
            break;
        default:
            LOG_PROCESS_ERROR(FALSE);
    }
    item->m_iteminfo.m_byBindType = itemdata->m_byBindType;

    // 生成 随机属性/孔位
    if (itemdata->m_byType == ITEMTYPE_EQUIP)
    {
        const EQUIP_DATA* equipdata = (const EQUIP_DATA*)itemdata;

        item->m_iteminfo.m_byIdentified = equipdata->m_byIdentified;

        if (equipdata->m_byIdentified)
        {
            GenerateRandomAttributes(item, RATE_MAX, nServerGroup);
        }
    }

    return item;

Exit0:
    if (itemdata)
        CRI("failed to generate item %d count %d", itemdata->m_nTemplateID, nItemCount);

    if (item)
        CGameWorld::GetInstance().DelItem(item);

    return NULL;
}

// ========== 下面全是自己新增加的代码 end
