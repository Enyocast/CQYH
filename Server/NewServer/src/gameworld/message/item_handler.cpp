#include "stdafx.h"

#include "zlib.h"

#include "message_handler.h"
#include "imessage_notifier.h"
#include "g2c_message.h"
#include "g2m_message.h"
#include "game_world.h"
#include "role.h"
#include "drop.h"
#include "region.h"
#include "rsa_sign.h"
#include "statistic.h"
#include "npc_shop_mgr.h"
#include "npc_data.h"
#include "level_data.h"

#include <m2c_message.h>

#ifndef _ROBOT

using namespace ExternalMessage;

// ==================== 下面全是 c2g收包 On函数

void CCliMessageHandler::OnUseItem(CRole* pRole, const char* pData)
{
    C2G_USE_ITEM* pMsg = (C2G_USE_ITEM*)pData;

    INT32 err = pRole->GetItemBag()->UseItem(pMsg->byConSlot, pMsg->byItemSlot);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnMoveItem(CRole* pRole, const char* pData)
{
    C2G_MOVE_ITEM* pMsg = (C2G_MOVE_ITEM*)pData;

    INT32 err = pRole->GetItemBag()->MoveItem(pMsg->bySrcConSlot, pMsg->bySrcItemSlot, pMsg->byDstConSlot, pMsg->byDstItemSlot);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnSplitItem(CRole* pRole, const char* pData)
{
    C2G_SPLIT_ITEM* pMsg = (C2G_SPLIT_ITEM*)pData;

    INT32 err = pRole->GetItemBag()->SplitItem(pMsg->bySrcConSlot, pMsg->bySrcItemSlot, pMsg->byDstConSlot, pMsg->byDstItemSlot, pMsg->shItemCount);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnDeleteItem(CRole* pRole, const char* pData)
{
    C2G_DELETE_ITEM* pMsg = (C2G_DELETE_ITEM*)pData;

    INT32 err = pRole->GetItemBag()->DeleteItem(pMsg->byConSlot, pMsg->byItemSlot, pMsg->shItemCount);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
    else
    {
        pRole->GetAchievementList().AddVariable(avdDestoryItemCount, 1);
    }

    return;
}

void CCliMessageHandler::OnPickUpItem(CRole* pRole, const char* pData)
{
    C2G_PICKUP_ITEM* pMsg = (C2G_PICKUP_ITEM*)pData;

    INT32 err = pRole->PickUp(pMsg->dwDropID);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, pMsg->dwDropID, pMsg->byPickMode);
    }

    return;
}

void CCliMessageHandler::OnBuyItem(CRole* pRole, const char* pData)
{
    C2G_BUY_ITEM* pMsg = (C2G_BUY_ITEM*)pData;

    INT32 err = pRole->BuyItem(pMsg->nShopID, pMsg->nShopItemIndex, pMsg->shItemCount);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnSellItem(CRole* pRole, const char* pData)
{
    C2G_SELL_ITEM* pMsg = (C2G_SELL_ITEM*)pData;

    INT32 err = pRole->SellItem(pMsg->byConSlot, pMsg->byItemSlot, pMsg->shItemCount);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnViewSoldItems(CRole* pRole, const char* pData)
{
    INT32 err = pRole->ViewSoldItems();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnBuyBackItem(CRole* pRole, const char* pData)
{
    C2G_BUY_BACK_ITEM* pMsg = (C2G_BUY_BACK_ITEM*)pData;

    INT32 err = pRole->BuyBackItem(pMsg->bySlot);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnRepairItem(CRole* pRole, const char* pData)
{
    C2G_REPAIR_ITEM* pMsg = (C2G_REPAIR_ITEM*)pData;

    INT32 err = pRole->RepairItem(pMsg->byConSlot, pMsg->byItemSlot, FALSE);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnRepairAllEquippedItem(CRole* pRole, const char* pData)
{
    INT32 err = pRole->RepairAllEquippedItem();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnSpecialRepairItem(CRole* pRole, const char* pData)
{
    C2G_SPECIAL_REPAIR_ITEM* pMsg = (C2G_SPECIAL_REPAIR_ITEM*)pData;

    INT32 err = pRole->RepairItem(pMsg->byConSlot, pMsg->byItemSlot, TRUE);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnRefine(CRole* pRole, const char* pData)
{
    C2G_REFINE* pMsg = (C2G_REFINE*)pData;

    INT32 err = pRole->GetItemBag()->Refine(pMsg->byRefineSlot, pMsg->byAddEquip, pMsg->byConSlot, pMsg->byItemSlot);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnBuyContainerSlot(CRole* pRole, const char* pData)
{
    C2G_BUY_CONTAINER_SLOT* pMsg = (C2G_BUY_CONTAINER_SLOT*)pData;

    INT32 err = pRole->GetItemBag()->BuySlots(pMsg->byConSlot, pMsg->byCount);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnOrganizeBag(CRole* pRole, const char* pData)
{
    C2G_ORGANIZE_BAG* pMsg = (C2G_ORGANIZE_BAG*)pData;

    INT32 err = pRole->GetItemBag()->OrganizeBag(pMsg->byConSlot);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnIdentifyItem(CRole* pRole, const char* pData)
{
    C2G_IDENTIFY_ITEM* pMsg = (C2G_IDENTIFY_ITEM*)pData;

    INT32 err = pRole->GetItemBag()->IdentifyItem(pMsg->byConSlot, pMsg->byItemSlot);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
    else
    {
        pRole->GetAchievementList().AddVariable(avdIdentifyItemCount, 1);
    }

    return;
}

void CCliMessageHandler::OnRandomizeItem(CRole* pRole, const char* pData)
{
    C2G_RANDOMIZE_ITEM* pMsg = (C2G_RANDOMIZE_ITEM*)pData;

    INT32 err = pRole->GetItemBag()->RandomizeItem(pMsg->byConSlot, pMsg->byItemSlot);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnConfirmRandomizeItem(CRole* pRole, const char* pData)
{
    INT32 err = pRole->GetItemBag()->ConfirmRandomizeItem();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }

    return;
}

void CCliMessageHandler::OnTradeAsk(CRole* pRole, const char* pData)
{
    C2G_TRADE_ASK* pMsg = (C2G_TRADE_ASK*)pData;

    INT32 err = pRole->GetTrade()->AskTrade(pMsg->dwRoleID);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
    else
    {
        pRole->ErrorCodeNotify(errTradeAskSent, 0, 0);
    }
}

void CCliMessageHandler::OnTradeAccept(CRole* pRole, const char* pData)
{
    C2G_TRADE_ACCEPT* pMsg = (C2G_TRADE_ACCEPT*)pData;

    INT32 err = pRole->GetTrade()->AcceptTrade(pMsg->dwRoleID);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnTradeSetItem(CRole* pRole, const char* pData)
{
    C2G_TRADE_SET_ITEM* pMsg = (C2G_TRADE_SET_ITEM*)pData;

    INT32 err = pRole->GetTrade()->SetItem(pMsg->byTradeSlot, pMsg->bAdd, pMsg->byConSlot, pMsg->byItemSlot);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnTradeSetMoney(CRole* pRole, const char* pData)
{
    C2G_TRADE_SET_MONEY* pMsg = (C2G_TRADE_SET_MONEY*)pData;

    INT32 err = pRole->GetTrade()->SetMoney(pMsg->nMoney);
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnTradeLock(CRole* pRole, const char* pData)
{
    INT32 err = pRole->GetTrade()->LockTrade();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnTradeConfirm(CRole* pRole, const char* pData)
{
    INT32 err = pRole->GetTrade()->ConfirmTrade();
    if (err != errSuccess && err != errTradeBagFull)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnTradeUnlock(CRole* pRole, const char* pData)
{
    INT32 err = pRole->GetTrade()->UnlockTrade();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnTradeCancel(CRole* pRole, const char* pData)
{
    INT32 err = pRole->GetTrade()->CancelTrade();
    if (err != errSuccess)
    {
        pRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnUpgradeSoul(CRole* poRole, const char* pData)
{
    C2G_UPGRADE_SOUL* pMsg = (C2G_UPGRADE_SOUL*)pData;

    INT32 err = poRole->GetItemBag()->UpgradeSoul(pMsg->byTargetConSlot, pMsg->byTargetItemSlot, pMsg->bySrcCount, pMsg->bySrcConSlot, pMsg->bySrcItemSlot);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnAddSoul(CRole* poRole, const char* pData)
{
    C2G_ADD_SOUL* pMsg = (C2G_ADD_SOUL*)pData;

    INT32 err = poRole->GetItemBag()->AddSoul(pMsg->byEquipConSlot, pMsg->byEquipItemSlot, pMsg->bySocketIndex, pMsg->bySoulConSlot, pMsg->bySoulItemSlot);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnRemoveSoul(CRole* poRole, const char* pData)
{
    C2G_REMOVE_SOUL* pMsg = (C2G_REMOVE_SOUL*)pData;

    INT32 err = poRole->GetItemBag()->RemoveSoul(pMsg->byConSlot, pMsg->byItemSlot, pMsg->bySocketIndex);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

// 铸魂 - 普通铭文洗练
void CCliMessageHandler::OnRuneItem(CRole* poRole, const char* pData)
{
    C2G_RUNE_ITEM* pMsg = (C2G_RUNE_ITEM*)pData;

    INT32 err = poRole->GetItemBag()->RuneItem(pMsg->byWeaponConSlot, pMsg->byWeaponItemSlot, pMsg->nRuneItemID);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

// 升级武器
void CCliMessageHandler::OnWeaponLevelUpPutIn(CRole* poRole, const char* pData)
{
    INT32 err = poRole->GetItemBag()->WeaponLevelUpPutIn();
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}
// 取回武器
void CCliMessageHandler::OnWeaponLevelUpTakeOut(CRole* poRole, const char* pData)
{
    INT32 err = poRole->GetItemBag()->WeaponLevelUpTakeOut();
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}
// 立即取回
void CCliMessageHandler::OnWeaponLevelUpTakeOutImmediately(CRole* poRole, const char* pData)
{
    INT32 err = poRole->GetItemBag()->WeaponLevelUpTakeOutImmediately();
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnDecompose(CRole* poRole, const char* pData)
{
    C2G_DECOMPOSE* pMsg = (C2G_DECOMPOSE*)pData;

    INT32 err = poRole->GetItemBag()->Decompose(pMsg->byConSlot, pMsg->byItemSlot);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnCompose(CRole* poRole, const char* pData)
{
    C2G_COMPOSE* pMsg = (C2G_COMPOSE*)pData;

    INT32 err = poRole->GetItemBag()->Compose(pMsg->nFormulaID);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnSignItem(CRole* poRole, const char* pData)
{
    C2G_SIGN_ITEM* pMsg = (C2G_SIGN_ITEM*)pData;

    INT32 err = poRole->GetItemBag()->SignItem(pMsg->byConSlot, pMsg->byItemSlot);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnUseMoneytype01Only(CRole* poRole, const char* pData)
{
    C2G_USE_MONEYTYPE01_ONLY* pMsg = (C2G_USE_MONEYTYPE01_ONLY*)pData;
    poRole->GetItemBag()->SetUseMoneytype01Only(pMsg->byUseMoneytype01Only);
}

void CCliMessageHandler::OnCheckNpcShopData(CRole* poRole, const char* pData)
{
    INT32 nRetCode = 0;
    C2G_CHECK_NPC_SHOP_DATA* pMsg = (C2G_CHECK_NPC_SHOP_DATA*)pData;
    G2C_SYNC_NPC_SHOP_DATA* pResponse = (G2C_SYNC_NPC_SHOP_DATA*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pResponse);

    CNpcShopMgr::GetInstance().SyncNpcShopData(pMsg->dwCrc, pResponse);

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pResponse, pResponse->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return;

Exit0:
    if (pResponse)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pResponse);
}

void CCliMessageHandler::OnBlackMarketLimitInfo(CRole* poRole, const char* pData)
{
    if (CGameWorld::GetInstance().NeedUpdateMSBMLimitMap())
    {
        DoMSGetBlackMarketLimitInfo(poRole->GetObjID());
    }
    else
    {
        DoBlackMarketLimitInfo(poRole);
    }
}

void CCliMessageHandler::OnBlackMarketCooldownInfo(CRole* poRole, const char* pData)
{
    DoBlackMarketCooldownInfo(poRole);
}

void CCliMessageHandler::OnBlackMarketBuy(CRole* poRole, const char* pData)
{
    C2G_BLACK_MARKET_BUY* pMsg = (C2G_BLACK_MARKET_BUY*)pData;
    INT32 err = poRole->GetItemBag()->OnBlackMarketBuy(pMsg->nBlackMarketProductID);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

// 装备重铸
void CCliMessageHandler::OnGamble(CRole* poRole, const char* pData)
{
    C2G_GAMBLE* pMsg = (C2G_GAMBLE*)pData;
    INT32 err = poRole->GetItemBag()->Gamble(pMsg->byEquipType);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnPotionGamble(CRole* poRole, const char* pData)
{
}

void CCliMessageHandler::OnGambleAdvance(CRole* poRole, const char* pData)
{
    C2G_GAMBLE_ADVANCE* pMsg = (C2G_GAMBLE_ADVANCE*)pData;
    INT32 err = poRole->GetItemBag()->GambleAdvance(pMsg->nGambleType, pMsg->nGambleLevel);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

// 历练兑换经验
void CCliMessageHandler::OnExerciseInfo(CRole* poRole, const char* pData)
{
    INT32 nResult = errItemUnknown;
    INT32 nRetCode;
    CNpc* npc = CGameWorld::GetInstance().FindNpc(poRole->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    nRetCode = poRole->CanInteract(npc);
    PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

    LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractExercise, errNpcNoSuchFunction);

    LOG_PROCESS_ERROR_RET_CODE(!poRole->IsDead(), errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(poRole->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!poRole->GetTrade()->IsTrading(), errItemTrading);

    DoExerciseInfo(poRole, poRole->GetTotalExerciseTime() / 3600, poRole->GetCurExerciseTime() / 3600);

    return;

Exit0:
    DoErrorCodeNotify(poRole, nResult, 0, 0);
}

void CCliMessageHandler::OnAddExerciseTime(CRole* poRole, const char* pData)
{
    C2G_ADD_EXERCISE_TIME* pMsg = (C2G_ADD_EXERCISE_TIME*)pData;
    INT32 nResult = errItemUnknown;
    INT32 nRetCode;

    CNpc* npc = CGameWorld::GetInstance().FindNpc(poRole->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    nRetCode = poRole->CanInteract(npc);
    PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

    LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractExercise, errNpcNoSuchFunction);

    LOG_PROCESS_ERROR_RET_CODE(!poRole->IsDead(), errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(poRole->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!poRole->GetTrade()->IsTrading(), errItemTrading);

    LOG_PROCESS_ERROR_RET_CODE(poRole->GetTotalExerciseTime() == 0, errItemExerciseTimeNotEmpty);
    LOG_PROCESS_ERROR(pMsg->nHour > 0);
    LOG_PROCESS_ERROR(pMsg->nHour <= MAX_EXERCISE_TIME);

    PROCESS_ERROR_RET_CODE(!poRole->GetDoingSubTime(), errTimeBillBusy);

    nRetCode = CCliMessageHandler::GetInstance().DoMSAddExerciseTime(poRole->GetObjID(), pMsg->nHour);
    LOG_PROCESS_ERROR(nRetCode);

    poRole->SetDoingSubTime(TRUE);

    return;

Exit0:
    DoErrorCodeNotify(poRole, nResult, 0, 0);
}

void CCliMessageHandler::OnGetExerciseExp(CRole* poRole, const char* pData)
{
    INT32 nResult = errItemUnknown;
    INT32 nRetCode;
    INT32 hour;
    const ROLE_LEVEL_DATA* level_data = NULL;

    CNpc* npc = CGameWorld::GetInstance().FindNpc(poRole->GetInteractNpc());
    PROCESS_ERROR_RET_CODE(npc, errNpcNotFound);

    nRetCode = poRole->CanInteract(npc);
    PROCESS_ERROR_RET_CODE(nRetCode == errSuccess, nRetCode);

    LOG_PROCESS_ERROR_RET_CODE(npc->GetNpcData()->bInteractExercise, errNpcNoSuchFunction);

    level_data = CDataManager<ROLE_LEVEL_DATA>::GetInstance().GetData(poRole->GetLevel());
    LOG_PROCESS_ERROR(level_data);

    LOG_PROCESS_ERROR_RET_CODE(!poRole->IsDead(), errItemRoleDead);
    LOG_PROCESS_ERROR_RET_CODE(poRole->GetMoveState() != CMS_STALL, errItemStall);
    LOG_PROCESS_ERROR_RET_CODE(!poRole->GetTrade()->IsTrading(), errItemTrading);

    hour = poRole->GetCurExerciseTime() / 3600;
    PROCESS_ERROR_RET_CODE(hour > 0, errItemNoExerciseTime);

    poRole->SetTotalExerciseTime(poRole->GetTotalExerciseTime() - hour * 3600);
    if (poRole->GetTotalExerciseTime() == 0)
        poRole->SetStartExerciseTime(0);
    else
        poRole->SetStartExerciseTime(poRole->GetStartExerciseTime() + hour * 3600);

    poRole->AddExp(hour * level_data->m_nExerciseExpPerHour, FALSE, FALSE);
    CCliMessageHandler::GetInstance().DoGetExerciseExp(poRole, hour, 100);

    poRole->GetAchievementList().AddVariable(avdExeciseTime, hour);

    return;

Exit0:
    DoErrorCodeNotify(poRole, nResult, 0, 0);
}

// 铭文高级洗练
void CCliMessageHandler::OnRuneItemAdvance(CRole* poRole, const char* pData)
{
    C2G_RUNE_ITEM_ADVANCE* pMsg = (C2G_RUNE_ITEM_ADVANCE*)pData;

    INT32 err = poRole->GetItemBag()->RuneItemAdvance(pMsg->byWeaponConSlot, pMsg->byWeaponItemSlot, pMsg->nRuneItemID);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

// 确认高级洗练
void CCliMessageHandler::OnRuneItemConfirm(CRole* poRole, const char* pData)
{
    C2G_RUNE_ITEM_ADVANCE_CONFIRM* pMsg = (C2G_RUNE_ITEM_ADVANCE_CONFIRM*)pData;

    INT32 err = poRole->GetItemBag()->RuneItemConfirm(pMsg->byWeaponConSlot, pMsg->byWeaponItemSlot);
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

void CCliMessageHandler::OnSellResourceItem(CRole* poRole, const char* pData)
{
}

// 技能书重著
void CCliMessageHandler::OnSpellBookGamble(CRole* poRole, const char* pData)
{
    // 暂时 屏蔽功能
    //poRole->ErrorCodeNotify(errNpcNoSuchFunction, 0, 0);

    INT32 err = poRole->GetItemBag()->SpellBookGamble();
    if (err != errSuccess)
    {
        poRole->ErrorCodeNotify(err, 0, 0);
    }
}

// ==================== 下面全是 g2c发包 Do函数

BOOL CCliMessageHandler::DoSyncRefineLevels(CRole* pRole)
{
    INT32 nRetCode = 0;
    G2C_SYNC_REFINE* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_SYNC_REFINE*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_REFINE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_refine;
    pRole->GetItemBag()->GetRefineLevels(pMsg->awRefineLevel);

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SYNC_REFINE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSyncMoney(CRole* pRole)
{
    INT32 nRetCode = 0;
    G2C_SYNC_MONEY* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_SYNC_MONEY*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_MONEY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_money;
    pRole->GetItemBag()->GetMoneyAllInfo(
        pMsg->allMoneys,
        pMsg->allMoneysLimit,
        pMsg->anDailyEarned,
        pMsg->anDailyEarnedLimit,
        pMsg->anDailyUsed,
        pMsg->anDailyUsedLimit,
        pMsg->anWeeklyEarned,
        pMsg->anWeeklyEarnedLimit,
        pMsg->anWeeklyUsed,
        pMsg->anWeeklyUsedLimit);
    pMsg->byUseMoneytype01Only = pRole->GetItemBag()->GetUseMoneytype01Only();

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SYNC_MONEY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSyncRealMoney(CRole* pRole)
{
    INT32 nRetCode = 0;
    M2C_SYNC_REAL_MONEY* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (M2C_SYNC_REAL_MONEY*)m_poPacketAllocator->Alloc(sizeof(M2C_SYNC_REAL_MONEY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = m2c_sync_real_money;
    pMsg->nBalance = 1000000;    // 应该写 pRole->m_dwRealMoney 要新加字段

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(M2C_SYNC_REAL_MONEY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSyncContainerSizes(CRole* pRole)
{
    INT32 nRetCode = 0;
    G2C_SYNC_CONTAINER_SIZES* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_SYNC_CONTAINER_SIZES*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_CONTAINER_SIZES));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_container_sizes;
    pRole->GetItemBag()->GetContainerSizes(pMsg->abySizes);

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SYNC_CONTAINER_SIZES));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSyncItemBag(CRole* pRole)
{
    INT32 nRetCode = 0;
    G2C_SYNC_ITEM_BAG* pMsg = NULL;
    const Item* item = NULL;
    char* itembuf = NULL;
    UINT32 itemlen = 0;
    CItemBag* bag = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_SYNC_ITEM_BAG*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_item_bag;
    pMsg->wSize = sizeof(G2C_SYNC_ITEM_BAG);
    pMsg->byItemCount = 0;
    bag = pRole->GetItemBag();

    bag->Begin();

    itembuf = pMsg->acItems;
    while ((item = bag->Next()) != NULL)
    {
        LOG_PROCESS_ERROR(itemlen < MAX_MESSAGE_SIZE - sizeof(G2C_SYNC_ITEM_BAG) - sizeof(ItemInfo) - 128);
        itemlen = item->m_iteminfo.Save(itembuf);
        itembuf += itemlen;
        pMsg->wSize += itemlen;
        pMsg->byItemCount++;
    }

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSyncRoleEquipData(CRole* poRole, CRole* poTargetRole, UINT32 dwCRC)
{
    INT32 nRetCode = 0;
    G2C_SYNC_ROLE_EQUIP_DATA* pMsg = NULL;
    const Item* item = NULL;
    char* itembuf = NULL;
    UINT32 itemlen = 0;
    CItemBag* bag = NULL;
    UINT32 dwNewCRC = 0;

    LOG_PROCESS_ERROR(poRole);
    LOG_PROCESS_ERROR(poTargetRole);

    pMsg = (G2C_SYNC_ROLE_EQUIP_DATA*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_role_equip_data;
    pMsg->wSize = sizeof(G2C_SYNC_ROLE_EQUIP_DATA);
    pMsg->byItemCount = 0;
    pMsg->dwRoleID = poTargetRole->GetObjID();
    bag = poTargetRole->GetItemBag();
    bag->GetRefineLevels(pMsg->awRefineLevels);

    bag->Begin();

    itembuf = pMsg->acItems;
    while ((item = bag->Next()) != NULL)
    {
        if (item->m_iteminfo.m_byConSlot != CONSLOT_EQUIPPED)
            continue;

        LOG_PROCESS_ERROR(itemlen < MAX_MESSAGE_SIZE - sizeof(G2C_SYNC_ROLE_EQUIP_DATA) - sizeof(ItemInfo) - 128);
        itemlen = item->m_iteminfo.Save(itembuf);
        itembuf += itemlen;
        pMsg->wSize += itemlen;
        pMsg->byItemCount++;
    }

    dwNewCRC = crc32(0, (const Bytef*)pMsg, pMsg->wSize);

    if (dwNewCRC != dwCRC)
    {
        nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    }

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;

}

BOOL CCliMessageHandler::DoSendMoneyChange(CRole* pRole, INT32 moneytype, INT64 money, INT32 dailyearned, INT32 dailyused, INT32 weeklyearned, INT32 weeklyused)
{
    INT32 nRetCode = 0;
    G2C_MONEY_CHANGE* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_MONEY_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_MONEY_CHANGE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_money_change;
    pMsg->nMoneyType = moneytype;
    pMsg->llMoney = money;
    pMsg->nDailyEarned = dailyearned;
    pMsg->nDailyUsed = dailyused;
    pMsg->nWeeklyEarned = weeklyearned;
    pMsg->nWeeklyUsed = weeklyused;

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_MONEY_CHANGE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendItemChange(CRole* pRole, Item* item)
{
    INT32 nRetCode = 0;
    G2C_ITEM_CHANGE* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(item);

    pMsg = (G2C_ITEM_CHANGE*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_item_change;
    pMsg->wSize = (UINT16)(sizeof(G2C_ITEM_CHANGE) + item->m_iteminfo.Save(pMsg->acItem));
    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoSendEquipDurChange(CRole* pRole, UINT8 conslot, UINT8 itemslot, INT32 dur)
{
    INT32 nRetCode = 0;
    G2C_EQUIP_DUR_CHANGE* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_EQUIP_DUR_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_EQUIP_DUR_CHANGE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_equip_dur_change;
    pMsg->byConSlot = conslot;
    pMsg->byEquipSlot = itemslot;
    pMsg->nDur = dur;
    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_EQUIP_DUR_CHANGE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoSendItemSwap(CRole* pRole, UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot)
{
    INT32 nRetCode = 0;
    G2C_ITEM_SWAP* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_ITEM_SWAP*)m_poPacketAllocator->Alloc(sizeof(G2C_ITEM_SWAP));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_item_swap;
    pMsg->bySrcConSlot = srcconslot;
    pMsg->bySrcItemSlot = srcitemslot;
    pMsg->byDstConSlot = dstconslot;
    pMsg->byDstItemSlot = dstitemslot;

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (char*)pMsg, sizeof(G2C_ITEM_SWAP));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendItemDelete(CRole* pRole, UINT8 conslot, UINT8 itemslot)
{
    INT32 nRetCode = 0;
    G2C_ITEM_DELETE* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_ITEM_DELETE*)m_poPacketAllocator->Alloc(sizeof(G2C_ITEM_DELETE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_item_delete;
    pMsg->byConSlot = conslot;
    pMsg->byItemSlot = itemslot;

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (char*)pMsg, sizeof(G2C_ITEM_DELETE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendDestroyDeathItem(CRole* pRole, Item* item)
{
    INT32 nRetCode = 0;
    G2C_DESTROY_DEATH_ITEM* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(item);

    pMsg = (G2C_DESTROY_DEATH_ITEM*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_destroy_death_item;
    pMsg->wSize = (UINT16)(sizeof(G2C_DESTROY_DEATH_ITEM) + item->m_iteminfo.Save(pMsg->acItem));
    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoSendLosePkItem(CRole* pRole, Item* item)
{
    INT32 nRetCode = 0;
    G2C_LOSE_PK_ITEM* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(item);

    pMsg = (G2C_LOSE_PK_ITEM*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_lose_pk_item;
    pMsg->wSize = (UINT16)(sizeof(G2C_LOSE_PK_ITEM) + item->m_iteminfo.Save(pMsg->acItem));
    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoSendSoldItemList(CRole* poRole, const std::list<Item*>& items)
{
    INT32 nRetCode = 0;
    UINT16 bufsize = 0;
    G2C_VIEW_SOLD_ITEMS* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_VIEW_SOLD_ITEMS*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_view_sold_items;
    pMsg->byCount = 0;
    for (std::list<Item*>::const_iterator it = items.begin(); it != items.end(); ++it)
    {
        bufsize += (*it)->m_iteminfo.Save(pMsg->acItems + bufsize);
        pMsg->byCount++;
    }
    pMsg->wSize = sizeof(G2C_VIEW_SOLD_ITEMS) + bufsize;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendRepairItem(CRole* poRole)
{
    INT32 nRetCode = 0;
    G2C_REPAIR_ITEM* pMsg = (G2C_REPAIR_ITEM*)m_poPacketAllocator->Alloc(sizeof(G2C_REPAIR_ITEM));
    LOG_PROCESS_ERROR(pMsg);

    LOG_PROCESS_ERROR(poRole);

    pMsg->wMsg = g2c_repair_item;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_REPAIR_ITEM));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendContainerSizeChange(CRole* pRole, UINT8 conslot, UINT8 consize)
{
    INT32 nRetCode = 0;
    G2C_CONTAINER_SIZE_CHANGE* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_CONTAINER_SIZE_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_CONTAINER_SIZE_CHANGE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_container_size_change;
    pMsg->byConSlot = conslot;
    pMsg->byConSize = consize;

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (char*)pMsg, sizeof(G2C_CONTAINER_SIZE_CHANGE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSyncRoleAvatar(CRole* pRole, UINT8 conslot, UINT8 itemslot, INT32 nItemTemplateID, UINT8 byRefineFx)
{
    INT32 nRetCode = 0;
    G2C_SYNC_ROLE_AVATAR* pMsg = NULL;

    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_SYNC_ROLE_AVATAR*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_ROLE_AVATAR));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_role_avatar;
    pMsg->dwRoleID = pRole->GetObjID();
    pMsg->byConSlot = conslot;
    pMsg->byItemSlot = itemslot;
    pMsg->nTemplateID = nItemTemplateID;
    pMsg->byRefineFx = byRefineFx;

    nRetCode = _Broadcast9Region(pRole->GetRegion(), (char*)pMsg, sizeof(G2C_SYNC_ROLE_AVATAR));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSyncHeroAvatar(CRole* poRole, UINT8 conslot, UINT8 itemslot, INT32 nItemTemplateID)
{
    INT32 nRetCode = 0;
    G2C_SYNC_HERO_AVATAR* pMsg = NULL;
    CHero* poHero = NULL;

    LOG_PROCESS_ERROR(poRole);

    poHero = poRole->GetHero();
    LOG_PROCESS_ERROR(poHero);

    pMsg = (G2C_SYNC_HERO_AVATAR*)m_poPacketAllocator->Alloc(sizeof(G2C_SYNC_HERO_AVATAR));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_hero_avatar;
    pMsg->dwHeroID = poHero->GetObjID();
    pMsg->byConSlot = conslot;
    pMsg->byItemSlot = itemslot;
    pMsg->nTemplateID = nItemTemplateID;

    nRetCode = _Broadcast9Region(poRole->GetRegion(), (char*)pMsg, sizeof(G2C_SYNC_HERO_AVATAR));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendTradeStateChange(CRole* poRole, UINT32 dwRoleID, UINT8 byState)
{
    INT32 nRetCode = 0;
    G2C_TRADE_STATE_CHANGE* pMsg = (G2C_TRADE_STATE_CHANGE*)m_poPacketAllocator->Alloc(sizeof(G2C_TRADE_STATE_CHANGE));
    LOG_PROCESS_ERROR(pMsg);
    LOG_PROCESS_ERROR(poRole);

    pMsg->wMsg = g2c_trade_state_change;
    pMsg->dwRoleID = dwRoleID;
    pMsg->byTradeState = byState;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_TRADE_STATE_CHANGE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendTradeItem(CRole* poRole, UINT32 dwRoleID, UINT8 byTradeSlot, UINT8 bAdd, Item* item)
{
    INT32 nRetCode = 0;
    G2C_TRADE_SET_ITEM* pMsg = (G2C_TRADE_SET_ITEM*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_trade_set_item;
    pMsg->dwRoleID = dwRoleID;
    pMsg->byTradeSlot = byTradeSlot;
    pMsg->bAdd = bAdd;
    if (bAdd)
    {
        LOG_PROCESS_ERROR(item);
        pMsg->wSize = (UINT16)(sizeof(G2C_TRADE_SET_ITEM) + item->m_iteminfo.Save(pMsg->acItem));
    }
    else
    {
        pMsg->wSize = sizeof(G2C_TRADE_SET_ITEM);
    }

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendTradeMoney(CRole* poRole, UINT32 dwRoleID, INT32 nMoney)
{
    INT32 nRetCode = 0;
    G2C_TRADE_SET_MONEY* pMsg = (G2C_TRADE_SET_MONEY*)m_poPacketAllocator->Alloc(sizeof(G2C_TRADE_SET_MONEY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_trade_set_money;
    pMsg->dwRoleID = dwRoleID;
    pMsg->nMoney = nMoney;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_TRADE_SET_MONEY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendUpgradeSoulResult(CRole* poRole, UINT8 byResult)
{
    INT32 nRetCode = 0;
    G2C_UPGRADE_SOUL* pMsg = (G2C_UPGRADE_SOUL*)m_poPacketAllocator->Alloc(sizeof(G2C_UPGRADE_SOUL));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_upgrade_soul;
    pMsg->byResult = byResult;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_UPGRADE_SOUL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendAddSoulResult(CRole* poRole, UINT8 byResult)
{
    INT32 nRetCode = 0;
    G2C_ADD_SOUL* pMsg = (G2C_ADD_SOUL*)m_poPacketAllocator->Alloc(sizeof(G2C_ADD_SOUL));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_add_soul;
    pMsg->byResult = byResult;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_ADD_SOUL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendRemoveSoulResult(CRole* poRole, UINT8 byResult)
{
    INT32 nRetCode = 0;
    G2C_REMOVE_SOUL* pMsg = (G2C_REMOVE_SOUL*)m_poPacketAllocator->Alloc(sizeof(G2C_REMOVE_SOUL));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_remove_soul;
    pMsg->byResult = byResult;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_REMOVE_SOUL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendRuneItem(CRole* poRole, UINT8 byResult)
{
    INT32 nRetCode = 0;
    G2C_RUNE_ITEM* pMsg = (G2C_RUNE_ITEM*)m_poPacketAllocator->Alloc(sizeof(G2C_RUNE_ITEM));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_rune_item;
    pMsg->byResult = byResult;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_RUNE_ITEM));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

// 高级铭文洗练
BOOL CCliMessageHandler::DoSendRuneItemAdvance(CRole* poRole, UINT8 byResult, UINT16 wRuneA, UINT16 wRuneB)
{
    INT32 nRetCode = 0;
    G2C_RUNE_ITEM_ADVANCE* pMsg = (G2C_RUNE_ITEM_ADVANCE*)m_poPacketAllocator->Alloc(sizeof(G2C_RUNE_ITEM_ADVANCE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_rune_item_advance;
    pMsg->byResult = byResult;
    pMsg->wRune[0] = wRuneA;
    pMsg->wRune[1] = wRuneB;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_RUNE_ITEM_ADVANCE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

// 确认高级洗练
BOOL CCliMessageHandler::DoSendRuneItemConfirm(CRole* poRole, UINT8 byResult)
{
    INT32 nRetCode = 0;
    G2C_RUNE_ITEM_ADVANCE_CONFIRM* pMsg = (G2C_RUNE_ITEM_ADVANCE_CONFIRM*)m_poPacketAllocator->Alloc(sizeof(G2C_RUNE_ITEM_ADVANCE_CONFIRM));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_rune_item_advance_confirm;
    pMsg->byResult = byResult;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_RUNE_ITEM_ADVANCE_CONFIRM));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendWeaponLevelUpPutIn(CRole* poRole)
{
    INT32 nRetCode = 0;
    G2C_WEAPON_LEVEL_UP_PUT_IN* pMsg = (G2C_WEAPON_LEVEL_UP_PUT_IN*)m_poPacketAllocator->Alloc(sizeof(G2C_WEAPON_LEVEL_UP_PUT_IN));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_weapon_level_up_put_in;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_WEAPON_LEVEL_UP_PUT_IN));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendWeaponLevelUpTakeOut(CRole* poRole)
{
    INT32 nRetCode = 0;
    G2C_WEAPON_LEVEL_UP_TAKE_OUT* pMsg = (G2C_WEAPON_LEVEL_UP_TAKE_OUT*)m_poPacketAllocator->Alloc(sizeof(G2C_WEAPON_LEVEL_UP_TAKE_OUT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_weapon_level_up_take_out;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_WEAPON_LEVEL_UP_TAKE_OUT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendWeaponLevelUpResult(CRole* poRole, UINT8 byResult)
{
    INT32 nRetCode = 0;
    G2C_WEAPON_LEVEL_UP_RESULT* pMsg = (G2C_WEAPON_LEVEL_UP_RESULT*)m_poPacketAllocator->Alloc(sizeof(G2C_WEAPON_LEVEL_UP_RESULT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_weapon_level_up_result;
    pMsg->byResult = byResult;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_WEAPON_LEVEL_UP_RESULT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendDecomposeResult(CRole* poRole, UINT8 byResult, INT32 original_itemid, INT32 itemid[], INT32 itemcount[])
{
    INT32 nRetCode = 0;
    G2C_DECOMPOSE* pMsg = (G2C_DECOMPOSE*)m_poPacketAllocator->Alloc(sizeof(G2C_DECOMPOSE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_decompose;
    pMsg->byResult = byResult;
    pMsg->nOriginalItemID = original_itemid;
    memcpy(pMsg->nItemID, itemid, sizeof(pMsg->nItemID));
    memcpy(pMsg->nItemCount, itemcount, sizeof(pMsg->nItemCount));

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_DECOMPOSE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendComposeResult(CRole* poRole, UINT8 byResult, INT32 nItemID)
{
    INT32 nRetCode = 0;
    G2C_COMPOSE* pMsg = (G2C_COMPOSE*)m_poPacketAllocator->Alloc(sizeof(G2C_COMPOSE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_compose;
    pMsg->byResult = byResult;
    pMsg->nResultItemID = nItemID;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_COMPOSE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendRefineResult(CRole* poRole, UINT8 bySlot, UINT8 byResult, UINT16 wRefineLevel)
{
    INT32 nRetCode = 0;
    G2C_REFINE* pMsg = (G2C_REFINE*)m_poPacketAllocator->Alloc(sizeof(G2C_REFINE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_refine;
    pMsg->bySlot = bySlot;
    pMsg->byResult = byResult;
    pMsg->wRefineLevel = wRefineLevel;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (char*)pMsg, sizeof(G2C_REFINE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendRandomizeItem(CRole* pRole, Item* item)
{
    INT32 nRetCode = 0;
    G2C_RANDOMIZE_ITEM* pMsg = (G2C_RANDOMIZE_ITEM*)m_poPacketAllocator->Alloc(sizeof(G2C_RANDOMIZE_ITEM));

    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(item);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_randomize_item;
    memcpy(pMsg->wRandomAttrID, item->m_iteminfo.m_wRandomAttrID, sizeof(pMsg->wRandomAttrID));
    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_RANDOMIZE_ITEM));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoSendIdentifyResult(CRole* pRole, UINT8 byResult)
{
    INT32 nRetCode = 0;
    G2C_IDENTIFY_ITEM* pMsg = (G2C_IDENTIFY_ITEM*)m_poPacketAllocator->Alloc(sizeof(G2C_IDENTIFY_ITEM));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_identify_item;
    pMsg->byResult = byResult;

    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (char*)pMsg, sizeof(G2C_IDENTIFY_ITEM));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSendLuckOilResult(CRole* pRole, INT8 result)
{
    INT32 nRetCode = 0;
    G2C_LUCK_OIL* pMsg = (G2C_LUCK_OIL*)m_poPacketAllocator->Alloc(sizeof(G2C_LUCK_OIL));

    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_luck_oil;
    pMsg->chResult = result;
    nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_LUCK_OIL));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);

    return FALSE;
}

BOOL CCliMessageHandler::DoGenerateDropFromObject(CDrop* poDrop, UINT32 dwSrcObjID)
{
    INT32 nRetCode = 0;
    G2C_GENERATE_DROP_FROM_OBJECT* pMsg = NULL;

    LOG_PROCESS_ERROR(poDrop);
    LOG_PROCESS_ERROR(poDrop->m_content.m_type == DropContent::DROP_ITEM || poDrop->m_content.m_type == DropContent::DROP_MONEY);

    pMsg = (G2C_GENERATE_DROP_FROM_OBJECT*)m_poPacketAllocator->Alloc(sizeof(G2C_GENERATE_DROP_FROM_OBJECT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_generate_drop_from_object;
    pMsg->dwSrcID = dwSrcObjID;
    pMsg->drop.dwDropID = poDrop->GetObjID();
    if (poDrop->m_content.m_type == DropContent::DROP_ITEM)
    {
        pMsg->drop.nTemplateID = poDrop->m_content.m_item->m_pTemplate->m_nTemplateID;
        pMsg->drop.nCount = poDrop->m_content.m_item->m_pTemplate->m_byDurType == DURTYPE_STACK ? poDrop->m_content.m_item->m_iteminfo.m_nCurDur : 1;
    }
    else
    {
        pMsg->drop.nTemplateID = poDrop->m_content.m_money.moneytype;
        pMsg->drop.nCount = poDrop->m_content.m_money.count;
    }
    pMsg->drop.wDestX = ConvertCoordS2N(poDrop->GetX());
    pMsg->drop.wDestY = ConvertCoordS2N(poDrop->GetY());
    pMsg->drop.wDestZ = ConvertCoordS2N(poDrop->GetZ());

    nRetCode = _Broadcast9Region(poDrop->GetRegion(), (PACKET_BUFFER*)pMsg, sizeof(G2C_GENERATE_DROP_FROM_OBJECT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

struct CTraverseDrop
{
    G2C_SYNC_DROP_LIST* pMsg;

    BOOL operator()(CDrop* poDrop)
    {
        LOG_PROCESS_ERROR(poDrop);
        LOG_PROCESS_ERROR(poDrop->m_content.m_type == DropContent::DROP_ITEM || poDrop->m_content.m_type == DropContent::DROP_MONEY);
        LOG_PROCESS_ERROR(pMsg->nCount < MAX_DROP_COUNT);

        {
            DROP_INFO& rDropInfo = pMsg->astDrops[pMsg->nCount];

            rDropInfo.dwDropID = poDrop->GetObjID();
            if (poDrop->m_content.m_type == DropContent::DROP_ITEM)
            {
                rDropInfo.nTemplateID = poDrop->m_content.m_item->m_pTemplate->m_nTemplateID;
                rDropInfo.nCount = poDrop->m_content.m_item->m_pTemplate->m_byDurType == DURTYPE_STACK ? poDrop->m_content.m_item->m_iteminfo.m_nCurDur : 1;
            }
            else
            {
                rDropInfo.nTemplateID = poDrop->m_content.m_money.moneytype;
                rDropInfo.nCount = poDrop->m_content.m_money.count;
            }
            rDropInfo.wDestX = ConvertCoordS2N(poDrop->GetX());
            rDropInfo.wDestY = ConvertCoordS2N(poDrop->GetY());
            rDropInfo.wDestZ = ConvertCoordS2N(poDrop->GetZ());

            pMsg->nCount++;
        }

        return TRUE;
    Exit0:
        return FALSE;
    }
};

BOOL CCliMessageHandler::DoSyncDropList(CRole* pRole, CRegion* poRegion)
{
    INT32 nRetCode = 0;
    CTraverseDrop TraverseDrop;
    G2C_SYNC_DROP_LIST* pMsg = NULL;

    LOG_PROCESS_ERROR(poRegion);
    LOG_PROCESS_ERROR(pRole);

    pMsg = (G2C_SYNC_DROP_LIST*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sync_drop_list;
    pMsg->byIsNew = 0;
    pMsg->nCount = 0;

    TraverseDrop.pMsg = pMsg;

    nRetCode = poRegion->TraverseDrop(TraverseDrop);
    LOG_CHECK_ERROR(nRetCode);

    if (pMsg->nCount > 0)
    {
        pMsg->wSize = (UINT16)(sizeof(G2C_SYNC_DROP_LIST) + sizeof(DROP_INFO) * pMsg->nCount);

        nRetCode = m_poNotifier->SendToUser(pRole->GetSessionID(), (PACKET_BUFFER*)TraverseDrop.pMsg, TraverseDrop.pMsg->wSize);
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    }

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoPickUpItem(CRole* poRole, UINT32 pickerid, const Item* item)
{
    G2C_PICKUP_ITEM* pMsg = NULL;
    CTeamInGS* pTeam = NULL;
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_PICKUP_ITEM*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_pickup_item;
    pMsg->dwRoleID = pickerid;
    pMsg->wSize = (UINT16)(sizeof(G2C_PICKUP_ITEM) + item->m_iteminfo.Save(pMsg->acItem));

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoPickUpMoney(CRole* poRole, INT32 moneytype, INT32 count)
{
    G2C_PICKUP_MONEY* pMsg = NULL;
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_PICKUP_MONEY*)m_poPacketAllocator->Alloc(sizeof(G2C_PICKUP_MONEY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_pickup_money;
    pMsg->nMoneyType = moneytype;
    pMsg->nCount = count;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_PICKUP_MONEY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;

Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSDropLimit(INT32 nItemID, INT32 nItemCount)
{
    INT32 nRetCode = 0;

    InternalMessage::G2M_DROP_LIMIT* pMsg = (InternalMessage::G2M_DROP_LIMIT*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_DROP_LIMIT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_drop_limit;
    pMsg->nItemID = nItemID;
    pMsg->nDropCount = nItemCount;

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_DROP_LIMIT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSignItem(CRole* poRole, UINT8 byConSlot, UINT8 byItemSlot, UCHAR* ucSign, UINT32 dwSignSize)
{
    INT32  nRetCode = 0;
    G2C_SIGN_ITEM* pMsg = NULL;

    LOG_PROCESS_ERROR(poRole);

    pMsg = (G2C_SIGN_ITEM*)m_poPacketAllocator->Alloc(sizeof(G2C_SIGN_ITEM));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_sign_item;
    pMsg->byConSlot = byConSlot;
    pMsg->byItemSlot = byItemSlot;
    memcpy(&pMsg->bySign, ucSign, dwSignSize);

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SIGN_ITEM));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoBlackMarketLimitInfo(CRole* poRole)
{
    INT32  nRetCode = 0;

    const std::map<INT32, CItemBag::BMRoleLimitInfo>& role_limit = poRole->GetItemBag()->GetBlackMarketLimitInfo();
    const CGameWorld::MS_BM_LIMIT_MAP& server_limit = CGameWorld::GetInstance().GetMSBMLimitMap();

    INT32 size = sizeof(G2C_BLACK_MARKET_LIMIT_INFO) + sizeof(BLACK_MARKET_LIMIT_INFO) * (role_limit.size() + server_limit.size());
    G2C_BLACK_MARKET_LIMIT_INFO* pMsg = (G2C_BLACK_MARKET_LIMIT_INFO*)m_poPacketAllocator->Alloc(size);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_black_market_limit_info;
    pMsg->wSize = size;
    pMsg->nLimitInfoCount = 0;

    for (std::map<INT32, CItemBag::BMRoleLimitInfo>::const_iterator it = role_limit.begin(); it != role_limit.end(); ++it)
    {
        pMsg->LimitInfo[pMsg->nLimitInfoCount].nBlackMarketProductID = it->first;
        pMsg->LimitInfo[pMsg->nLimitInfoCount].nCount = it->second.nCount;
        pMsg->nLimitInfoCount++;
    }

    for (CGameWorld::MS_BM_LIMIT_MAP::const_iterator it = server_limit.begin(); it != server_limit.end(); ++it)
    {
        pMsg->LimitInfo[pMsg->nLimitInfoCount].nBlackMarketProductID = it->first;
        pMsg->LimitInfo[pMsg->nLimitInfoCount].nCount = it->second;
        pMsg->nLimitInfoCount++;
    }

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, size);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoBlackMarketCooldownInfo(CRole* poRole)
{
    INT32  nRetCode = 0;

    const std::map<INT32, UINT32>& cooldown_info = poRole->GetItemBag()->GetBlackMarketCooldownInfo();

    INT32 size = sizeof(G2C_BLACK_MARKET_LIMIT_INFO) + sizeof(BLACK_MARKET_LIMIT_INFO) * cooldown_info.size();
    G2C_BLACK_MARKET_COOLDOWN_INFO* pMsg = (G2C_BLACK_MARKET_COOLDOWN_INFO*)m_poPacketAllocator->Alloc(size);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_black_market_cooldown_info;
    pMsg->wSize = size;
    pMsg->nCooldownInfoCount = 0;

    poRole->GetItemBag()->UpdateBlackMarketCooldown();
    for (std::map<INT32, UINT32>::const_iterator it = cooldown_info.begin(); it != cooldown_info.end(); ++it)
    {
        pMsg->CooldownInfo[pMsg->nCooldownInfoCount].nBlackMarketProductID = it->first;
        pMsg->CooldownInfo[pMsg->nCooldownInfoCount].dwCooldown = it->second;
        pMsg->nCooldownInfoCount++;
    }

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, size);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoBlackMarketBuy(CRole* poRole, INT32 nBlackMarketProductID, INT32 nCount)
{
    INT32 nRetCode = 0;

    G2C_BLACK_MARKET_BUY* pMsg = (G2C_BLACK_MARKET_BUY*)m_poPacketAllocator->Alloc(sizeof(G2C_BLACK_MARKET_BUY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_black_market_buy;
    pMsg->nBlackMarketProductID = nBlackMarketProductID;
    pMsg->nCount = nCount;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_BLACK_MARKET_BUY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoGamble(CRole* poRole, INT32 nResult, INT32 nItemID)
{
    INT32 nRetCode = 0;

    G2C_GAMBLE* pMsg = (G2C_GAMBLE*)m_poPacketAllocator->Alloc(sizeof(G2C_GAMBLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_gamble;
    pMsg->nResult = nResult;
    pMsg->nItemID = nItemID;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_GAMBLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoSpellBookGamble(CRole* poRole, INT32 nResult, INT32 nItemID)
{
    INT32 nRetCode = 0;

    G2C_SPELL_BOOK_GAMBLE* pMsg = (G2C_SPELL_BOOK_GAMBLE*)m_poPacketAllocator->Alloc(sizeof(G2C_SPELL_BOOK_GAMBLE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_spell_book_gamble;
    pMsg->nResult = nResult;
    pMsg->nItemID = nItemID;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_SPELL_BOOK_GAMBLE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoExerciseInfo(CRole* poRole, INT32 nTotalHour, INT32 nCurHour)
{
    INT32 nRetCode = 0;

    G2C_EXERCISE_INFO* pMsg = (G2C_EXERCISE_INFO*)m_poPacketAllocator->Alloc(sizeof(G2C_EXERCISE_INFO));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_exercise_info;
    pMsg->nTotalHour = nTotalHour;
    pMsg->nCurHour = nCurHour;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_EXERCISE_INFO));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoAddExerciseTime(CRole* poRole, INT32 nTotalHour)
{
    INT32 nRetCode = 0;

    G2C_ADD_EXERCISE_TIME* pMsg = (G2C_ADD_EXERCISE_TIME*)m_poPacketAllocator->Alloc(sizeof(G2C_ADD_EXERCISE_TIME));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_add_exercise_time;
    pMsg->nTotalHour = nTotalHour;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_ADD_EXERCISE_TIME));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoGetExerciseExp(CRole* poRole, INT32 nHour, INT32 nExp)
{
    INT32 nRetCode = 0;

    G2C_GET_EXERCISE_EXP* pMsg = (G2C_GET_EXERCISE_EXP*)m_poPacketAllocator->Alloc(sizeof(G2C_GET_EXERCISE_EXP));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = g2c_get_exercise_exp;
    pMsg->nHour = nHour;
    pMsg->nExp = nExp;

    nRetCode = m_poNotifier->SendToUser(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(G2C_GET_EXERCISE_EXP));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSAuctionSell(INT32 nResult, UINT32 dwRoleID, UINT8 byTimeType, UINT8 byOpen, INT64 llPrice, INT64 llBuyoutPrice, INT64 llDepositePrice, CHAR* szItemInfo, UINT32 dwItemInfoSize)
{
    INT32 nRetCode = 0;
    UINT32 dwSize = sizeof(InternalMessage::G2M_AUCTION_SELL);
    InternalMessage::G2M_AUCTION_SELL* pMsg = (InternalMessage::G2M_AUCTION_SELL*)m_poPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_auction_sell;
    pMsg->nResult = nResult;
    pMsg->dwRoleID = dwRoleID;
    pMsg->byTimeType = byTimeType;
    pMsg->byOpen = byOpen;
    pMsg->llPrice = llPrice;
    pMsg->llBuyoutPrice = llBuyoutPrice;
    pMsg->llDepositePrice = llDepositePrice;
    if (nResult == errSuccess)
    {
        memset(pMsg->acItem, 0, dwItemInfoSize);

        // 自己改代码
        dwSize += dwItemInfoSize;
        memcpy_s(pMsg->acItem, dwItemInfoSize, szItemInfo, dwItemInfoSize);

        // 默认代码
        //LOG_PROCESS_ERROR(item);
        //dwSize += item->m_iteminfo.Save(pMsg->acItem);
    }

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, dwSize);
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSAuctionBuy(INT32 nResult, UINT32 dwRoleID, UINT32 dwAuctionID, INT64 llPrice)
{
    INT32 nRetCode = 0;
    InternalMessage::G2M_AUCTION_BUY* pMsg = (InternalMessage::G2M_AUCTION_BUY*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_AUCTION_BUY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_auction_buy;
    pMsg->nResult = nResult;
    pMsg->dwRoleID = dwRoleID;
    pMsg->dwAuctionID = dwAuctionID;
    pMsg->llPrice = llPrice;

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_AUCTION_BUY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSAuctionPay(INT32 nResult, UINT32 dwRoleID, UINT32 dwAuctionID, INT64 llPrice)
{
    INT32 nRetCode = 0;
    InternalMessage::G2M_AUCTION_PAY* pMsg = (InternalMessage::G2M_AUCTION_PAY*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_AUCTION_PAY));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_auction_pay;
    pMsg->nResult = nResult;
    pMsg->dwRoleID = dwRoleID;
    pMsg->dwAuctionID = dwAuctionID;
    pMsg->llPrice = llPrice;

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_AUCTION_PAY));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSExchangeAddOrder(INT32 nResult, UINT32 dwRoleID, INT32 nItemIDRequire, INT32 nItemCountRequire, UINT8 byOrderType, INT32 nPriceOrder, INT32 nCountOrder)
{
    INT32 nRetCode = 0;
    InternalMessage::G2M_EXCHANGE_ADD_ORDER* pMsg = (InternalMessage::G2M_EXCHANGE_ADD_ORDER*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_EXCHANGE_ADD_ORDER));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_exchange_add_order;
    pMsg->nResult = nResult;
    pMsg->dwRoleID = dwRoleID;
    pMsg->nItemIDRequire = nItemIDRequire;
    pMsg->nItemCountRequire = nItemCountRequire;
    pMsg->byOrderType = byOrderType;
    pMsg->nPriceOrder = nPriceOrder;
    pMsg->nCountOrder = nCountOrder;

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_EXCHANGE_ADD_ORDER));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSGetBlackMarketLimitInfo(UINT32 dwRoleID)
{
    INT32 nRetCode = 0;
    InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO* pMsg = (InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_get_black_market_limit_info;
    pMsg->dwRoleID = dwRoleID;

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSCheckBlackMarketProduct(UINT32 dwRoleID, INT32 nBlackMarketProductID)
{
    INT32 nRetCode = 0;
    InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT* pMsg = (InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_check_black_market_product;
    pMsg->dwRoleID = dwRoleID;
    pMsg->nBlackMarketProductID = nBlackMarketProductID;

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSAddExerciseTime(UINT32 dwRoleID, INT32 nHour)
{
    INT32 nRetCode = 0;
    InternalMessage::G2M_ADD_EXERCISE_TIME* pMsg = (InternalMessage::G2M_ADD_EXERCISE_TIME*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_ADD_EXERCISE_TIME));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_add_exercise_time;
    pMsg->dwRoleID = dwRoleID;
    pMsg->nHour = nHour;

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_ADD_EXERCISE_TIME));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSUpdateRankListData(CRole* poRole)
{
    INT32 nRetCode = 0;
    InternalMessage::G2M_RANKLIST_ROLE_DATA* pMsg = (InternalMessage::G2M_RANKLIST_ROLE_DATA*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_RANKLIST_ROLE_DATA));

    LOG_PROCESS_ERROR(poRole);
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_ranklist_role_data;
    pMsg->dwRoleID = poRole->GetObjID();

    pMsg->nLevel = poRole->GetLevel();
    pMsg->nClass = poRole->GetClass();
    pMsg->nAchievement = poRole->GetItemBag()->GetMoney(MONEYTYPE_ACHIEVEMENTPTS);
    pMsg->nMoney = poRole->GetItemBag()->GetMoney(MONEYTYPE_02);
    pMsg->nMaster = poRole->GetItemBag()->GetMoney(MONEYTYPE_MASTER_EXP);
    pMsg->nPkValue = poRole->GetPkValue();
    pMsg->nTotalKillCount = poRole->GetAchievementList().GetVariable(avdKillWarriorCount) +
        poRole->GetAchievementList().GetVariable(avdKillMageCount) +
        poRole->GetAchievementList().GetVariable(avdKillArcherCount) +
        poRole->GetAchievementList().GetVariable(avdKillRogueCount);
    pMsg->nTotalPower = poRole->GetPow();
    pMsg->nArmerPower = poRole->GetItemBag()->GetPow();
    pMsg->nSpiritPower = poRole->GetSpirit().GetPow();
    pMsg->nExp = poRole->GetExp();
    pMsg->nItemPower = poRole->GetItemBag()->GetPow();

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_RANKLIST_ROLE_DATA));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

BOOL CCliMessageHandler::DoMSUpdateRankListNode(INT32 nServerGroup, INT32 nRankListType, INT64 llKey, INT64 llValue)
{
    INT32 nRetCode = 0;
    InternalMessage::G2M_UPDATE_RANKLIST_NODE* pMsg = NULL;

    pMsg = (InternalMessage::G2M_UPDATE_RANKLIST_NODE*)m_poPacketAllocator->Alloc(sizeof(InternalMessage::G2M_UPDATE_RANKLIST_NODE));
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = InternalMessage::g2m_update_ranklist_node;
    pMsg->byServerGroup = (UINT8)nServerGroup;
    pMsg->nRankListType = nRankListType;
    pMsg->llKey = llKey;
    pMsg->llValue = llValue;

    nRetCode = m_poNotifier->SendToMS((PACKET_BUFFER*)pMsg, sizeof(InternalMessage::G2M_UPDATE_RANKLIST_NODE));
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:
    if (pMsg)
        m_poPacketAllocator->Free((PACKET_BUFFER*)pMsg);
    return FALSE;
}

#endif  // _ROBOT
