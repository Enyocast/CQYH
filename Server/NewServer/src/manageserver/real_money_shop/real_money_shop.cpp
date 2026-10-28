#include "stdafx.h"
#include "real_money_shop.h"

#include "m2c_message.h"
#include "zlib.h"
#include "role_data_mgr.h"
#include "oa_bill_mgr.h"
#include "mail/mail_mgr.h"
#include "../onlinerole/online_role_data_mgr.h"
#include "message_handler.h"
#include "manageserver.h"
#include "mail_template_data.h"
#include "item_data.h"
#include "money_data.h"
#include "db/ms_sql_stmt_list.h"
#include "server_config.h"

CRealMoneyShop::CRealMoneyShop()
    :m_datamgr(CDataManager<REAL_MONEY_SHOP_DATA>::GetInstance())
{
    m_dwCrc = 0;
    m_dwItemCount = 0;
}

BOOL CRealMoneyShop::Init()
{
    ExternalMessage::REAL_MONEY_ITEM_INFO* iteminfo = (ExternalMessage::REAL_MONEY_ITEM_INFO*)m_itembuf;

    const REAL_MONEY_SHOP_DATA* data = m_datamgr.GetFirstData();

    m_dwItemCount = 0;

    while (data)
    {
        if (data->m_nItemTemplateID)
        {
            iteminfo[m_dwItemCount].m_nItemTemplateID = data->m_nItemTemplateID;
            iteminfo[m_dwItemCount].m_shItemCount = data->m_shItemCount;
            iteminfo[m_dwItemCount].m_byPage = data->m_byPage;
            iteminfo[m_dwItemCount].m_byFlag = data->m_byFlag;
            iteminfo[m_dwItemCount].m_nCurrentPrice = data->m_nCurrentPrice;
            iteminfo[m_dwItemCount].m_nOriginalPrice = data->m_nOriginalPrice;
            iteminfo[m_dwItemCount].m_nRenQi = data->m_nRenQi;

            m_dwItemCount++;
        }

        data = m_datamgr.GetNextData();
    }

    if (m_dwItemCount)
    {
        m_dwCrc = crc32(0, (const Bytef*)m_itembuf, sizeof(ExternalMessage::REAL_MONEY_ITEM_INFO) * m_dwItemCount);
    }
    else
    {
        m_dwCrc = 0;
    }

    return TRUE;
}

BOOL CRealMoneyShop::UnInit()
{
    return TRUE;
}

void CRealMoneyShop::SyncRealMoneyShopData(UINT32 dwCrc, ExternalMessage::M2C_SYNC_REAL_MONEY_SHOP_DATA* pMsg)
{
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = ExternalMessage::m2c_sync_real_money_shop_data;
    if (dwCrc == m_dwCrc)
    {
        pMsg->dwCrc = m_dwCrc;
        pMsg->dwItemCount = 0;
        pMsg->wSize = sizeof(ExternalMessage::M2C_SYNC_REAL_MONEY_SHOP_DATA);
    }
    else
    {
        pMsg->dwCrc = m_dwCrc;
        pMsg->dwItemCount = m_dwItemCount;
        memcpy(pMsg->Items, m_itembuf, sizeof(ExternalMessage::REAL_MONEY_ITEM_INFO) * m_dwItemCount);
        pMsg->wSize = (UINT16)(sizeof(ExternalMessage::M2C_SYNC_REAL_MONEY_SHOP_DATA) + sizeof(ExternalMessage::REAL_MONEY_ITEM_INFO) * m_dwItemCount);
    }

Exit0:
    return;
}

