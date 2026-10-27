#include "stdafx.h"
#include "item_bag.h"

#include "server_config.h"

#include "item_mgr.h"
#include "message_handler.h"
#include "robot_message_handler.h"
#include "role.h"
#include "spell_config.h"
#include "spell.h"
#include "gameworld/game_world.h"
#include "refine_data.h"
#include "set_data.h"
#include "script_mgr.h"
#include "statistic.h"
#include "soul_data.h"
#include "rune_data.h"
#include "decompose_data.h"
#include "compose_data.h"
#include "drop_generator.h"
#include "game_world_config.h"
#include <algorithm>
#include "attribute_data.h"
#include "pk_drop_count_data.h"
#include "pk_drop_rate_data.h"
#include "adventure.h"
#include "modifier_tree.h"
#include "level_data.h"
#include "money_data.h"
#include "activity_reward_data.h"
#include "scene_data.h"
#include <functional>
#include "mail_template_data.h"
#include "character.h"
#include "black_market_data.h"
#include "gamble_data.h"

//////////////////////////////////////////////////////////////////////////
//public:

template <typename T>
T _Min(T t1, T t2)
{
    return t1 < t2 ? t1 : t2;
}

CItemBag::CItemBag()
{
    m_randomize_item = NULL;
    m_WeaponItem = NULL;
    m_pOwner = NULL;
    m_pWeaponAura = NULL;
    m_pArmorAura = NULL;
    m_pBagAura = NULL;
    Clear();
}

void CItemBag::Clear()
{
    memset(m_refine_levels, 0, sizeof(m_refine_levels));

    for (INT32 i = 0; i < CONSLOT_COUNT; i++)
    {
        m_con_sizes[i] = INIT_CONTAINER_SIZE[i];
    }

    for (UINT16 i = 0; i < CONSLOT_COUNT; i++)
    {
        Container& container = m_cons[i];
        for (ConIt it = container.begin(); it != container.end(); ++it)
        {
            BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(it->second);
            LOG_CHECK_ERROR(bItemRet);
        }
        container.clear();
    }

    for (INT32 i = 0; i < MONEYTYPE_COUNT; i++)
    {
        m_moneys[i] = 0;
        m_moneys_limit[i] = MAX_MONEY;
        m_moneys_daily_earned[i] = 0;
        m_moneys_daily_earned_limit[i] = 0;
        m_moneys_daily_used[i] = 0;
        m_moneys_daily_used_limit[i] = 0;
        m_moneys_weekly_earned[i] = 0;
        m_moneys_weekly_earned_limit[i] = 0;
        m_moneys_weekly_used[i] = 0;
        m_moneys_weekly_used_limit[i] = 0;
    }
    m_use_moneytype01_only = 1;
    m_gold_pool = 1000;

    for (std::list<Item*>::iterator it = m_soldlist.begin(); it != m_soldlist.end(); ++it)
    {
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(*it);
        LOG_CHECK_ERROR(bItemRet);
    }
    m_soldlist.clear();

    m_dwLastOrganizeTime = 0;

    _ClearRandomizeItem();

    m_dwFirstDeathTime = 0;
    m_dwDeathCountFromFirst = 0;
    m_dwLastDeathTime = 0;

    if (m_WeaponItem)
    {
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(m_WeaponItem);
        LOG_CHECK_ERROR(bItemRet);
        m_WeaponItem = NULL;
    }
    m_dwWeaponLevelUpStartTime = 0;
    m_nWeaponDur = 0;
    m_nWeaponPhy = 0;
    m_nWeaponMag = 0;
    m_nWeaponTao = 0;
    m_byMailNotified = 0;

    m_pWeaponAura = NULL;
    m_pArmorAura = NULL;
    m_pBagAura = NULL;

    m_black_market_limit_map.clear();
    m_black_market_cooldown_map.clear();

    m_nExpBottleTimes = 0;
}

void CItemBag::SetOwner(CRole* role)
{
    m_pOwner = role;
}

CRole* CItemBag::GetOwner()
{
    return m_pOwner;
}

BOOL CItemBag::MainLoop()
{
    BOOL check_hp = FALSE;
    BOOL check_mp = FALSE;
    BOOL item_change = FALSE;

    // 获取战具对象指针
    Item* item = GetItem(CONSLOT_RECOVER, 0);
    if (item)
    {
        LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_RECOVER);

        if (item->m_pTemplate->m_bySubType == ITEMSUBTYPE_RECOVER_HP)
        {
            check_hp = TRUE;
        }
        else if (item->m_pTemplate->m_bySubType == ITEMSUBTYPE_RECOVER_MP)
        {
            check_mp = TRUE;
        }
        else if (item->m_pTemplate->m_bySubType == ITEMSUBTYPE_RECOVER_HPMP)
        {
            check_hp = TRUE;
            check_mp = TRUE;
        }
        else
            LOG_PROCESS_ERROR(FALSE);

        if (check_hp)
        {
            INT32 maxhp = m_pOwner->GetAttr(catMaxHp);
            INT32 curhp = m_pOwner->GetHp();

            if (maxhp - curhp >= AUTO_RECOVER_HP_MIN_DIFF)
            {
                INT32 recover_point = AUTO_RECOVER_HP_POINT;
                LOG_PROCESS_ERROR(item->m_iteminfo.m_nCurDur > 0);

                if (recover_point > item->m_iteminfo.m_nCurDur)
                    recover_point = item->m_iteminfo.m_nCurDur;

                m_pOwner->ChangeHp(recover_point, 0);

                item->m_iteminfo.m_nCurDur -= recover_point;
                if (item->m_iteminfo.m_nCurDur > 0)
                {
                    item_change = TRUE;
                }
                else
                {
                    DeleteItemPos(CONSLOT_RECOVER, 0, 1, ITEMLOG_RECOVER_USED_UP, 0);
                }
            }
        }

        if (check_mp)
        {
            INT32 maxmp = m_pOwner->GetAttr(catMaxMp);
            INT32 curmp = m_pOwner->GetMp();

            if (maxmp - curmp >= AUTO_RECOVER_MP_MIN_DIFF)
            {
                INT32 recover_point = AUTO_RECOVER_MP_POINT;
                LOG_PROCESS_ERROR(item->m_iteminfo.m_nCurDur > 0);

                if (recover_point > item->m_iteminfo.m_nCurDur)
                    recover_point = item->m_iteminfo.m_nCurDur;

                m_pOwner->ChangeMp(recover_point);

                item->m_iteminfo.m_nCurDur -= recover_point;
                if (item->m_iteminfo.m_nCurDur > 0)
                {
                    item_change = TRUE;
                }
                else
                {
                    DeleteItemPos(CONSLOT_RECOVER, 0, 1, ITEMLOG_RECOVER_USED_UP, 0);
                }
            }
        }

        if (item_change)
        {
#ifndef _ROBOT
            BOOL bRet = CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);
            LOG_CHECK_ERROR(bRet);
#endif
        }
    }

    // 判断 是否有武器正在升级中
    if (m_WeaponItem && !m_byMailNotified &&
        CGameWorld::GetInstance().GetGameTime() - m_dwWeaponLevelUpStartTime >= WEAPON_LEVEL_UP_TIME)
    {
        m_pOwner->SendMail(m_pOwner->GetObjID(), mtiWeaponLevelUpFinish);
        m_byMailNotified = 1;
    }

    return TRUE;

Exit0:
    return FALSE;
}

void CItemBag::UpdateMoneyLimits()
{
    const ROLE_LEVEL_DATA* level_data = CDataManager<ROLE_LEVEL_DATA>::GetInstance().GetData(m_pOwner->GetLevel());
    LOG_PROCESS_ERROR(level_data);

    for (INT32 i = MONEYTYPE_01; i < MONEYTYPE_COUNT; i++)
    {
        const MONEY_DATA* money_data = CDataManager<MONEY_DATA>::GetInstance().GetData(i);
        LOG_CHECK_ERROR(money_data);

        if (money_data)
        {
            if (money_data->m_nTotalLimit > 0)
                m_moneys_limit[i] = money_data->m_nTotalLimit;
            else
                m_moneys_limit[i] = MAX_MONEY;

            m_moneys_daily_earned_limit[i] = money_data->m_nDailyEarnLimit;
            m_moneys_daily_used_limit[i] = money_data->m_nDailyUseLimit;
            m_moneys_weekly_earned_limit[i] = money_data->m_nWeeklyEarnLimit;
            m_moneys_weekly_used_limit[i] = money_data->m_nWeeklyUseLimit;
        }
        else
        {
            m_moneys_limit[i] = MAX_MONEY;
            m_moneys_daily_earned_limit[i] = 0;
            m_moneys_daily_used_limit[i] = 0;
            m_moneys_weekly_earned_limit[i] = 0;
            m_moneys_weekly_used_limit[i] = 0;
        }
    }

    UpdateMoneytype01DailyUsedLimit();

    m_moneys_daily_earned_limit[MONEYTYPE_02] = level_data->m_nMoneyType02DailyEarnLimit;

    m_moneys_limit[MONEYTYPE_BF] = level_data->m_nMoneyTypeBFTotalLimit;
    m_moneys_weekly_earned_limit[MONEYTYPE_BF] = level_data->m_nMoneyTypeBFWeeklyEarnLimit;

    m_moneys_limit[MONEYTYPE_ARENA] = level_data->m_nMoneyTypeArenaTotalLimit;
    m_moneys_weekly_earned_limit[MONEYTYPE_ARENA] = level_data->m_nMoneyTypeArenaWeeklyEarnLimit;

    for (INT32 i = MONEYTYPE_01; i < MONEYTYPE_COUNT; i++)
    {
        if (m_moneys_limit[i] == 0)
            m_moneys_limit[i] = MAX_MONEY;
    }

Exit0:
    return;
}

void CItemBag::UpdateMoneytype01DailyUsedLimit()
{
    INT64 level_basic, activity_reward_percent, vip_percent;

    const ACTIVITY_REWARD_DATA* reward_data = NULL;
    const ROLE_LEVEL_DATA* level_data = CDataManager<ROLE_LEVEL_DATA>::GetInstance().GetData(m_pOwner->GetLevel());

    for (INT32 nIndex = 31; nIndex >= 0; nIndex--)
    {
        reward_data = CDataManager<ACTIVITY_REWARD_DATA>::GetInstance().GetData(nIndex);
        if (reward_data && reward_data->nActivityValue <= m_pOwner->GetActivity())
        {
            break;
        }
    }

    LOG_PROCESS_ERROR(level_data);
    LOG_PROCESS_ERROR(reward_data);

    level_basic = level_data->m_nMoneyType01DailyUseLimit;
    activity_reward_percent = reward_data->nMoneytype01DailyUseLimit * 100;
    vip_percent = g_GWConfig.VIPData[m_pOwner->GetVIPLevel()].nDailyUseMoneyType01Percent;

    m_moneys_daily_used_limit[MONEYTYPE_01] = (INT32)(level_basic * (RATE_MAX + activity_reward_percent + vip_percent) / RATE_MAX);

Exit0:
    return;
}

void CItemBag::UpdateDaily()
{
    memset(m_moneys_daily_earned, 0, sizeof(m_moneys_daily_earned));
    memset(m_moneys_daily_used, 0, sizeof(m_moneys_daily_used));
    m_nExpBottleTimes = 0;
}

void CItemBag::UpdateWeekly()
{
    memset(m_moneys_weekly_earned, 0, sizeof(m_moneys_weekly_earned));
    memset(m_moneys_weekly_used, 0, sizeof(m_moneys_weekly_used));
}

void CItemBag::GetRefineLevels(UINT16 levels[])
{
    memcpy(levels, m_refine_levels, sizeof(m_refine_levels));
}

void CItemBag::GetContainerSizes(UINT8 sizes[])
{
    memcpy(sizes, m_con_sizes, sizeof(m_con_sizes));
}

void CItemBag::Begin()
{
    m_allitem.clear();
    for (INT32 i = 0; i < CONSLOT_COUNT; i++)
    {
        const Container& con = m_cons[i];
        for (Container::const_iterator it = con.begin(); it != con.end(); ++it)
        {
            m_allitem.push_back(it->second);
        }
    }
}

const Item* CItemBag::Next()
{
    if (m_allitem.empty())
        return NULL;

    const Item* item = m_allitem.front();
    m_allitem.pop_front();
    return item;
}

void CItemBag::Begin(UINT8 conslot)
{
    m_allitem.clear();
    LOG_PROCESS_ERROR(conslot >= 0 && conslot < CONSLOT_COUNT);

    for (Container::const_iterator it = m_cons[conslot].begin(); it != m_cons[conslot].end(); ++it)
    {
        m_allitem.push_back(it->second);
    }

    return;
Exit0:
    return;
}

const Item* CItemBag::Next(UINT8 conslot)
{
    LOG_PROCESS_ERROR(conslot >= 0 && conslot < CONSLOT_COUNT);

    if (m_allitem.empty())
        return NULL;

    const Item* item = m_allitem.front();
    m_allitem.pop_front();
    return item;
Exit0:
    return NULL;
}

INT32 CItemBag::AddItem(Item* item, EItemLog reason, UINT64 userdefine)
{
    INT32 nResult = errItemUnknown;

    LOG_PROCESS_ERROR_RET_CODE(item, errItemUnknown);
    LOG_PROCESS_ERROR_RET_CODE(item->m_pTemplate, errItemUnknown);

    return AddItemToContainer(item, CONSLOT_DEFAULT, reason, userdefine);

Exit0:
    return nResult;
}

INT32 CItemBag::AddItem(INT32 itemid, INT32 itemcount, EItemLog reason, UINT64 userdefine, BOOL forcebinded)
{
    INT32 nResult = errItemUnknown;

    Item* item = CItemMgr::GetInstance().GenerateItem(itemid, itemcount);
    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(item->m_pTemplate);

    // 商店货不给随机属性
    if (reason == ITEMLOG_SHOP && item->m_pTemplate->m_byType == ITEMTYPE_EQUIP)
    {
        for (INT32 i = 0; i < MAX_RANDOM_ATTR_COUNT; i++)
        {
            item->m_iteminfo.m_wRandomAttrID[i] = 0;
        }
    }

    if (forcebinded)
        item->m_iteminfo.m_byBindType = BINDTYPE_BINDED;

    nResult = AddItem(item, reason, userdefine);
    if (nResult != errSuccess)
    {
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
        LOG_CHECK_ERROR(bItemRet);
    }

Exit0:
    return nResult;
}

INT32 CItemBag::AddItemToDefaultCon(Item* item, UINT8 conslot, UINT8 itemslot, EItemLog reason)
{
    INT32   nResult = errItemUnknown;
    BOOL    delete_item = FALSE;
    Item* pOldItem = NULL;

    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(CONSLOT_DEFAULT == conslot, errItemInvalidPos);

    pOldItem = GetItem(conslot, itemslot);
    LOG_PROCESS_ERROR_RET_CODE(pOldItem == NULL, errItemInvalidPos);

    m_cons[conslot].insert(Container::value_type(itemslot, item));
    item->SetPos(conslot, itemslot);
#ifndef _ROBOT
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);

    if (item->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLLogItem(
            m_pOwner->GetObjID(),
            m_pOwner->GetServerGroup(),
            item->m_iteminfo.m_llGuid,
            item->m_pTemplate->m_nTemplateID,
            item->m_pTemplate->m_byDurType == DURTYPE_STACK ? item->m_iteminfo.m_nCurDur : 1,
            reason,
            ITEMACTION_INC,
            0);
    }

    if (item->m_pTemplate->m_byStat)
    {
        CCliMessageHandler::GetInstance().DoDLStatItem(
            m_pOwner->GetServerGroup(),
            item->m_pTemplate->m_nTemplateID,
            item->m_pTemplate->m_byDurType == DURTYPE_STACK ? item->m_iteminfo.m_nCurDur : 1,
            1);
    }
#endif // _ROBOT

    return errSuccess;
Exit0:
    return nResult;
}

INT32 CItemBag::UseItem(UINT8 conslot, UINT8 itemslot)
{
#ifdef _ROBOT
    INT32 nRetCode = CRobotMessageHandler::GetInstance().DoUseItem(m_pOwner, conslot, itemslot);
    LOG_CHECK_ERROR(nRetCode);
    return errSuccess;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    ConIt it;
    Item* item = NULL;

    LOG_PROCESS_ERROR(conslot == CONSLOT_DEFAULT);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_DIE, errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    //LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->IsFreeMode(), errFreeMode);    // 默认代码, 放下面判断

    it = m_cons[conslot].find(itemslot);
    if (it == m_cons[conslot].end())
        return errItemNotFound;

    item = it->second;

    // 新增代码 (暂时屏蔽) - 如果开启点卡功能, 当使用点卡道具时, 不判断 m_bFreeMode标志
    //if (g_ServerConfig.MS.bCustomGameTimeCardEnable == TRUE &&
    //    m_pOwner->GetLevel() > g_ServerConfig.MS.nCustomFreeRoleLevel && 
    //    CheckTemplateIDIsTimeCard(item->m_pTemplate->m_nTemplateID) == FALSE)
    //{
    //    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->IsFreeMode(), errFreeMode);
    //}

    if (!_Satisfied(m_pOwner, item))
        return errItemUnsatisfied;

    if (item->m_pTemplate->m_nSelfCoolDown > 0 &&
        !m_pOwner->GetCoolDown().CheckReady(MakeCoolDownID(COOLDOWN_ITEM, item->m_pTemplate->m_nTemplateID)))
        return errItemNotReady;

    if (item->m_pTemplate->m_nCdGrpCount > 0)
    {
        for (INT32 i = 0; i < item->m_pTemplate->m_nCdGrpCount; i++)
        {
            if (!m_pOwner->GetCoolDown().CheckReady(MakeCoolDownID(COOLDOWN_GROUP, item->m_pTemplate->m_CdGrp[i].m_nCdGrpID)))
                return errItemNotReady;
        }
    }

    if ((item->m_pTemplate->m_byUseInCombat == ITEMCOMBAT_IN && m_pOwner->GetFlag().CheckFlag(cfInCombat) == FALSE) ||
        (item->m_pTemplate->m_byUseInCombat == ITEMCOMBAT_OUT && m_pOwner->GetFlag().CheckFlag(cfInCombat) == TRUE))
        return errItemWrongCombatState;

    if (m_pOwner->GetScene() && m_pOwner->GetScene()->GetSceneData()->nType == estArena)
    {
        LOG_PROCESS_ERROR_RET_CODE(item->m_pTemplate->m_byUseInArena, errItemCannotUseInArena);
    }

    // 脚本 script
    if ('\0' != item->m_pTemplate->m_szScript[0])
    {
        INT32 nUseItemRtn = errSuccess;
        CLuaScript* poScript = CScriptMgr::GetInstance().FindScript(ITEM_SCRIPT_NAME);
        LOG_PROCESS_ERROR_RET_CODE(poScript, errItemCannotFindScript);

        BOOL bRet = poScript->CallFunction(item->m_pTemplate->m_szScript, "oo:d", item, "Item", m_pOwner, "CRole", &nUseItemRtn);
        LOG_PROCESS_ERROR_RET_CODE(bRet, errItemScriptUseFail);

        if (nUseItemRtn == errSuccess)
        {
            _OnUseItemSuccess(conslot, itemslot, item);
        }
        return nUseItemRtn;
    }

    // 判断类型
    switch (item->m_pTemplate->m_byType)
    {
    case ITEMTYPE_USABLE:
    {
        // 自己新增代码 - 处理新物品
        switch (item->m_pTemplate->m_nTemplateID)
        {
        default:
            break;
        }

        if (item->m_pTemplate->m_nSpellID)
        {
            CSpellTemplate* pSpell = CSpellConfig::GetInstance().FindSpellTemplate(item->m_pTemplate->m_nSpellID, item->m_pTemplate->m_nSpellLevel, 0);
            if (pSpell == NULL)
                return errItemUnknown;
            nResult = m_pOwner->CastInstantSpell(m_pOwner, pSpell, m_pOwner, m_pOwner->GetX(), m_pOwner->GetY(), m_pOwner->GetZ());
            if (nResult == errSuccess)
            {
                _OnUseItemSuccess(conslot, itemslot, item);
            }
            return nResult;
        }
        else
            return errItemUnknown;
        break;
    }
    case ITEMTYPE_SPELLBOOK:
    {
        if (item->m_pTemplate->m_nSpellID)
        {
            nResult = m_pOwner->LearnSpell(item->m_pTemplate->m_nSpellID, item->m_pTemplate->m_nSpellLevel, TRUE);
            if (nResult == errSuccess)
            {
                _OnUseItemSuccess(conslot, itemslot, item);
            }
            return nResult;
        }
        else
            return errItemUnknown;
        break;
    }
    case ITEMTYPE_MATERIAL:
    {
        if (item->m_pTemplate->m_bySubType == ITEMSUBTYPE_MATERIAL_MISC && item->m_pTemplate->m_nDropGroupID)
        {
            BOOL bRet = FALSE;
            INT32 nRetCode = errItemUnknown;

            DropContent content;
            const DROP_GROUP_DATA* drop_group_data = CDropManager::GetInstance().GetData(item->m_pTemplate->m_nDropGroupID);
            LOG_PROCESS_ERROR(drop_group_data);

            bRet = LoseMineDur(USE_MATERIAL_WEAPON_ID);
            PROCESS_ERROR_RET_CODE(bRet, errItemMaterialWeaopn);

            nRetCode = DeleteItemPos(conslot, itemslot, 1, ITEMLOG_MATERIAL, 0);
            PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

            PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);

            bRet = CDropGenerator::GetInstance().GenerateDropContentFromDropGroupData(m_pOwner->GetServerGroup(), drop_group_data, content);
            if (bRet)
            {
                if (content.m_type == DropContent::DROP_MONEY)
                    nRetCode = AddMoney(content.m_money.moneytype, content.m_money.count, MONEYLOG_MATERIAL, 0);
                else if (content.m_type == DropContent::DROP_ITEM)
                {
                    if (content.m_item->m_pTemplate->m_byType == ITEMTYPE_SOUL)
                    {
                        char szBroadcast[1024];
                        const char* pcszFormat = CGameWorld::GetInstance().GetString(essItemMaterial);
                        LOG_CHECK_ERROR(pcszFormat);

                        if (pcszFormat)
                        {
                            snprintf(szBroadcast, 1024, "<#P0:<#PN:%s>><#P1:<#I:%d>><#T:%s>", m_pOwner->GetName(), content.m_item->m_iteminfo.m_nTemplateID, pcszFormat);
                        }
                        else
                        {
                            strxcpy(szBroadcast, "cannot found essItemMaterial", sizeof(szBroadcast));
                        }
                        m_pOwner->Say(cctGroup, cltTvShow, szBroadcast);
                    }
                    nRetCode = AddItem(content.m_item, ITEMLOG_MATERIAL, 0);
                }

                LOG_CHECK_ERROR(nRetCode == errSuccess);
                if (nRetCode != errSuccess)
                    m_pOwner->ErrorCodeNotify(nRetCode, 0, 0);
            }

            return errSuccess;
        }
        else
            return errItemCannotUse;
        break;
    }
    case ITEMTYPE_DEPOSIT:
    {
        if (item->m_iteminfo.m_nCurDur < item->m_iteminfo.m_nMaxDur)
            return errItemNotFull;

        if (item->m_pTemplate->m_bySubType == ITEMSUBTYPE_DEPOSIT_SOUL)
        {
            nResult = AddMoney(MONEYTYPE_SOUL_PTS, item->m_iteminfo.m_nCurDur, MONEYLOG_INVALID, 0);
            if (nResult == errSuccess)
            {
                _OnUseItemSuccess(conslot, itemslot, item);
            }
            return nResult;
        }
        else if (item->m_pTemplate->m_bySubType == ITEMSUBTYPE_DEPOSIT_EXP)
        {
            PROCESS_ERROR_RET_CODE(m_nExpBottleTimes < MAX_TIMES_EXP_BOTTLE_USE, errItemExpBottleMaxTimes);

            m_pOwner->AddExp(item->m_iteminfo.m_nCurDur, FALSE, FALSE);
            _OnUseItemSuccess(conslot, itemslot, item);
            m_nExpBottleTimes++;
            return errSuccess;
        }
        else
            return errItemUnknown;
        break;
    }
    default:
        return errItemCannotUse;
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::MoveItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot)
{
#ifdef _ROBOT
    INT32 nRetCode = CRobotMessageHandler::GetInstance().DoMoveItem(m_pOwner, srcconslot, srcitemslot, dstconslot, dstitemslot);
    LOG_CHECK_ERROR(nRetCode);
    return errSuccess;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    Item* srcitem = NULL;
    Item* dstitem = NULL;

    if ((srcconslot == CONSLOT_BANK || dstconslot == CONSLOT_BANK) && m_pOwner->GetVIPLevel() < vlLevel1)
    {
        CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
        PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

        nResult = m_pOwner->CanInteract(npc);
        PROCESS_ERROR(nResult == errSuccess);

        LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractBank, errNpcNoSuchFunction);
    }

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(srcconslot, srcitemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(dstconslot, dstitemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(!_SrcDstSame(srcconslot, srcitemslot, dstconslot, dstitemslot), errItemInvalidPos);

    srcitem = GetItem(srcconslot, srcitemslot);    // 原始物品
    dstitem = GetItem(dstconslot, dstitemslot);    // 目标物品

    // 判断 - 原始物品 是否为空
    if (srcitem == NULL)
        return errItemNotFound;

    // 判断 - (原始位置 == 主背包 1, 目标位置 == 装备栏 0)
    if (srcconslot == CONSLOT_DEFAULT && dstconslot == CONSLOT_EQUIPPED)
    {
        //Equip
        if (srcitem->m_pTemplate->m_byType != ITEMTYPE_EQUIP)
            return errItemTypeMismatch;
        if (!_Satisfied(m_pOwner, srcitem))
            return errItemUnsatisfied;
        if (!_CorrectSlot(srcitem, dstitemslot))
            return errItemEquipMismatch;
        if (srcitem->m_iteminfo.m_dwRoleID && srcitem->m_iteminfo.m_dwRoleID != m_pOwner->GetObjID())
            return errItemOthersSigned;
        if (dstitemslot == NES_MAIN_HAND && srcitem->GetWeight() > m_pOwner->GetAttr(catWeaponWeightLmt))
            return errItemWeaponTooHeavy;
        if (dstitemslot != NES_MAIN_HAND &&
            _GetArmorWeight() - (dstitem ? dstitem->GetWeight() : 0) + srcitem->GetWeight() > m_pOwner->GetAttr(catArmorWeightLmt))
            return errItemArmorTooHeavy;
        if (dstitem && ((const EQUIP_DATA*)dstitem->m_pTemplate)->m_byCannotUnEquip)
            return errItemCannotUnEquip;

        nResult = _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);

        if (nResult == errSuccess)
        {
            if (dstitem && dstitem->m_iteminfo.m_nCurDur > 0)
                dstitem->OnUnEquip(m_pOwner, m_refine_levels[dstitemslot], m_pOwner->GetClass(), dstitemslot);
            if (srcitem->m_iteminfo.m_nCurDur > 0)
                srcitem->OnEquip(m_pOwner, m_refine_levels[dstitemslot], m_pOwner->GetClass(), dstitemslot);

            if (srcitem->m_iteminfo.m_byBindType == BINDTYPE_BOE)
            {
                srcitem->m_iteminfo.m_byBindType = BINDTYPE_BINDED;
                CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, srcitem);
            }
        }

        return nResult;
    }

    // 判断 - (原始位置 == 装备栏 0, 目标位置 == 主背包 1)
    if (srcconslot == CONSLOT_EQUIPPED && dstconslot == CONSLOT_DEFAULT)
    {
        //UnEquip
        if (dstitem && dstitem->m_pTemplate->m_byType != ITEMTYPE_EQUIP)
            return errItemTypeMismatch;
        if (dstitem && !_Satisfied(m_pOwner, dstitem))
            return errItemUnsatisfied;
        if (dstitem && !_CorrectSlot(dstitem, srcitemslot))
            return errItemEquipMismatch;
        if (dstitem && dstitem->m_iteminfo.m_dwRoleID && dstitem->m_iteminfo.m_dwRoleID != m_pOwner->GetObjID())
            return errItemOthersSigned;
        if (dstitem && srcitemslot == NES_MAIN_HAND && dstitem->GetWeight() > m_pOwner->GetAttr(catWeaponWeightLmt))
            return errItemWeaponTooHeavy;
        if (dstitem && srcitemslot != NES_MAIN_HAND &&
            _GetArmorWeight() - srcitem->GetWeight() + dstitem->GetWeight() > m_pOwner->GetAttr(catArmorWeightLmt))
            return errItemArmorTooHeavy;
        if (((const EQUIP_DATA*)srcitem->m_pTemplate)->m_byCannotUnEquip)
            return errItemCannotUnEquip;

        nResult = _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);

        if (nResult == errSuccess)
        {
            if (srcitem->m_iteminfo.m_nCurDur > 0)
                srcitem->OnUnEquip(m_pOwner, m_refine_levels[srcitemslot], m_pOwner->GetClass(), srcitemslot);
            if (dstitem && dstitem->m_iteminfo.m_nCurDur > 0)
                dstitem->OnEquip(m_pOwner, m_refine_levels[srcitemslot], m_pOwner->GetClass(), srcitemslot);

            if (dstitem && dstitem->m_iteminfo.m_byBindType == BINDTYPE_BOE)
            {
                dstitem->m_iteminfo.m_byBindType = BINDTYPE_BINDED;
                CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, dstitem);
            }
        }

        return nResult;
    }

    // 判断 - (原始位置 == 主背包 1, 目标位置 == 资源包 7)
    if (srcconslot == CONSLOT_DEFAULT && dstconslot == CONSLOT_RESOURCE)
    {
        // 只能放入 [矿石/配方] 物品
        if (srcitem->m_pTemplate->m_byType == ITEMTYPE_MATERIAL || srcitem->m_pTemplate->m_byType == ITEMTYPE_FORMULA)
        {
            return _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);
        }
    }

    // 判断 - (原始位置 == 资源包 7, 目标位置 == 主背包 1)
    if (srcconslot == CONSLOT_RESOURCE && dstconslot == CONSLOT_DEFAULT)
    {
        // 只能取出 [矿石/配方] 物品
        if (srcitem->m_pTemplate->m_byType == ITEMTYPE_MATERIAL || srcitem->m_pTemplate->m_byType == ITEMTYPE_FORMULA)
        {
            return _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);
        }
    }

    // 判断 - (原始位置 == 英雄背包 4 或者 原始位置 == 主背包 1, 目标位置 == 英雄装备栏 3)
    if ((srcconslot == CONSLOT_HERO_EQUIPMENT || srcconslot == CONSLOT_DEFAULT) && dstconslot == CONSLOT_HERO_EQUIPPED)
    {
        CHero* poHero = m_pOwner->GetHero();
        LOG_PROCESS_ERROR_RET_CODE(poHero, errUnknownError);
        //Equip
        if (srcitem->m_pTemplate->m_byType != ITEMTYPE_EQUIP)
            return errItemTypeMismatch;
        if (!_Satisfied(poHero, srcitem))
            return errItemUnsatisfied;
        if (!_CorrectSlot(srcitem, dstitemslot))
            return errItemEquipMismatch;
        if (srcitem->m_iteminfo.m_dwRoleID && srcitem->m_iteminfo.m_dwRoleID != m_pOwner->GetObjID())
            return errItemOthersSigned;

        nResult = _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);

        if (nResult == errSuccess)
        {
            if (dstitem && dstitem->m_iteminfo.m_nCurDur > 0)
                dstitem->OnUnEquip(poHero, 0, 0, 0);
            if (srcitem->m_iteminfo.m_nCurDur > 0)
                srcitem->OnEquip(poHero, 0, 0, 0);

            if (srcitem->m_iteminfo.m_byBindType == BINDTYPE_BOE)
            {
                srcitem->m_iteminfo.m_byBindType = BINDTYPE_BINDED;
                CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, srcitem);
            }
        }

        return nResult;
    }

    // 判断 - (原始位置 == 英雄装备栏 3, 目标位置 == 英雄背包 4 或者 目标位置 == 主背包 1)
    if (srcconslot == CONSLOT_HERO_EQUIPPED && (dstconslot == CONSLOT_HERO_EQUIPMENT || dstconslot == CONSLOT_DEFAULT))
    {
        CHero* poHero = m_pOwner->GetHero();
        LOG_PROCESS_ERROR_RET_CODE(poHero, errUnknownError);

        //UnEquip
        if (dstitem && dstitem->m_pTemplate->m_byType != ITEMTYPE_EQUIP)
            return errItemTypeMismatch;
        if (dstitem && !_Satisfied(poHero, dstitem))
            return errItemUnsatisfied;
        if (dstitem && !_CorrectSlot(dstitem, srcitemslot))
            return errItemEquipMismatch;
        if (dstitem && dstitem->m_iteminfo.m_dwRoleID && dstitem->m_iteminfo.m_dwRoleID != m_pOwner->GetObjID())
            return errItemOthersSigned;

        nResult = _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);

        if (nResult == errSuccess)
        {
            if (srcitem->m_iteminfo.m_nCurDur > 0)
                srcitem->OnUnEquip(poHero, 0, 0, 0);
            if (dstitem && dstitem->m_iteminfo.m_nCurDur > 0)
                dstitem->OnEquip(poHero, 0, 0, 0);

            if (dstitem && dstitem->m_iteminfo.m_byBindType == BINDTYPE_BOE)
            {
                dstitem->m_iteminfo.m_byBindType = BINDTYPE_BINDED;
                CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, dstitem);
            }
        }

        return nResult;
    }

    // 判断 - (原始位置 == 装备栏 0, 目标位置 == 装备栏 0)
    if (srcconslot == CONSLOT_EQUIPPED && dstconslot == CONSLOT_EQUIPPED)
    {
        //Swap Equip
        if (!_CorrectSlot(srcitem, dstitemslot))
            return errItemEquipMismatch;
        if (dstitem && !_CorrectSlot(dstitem, srcitemslot))
            return errItemEquipMismatch;

        return _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);
    }

    // 判断 - (原始位置 == 主背包 1, 目标位置 == 储值栏 5)
    if (srcconslot == CONSLOT_DEFAULT && dstconslot == CONSLOT_DEPOSIT)
    {
        if (!_CorrectDepositSlot(srcitem, dstitemslot))
            return errItemTypeMismatch;

        if (srcitem->m_iteminfo.m_nCurDur >= srcitem->m_iteminfo.m_nMaxDur)
            return errItemFull;

        return _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);
    }

    // 判断 - (原始位置 == 储值栏 5, 目标位置 == 主背包 1)
    if (srcconslot == CONSLOT_DEPOSIT && dstconslot == CONSLOT_DEFAULT)
    {
        if (dstitem && !_CorrectDepositSlot(dstitem, srcitemslot))
            return errItemTypeMismatch;

        if (dstitem && dstitem->m_iteminfo.m_nCurDur >= dstitem->m_iteminfo.m_nMaxDur)
            return errItemFull;

        return _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);
    }

    // 判断 - (原始位置 == 主背包 1, 目标位置 == 自动恢复栏 6)
    if (srcconslot == CONSLOT_DEFAULT && dstconslot == CONSLOT_RECOVER)
    {
        if (srcitem->m_pTemplate->m_byType != ITEMTYPE_RECOVER)
            return errItemTypeMismatch;

        return _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);
    }

    // 判断 - (原始位置 == 自动恢复栏 6, 目标位置 == 主背包 1)
    if (srcconslot == CONSLOT_RECOVER && dstconslot == CONSLOT_DEFAULT)
    {
        if (dstitem && dstitem->m_pTemplate->m_byType != ITEMTYPE_RECOVER)
            return errItemTypeMismatch;

        return _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);
    }

    // 判断 - (原始位置 == 仓库 2, 目标位置 == 主背包 1)
    if (srcconslot == CONSLOT_BANK && dstconslot == CONSLOT_DEFAULT)
    {
        if (_GetBagWeight() + srcitem->GetWeight() - (dstitem ? dstitem->GetWeight() : 0) > m_pOwner->GetAttr(catBagWeightLmt))
            return errItemBagTooHeavy;
    }

    // 判断 - (原始位置 == 主背包 1, 目标位置 == 仓库 2)
    if (srcconslot == CONSLOT_DEFAULT && dstconslot == CONSLOT_BANK &&
        dstitem &&
        !(srcitem->m_pTemplate == dstitem->m_pTemplate && srcitem->m_iteminfo.m_byBindType == dstitem->m_iteminfo.m_byBindType))
    {
        if (_GetBagWeight() - srcitem->GetWeight() + dstitem->GetWeight() > m_pOwner->GetAttr(catBagWeightLmt))
            return errItemBagTooHeavy;
    }

    // 判断 - (目标位置 != 仓库 2, 目标位置 != 主背包 1)
    if (dstconslot != CONSLOT_BANK && dstconslot != CONSLOT_DEFAULT)
        return errItemTypeMismatch;

    // 判断 - (原始位置 != 仓库 2, 原始位置 != 主背包 1)
    if (srcconslot != CONSLOT_BANK && srcconslot != CONSLOT_DEFAULT)
        return errItemTypeMismatch;

    return _MoveItem(srcconslot, srcitemslot, dstconslot, dstitemslot);

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::SplitItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot, INT16 itemcount)
{
#ifdef _ROBOT
    INT32 nRetCode = CRobotMessageHandler::GetInstance().DoSplitItem(m_pOwner, srcconslot, srcitemslot, dstconslot, dstitemslot, itemcount);
    LOG_CHECK_ERROR(nRetCode);
    return errSuccess;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    Item* srcitem = NULL;
    Item* dstitem = NULL;

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    if (m_pOwner->GetTrade()->IsTrading())
    {
        LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTradeItem(srcconslot, srcitemslot), errItemTrading);
        LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTradeItem(dstconslot, dstitemslot), errItemTrading);
    }
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(srcconslot, srcitemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(srcconslot, srcitemslot), errItemInvalidPos);

    srcitem = GetItem(srcconslot, srcitemslot);
    dstitem = GetItem(dstconslot, dstitemslot);

    LOG_PROCESS_ERROR_RET_CODE(srcitem, errItemNotFound);

    if (srcitem->m_pTemplate->m_byDurType != DURTYPE_STACK ||
        itemcount <= 0 || itemcount >= srcitem->m_iteminfo.m_nCurDur)
    {
        return errItemCannotSplit;
    }

    if ((srcconslot != dstconslot) && (srcconslot != CONSLOT_BANK) && (dstconslot != CONSLOT_BANK))
    {
        return errItemTypeMismatch;
    }

    if (dstitem)
    {
        UINT32 real_count = 0;

        //移到已有物品上
        if (srcitem->m_pTemplate != dstitem->m_pTemplate ||
            dstitem->m_iteminfo.m_nCurDur >= dstitem->m_pTemplate->m_nDur)
        {
            return errItemCannotSplit;
        }

        if (dstitem->m_iteminfo.m_nCurDur + itemcount <= dstitem->m_pTemplate->m_nDur)
        {
            real_count = itemcount;
        }
        else
        {
            real_count = dstitem->m_pTemplate->m_nDur - dstitem->m_iteminfo.m_nCurDur;
        }
        srcitem->m_iteminfo.m_nCurDur -= real_count;
        dstitem->m_iteminfo.m_nCurDur += real_count;

        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, srcitem);
        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, dstitem);

        if (srcitem->m_pTemplate->m_byLog)
        {
            CCliMessageHandler::GetInstance().DoDLLogItem(
                m_pOwner->GetObjID(),
                m_pOwner->GetServerGroup(),
                srcitem->m_iteminfo.m_llGuid,
                srcitem->m_pTemplate->m_nTemplateID,
                real_count,
                ITEMLOG_SPLIT,
                ITEMACTION_DEC,
                dstitem->m_iteminfo.m_llGuid);

            CCliMessageHandler::GetInstance().DoDLLogItem(
                m_pOwner->GetObjID(),
                m_pOwner->GetServerGroup(),
                dstitem->m_iteminfo.m_llGuid,
                dstitem->m_pTemplate->m_nTemplateID,
                real_count,
                ITEMLOG_SPLIT,
                ITEMACTION_INC,
                srcitem->m_iteminfo.m_llGuid);
        }
    }
    else
    {
        //移到空处
        Item* newitem = CItemMgr::GetInstance().CopyItem(srcitem);
        LOG_PROCESS_ERROR(newitem);
        srcitem->m_iteminfo.m_nCurDur -= itemcount;
        newitem->m_iteminfo.m_nCurDur = itemcount;
        m_cons[dstconslot].insert(Container::value_type(dstitemslot, newitem));
        newitem->SetPos(dstconslot, dstitemslot);

        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, srcitem);
        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, newitem);

        if (srcitem->m_pTemplate->m_byLog)
        {
            CCliMessageHandler::GetInstance().DoDLLogItem(
                m_pOwner->GetObjID(),
                m_pOwner->GetServerGroup(),
                srcitem->m_iteminfo.m_llGuid,
                srcitem->m_pTemplate->m_nTemplateID,
                itemcount,
                ITEMLOG_SPLIT,
                ITEMACTION_DEC,
                newitem->m_iteminfo.m_llGuid);

            CCliMessageHandler::GetInstance().DoDLLogItem(
                m_pOwner->GetObjID(),
                m_pOwner->GetServerGroup(),
                newitem->m_iteminfo.m_llGuid,
                newitem->m_pTemplate->m_nTemplateID,
                itemcount,
                ITEMLOG_SPLIT,
                ITEMACTION_ADD,
                srcitem->m_iteminfo.m_llGuid);
        }
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

