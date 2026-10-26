#include "stdafx.h"
#include "npc_shop_mgr.h"
#include "g2c_message.h"
#include "zlib.h"

CNpcShopMgr::CNpcShopMgr()
{
    m_dwCrc = 0;
    m_dwItemCount = 0;
}

CNpcShopMgr& CNpcShopMgr::GetInstance()
{
    static CNpcShopMgr s_npc_shop_mgr;
    return s_npc_shop_mgr;
}

BOOL CNpcShopMgr::Init()
{
    ExternalMessage::NPC_SHOP_DATA* shop_data_buf = (ExternalMessage::NPC_SHOP_DATA*)m_shop_data_buf;

    CDataManager<SHOP_DATA>& data_mgr = CDataManager<SHOP_DATA>::GetInstance();
    const SHOP_DATA* shop_data = data_mgr.GetFirstData();

    m_npc_shop_map.clear();
    m_dwItemCount = 0;
    m_dwCrc = 0;

    while (shop_data)
    {
        m_npc_shop_map[shop_data->m_nShopID].push_back(shop_data);

        shop_data_buf[m_dwItemCount].m_nShopID = shop_data->m_nShopID;
        strxcpy(shop_data_buf[m_dwItemCount].m_szShopName, shop_data->m_szShopName, SHOP_NAME_LEN);
        shop_data_buf[m_dwItemCount].m_nItemID = shop_data->m_nItemID;
        shop_data_buf[m_dwItemCount].m_nItemCount = shop_data->m_nItemCount;
        shop_data_buf[m_dwItemCount].m_nCostItemID1 = shop_data->m_nCostItemID1;
        shop_data_buf[m_dwItemCount].m_nCostValue1 = shop_data->m_nCostValue1;
        shop_data_buf[m_dwItemCount].m_nCostItemID2 = shop_data->m_nCostItemID2;
        shop_data_buf[m_dwItemCount].m_nCostValue2 = shop_data->m_nCostValue2;
        shop_data_buf[m_dwItemCount].m_nRequireForceID = shop_data->m_nRequireForceID;
        shop_data_buf[m_dwItemCount].m_nReputation = shop_data->m_nReputation;
        shop_data_buf[m_dwItemCount].m_nRequireGuildBuildingID = shop_data->m_nRequireGuildBuildingID;
        shop_data_buf[m_dwItemCount].m_nBuildingLevel = shop_data->m_nBuildingLevel;
        shop_data_buf[m_dwItemCount].m_nShopTypeSell = shop_data->m_nShopTypeSell;

        m_dwItemCount++;

        shop_data = data_mgr.GetNextData();

        LOG_PROCESS_ERROR(m_dwItemCount * sizeof(ExternalMessage::NPC_SHOP_DATA) < MAX_MESSAGE_SIZE - sizeof(ExternalMessage::G2C_SYNC_NPC_SHOP_DATA));
    }

    if (m_dwItemCount)
    {
        m_dwCrc = crc32(0, (const Bytef*)m_shop_data_buf, sizeof(ExternalMessage::NPC_SHOP_DATA) * m_dwItemCount);
    }


    return TRUE;

Exit0:
    return FALSE;
}

BOOL CNpcShopMgr::UnInit()
{
    m_npc_shop_map.clear();
    return TRUE;
}

void CNpcShopMgr::SyncNpcShopData(UINT32 dwCrc, ExternalMessage::G2C_SYNC_NPC_SHOP_DATA* pMsg)
{
    LOG_PROCESS_ERROR(pMsg);

    pMsg->wMsg = ExternalMessage::g2c_sync_npc_shop_data;
    if (dwCrc == m_dwCrc)
    {
        pMsg->dwCrc = m_dwCrc;
        pMsg->dwItemCount = 0;
        pMsg->wSize = sizeof(ExternalMessage::G2C_SYNC_NPC_SHOP_DATA);
    }
    else
    {
        pMsg->dwCrc = m_dwCrc;
        pMsg->dwItemCount = m_dwItemCount;
        memcpy(pMsg->ShopData, m_shop_data_buf, sizeof(ExternalMessage::NPC_SHOP_DATA) * m_dwItemCount);
        pMsg->wSize = (UINT16)sizeof(ExternalMessage::G2C_SYNC_NPC_SHOP_DATA) + sizeof(ExternalMessage::NPC_SHOP_DATA) * m_dwItemCount;
    }

Exit0:
    return;
}

const SHOP_DATA* CNpcShopMgr::FindShopData(INT32 nShopID, INT32 nShopItemIndex) const
{
    NPC_SHOP_MAP::const_iterator it = m_npc_shop_map.find(nShopID);
    if (it == m_npc_shop_map.end())
        return NULL;
    else
    {
        const NPC_SHOP& shop = it->second;
        if (nShopItemIndex >= shop.size())
            return NULL;
        else
            return shop[nShopItemIndex];
    }
}