INT32 CRealMoneyShop::Buy(MS_ONLINE_ROLE_DATA* pOnlineRole, INT32 nItemID, INT32 nItemCount, char* szRoleName)
{
    BOOL bRet = FALSE;
    INT32 total_cost;
    const REAL_MONEY_SHOP_DATA* shop_data = NULL;

    LOG_PROCESS_ERROR(pOnlineRole);
    LOG_PROCESS_ERROR(nItemCount > 0);
    LOG_PROCESS_ERROR(szRoleName);

    shop_data = m_datamgr.GetData(nItemID);
    if (shop_data == NULL)
        return errRealMoneyShopItemNotFound;

    total_cost = shop_data->m_nCurrentPrice * nItemCount;

    if (strlen(szRoleName) > 0 && CRoleDataMgr::GetInstance().FindRoleByName(szRoleName) == NULL)
        return errRealMoneyShopFriendNotFound;

    // Default code
    //COABillMgr::GetInstance().DoCharge(pOnlineRole, total_cost, nItemID, nItemCount, szRoleName);

    // Custom code: ask GS to deduct ingots
    bRet = CMessageHandler::GetInstance().DoGSRoleRealMoneyShopBuyItemReq(pOnlineRole->dwGSSessionID, pOnlineRole->dwCliSessionID,szRoleName, pOnlineRole->pRoleData->dwRoleID, total_cost, nItemID, nItemCount);
    LOG_PROCESS_ERROR(bRet);

    return errSuccess;

Exit0:
    return errItemUnknown;
}