// 丢弃物品
INT32 CItemBag::DeleteItem(UINT8 conslot, UINT8 itemslot, INT16 itemcount)
{
#ifdef _ROBOT
    INT32 nRetCode = CRobotMessageHandler::GetInstance().DoDeleteItem(m_pOwner, conslot, itemslot, itemcount);
    LOG_CHECK_ERROR(nRetCode);
    return errSuccess;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    BOOL bRet = FALSE;
    Item* item = NULL;
    CDrop* drop = NULL;
    DropContent content = { 0 };

    LOG_PROCESS_ERROR(m_pOwner->GetScene());
    LOG_PROCESS_ERROR(m_pOwner->GetGrid());
    PROCESS_ERROR_RET_CODE(!m_pOwner->GetGrid()->bRoleCannotDropItem, errItemCannotDestroy);

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    if (m_pOwner->GetTrade()->IsTrading())
    {
        LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTradeItem(conslot, itemslot), errItemTrading);
    }
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->IsFreeMode(), errFreeMode);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetLevel() >= g_GWConfig.nRoleLowLevel, errRoleLowLevel);

    item = GetItem(conslot, itemslot);
    LOG_PROCESS_ERROR_RET_CODE(item, errItemNotFound);
    PROCESS_ERROR_RET_CODE(item->m_pTemplate->m_byCanDelete, errItemCannotDestroy);

    drop = CGameWorld::GetInstance().NewDrop(0);
    LOG_PROCESS_ERROR(drop);

    content.m_type = DropContent::DROP_ITEM;
    content.m_item = item;

    bRet = drop->Init(CGameWorld::GetInstance().GetDropID(drop), content, CDrop::DS_PLAYER);
    LOG_PROCESS_ERROR(bRet);

    if (item->m_iteminfo.m_byBindType == BINDTYPE_BINDED)
    {
        drop->AddOwner(m_pOwner->GetObjID());
    }

    bRet = m_pOwner->GetScene()->AddDrop(drop, m_pOwner->GetX(), m_pOwner->GetY(), m_pOwner->GetZ(), m_pOwner->GetObjID());
    if (bRet)
    {
        nResult = RemoveItem(conslot, itemslot, ITEMLOG_USER_REQUEST);
        LOG_PROCESS_ERROR(nResult == errSuccess);
    }
    else
    {
        drop->m_content.m_type = DropContent::DROP_INVALID;

        bRet = drop->UnInit();
        LOG_CHECK_ERROR(bRet);

        bRet = CGameWorld::GetInstance().DelDrop(drop);
        LOG_CHECK_ERROR(bRet);

        return errItemDropTooMany;
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::SellItem(UINT8 conslot, UINT8 itemslot, INT32 shoptypesell)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else // _ROBOT

    INT32 nRetCode = 0;
    INT32 nResult = errItemUnknown;
    Item* item = NULL;
    INT32 sellprice = 0;

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);

    item = GetItem(conslot, itemslot);
    LOG_PROCESS_ERROR_RET_CODE(item, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(item->m_pTemplate->m_byCanSell, errItemCannotSell);
    LOG_PROCESS_ERROR_RET_CODE(item->m_iteminfo.m_dwRoleID == 0, errItemAlreadySigned);

    // 屏蔽商店类型, 任何商店都能卖东西
    LOG_PROCESS_ERROR_RET_CODE(item->m_pTemplate->m_nShopTypeSell == 0 || shoptypesell == 0 || item->m_pTemplate->m_nShopTypeSell == shoptypesell, errShopTypeSell);

    sellprice = _GetSellPrice(item);
    LOG_PROCESS_ERROR(sellprice > 0);

    nResult = RemoveItem(conslot, itemslot, ITEMLOG_SELL);
    LOG_PROCESS_ERROR(nResult == errSuccess);

    _AddItemToSoldList(item);

    AddMoney(MONEYTYPE_02, sellprice, MONEYLOG_SELL_ITEM, 0);

    CStatistic::GetInstance().OnAddMoney(m_pOwner, avdSaleMoneyTotal, MONEYTYPE_02, sellprice);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::ViewSoldItems()
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    CCliMessageHandler::GetInstance().DoSendSoldItemList(m_pOwner, m_soldlist);
    return errSuccess;
#endif // _ROBOT
}

INT32 CItemBag::BuyBackItem(UINT8 slot)
{
    Item* item = NULL;
    std::list<Item*>::iterator it = m_soldlist.begin();
    INT32 sellprice = 0;
    INT32 nResult = errItemUnknown;

    LOG_PROCESS_ERROR(slot < MAX_SOLD_ITEMS);
    PROCESS_ERROR(slot < m_soldlist.size());

    std::advance(it, slot);
    item = (*it);
    LOG_PROCESS_ERROR(item);

    sellprice = _GetSellPrice(item);
    LOG_PROCESS_ERROR(sellprice > 0);

    PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= sellprice, errItemNotEnoughMoneytype02);

    nResult = AddItem(item, ITEMLOG_BUY_BACK, 0);
    PROCESS_ERROR(nResult == errSuccess);

    SubMoney(MONEYTYPE_02, sellprice, MONEYLOG_BUY_BACK, 0);
    m_soldlist.erase(it);

    return errSuccess;

Exit0:
    return nResult;
}

INT32 CItemBag::RepairItem(UINT8 conslot, UINT8 itemslot, BOOL bSpecial)
{
#ifdef _ROBOT
    // TODO:
    return errItemUnknown;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    Item* item = GetItem(conslot, itemslot);

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(item, errItemNotFound);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);

    if (item->m_iteminfo.m_nCurDur < item->m_iteminfo.m_nMaxDur)
    {
        const EQUIP_DATA* equip_data = (const EQUIP_DATA*)item->m_pTemplate;
        INT32 repair_cost = 0;
        UINT16 old_cur = item->m_iteminfo.m_nCurDur;

        LOG_PROCESS_ERROR_RET_CODE(equip_data->m_nCanRepair, errItemCannotRepair);
        LOG_PROCESS_ERROR(equip_data->m_nRepairCost > 0);
        LOG_PROCESS_ERROR(equip_data->m_nDur > 0);

        if (bSpecial)
        {
            repair_cost = (INT64)(item->m_iteminfo.m_nMaxDur - item->m_iteminfo.m_nCurDur) * equip_data->m_nSpecialRepairCost / equip_data->m_nDur;
        }
        else
        {
            repair_cost = (INT64)(item->m_iteminfo.m_nMaxDur - item->m_iteminfo.m_nCurDur) * equip_data->m_nRepairCost / equip_data->m_nDur;
        }

        if (repair_cost > 0)
        {
            PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= repair_cost, errItemNotEnoughMoneytype02);

            SubMoney(MONEYTYPE_02, repair_cost, MONEYLOG_REPAIR, 0);

            CStatistic::GetInstance().OnAddMoney(m_pOwner, avdRepairMoneyTotal, MONEYTYPE_02, repair_cost);
            CStatistic::GetInstance().OnCompareMaxValue(m_pOwner, avdRepairMoneyMax, repair_cost);
        }

        if (!bSpecial)
            item->m_iteminfo.m_nMaxDur -= (item->m_iteminfo.m_nMaxDur - item->m_iteminfo.m_nCurDur) / 30;

        item->m_iteminfo.m_nCurDur = item->m_iteminfo.m_nMaxDur;
        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);

        m_pOwner->GetAchievementList().AddVariable(avdItemRepairCount, 1);

        if (conslot == CONSLOT_EQUIPPED && old_cur == 0 && item->m_iteminfo.m_nCurDur > 0)
        {
            item->OnEquip(m_pOwner, m_refine_levels[itemslot], m_pOwner->GetClass(), itemslot);
        }
    }
    else
        return errItemNoNeedRepair;

    CCliMessageHandler::GetInstance().DoSendRepairItem(m_pOwner);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::RepairAllEquippedItem()
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    INT32 total_repair_cost = 0;
    std::list<Item*> to_be_repaired;

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);

    for (ConIt it = m_cons[CONSLOT_EQUIPPED].begin(); it != m_cons[CONSLOT_EQUIPPED].end(); ++it)
    {
        Item* item = it->second;
        if (item->m_iteminfo.m_nCurDur < item->m_iteminfo.m_nMaxDur)
        {
            const EQUIP_DATA* equip_data = (const EQUIP_DATA*)item->m_pTemplate;
            if (equip_data->m_nCanRepair)
            {
                INT32 repair_cost = 0;

                LOG_PROCESS_ERROR(equip_data->m_nRepairCost > 0);
                LOG_PROCESS_ERROR(equip_data->m_nDur > 0);

                repair_cost = (item->m_iteminfo.m_nMaxDur - item->m_iteminfo.m_nCurDur) * equip_data->m_nRepairCost / equip_data->m_nDur;
                total_repair_cost += repair_cost;

                to_be_repaired.push_back(item);
            }
        }
    }

    if (to_be_repaired.empty())
        return errItemNoNeedRepair;

    if (total_repair_cost > 0)
    {
        if (GetMoney(MONEYTYPE_02) < total_repair_cost)
            return errItemNotEnoughMoneytype02;

        SubMoney(MONEYTYPE_02, total_repair_cost, MONEYLOG_REPAIR, 0);

        CStatistic::GetInstance().OnAddMoney(m_pOwner, avdRepairMoneyTotal, MONEYTYPE_02, total_repair_cost);
        CStatistic::GetInstance().OnCompareMaxValue(m_pOwner, avdRepairMoneyMax, total_repair_cost);
    }

    for (std::list<Item*>::iterator it = to_be_repaired.begin(); it != to_be_repaired.end(); ++it)
    {
        Item* item = *it;
        if (item->m_iteminfo.m_nCurDur < item->m_iteminfo.m_nMaxDur)
        {
            UINT16 old_cur = item->m_iteminfo.m_nCurDur;

            item->m_iteminfo.m_nMaxDur -= (item->m_iteminfo.m_nMaxDur - item->m_iteminfo.m_nCurDur) / 30;
            item->m_iteminfo.m_nCurDur = item->m_iteminfo.m_nMaxDur;
            CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);

            m_pOwner->GetAchievementList().AddVariable(avdItemRepairCount, 1);

            if (old_cur == 0 && item->m_iteminfo.m_nCurDur > 0)
            {
                item->OnEquip(m_pOwner, m_refine_levels[item->m_iteminfo.m_byItemSlot], m_pOwner->GetClass(), item->m_iteminfo.m_byItemSlot);
            }
        }
    }

    CCliMessageHandler::GetInstance().DoSendRepairItem(m_pOwner);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

// 鉴定物品?
INT32 CItemBag::IdentifyItem(UINT8 conslot, UINT8 itemslot)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    Item* item = GetItem(conslot, itemslot);
    const EQUIP_DATA* equip_data = NULL;
    INT32 require_money = 0;

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(item, errItemNotFound);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);
    LOG_PROCESS_ERROR_RET_CODE(conslot != CONSLOT_EQUIPPED && conslot != CONSLOT_HERO_EQUIPPED, errItemEquipped);
    LOG_PROCESS_ERROR_RET_CODE(item->m_iteminfo.m_byIdentified == 0, errItemAlreadyIdentified);

    equip_data = (const EQUIP_DATA*)item->m_pTemplate;
    require_money = equip_data->m_nIdentifyCost;

    if (require_money > 0)
    {
        PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= require_money, errItemNotEnoughMoneytype02);
        SubMoney(MONEYTYPE_02, require_money, MONEYLOG_IDENTIFY_ITEM, 0);
    }

    CCliMessageHandler::GetInstance().DoSendIdentifyResult(m_pOwner, errSuccess);
    item->m_iteminfo.m_byIdentified = 1;
    CItemMgr::GetInstance().GenerateRandomAttributes(item);
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);

    if (item->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_IDENTIFY,
            item->m_iteminfo);
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::RandomizeItem(UINT8 conslot, UINT8 itemslot)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    Item* item = GetItem(conslot, itemslot);
    const EQUIP_DATA* equip_data = NULL;
    INT32 require_money = 0;

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(item, errItemNotFound);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);
    LOG_PROCESS_ERROR_RET_CODE(conslot != CONSLOT_EQUIPPED && conslot != CONSLOT_HERO_EQUIPPED, errItemEquipped);
    LOG_PROCESS_ERROR_RET_CODE(item->m_iteminfo.m_byIdentified == 1, errItemNotIdentified);

    equip_data = (const EQUIP_DATA*)item->m_pTemplate;
    require_money = equip_data->m_nIdentifyCost;

    if (require_money > 0)
    {
        PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= require_money, errItemNotEnoughMoneytype02);
        SubMoney(MONEYTYPE_02, require_money, MONEYLOG_RANDOMIZE_ITEM, 0);
    }

    if (m_randomize_item == NULL)
    {
        m_randomize_item = CItemMgr::GetInstance().CopyItem(item);
        LOG_PROCESS_ERROR(m_randomize_item);
    }
    else
    {
        m_randomize_item->m_iteminfo = item->m_iteminfo;
        m_randomize_item->m_pTemplate = item->m_pTemplate;
    }

    CItemMgr::GetInstance().GenerateRandomAttributes(m_randomize_item);
    CCliMessageHandler::GetInstance().DoSendRandomizeItem(m_pOwner, m_randomize_item);

    CAdventure::GetInstance().OnRandomizeEquip(m_pOwner);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::ConfirmRandomizeItem()
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    Item* item = NULL;
    INT32 require_money = 100;//临时性，100块

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR(m_randomize_item);

    item = GetItem(m_randomize_item->m_iteminfo.m_byConSlot, m_randomize_item->m_iteminfo.m_byItemSlot);
    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(item->m_iteminfo.m_llGuid == m_randomize_item->m_iteminfo.m_llGuid);
    LOG_PROCESS_ERROR(item->m_pTemplate == m_randomize_item->m_pTemplate);

    memcpy(item->m_iteminfo.m_wRandomAttrID, m_randomize_item->m_iteminfo.m_wRandomAttrID, sizeof(item->m_iteminfo.m_wRandomAttrID));
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);

    if (item->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_RANDOMIZE,
            item->m_iteminfo);
    }

    _ClearRandomizeItem();

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::Refine(UINT8 refineslot, UINT8 addequip, UINT8 conslot, UINT8 itemslot)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    const REFINE_DATA* refine_data = NULL;
    Item* src_item = NULL;
    INT32 src_item_pow = 0;
    UINT32 refine_success_rate = 0;

    LOG_PROCESS_ERROR(m_pOwner);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR(refineslot < NES_TOTAL);
    LOG_PROCESS_ERROR_RET_CODE(m_refine_levels[refineslot] < MAX_REFINE_LEVEL, errItemMaxRefineLevel);

    if (addequip)
    {
        src_item = GetItem(conslot, itemslot);
        LOG_PROCESS_ERROR_RET_CODE(src_item, errItemNotFound);
        LOG_PROCESS_ERROR(src_item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);
        LOG_PROCESS_ERROR(_CorrectSlot(src_item, refineslot));
        src_item_pow = _GetPow(src_item);
    }

    refine_data = CDataManager<REFINE_DATA>::GetInstance().GetData(m_refine_levels[refineslot] + 1);
    LOG_PROCESS_ERROR(refine_data);
    LOG_PROCESS_ERROR(refine_data->m_nCost > 0);
    LOG_PROCESS_ERROR(refine_data->m_nBasePow > 0);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetSpirit().GetLevel() >= refine_data->m_nRequireLevel, errItemMaxRefineLevel);

    if (GetMoney(MONEYTYPE_01) < refine_data->m_nCost)
        return errItemNotEnoughMoneytype01;

    //删物品删钱
    if (addequip)
    {
        DeleteItemPos(conslot, itemslot, 1, ITEMLOG_REFINE_ITEM, 0);
        src_item = NULL;
    }

    SubMoney(MONEYTYPE_01, refine_data->m_nCost, MONEYLOG_REFINE_ITEM, 0);

    //计算强化成功率
    refine_success_rate = refine_data->m_dwSuccessRate;
    if (addequip)
    {
        refine_success_rate += src_item_pow * 100 / refine_data->m_nBasePow;
    }
    if (g_Random(10000) >= refine_success_rate)
    {
        //失败。。。
        CCliMessageHandler::GetInstance().DoSendRefineResult(m_pOwner, refineslot, 0, m_refine_levels[refineslot]);
        return errSuccess;
    }

    SetRefineLevel(refineslot, m_refine_levels[refineslot] + 1);

    //全服广播
    if (refine_data->m_nBroadCast)
    {
        char szBroadcast[1024];
        const char* pcszFormat = CGameWorld::GetInstance().GetString(essItemRefineSuccess);
        LOG_CHECK_ERROR(pcszFormat);

        if (pcszFormat)
        {
            snprintf(szBroadcast, 1024, "<#P0:<#PN:%s>><#E:%d><#EL:%d><#T:%s>", m_pOwner->GetName(), refineslot, m_refine_levels[refineslot], pcszFormat);
        }
        else
        {
            strxcpy(szBroadcast, "cannot found essItemRefineSuccess", sizeof(szBroadcast));
        }
        m_pOwner->Say(cctGroup, cltTvShow, szBroadcast);
    }

    CAdventure::GetInstance().OnRefineEquip(m_pOwner);

    m_pOwner->GetAchievementList().AddVariable(avdTotalRefineTime, 1);	// 装备强化总次数

    return errSuccess;

Exit0:
    m_pOwner->GetAchievementList().AddVariable(avdRefineFailTime, 1);	// 强化失败次数

    return nResult;

#endif // _ROBOT
}

void CItemBag::SetRefineLevel(UINT8 refineslot, UINT16 level)
{
    Item* equipped_item = GetItem(CONSLOT_EQUIPPED, refineslot);
    UINT16 old_min_level = MAX_REFINE_LEVEL;
    UINT16 cur_min_level = MAX_REFINE_LEVEL;

    if (m_refine_levels[refineslot] == level)
        return;

    //如果强化部位存在已装备的物品，则需要计算新的属性
    if (equipped_item && equipped_item->m_pTemplate->m_byType == ITEMTYPE_EQUIP && equipped_item->m_iteminfo.m_nCurDur > 0 && m_refine_levels[refineslot] > 0)
    {
        const REFINE_ATTR_DATA* refine_attr_data = CDataManager<REFINE_ATTR_DATA>::GetInstance().GetData(REFINE_ATTR_DATA::MakeKey(m_refine_levels[refineslot], m_pOwner->GetClass(), refineslot));
        if (refine_attr_data)
        {
            for (INT32 i = 0; i < refine_attr_data->m_nNodeCount; i++)
                CModifierTree::GetInstance().RollBackExtraNode(refine_attr_data->m_pAttrData[i]->m_nNodeID, m_pOwner, NULL);
        }
    }

    for (INT32 i = 0; i < NES_TOTAL; i++)
    {
        if (m_refine_levels[i] < old_min_level)
            old_min_level = m_refine_levels[i];
    }

    m_refine_levels[refineslot] = level;

    if (equipped_item && equipped_item->m_pTemplate->m_byType == ITEMTYPE_EQUIP && equipped_item->m_iteminfo.m_nCurDur > 0 && m_refine_levels[refineslot] > 0)
    {
        const REFINE_ATTR_DATA* refine_attr_data = CDataManager<REFINE_ATTR_DATA>::GetInstance().GetData(REFINE_ATTR_DATA::MakeKey(m_refine_levels[refineslot], m_pOwner->GetClass(), refineslot));
        if (refine_attr_data)
        {
            for (INT32 i = 0; i < refine_attr_data->m_nNodeCount; i++)
                CModifierTree::GetInstance().ApplyExtraNode(refine_attr_data->m_pAttrData[i]->m_nNodeID, m_pOwner, NULL);
        }
    }

    for (INT32 i = 0; i < NES_TOTAL; i++)
    {
        if (m_refine_levels[i] < cur_min_level)
            cur_min_level = m_refine_levels[i];
    }

    //计算强化激活属性
    if (old_min_level != cur_min_level)
    {
        const REFINE_ATTR_DATA* old_data = CDataManager<REFINE_ATTR_DATA>::GetInstance().GetData(REFINE_ATTR_DATA::MakeKey(old_min_level, m_pOwner->GetClass(), NES_TOTAL));
        const REFINE_ATTR_DATA* cur_data = CDataManager<REFINE_ATTR_DATA>::GetInstance().GetData(REFINE_ATTR_DATA::MakeKey(cur_min_level, m_pOwner->GetClass(), NES_TOTAL));

        if (old_data)
        {
            for (INT32 i = 0; i < old_data->m_nNodeCount; i++)
                CModifierTree::GetInstance().RollBackExtraNode(old_data->m_pAttrData[i]->m_nNodeID, m_pOwner, NULL);
        }

        if (cur_data)
        {
            for (INT32 i = 0; i < cur_data->m_nNodeCount; i++)
                CModifierTree::GetInstance().RollBackExtraNode(cur_data->m_pAttrData[i]->m_nNodeID, m_pOwner, NULL);
        }
    }

#ifndef _ROBOT
    CCliMessageHandler::GetInstance().DoSendRefineResult(m_pOwner, refineslot, 1, m_refine_levels[refineslot]);
#endif // _ROBOT
}

