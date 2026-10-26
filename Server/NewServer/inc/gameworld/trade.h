#ifndef _TRADE_H_
#define _TRADE_H_

#include "item_def.h"

class CRole;

class CTrade
{
public:
    CTrade();
    void Clear(BOOL bClearTarget=TRUE);
    void SetOwner(CRole* role);

    INT32 AskTrade(UINT32 dwRoleID);
    INT32 AcceptTrade(UINT32 dwRoleID);
    INT32 SetItem(UINT8 byTradeSlot, UINT8 bAdd, UINT8 byConSlot, UINT8 byItemSlot);
    INT32 SetMoney(INT32 nCount);
    INT32 LockTrade();
    INT32 ConfirmTrade();
    INT32 UnlockTrade();
    INT32 CancelTrade();

    BOOL IsTrading() const { return m_state != etsFree; }
    BOOL IsTradeItem(UINT8 byContainerSlot, UINT8 byItemSlot) const;

private:
    INT32 _CommitTrade();
    void _BroadcastStateChange();

    CRole* m_pOwner;
    CRole* m_pTradeTarget;
    ETradeState m_state;

    UINT16 m_slots[MAX_TRADE_SLOT];
    INT32 m_money;
};


#endif // _TRADE_H_