void CRealMoneyShop::OnCharge(INT32 nResult, UINT32 dwRoleID, INT32 nItemID, INT32 nItemCount, char* szRoleName)
{
    INT32 nRetCode = 0;

    if (nResult == 0)
    {
        const REAL_MONEY_SHOP_DATA* shop_data = m_datamgr.GetData(nItemID);
        MS_ROLE_DATA* buyer_role = CRoleDataMgr::GetInstance().FindRole(dwRoleID);
        MS_ROLE_DATA* target_role = NULL;
        MS_ONLINE_ROLE_DATA* online_target_role = NULL;
        SaleInfo sale_info;
        bool giving = (szRoleName && strlen(szRoleName) > 0);
        char giver_role_name[ROLE_NAME_LEN];

        LOG_PROCESS_ERROR(shop_data);
        LOG_PROCESS_ERROR(buyer_role);

        //Log gold transactions
        if (nItemID == MONEYTYPE_02)
        {
            nRetCode = CMessageHandler::GetInstance().DoDLRealMoney2Money02(CManageServer::GetInstance().GetGameTime(),
                buyer_role->byGroup, shop_data->m_nCurrentPrice * nItemCount);
            LOG_CHECK_ERROR(nRetCode);

            MS_ONLINE_ROLE_DATA* online_buyer_role = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(dwRoleID);
            if (online_buyer_role && online_buyer_role->m_byShopLogLoaded)
            {
                MS_ONLINE_ROLE_DATA::ShopLog shoplog;
                shoplog.nItemID = nItemID;
                shoplog.nItemCount = shop_data->m_shItemCount * nItemCount;
                shoplog.nCost = shop_data->m_nCurrentPrice * nItemCount;
                shoplog.dwShopTime = CManageServer::GetInstance().GetGameTime();
                online_buyer_role->AddShopLog(shoplog);
            }

            CManageServer::GetInstance().GetSqlMgr().AsyncExecSqlStmt(msqlInsertShopLog, NULL, NULL, "ucdddd", buyer_role->byGroup, dwRoleID, nItemID, shop_data->m_shItemCount * nItemCount, shop_data->m_nCurrentPrice * nItemCount);
        }
        else
        {
            nRetCode = CMessageHandler::GetInstance().DoDLRealMoney2Item(CManageServer::GetInstance().GetGameTime(),
                buyer_role->byGroup, shop_data->m_nCurrentPrice * nItemCount);
            LOG_CHECK_ERROR(nRetCode);
        }

        if (giving)
        {
            online_target_role = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByName(szRoleName);
            strxcpy(giver_role_name, buyer_role->szRoleName, ROLE_NAME_LEN);
        }
        else
        {
            online_target_role = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(dwRoleID);
            giver_role_name[0] = 0;
        }

        if (online_target_role)
        {
            //If online, try sending to GS for direct delivery to the bag
            BOOL bRet = CMessageHandler::GetInstance().DoGSRealMoneyBuySuccess(online_target_role->dwGSSessionID, online_target_role->pRoleData->dwRoleID, nItemID, shop_data->m_shItemCount, nItemCount, shop_data->m_nOriginalPrice, giver_role_name, dwRoleID);
            LOG_PROCESS_ERROR(bRet);
        }
        else
        {
            //If offline, send mail
            BOOL bRet;
            char mail_subject[MAIL_SUBJECT_LEN];
            char mail_content[MAIL_CONTENT_LEN];
            const MAIL_TEMPLATE_DATA* mail_data = NULL;
            if (giving)
                mail_data = CDataManager<MAIL_TEMPLATE_DATA>::GetInstance().GetData(mtiRealMoneyShopGive);
            else
                mail_data = CDataManager<MAIL_TEMPLATE_DATA>::GetInstance().GetData(mtiRealMoneyShop);

            if (mail_data)
            {
                char item_name[MAX_ITEM_NAME_LEN];
                if (nItemID < MONEYTYPE_COUNT)
                {
                    const MONEY_DATA* money_data = CDataManager<MONEY_DATA>::GetInstance().GetData(nItemID);
                    if (money_data)
                        strxcpy(item_name, money_data->m_szMoneyName, MAX_ITEM_NAME_LEN);
                    else
                        strxcpy(item_name, "Unknown Money", MAX_ITEM_NAME_LEN);
                }
                else
                {
                    const ITEM_DATA* item_data = GetItemData(nItemID);
                    if (item_data)
                        strxcpy(item_name, item_data->m_szName, MAX_ITEM_NAME_LEN);
                    else
                        strxcpy(item_name, "Unknown Item", MAX_ITEM_NAME_LEN);
                }

                if (giving)
                    snprintf(mail_subject, MAIL_SUBJECT_LEN, mail_data->m_szMailSubject, buyer_role->szRoleName, item_name);
                else
                    snprintf(mail_subject, MAIL_SUBJECT_LEN, mail_data->m_szMailSubject, item_name);

                strxcpy(mail_content, mail_data->m_szMailContent, MAIL_CONTENT_LEN);
            }
            else
            {
                strxcpy(mail_subject, "Unknown Mail Subject", MAIL_SUBJECT_LEN);
                strxcpy(mail_content, "Unknown Mail Content", MAIL_CONTENT_LEN);
            }

            if (giving)
                target_role = CRoleDataMgr::GetInstance().FindRoleByName(szRoleName);
            else
                target_role = buyer_role;
            LOG_PROCESS_ERROR(target_role);

            if (nItemID < MONEYTYPE_COUNT)
            {
                bRet = CMailMgr::GetInstance().SendSystemMailWithSimpleAttach(target_role, mail_subject, mail_data->m_szMailContent, nItemID, shop_data->m_shItemCount * nItemCount);
                LOG_PROCESS_ERROR(bRet);
            }
            else
            {
                for (INT32 i = 0; i < nItemCount; i++)
                {
                    bRet = CMailMgr::GetInstance().SendSystemMailWithSimpleAttach(target_role, mail_subject, mail_data->m_szMailContent, nItemID, shop_data->m_shItemCount);
                    LOG_CHECK_ERROR(bRet);
                }
            }
        }

        sale_info.dwTime = CManageServer::GetInstance().GetGameTime();
        sale_info.nItemID = nItemID;
        strxcpy(sale_info.szRoleName, szRoleName, ROLE_NAME_LEN);
        m_lstSaleInfo.push_back(sale_info);
        if (m_lstSaleInfo.size() > 10)
            m_lstSaleInfo.pop_front();
    }
    else
    {
        MS_ONLINE_ROLE_DATA* pOnlineRole = COnlineRoleDataMgr::GetInstance().FindOnlineRoleByRoleID(dwRoleID);
        if (pOnlineRole)
        {
            if (nResult == -106114 || nResult == -106908)
            {
                CMessageHandler::GetInstance().DoErrorNotify(pOnlineRole->dwCliSessionID, errRealMoneyBuyNotEnoughMoney, 0, 0);
            }
            else
            {
                CMessageHandler::GetInstance().DoErrorNotify(pOnlineRole->dwCliSessionID, errBillingSystemError, nResult, 0);
            }
        }
    }

    return;

Exit0:
    WRN("Send Real Money Item Failed: RoleID: %u, ItemID: %d, ItemCount: %d, Target: %s", dwRoleID, nItemID, nItemCount, szRoleName);
}