INT32 CItemBag::SignItem(UINT8 conslot, UINT8 itemslot)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else // _ROBOT

    INT32 nResult = errItemUnknown;
    Item* item = GetItem(conslot, itemslot);

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(item, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP, errItemCannotSign);
    LOG_PROCESS_ERROR_RET_CODE(conslot != CONSLOT_EQUIPPED && conslot != CONSLOT_HERO_EQUIPPED, errItemEquipped);
    LOG_PROCESS_ERROR_RET_CODE(item->m_iteminfo.m_dwRoleID == 0, errItemAlreadySigned);
    LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= SIGN_ITEM_COST, errItemNotEnoughMoneytype02);

    SubMoney(MONEYTYPE_02, SIGN_ITEM_COST, MONEYLOG_SIGN_ITEM_COST, 0);

    item->m_iteminfo.m_dwRoleID = m_pOwner->GetObjID();
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);

    if (item->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_SIGN,
            item->m_iteminfo);
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::AuctionSell(UINT8 conslot, UINT8 itemslot, UINT8 byAuctionTimeType, UINT8 byOpen, INT64 llprice, INT64 llbuyoutPrice, INT64 llDepositePrice)
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    INT32 nCurDur = 0;
    INT32 nRetCode = 0;
    INT32 nResult = errItemUnknown;
    UINT32 dwItemInfoSize = 0;
    char szItemInfo[256] = { 0 };
    Item* item = GetItem(conslot, itemslot);

    // 默认代码 判断vip等级
    //if (m_pOwner->GetVIPLevel() < vlLevel3)
    //{
    //	CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    //	PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);
    //
    //	nResult = m_pOwner->CanInteract(npc);
    //	PROCESS_ERROR(nResult == errSuccess);
    //
    //	LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractAuction, errNpcNoSuchFunction);
    //}

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(item, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(item->m_pTemplate->m_bAuction, errItemCannotAuction);
    LOG_PROCESS_ERROR_RET_CODE(item->m_iteminfo.m_byBindType != BINDTYPE_BINDED, errItemBinded);
    LOG_PROCESS_ERROR_RET_CODE(llprice >= item->m_pTemplate->m_nDefaultAuctionPrice, errAuctionSellingPriceLow);
    LOG_PROCESS_ERROR_RET_CODE(byAuctionTimeType < MAX_AUCTION_TIME_INTERVAL_TYPE, errAuctionUnknown);    // 时间类型不对
    LOG_PROCESS_ERROR(item->m_pTemplate->m_nAuctionFee);
    LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= item->m_pTemplate->m_nAuctionFee[byAuctionTimeType], errItemNotEnoughMoneytype02);

    // 扣钱 手续费
    nRetCode = SubMoney(MONEYTYPE_02, item->m_pTemplate->m_nAuctionFee[byAuctionTimeType], MONEYLOG_AUCTION_SELL_COST, 0);
    LOG_PROCESS_ERROR(nRetCode == errSuccess);

    // 删除物品之前, 先保存 item->m_iteminfo 的数据, 在 DeleteItemPos 中, 会销毁 item 指针对象
    dwItemInfoSize = item->m_iteminfo.Save(szItemInfo);

    // 删除物品
    nRetCode = DeleteItemPos(conslot, itemslot,
        item->m_pTemplate->m_byDurType == DURTYPE_STACK ? item->m_iteminfo.m_nCurDur : 1,
        ITEMLOG_AUCTION_SELL, 0);
    LOG_PROCESS_ERROR(nRetCode == errSuccess);

    // 添加玩家变量
    m_pOwner->GetAchievementList().AddVariable(avdAuctionSellCount, 1);

    // 发包给MS
    CCliMessageHandler::GetInstance().DoMSAuctionSell(errSuccess, m_pOwner->GetObjID(), byAuctionTimeType, byOpen, llprice, llbuyoutPrice, llDepositePrice, szItemInfo, dwItemInfoSize);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::AuctionBuy(UINT32 auctionid, INT64 llBidPrice, INT64 llAuctionPrice, INT64 llDepositPrice, UINT8 byBuyType)
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    INT32 nRetCode = 0;
    INT32 nResult = errItemUnknown;

    // 默认代码 判断vip等级
    //if (m_pOwner->GetVIPLevel() < vlLevel3)
    //{
    //	CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    //	PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);
    //
    //	nResult = m_pOwner->CanInteract(npc);
    //	PROCESS_ERROR(nResult == errSuccess);
    //
    //	LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractAuction, errNpcNoSuchFunction);
    //}

    LOG_PROCESS_ERROR(byBuyType > EAuctionBuyType::eabInvalid);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);

    // 无论是 "一口价" 或 "竞拍", 都是只扣保证金
    LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= llDepositPrice, errItemNotEnoughMoneytype02);

    // 扣钱, 保证金
    SubMoney(MONEYTYPE_02, llDepositPrice, MONEYLOG_AUCTION_DEPOSIT_COST, 0);

    // 根据出价类型, 发送的价格变量不一样, 会直接影响 Auction对象 和 客户端显示
    if (byBuyType == EAuctionBuyType::eabtBuyout)
    {
        CCliMessageHandler::GetInstance().DoMSAuctionBuy(errSuccess, m_pOwner->GetObjID(), auctionid, llAuctionPrice);
    }
    else if (byBuyType == EAuctionBuyType::eabtBid)
    {
        CCliMessageHandler::GetInstance().DoMSAuctionBuy(errSuccess, m_pOwner->GetObjID(), auctionid, llBidPrice);
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::AuctionPay(UINT32 auctionid, INT64 llprice)
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    INT32 nRetCode = 0;
    INT32 nResult = errItemUnknown;

    // 默认代码 判断vip等级
    //if (m_pOwner->GetVIPLevel() < vlLevel3)
    //{
    //	CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    //	PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);
    //
    //	nResult = m_pOwner->CanInteract(npc);
    //	PROCESS_ERROR(nResult == errSuccess);
    //
    //	LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractAuction, errNpcNoSuchFunction);
    //}

    //LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    //LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= llprice, errItemNotEnoughMoneytype02);

    // 扣钱 "一口价" 或 "竞拍"
    SubMoney(MONEYTYPE_02, llprice, MONEYLOG_AUCTION_LEFT_MONEY, 0);

    CCliMessageHandler::GetInstance().DoMSAuctionPay(errSuccess, m_pOwner->GetObjID(), auctionid, llprice);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::ExchangeAddOrder(INT32 nItemIDRequire, INT32 nItemCountRequire, UINT8 byOrderType, INT32 nPriceOrder, INT32 nCountOrder)
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    INT32 nRetCode = 0;
    INT32 nResult = errItemUnknown;

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(nItemIDRequire == MONEYTYPE_02, errItemUnknown);
    LOG_PROCESS_ERROR_RET_CODE(GetMoney(nItemIDRequire) >= nItemCountRequire + EXCHANGE_FEE, errItemNotEnoughMoneytype02);

    CCliMessageHandler::GetInstance().DoMSExchangeAddOrder(errSuccess, m_pOwner->GetObjID(), nItemIDRequire, nItemCountRequire, byOrderType, nPriceOrder, nCountOrder);

    SubMoney(nItemIDRequire, nItemCountRequire, MONEYLOG_EXCHANGE, 0);
    SubMoney(nItemIDRequire, EXCHANGE_FEE, MONEYLOG_EXCHANGE_FEE, 0);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::DeleteItemPos(UINT8 conslot, UINT8 itemslot, INT16 itemcount, EItemLog reason, UINT64 qwUserDefinedID)
{
    INT32 nResult = errItemUnknown;
    INT32 nRetCode = 0;
    ConIt it;
    Item* item = NULL;

    LOG_PROCESS_ERROR_RET_CODE(itemcount >= 0, errItemUnknown);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);

    it = m_cons[conslot].find(itemslot);
    if (it == m_cons[conslot].end())
        return errItemNotFound;

    item = it->second;

    if (item->m_pTemplate->m_byDurType == DURTYPE_STACK)
    {
        LOG_PROCESS_ERROR_RET_CODE(itemcount <= item->m_iteminfo.m_nCurDur, errItemUnknown);

        item->m_iteminfo.m_nCurDur -= itemcount;
        if (item->m_iteminfo.m_nCurDur <= 0)
        {
#ifndef _ROBOT
            CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, conslot, itemslot);

            if (item->m_pTemplate->m_byLog)
            {
                CCliMessageHandler::GetInstance().DoDLLogItem(
                    m_pOwner->GetObjID(),
                    m_pOwner->GetServerGroup(),
                    item->m_iteminfo.m_llGuid,
                    item->m_pTemplate->m_nTemplateID,
                    itemcount,
                    reason,
                    ITEMACTION_DEL,
                    0);
            }

            if (item->m_pTemplate->m_byStat)
            {
                CCliMessageHandler::GetInstance().DoDLStatItem(
                    m_pOwner->GetServerGroup(),
                    item->m_pTemplate->m_nTemplateID,
                    itemcount,
                    0);
            }
#endif // _ROBOT

            BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
            LOG_CHECK_ERROR(bItemRet);
            m_cons[conslot].erase(it);
        }
        else
        {
#ifndef _ROBOT
            CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);

            if (item->m_pTemplate->m_byLog)
            {
                CCliMessageHandler::GetInstance().DoDLLogItem(
                    m_pOwner->GetObjID(),
                    m_pOwner->GetServerGroup(),
                    item->m_iteminfo.m_llGuid,
                    item->m_pTemplate->m_nTemplateID,
                    itemcount,
                    reason,
                    ITEMACTION_DEC,
                    qwUserDefinedID);
            }

            if (item->m_pTemplate->m_byStat)
            {
                CCliMessageHandler::GetInstance().DoDLStatItem(
                    m_pOwner->GetServerGroup(),
                    item->m_pTemplate->m_nTemplateID,
                    itemcount,
                    0);
            }
#endif _ROBOT
        }
    }
    else
    {
        LOG_PROCESS_ERROR_RET_CODE(itemcount == 1, errItemUnknown);

#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, conslot, itemslot);

        if (item->m_pTemplate->m_byLog)
        {
            CCliMessageHandler::GetInstance().DoDLLogItem(
                m_pOwner->GetObjID(),
                m_pOwner->GetServerGroup(),
                item->m_iteminfo.m_llGuid,
                item->m_pTemplate->m_nTemplateID,
                itemcount,
                reason,
                ITEMACTION_DEL,
                0);
        }

        if (item->m_pTemplate->m_byStat)
        {
            CCliMessageHandler::GetInstance().DoDLStatItem(
                m_pOwner->GetServerGroup(),
                item->m_pTemplate->m_nTemplateID,
                itemcount,
                0);
        }

        if (conslot == CONSLOT_EQUIPPED && itemslot < NES_VISIBLE_TOTAL)
            CCliMessageHandler::GetInstance().DoSyncRoleAvatar(m_pOwner, conslot, itemslot, 0, 0);
#endif // _ROBOT

        if (conslot == CONSLOT_EQUIPPED && item->m_iteminfo.m_nCurDur > 0)
            item->OnUnEquip(m_pOwner, m_refine_levels[itemslot], m_pOwner->GetClass(), itemslot);
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
        LOG_CHECK_ERROR(bItemRet);
        m_cons[conslot].erase(it);
    }

    CheckWeight();

    return errSuccess;

Exit0:
    return nResult;
}

INT32 CItemBag::DeleteItemId(INT32 itemid, INT16 itemcount, EItemLog reason, BOOL includebank, UINT64 qwUserDefinedID)
{
    UINT16 search_end = CONSLOT_DEFAULT;
    if (includebank)
        search_end = CONSLOT_BANK;

    if (m_pOwner->GetMoveState() == CMS_STALL)
        return errItemStall;

    for (INT32 i = CONSLOT_DEFAULT; i <= search_end; i++)
    {
        Container& con = m_cons[i];
        for (ConIt it = con.begin(); it != con.end();)
        {
            Item* item = it->second;
            if (item->m_pTemplate->m_nTemplateID == itemid)
            {
                INT16 findcount = 1;
                if (item->m_pTemplate->m_byDurType == DURTYPE_STACK)
                    findcount = item->m_iteminfo.m_nCurDur;

                if (itemcount <= findcount)
                {
                    INT32 nRetCode = DeleteItemPos(i, it->first, itemcount, reason, qwUserDefinedID);
                    LOG_CHECK_ERROR(nRetCode == errSuccess);

                    return errSuccess;
                }
                else
                {
                    UINT8 itemslot = it->first;
                    ++it;
                    INT32 nRetCode = DeleteItemPos(i, itemslot, findcount, reason, qwUserDefinedID);
                    LOG_CHECK_ERROR(nRetCode == errSuccess);

                    itemcount -= findcount;

                    continue;
                }
            }
            ++it;
        }
    }

    return errItemNotEnough;
}

INT32 CItemBag::RemoveItem(UINT8 conslot, UINT8 itemslot, EItemLog reason)
{
    // 此方法仅供trade调用，可以删除物品而不删除对象，因为对象还要给另外一个玩家
    INT32 nResult = errItemUnknown;
    INT32 nRetCode = 0;
    Item* item = GetItem(conslot, itemslot);

    LOG_PROCESS_ERROR_RET_CODE(item, errItemNotFound);

#ifndef _ROBOT
    CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, conslot, itemslot);

    if (item->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLLogItem(
            m_pOwner->GetObjID(),
            m_pOwner->GetServerGroup(),
            item->m_iteminfo.m_llGuid,
            item->m_pTemplate->m_nTemplateID,
            item->m_pTemplate->m_byDurType == DURTYPE_STACK ? item->m_iteminfo.m_nCurDur : 1,
            reason,
            ITEMACTION_DEL,
            0);
    }

    if (item->m_pTemplate->m_byStat)
    {
        CCliMessageHandler::GetInstance().DoDLStatItem(
            m_pOwner->GetServerGroup(),
            item->m_pTemplate->m_nTemplateID,
            item->m_pTemplate->m_byDurType == DURTYPE_STACK ? item->m_iteminfo.m_nCurDur : 1,
            0);
    }
#endif  // _ROBOT
    m_cons[conslot].erase(itemslot);

    if (conslot == CONSLOT_EQUIPPED && item->m_iteminfo.m_nCurDur > 0)
        item->OnUnEquip(m_pOwner, m_refine_levels[itemslot], m_pOwner->GetClass(), itemslot);

    CheckWeight();

    return errSuccess;

Exit0:
    return nResult;
}

INT16 CItemBag::GetItemCount(INT32 itemid, BOOL includebank/*=FALSE*/) const
{
    INT16 itemcount = 0;
    UINT16 search_end = CONSLOT_DEFAULT;
    if (includebank)
        search_end = CONSLOT_BANK;

    for (INT32 i = CONSLOT_DEFAULT; i <= search_end; i++)
    {
        const Container& con = m_cons[i];
        for (Container::const_iterator it = con.begin(); it != con.end(); ++it)
        {
            const Item* item = it->second;
            if (item->m_pTemplate->m_nTemplateID == itemid)
            {
                if (item->m_pTemplate->m_byDurType == DURTYPE_STACK)
                    itemcount += item->m_iteminfo.m_nCurDur;
                else
                    itemcount++;
            }
        }
    }

    return itemcount;
}

UINT32 CItemBag::GetFreeSlots(UINT8 conslot)
{
    LOG_PROCESS_ERROR(conslot < CONSLOT_COUNT);
    LOG_PROCESS_ERROR(m_cons[conslot].size() <= m_con_sizes[conslot]);

    return (UINT32)(m_con_sizes[conslot] - m_cons[conslot].size());

Exit0:
    return 0;
}

UINT32 CItemBag::GetUsedSlotCount(UINT8 conslot)
{
    LOG_PROCESS_ERROR(conslot < CONSLOT_COUNT);

    return (UINT32)m_cons[conslot].size();
Exit0:
    return 0;
}

void CItemBag::LoseItemOnDeath(BOOL is_player)
{
    Item* drop_items[256];
    INT32 total_drop_count = 0;

    //以下分别是包内普通物品，包内贵重物品，已装备物品的最多掉落数量和被选掉落物品，具体掉落概率还需要根据物品不同而变化
    std::vector<Item*> items_to_be_dropped[3];

    UINT8 name_color = m_pOwner->GetNameColor();
    const PK_DROP_COUNT_DATA* pk_drop_data = CDataManager<PK_DROP_COUNT_DATA>::GetInstance().GetData(m_pOwner->GetLevel());
    LOG_PROCESS_ERROR(pk_drop_data);

    if (m_dwFirstDeathTime == 0 || m_dwFirstDeathTime + 600000 < CGameWorld::GetInstance().GetGameTime())
    {
        m_dwFirstDeathTime = CGameWorld::GetInstance().GetGameTime();
        m_dwDeathCountFromFirst = 0;
    }
    else
    {
        m_dwDeathCountFromFirst++;
    }

    if (m_dwDeathCountFromFirst >= 50)
    {
        //如果玩家角色在10分钟内PK死亡超过50次，则玩家身上和背包内受到白名单保护的道具中随机掉落一个。
        std::vector<Item*> protected_items;

        for (ConIt it = m_cons[CONSLOT_DEFAULT].begin(); it != m_cons[CONSLOT_DEFAULT].end(); it++)
        {
            Item* item = it->second;
            if (item->m_pTemplate->m_bPkDrop == PKDROP_NOT_DROP && item->m_iteminfo.m_byBindType != BINDTYPE_BINDED)
            {
                protected_items.push_back(item);
                //debug
                if (item->m_iteminfo.m_byConSlot != CONSLOT_DEFAULT || item->m_iteminfo.m_byItemSlot != it->first)
                {
                    CRI("ItemPos Error: %d, %d, %d, %d, %d", item->m_iteminfo.m_nTemplateID, item->m_iteminfo.m_byConSlot, item->m_iteminfo.m_byItemSlot, CONSLOT_DEFAULT, it->first);
                }
            }
        }
        for (ConIt it = m_cons[CONSLOT_EQUIPPED].begin(); it != m_cons[CONSLOT_EQUIPPED].end(); it++)
        {
            Item* item = it->second;
            if (item->m_pTemplate->m_bPkDrop == PKDROP_NOT_DROP && item->m_iteminfo.m_byBindType != BINDTYPE_BINDED)
            {
                protected_items.push_back(item);
                //debug
                if (item->m_iteminfo.m_byConSlot != CONSLOT_EQUIPPED || item->m_iteminfo.m_byItemSlot != it->first)
                {
                    CRI("ItemPos Error: %d, %d, %d, %d, %d", item->m_iteminfo.m_nTemplateID, item->m_iteminfo.m_byConSlot, item->m_iteminfo.m_byItemSlot, CONSLOT_EQUIPPED, it->first);
                }
            }
        }

        if (protected_items.size() > 0)
        {
            Item* item = protected_items[g_Random((INT32)protected_items.size())];
            drop_items[total_drop_count++] = item;
        }
    }

    if (m_dwLastDeathTime && m_dwLastDeathTime + pk_drop_data->m_nProtectTime / GAME_FPS >= CGameWorld::GetInstance().GetGameTime())
    {
        //保护时间内免掉落一次
        m_dwLastDeathTime = 0;
    }
    else
    {
        m_dwLastDeathTime = CGameWorld::GetInstance().GetGameTime();

        for (ConIt it = m_cons[CONSLOT_DEFAULT].begin(); it != m_cons[CONSLOT_DEFAULT].end(); it++)
        {
            Item* item = it->second;
            //debug
            if (item->m_iteminfo.m_byConSlot != CONSLOT_DEFAULT || item->m_iteminfo.m_byItemSlot != it->first)
            {
                CRI("ItemPos Error: %d, %d, %d, %d, %d", item->m_iteminfo.m_nTemplateID, item->m_iteminfo.m_byConSlot, item->m_iteminfo.m_byItemSlot, CONSLOT_DEFAULT, it->first);
            }
            if (item->m_iteminfo.m_byBindType != BINDTYPE_BINDED)
            {
                if (item->m_pTemplate->m_bPkDrop == PKDROP_MUST_DROP)
                {
                    drop_items[total_drop_count++] = item;
                    if (total_drop_count >= 256)
                        break;
                }
                else if (item->m_pTemplate->m_byExpensiveItem)
                    items_to_be_dropped[1].push_back(item);
                else
                    items_to_be_dropped[0].push_back(item);
            }
        }

        if (total_drop_count < 256)
        {
            for (ConIt it = m_cons[CONSLOT_EQUIPPED].begin(); it != m_cons[CONSLOT_EQUIPPED].end(); it++)
            {
                Item* item = it->second;
                //debug
                if (item->m_iteminfo.m_byConSlot != CONSLOT_EQUIPPED || item->m_iteminfo.m_byItemSlot != it->first)
                {
                    CRI("ItemPos Error: %d, %d, %d, %d, %d", item->m_iteminfo.m_nTemplateID, item->m_iteminfo.m_byConSlot, item->m_iteminfo.m_byItemSlot, CONSLOT_EQUIPPED, it->first);
                }
                if (item->m_iteminfo.m_byBindType != BINDTYPE_BINDED)
                {
                    if (item->m_pTemplate->m_bPkDrop == PKDROP_MUST_DROP)
                    {
                        drop_items[total_drop_count++] = item;
                        if (total_drop_count >= 256)
                            break;
                    }
                    else
                        items_to_be_dropped[2].push_back(item);
                }
            }
        }

        for (INT32 i = 0; i < 3; i++)
        {
            if (total_drop_count < 256)
            {
                INT32 this_type_count = 0;

                // std::random_shuffle was removed in C++17: Fisher-Yates with the game's own random generator
                for (size_t k = items_to_be_dropped[i].size(); k > 1; k--)
                    std::swap(items_to_be_dropped[i][k - 1], items_to_be_dropped[i][g_Random((UINT32)k)]);

                for (std::vector<Item*>::iterator it = items_to_be_dropped[i].begin(); it != items_to_be_dropped[i].end(); it++)
                {
                    Item* item = (*it);
                    if (g_Random(10000) < _GetPkDropChance(item, is_player, name_color))
                    {
                        drop_items[total_drop_count++] = item;
                        if (total_drop_count >= 256)
                            break;

                        this_type_count++;
                        if (this_type_count >= pk_drop_data->m_nMaxDropCount[i][name_color])
                            break;
                    }
                }
            }
        }
    }

    if (total_drop_count > 0)
    {
        for (INT32 i = 0; i < total_drop_count; i++)
        {
            Item* drop_item = drop_items[i];

            if (drop_item->m_iteminfo.m_byConSlot == CONSLOT_EQUIPPED && drop_item->m_iteminfo.m_nCurDur > 0)
            {
                drop_item->OnUnEquip(m_pOwner, m_refine_levels[drop_item->m_iteminfo.m_byItemSlot], m_pOwner->GetClass(), drop_item->m_iteminfo.m_byItemSlot);
            }

            //debug
            if (GetItem(drop_item->m_iteminfo.m_byConSlot, drop_item->m_iteminfo.m_byItemSlot) != drop_item)
            {
                Item* strange_item = GetItem(drop_item->m_iteminfo.m_byConSlot, drop_item->m_iteminfo.m_byItemSlot);
                CRI("ItemPos Error 1: %d, %d, %d", drop_item->m_iteminfo.m_nTemplateID, drop_item->m_iteminfo.m_byConSlot, drop_item->m_iteminfo.m_byItemSlot);
                
                if (strange_item)
                    CRI("ItemPos Error 2: %d, %d, %d", strange_item->m_iteminfo.m_nTemplateID, strange_item->m_iteminfo.m_byConSlot, strange_item->m_iteminfo.m_byItemSlot);
            }

            m_cons[drop_item->m_iteminfo.m_byConSlot].erase(drop_item->m_iteminfo.m_byItemSlot);

#ifndef _ROBOT
            CCliMessageHandler::GetInstance().DoSendLosePkItem(m_pOwner, drop_item);
            CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, drop_item->m_iteminfo.m_byConSlot, drop_item->m_iteminfo.m_byItemSlot);

            if (drop_item->m_pTemplate->m_byLog)
            {
                CCliMessageHandler::GetInstance().DoDLLogItem(
                    m_pOwner->GetObjID(),
                    m_pOwner->GetServerGroup(),
                    drop_item->m_iteminfo.m_llGuid,
                    drop_item->m_pTemplate->m_nTemplateID,
                    drop_item->m_pTemplate->m_byDurType == DURTYPE_STACK ? drop_item->m_iteminfo.m_nCurDur : 1,
                    ITEMLOG_DEATH,
                    ITEMACTION_DEL,
                    0);
            }

            if (drop_item->m_pTemplate->m_byStat)
            {
                CCliMessageHandler::GetInstance().DoDLStatItem(
                    m_pOwner->GetServerGroup(),
                    drop_item->m_pTemplate->m_nTemplateID,
                    drop_item->m_pTemplate->m_byDurType == DURTYPE_STACK ? drop_item->m_iteminfo.m_nCurDur : 1,
                    0);
            }
#endif // _ROBOT
        }
        CDropGenerator::GetInstance().GeneratePKDrops(drop_items, total_drop_count, m_pOwner->GetScene(), m_pOwner->GetX(), m_pOwner->GetY(), m_pOwner->GetZ(), m_pOwner->GetObjID());

        m_pOwner->GetAchievementList().AddVariable(avdDropItemBeKilled, total_drop_count);
    }

Exit0:
    return;
}

void CItemBag::DestroyItemOnDeath()
{
    for (ConIt it = m_cons[CONSLOT_EQUIPPED].begin(); it != m_cons[CONSLOT_EQUIPPED].end();)
    {
        Item* item = it->second;
        if (((const EQUIP_DATA*)item->m_pTemplate)->m_byDestroyOnDeath)
        {
#ifndef _ROBOT
            CCliMessageHandler::GetInstance().DoSendDestroyDeathItem(m_pOwner, item);
            CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, CONSLOT_EQUIPPED, it->first);

            if (item->m_pTemplate->m_byLog)
            {
                CCliMessageHandler::GetInstance().DoDLLogItem(
                    m_pOwner->GetObjID(),
                    m_pOwner->GetServerGroup(),
                    item->m_iteminfo.m_llGuid,
                    item->m_pTemplate->m_nTemplateID,
                    1,
                    ITEMLOG_DEATH,
                    ITEMACTION_DEL,
                    0);
            }

            if (item->m_pTemplate->m_byStat)
            {
                CCliMessageHandler::GetInstance().DoDLStatItem(
                    m_pOwner->GetServerGroup(),
                    item->m_pTemplate->m_nTemplateID,
                    1,
                    0);
            }
#endif // _ROBOT

            if (item->m_iteminfo.m_nCurDur > 0)
                item->OnUnEquip(m_pOwner, m_refine_levels[item->m_iteminfo.m_byItemSlot], m_pOwner->GetClass(), item->m_iteminfo.m_byItemSlot);
            BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
            LOG_CHECK_ERROR(bItemRet);
            m_cons[CONSLOT_EQUIPPED].erase(it++);
        }
        else
            ++it;
    }
}

struct CmpItem
{
    bool operator()(const Item* item1, const Item* item2) const
    {
        if (item1->m_pTemplate->m_byType != item2->m_pTemplate->m_byType)
            return item1->m_pTemplate->m_byType < item2->m_pTemplate->m_byType;

        if (item1->m_pTemplate->m_bySubType != item2->m_pTemplate->m_bySubType)
            return item1->m_pTemplate->m_bySubType < item2->m_pTemplate->m_bySubType;

        if (item1->m_iteminfo.m_nTemplateID != item2->m_iteminfo.m_nTemplateID)
            return item1->m_iteminfo.m_nTemplateID < item2->m_iteminfo.m_nTemplateID;

        return item1->m_iteminfo.m_llGuid < item2->m_iteminfo.m_llGuid;
    }
};

INT32 CItemBag::OrganizeBag(UINT8 conslot)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else
    INT32 nResult = errItemUnknown;
    std::vector<Item*> items;
    UINT8 itemslot = 0;

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR(CGameWorld::GetInstance().GetGameTime() - m_dwLastOrganizeTime >= 10);
    LOG_PROCESS_ERROR(conslot == CONSLOT_DEFAULT || conslot == CONSLOT_BANK || conslot == CONSLOT_RESOURCE);

    m_dwLastOrganizeTime = CGameWorld::GetInstance().GetGameTime();

    for (ConIt it = m_cons[conslot].begin(); it != m_cons[conslot].end(); ++it)
    {
        items.push_back(it->second);
    }
    m_cons[conslot].clear();

    std::sort(items.begin(), items.end(), CmpItem());

    for (UINT16 i = 0; i < items.size();)
    {
        Item* srcitem = items[i];
        bool erased = false;
        if (srcitem->m_pTemplate->m_byDurType == DURTYPE_STACK)
        {
            for (UINT16 j = 0; j < i; j++)
            {
                Item* dstitem = items[j];
                if (dstitem->m_pTemplate == srcitem->m_pTemplate &&
                    dstitem->m_iteminfo.m_byBindType == srcitem->m_iteminfo.m_byBindType &&
                    dstitem->m_iteminfo.m_nCurDur < dstitem->m_pTemplate->m_nDur)
                {
                    if (dstitem->m_iteminfo.m_nCurDur + srcitem->m_iteminfo.m_nCurDur <= dstitem->m_pTemplate->m_nDur)
                    {
                        dstitem->m_iteminfo.m_nCurDur += srcitem->m_iteminfo.m_nCurDur;

                        if (srcitem->m_pTemplate->m_byLog)
                        {
                            CCliMessageHandler::GetInstance().DoDLLogItem(
                                m_pOwner->GetObjID(),
                                m_pOwner->GetServerGroup(),
                                srcitem->m_iteminfo.m_llGuid,
                                srcitem->m_pTemplate->m_nTemplateID,
                                srcitem->m_iteminfo.m_nCurDur,
                                ITEMLOG_ORGANIZE_BAG,
                                ITEMACTION_DEL,
                                dstitem->m_iteminfo.m_llGuid);

                            CCliMessageHandler::GetInstance().DoDLLogItem(
                                m_pOwner->GetObjID(),
                                m_pOwner->GetServerGroup(),
                                dstitem->m_iteminfo.m_llGuid,
                                dstitem->m_pTemplate->m_nTemplateID,
                                srcitem->m_iteminfo.m_nCurDur,
                                ITEMLOG_ORGANIZE_BAG,
                                ITEMACTION_INC,
                                srcitem->m_iteminfo.m_llGuid);
                        }

                        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(srcitem);
                        LOG_CHECK_ERROR(bItemRet);
                        items.erase(items.begin() + i);
                        erased = true;
                        break;
                    }
                    else
                    {
                        INT32 real_count = dstitem->m_pTemplate->m_nDur - dstitem->m_iteminfo.m_nCurDur;
                        srcitem->m_iteminfo.m_nCurDur -= real_count;
                        dstitem->m_iteminfo.m_nCurDur += real_count;

                        if (srcitem->m_pTemplate->m_byLog)
                        {
                            CCliMessageHandler::GetInstance().DoDLLogItem(
                                m_pOwner->GetObjID(),
                                m_pOwner->GetServerGroup(),
                                srcitem->m_iteminfo.m_llGuid,
                                srcitem->m_pTemplate->m_nTemplateID,
                                real_count,
                                ITEMLOG_ORGANIZE_BAG,
                                ITEMACTION_DEC,
                                dstitem->m_iteminfo.m_llGuid);

                            CCliMessageHandler::GetInstance().DoDLLogItem(
                                m_pOwner->GetObjID(),
                                m_pOwner->GetServerGroup(),
                                dstitem->m_iteminfo.m_llGuid,
                                dstitem->m_pTemplate->m_nTemplateID,
                                real_count,
                                ITEMLOG_ORGANIZE_BAG,
                                ITEMACTION_INC,
                                srcitem->m_iteminfo.m_llGuid);
                        }
                    }
                }
            }
        }
        if (!erased)
            i++;
    }

    std::sort(items.begin(), items.end(), CmpItem());

    for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); ++it)
    {
        Item* item = *it;
        item->SetPos(conslot, itemslot);
        m_cons[conslot][itemslot] = item;
        itemslot++;
    }

    CCliMessageHandler::GetInstance().DoSyncItemBag(m_pOwner);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

// 设置-武器幸运数值 (不是增加, 是直接赋值)
void CItemBag::SetWeaponLuck(INT8 v)
{
#ifndef _ROBOT
    INT8 new_luck = 0;
    INT8 current_luck = 0;
    Item* weapon = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
    LOG_PROCESS_ERROR(weapon);

    current_luck = weapon->m_iteminfo.m_byLuck;

    new_luck = weapon->m_iteminfo.m_byLuck = v;
    LOG_PROCESS_ERROR(new_luck >= -9 && new_luck <= 9);

    CCliMessageHandler::GetInstance().DoSendLuckOilResult(m_pOwner, v);

    if (current_luck != new_luck)
    {
        m_pOwner->GetAttrList().SetAttrBase(m_pOwner, catLuck, new_luck);
        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, weapon);

        if (weapon->m_pTemplate->m_byLog)
        {
            CCliMessageHandler::GetInstance().DoDLChangeItem(
                m_pOwner->GetServerGroup(),
                m_pOwner->GetObjID(),
                ITEMLOG_LUCK_OIL,
                weapon->m_iteminfo);
        }
    }

    // 新增代码 - 清零-祝福油节点
    m_pOwner->ResetLuckRootCount();
    m_pOwner->NotifyRole_LuckRootCount();

Exit0:
    return;

#endif // _ROBOT
}

// 增加-武器幸运数值 (传入负数, 是扣数值)
void CItemBag::IncreaseWeaponLuck(INT8 v)
{
#ifndef _ROBOT
    INT8 new_luck = 0;
    Item* weapon = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
    LOG_PROCESS_ERROR(weapon);

    new_luck = weapon->m_iteminfo.m_byLuck + v;
    LOG_PROCESS_ERROR(new_luck >= -9 && new_luck <= 9);

    CCliMessageHandler::GetInstance().DoSendLuckOilResult(m_pOwner, v);

    weapon->m_iteminfo.m_byLuck = new_luck;
    if (v)
    {
        m_pOwner->GetAttrList().SetAttrBase(m_pOwner, catLuck, new_luck);
        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, weapon);

        if (weapon->m_pTemplate->m_byLog)
        {
            CCliMessageHandler::GetInstance().DoDLChangeItem(
                m_pOwner->GetServerGroup(),
                m_pOwner->GetObjID(),
                ITEMLOG_LUCK_OIL,
                weapon->m_iteminfo);
        }
    }

    // 新增代码 - 增加祝福油节点
    m_pOwner->IncLuckRootCount();
    m_pOwner->NotifyRole_LuckRootCount();

Exit0:
    return;

#endif // _ROBOT
}

void CItemBag::DecreaseWeaponLuck()
{
#ifndef _ROBOT
    //若被击杀玩家的PK值小于100，则有20%的几率降低一点幸运值。
    Item* item = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
    if (item && item->m_iteminfo.m_byLuck > -9 && g_Random(100) < 20)
    {
        item->m_iteminfo.m_byLuck--;
        m_pOwner->GetAttrList().SetAttrBase(m_pOwner, catLuck, item->m_iteminfo.m_byLuck);
        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);

        if (item->m_pTemplate->m_byLog)
        {
            CCliMessageHandler::GetInstance().DoDLChangeItem(
                m_pOwner->GetServerGroup(),
                m_pOwner->GetObjID(),
                ITEMLOG_DEATH,
                item->m_iteminfo);
        }
    }

#endif // _ROBOT
}

INT32 CItemBag::TransferItemTo(CItemBag* dstbag, Item* item, INT16 itemcount, EItemLog reason)
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    INT32 nRetCode = errUnknownError;
    UINT8 old_conslot = 0;
    UINT8 old_itemslot = 0;

    LOG_PROCESS_ERROR(dstbag);
    LOG_PROCESS_ERROR(this != dstbag);
    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(m_pOwner);
    LOG_PROCESS_ERROR(item->m_pTemplate);

    old_conslot = item->m_iteminfo.m_byConSlot;
    old_itemslot = item->m_iteminfo.m_byItemSlot;
    LOG_PROCESS_ERROR(GetItem(old_conslot, old_itemslot) == item);

    if (item->m_pTemplate->m_byDurType == DURTYPE_STACK && itemcount < item->m_iteminfo.m_nCurDur)
    {
        Item* newitem = CItemMgr::GetInstance().CopyItem(item);
        LOG_PROCESS_ERROR(newitem);
        newitem->m_iteminfo.m_nCurDur = itemcount;

        nRetCode = dstbag->AddItem(newitem, reason, m_pOwner->GetObjID());
        if (nRetCode == errSuccess)
        {
            item->m_iteminfo.m_nCurDur -= itemcount;
            CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);
            CheckWeight();

            if (item->m_pTemplate->m_byLog)
            {
                CCliMessageHandler::GetInstance().DoDLLogItem(
                    m_pOwner->GetObjID(),
                    m_pOwner->GetServerGroup(),
                    item->m_iteminfo.m_llGuid,
                    item->m_pTemplate->m_nTemplateID,
                    itemcount,
                    reason,
                    ITEMACTION_DEC,
                    dstbag->GetOwner()->GetObjID());
            }
        }
        else
        {
            BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(newitem);
            LOG_CHECK_ERROR(bItemRet);
        }

        return nRetCode;
    }
    else
    {
        if (item->m_pTemplate->m_byDurType == DURTYPE_STACK)
            LOG_PROCESS_ERROR(itemcount == item->m_iteminfo.m_nCurDur);
        else
            LOG_PROCESS_ERROR(itemcount == 1);

        nRetCode = dstbag->AddItem(item, reason, m_pOwner->GetObjID());
        if (nRetCode == errSuccess)
        {
            m_cons[old_conslot].erase(old_itemslot);
            CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, old_conslot, old_itemslot);
            CheckWeight();

            if (item->m_pTemplate->m_byLog)
            {
                CCliMessageHandler::GetInstance().DoDLLogItem(
                    m_pOwner->GetObjID(),
                    m_pOwner->GetServerGroup(),
                    item->m_iteminfo.m_llGuid,
                    item->m_pTemplate->m_nTemplateID,
                    itemcount,
                    reason,
                    ITEMACTION_DEL,
                    dstbag->GetOwner()->GetObjID());
            }
        }
        return nRetCode;
    }

