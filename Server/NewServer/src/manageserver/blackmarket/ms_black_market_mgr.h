#ifndef _MS_BLACK_MARKET_MGR_H_
#define _MS_BLACK_MARKET_MGR_H_

class CMSBlackMarketMgr
{
public:
    static CMSBlackMarketMgr& GetInstance();
    BOOL MainLoop();

    struct BMServerLimitInfo
    {
        INT32 nCount;
        UINT32 dwNextRefreshTime;
    };
    const std::map<INT32, BMServerLimitInfo>& GetLimitMap() const { return m_BlackMarketLimitMap; }
    INT32 CheckProduct(INT32 nProductID, INT32& nCount);

private:
    static CMSBlackMarketMgr ms_Instance;
    std::map<INT32, BMServerLimitInfo> m_BlackMarketLimitMap;
};

#endif // _MS_BLACK_MARKET_MGR_H_
