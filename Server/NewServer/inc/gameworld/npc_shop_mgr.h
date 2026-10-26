#ifndef _NPC_SHOP_MGR_H_
#define _NPC_SHOP_MGR_H_

#include "shop_data.h"
#include "net.h"

namespace ExternalMessage
{
    struct G2C_SYNC_NPC_SHOP_DATA;
}

class CNpcShopMgr
{
public:
    static CNpcShopMgr& GetInstance();
    BOOL Init();
    BOOL UnInit();

    void SyncNpcShopData(UINT32 dwCrc, ExternalMessage::G2C_SYNC_NPC_SHOP_DATA* pMsg);

    const SHOP_DATA* FindShopData(INT32 nShopID, INT32 nShopItemIndex) const;

private:
    typedef std::vector<const SHOP_DATA*> NPC_SHOP;
    typedef std::map<INT32, NPC_SHOP> NPC_SHOP_MAP;
    NPC_SHOP_MAP m_npc_shop_map;

    UINT32 m_dwCrc;
    UINT32 m_dwItemCount;
    char m_shop_data_buf[MAX_MESSAGE_SIZE];

    CNpcShopMgr();
};

#endif // _NPC_SHOP_MGR_H_