Exit0:
    return errItemUnknown;

#endif // _ROBOT
}

void CItemBag::OnDisArm()
{

}

void CItemBag::OnDisArmFinish()
{

}

void CItemBag::LoseWeaponDur()
{
    Item* weapon = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
    if (weapon && weapon->m_iteminfo.m_nCurDur > 0)
    {
        _LoseDur(weapon, g_Random(0, 5) + 2 - ((const EQUIP_DATA*)(weapon->m_pTemplate))->m_byEquipStrength, ITEMLOG_ATTACK);
    }
}

BOOL CItemBag::LoseMineDur(INT32 nItemID)
{
    Item* weapon = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
    PROCESS_ERROR(weapon);
    PROCESS_ERROR(weapon->m_iteminfo.m_nCurDur > 0);
    PROCESS_ERROR(weapon->m_pTemplate->m_nTemplateID == nItemID);

    _LoseDur(weapon, g_Random(0, 15) + 5, ITEMLOG_MINE);

    return TRUE;
Exit0:
    return FALSE;
}

void CItemBag::LoseArmorDur(INT32 damage)
{
    for (CConIt it = m_cons[CONSLOT_EQUIPPED].begin(); it != m_cons[CONSLOT_EQUIPPED].end(); ++it)
    {
        if (it->first == NES_BODY || g_Random(8) == 0)
        {
            _LoseDur(it->second, damage, ITEMLOG_ATTACK);
        }
    }
}

void CItemBag::LoseAllDur(INT32 nPercent, EItemLog reason)
{
    for (INT32 nIndex = NES_MAIN_HAND; nIndex < NES_TOTAL; nIndex++)
    {
        Item* item = GetItem(CONSLOT_EQUIPPED, nIndex);
        if (item)
        {
            INT32 nDropDur = item->m_iteminfo.m_nCurDur;

            LOG_CHECK_ERROR(item->m_pTemplate);
            if (item->m_pTemplate)
                nDropDur = item->m_pTemplate->m_nDur * nPercent / 100;

            _LoseDur(item, nDropDur, reason);
        }
    }
}

void CItemBag::LoseHeroWeaponDur()
{
}

void CItemBag::LoseHeroArmorDur()
{
}

void CItemBag::LoseHeroAllDur(INT32 nPercent, EItemLog reason)
{
    for (INT32 nIndex = NES_MAIN_HAND; nIndex < NES_TOTAL; nIndex++)
    {
        Item* item = GetItem(CONSLOT_HERO_EQUIPPED, nIndex);
        if (item)
        {
            INT32 nDropDur = item->m_iteminfo.m_nCurDur;

            LOG_CHECK_ERROR(item->m_pTemplate);
            if (item->m_pTemplate)
                nDropDur = item->m_pTemplate->m_nDur * nPercent / 100;

            _LoseDur(item, nDropDur, reason);
        }
    }

}

UINT8 CItemBag::GetWeaponType()
{
    Item* item = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
    if (item)
        return ((EQUIP_DATA*)item->m_pTemplate)->m_byEquipType;
    else
        return WEAPONTYPE_HAND;
}

UINT8 CItemBag::GetHeroWeaponType()
{
    Item* item = GetItem(CONSLOT_HERO_EQUIPPED, NES_MAIN_HAND);
    if (item)
        return ((EQUIP_DATA*)item->m_pTemplate)->m_byEquipType;
    else
        return WEAPONTYPE_HAND;
}

void CItemBag::GetAppearance(INT32 nAvatar[])
{
    memset(nAvatar, 0, sizeof(INT32) * NES_VISIBLE_TOTAL);
    for (Container::const_iterator it = m_cons[CONSLOT_EQUIPPED].begin(); it != m_cons[CONSLOT_EQUIPPED].end(); ++it)
    {
        if (it->first < NES_VISIBLE_TOTAL)
            nAvatar[it->first] = it->second->m_iteminfo.m_nTemplateID;
        else
            break;
    }
}

void CItemBag::GetHeroAppearance(INT32 nAvatar[])
{
    memset(nAvatar, 0, sizeof(INT32) * NES_VISIBLE_TOTAL);
    for (Container::const_iterator it = m_cons[CONSLOT_HERO_EQUIPPED].begin(); it != m_cons[CONSLOT_HERO_EQUIPPED].end(); ++it)
    {
        if (it->first < NES_VISIBLE_TOTAL)
            nAvatar[it->first] = it->second->m_iteminfo.m_nTemplateID;
        else
            break;
    }
}

BOOL CItemBag::EquipItemOnBirth(INT32 itemid, UINT8 itemslot)
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    INT32 nRetCode = 0;
    Item* item = NULL;

    LOG_PROCESS_ERROR(_CheckValidItemPos(CONSLOT_EQUIPPED, itemslot));
    LOG_PROCESS_ERROR(GetItem(CONSLOT_EQUIPPED, itemslot) == NULL);

    item = CItemMgr::GetInstance().GenerateItem(itemid, 1);
    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(item->m_pTemplate);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);

    if (item->m_iteminfo.m_byBindType == BINDTYPE_BOE || item->m_iteminfo.m_byBindType == BINDTYPE_BOP)
        item->m_iteminfo.m_byBindType = BINDTYPE_BINDED;

    item->SetPos(CONSLOT_EQUIPPED, itemslot);
    m_cons[CONSLOT_EQUIPPED][itemslot] = item;
    item->OnEquip(m_pOwner, 0, 0, 0);

    if (item->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLLogItem(
            m_pOwner->GetObjID(),
            m_pOwner->GetServerGroup(),
            item->m_iteminfo.m_llGuid,
            item->m_pTemplate->m_nTemplateID,
            1,
            ITEMLOG_CREATE_ROLE,
            ITEMACTION_ADD,
            0);
    }

    if (item->m_pTemplate->m_byStat)
    {
        CCliMessageHandler::GetInstance().DoDLStatItem(
            m_pOwner->GetServerGroup(),
            item->m_pTemplate->m_nTemplateID,
            1,
            1);
    }

    return TRUE;

Exit0:
    return FALSE;

#endif // _ROBOT
}

BOOL CItemBag::EquipHeroItemOnBirth(INT32 itemid, UINT8 itemslot)
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    INT32 nRetCode = 0;
    Item* item = NULL;

    CHero* poHero = m_pOwner->GetHero();
    LOG_PROCESS_ERROR(poHero);

    LOG_PROCESS_ERROR(_CheckValidItemPos(CONSLOT_HERO_EQUIPPED, itemslot));
    LOG_PROCESS_ERROR(GetItem(CONSLOT_HERO_EQUIPPED, itemslot) == NULL);

    item = CItemMgr::GetInstance().GenerateItem(itemid, 1);
    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(item->m_pTemplate);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == DURTYPE_EQUIP);

    if (item->m_iteminfo.m_byBindType == BINDTYPE_BOE)
        item->m_iteminfo.m_byBindType = BINDTYPE_BINDED;

    item->SetPos(CONSLOT_HERO_EQUIPPED, itemslot);
    m_cons[CONSLOT_HERO_EQUIPPED][itemslot] = item;
    item->OnEquip(poHero, 0, 0, 0);

    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);

    if (IsAppearance(CONSLOT_HERO_EQUIPPED, itemslot))
        CCliMessageHandler::GetInstance().DoSyncHeroAvatar(m_pOwner, CONSLOT_HERO_EQUIPPED, itemslot, item->m_iteminfo.m_nTemplateID);

    if (item->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLLogItem(
            m_pOwner->GetObjID(),
            m_pOwner->GetServerGroup(),
            item->m_iteminfo.m_llGuid,
            item->m_pTemplate->m_nTemplateID,
            1,
            ITEMLOG_CREATE_HERO,
            ITEMACTION_ADD,
            0);
    }

    if (item->m_pTemplate->m_byStat)
    {
        CCliMessageHandler::GetInstance().DoDLStatItem(
            m_pOwner->GetServerGroup(),
            item->m_pTemplate->m_nTemplateID,
            1,
            1);
    }

    return TRUE;

Exit0:
    return FALSE;

#endif // #ifndef _ROBOT
}

INT64 CItemBag::GetMoney(INT32 moneytype, BOOL use_moneytype01_only/*=FALSE*/) const
{
    INT64 usable_money = 0;

    LOG_PROCESS_ERROR(moneytype > MONEYTYPE_INVALID && moneytype < MONEYTYPE_COUNT);

    usable_money = m_moneys[moneytype];
    LOG_PROCESS_ERROR(usable_money >= 0);

    if (m_moneys_daily_used_limit[moneytype] > 0 && usable_money > m_moneys_daily_used_limit[moneytype] - m_moneys_daily_used[moneytype])
    {
        usable_money = m_moneys_daily_used_limit[moneytype] - m_moneys_daily_used[moneytype];
        if (usable_money < 0)
            usable_money = 0;
    }
    if (m_moneys_weekly_used_limit[moneytype] > 0 && usable_money > m_moneys_weekly_used_limit[moneytype] - m_moneys_weekly_used[moneytype])
    {
        usable_money = m_moneys_weekly_used_limit[moneytype] - m_moneys_weekly_used[moneytype];
        if (usable_money < 0)
            usable_money = 0;
    }

    if (moneytype == MONEYTYPE_01 && !use_moneytype01_only && !m_use_moneytype01_only)
        return usable_money + GetMoney(MONEYTYPE_02);
    else
        return usable_money;

Exit0:
    return 0;
}

INT64 CItemBag::GetMoneyInfo(INT32 moneytype)
{
    LOG_PROCESS_ERROR(moneytype > MONEYTYPE_INVALID && moneytype < MONEYTYPE_COUNT);

    return m_moneys[moneytype];

Exit0:
    return 0;
}

void CItemBag::GetMoneyAllInfo(
    INT64 allMoneys[],
    INT64 allMoneysLimit[],
    INT32 anDailyEarned[],
    INT32 anDailyEarnedLimit[],
    INT32 anDailyUsed[],
    INT32 anDailyUsedLimit[],
    INT32 anWeeklyEarned[],
    INT32 anWeeklyEarnedLimit[],
    INT32 anWeeklyUsed[],
    INT32 anWeeklyUsedLimit[])
{
    memcpy(allMoneys, m_moneys, sizeof(m_moneys));
    memcpy(allMoneysLimit, m_moneys_limit, sizeof(m_moneys_limit));
    memcpy(anDailyEarned, m_moneys_daily_earned, sizeof(m_moneys_daily_earned));
    memcpy(anDailyEarnedLimit, m_moneys_daily_earned_limit, sizeof(m_moneys_daily_earned_limit));
    memcpy(anDailyUsed, m_moneys_daily_used, sizeof(m_moneys_daily_used));
    memcpy(anDailyUsedLimit, m_moneys_daily_used_limit, sizeof(m_moneys_daily_used_limit));
    memcpy(anWeeklyEarned, m_moneys_weekly_earned, sizeof(m_moneys_weekly_earned));
    memcpy(anWeeklyEarnedLimit, m_moneys_weekly_earned_limit, sizeof(m_moneys_weekly_earned_limit));
    memcpy(anWeeklyUsed, m_moneys_weekly_used, sizeof(m_moneys_weekly_used));
    memcpy(anWeeklyUsedLimit, m_moneys_weekly_used_limit, sizeof(m_moneys_weekly_used_limit));
}

INT32 CItemBag::AddMoney(INT32 moneytype, INT32 nCount, EMoneyLog reason, UINT32 dwSourceID)
{
#ifdef _ROBOT
    return errItemUnknown;
#else
    INT32 nResult = errItemUnknown;
    INT32 actual_add = nCount;
    INT32 fcm_loss = 0;
    INT32 daily_limit_loss = 0;
    INT32 weekly_limit_loss = 0;
    INT32 total_limit_loss = 0;

    LOG_PROCESS_ERROR_RET_CODE(moneytype > MONEYTYPE_INVALID && moneytype < MONEYTYPE_COUNT, errItemUnknown);
    LOG_PROCESS_ERROR_RET_CODE(nCount > 0, errItemUnknown);

    if (m_pOwner->GetFcmState() == fcmsNone)
    {
        if (moneytype == MONEYTYPE_01 || moneytype == MONEYTYPE_02)
        {
            CCliMessageHandler::GetInstance().DoDLAddMoney(m_pOwner->GetSessionID(),
                dwSourceID, m_pOwner->GetObjID(), moneytype, actual_add, reason, 0);
            CCliMessageHandler::GetInstance().DoDLSubMoney(m_pOwner->GetSessionID(),
                m_pOwner->GetObjID(), 0, moneytype, actual_add, MONEYLOG_FCM_LOSS, 0);
        }
        return errSuccess;
    }

    if (m_pOwner->GetFcmState() == fcmsHalf)
    {
        actual_add /= 2;
        fcm_loss = nCount - actual_add;
    }

    //redmine #23983
    //余力烨：金币的直接交易，摆摊获得，组队拍卖获得，邮件不计入每日及每周获取上限
    if (!(moneytype == MONEYTYPE_02 &&
        (reason == MONEYLOG_PLAYER_TRADE ||
            reason == MONEYLOG_PLAYER_STALL ||
            reason == MONEYLOG_TEAM_AUCTION_BONUS ||
            reason == MONEYLOG_TEAM_AUCTION_RETURN ||
            reason == MONEYLOG_GET_MAIL_ATTACH)))
    {
        if (m_moneys_daily_earned_limit[moneytype] > 0 && m_moneys_daily_earned[moneytype] + actual_add > m_moneys_daily_earned_limit[moneytype])
        {
            actual_add = m_moneys_daily_earned_limit[moneytype] - m_moneys_daily_earned[moneytype];
            m_pOwner->ErrorCodeNotify(errItemDailyMoneyExceeded, moneytype, 0);
            daily_limit_loss = nCount - fcm_loss - actual_add;
        }
        if (m_moneys_weekly_earned_limit[moneytype] > 0 && m_moneys_weekly_earned[moneytype] + actual_add > m_moneys_weekly_earned_limit[moneytype])
        {
            actual_add = m_moneys_weekly_earned_limit[moneytype] - m_moneys_weekly_earned[moneytype];
            m_pOwner->ErrorCodeNotify(errItemWeekMoneyExceeded, moneytype, 0);
            weekly_limit_loss = nCount - fcm_loss - daily_limit_loss - actual_add;
        }
    }
    if (m_moneys[moneytype] + actual_add > m_moneys_limit[moneytype])
    {
        actual_add = (INT32)(m_moneys_limit[moneytype] - m_moneys[moneytype]);
        m_pOwner->ErrorCodeNotify(errItemTotalMoneyExceeded, moneytype, 0);
        total_limit_loss = nCount - fcm_loss - daily_limit_loss - weekly_limit_loss - actual_add;
    }
    if (actual_add > 0)
    {
        m_moneys[moneytype] += actual_add;

        if (m_moneys_daily_earned_limit[moneytype] > 0)
            m_moneys_daily_earned[moneytype] += actual_add;

        if (m_moneys_weekly_earned_limit[moneytype] > 0)
            m_moneys_weekly_earned[moneytype] += actual_add;

        if (!m_pOwner->IsLoading())
        {
            CCliMessageHandler::GetInstance().DoSendMoneyChange(m_pOwner, moneytype, m_moneys[moneytype],
                m_moneys_daily_earned[moneytype], m_moneys_daily_used[moneytype], m_moneys_weekly_earned[moneytype], m_moneys_weekly_used[moneytype]);
        }
    }

    if (moneytype == MONEYTYPE_01 || moneytype == MONEYTYPE_02)
    {
        CCliMessageHandler::GetInstance().DoDLAddMoney(m_pOwner->GetSessionID(),
            dwSourceID, m_pOwner->GetObjID(), moneytype, nCount, reason, 0);

        if (fcm_loss > 0)
        {
            CCliMessageHandler::GetInstance().DoDLSubMoney(m_pOwner->GetSessionID(),
                m_pOwner->GetObjID(), 0, moneytype, fcm_loss, MONEYLOG_FCM_LOSS, 0);
        }

        if (daily_limit_loss > 0)
        {
            CCliMessageHandler::GetInstance().DoDLSubMoney(m_pOwner->GetSessionID(),
                m_pOwner->GetObjID(), 0, moneytype, daily_limit_loss, MONEYLOG_DAILY_LIMIT_LOSS, 0);
        }

        if (weekly_limit_loss > 0)
        {
            CCliMessageHandler::GetInstance().DoDLSubMoney(m_pOwner->GetSessionID(),
                m_pOwner->GetObjID(), 0, moneytype, weekly_limit_loss, MONEYLOG_WEEKLY_LIMIT_LOSS, 0);
        }

        if (total_limit_loss > 0)
        {
            CCliMessageHandler::GetInstance().DoDLSubMoney(m_pOwner->GetSessionID(),
                m_pOwner->GetObjID(), 0, moneytype, total_limit_loss, MONEYLOG_TOTAL_LIMIT_LOSS, 0);
        }
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::SubMoney(INT32 moneytype, INT32 nCount, EMoneyLog reason, UINT32 dwTargetID)
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    INT32 nRetCode = 0;
    INT32 nResult = errSuccess;
    INT64 usable_money = 0;

    LOG_PROCESS_ERROR(m_pOwner);
    LOG_PROCESS_ERROR_RET_CODE(moneytype > MONEYTYPE_INVALID && moneytype < MONEYTYPE_COUNT, errItemUnknown);
    LOG_PROCESS_ERROR_RET_CODE(nCount >= 0 && nCount <= MAX_MONEY, errItemUnknown);

    usable_money = GetMoney(moneytype, TRUE);
    LOG_PROCESS_ERROR(usable_money >= 0);

    if (moneytype == MONEYTYPE_01 && usable_money < nCount && !m_use_moneytype01_only)
    {
        INT64 usable_moneytype_02 = GetMoney(MONEYTYPE_02, TRUE);
        LOG_PROCESS_ERROR_RET_CODE(usable_money + usable_moneytype_02 >= nCount, errItemNotEnoughMoney);

        if (usable_money > 0)
        {
            m_moneys[moneytype] -= usable_money;

            if (m_moneys_daily_used_limit[moneytype] > 0)
                m_moneys_daily_used[moneytype] += (INT32)usable_money;

            if (m_moneys_weekly_used_limit[moneytype] > 0)
                m_moneys_weekly_used[moneytype] += (INT32)usable_money;

            if (!m_pOwner->IsLoading())
            {
                CCliMessageHandler::GetInstance().DoSendMoneyChange(m_pOwner, moneytype, m_moneys[moneytype],
                    m_moneys_daily_earned[moneytype], m_moneys_daily_used[moneytype], m_moneys_weekly_earned[moneytype], m_moneys_weekly_used[moneytype]);
            }

            CCliMessageHandler::GetInstance().DoDLSubMoney(m_pOwner->GetSessionID(),
                m_pOwner->GetObjID(), dwTargetID, moneytype, (INT)usable_money, reason, 0);
        }

        SubMoney(MONEYTYPE_02, nCount - (INT32)usable_money, reason, 0);
    }
    else
    {
        LOG_PROCESS_ERROR_RET_CODE(usable_money >= nCount, errItemNotEnoughMoney);
        m_moneys[moneytype] -= nCount;

        if (m_moneys_daily_used_limit[moneytype] > 0)
            m_moneys_daily_used[moneytype] += nCount;

        if (m_moneys_weekly_used_limit[moneytype] > 0)
            m_moneys_weekly_used[moneytype] += nCount;

        CCliMessageHandler::GetInstance().DoSendMoneyChange(m_pOwner, moneytype, m_moneys[moneytype],
            m_moneys_daily_earned[moneytype], m_moneys_daily_used[moneytype], m_moneys_weekly_earned[moneytype], m_moneys_weekly_used[moneytype]);

        if (moneytype == MONEYTYPE_01 || moneytype == MONEYTYPE_02)
        {
            CCliMessageHandler::GetInstance().DoDLSubMoney(m_pOwner->GetSessionID(),
                m_pOwner->GetObjID(), dwTargetID, moneytype, nCount, reason, 0);
        }
    }

Exit0:
    return nResult;

#endif // _ROBOT
}

INT32 CItemBag::SetMoney(INT32 moneytype, INT32 nCount)
{
    LOG_PROCESS_ERROR(moneytype > MONEYTYPE_INVALID && moneytype < MONEYTYPE_COUNT);
    LOG_PROCESS_ERROR(nCount >= 0 && nCount <= MAX_MONEY);
    m_moneys[moneytype] = nCount;

#ifndef _ROBOT
    if (!m_pOwner->IsLoading())
    {
        CCliMessageHandler::GetInstance().DoSendMoneyChange(m_pOwner, moneytype, m_moneys[moneytype],
            m_moneys_daily_earned[moneytype], m_moneys_daily_used[moneytype], m_moneys_weekly_earned[moneytype], m_moneys_weekly_used[moneytype]);
    }
#endif // _ROBOT

    return errSuccess;
Exit0:
    return errUnknownError;
}

void CItemBag::AddGoldPool(INT32 money)
{
    m_gold_pool += money;
    if (m_gold_pool > 2000000000)
        m_gold_pool = 2000000000;

    DBG("%s goldpool: %d", m_pOwner->GetName(), m_gold_pool);

    if (g_GWConfig.DebugOption.dropstat)
    {
        DBG("%s goldpool: %d", m_pOwner->GetName(), m_gold_pool);
    }
}

void CItemBag::SubGoldPool(INT32 money)
{
    m_gold_pool -= money;
    if (m_gold_pool < -500000)
        m_gold_pool = -500000;

    if (g_GWConfig.DebugOption.dropstat)
    {
        DBG("%s goldpool: %d", m_pOwner->GetName(), m_gold_pool);
    }
}

INT32 CItemBag::GetGoldPool() const
{
    return m_gold_pool;
}

INT32 CItemBag::GetChanceByGoldPool() const
{
    if (m_gold_pool > -10000)
        return RATE_MAX;
    else if (m_gold_pool > -20000)
        return 8000;
    else if (m_gold_pool > -50000)
        return 6000;
    else if (m_gold_pool > -100000)
        return 4000;
    else
        return 2000;
}

INT32 CItemBag::BuySlots(UINT8 conslot, UINT8 slotcount)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else

    INT32 nRetCode = 0;
    INT32 slot = 0;
    INT32 require_money = 0;

    LOG_PROCESS_ERROR(conslot == CONSLOT_DEFAULT || conslot == CONSLOT_BANK || conslot == CONSLOT_RESOURCE);
    LOG_PROCESS_ERROR(slotcount > 0);
    LOG_PROCESS_ERROR(m_con_sizes[conslot] + slotcount <= MAX_CONTAINER_SIZE[conslot]);

    // 判断背包类型 (默认背包/仓库/资源背包)
    switch (conslot)
    {
    default:
        return errItemUnknown;
    case CONSLOT_DEFAULT:
        for (UINT8 i = 0; i < slotcount; i++)
        {
            INT32 slot = m_con_sizes[CONSLOT_DEFAULT] - INIT_CONTAINER_SIZE[CONSLOT_DEFAULT] + i;
            LOG_PROCESS_ERROR(slot < MAX_CONTAINER_SIZE[CONSLOT_DEFAULT] - INIT_CONTAINER_SIZE[CONSLOT_DEFAULT]);
            require_money += g_GWConfig.nBagSlotCost[slot];
        }
        break;
    case CONSLOT_BANK:
        for (UINT8 i = 0; i < slotcount; i++)
        {
            INT32 slot = m_con_sizes[CONSLOT_BANK] - INIT_CONTAINER_SIZE[CONSLOT_BANK] + i;
            LOG_PROCESS_ERROR(slot < MAX_CONTAINER_SIZE[CONSLOT_BANK] - INIT_CONTAINER_SIZE[CONSLOT_BANK]);
            require_money += g_GWConfig.nBankSlotCost[slot];
        }
        break;
    case CONSLOT_RESOURCE:
        for (UINT8 i = 0; i < slotcount; i++)
        {
            INT32 slot = m_con_sizes[CONSLOT_RESOURCE] - INIT_CONTAINER_SIZE[CONSLOT_RESOURCE] + i;
            LOG_PROCESS_ERROR(slot < MAX_CONTAINER_SIZE[CONSLOT_RESOURCE] - INIT_CONTAINER_SIZE[CONSLOT_RESOURCE]);
            require_money += g_GWConfig.nResourceSlotCost[slot];
        }
        break;
    }

    if (GetMoney(MONEYTYPE_02) < require_money)
        return errItemNotEnoughMoneytype02;

    SubMoney(MONEYTYPE_02, require_money, MONEYLOG_BUY_SLOTS, 0);

    m_con_sizes[conslot] += slotcount;

    CCliMessageHandler::GetInstance().DoSendContainerSizeChange(m_pOwner, conslot, m_con_sizes[conslot]);

    CCliMessageHandler::GetInstance().DoDLBuyConSlot(m_pOwner, conslot, m_con_sizes[conslot]);

    return errSuccess;

Exit0:
    return errItemUnknown;

#endif // _ROBOT
}

