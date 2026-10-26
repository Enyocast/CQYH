#ifndef _STALL_H_
#define _STALL_H_

#include "string_def.h"
#include "item.h"

class CRole;

class CStall
{
public:
    CStall();
    void Clear();
    void SetOwner(CRole* role);
    BOOL Load_v_1(const char* pcData, UINT32 dwSize);
    BOOL Save(const char* pcData, UINT32& rdwSize);

    EStallState GetStallState() const { return m_state; }
    const char* GetStallName() const { return m_szStallName; }
    UINT32 GetStallLevelUpExpireTime() const { return m_dwUpgradeExpireTime; }

    INT32 Open();
    INT32 Close();
    INT32 RealOpen();
    INT32 RealClose();
    INT32 AddGood(UINT8 slot, UINT8 conslot, UINT8 itemslot, INT16 itemcount, INT32 price);
    INT32 RemoveGood(UINT8 slot);
    INT32 ChangeName(const char* stallname);
    INT32 Upgrade(UINT8 type);
    INT32 ViewGood(CRole* viewer);
    INT32 BuyGood(CRole* buyer, UINT8 slot, INT32 itemcount, INT64 modifyframe);

#ifdef _ROBOT
	INT8 GetFirstGoodSolt();
	INT64 GetFirstGoodModifyFrame();
	INT8 GetNextAddGoodSolt();
	BOOL IsItemAlreadyInStall(UINT8 byConSlot, UINT8 byItemSlot);
	BOOL SoldStallItem(UINT8 slot, INT32 itemcount);
	void SetStallLevelUpExpireTime(UINT32 dwUpgradeExpireTime);
	BOOL SyncStallItem(UINT8 slot, INT64 modifyframe);
#else
	INT8 GetFirstGoodSolt() { return -1; }
	INT64 GetFirstGoodModifyFrame() { return 0; }
	INT8 GetNextAddGoodSolt() { return -1; }
	BOOL IsItemAlreadyInStall(UINT8 byConSlot, UINT8 byItemSlot) { return FALSE; }
	BOOL SoldStallItem(UINT8 slot, INT32 itemcount) { return FALSE; }
	BOOL SyncStallItem(UINT8 slot, INT64 modifyframe) { return FALSE; }
#endif

    struct Good
    {
        Item* item;
        INT32 count;
        INT32 price;
        INT64 lastmodifyframe;
    };
    typedef std::map<UINT8, Good> Goods;
    const Goods& GetGoods() { return m_goods; }

private:
    INT64 _GetTotalPrice() const;
    //摊位数据，不存盘
    EStallState m_state;
    char		m_szStallName[STALL_NAME_LEN];
    Goods		m_goods;

    //摊位升级到期时间，存盘
    UINT32 m_dwUpgradeExpireTime;

    CRole* m_pOwner;
};

#endif // _STALL_H_
