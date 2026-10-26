#ifndef _EXCHANGE_HISTORY_H_
#define _EXCHANGE_HISTORY_H_

#include "server_def.h"

struct Bar
{
    INT32 m_nOpen, m_nClose, m_nHigh, m_nLow, m_nVolume;
    INT64 m_llTotalPrice;

    void AddPrice(INT32 price, INT32 count);
};

class CExchangeHistory
{
public:
    static CExchangeHistory& GetInstance() { return ms_Instance; }
    BOOL Init(void);
    BOOL UnInit(void);

    BOOL AddPrice(UINT8 groupid, INT32 price, INT32 count, UINT32 curtime);

private:
    static BOOL _Load(std::list<void*>& rResult, void* pUserData);

    BOOL _LoadHistory(UINT8 byGroupID, UINT32 dwHistoryTime, INT32 nOpen, INT32 nClose, INT32 nHigh, INT32 nLow, INT32 nVolume, INT64 llTotalPrice);

    static CExchangeHistory ms_Instance;

    typedef std::map<UINT32, Bar> CHART;
    CHART charts[MAX_SERVER_GROUP_COUNT];

    INT32 m_nLoadedCount;
};

#endif // _EXCHANGE_HISTORY_H_