INT32 CItemBag::UpgradeSoul(UINT8 targetconslot, UINT8 targetitemslot, UINT8 srccount, UINT8 srcconslot[], UINT8 srcitemslot[])
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else

    INT32 nResult = errItemUnknown;
    Item* target_soul = GetItem(targetconslot, targetitemslot);
    const SOUL_DATA* target_soul_data = NULL;
    const SOUL_DATA* next_level_soul_data = NULL;
    Item* src_soul[MAX_SOUL_UPGRADE_SRC];
    const SOUL_DATA* src_soul_data[MAX_SOUL_UPGRADE_SRC];
    UINT8 src_soul_count[MAX_SOUL_UPGRADE_SRC];
    UINT8 real_src_count = 0;
    UINT32 total_price_value = 0;
    BOOL upgrade_success = FALSE;

    if (m_pOwner->GetVIPLevel() < vlLevel2)
    {
        CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
        PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

        nResult = m_pOwner->CanInteract(npc);
        PROCESS_ERROR(nResult == errSuccess);

        LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractSoul, errNpcNoSuchFunction);
    }

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(targetconslot, targetitemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(target_soul, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(srccount > 0 && srccount <= MAX_SOUL_UPGRADE_SRC, errItemUnknown);
    LOG_PROCESS_ERROR_RET_CODE(target_soul->m_pTemplate->m_byType == ITEMTYPE_SOUL, errItemCannotUpgradeSoul);

    target_soul_data = CDataManager<SOUL_DATA>::GetInstance().GetData(target_soul->m_iteminfo.m_nTemplateID);
    LOG_PROCESS_ERROR(target_soul_data);
    LOG_PROCESS_ERROR_RET_CODE(target_soul_data->m_nUpgradeSoulID > 0, errItemUpgradeSoulLimit);

    next_level_soul_data = CDataManager<SOUL_DATA>::GetInstance().GetData(target_soul_data->m_nUpgradeSoulID);
    LOG_PROCESS_ERROR(next_level_soul_data && next_level_soul_data->m_nPriceValue);

    //整理输入，有可能几个材料是堆在同一格里的
    memset(src_soul, 0, sizeof(src_soul));
    memset(src_soul_data, 0, sizeof(src_soul_data));
    memset(src_soul_count, 0, sizeof(src_soul_count));
    for (UINT8 i = 0; i < srccount; i++)
    {
        BOOL found_exist = FALSE;
        for (UINT8 j = 0; j < real_src_count; j++)
        {
            if (src_soul[j]->m_iteminfo.m_byConSlot == srcconslot[i] && src_soul[j]->m_iteminfo.m_byItemSlot == srcitemslot[i])
            {
                src_soul_count[j]++;
                found_exist = TRUE;
                break;
            }
        }
        if (!found_exist)
        {
            Item* _soul = GetItem(srcconslot[i], srcitemslot[i]);
            LOG_PROCESS_ERROR_RET_CODE(_soul, errItemNotFound);
            LOG_PROCESS_ERROR_RET_CODE(_soul->m_pTemplate->m_byType == ITEMTYPE_SOUL, errItemCannotUpgradeSoul);

            src_soul[real_src_count] = _soul;
            src_soul_data[real_src_count] = CDataManager<SOUL_DATA>::GetInstance().GetData(_soul->m_iteminfo.m_nTemplateID);
            LOG_PROCESS_ERROR(src_soul_data[real_src_count]);

            src_soul_count[real_src_count] = 1;
            real_src_count++;
        }
    }

    for (UINT8 i = 0; i < real_src_count; i++)
    {
        LOG_PROCESS_ERROR_RET_CODE(src_soul[i]->m_iteminfo.m_nCurDur >= src_soul_count[i], errItemNotEnough);
        total_price_value += src_soul_data[i]->m_nPriceValue * src_soul_count[i];
    }

    if (target_soul->m_iteminfo.m_nCurDur > 1)
    {
        LOG_PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);
    }

    //删材料
    for (UINT8 i = 0; i < real_src_count; i++)
    {
        INT32 ret = DeleteItemPos(src_soul[i]->m_iteminfo.m_byConSlot, src_soul[i]->m_iteminfo.m_byItemSlot, src_soul_count[i],
            ITEMLOG_UPGRADE_SOUL, 0);
        LOG_CHECK_ERROR(ret == errSuccess);
    }

    //随机
    upgrade_success = g_Random(next_level_soul_data->m_nPriceValue) < total_price_value;
    if (upgrade_success)
    {
        INT32 ret = DeleteItemPos(targetconslot, targetitemslot, 1, ITEMLOG_UPGRADE_SOUL, 0);
        LOG_CHECK_ERROR(ret == errSuccess);

        ret = AddItem(target_soul_data->m_nUpgradeSoulID, 1, ITEMLOG_UPGRADE_SOUL, 0, FALSE);
        LOG_CHECK_ERROR(ret == errSuccess);
    }

    CCliMessageHandler::GetInstance().DoSendUpgradeSoulResult(m_pOwner, upgrade_success);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

// 镶嵌灵石
INT32 CItemBag::AddSoul(UINT8 equipconslot, UINT8 equipitemslot, UINT8 socketindex, UINT8 soulconslot, UINT8 soulitemslot)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else

    INT32 nResult = errItemUnknown;
    Item* target_equip = GetItem(equipconslot, equipitemslot);
    Item* soul = GetItem(soulconslot, soulitemslot);
    const SOUL_DATA* soul_data = NULL;
    UINT8 target_socket_type = SOCKET_NONE;

    if (m_pOwner->GetVIPLevel() < vlLevel2)
    {
        CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
        PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

        nResult = m_pOwner->CanInteract(npc);
        PROCESS_ERROR(nResult == errSuccess);

        LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractSoul, errNpcNoSuchFunction);
    }

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(equipconslot, equipitemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(soulconslot, soulitemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(!_SrcDstSame(equipconslot, equipitemslot, soulconslot, soulitemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(target_equip, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(soul, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(equipconslot != CONSLOT_EQUIPPED && equipconslot != CONSLOT_HERO_EQUIPPED, errItemEquipped);
    LOG_PROCESS_ERROR(socketindex < MAX_SOCKET_COUNT);//最多插3个
    LOG_PROCESS_ERROR_RET_CODE(soul->m_pTemplate->m_byType == ITEMTYPE_SOUL, errItemCannotAddSoul);//必须用灵魂来插
    LOG_PROCESS_ERROR_RET_CODE(target_equip->m_pTemplate->m_byType == ITEMTYPE_EQUIP, errItemCannotAddSoul);//只能插在装备上

    target_socket_type = target_equip->m_iteminfo.GetSocketType(socketindex);
    LOG_PROCESS_ERROR(target_socket_type != SOCKET_NONE);//有孔才能插
    LOG_PROCESS_ERROR_RET_CODE(target_equip->m_iteminfo.m_nSoulID[socketindex] == 0, errItemAlreadySocketed);

    soul_data = CDataManager<SOUL_DATA>::GetInstance().GetData(soul->m_iteminfo.m_nTemplateID);
    LOG_PROCESS_ERROR(soul_data);
    if (target_socket_type != SOCKET_COLORFUL)
    {
        //如果不是彩色孔，则颜色必须匹配
        LOG_PROCESS_ERROR_RET_CODE(target_socket_type == soul_data->m_nMatchSocket, errItemSocketNotMatch);
    }
    //LOG_PROCESS_ERROR(target_equip->m_pTemplate->m_byRequireLevel >= soul_data->m_nSoulLevel);//灵魂有等级需求，需大于装备需求等级

    //满足了所有条件，那就插进去吧
    DeleteItemPos(soulconslot, soulitemslot, 1, ITEMLOG_INSERT_SOUL, 0);

    target_equip->m_iteminfo.m_nSoulID[socketindex] = soul_data->m_nTemplateID;
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, target_equip);

    if (target_equip->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_INSERT_SOUL,
            target_equip->m_iteminfo);
    }

    CCliMessageHandler::GetInstance().DoSendAddSoulResult(m_pOwner, errSuccess);

    CAdventure::GetInstance().OnAddSoul(m_pOwner);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

// 拆除灵石
INT32 CItemBag::RemoveSoul(UINT8 conslot, UINT8 itemslot, UINT8 socketindex)
{
#ifdef _ROBOT
    //TODO
    return errItemUnknown;
#else

    INT32 nResult = errItemUnknown;
    Item* target_equip = GetItem(conslot, itemslot);
    const SOUL_DATA* soul_data = NULL;

    if (m_pOwner->GetVIPLevel() < vlLevel2)
    {
        CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
        PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

        nResult = m_pOwner->CanInteract(npc);
        PROCESS_ERROR(nResult == errSuccess);

        LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractSoul, errNpcNoSuchFunction);
    }

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(target_equip, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(conslot != CONSLOT_EQUIPPED && conslot != CONSLOT_HERO_EQUIPPED, errItemEquipped);
    LOG_PROCESS_ERROR(socketindex < MAX_SOCKET_COUNT);
    LOG_PROCESS_ERROR_RET_CODE(target_equip->m_pTemplate->m_byType == ITEMTYPE_EQUIP, errItemCannotAddSoul);
    LOG_PROCESS_ERROR_RET_CODE(target_equip->m_iteminfo.m_dwSocketCombination > 0, errItemCannotAddSoul);
    LOG_PROCESS_ERROR(target_equip->m_iteminfo.GetSocketType(socketindex) != SOCKET_NONE);
    LOG_PROCESS_ERROR_RET_CODE(target_equip->m_iteminfo.m_nSoulID[socketindex] != 0, errItemNotSocketed);

    soul_data = CDataManager<SOUL_DATA>::GetInstance().GetData(target_equip->m_iteminfo.m_nSoulID[socketindex]);
    LOG_PROCESS_ERROR(soul_data);
    LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= soul_data->m_nRemovePrice, errItemNotEnoughMoneytype02);
    LOG_PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);

    SubMoney(MONEYTYPE_02, soul_data->m_nRemovePrice, MONEYLOG_REMOVE_SOUL, 0);
    AddItem(target_equip->m_iteminfo.m_nSoulID[socketindex], 1, ITEMLOG_REMOVE_SOUL, 0, FALSE);

    target_equip->m_iteminfo.m_nSoulID[socketindex] = 0;
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, target_equip);

    if (target_equip->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_REMOVE_SOUL,
            target_equip->m_iteminfo);
    }

    CCliMessageHandler::GetInstance().DoSendRemoveSoulResult(m_pOwner, errSuccess);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

// 普通铭文洗练
INT32 CItemBag::RuneItem(UINT8 conslot, UINT8 itemslot, INT32 itemid)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else

    BOOL bRet = FALSE;
    INT32 nResult = errItemUnknown;
    INT32 nRuneID = 0;
    const RUNE_DATA* pcRuneData = NULL;
    Item* weapon = GetItem(conslot, itemslot);
    INT32 runegroup = 1;
    INT32 nRuneRootCount = 0;

    if (m_pOwner->GetVIPLevel() < vlLevel2)
    {
        CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
        PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

        nResult = m_pOwner->CanInteract(npc);
        PROCESS_ERROR(nResult == errSuccess);

        LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractRune, errNpcNoSuchFunction);

        runegroup = npc->GetNpcData()->nRuneGroup;
    }

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(weapon, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(weapon->m_pTemplate->m_byType == ITEMTYPE_EQUIP, errItemRuneError);
    LOG_PROCESS_ERROR_RET_CODE(weapon->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_WEAPON, errItemRuneError);
    LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= RUNE_ITEM_COST, errItemNotEnoughMoneytype02);
    LOG_PROCESS_ERROR_RET_CODE(GetItemCount(itemid) >= 1, errItemRuneNotEnoughMaterial);
    if (m_pOwner->GetScene()->GetSceneID() == m_pOwner->GetGuildID())
    {
        LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_GUILD) >= GUILD_RUNE_COST, errGuildNotEnoughContribution);
    }

    // 获取节点数值
    if (itemid == RUNE_ITEMID_WARRIOR_1)
        nRuneRootCount = m_pOwner->GetRuneRootCount(rrrNormal, clsWarrior);
    else if (itemid == RUNE_ITEMID_MAGE_1)
        nRuneRootCount = m_pOwner->GetRuneRootCount(rrrNormal, clsMage);
    else if (itemid == RUNE_ITEMID_TAOIST_1)
        nRuneRootCount = m_pOwner->GetRuneRootCount(rrrNormal, clsTaoist);

    // 达到节点 2500
    if (nRuneRootCount >= RUNE_ROOT_NORMAL)
    {
        if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
            weapon->OnUnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

        if (itemid == RUNE_ITEMID_WARRIOR_1)
        {
            nRuneID = RUNE_ROOT_NORMAL_Warrior;  // 斩月印
            m_pOwner->IncRuneRootCount(rrrNormal, clsWarrior);
        }
        else if (itemid == RUNE_ITEMID_MAGE_1)
        {
            nRuneID = RUNE_ROOT_NORMAL_Mage;  // 雷咒印
            m_pOwner->IncRuneRootCount(rrrNormal, clsMage);
        }
        else if (itemid == RUNE_ITEMID_TAOIST_1)
        {
            nRuneID = RUNE_ROOT_NORMAL_Taoist;  // 圣兽印
            m_pOwner->IncRuneRootCount(rrrNormal, clsTaoist);
        }
        else
        {
            LOG_PROCESS_ERROR(FALSE);
        }

        // 固定卡槽1
        weapon->m_iteminfo.m_wRune[0] = nRuneID;

        if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
            weapon->OnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);
    }
    // 没到节点
    else
    {
        // 普通洗练
        if (itemid == RUNE_ITEMID_WARRIOR_1 || itemid == RUNE_ITEMID_MAGE_1 || itemid == RUNE_ITEMID_TAOIST_1)
        {
            // 脱装备
            if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
                weapon->OnUnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

            // 三职业铭文
            if (itemid == RUNE_ITEMID_WARRIOR_1)
            {
                nRuneID = CItemMgr::GetInstance().GenerateRandomRuneData(m_pOwner->GetServerGroup(), weapon, clsWarrior, m_pOwner->GetLevel(), runegroup);
                m_pOwner->IncRuneRootCount(rrrNormal, clsWarrior);
            }
            else if (itemid == RUNE_ITEMID_MAGE_1)
            {
                nRuneID = CItemMgr::GetInstance().GenerateRandomRuneData(m_pOwner->GetServerGroup(), weapon, clsMage, m_pOwner->GetLevel(), runegroup);
                m_pOwner->IncRuneRootCount(rrrNormal, clsMage);
            }
            else if (itemid == RUNE_ITEMID_TAOIST_1)
            {
                nRuneID = CItemMgr::GetInstance().GenerateRandomRuneData(m_pOwner->GetServerGroup(), weapon, clsTaoist, m_pOwner->GetLevel(), runegroup);
                m_pOwner->IncRuneRootCount(rrrNormal, clsTaoist);
            }

            // 穿装备
            if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
                weapon->OnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);
        }
        // 新手教程, 固定铭文
        else if (itemid == RUNE_ITEMID_WARRIOR_2 || itemid == RUNE_ITEMID_MAGE_2 || itemid == RUNE_ITEMID_TAOIST_2)
        {
            if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
                weapon->OnUnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

            if (itemid == RUNE_ITEMID_WARRIOR_2)
                nRuneID = 10314;
            else if (itemid == RUNE_ITEMID_MAGE_2)
                nRuneID = 25311;
            else
                nRuneID = 30011;

            weapon->m_iteminfo.m_wRune[0] = nRuneID;

            if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
                weapon->OnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);
        }
        else
        {
            LOG_PROCESS_ERROR(FALSE);
        }
    }

    // 删除物品
    DeleteItemId(itemid, 1, ITEMLOG_RUNE, FALSE, 0);

    // 扣钱
    SubMoney(MONEYTYPE_02, RUNE_ITEM_COST, MONEYLOG_RUNE, 0);
    weapon->m_iteminfo.m_dwCostMoney += RUNE_ITEM_COST;

    // 判断 当前场景是不是行会地图
    if (m_pOwner->GetScene()->GetSceneID() == m_pOwner->GetGuildID())
    {
        SubMoney(MONEYTYPE_GUILD, GUILD_RUNE_COST, MONEYLOG_INVALID, 0);
    }

    // 根据铭文ID, 获取铭文模板
    pcRuneData = CDataManager<RUNE_DATA>::GetInstance().GetData(nRuneID);
    if (pcRuneData)
    {
        // 发公告
        if (pcRuneData->nBroadCast)
        {
            char szBroadcast[1024];
            const char* pcszFormat = CGameWorld::GetInstance().GetString(essItemRuneSuccess);
            LOG_CHECK_ERROR(pcszFormat);

            if (pcszFormat)
            {
                snprintf(szBroadcast, 1024, "<#P0:<#PN:%s>><#R:%d><#T:%s>", m_pOwner->GetName(), nRuneID, pcszFormat);
            }
            else
            {
                strxcpy(szBroadcast, "cannot found essItemRuneSuccess", sizeof(szBroadcast));
            }
            m_pOwner->Say(cctGroup, cltTvShow, szBroadcast);
        }

        // 同步百晓生
        if (pcRuneData->nHandbookType != 0)
            m_pOwner->GetAchievementList().ActivateHandbook(pcRuneData->nHandbookType, pcRuneData->nHandbookIndex);
    }

    // 发包同步装备数据
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, weapon);

    // 记录日志 - 装备洗练
    if (weapon->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_RUNE,
            weapon->m_iteminfo);
    }

    // 发包同步洗练
    CCliMessageHandler::GetInstance().DoSendRuneItem(m_pOwner, errSuccess);

    // 记录日志 - 铭文物品改变
    CCliMessageHandler::GetInstance().DoDLRuneItem(
        m_pOwner->GetObjID(),
        m_pOwner->GetServerGroup(),
        m_pOwner->GetLevel(),
        weapon->m_pTemplate->m_nTemplateID,
        itemid,
        nRuneID);

    // 给玩家发送通知节点信息
    {
        if (itemid == RUNE_ITEMID_WARRIOR_1)
        {
            m_pOwner->NotifyRole_RuneRootCount(rrrNormal, clsWarrior);
        }
        else if (itemid == RUNE_ITEMID_MAGE_1)
        {
            m_pOwner->NotifyRole_RuneRootCount(rrrNormal, clsMage);
        }
        else if (itemid == RUNE_ITEMID_TAOIST_1)
        {
            m_pOwner->NotifyRole_RuneRootCount(rrrNormal, clsTaoist);
        }
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

// 高级铭文洗练
INT32 CItemBag::RuneItemAdvance(UINT8 conslot, UINT8 itemslot, INT32 itemid)
{
#ifdef _ROBOT
    return errItemUnknown;
#else

    BOOL bRet = FALSE;
    INT32 nResult = errItemUnknown;
    INT32 nRuneID = 0;
    const RUNE_DATA* pcRuneData = NULL;
    Item* weapon = GetItem(conslot, itemslot);
    INT32 runegroup = 1;
    INT32 nRuneRootCount = 0;

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(weapon, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(weapon->m_pTemplate->m_byType == ITEMTYPE_EQUIP, errItemRuneError);
    LOG_PROCESS_ERROR_RET_CODE(weapon->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_WEAPON, errItemRuneError);
    LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= RUNE_ITEM_COST_HIGH, errItemNotEnoughMoneytype02);  // 高级洗练 10万金币
    LOG_PROCESS_ERROR_RET_CODE(GetItemCount(itemid) >= 1, errItemRuneNotEnoughMaterial);
    if (m_pOwner->GetScene()->GetSceneID() == m_pOwner->GetGuildID())
    {
        LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_GUILD) >= GUILD_RUNE_COST, errGuildNotEnoughContribution);
    }

    // 两个卡槽, 如果第二卡槽为0, 那就是没有铭文, 就不能洗
    if (weapon->m_iteminfo.m_wRune[1] == 0)
        return nResult;

    // 获取节点数值
    if (itemid == RUNE_ITEMID_WARRIOR_1)
        nRuneRootCount = m_pOwner->GetRuneRootCount(rrrAdvanced, clsWarrior);
    else if (itemid == RUNE_ITEMID_MAGE_1)
        nRuneRootCount = m_pOwner->GetRuneRootCount(rrrAdvanced, clsMage);
    else if (itemid == RUNE_ITEMID_TAOIST_1)
        nRuneRootCount = m_pOwner->GetRuneRootCount(rrrAdvanced, clsTaoist);

    // 节点达到 500
    if (nRuneRootCount >= RUNE_ROOT_ADVANCED)
    {
        if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
            weapon->OnUnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

        if (itemid == RUNE_ITEMID_WARRIOR_1)
        {
            nRuneID = RUNE_ROOT_ADVANCED_Warrior;  // 神躯印
            m_pOwner->IncRuneRootCount(rrrAdvanced, clsWarrior);
        }
        else if (itemid == RUNE_ITEMID_MAGE_1)
        {
            nRuneID = RUNE_ROOT_ADVANCED_Mage;  // 火雨印
            m_pOwner->IncRuneRootCount(rrrAdvanced, clsMage);
        }
        else if (itemid == RUNE_ITEMID_TAOIST_1)
        {
            nRuneID = RUNE_ROOT_ADVANCED_Taoist;  // 夺魂印
            m_pOwner->IncRuneRootCount(rrrAdvanced, clsTaoist);
        }
        else
        {
            LOG_PROCESS_ERROR(FALSE);
        }

        // 固定卡槽2
        weapon->m_iteminfo.m_wRune[1] = nRuneID;

        if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
            weapon->OnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);
    }
    // 没到节点
    else
    {
        if (itemid == RUNE_ITEMID_WARRIOR_1 || itemid == RUNE_ITEMID_MAGE_1 || itemid == RUNE_ITEMID_TAOIST_1)
        {
            if (itemid == RUNE_ITEMID_WARRIOR_1)
            {
                nRuneID = CItemMgr::GetInstance().GenerateRandomRuneDataAdvanced(m_pOwner->GetServerGroup(), weapon, clsWarrior, m_pOwner->GetLevel(), runegroup);
                m_pOwner->IncRuneRootCount(rrrAdvanced, clsWarrior);
            }
            else if (itemid == RUNE_ITEMID_MAGE_1)
            {
                nRuneID = CItemMgr::GetInstance().GenerateRandomRuneDataAdvanced(m_pOwner->GetServerGroup(), weapon, clsMage, m_pOwner->GetLevel(), runegroup);
                m_pOwner->IncRuneRootCount(rrrAdvanced, clsMage);
            }
            else if (itemid == RUNE_ITEMID_TAOIST_1)
            {
                nRuneID = CItemMgr::GetInstance().GenerateRandomRuneDataAdvanced(m_pOwner->GetServerGroup(), weapon, clsTaoist, m_pOwner->GetLevel(), runegroup);
                m_pOwner->IncRuneRootCount(rrrAdvanced, clsTaoist);
            }
        }
        else
        {
            LOG_PROCESS_ERROR(FALSE);
        }
    }

    // 删除物品
    DeleteItemId(itemid, 1, ITEMLOG_RUNE, FALSE, 0);

    // 扣钱
    SubMoney(MONEYTYPE_02, RUNE_ITEM_COST_HIGH, MONEYLOG_RUNE, 0);
    weapon->m_iteminfo.m_dwCostMoney += RUNE_ITEM_COST_HIGH;

    // 判断 当前场景是不是行会地图
    if (m_pOwner->GetScene()->GetSceneID() == m_pOwner->GetGuildID())
    {
        SubMoney(MONEYTYPE_GUILD, GUILD_RUNE_COST, MONEYLOG_INVALID, 0);
    }

    // 高级洗练结果, 保存到临时字段上
    m_pOwner->SetRuneItemHighResult(nRuneID);

    // 发包同步 - 高级洗练结果
    CCliMessageHandler::GetInstance().DoSendRuneItemAdvance(m_pOwner, errSuccess, weapon->m_iteminfo.m_wRune[0], nRuneID);

    // 记录日志
    if (weapon->m_pTemplate->m_byLog)
    {
        // 铭文物品改变
        CCliMessageHandler::GetInstance().DoDLRuneItem(
            m_pOwner->GetObjID(),
            m_pOwner->GetServerGroup(),
            m_pOwner->GetLevel(),
            weapon->m_pTemplate->m_nTemplateID,
            itemid,
            nRuneID);
    }

    // 给玩家发送通知节点信息
    {
        if (itemid == RUNE_ITEMID_WARRIOR_1)
        {
            m_pOwner->NotifyRole_RuneRootCount(rrrAdvanced, clsWarrior);
        }
        else if (itemid == RUNE_ITEMID_MAGE_1)
        {
            m_pOwner->NotifyRole_RuneRootCount(rrrAdvanced, clsMage);
        }
        else if (itemid == RUNE_ITEMID_TAOIST_1)
        {
            m_pOwner->NotifyRole_RuneRootCount(rrrAdvanced, clsTaoist);
        }
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

// 确认高级洗练
INT32 CItemBag::RuneItemConfirm(UINT8 conslot, UINT8 itemslot)
{
    INT32 nResult = errItemUnknown;
    const EQUIP_DATA* equip_data = NULL;
    Item* weapon = GetItem(conslot, itemslot);

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(weapon, errItemNotFound);
    LOG_PROCESS_ERROR_RET_CODE(weapon->m_pTemplate->m_byType == ITEMTYPE_EQUIP, errItemRuneError);
    LOG_PROCESS_ERROR_RET_CODE(weapon->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_WEAPON, errItemRuneError);

    equip_data = (const EQUIP_DATA*)weapon->m_pTemplate;

    // 脱装备
    if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
        weapon->OnUnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

    // 覆盖铭文属性 - 固定修改第二卡槽
    if (weapon->m_iteminfo.m_wRune[1] || (weapon->m_iteminfo.m_dwCostMoney >= equip_data->m_dwSecondRuneCostMax))
    {
        weapon->m_iteminfo.m_wRune[1] = m_pOwner->GetRuneItemHighResult();
    }

    // 穿装备
    if (conslot == CONSLOT_EQUIPPED && itemslot == NES_MAIN_HAND && weapon->m_iteminfo.m_nCurDur > 0)
        weapon->OnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

    // 发包同步 - 装备数据
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, weapon);

    // 发包同步 - 确认洗练
    CCliMessageHandler::GetInstance().DoSendRuneItemConfirm(m_pOwner, errSuccess);

    // 记录日志
    if (weapon->m_pTemplate->m_byLog)
    {
        // 装备数据, 发生改变
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_RUNE,
            weapon->m_iteminfo);
    }

    return errSuccess;

Exit0:
    return nResult;
}

// 测试铭文 - 参数 铭文ID (例如: 10314)
INT32 CItemBag::RuneTest(INT32 nRuneID)
{
    INT32 nResult = errItemUnknown;

    // 默认当前佩戴的武器
    Item* weapon = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
    LOG_PROCESS_ERROR_RET_CODE(weapon, errItemNotFound);

    // 移除当前装备属性
    weapon->OnUnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

    // 铭文赋值
    weapon->m_iteminfo.m_wRune[0] = nRuneID;

    // 添加当前装备属性
    weapon->OnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

    // 发包同步装备数据
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, weapon);

    // 发包同步洗练
    CCliMessageHandler::GetInstance().DoSendRuneItem(m_pOwner, errSuccess);

Exit0:
    return nResult;
}

// 打孔
INT32 CItemBag::EquipAddSocket(INT32 nIndex)
{
    INT32 nItemID = 91115;  // 91115-打孔石
    Item* pEquip = NULL;
    INT32 nEquipSlot = -1;
    const EQUIP_DATA* equip_data = NULL;

    if (m_pOwner->IsDead() == TRUE)
        return errItemRoleDead;  // 角色处于死亡状态中

    if (m_pOwner->GetMoveState() == CMS_STALL)
        return errItemStall;  // 当前正在摆摊中

    if (m_pOwner->GetTrade()->IsTrading())
        return errItemTrading;  // 当前正在交易中

    // 11-头盔, 12-衣服, 13-腰带, 14-鞋子, 15-护肩, 16-护腕, 17-披风
    switch (nIndex)
    {
    case 11: nEquipSlot = NES_HEAD;     break;
    case 12: nEquipSlot = NES_BODY;     break;
    case 13: nEquipSlot = NES_WAIST;    break;
    case 14: nEquipSlot = NES_FOOT;     break;
    case 15: nEquipSlot = NES_SHOULDER; break;
    case 16: nEquipSlot = NES_ARM;      break;
    case 17: nEquipSlot = NES_BACK;     break;
    }

    pEquip = GetItem(CONSLOT_EQUIPPED, nEquipSlot);
    if (pEquip == NULL)
        return asetEquipIsNull;  // 装备不存在

    equip_data = (const EQUIP_DATA*)pEquip->m_pTemplate;
    if (equip_data->m_byCanSocket != 1)
        return asetEquipCantSocket;  // 该装备不能打孔

    // 获取该装备当前孔位数量
    INT32 nSocketCount = 0;
    UINT8 bySocket_0 = (pEquip->m_iteminfo.m_dwSocketCombination >> 0) & 0xFF;
    UINT8 bySocket_1 = (pEquip->m_iteminfo.m_dwSocketCombination >> 8) & 0xFF;
    if (bySocket_0 != 0)
        nSocketCount += 1;
    if (bySocket_1 != 0)
        nSocketCount += 1;

    // 判断该装备最大孔位数量
    if (nSocketCount >= equip_data->m_bySocketCountMaxNew)
        return asetEquipCantNotBeAddSocket;  // 该装备无法再继续打孔

    // 判断 打第几个孔
    INT32 nSocketSlot = 0;
    if (bySocket_0 == 0 && bySocket_1 == 0)
        nSocketSlot = 0;
    if (bySocket_0 != 0 && bySocket_1 == 0)
        nSocketSlot = 1;
    if (nSocketSlot != 0 && nSocketSlot != 1)
        return asetEquipAddSocketSlotUnknown;  // 打孔位置未知错误

    // 查找对应的材料数量
    INT32 nNeedItemCount = 0;
    if (nSocketSlot == 0)
        nNeedItemCount = equip_data->m_byFirstSocketCost;
    if (nSocketSlot == 1)
        nNeedItemCount = equip_data->m_bySecondSocketCost;
    if (nNeedItemCount == 0)
        return asetEquipNeedItemCount;  // 获取打孔材料消耗数量错误

    // 获取背包里当前材料数量
    INT32 nNowItemCount = GetItemCount(nItemID);
    if (nNowItemCount < nNeedItemCount)
        return asetEquipItemNotEnough;  // 打孔材料数量不够

    // 删除物品, 扣除材料
    DeleteItemId(nItemID, nNeedItemCount, ITEMLOG_EQUIP_ADD_SOCKET, FALSE, 0);

    // 修改孔位颜色, 打孔默认都是黄色
    pEquip->m_iteminfo.m_dwSocketCombination |= SOCKET_YELLOW << (nSocketSlot * 8);

    // 发包同步装备数据
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, pEquip);

    // 记录日志 - 装备洗练
    if (pEquip->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_EQUIP_ADD_SOCKET,
            pEquip->m_iteminfo);

        // 记录日志 - 物品孔位改变 (后期仿照这个函数参数, 新增加一个日志函数)
        //CCliMessageHandler::GetInstance().DoDLRuneItem(
        //    m_pOwner->GetObjID(),
        //    m_pOwner->GetServerGroup(),
        //    m_pOwner->GetLevel(),
        //    pEquip->m_pTemplate->m_nTemplateID,
        //    itemid,
        //    nRuneID);
    }

    return errSuccess;
}

// 雕色
INT32 CItemBag::SetSocketColor(INT32 nIndex, INT32 nTargetColor)
{
    INT32 nItemID = 91116;  // 91116-雕色石
    Item* pEquip = NULL;
    INT32 nEquipSlot = -1;
    const EQUIP_DATA* equip_data = NULL;

    INT32 nCheckSlotColor = SOCKET_NONE;  // 判断另一个孔位
    INT32 nTargetSlot = -1;  // 目标孔位下标

    if (nTargetColor < SOCKET_RED || nTargetColor > SOCKET_PURPLE)
        return ssctEquipSetColorError;  // 雕色颜色错误

    if (m_pOwner->IsDead() == TRUE)
        return errItemRoleDead;  // 角色处于死亡状态中

    if (m_pOwner->GetMoveState() == CMS_STALL)
        return errItemStall;  // 当前正在摆摊中

    if (m_pOwner->GetTrade()->IsTrading())
        return errItemTrading;  // 当前正在交易中

    // [第1孔位] => 21-头盔, 22-衣服, 23-腰带, 24-鞋子, 25-护肩, 26-护腕, 27-披风
    // [第2孔位] => 31-头盔, 32-衣服, 33-腰带, 34-鞋子, 35-护肩, 36-护腕, 37-披风
    switch (nIndex)
    {
    case 21:
    case 31:
        nEquipSlot = NES_HEAD;
        break;
    case 22:
    case 32:
        nEquipSlot = NES_BODY;
        break;
    case 23:
    case 33:
        nEquipSlot = NES_WAIST;
        break;
    case 24:
    case 34:
        nEquipSlot = NES_FOOT;
        break;
    case 25:
    case 35:
        nEquipSlot = NES_SHOULDER;
        break;
    case 26:
    case 36:
        nEquipSlot = NES_ARM;
        break;
    case 27:
    case 37:
        nEquipSlot = NES_BACK;
        break;
    }

    pEquip = GetItem(CONSLOT_EQUIPPED, nEquipSlot);
    if (pEquip == NULL)
        return ssctEquipIsNull;  // 装备不存在

    equip_data = (const EQUIP_DATA*)pEquip->m_pTemplate;
    if (equip_data->m_byCanSocket != 1)
        return ssctEquipCantSetColor;  // 装备不能雕色

    UINT8 bySocketColor_0 = (pEquip->m_iteminfo.m_dwSocketCombination >> 0) & 0xFF;
    UINT8 bySocketColor_1 = (pEquip->m_iteminfo.m_dwSocketCombination >> 8) & 0xFF;

    // 获取 消耗材料数量
    INT32 nNeedItemCount = 0;

    // 给第1孔位雕色
    if (nIndex >= 21 && nIndex <= 27)
    {
        if (bySocketColor_0 == SOCKET_NONE)
            return ssctEquipNoSocket1;  // 目标孔位1不存在

        // 判断 第2孔位
        if (bySocketColor_1 == SOCKET_NONE)
            nCheckSlotColor = SOCKET_YELLOW;    // 按黄色判断
        else
            nCheckSlotColor = bySocketColor_1;  // 第2孔位 存在

        nTargetSlot = 0;

        nNeedItemCount = GetSetSocketColorCost(nTargetColor, nCheckSlotColor);
    }
    // 给第2孔位雕色
    else if (nIndex >= 31 && nIndex <= 37)
    {
        if (bySocketColor_0 == SOCKET_NONE)
            return ssctEquipNoSocket1;  // 目标孔位1不存在

        if (bySocketColor_1 == SOCKET_NONE)
            return ssctEquipNoSocket2;  // 目标孔位2不存在

        nCheckSlotColor = bySocketColor_0;   // 判断 第1孔位颜色

        nTargetSlot = 1;

        nNeedItemCount = GetSetSocketColorCost(nTargetColor, nCheckSlotColor);
    }

    if (nNeedItemCount == 0)
        return ssctEquipNeedItemCount;  // 获取打孔材料消耗数量错误
    if (nTargetSlot == -1)
        return ssctEquipSetSlotError;  // 目标孔位错误

    // 获取背包里当前材料数量
    INT32 nNowItemCount = GetItemCount(nItemID);
    if (nNowItemCount < nNeedItemCount)
        return ssctEquipItemNotEnough;  // 雕色材料数量不够

    WRN("Slot now 0-[%d], 1-[%d], nColor %d, nTargetSlot %d, nNeedItemCount %d",
        bySocketColor_0, bySocketColor_1, nTargetColor, nTargetSlot, nNeedItemCount);

    // 删除物品, 扣除材料
    DeleteItemId(nItemID, nNeedItemCount, ITEMLOG_EQUIP_SET_COLOR, FALSE, 0);

    // 修改孔位颜色 (注意不能无脑 [|=], 这样只会叠加数值, 需要先清除, 再写入)
    pEquip->m_iteminfo.m_dwSocketCombination &= ~(0xFF << (nTargetSlot * 8));  // 先清除原数值
    pEquip->m_iteminfo.m_dwSocketCombination |= nTargetColor << (nTargetSlot * 8);   // 再把新数值写入

    // 发包同步装备数据
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, pEquip);

    // 记录日志 - 装备洗练
    if (pEquip->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_EQUIP_SET_COLOR,
            pEquip->m_iteminfo);

        // 记录日志 - 物品雕色改变 (后期仿照这个函数参数, 新增加一个日志函数)
        //CCliMessageHandler::GetInstance().DoDLRuneItem(
        //    m_pOwner->GetObjID(),
        //    m_pOwner->GetServerGroup(),
        //    m_pOwner->GetLevel(),
        //    pEquip->m_pTemplate->m_nTemplateID,
        //    itemid,
        //    nRuneID);
    }

    return errSuccess;
}

INT32 CItemBag::GetSetSocketColorCost(int targetID, int CheckID)
{
    const static std::vector<std::vector<int>> vecSetSocketColor =
    {
        // 列号 下标0是ID列 不计入, 下标1-5 分别对应 红1/黄2/蓝3/绿3/紫5
        // 修改数据, 把 红绿蓝 改成一样的消耗
        { 1, 235, 50, 70,  135, 55 },     // ID=1, SOCKET_RED
        { 2, 10,  10, 10,  10,  10 },     // ID=2, SOCKET_YELLOW
        { 3, 60,  50, 235,  85,  45 },    // ID=3, SOCKET_BLUE
        { 4, 160, 50, 120, 235, 75 },     // ID=4, SOCKET_GREEN
        { 5, 40,  10, 40,  35,  35 },     // ID=5, SOCKET_PURPLE

        // 原版数据
        //{ 1, 110, 25, 70,  135, 55 },    // ID=1, SOCKET_RED
        //{ 2, 10,  10, 10,  10,  10 },    // ID=2, SOCKET_YELLOW
        //{ 3, 60,  15, 70,  85,  45 },    // ID=3, SOCKET_BLUE
        //{ 4, 160, 50, 120, 235, 75 },    // ID=4, SOCKET_GREEN
        //{ 5, 40,  10, 40,  35,  35 },    // ID=5, SOCKET_PURPLE
    };

    // 先按行ID找 通过目标颜色数值 找到对应的行, 再按列 找到当前颜色数值的列, 交汇点就是消耗数值
    // 原版例子
    // 假设 当前2个孔都是[黄色], 想把其中一个 改成[蓝色]
    // 现在2个孔位 [1黄1黄], 目标颜色行 [蓝色]是第3行, 当前孔位颜色 [黄色]是第2列, 交汇点数值是 15
    // 现在2个孔位 [1黄1蓝], 再继续把[黄色]孔 改成[绿色], 目标颜色行 [绿色]是第4行, 当前孔位颜色 [黄色]是第2列, 交汇点数值是 50
    // 现在2个孔位 [1绿1蓝], 再继续把[蓝色]孔 改成[红色], 目标颜色行 [红色]是第1行, 当前孔位颜色 [蓝色]是第3列, 交汇点数值是 70
    for (const auto& row : vecSetSocketColor)
    {
        if (row[0] == targetID) // 每行的第一个元素是ID
        {
            if (CheckID >= 1 && CheckID < row.size())
            {
                return row[CheckID];  // 直接返回对应列的值
            }
            break;
        }
    }
    return 0;  // 未找到
}

// 获得命运武器
INT32 CItemBag::AddDestinyWeapon(INT32 nItemID, INT32 nLevel)
{
    INT32 nResult = errItemUnknown;

    Item* item = CItemMgr::GetInstance().GenerateItem(nItemID, 1);
    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(item->m_pTemplate);

    nResult = AddItem(item, ITEMLOG_ADD_DESTINY_WEAPON, 2000024);
    if (nResult != errSuccess)
    {
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
        LOG_CHECK_ERROR(bItemRet);
    }

    // 升级武器
    if (nLevel > 0)
    {
        nResult = EquipLevelUpToSpecifiedLevel(item, nLevel);
    }

Exit0:
    return nResult;
}

