#ifndef _REAL_MONEY_SHOP_H_
#define _REAL_MONEY_SHOP_H_

#include "real_money_shop_data.h"
#include "net.h"
#include "server_def.h"
#include "string_def.h"

namespace ExternalMessage
{
    struct M2C_SYNC_REAL_MONEY_SHOP_DATA;
}

struct MS_ONLINE_ROLE_DATA;

class CRealMoneyShop
{
public:
    static CRealMoneyShop& GetInstance()
    {
        static CRealMoneyShop ms_Instance;
        return ms_Instance;
    }

    BOOL Init();
    BOOL UnInit();
    void SyncRealMoneyShopData(UINT32 dwCrc, ExternalMessage::M2C_SYNC_REAL_MONEY_SHOP_DATA* pMsg);
    INT32 Buy(MS_ONLINE_ROLE_DATA* pOnlineRole, INT32 nItemID, INT32 nItemCount, char* szRoleName);
    void OnCharge(INT32 nResult, UINT32 dwRoleID, INT32 nItemID, INT32 nItemCount, char* szRoleName);

    struct SaleInfo
    {
        INT32       dwTime;
        INT32       nItemID;
        char        szRoleName[ROLE_NAME_LEN];
    };
    const std::list<SaleInfo>& GetSaleInfoList() const { return m_lstSaleInfo; }
    CDataManager<REAL_MONEY_SHOP_DATA>& GetDataMgr() { return m_datamgr; }

private:
    CRealMoneyShop();
    CDataManager<REAL_MONEY_SHOP_DATA>& m_datamgr;

    UINT32 m_dwCrc;
    UINT32 m_dwItemCount;
    char m_itembuf[MAX_MESSAGE_SIZE];

    std::list<SaleInfo> m_lstSaleInfo;
};


#endif // _REAL_MONEY_SHOP_H_