// 装备升级到指定顶级
INT32 CItemBag::EquipLevelUpToSpecifiedLevel(Item* item, INT32 nLevel)
{
    INT32 nResult = errItemUnknown;

    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);  // 必须是装备类型

    switch (item->m_pTemplate->m_nTemplateID)
    {
    case 99900030:  // 命运之刃
        item->m_iteminfo.m_byLevelupPhyPoint = nLevel;
        break;
    case 99900046:  // 命运之杖
        item->m_iteminfo.m_byLevelupMagPoint = nLevel;
        break;
    case 99900047:  // 命运之幡
        item->m_iteminfo.m_byLevelupTaoPoint = nLevel;
        break;
    }

    item->m_iteminfo.m_byLevelupTimes = nLevel;
    item->m_iteminfo.m_byIdentified = IDENTIFY_TYPE_YES;
    item->m_iteminfo.m_byLevelupTypeHidden = 0;
    item->m_iteminfo.m_byLevelupPointHidden = 0;

#ifndef _ROBOT
    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);
    CCliMessageHandler::GetInstance().DoSendWeaponLevelUpResult(m_pOwner, 1);

    if (item->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_EQUIP_LEVELUP_SUCCEEDED,
            item->m_iteminfo);
    }
#endif

Exit0:
    return nResult;
}

// 升级武器
INT32 CItemBag::WeaponLevelUpPutIn()
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else

    INT32 nResult = errItemUnknown;
    INT32 dur_list[64];     //MAX_CONTAINER_SIZE[CONSLOT_DEFAULT]
    INT32 nItemCount = 0;   //黑铁总数
    INT32 CCount = 0;       //黑铁的有效计数
    INT32 nDura = 0;        // 黑铁矿石总纯度
    INT32 nPhyMin = 0;
    INT32 nPhyMax = 0;
    INT32 nMagMin = 0;
    INT32 nMagMax = 0;
    INT32 nTaoMin = 0;
    INT32 nTaoMax = 0;

    Item* weapon = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);

    CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);  // NPC未找到

    nResult = m_pOwner->CanInteract(npc);
    PROCESS_ERROR(nResult == errSuccess);

    LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractWeaponLevelUpPutIn, errNpcNoSuchFunction);   // Npc没有此功能
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);                    // 摆摊中
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);                     // 交易中
    LOG_PROCESS_ERROR_RET_CODE(weapon, errItemNotFound);                                                // 物品不存在
    LOG_PROCESS_ERROR_RET_CODE(weapon->m_iteminfo.m_nMaxDur > 2 * EQUIP_DUR_MULTIPLIER, errItemDurLow); // 耐久度过低
    LOG_PROCESS_ERROR_RET_CODE(weapon->m_pTemplate->m_byType == ITEMTYPE_EQUIP &&                       // 
        weapon->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_WEAPON, errItemCannotLevelup);            // 不可升级

    LOG_PROCESS_ERROR_RET_CODE(m_WeaponItem == NULL, errItemLevelUpInProcess);  // 炼刀中

    // 未鉴定
    if (weapon->m_iteminfo.m_byIdentified == IDENTIFY_TYPE_NO)
        nResult = errItemNotIdentified;

    // 已鉴定，等待试刀
    if (weapon->m_iteminfo.m_byIdentified == IDENTIFY_TYPE_LEVEL_UP)
        nResult = errItemWeaponNotTried;

    // 已鉴定
    LOG_PROCESS_ERROR(weapon->m_iteminfo.m_byIdentified == IDENTIFY_TYPE_YES);

    // 金币不足 10000
    LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= WEAPON_LEVEL_UP_COST, errItemNotEnoughMoneytype02);

    // 没有黑铁 - 至少要1个黑铁
    LOG_PROCESS_ERROR_RET_CODE(
        SearchDefaultContainer(ITEMTYPE_MATERIAL, ITEMSUBTYPE_MATERIAL_WEAPON_LEVELUP, 1) != INVALID_ITEM_SLOT, errItemNotEnoughBlackIron);

    //计算开始，以下内容从舒工提供代码翻译而来
    for (ConIt it = m_cons[CONSLOT_DEFAULT].begin(); it != m_cons[CONSLOT_DEFAULT].end();)
    {
        Item* item = it->second;

        //黑铁
        if (item->m_pTemplate->m_byType == ITEMTYPE_MATERIAL &&
            item->m_pTemplate->m_bySubType == ITEMSUBTYPE_MATERIAL_WEAPON_LEVELUP)
        {
            dur_list[nItemCount++] = item->m_pTemplate->m_nDur;

            CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, CONSLOT_DEFAULT, it->first);

            BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
            LOG_CHECK_ERROR(bItemRet);

            m_cons[CONSLOT_DEFAULT].erase(it++);
        }
        //首饰
        else if (item->m_pTemplate->m_byType == ITEMTYPE_EQUIP)
        {
            if (item->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_NECKLACE ||
                item->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_RING ||
                item->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_BRACELET)
            {
                const EQUIP_DATA* equip_data = (const EQUIP_DATA*)item->m_pTemplate;

                INT32 phy = equip_data->m_nFixAttr[0] + equip_data->m_nFixAttr[1];
                INT32 mag = equip_data->m_nFixAttr[2] + equip_data->m_nFixAttr[3];
                INT32 tao = equip_data->m_nFixAttr[4] + equip_data->m_nFixAttr[5];

                if (item->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_BRACELET)
                {
                    ++phy;
                    ++mag;
                    ++tao;
                }

                if (nPhyMin < phy)
                {
                    nPhyMax = nPhyMin;
                    nPhyMin = phy;
                }
                else if (nPhyMax < phy)
                {
                    nPhyMax = phy;
                }

                if (nMagMin < mag)
                {
                    nMagMax = nMagMin;
                    nMagMin = mag;
                }
                else if (nMagMax < mag)
                {
                    nMagMax = mag;
                }

                if (nTaoMin < tao)
                {
                    nTaoMax = nTaoMin;
                    nTaoMin = tao;
                }
                else if (nTaoMax < tao)
                {
                    nTaoMax = tao;
                }

                CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, CONSLOT_DEFAULT, it->first);

                BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
                LOG_CHECK_ERROR(bItemRet);

                m_cons[CONSLOT_DEFAULT].erase(it++);
            }
        }
        else
            ++it;
    }

    LOG_PROCESS_ERROR(nItemCount > 0);

    // 判断黑铁数量
    if (nItemCount > 5)
    {
        // 把黑铁矿石 按纯度排序, 从大到小 
        // (原代码是 std::greater<UINT16>(), 现在修改 UINT16 => INT32)
        std::sort(dur_list, dur_list + nItemCount, std::greater<INT32>());
        nItemCount = 6;
        CCount = 5;
    }
    else
    {
        CCount = nItemCount;
    }

    // 只取纯度前6个矿石
    for (INT32 i = 0; i < nItemCount; i++)
    {
        nDura += dur_list[i];
    }

    //注：原始算式：Round(CCount + CCount * ((nDura / nItemCount) / 5.0));
    m_nWeaponDur = round_div(CCount * nItemCount * 5 + CCount * nDura, nItemCount * 5);
    m_nWeaponPhy = round_div(nPhyMin, 5) + nPhyMin + round_div(nPhyMax, 3);
    m_nWeaponMag = round_div(nMagMin, 5) + nMagMin + round_div(nMagMax, 3);
    m_nWeaponTao = round_div(nTaoMin, 5) + nTaoMin + round_div(nTaoMax, 3);

    //计算到此结束
#ifdef _DEBUG
    char debug_string[1024];
    snprintf(debug_string, 1024, "PutIn: dur=%d, phy=%d, mag=%d, tao=%d",
        m_nWeaponDur, m_nWeaponPhy, m_nWeaponMag, m_nWeaponTao);
    m_pOwner->Say(cctScreen, cltNormal, debug_string);
#endif

    // 扣钱
    SubMoney(MONEYTYPE_02, WEAPON_LEVEL_UP_COST, MONEYLOG_EQUIP_LEVELUP, 0);
    weapon->m_iteminfo.m_dwCostMoney += WEAPON_LEVEL_UP_COST;

    // 删除武器, 但是不删除对象
    nResult = RemoveItem(CONSLOT_EQUIPPED, NES_MAIN_HAND, ITEMLOG_EQUIP_LEVELUP);
    LOG_CHECK_ERROR(nResult == errSuccess);

    // 设置pos
    weapon->SetPos(CONSLOT_WEAPON_LEVEL_UP, 0);

    m_WeaponItem = weapon;
    m_dwWeaponLevelUpStartTime = CGameWorld::GetInstance().GetGameTime();
    m_byMailNotified = 0;

    CCliMessageHandler::GetInstance().DoSendWeaponLevelUpPutIn(m_pOwner);

    CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, CONSLOT_EQUIPPED, NES_MAIN_HAND);

    CCliMessageHandler::GetInstance().DoSyncRoleAvatar(m_pOwner, CONSLOT_EQUIPPED, NES_MAIN_HAND, 0, 0);

    if (weapon->m_pTemplate->m_byLog)
    {
        CCliMessageHandler::GetInstance().DoDLChangeItem(
            m_pOwner->GetServerGroup(),
            m_pOwner->GetObjID(),
            ITEMLOG_EQUIP_LEVELUP,
            weapon->m_iteminfo);
    }

    return errSuccess;

Exit0:
    return nResult;
#endif
}

// 取回武器 (等2小时)
INT32 CItemBag::WeaponLevelUpTakeOut()
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else

    INT32 nResult = errItemUnknown;
    INT32 AbilCode = -1;
    UINT32 factor = 0;
    CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    nResult = m_pOwner->CanInteract(npc);
    PROCESS_ERROR(nResult == errSuccess);

    LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractWeaponLevelUpTakeOut, errNpcNoSuchFunction); // Npc没有此功能
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);                    // 摆摊中
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);                     // 交易中
    PROCESS_ERROR_RET_CODE(m_WeaponItem, errItemNoLevelUp);                                             // 没有正在炼刀的武器

    LOG_PROCESS_ERROR(m_WeaponItem->m_pTemplate->m_byType == ITEMTYPE_EQUIP &&                          // 
        m_WeaponItem->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_WEAPON);                            // 

    LOG_PROCESS_ERROR(m_WeaponItem->m_iteminfo.m_byIdentified == IDENTIFY_TYPE_YES);                    // 已鉴定

    PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);                          // 包裹已满

    // 时间还没到
    if (CGameWorld::GetInstance().GetGameTime() - m_dwWeaponLevelUpStartTime < WEAPON_LEVEL_UP_TIME)
    {
#ifndef _ROBOT
        m_pOwner->ErrorCodeNotify(errItemLevelUpNotFinished,
            WEAPON_LEVEL_UP_TIME - (CGameWorld::GetInstance().GetGameTime() - m_dwWeaponLevelUpStartTime), 0);
#endif
        return errSuccess;
    }

    // 计算开始，以下内容从舒工提供代码翻译而来
    {
        // 计算耐久度 - 新代码
        if (m_nWeaponDur >= 0 && m_nWeaponDur <= 8)
        {
            // 低纯度惩罚区 - 直接扣除 4点最大耐久
            if (m_WeaponItem->m_iteminfo.m_nMaxDur > 4 * EQUIP_DUR_MULTIPLIER)
                m_WeaponItem->m_iteminfo.m_nMaxDur -= 4 * EQUIP_DUR_MULTIPLIER;
            else
                m_WeaponItem->m_iteminfo.m_nMaxDur = (INT16)round_div(m_WeaponItem->m_iteminfo.m_nMaxDur, 2);

            if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
                m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
        }
        else if (m_nWeaponDur >= 9 && m_nWeaponDur <= 15)
        {
            // 中低等纯度区 - 概率性小幅度损失 3点最大耐久
            if (g_Random(m_nWeaponDur) < 6)
            {
                if (m_WeaponItem->m_iteminfo.m_nMaxDur > 3 * EQUIP_DUR_MULTIPLIER)
                    m_WeaponItem->m_iteminfo.m_nMaxDur -= 3 * EQUIP_DUR_MULTIPLIER;

                if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
                    m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
            }
        }
        else if (m_nWeaponDur >= 16 && m_nWeaponDur <= 24)
        {
            // 中等纯度区 - 概率性小幅度损失 2点最大耐久
            if (g_Random(m_nWeaponDur) < 6)
            {
                if (m_WeaponItem->m_iteminfo.m_nMaxDur > 2 * EQUIP_DUR_MULTIPLIER)
                    m_WeaponItem->m_iteminfo.m_nMaxDur -= 2 * EQUIP_DUR_MULTIPLIER;

                if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
                    m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
            }
        }
        else if (m_nWeaponDur >= 25 && m_nWeaponDur <= 29)
        {
            // 高纯度区 - 概率性小幅度损失 1点最大耐久
            if (g_Random(m_nWeaponDur) < 6)
            {
                if (m_WeaponItem->m_iteminfo.m_nMaxDur > 1 * EQUIP_DUR_MULTIPLIER)
                    m_WeaponItem->m_iteminfo.m_nMaxDur -= 1 * EQUIP_DUR_MULTIPLIER;

                if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
                    m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
            }
        }
        else if (m_nWeaponDur >= 30 && m_nWeaponDur <= 255)
        {
            // 极高纯度区 - 完全不损失耐久 (6个纯度26 或者 6个纯度25)
        }

        // 计算耐久度 - 原版默认代码, 设计的数值区间不合理
        //if (m_nWeaponDur >= 0 && m_nWeaponDur <= 8)
        //{
        //    if (m_WeaponItem->m_iteminfo.m_nMaxDur > 3 * EQUIP_DUR_MULTIPLIER)
        //        m_WeaponItem->m_iteminfo.m_nMaxDur -= 3 * EQUIP_DUR_MULTIPLIER;
        //    else
        //        m_WeaponItem->m_iteminfo.m_nMaxDur = (INT16)round_div(m_WeaponItem->m_iteminfo.m_nMaxDur, 2);
        //
        //    if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
        //        m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
        //}
        //else if (m_nWeaponDur >= 9 && m_nWeaponDur <= 15)
        //{
        //    if (g_Random(m_nWeaponDur) < 6)
        //    {
        //        if (m_WeaponItem->m_iteminfo.m_nMaxDur > EQUIP_DUR_MULTIPLIER)
        //            m_WeaponItem->m_iteminfo.m_nMaxDur -= EQUIP_DUR_MULTIPLIER;
        //
        //        if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
        //            m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
        //    }
        //}
        //else if (m_nWeaponDur >= 18 && m_nWeaponDur <= 255)
        //{
        //    INT32 random_number = g_Random(m_nWeaponDur);
        //
        //    if (random_number >= 0 && random_number <= 4)
        //        if (m_WeaponItem->m_iteminfo.m_nMaxDur > EQUIP_DUR_MULTIPLIER)
        //            m_WeaponItem->m_iteminfo.m_nMaxDur -= EQUIP_DUR_MULTIPLIER;
        //
        //    if (random_number >= 5 && random_number <= 7)
        //        if (m_WeaponItem->m_iteminfo.m_nMaxDur > 2 * EQUIP_DUR_MULTIPLIER)
        //            m_WeaponItem->m_iteminfo.m_nMaxDur -= 2 * EQUIP_DUR_MULTIPLIER;
        //
        //    if (random_number >= 8 && random_number <= 255)
        //        if (m_WeaponItem->m_iteminfo.m_nMaxDur > 4 * EQUIP_DUR_MULTIPLIER)
        //            m_WeaponItem->m_iteminfo.m_nMaxDur -= 4 * EQUIP_DUR_MULTIPLIER;
        //
        //    if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
        //        m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
        //}
    }

    //计算增加的属性
    //注：下面这段代码有问题，AbilCode 其实根本没起作用，本着连bug也要一致的指导思想，直接照抄未作修改
    m_WeaponItem->m_iteminfo.m_byIdentified = IDENTIFY_TYPE_LEVEL_UP;

    if (m_WeaponItem->m_iteminfo.m_byLevelupTimes < 255)
        m_WeaponItem->m_iteminfo.m_byLevelupTimes++;

    if (m_nWeaponPhy == m_nWeaponMag && m_nWeaponPhy == m_nWeaponTao)
        AbilCode = g_Random(3);

    if ((m_nWeaponPhy >= m_nWeaponMag && m_nWeaponPhy >= m_nWeaponTao) || AbilCode == 0)
    {
        //factor = _Min(85, _Min(11, m_nWeaponPhy) * 7 + 10 + m_WeaponItem->m_iteminfo.m_byLuck);  // 原代码不合理
        factor = _Min(85, _Min(11, m_nWeaponPhy) * 7 + 10) + m_WeaponItem->m_iteminfo.m_byLuck;  // 新代码 - 把幸运单独拿出来加
        if (g_Random(130) < factor)
        {
            m_WeaponItem->m_iteminfo.m_byLevelupTypeHidden = 1;
            m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 1;
            if (factor > 63 && g_Random(30) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 2;
            if (factor > 79 && g_Random(200) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 3;
        }
    }

    if ((m_nWeaponMag >= m_nWeaponPhy && m_nWeaponMag >= m_nWeaponTao) || AbilCode == 1)
    {
        //factor = _Min(85, _Min(11, m_nWeaponMag) * 7 + 10 + m_WeaponItem->m_iteminfo.m_byLuck);  // 原代码不合理
        factor = _Min(85, _Min(11, m_nWeaponMag) * 7 + 10) + m_WeaponItem->m_iteminfo.m_byLuck;  // 新代码 - 把幸运单独拿出来加
        if (g_Random(130) < factor)
        {
            m_WeaponItem->m_iteminfo.m_byLevelupTypeHidden = 2;
            m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 1;
            if (factor > 63 && g_Random(30) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 2;
            if (factor > 79 && g_Random(200) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 3;
        }
    }

    if ((m_nWeaponPhy >= m_nWeaponMag && m_nWeaponTao >= m_nWeaponPhy) || AbilCode == 2)
    {
        //factor = _Min(85, _Min(11, m_nWeaponTao) * 7 + 10 + m_WeaponItem->m_iteminfo.m_byLuck);  // 原代码不合理
        factor = _Min(85, _Min(11, m_nWeaponTao) * 7 + 10) + m_WeaponItem->m_iteminfo.m_byLuck;  // 新代码 - 把幸运单独拿出来加
        if (g_Random(130) < factor)
        {
            m_WeaponItem->m_iteminfo.m_byLevelupTypeHidden = 3;
            m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 1;
            if (factor > 63 && g_Random(30) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 2;
            if (factor > 79 && g_Random(200) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 3;
        }
    }
    //计算到此结束

#ifdef _DEBUG
#ifndef _ROBOT
    char debug_string[1024];
    char result_string[4][4] =
    {
        "n/a",
        "phy",
        "mag",
        "tao"
    };
    snprintf(debug_string, 1024, "TakeOut: factor=%d, result=%s+%d",
        factor,
        result_string[m_WeaponItem->m_iteminfo.m_byLevelupTypeHidden],
        m_WeaponItem->m_iteminfo.m_byLevelupPointHidden);
    m_pOwner->Say(cctScreen, cltNormal, debug_string);
#endif
#endif

    CCliMessageHandler::GetInstance().DoSendWeaponLevelUpTakeOut(m_pOwner);

    nResult = AddItem(m_WeaponItem, ITEMLOG_EQUIP_LEVELUP, 0);
    LOG_PROCESS_ERROR(nResult == errSuccess);

    m_WeaponItem = NULL;
    m_dwWeaponLevelUpStartTime = 0;
    m_nWeaponDur = 0;
    m_nWeaponPhy = 0;
    m_nWeaponMag = 0;
    m_nWeaponTao = 0;

    return errSuccess;

Exit0:
    return nResult;
#endif
}

// 立即取回 (花费10万金币)
INT32 CItemBag::WeaponLevelUpTakeOutImmediately()
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else

    INT32 nResult = errItemUnknown;
    INT32 AbilCode = -1;
    UINT32 factor = 0;
    CNpc* npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    nResult = m_pOwner->CanInteract(npc);
    PROCESS_ERROR(nResult == errSuccess);

    PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= 100000, errItemNotEnoughMoneytype02);
    LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractWeaponLevelUpTakeOut, errNpcNoSuchFunction);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    PROCESS_ERROR_RET_CODE(m_WeaponItem, errItemNoLevelUp);
    LOG_PROCESS_ERROR(m_WeaponItem->m_pTemplate->m_byType == ITEMTYPE_EQUIP && m_WeaponItem->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_WEAPON);
    LOG_PROCESS_ERROR(m_WeaponItem->m_iteminfo.m_byIdentified == IDENTIFY_TYPE_YES);
    PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);

    // 扣除金币
    nResult = SubMoney(MONEYTYPE_02, 100000, MONEYLOG_EQUIP_LEVELUP_TAKE_OUT_IMMEDIATELY, 0);
    LOG_PROCESS_ERROR(nResult == errSuccess);

    // 计算开始，以下内容从舒工提供代码翻译而来
    {
        // 计算耐久度 - 新代码
        if (m_nWeaponDur >= 0 && m_nWeaponDur <= 8)
        {
            // 低纯度惩罚区 - 直接扣除 4点最大耐久
            if (m_WeaponItem->m_iteminfo.m_nMaxDur > 4 * EQUIP_DUR_MULTIPLIER)
                m_WeaponItem->m_iteminfo.m_nMaxDur -= 4 * EQUIP_DUR_MULTIPLIER;
            else
                m_WeaponItem->m_iteminfo.m_nMaxDur = (INT16)round_div(m_WeaponItem->m_iteminfo.m_nMaxDur, 2);

            if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
                m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
        }
        else if (m_nWeaponDur >= 9 && m_nWeaponDur <= 15)
        {
            // 中低等纯度区 - 概率性小幅度损失 3点最大耐久
            if (g_Random(m_nWeaponDur) < 6)
            {
                if (m_WeaponItem->m_iteminfo.m_nMaxDur > 3 * EQUIP_DUR_MULTIPLIER)
                    m_WeaponItem->m_iteminfo.m_nMaxDur -= 3 * EQUIP_DUR_MULTIPLIER;

                if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
                    m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
            }
        }
        else if (m_nWeaponDur >= 16 && m_nWeaponDur <= 24)
        {
            // 中等纯度区 - 概率性小幅度损失 2点最大耐久
            if (g_Random(m_nWeaponDur) < 6)
            {
                if (m_WeaponItem->m_iteminfo.m_nMaxDur > 2 * EQUIP_DUR_MULTIPLIER)
                    m_WeaponItem->m_iteminfo.m_nMaxDur -= 2 * EQUIP_DUR_MULTIPLIER;

                if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
                    m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
            }
        }
        else if (m_nWeaponDur >= 25 && m_nWeaponDur <= 29)
        {
            // 高纯度区 - 概率性小幅度损失 1点最大耐久
            if (g_Random(m_nWeaponDur) < 6)
            {
                if (m_WeaponItem->m_iteminfo.m_nMaxDur > 1 * EQUIP_DUR_MULTIPLIER)
                    m_WeaponItem->m_iteminfo.m_nMaxDur -= 1 * EQUIP_DUR_MULTIPLIER;

                if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
                    m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
            }
        }
        else if (m_nWeaponDur >= 30 && m_nWeaponDur <= 255)
        {
            // 极高纯度区 - 完全不损失耐久 (6个纯度26 或者 6个纯度25)
        }

        // 计算耐久度 - 原版默认代码, 设计的数值区间不合理
        //if (m_nWeaponDur >= 0 && m_nWeaponDur <= 8)
        //{
        //    if (m_WeaponItem->m_iteminfo.m_nMaxDur > 3 * EQUIP_DUR_MULTIPLIER)
        //        m_WeaponItem->m_iteminfo.m_nMaxDur -= 3 * EQUIP_DUR_MULTIPLIER;
        //    else
        //        m_WeaponItem->m_iteminfo.m_nMaxDur = (INT16)round_div(m_WeaponItem->m_iteminfo.m_nMaxDur, 2);
        //
        //    if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
        //        m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
        //}
        //else if (m_nWeaponDur >= 9 && m_nWeaponDur <= 15)
        //{
        //    if (g_Random(m_nWeaponDur) < 6)
        //    {
        //        if (m_WeaponItem->m_iteminfo.m_nMaxDur > EQUIP_DUR_MULTIPLIER)
        //            m_WeaponItem->m_iteminfo.m_nMaxDur -= EQUIP_DUR_MULTIPLIER;
        //
        //        if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
        //            m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
        //    }
        //}
        //else if (m_nWeaponDur >= 18 && m_nWeaponDur <= 255)
        //{
        //    INT32 random_number = g_Random(m_nWeaponDur);
        //
        //    if (random_number >= 0 && random_number <= 4)
        //        if (m_WeaponItem->m_iteminfo.m_nMaxDur > EQUIP_DUR_MULTIPLIER)
        //            m_WeaponItem->m_iteminfo.m_nMaxDur -= EQUIP_DUR_MULTIPLIER;
        //
        //    if (random_number >= 5 && random_number <= 7)
        //        if (m_WeaponItem->m_iteminfo.m_nMaxDur > 2 * EQUIP_DUR_MULTIPLIER)
        //            m_WeaponItem->m_iteminfo.m_nMaxDur -= 2 * EQUIP_DUR_MULTIPLIER;
        //
        //    if (random_number >= 8 && random_number <= 255)
        //        if (m_WeaponItem->m_iteminfo.m_nMaxDur > 4 * EQUIP_DUR_MULTIPLIER)
        //            m_WeaponItem->m_iteminfo.m_nMaxDur -= 4 * EQUIP_DUR_MULTIPLIER;
        //
        //    if (m_WeaponItem->m_iteminfo.m_nCurDur > m_WeaponItem->m_iteminfo.m_nMaxDur)
        //        m_WeaponItem->m_iteminfo.m_nCurDur = m_WeaponItem->m_iteminfo.m_nMaxDur;
        //}
    }

    //计算增加的属性
    //注：下面这段代码有问题，AbilCode其实根本没起作用，本着连bug也要一致的指导思想，直接照抄未作修改
    m_WeaponItem->m_iteminfo.m_byIdentified = IDENTIFY_TYPE_LEVEL_UP;
    if (m_WeaponItem->m_iteminfo.m_byLevelupTimes < 255)
        m_WeaponItem->m_iteminfo.m_byLevelupTimes++;

    // 3种属性相同, 就随机一种
    if (m_nWeaponPhy == m_nWeaponMag && m_nWeaponPhy == m_nWeaponTao)
        AbilCode = g_Random(3);

    // 攻击属性, 同时大于 魔法/道术
    if ((m_nWeaponPhy >= m_nWeaponMag && m_nWeaponPhy >= m_nWeaponTao) || AbilCode == 0)
    {
        //factor = _Min(85, _Min(11, m_nWeaponPhy) * 7 + 10 + m_WeaponItem->m_iteminfo.m_byLuck);  // 原代码不合理
        factor = _Min(85, _Min(11, m_nWeaponPhy) * 7 + 10) + m_WeaponItem->m_iteminfo.m_byLuck;  // 新代码 - 把幸运单独拿出来加
        if (g_Random(130) < factor)
        {
            m_WeaponItem->m_iteminfo.m_byLevelupTypeHidden = 1;
            m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 1;

            // 判断 是否增加隐藏属性
            if (factor > 63 && g_Random(30) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 2;
            if (factor > 79 && g_Random(200) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 3;
        }
    }

    // 魔法属性, 同时大于 攻击/道术
    if ((m_nWeaponMag >= m_nWeaponPhy && m_nWeaponMag >= m_nWeaponTao) || AbilCode == 1)
    {
        //factor = _Min(85, _Min(11, m_nWeaponMag) * 7 + 10 + m_WeaponItem->m_iteminfo.m_byLuck);  // 原代码不合理
        factor = _Min(85, _Min(11, m_nWeaponMag) * 7 + 10) + m_WeaponItem->m_iteminfo.m_byLuck;  // 新代码 - 把幸运单独拿出来加
        if (g_Random(130) < factor)
        {
            m_WeaponItem->m_iteminfo.m_byLevelupTypeHidden = 2;
            m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 1;

            // 判断 是否增加隐藏属性
            if (factor > 63 && g_Random(30) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 2;
            if (factor > 79 && g_Random(200) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 3;
        }
    }

    // 道术属性 (攻击 > 魔法 && 道术 > 攻击)
    if ((m_nWeaponPhy >= m_nWeaponMag && m_nWeaponTao >= m_nWeaponPhy) || AbilCode == 2)
    {
        //factor = _Min(85, _Min(11, m_nWeaponTao) * 7 + 10 + m_WeaponItem->m_iteminfo.m_byLuck);  // 原代码不合理
        factor = _Min(85, _Min(11, m_nWeaponTao) * 7 + 10) + m_WeaponItem->m_iteminfo.m_byLuck;  // 新代码 - 把幸运单独拿出来加
        if (g_Random(130) < factor)
        {
            m_WeaponItem->m_iteminfo.m_byLevelupTypeHidden = 3;
            m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 1;

            // 判断 是否增加隐藏属性
            if (factor > 63 && g_Random(30) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 2;
            if (factor > 79 && g_Random(200) == 0)
                m_WeaponItem->m_iteminfo.m_byLevelupPointHidden = 3;
        }
    }
    //计算到此结束

#ifdef _DEBUG
#ifndef _ROBOT
    char debug_string[1024];
    char result_string[4][4] =
    {
        "n/a",
        "phy",
        "mag",
        "tao"
    };
    snprintf(debug_string, 1024, "TakeOut: factor=%d, result=%s+%d",
        factor,
        result_string[m_WeaponItem->m_iteminfo.m_byLevelupTypeHidden],
        m_WeaponItem->m_iteminfo.m_byLevelupPointHidden);
    m_pOwner->Say(cctScreen, cltNormal, debug_string);
#endif
#endif

    CCliMessageHandler::GetInstance().DoSendWeaponLevelUpTakeOut(m_pOwner);

    nResult = AddItem(m_WeaponItem, ITEMLOG_EQUIP_LEVELUP, 0);
    LOG_PROCESS_ERROR(nResult == errSuccess);

    m_WeaponItem = NULL;
    m_dwWeaponLevelUpStartTime = 0;
    m_nWeaponDur = 0;
    m_nWeaponPhy = 0;
    m_nWeaponMag = 0;
    m_nWeaponTao = 0;

    return errSuccess;

Exit0:
    return nResult;
#endif
}

// 试刀
void CItemBag::OnPhyAttack()
{
    Item* weapon = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);

    if (weapon && weapon->m_iteminfo.m_byIdentified == IDENTIFY_TYPE_LEVEL_UP)
    {
        // 计算 升级点数总和
        INT32 nTotalPoint = weapon->m_iteminfo.m_byLevelupPhyPoint + weapon->m_iteminfo.m_byLevelupMagPoint + weapon->m_iteminfo.m_byLevelupTaoPoint;

        // 点数总和 最大为7, 隐藏属性点 1-3点, 没有隐藏点 就是升级失败
        if (nTotalPoint >= 7 ||
            weapon->m_iteminfo.m_byLevelupTypeHidden < 1 ||
            weapon->m_iteminfo.m_byLevelupTypeHidden > 3)
        {
            // 升级失败 删除物品数据
            DeleteItemPos(CONSLOT_EQUIPPED, NES_MAIN_HAND, 1, ITEMLOG_EQUIP_LEVELUP_FAILED, 0);

#ifndef _ROBOT
            CCliMessageHandler::GetInstance().DoSendWeaponLevelUpResult(m_pOwner, 0);
#endif
            return;
        }

        if (weapon->m_iteminfo.m_nCurDur > 0)
            weapon->OnUnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

        // 升级点数
        switch (weapon->m_iteminfo.m_byLevelupTypeHidden)
        {
        case 1:
            weapon->m_iteminfo.m_byLevelupPhyPoint += weapon->m_iteminfo.m_byLevelupPointHidden;
            break;
        case 2:
            weapon->m_iteminfo.m_byLevelupMagPoint += weapon->m_iteminfo.m_byLevelupPointHidden;
            break;
        case 3:
            weapon->m_iteminfo.m_byLevelupTaoPoint += weapon->m_iteminfo.m_byLevelupPointHidden;
            break;
        default:
            LOG_PROCESS_ERROR(FALSE);
        }

        // 穿上装备
        if (weapon->m_iteminfo.m_nCurDur > 0)
            weapon->OnEquip(m_pOwner, m_refine_levels[NES_MAIN_HAND], m_pOwner->GetClass(), NES_MAIN_HAND);

        weapon->m_iteminfo.m_byIdentified = IDENTIFY_TYPE_YES;
        weapon->m_iteminfo.m_byLevelupTypeHidden = 0;
        weapon->m_iteminfo.m_byLevelupPointHidden = 0;

#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, weapon);
        CCliMessageHandler::GetInstance().DoSendWeaponLevelUpResult(m_pOwner, 1);

        if (weapon->m_pTemplate->m_byLog)
        {
            CCliMessageHandler::GetInstance().DoDLChangeItem(
                m_pOwner->GetServerGroup(),
                m_pOwner->GetObjID(),
                ITEMLOG_EQUIP_LEVELUP_SUCCEEDED,
                weapon->m_iteminfo);
        }
#endif
    }

Exit0:
    return;
}

// 分解
INT32 CItemBag::Decompose(UINT8 conslot, UINT8 itemslot)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else

    INT32 nResult = errItemUnknown;
    Item* item = GetItem(conslot, itemslot);
    INT32 original_itemid = 0;
    const DECOMPOSE_DATA* de_data = NULL;
    INT32 total_count = 0;
    INT32 itemid[MAX_DECOMPOSE_ITEM_COUNT], itemcount[MAX_DECOMPOSE_ITEM_COUNT];
    memset(itemid, 0, sizeof(itemid));
    memset(itemcount, 0, sizeof(itemcount));

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(_CheckValidItemPos(conslot, itemslot), errItemInvalidPos);
    LOG_PROCESS_ERROR_RET_CODE(item, errItemNotFound);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP || item->m_pTemplate->m_byType == ITEMTYPE_SPELLBOOK);
    LOG_PROCESS_ERROR_RET_CODE(((const EQUIP_DATA*)(item->m_pTemplate))->m_nCanDecompose, errItemCannotDecompose);
    LOG_PROCESS_ERROR(conslot == CONSLOT_DEFAULT);
    LOG_PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) >= MAX_DECOMPOSE_ITEM_COUNT - 1, errItemBagFull);

    de_data = CDataManager<DECOMPOSE_DATA>::GetInstance().GetData(item->m_iteminfo.m_nTemplateID);
    LOG_PROCESS_ERROR(de_data);

    CStatistic::GetInstance().OnDecomposeItem(m_pOwner, item->m_pTemplate->m_byColor, 1);

    original_itemid = item->m_pTemplate->m_nTemplateID;
    DeleteItemPos(conslot, itemslot, 1, ITEMLOG_DECOMPOSE, 0);

    for (UINT8 i = 0; i < MAX_DECOMPOSE_ITEM_COUNT; i++)
    {
        DropContent drop_content = { 0 };

        CDropGenerator::GetInstance().GenerateDropContentFromDropChanceData(
            m_pOwner->GetServerGroup(), de_data->m_data + i, drop_content, RATE_MAX);

        if (drop_content.m_type == DropContent::DROP_MONEY)
        {
            itemid[total_count] = drop_content.m_money.moneytype;
            itemcount[total_count++] = drop_content.m_money.count;
            AddMoney(drop_content.m_money.moneytype, drop_content.m_money.count, MONEYLOG_DECOMPOSE, 0);
        }
        else if (drop_content.m_type == DropContent::DROP_ITEM)
        {
            itemid[total_count] = drop_content.m_item->m_pTemplate->m_nTemplateID;
            itemcount[total_count++] = drop_content.m_item->m_pTemplate->m_byDurType == DURTYPE_STACK ? drop_content.m_item->m_iteminfo.m_nCurDur : 1;
            INT32 nRetCode = AddItem(drop_content.m_item, ITEMLOG_DECOMPOSE, 0);
            if (nRetCode != errSuccess)
            {
                BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(drop_content.m_item);
                LOG_CHECK_ERROR(bItemRet);
                LOG_CHECK_ERROR(FALSE);
            }
        }
    }

    CCliMessageHandler::GetInstance().DoSendDecomposeResult(m_pOwner, errSuccess, original_itemid, itemid, itemcount);

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

// 合成
INT32 CItemBag::Compose(INT32 formulaid)
{
#ifdef _ROBOT
    // TODO
    return errItemUnknown;
#else

    INT32 nResult = errItemUnknown;
    const COMPOSE_DATA* co_data = NULL;
    const ITEM_DATA* item_data = NULL;
    BOOL is_double = FALSE;

    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    LOG_PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) >= 2, errItemBagFull);
    LOG_PROCESS_ERROR(formulaid > 0);

    co_data = CDataManager<COMPOSE_DATA>::GetInstance().GetData(formulaid);
    LOG_PROCESS_ERROR(co_data);

    item_data = GetItemData(co_data->m_nItemID);
    LOG_PROCESS_ERROR(item_data);

    if (co_data->m_nMoney > 0)
        LOG_PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= co_data->m_nMoney, errItemNotEnoughMoneytype02);

    for (UINT8 i = 0; i < MAX_COMPOSE_ITEM_COUNT; i++)
    {
        if (co_data->m_nRequireItemID[i] > 0 && co_data->m_nRequireItemCount[i] > 0)
            LOG_PROCESS_ERROR_RET_CODE(GetItemCount(co_data->m_nRequireItemID[i]) >= co_data->m_nRequireItemCount[i], errItemComposeError);
    }

    if (co_data->m_nMoney > 0)
    {
        nResult = SubMoney(MONEYTYPE_02, co_data->m_nMoney, MONEYLOG_COMPOSE, 0);
        LOG_PROCESS_ERROR(nResult == errSuccess);
    }

    for (UINT8 i = 0; i < MAX_COMPOSE_ITEM_COUNT; i++)
    {
        if (co_data->m_nRequireItemID[i] > 0 && co_data->m_nRequireItemCount[i] > 0)
        {
            nResult = DeleteItemId(co_data->m_nRequireItemID[i], co_data->m_nRequireItemCount[i], ITEMLOG_COMPOSE, FALSE, 0);
            LOG_PROCESS_ERROR(nResult == errSuccess);
        }
    }

    AddItem(co_data->m_nItemID, 1, ITEMLOG_COMPOSE, 0, FALSE);

    if (g_Random(RATE_MAX) < co_data->m_dwDoubleRate)
    {
        is_double = TRUE;
        AddItem(co_data->m_nItemID, 1, ITEMLOG_COMPOSE, 0, FALSE);
        CCliMessageHandler::GetInstance().DoSendComposeResult(m_pOwner, 2, co_data->m_nItemID);
    }
    else
    {
        CCliMessageHandler::GetInstance().DoSendComposeResult(m_pOwner, 1, co_data->m_nItemID);
    }

    CStatistic::GetInstance().OnComposeItem(m_pOwner, item_data->m_byColor, 1);

    //全服广播
    if (co_data->m_nBroadCast)
    {
        char szBroadcast[1024];
        const char* pcszFormat = NULL;
        if (is_double)
            pcszFormat = CGameWorld::GetInstance().GetString(essItemComposeSuccessDouble);
        else
            pcszFormat = CGameWorld::GetInstance().GetString(essItemComposeSuccess);
        LOG_CHECK_ERROR(pcszFormat);

        if (pcszFormat)
        {
            snprintf(szBroadcast, 1024, "<#P0:<#PN:%s>><#P1:%d><#T:%s>", m_pOwner->GetName(), item_data->m_nTemplateID, pcszFormat);
        }
        else
        {
            strxcpy(szBroadcast, "cannot found essItemComposeSuccess/essItemComposeSuccessDouble", sizeof(szBroadcast));
        }
        m_pOwner->Say(cctGroup, cltTvShow, szBroadcast);
    }

    return errSuccess;

Exit0:
    return nResult;

#endif // _ROBOT
}

void CItemBag::OpenHeroContainers(void)
{
#ifndef _ROBOT
    m_con_sizes[CONSLOT_HERO_EQUIPPED] = MAX_CONTAINER_SIZE[CONSLOT_HERO_EQUIPPED];
    m_con_sizes[CONSLOT_HERO_EQUIPMENT] = MAX_CONTAINER_SIZE[CONSLOT_HERO_EQUIPMENT];

    if (!m_pOwner->IsLoading())
    {
        CCliMessageHandler::GetInstance().DoSendContainerSizeChange(m_pOwner, CONSLOT_HERO_EQUIPPED, m_con_sizes[CONSLOT_HERO_EQUIPPED]);
        CCliMessageHandler::GetInstance().DoSendContainerSizeChange(m_pOwner, CONSLOT_HERO_EQUIPMENT, m_con_sizes[CONSLOT_HERO_EQUIPMENT]);
    }

#endif // _ROBOT
}

void CItemBag::ApplyHeroEquipments(void)
{
#ifndef _ROBOT
    CHero* poHero = m_pOwner->GetHero();
    LOG_PROCESS_ERROR(poHero);

    for (Container::iterator itr = m_cons[CONSLOT_HERO_EQUIPPED].begin(); itr != m_cons[CONSLOT_HERO_EQUIPPED].end(); ++itr)
    {
        Item* item = itr->second;
        LOG_PROCESS_ERROR(item);

        item->OnEquip(poHero, 0, 0, 0);
    }

Exit0:
    return;

#endif // _ROBOT
}

void CItemBag::CloseHeroContainers(void)
{
#ifndef _ROBOT
    m_con_sizes[CONSLOT_HERO_EQUIPPED] = 0;
    m_con_sizes[CONSLOT_HERO_EQUIPMENT] = 0;

    if (!m_pOwner->IsLoading())
    {
        CCliMessageHandler::GetInstance().DoSendContainerSizeChange(m_pOwner, CONSLOT_HERO_EQUIPPED, m_con_sizes[CONSLOT_HERO_EQUIPPED]);
        CCliMessageHandler::GetInstance().DoSendContainerSizeChange(m_pOwner, CONSLOT_HERO_EQUIPMENT, m_con_sizes[CONSLOT_HERO_EQUIPMENT]);
    }

#endif // _ROBOT
}

INT32 CItemBag::GetSetItemCountBefore(const SET_DATA* data, INT32 itemid, UINT8 itemslot)
{
    INT32 set_item_count = 0;

    for (INT32 i = 0; i < MAX_SET_PART_COUNT && data->m_nItemID[i]; i++)
    {
        if (itemid == data->m_nItemID[i])
        {
            set_item_count++;
            continue;
        }
        for (ConIt it = m_cons[CONSLOT_EQUIPPED].begin(); it != m_cons[CONSLOT_EQUIPPED].end(); ++it)
        {
            if (it->first != itemslot && it->second->m_pTemplate->m_nTemplateID == data->m_nItemID[i] && it->second->m_iteminfo.m_nCurDur > 0)
            {
                set_item_count++;
                break;
            }

        }
    }

    return set_item_count;
}

INT32 CItemBag::GetSetItemCountAfter(const SET_DATA* data)
{
    INT32 set_item_count = 0;

    for (INT32 i = 0; i < MAX_SET_PART_COUNT && data->m_nItemID[i]; i++)
    {
        for (ConIt it = m_cons[CONSLOT_EQUIPPED].begin(); it != m_cons[CONSLOT_EQUIPPED].end(); ++it)
        {
            if (it->second->m_pTemplate->m_nTemplateID == data->m_nItemID[i] && it->second->m_iteminfo.m_nCurDur > 0)
            {
                set_item_count++;
                break;
            }
        }
    }

    return set_item_count;
}

UINT8 _GetFxFromLevel(UINT16 l)
{
    if (l >= g_GWConfig.shRefineFxLevel2)
        return 2;
    if (l >= g_GWConfig.shRefineFxLevel1)
        return 1;
    return 0;
}

UINT8 CItemBag::GetRefineFx()
{
    Item* weapon = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
    if (weapon)
        return weapon->m_iteminfo.m_byLevelupPhyPoint +
        weapon->m_iteminfo.m_byLevelupMagPoint +
        weapon->m_iteminfo.m_byLevelupTaoPoint;
    else
        return 0;
}

INT32 CItemBag::GetPow()
{
    INT32 p = 0;
    std::map<const SET_DATA*, INT32> set_count;
    UINT16 equip_slot = 0;

    for (ConIt it = m_cons[CONSLOT_EQUIPPED].begin(); it != m_cons[CONSLOT_EQUIPPED].end(); it++)
    {
        Item* item = it->second;
        const EQUIP_DATA* equip_data = (const EQUIP_DATA*)item->m_pTemplate;

        //装备本身的战斗力
        p += _GetPow(item);

        //套装计数，后面统一计算套装属性的战斗力
        if (equip_data->m_SetData)
            set_count[equip_data->m_SetData]++;

        //强化的战斗力
        equip_slot = it->first;
        LOG_PROCESS_ERROR(equip_slot < NES_TOTAL);
        if (m_refine_levels[equip_slot])
        {
            const REFINE_ATTR_DATA* refine_attr_data = CDataManager<REFINE_ATTR_DATA>::GetInstance().GetData(
                REFINE_ATTR_DATA::MakeKey(m_refine_levels[equip_slot], m_pOwner->GetClass(), equip_slot));
            if (refine_attr_data)
            {
                for (UINT8 i = 0; i < MAX_REFINE_ATTR_COUNT; i++)
                {
                    if (refine_attr_data->m_nAttrID[i])
                    {
                        const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(refine_attr_data->m_nAttrID[i]);
                        if (attr_data)
                        {
                            p += attr_data->m_nPow;
                        }
                    }
                }
            }
        }
    }

    //统一计算套装战斗力
    for (std::map<const SET_DATA*, INT32>::iterator it = set_count.begin(); it != set_count.end(); it++)
    {
        const SET_DATA* set_data = it->first;
        for (UINT8 i = 0; i < MAX_SET_ATTR_COUNT; i++)
        {
            if (set_data->m_nCount[i] && it->second >= set_data->m_nCount[i] && set_data->m_pAttrData[i])
            {
                p += set_data->m_pAttrData[i]->m_nPow;
            }
        }
    }

Exit0:
    return p;
}

UINT8 CItemBag::SearchDefaultContainer(INT32 itemid, INT16 dur) const
{
    for (Container::const_iterator it = m_cons[CONSLOT_DEFAULT].begin(); it != m_cons[CONSLOT_DEFAULT].end(); ++it)
    {
        if (it->second->m_pTemplate->m_nTemplateID == itemid && it->second->m_iteminfo.m_nCurDur >= dur)
        {
            return it->first;
        }
    }
    return INVALID_ITEM_SLOT;
}

UINT8 CItemBag::SearchDefaultContainer(UINT8 itemtype, UINT8 itemsubtype, INT16 dur) const
{
    for (Container::const_iterator it = m_cons[CONSLOT_DEFAULT].begin(); it != m_cons[CONSLOT_DEFAULT].end(); ++it)
    {
        if (it->second->m_pTemplate->m_byType == itemtype &&
            it->second->m_pTemplate->m_bySubType == itemsubtype &&
            it->second->m_iteminfo.m_nCurDur >= dur)
        {
            return it->first;
        }
    }
    return INVALID_ITEM_SLOT;
}

BOOL CItemBag::LoseItemDur(INT32 itemid, INT16 dur, EItemLog reason)
{
    Item* item = NULL;
    Container::const_iterator it;

    LOG_PROCESS_ERROR(dur > 0);

    for (it = m_cons[CONSLOT_DEFAULT].begin(); it != m_cons[CONSLOT_DEFAULT].end(); ++it)
    {
        if (it->second->m_pTemplate->m_nTemplateID == itemid && it->second->m_iteminfo.m_nCurDur >= dur)
        {
            item = it->second;
            break;
        }
    }
    PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(
        item->m_pTemplate->m_byDurType == DURTYPE_STACK ||
        item->m_pTemplate->m_byDurType == DURTYPE_USE ||
        item->m_pTemplate->m_byDurType == DURTYPE_NONE);
    LOG_PROCESS_ERROR(item->m_iteminfo.m_nCurDur >= dur);

    _LoseDur(item, dur, reason);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CItemBag::LoseItemDur(UINT8 conslot, UINT8 itemslot, INT16 dur, EItemLog reason)
{
    Item* item = GetItem(conslot, itemslot);
    PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(dur > 0);

    LOG_PROCESS_ERROR(
        item->m_pTemplate->m_byDurType == DURTYPE_EQUIP ||
        item->m_pTemplate->m_byDurType == DURTYPE_STACK ||
        item->m_pTemplate->m_byDurType == DURTYPE_USE ||
        item->m_pTemplate->m_byDurType == DURTYPE_NONE);
    PROCESS_ERROR(item->m_iteminfo.m_nCurDur >= dur);

    _LoseDur(item, dur, reason);

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CItemBag::LoseItemDur(UINT8 conslot, UINT8 itemslot, INT32 itemid, INT16 dur, EItemLog reason)
{
    Item* item = GetItem(conslot, itemslot);
    PROCESS_ERROR(item);
    PROCESS_ERROR(item->m_iteminfo.m_nTemplateID == itemid);
    LOG_PROCESS_ERROR(dur > 0);

    LOG_PROCESS_ERROR(
        item->m_pTemplate->m_byDurType == DURTYPE_EQUIP ||
        item->m_pTemplate->m_byDurType == DURTYPE_STACK ||
        item->m_pTemplate->m_byDurType == DURTYPE_USE ||
        item->m_pTemplate->m_byDurType == DURTYPE_NONE);
    PROCESS_ERROR(item->m_iteminfo.m_nCurDur > 0);

    _LoseDur(item, dur, reason);

    return TRUE;
Exit0:
    return FALSE;
}

void CItemBag::UpdateBlackMarketLimit()
{
    UINT32 cur_time = CGameWorld::GetInstance().GetGameTime();

    for (std::map<INT32, BMRoleLimitInfo>::iterator it = m_black_market_limit_map.begin(); it != m_black_market_limit_map.end();)
    {
        if (it->second.dwNextRefreshTime <= cur_time)
            m_black_market_limit_map.erase(it++);
        else
            ++it;
    }
}

INT32 CItemBag::DecreaseBlackMarketLimit(const BLACK_MARKET_DATA* data)
{
    std::map<INT32, BMRoleLimitInfo>::iterator it;
    LOG_PROCESS_ERROR(data);
    LOG_PROCESS_ERROR(data->nLimitType == ebmltRole);
    LOG_PROCESS_ERROR(data->nLimit > 0);

    it = m_black_market_limit_map.find(data->nBMProductID);
    if (it == m_black_market_limit_map.end())
    {
        m_black_market_limit_map[data->nBMProductID].nCount = data->nLimit - 1;
        m_black_market_limit_map[data->nBMProductID].dwNextRefreshTime = CGameWorld::GetInstance().GetGameTime() + data->dwRefreshTime;
    }
    else
    {
        LOG_PROCESS_ERROR(m_black_market_limit_map[data->nBMProductID].nCount > 0);
        m_black_market_limit_map[data->nBMProductID].nCount--;
    }

    return m_black_market_limit_map[data->nBMProductID].nCount;

Exit0:
    return 0;
}

void CItemBag::UpdateBlackMarketCooldown()
{
    UINT32 cur_time = CGameWorld::GetInstance().GetGameTime();

    for (std::map<INT32, UINT32>::iterator it = m_black_market_cooldown_map.begin(); it != m_black_market_cooldown_map.end();)
    {
        if (it->second <= cur_time)
            m_black_market_cooldown_map.erase(it++);
        else
            ++it;
    }
}

INT32 CItemBag::OnBlackMarketBuy(INT32 productid)
{
    INT32 nResult = errItemUnknown;
    INT32 interact_result = errItemUnknown;
    BOOL bRet = FALSE;
    INT32 res;
    const BLACK_MARKET_DATA* data = NULL;
    const ITEM_DATA* item_data = NULL;
    CNpc* npc = NULL;
    INT32 left_count = 0;

    LOG_PROCESS_ERROR(productid);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->IsDead(), errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);

    data = CDataManager<BLACK_MARKET_DATA>::GetInstance().GetData(productid);
    LOG_PROCESS_ERROR(data);

    item_data = GetItemData(data->nItemID);
    LOG_PROCESS_ERROR(item_data);

    npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    interact_result = m_pOwner->CanInteract(npc);
    PROCESS_ERROR_RET_CODE(interact_result == errSuccess, interact_result);

    PROCESS_ERROR_RET_CODE(data->nBMID == npc->GetNpcData()->nBlackMarketID, errItemBlackMarketNotFound);

    PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);
    PROCESS_ERROR_RET_CODE(_GetBagWeight() + item_data->m_nWeight <= m_pOwner->GetAttr(catBagWeightLmt), errItemBagTooHeavy);
    PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= data->nPrice, errItemNotEnoughMoneytype02);

    if (data->dwCooldownTime)
    {
        UpdateBlackMarketCooldown();
        PROCESS_ERROR_RET_CODE(m_black_market_cooldown_map.find(productid) == m_black_market_cooldown_map.end(), errItemBlackMarketCooldown);
    }

    if (data->nLimitType == ebmltServer)
    {
#ifndef _ROBOT
        bRet = CCliMessageHandler::GetInstance().DoMSCheckBlackMarketProduct(m_pOwner->GetObjID(), productid);
        LOG_PROCESS_ERROR(bRet);
#endif // _ROBOT
        return errSuccess;
    }
    else if (data->nLimitType == ebmltRole)
    {
        UpdateBlackMarketLimit();
        std::map<INT32, BMRoleLimitInfo>::iterator it = m_black_market_limit_map.find(productid);
        PROCESS_ERROR_RET_CODE(it == m_black_market_limit_map.end() || it->second.nCount > 0, errItemBlackMarketSold);
    }

    if (data->dwCooldownTime)
    {
        m_black_market_cooldown_map[productid] = CGameWorld::GetInstance().GetGameTime() + data->dwCooldownTime;
    }

    if (data->nLimitType == ebmltRole)
    {
        left_count = DecreaseBlackMarketLimit(data);
    }

    res = SubMoney(MONEYTYPE_02, data->nPrice, MONEYLOG_BLACK_MARKET, 0);
    LOG_PROCESS_ERROR_RET_CODE(res == errSuccess, res);

    res = AddItem(data->nItemID, 1, ITEMLOG_BLACK_MARKET, 0, FALSE);
    LOG_PROCESS_ERROR_RET_CODE(res == errSuccess, res);

#ifndef _ROBOT
    CCliMessageHandler::GetInstance().DoBlackMarketBuy(m_pOwner, productid, left_count);
#endif

    return errSuccess;

Exit0:
    return nResult;
}

INT32 CItemBag::OnMsBlackMarketBuy(INT32 productid, INT32 count)
{
    INT32 nResult = errItemUnknown;
    INT32 interact_result = errItemUnknown;
    INT32 res;
    const BLACK_MARKET_DATA* data = NULL;
    const ITEM_DATA* item_data = NULL;
    CNpc* npc = NULL;

    LOG_PROCESS_ERROR(productid);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->IsDead(), errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);

    data = CDataManager<BLACK_MARKET_DATA>::GetInstance().GetData(productid);
    LOG_PROCESS_ERROR(data);
    LOG_PROCESS_ERROR(data->nLimitType == ebmltServer);

    item_data = GetItemData(data->nItemID);
    LOG_PROCESS_ERROR(item_data);

    npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    interact_result = m_pOwner->CanInteract(npc);
    PROCESS_ERROR_RET_CODE(interact_result == errSuccess, interact_result);

    PROCESS_ERROR_RET_CODE(data->nBMID == npc->GetNpcData()->nBlackMarketID, errItemBlackMarketNotFound);

    PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);
    PROCESS_ERROR_RET_CODE(_GetBagWeight() + item_data->m_nWeight <= m_pOwner->GetAttr(catBagWeightLmt), errItemBagTooHeavy);
    PROCESS_ERROR_RET_CODE(GetMoney(MONEYTYPE_02) >= data->nPrice, errItemNotEnoughMoneytype02);

    if (data->dwCooldownTime)
    {
        m_black_market_cooldown_map[productid] = CGameWorld::GetInstance().GetGameTime() + data->dwCooldownTime;
    }

    res = SubMoney(MONEYTYPE_02, data->nPrice, MONEYLOG_BLACK_MARKET, 0);
    LOG_PROCESS_ERROR_RET_CODE(res == errSuccess, res);

    res = AddItem(data->nItemID, 1, ITEMLOG_BLACK_MARKET, 0, FALSE);
    LOG_PROCESS_ERROR_RET_CODE(res == errSuccess, res);

#ifndef _ROBOT
    CCliMessageHandler::GetInstance().DoBlackMarketBuy(m_pOwner, productid, count);
#endif

    return errSuccess;

Exit0:
    return nResult;
}

// 应该已经废弃了
INT32 CItemBag::Gamble(UINT8 equiptype)
{
    INT32 nResult = errItemUnknown;
    const GAMBLE_DATA* data = NULL;
    CNpc* npc = NULL;
    DropContent content;
    const DROP_GROUP_DATA* drop_group_data = NULL;
    BOOL bRet;

    LOG_PROCESS_ERROR(equiptype != ITEMSUBTYPE_INVALID);

    data = CDataManager<GAMBLE_DATA>::GetInstance().GetData(equiptype);
    LOG_PROCESS_ERROR(data);

    npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    nResult = m_pOwner->CanInteract(npc);
    PROCESS_ERROR(nResult == errSuccess);

    LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractGamble, errNpcNoSuchFunction);

    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->IsDead(), errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);
    PROCESS_ERROR_RET_CODE(GetItemCount(data->nCostItemID) >= data->nCostItemCount, errItemNotEnough);

    //drop_group_data = CDropManager::GetInstance().GetData(data->nDropGroupID);
    drop_group_data = CDropManager::GetInstance().GetData(data->NormalDrop.nDropGroupID);
    LOG_PROCESS_ERROR(drop_group_data);

    DeleteItemId(data->nCostItemID, data->nCostItemCount, ITEMLOG_GAMBLE, FALSE, 0);

#ifndef _ROBOT
    //if (g_Random(RATE_MAX) < data->nSuccessRate)
    if (g_Random(RATE_MAX) < data->NormalDrop.nDropChance)
    {
        CCliMessageHandler::GetInstance().DoGamble(m_pOwner, 0, 0);
        return errSuccess;
    }
#endif

    bRet = CDropGenerator::GetInstance().GenerateDropContentFromDropGroupData(m_pOwner->GetServerGroup(), drop_group_data, content);
    if (bRet)
    {
        LOG_PROCESS_ERROR(content.m_type == DropContent::DROP_ITEM);
        LOG_PROCESS_ERROR(content.m_item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);
        LOG_PROCESS_ERROR(content.m_item->m_pTemplate->m_bySubType == equiptype);

        CItemMgr::GetInstance().GenerateRandomAttributes(content.m_item, data->nRandomAttrFactor);
        //CItemMgr::GetInstance().GenerateRandomSockets(content.m_item, data->nSocketFactor);

        INT32 itemid = content.m_item->m_iteminfo.m_nTemplateID;
        INT32 nRetCode = AddItem(content.m_item, ITEMLOG_GAMBLE, 0);

        LOG_PROCESS_ERROR(nRetCode == errSuccess);

#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoGamble(m_pOwner, 1, itemid);
#endif
    }
    else
    {
#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoGamble(m_pOwner, 0, 0);
#endif
    }

    return errSuccess;

Exit0:
    return nResult;
}

// 装备重铸
INT32 CItemBag::GambleAdvance(INT32 nGambleType, INT32 nGambleLevel)
{
    INT32 nResult = errItemUnknown;

    const GAMBLE_DATA* data = NULL;
    CNpc* npc = NULL;
    DropContent content;
    const DROP_GROUP_DATA* drop_group_data = NULL;
    BOOL bRet;

    INT32 tmpGambleType = ITEMSUBTYPE_INVALID;
    switch (nGambleType)
    {
    case egtEquipWeapon:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_WEAPON;
        break;
    }
    case egtEquipHat:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_HAT;
        break;
    }
    case egtEquipShoulderArmor:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_SHOULDER_ARMOR;
        break;
    }
    case egtEquipChestArmor:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_CHEST_ARMOR;
        break;
    }
    case egtEquipWristArmor:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_WRIST_ARMOR;
        break;
    }
    case egtEquipBelt:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_BELT;
        break;
    }
    case egtEquipShoes:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_SHOES;
        break;
    }
    case egtEquipCloak:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_CLOAK;
        break;
    }
    case egtEquipNecklace:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_NECKLACE;
        break;
    }
    case egtEquipRing:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_RING;
        break;
    }
    case egtEquipBracelet:
    {
        tmpGambleType = ITEMSUBTYPE_EQUIP_BRACELET;
        break;
    }
    case egtInvalid:
    {
        tmpGambleType = ITEMSUBTYPE_INVALID;
        break;
    }
    default:
    {
        tmpGambleType = ITEMSUBTYPE_INVALID;
        break;
    }
    }

    LOG_PROCESS_ERROR(tmpGambleType != ITEMSUBTYPE_INVALID);

    data = CDataManager<GAMBLE_DATA>::GetInstance().GetData(nGambleType << 16 | nGambleLevel);
    LOG_PROCESS_ERROR(data);

    npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    nResult = m_pOwner->CanInteract(npc);
    PROCESS_ERROR(nResult == errSuccess);

    LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractGamble, errNpcNoSuchFunction);

    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->IsDead(), errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);
    PROCESS_ERROR_RET_CODE(GetItemCount(data->nCostItemID) >= data->nCostItemCount, errItemNotEnough);

    drop_group_data = CDropManager::GetInstance().GetData(data->NormalDrop.nDropGroupID);
    LOG_PROCESS_ERROR(drop_group_data);

    DeleteItemId(data->nCostItemID, data->nCostItemCount, ITEMLOG_GAMBLE, FALSE, 0);

#ifndef _ROBOT
    //if (g_Random(RATE_MAX) < data->NormalDrop.nDropChance)
    if (g_Random(RATE_MAX * 100) < data->NormalDrop.nDropChance)
    {
        CCliMessageHandler::GetInstance().DoGamble(m_pOwner, 0, 0);
        return errSuccess;
    }
#endif

    bRet = CDropGenerator::GetInstance().GenerateDropContentFromDropGroupData(m_pOwner->GetServerGroup(), drop_group_data, content);
    if (bRet)
    {
        LOG_PROCESS_ERROR(content.m_type == DropContent::DROP_ITEM);
        LOG_PROCESS_ERROR(content.m_item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);
        LOG_PROCESS_ERROR(content.m_item->m_pTemplate->m_bySubType == tmpGambleType);

        CItemMgr::GetInstance().GenerateRandomAttributes(content.m_item, data->nRandomAttrFactor);
        //CItemMgr::GetInstance().GenerateRandomSockets(content.m_item, data->nSocketFactor);

        INT32 itemid = content.m_item->m_iteminfo.m_nTemplateID;
        INT32 nRetCode = AddItem(content.m_item, ITEMLOG_GAMBLE, 0);

        LOG_PROCESS_ERROR(nRetCode == errSuccess);

#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoGamble(m_pOwner, 1, itemid);
#endif
    }
    else
    {
#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoGamble(m_pOwner, 0, 0);
#endif
    }

    return errSuccess;

Exit0:
    return nResult;
}

// 技能书重著
INT32 CItemBag::SpellBookGamble()
{
    INT32 nResult = errItemUnknown;

    const GAMBLE_DATA* data = NULL;
    CNpc* npc = NULL;
    DropContent content;
    const DROP_GROUP_DATA* drop_group_data = NULL;
    BOOL bRet;

    data = CDataManager<GAMBLE_DATA>::GetInstance().GetData(egtSpellBook << 16 | 0);
    LOG_PROCESS_ERROR(data);

    npc = CGameWorld::GetInstance().FindNpc(m_pOwner->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    nResult = m_pOwner->CanInteract(npc);
    PROCESS_ERROR(nResult == errSuccess);

    LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractSpellBookGamble, errNpcNoSuchFunction);

    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->IsDead(), errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(m_pOwner->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!m_pOwner->GetTrade()->IsTrading(), errItemTrading);
    PROCESS_ERROR_RET_CODE(GetFreeSlots(CONSLOT_DEFAULT) > 0, errItemBagFull);
    PROCESS_ERROR_RET_CODE(GetItemCount(data->nCostItemID) >= data->nCostItemCount, errItemNotEnough);

    drop_group_data = CDropManager::GetInstance().GetData(data->NormalDrop.nDropGroupID);
    LOG_PROCESS_ERROR(drop_group_data);

    DeleteItemId(data->nCostItemID, data->nCostItemCount, ITEMLOG_SPELL_BOOK_GAMBLE, FALSE, 0);

#ifndef _ROBOT
    if (g_Random(RATE_MAX * 100) < data->NormalDrop.nDropChance)
    {
        CCliMessageHandler::GetInstance().DoSpellBookGamble(m_pOwner, 0, 0);
        return errSuccess;
    }
#endif

    bRet = CDropGenerator::GetInstance().GenerateDropContentFromDropGroupData(m_pOwner->GetServerGroup(), drop_group_data, content);
    if (bRet)
    {
        LOG_PROCESS_ERROR(content.m_type == DropContent::DROP_ITEM);
        LOG_PROCESS_ERROR(content.m_item->m_pTemplate->m_byType == ITEMTYPE_SPELLBOOK);
        LOG_PROCESS_ERROR(content.m_item->m_pTemplate->m_bySubType == ITEMSUBTYPE_SPELLBOOK_PLAYER);

        INT32 itemid = content.m_item->m_iteminfo.m_nTemplateID;
        INT32 nRetCode = AddItem(content.m_item, ITEMLOG_SPELL_BOOK_GAMBLE, 0);

        LOG_PROCESS_ERROR(nRetCode == errSuccess);

#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoSpellBookGamble(m_pOwner, 1, itemid);
#endif
    }
    else
    {
#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoSpellBookGamble(m_pOwner, 0, 0);
#endif
    }

    return errSuccess;

Exit0:
    return nResult;
}

BOOL CItemBag::CheckTemplateIDIsTimeCard(INT32 nTemplateID)
{
    for (auto id : g_ServerConfig.CC.nCustomGameTimeCardTemplateID)
    {
        if (id == nTemplateID)
        {
            return TRUE;
        }
    }
    return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//private:

INT32 CItemBag::AddItemToContainer(Item* item, UINT8 conslot, EItemLog reason, UINT64 userdefine)
{
    INT32 nResult = errItemUnknown;
    BOOL delete_item = FALSE;
    Container& container = m_cons[conslot];

    if (conslot == CONSLOT_DEFAULT &&
        (reason == ITEMLOG_LOOT || reason == ITEMLOG_SHOP || reason == ITEMLOG_BUY_BACK))
    {
        if (_GetBagWeight() + item->GetWeight() > m_pOwner->GetAttr(catBagWeightLmt))
            return errItemBagTooHeavy;
    }

    if (item->m_pTemplate->m_byDurType == DURTYPE_STACK)
    {
        //如果物品可堆叠，则尝试堆叠到相同物品上
        for (ConIt it = container.begin(); it != container.end(); ++it)
        {
            Item* olditem = it->second;
            if (olditem->m_pTemplate == item->m_pTemplate &&
                (olditem->m_iteminfo.m_byBindType == item->m_iteminfo.m_byBindType ||
                    olditem->m_iteminfo.m_byBindType == BINDTYPE_BINDED && item->m_iteminfo.m_byBindType == BINDTYPE_BOP) &&
                olditem->m_iteminfo.m_nCurDur + item->m_iteminfo.m_nCurDur <= item->m_pTemplate->m_nDur)
            {
                olditem->m_iteminfo.m_nCurDur += item->m_iteminfo.m_nCurDur;

#ifndef _ROBOT
                if (!m_pOwner->IsLoading())
                {
                    CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, olditem);
                }

                if (olditem->m_pTemplate->m_byLog)
                {
                    CCliMessageHandler::GetInstance().DoDLLogItem(
                        m_pOwner->GetObjID(),
                        m_pOwner->GetServerGroup(),
                        olditem->m_iteminfo.m_llGuid,
                        olditem->m_pTemplate->m_nTemplateID,
                        item->m_iteminfo.m_nCurDur,
                        reason,
                        ITEMACTION_INC,
                        userdefine);
                }

                if (olditem->m_pTemplate->m_byStat)
                {
                    CCliMessageHandler::GetInstance().DoDLStatItem(
                        m_pOwner->GetServerGroup(),
                        olditem->m_pTemplate->m_nTemplateID,
                        item->m_iteminfo.m_nCurDur,
                        1);
                }
#endif // _ROBOT

                delete_item = TRUE;
                nResult = errSuccess;
                break;
            }
        }
    }

    if (nResult != errSuccess)
    {
        //不可堆叠，则寻找空位子放入
        UINT8 itemslot = 0;
        BOOL found = FALSE;
        for (ConIt it = container.begin(); it != container.end(); ++it)
        {
            if (itemslot < it->first)
            {
                found = TRUE;
                break;
            }
            itemslot++;
        }

        if (found || itemslot < m_con_sizes[conslot])
        {
            container.insert(Container::value_type(itemslot, item));
            item->SetPos(conslot, itemslot);

            // 拾取绑定
            if (item->m_iteminfo.m_byBindType == BINDTYPE_BOP)
                item->m_iteminfo.m_byBindType = BINDTYPE_BINDED;

            // 交易绑定
            if (item->m_iteminfo.m_byBindType == BINDTYPE_BOT && reason == ITEMLOG_PLAYER_TRADE)
                item->m_iteminfo.m_byBindType = BINDTYPE_BINDED;

#ifndef _ROBOT
            if (!m_pOwner->IsLoading())
            {
                CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);
            }

            if (item->m_pTemplate->m_byLog)
            {
                CCliMessageHandler::GetInstance().DoDLLogItem(
                    m_pOwner->GetObjID(),
                    m_pOwner->GetServerGroup(),
                    item->m_iteminfo.m_llGuid,
                    item->m_pTemplate->m_nTemplateID,
                    item->m_pTemplate->m_byDurType == DURTYPE_STACK ? item->m_iteminfo.m_nCurDur : 1,
                    reason,
                    ITEMACTION_ADD,
                    userdefine);

                if (item->m_pTemplate->m_byType == ITEMTYPE_EQUIP)
                {
                    CCliMessageHandler::GetInstance().DoDLChangeItem(
                        m_pOwner->GetServerGroup(),
                        m_pOwner->GetObjID(),
                        reason,
                        item->m_iteminfo);
                }
            }

            if (item->m_pTemplate->m_byStat)
            {
                CCliMessageHandler::GetInstance().DoDLStatItem(
                    m_pOwner->GetServerGroup(),
                    item->m_pTemplate->m_nTemplateID,
                    item->m_pTemplate->m_byDurType == DURTYPE_STACK ? item->m_iteminfo.m_nCurDur : 1,
                    1);
            }
#endif // _ROBOT
            nResult = errSuccess;
        }
        else
            nResult = errItemBagFull;
    }

#ifndef _ROBOT
    if (nResult == errSuccess)
    {
        CheckWeight();
        if (reason == ITEMLOG_LOOT)
        {
            CTeamInGS* pTeam = CGameWorld::GetInstance().FindTeam(m_pOwner->GetTeamID());
            if (pTeam)
            {
                for (UINT32 i = 0; i < pTeam->GetMaxMemberCount(); i++)
                {
                    CRole* teammate = CGameWorld::GetInstance().FindValidRole(pTeam->GetMemberTable(i).dwRoleID);
                    if (teammate)
                        CCliMessageHandler::GetInstance().DoPickUpItem(teammate, m_pOwner->GetObjID(), item);
                }
            }
            else
                CCliMessageHandler::GetInstance().DoPickUpItem(m_pOwner, m_pOwner->GetObjID(), item);
        }

        if (item->m_pTemplate->m_nHandbookType > htInvalid)
        {
            if (item->m_pTemplate->m_nHandbookType >= htEquip_Begin && item->m_pTemplate->m_nHandbookType < htEquip_End)
            {
                if (item->m_pTemplate->m_byType == ITEMTYPE_EQUIP)
                {
                    EQUIP_DATA* equip = (EQUIP_DATA*)item->m_pTemplate;
                    if (equip->m_SetData != NULL)
                    {
                        BOOL bSetComplete = TRUE;
                        for (INT32 i = 0; i < MAX_SET_PART_COUNT; i++)
                        {
                            if (equip->m_SetData->m_nItemID[i] != 0)
                            {
                                INT32 nCount = GetItemCount(equip->m_SetData->m_nItemID[i], FALSE);
                                if (nCount <= 0)
                                {
                                    bSetComplete = FALSE;
                                    break;
                                }
                            }
                        }
                        if (bSetComplete)
                        {
                            m_pOwner->GetAchievementList().ActivateHandbook(equip->m_SetData->m_nHandbookType, equip->m_SetData->m_nHankbookIndex);
                        }
                    }
                }
            }
            m_pOwner->GetAchievementList().ActivateHandbook(item->m_pTemplate->m_nHandbookType, item->m_pTemplate->m_nHandbookIndex);
        }
    }
#endif // _ROBOT

    if (delete_item)
    {
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
        LOG_CHECK_ERROR(bItemRet);
    }

    return nResult;
}


BOOL CItemBag::_CheckValidItemPos(UINT8 conslot, UINT8 itemslot)
{
    return (conslot < CONSLOT_COUNT && itemslot < m_con_sizes[conslot]);
}

BOOL CItemBag::_SrcDstSame(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot)
{
    return (srcconslot == dstconslot && srcitemslot == dstitemslot);
}

BOOL CItemBag::_Satisfied(CCharacter* poChar, const Item* item) const
{
    PROCESS_ERROR(poChar);

    if (poChar->GetLevel() < item->m_pTemplate->m_byRequireLevel)
        return FALSE;

    if (item->m_pTemplate->m_byRequireGender != cstInvalid)
    {
        if (item->m_pTemplate->m_byRequireGender != poChar->GetSex())
            return FALSE;
    }

    if ((item->m_pTemplate->m_byRequireClass & (1 << poChar->GetClass())) == 0)
        return FALSE;

    if (item->m_pTemplate->m_byType == ITEMTYPE_EQUIP)
    {
        const EQUIP_DATA* equip_data = (const EQUIP_DATA*)item->m_pTemplate;
        if (poChar->GetAttr(catMaxPhyAtk) < equip_data->m_nRequireMaxPhyAtk)
            return FALSE;
        if (poChar->GetAttr(catMaxMagAtk) < equip_data->m_nRequireMaxMagAtk)
            return FALSE;
        if (poChar->GetAttr(catMaxTaoAtk) < equip_data->m_nRequireMaxTaoAtk)
            return FALSE;
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL CItemBag::_CorrectSlot(const Item* item, UINT8 itemslot)
{
    LOG_PROCESS_ERROR(item && item->m_pTemplate);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);

    switch (item->m_pTemplate->m_bySubType)
    {
    case ITEMSUBTYPE_EQUIP_WEAPON:
        return itemslot == NES_MAIN_HAND;
    case ITEMSUBTYPE_EQUIP_HAT:
        return itemslot == NES_HEAD;
    case ITEMSUBTYPE_EQUIP_SHOULDER_ARMOR:
        return itemslot == NES_SHOULDER;
    case ITEMSUBTYPE_EQUIP_CHEST_ARMOR:
        return itemslot == NES_BODY;
    case ITEMSUBTYPE_EQUIP_WRIST_ARMOR:
        return itemslot == NES_ARM;
    case ITEMSUBTYPE_EQUIP_BELT:
        return itemslot == NES_WAIST;
    case ITEMSUBTYPE_EQUIP_SHOES:
        return itemslot == NES_FOOT;
    case ITEMSUBTYPE_EQUIP_CLOAK:
        return itemslot == NES_BACK;
    case ITEMSUBTYPE_EQUIP_NECKLACE:
        return itemslot == NES_NECK;
    case ITEMSUBTYPE_EQUIP_RING:
        return itemslot == NES_FINGER_L || itemslot == NES_FINGER_R;
    case ITEMSUBTYPE_EQUIP_BRACELET:
        return itemslot == NES_WRIST_L || itemslot == NES_WRIST_R;
    default:
        return FALSE;
    }

Exit0:
    return FALSE;
}

BOOL CItemBag::_CorrectDepositSlot(const Item* item, UINT8 itemslot)
{
    LOG_PROCESS_ERROR(item && item->m_pTemplate);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_DEPOSIT);

    switch (item->m_pTemplate->m_bySubType)
    {
    case ITEMSUBTYPE_DEPOSIT_SOUL:
        return itemslot == DEPOSIT_SOUL_SLOT;
    case ITEMSUBTYPE_DEPOSIT_EXP:
        return itemslot == DEPOSIT_EXP_SLOT;
    default:
        return FALSE;
    }

Exit0:
    return FALSE;
}

INT32 CItemBag::_MoveItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot)
{
    ConIt srcit = m_cons[srcconslot].find(srcitemslot);
    if (srcit == m_cons[srcconslot].end())
        return errItemNotFound;
    Item* srcitem = srcit->second;

    ConIt dstit = m_cons[dstconslot].find(dstitemslot);
    Item* dstitem = NULL;
    if (dstit == m_cons[dstconslot].end())
    {
        //物品移向空格
#ifndef _ROBOT
        CCliMessageHandler::GetInstance().DoSendItemSwap(m_pOwner, srcconslot, srcitemslot, dstconslot, dstitemslot);
#endif // _ROBOT
        m_cons[srcconslot].erase(srcit);
        m_cons[dstconslot][dstitemslot] = srcitem;
        srcitem->SetPos(dstconslot, dstitemslot);
    }
    else
    {
        //物品移向另一物品
        dstitem = dstit->second;
        if (srcitem->m_pTemplate->m_byDurType == DURTYPE_STACK &&
            srcitem->m_pTemplate == dstitem->m_pTemplate &&
            srcitem->m_iteminfo.m_byBindType == dstitem->m_iteminfo.m_byBindType)
        {
            //堆叠
            if (srcitem->m_iteminfo.m_nCurDur + dstitem->m_iteminfo.m_nCurDur <= srcitem->m_pTemplate->m_nDur)
            {
                dstitem->m_iteminfo.m_nCurDur += srcitem->m_iteminfo.m_nCurDur;
#ifndef _ROBOT
                CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, srcconslot, srcitemslot);
                CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, dstitem);

                if (srcitem->m_pTemplate->m_byLog)
                {
                    CCliMessageHandler::GetInstance().DoDLLogItem(
                        m_pOwner->GetObjID(),
                        m_pOwner->GetServerGroup(),
                        srcitem->m_iteminfo.m_llGuid,
                        srcitem->m_pTemplate->m_nTemplateID,
                        srcitem->m_iteminfo.m_nCurDur,
                        ITEMLOG_MOVE,
                        ITEMACTION_DEL,
                        dstitem->m_iteminfo.m_llGuid);

                    CCliMessageHandler::GetInstance().DoDLLogItem(
                        m_pOwner->GetObjID(),
                        m_pOwner->GetServerGroup(),
                        dstitem->m_iteminfo.m_llGuid,
                        dstitem->m_pTemplate->m_nTemplateID,
                        srcitem->m_iteminfo.m_nCurDur,
                        ITEMLOG_MOVE,
                        ITEMACTION_INC,
                        srcitem->m_iteminfo.m_llGuid);
                }

#endif // _ROBOT
                BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(srcitem);
                LOG_CHECK_ERROR(bItemRet);
                m_cons[srcconslot].erase(srcit);
            }
            else
            {
                INT32 real_count = dstitem->m_pTemplate->m_nDur - dstitem->m_iteminfo.m_nCurDur;

                srcitem->m_iteminfo.m_nCurDur -= real_count;
                dstitem->m_iteminfo.m_nCurDur += real_count;

#ifndef _ROBOT
                CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, srcitem);
                CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, dstitem);

                if (srcitem->m_pTemplate->m_byLog)
                {
                    CCliMessageHandler::GetInstance().DoDLLogItem(
                        m_pOwner->GetObjID(),
                        m_pOwner->GetServerGroup(),
                        srcitem->m_iteminfo.m_llGuid,
                        srcitem->m_pTemplate->m_nTemplateID,
                        real_count,
                        ITEMLOG_MOVE,
                        ITEMACTION_DEC,
                        dstitem->m_iteminfo.m_llGuid);

                    CCliMessageHandler::GetInstance().DoDLLogItem(
                        m_pOwner->GetObjID(),
                        m_pOwner->GetServerGroup(),
                        dstitem->m_iteminfo.m_llGuid,
                        dstitem->m_pTemplate->m_nTemplateID,
                        real_count,
                        ITEMLOG_MOVE,
                        ITEMACTION_INC,
                        srcitem->m_iteminfo.m_llGuid);
                }
#endif // _ROBOT
            }
        }
        else
        {
            //交换
#ifndef _ROBOT
            CCliMessageHandler::GetInstance().DoSendItemSwap(m_pOwner, srcconslot, srcitemslot, dstconslot, dstitemslot);
#endif // _ROBOT
            m_cons[srcconslot][srcitemslot] = dstitem;
            dstitem->SetPos(srcconslot, srcitemslot);
            m_cons[dstconslot][dstitemslot] = srcitem;
            srcitem->SetPos(dstconslot, dstitemslot);
        }
    }

#ifndef _ROBOT
    if (IsAppearance(srcconslot, srcitemslot))
    {
        if (srcconslot == CONSLOT_HERO_EQUIPPED)
            CCliMessageHandler::GetInstance().DoSyncHeroAvatar(m_pOwner, srcconslot, srcitemslot, (dstitem ? dstitem->m_iteminfo.m_nTemplateID : 0));
        else
            CCliMessageHandler::GetInstance().DoSyncRoleAvatar(m_pOwner, srcconslot, srcitemslot, (dstitem ? dstitem->m_iteminfo.m_nTemplateID : 0),
                (dstitem && srcitemslot == NES_MAIN_HAND) ? GetRefineFx() : 0);
    }
    if (IsAppearance(dstconslot, dstitemslot))
    {
        if (dstconslot == CONSLOT_HERO_EQUIPPED)
            CCliMessageHandler::GetInstance().DoSyncHeroAvatar(m_pOwner, dstconslot, dstitemslot, srcitem->m_iteminfo.m_nTemplateID);
        else
            CCliMessageHandler::GetInstance().DoSyncRoleAvatar(m_pOwner, dstconslot, dstitemslot, srcitem->m_iteminfo.m_nTemplateID,
                dstitemslot == NES_MAIN_HAND ? GetRefineFx() : 0);
    }
#endif // _ROBOT

    CheckWeight();

    return errSuccess;
}

void CItemBag::_LoseDur(Item* item, INT16 dur, EItemLog reason)
{
#ifndef _ROBOT
    INT32 old_dur = 0;

    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(dur > 0);

    old_dur = item->m_iteminfo.m_nCurDur;
    item->m_iteminfo.m_nCurDur -= dur;
    if (item->m_iteminfo.m_nCurDur < 0)
    {
        item->m_iteminfo.m_nCurDur = 0;
    }

    if (item->m_pTemplate->m_byStat && item->m_pTemplate->m_byDurType == DURTYPE_STACK)
    {
        CCliMessageHandler::GetInstance().DoDLStatItem(
            m_pOwner->GetServerGroup(),
            item->m_pTemplate->m_nTemplateID,
            old_dur - item->m_iteminfo.m_nCurDur,
            0);
    }

    if (item->m_iteminfo.m_nCurDur == 0)
    {
        if (item->m_pTemplate->m_byDurType == DURTYPE_STACK ||
            item->m_pTemplate->m_byDurType == DURTYPE_USE ||
            item->m_pTemplate->m_byDurType == DURTYPE_NONE)
        {
            UINT8 conslot = item->m_iteminfo.m_byConSlot;
            UINT8 itemslot = item->m_iteminfo.m_byItemSlot;
            CCliMessageHandler::GetInstance().DoSendItemDelete(m_pOwner, conslot, itemslot);

            if (item->m_pTemplate->m_byLog)
            {
                CCliMessageHandler::GetInstance().DoDLLogItem(
                    m_pOwner->GetObjID(),
                    m_pOwner->GetServerGroup(),
                    item->m_iteminfo.m_llGuid,
                    item->m_pTemplate->m_nTemplateID,
                    1,
                    reason,
                    ITEMACTION_DEL,
                    0);
            }

            BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(item);
            LOG_CHECK_ERROR(bItemRet);
            m_cons[conslot].erase(itemslot);

            CheckWeight();

            return;
        }
    }

    if (item->m_iteminfo.m_byConSlot == CONSLOT_EQUIPPED)
    {
        if (old_dur)
        {
            CCliMessageHandler::GetInstance().DoSendEquipDurChange(m_pOwner, CONSLOT_EQUIPPED, item->m_iteminfo.m_byItemSlot, item->m_iteminfo.m_nCurDur);

            if (item->m_iteminfo.m_nCurDur == 0)
            {
                item->OnUnEquip(m_pOwner, m_refine_levels[item->m_iteminfo.m_byItemSlot], m_pOwner->GetClass(), item->m_iteminfo.m_byItemSlot);
            }
        }
    }
    else
    {
        CCliMessageHandler::GetInstance().DoSendItemChange(m_pOwner, item);
    }

Exit0:
    return;

#endif // _ROBOT
}

void CItemBag::_AddItemToSoldList(Item* item)
{
    LOG_PROCESS_ERROR(item);

    while (m_soldlist.size() >= MAX_SOLD_ITEMS)
    {
        Item* solditem = m_soldlist.front();
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(solditem);
        LOG_CHECK_ERROR(bItemRet);
        m_soldlist.pop_front();
    }

    m_soldlist.push_back(item);

Exit0:
    return;
}

void CItemBag::_OnUseItemSuccess(UINT8 conslot, UINT8 itemslot, Item* item)
{
    if (item->m_pTemplate->m_nSelfCoolDown)
    {
        INT32 nCoolDownFrm = item->m_pTemplate->m_nSelfCoolDown;
        m_pOwner->AddCooldown(MakeCoolDownID(COOLDOWN_ITEM, item->m_pTemplate->m_nTemplateID), nCoolDownFrm);
    }

    if (item->m_pTemplate->m_nCdGrpCount > 0)
    {
        for (INT32 i = 0; i < item->m_pTemplate->m_nCdGrpCount; i++)
        {
            INT32 nCoolDownFrm = item->m_pTemplate->m_CdGrp[i].m_nCdGrpValue;
            m_pOwner->AddCooldown(MakeCoolDownID(COOLDOWN_GROUP, item->m_pTemplate->m_CdGrp[i].m_nCdGrpID), nCoolDownFrm);
        }
    }

    CStatistic::GetInstance().OnUseItem(m_pOwner, item);

    if (item->m_pTemplate->m_byDurType == DURTYPE_STACK || item->m_pTemplate->m_byDurType == DURTYPE_USE)
    {
        _LoseDur(item, 1, ITEMLOG_USE_ITEM);
    }
    else if (item->m_pTemplate->m_byDurType == DURTYPE_DEPOSIT)
    {
        DeleteItemPos(conslot, itemslot, 1, ITEMLOG_USE_ITEM, 0);
    }
}

void CItemBag::_ClearRandomizeItem()
{
    if (m_randomize_item)
    {
        BOOL bItemRet = CItemMgr::GetInstance().DestroyItem(m_randomize_item);
        LOG_CHECK_ERROR(bItemRet);
        m_randomize_item = NULL;
    }
}

INT32 CItemBag::_GetPow(const Item* item) const
{
    const EQUIP_DATA* equip_data = NULL;
    INT32 p = 0;

    LOG_PROCESS_ERROR(item->m_pTemplate->m_byType == ITEMTYPE_EQUIP);
    equip_data = (const EQUIP_DATA*)item->m_pTemplate;

    p = equip_data->m_nPow;

    if (item->m_iteminfo.m_byLuck > 0)
        p = p * (20 + item->m_iteminfo.m_byLuck) / 20;

    for (UINT8 i = 0; i < MAX_RANDOM_ATTR_COUNT; i++)
    {
        if (item->m_iteminfo.m_wRandomAttrID[i])
        {
            const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(item->m_iteminfo.m_wRandomAttrID[i]);
            LOG_PROCESS_ERROR(attr_data);
            p += attr_data->m_nPow;
        }
    }

    for (UINT8 i = 0; i < MAX_SOCKET_COUNT; i++)
    {
        if (item->m_iteminfo.m_nSoulID[i])
        {
            const SOUL_DATA* soul_data = CDataManager<SOUL_DATA>::GetInstance().GetData(item->m_iteminfo.m_nSoulID[i]);
            LOG_PROCESS_ERROR(soul_data);
            p += soul_data->m_pAttrData->m_nPow;
        }

        if (item->m_iteminfo.GetSocketType(i) != SOCKET_NONE)
        {
            p += 10;
        }
    }

    p += (item->m_iteminfo.m_byLevelupPhyPoint + item->m_iteminfo.m_byLevelupMagPoint + item->m_iteminfo.m_byLevelupTaoPoint) * 5;

Exit0:
    return p;
}

INT32 CItemBag::_GetSellPrice(const Item* item) const
{
    INT32 sell_price = 0;

    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(item->m_pTemplate->m_nDur > 0);

    sell_price = item->m_pTemplate->m_nSellPrice;
    LOG_PROCESS_ERROR(sell_price > 0);

    if (item->m_pTemplate->m_byDurType == DURTYPE_STACK)
    {
        sell_price *= item->m_iteminfo.m_nCurDur;
    }
    else if (item->m_pTemplate->m_byDurType == DURTYPE_USE)
    {
        sell_price = sell_price * item->m_iteminfo.m_nCurDur / item->m_pTemplate->m_nDur;
    }
    else if (item->m_pTemplate->m_byDurType == DURTYPE_EQUIP)
    {
        //随机属性
        for (INT32 i = 0; i < MAX_RANDOM_ATTR_COUNT; i++)
        {
            if (item->m_iteminfo.m_wRandomAttrID[i])
            {
                const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(item->m_iteminfo.m_wRandomAttrID[i]);
                if (attr_data)
                    sell_price += attr_data->m_nPow * 100;
            }
        }

        //融灵属性
        for (INT32 i = 0; i < MAX_SOCKET_COUNT; i++)
        {
            if (item->m_iteminfo.m_nSoulID[i])
            {
                const SOUL_DATA* soul_data = CDataManager<SOUL_DATA>::GetInstance().GetData(item->m_iteminfo.m_nSoulID[i]);
                if (soul_data)
                {
                    const ATTRIBUTE_DATA* attr_data = CDataManager<ATTRIBUTE_DATA>::GetInstance().GetData(soul_data->m_nAttrID);
                    if (attr_data)
                        sell_price += attr_data->m_nPow * 100;
                }
            }
            else if (item->m_iteminfo.GetSocketType(i) != SOCKET_NONE)
            {
                sell_price += EMPTY_SOCKET_SELL_PRICE;
            }
        }

        //铸魂属性
        for (INT32 i = 0; i < MAX_RUNE_COUNT; i++)
        {
            if (item->m_iteminfo.m_wRune[i])
                sell_price += RUNE_SELL_PRICE;
        }

        //幸运、诅咒
        sell_price += abs(item->m_iteminfo.m_byLuck);

        //升级属性
        sell_price += item->m_iteminfo.m_byLevelupPhyPoint * 100;
        sell_price += item->m_iteminfo.m_byLevelupMagPoint * 100;
        sell_price += item->m_iteminfo.m_byLevelupTaoPoint * 100;

        //卖店价=（满耐久卖店价*90%）*（当前耐久/最大耐久）+满耐久卖店价*10%
        sell_price = ((INT64)sell_price * 9 * item->m_iteminfo.m_nCurDur / item->m_pTemplate->m_nDur + sell_price) / 10;
    }

    if (sell_price <= 0)
        sell_price = 1;

    return sell_price;

Exit0:
    return 0;
}

UINT32 CItemBag::_GetPkDropChance(Item* item, UINT8 isplayer, UINT8 namecolor)
{
    LOG_PROCESS_ERROR(namecolor < rncTotal);

    if (item->m_iteminfo.m_byConSlot == CONSLOT_EQUIPPED)
    {
        UINT32 isweapon = (item->m_pTemplate->m_byType == ITEMTYPE_EQUIP && item->m_pTemplate->m_bySubType == ITEMSUBTYPE_EQUIP_WEAPON) ? 1 : 0;
        const PK_DROP_RATE_DATA* rate_data = CDataManager<PK_DROP_RATE_DATA>::GetInstance().GetData(
            PK_DROP_RATE_DATA::MakeKey(item->m_pTemplate->m_byColor, isweapon, isplayer));

        LOG_PROCESS_ERROR(rate_data);

        return rate_data->m_dwDropRate[namecolor];
    }
    else
    {
        if (isplayer)
        {
            if (item->m_pTemplate->m_byExpensiveItem)
                return g_GWConfig.nBagExpensiveItemDropRateByPlayer[namecolor];
            else
                return g_GWConfig.nBagNormalItemDropRateByPlayer[namecolor];
        }
        else
        {
            if (item->m_pTemplate->m_byExpensiveItem)
                return g_GWConfig.nBagExpensiveItemDropRateByNonPlayer[namecolor];
            else
                return g_GWConfig.nBagNormalItemDropRateByNonPlayer[namecolor];
        }
    }

Exit0:
    return 0;
}

INT32 CItemBag::_GetArmorWeight() const
{
    INT32 weight = 0;
    for (CConIt it = m_cons[CONSLOT_EQUIPPED].lower_bound(NES_BODY); it != m_cons[CONSLOT_EQUIPPED].end(); ++it)
    {
        weight += it->second->GetWeight();
    }
    return weight;
}

INT32 CItemBag::_GetBagWeight() const
{
    INT32 weight = 0;
    for (CConIt it = m_cons[CONSLOT_DEFAULT].begin(); it != m_cons[CONSLOT_DEFAULT].end(); ++it)
    {
        weight += it->second->GetWeight();
    }
    return weight;
}

void CItemBag::CheckWeight()
{
    static BOOL aura_init = FALSE;
    static CAuraTemplate* weapon_aura, * armor_aura, * bag_aura;

    Item* weapon = GetItem(CONSLOT_EQUIPPED, NES_MAIN_HAND);
    BOOL bWeaponOverWeight;
    BOOL bArmorOverWeight;
    BOOL bBagOverWeight;

    if (!aura_init)
    {
        weapon_aura = CSpellConfig::GetInstance().FindAuraTemplate(g_GWConfig.nWeaponOverWeightAuraID);
        LOG_PROCESS_ERROR(weapon_aura);

        armor_aura = CSpellConfig::GetInstance().FindAuraTemplate(g_GWConfig.nArmorOverWeightAuraID);
        LOG_PROCESS_ERROR(armor_aura);

        bag_aura = CSpellConfig::GetInstance().FindAuraTemplate(g_GWConfig.nBagOverWeightAuraID);
        LOG_PROCESS_ERROR(bag_aura);

        aura_init = TRUE;
    }

    bWeaponOverWeight = weapon ? weapon->GetWeight() > m_pOwner->GetAttr(catWeaponWeightLmt) : FALSE;
    bArmorOverWeight = _GetArmorWeight() > m_pOwner->GetAttr(catArmorWeightLmt);
    bBagOverWeight = _GetBagWeight() > m_pOwner->GetAttr(catBagWeightLmt);

    if (bWeaponOverWeight && m_pWeaponAura == NULL)
    {
        m_pWeaponAura = m_pOwner->AppendAura(weapon_aura, m_pOwner, m_pOwner->GetObjID(), NULL, 0, 0, 0, 0);
    }
    if (!bWeaponOverWeight && m_pWeaponAura)
    {
        m_pOwner->RemoveAura(m_pWeaponAura, TRUE);
        m_pWeaponAura = NULL;
    }
    if (bArmorOverWeight && m_pArmorAura == NULL)
    {
        m_pArmorAura = m_pOwner->AppendAura(armor_aura, m_pOwner, m_pOwner->GetObjID(), NULL, 0, 0, 0, 0);
    }
    if (!bArmorOverWeight && m_pArmorAura)
    {
        m_pOwner->RemoveAura(m_pArmorAura, TRUE);
        m_pArmorAura = NULL;
    }
    if (bBagOverWeight && m_pBagAura == NULL)
    {
        m_pBagAura = m_pOwner->AppendAura(bag_aura, m_pOwner, m_pOwner->GetObjID(), NULL, 0, 0, 0, 0);
    }
    if (!bBagOverWeight && m_pBagAura)
    {
        m_pOwner->RemoveAura(m_pBagAura, TRUE);
        m_pBagAura = NULL;
    }
Exit0:
    return;
}

Item* CItemBag::GetItem(UINT8 conslot, UINT8 itemslot)
{
    if (!_CheckValidItemPos(conslot, itemslot))
        return NULL;

    ConIt it = m_cons[conslot].find(itemslot);
    if (it == m_cons[conslot].end())
        return NULL;

    return it->second;
}

#ifdef _ROBOT

void CItemBag::SetContainerSize(UINT8 conslot, UINT8 consize)
{
    LOG_PROCESS_ERROR(conslot < CONSLOT_COUNT);
    m_con_sizes[conslot] = consize;

Exit0:
    return;
}

void CItemBag::OnItemChange(const ItemInfo& iteminfo)
{
    Item* item = NULL;

    LOG_PROCESS_ERROR(_CheckValidItemPos(iteminfo.m_byConSlot, iteminfo.m_byItemSlot));

    item = GetItem(iteminfo.m_byConSlot, iteminfo.m_byItemSlot);
    if (item == NULL)
    {
        item = CGameWorld::GetInstance().NewItem(iteminfo.m_llGuid);
        LOG_PROCESS_ERROR(item);
        m_cons[iteminfo.m_byConSlot][iteminfo.m_byItemSlot] = item;
    }

    item->m_pTemplate = GetItemData(iteminfo.m_nTemplateID);
    LOG_PROCESS_ERROR(item->m_pTemplate);
    item->m_iteminfo = iteminfo;

Exit0:
    return;
}

void CItemBag::OnItemDelete(UINT8 conslot, UINT8 itemslot)
{
    Item* item = NULL;

    LOG_PROCESS_ERROR(_CheckValidItemPos(conslot, itemslot));

    item = GetItem(conslot, itemslot);

    LOG_PROCESS_ERROR(item);

    CGameWorld::GetInstance().DelItem(item);
    m_cons[conslot].erase(itemslot);

Exit0:
    return;
}

void CItemBag::OnItemSwap(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot)
{
    Item* srcitem;
    Item* dstitem;

    LOG_PROCESS_ERROR(_CheckValidItemPos(srcconslot, srcitemslot));
    LOG_PROCESS_ERROR(_CheckValidItemPos(dstconslot, dstitemslot));

    srcitem = GetItem(srcconslot, srcitemslot);
    dstitem = GetItem(dstconslot, dstitemslot);

    LOG_PROCESS_ERROR(srcitem);

    if (dstitem)
    {
        srcitem->m_iteminfo.m_byConSlot = dstconslot;
        srcitem->m_iteminfo.m_byItemSlot = dstitemslot;
        dstitem->m_iteminfo.m_byConSlot = srcconslot;
        dstitem->m_iteminfo.m_byItemSlot = srcitemslot;

        m_cons[srcconslot][srcitemslot] = dstitem;
        m_cons[dstconslot][dstitemslot] = srcitem;
    }
    else
    {
        srcitem->m_iteminfo.m_byConSlot = dstconslot;
        srcitem->m_iteminfo.m_byItemSlot = dstitemslot;

        m_cons[srcconslot].erase(srcitemslot);
        m_cons[dstconslot][dstitemslot] = srcitem;
    }

Exit0:
    return;
}

#endif // _ROBOT
