#ifndef _ITEM_BAG_H_
#define _ITEM_BAG_H_


#include "item.h"
#include "money_def.h"
#include <vector>

class CCharacter;
class CRole;
class CHero;
class CAuraInstance;
struct BLACK_MARKET_DATA;

class CItemBag
{
public:
	CItemBag();
	void Clear();
	void SetOwner(CRole* role);
	CRole* GetOwner();
	BOOL Load_v_1(const char* pcData, UINT32 dwSize);
	BOOL Load_v_2(const char* pcData, UINT32 dwSize);
	BOOL Save(const char* pcData, UINT32& rdwSize);

    BOOL LoadBlackMarket_v_1(const char* pcData, UINT32 dwSize);
    BOOL SaveBlackMarket(const char* pcData, UINT32& dwSize);

    BOOL LoadBlackMarketLimit_v_1(const char* pcData, UINT32 dwSize);
    BOOL LoadBlackMarketCooldown_v_1(const char* pcData, UINT32 dwSize);

    BOOL SaveBlackMarketLimit(const char* pcData, UINT32& dwSize);
    BOOL SaveBlackMarketCooldown(const char* pcData, UINT32& dwSize);

    BOOL MainLoop();

	void UpdateMoneyLimits();
	void UpdateMoneytype01DailyUsedLimit();
	void UpdateDaily();
	void UpdateWeekly();

    void CheckWeight();

	void GetRefineLevels(UINT16 levels[]);
	void GetContainerSizes(UINT8 sizes[]);

	void Begin();
	const Item* Next();

	void Begin(UINT8 conslot);
    const Item* Next(UINT8 conslot);

    INT32 AddItem(Item* item, EItemLog reason, UINT64 userdefine);
    INT32 AddItem(INT32 itemid, INT32 itemcount, EItemLog reason, UINT64 userdefine, BOOL forcebinded);

    // dangerous api by taoqun
	INT32 AddItemToDefaultCon(Item* item, UINT8 conslot, UINT8 itemslot, EItemLog reason);

	INT32 UseItem(UINT8 conslot, UINT8 itemslot);
	INT32 MoveItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot);
	INT32 SplitItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot, INT16 itemcount);
	INT32 DeleteItem(UINT8 conslot, UINT8 itemslot, INT16 itemcount);
	INT32 SellItem(UINT8 conslot, UINT8 itemslot, INT32 shoptypesell);
	INT32 ViewSoldItems();
	INT32 BuyBackItem(UINT8 slot);
	INT32 RepairItem(UINT8 conslot, UINT8 itemslot, BOOL bSpecial);
	INT32 RepairAllEquippedItem();
	INT32 IdentifyItem(UINT8 conslot, UINT8 itemslot);
	INT32 RandomizeItem(UINT8 conslot, UINT8 itemslot);
	INT32 ConfirmRandomizeItem();
	INT32 Refine(UINT8 refineslot, UINT8 addequip, UINT8 conslot, UINT8 itemslot);
	void SetRefineLevel(UINT8 refineslot, UINT16 level);
	INT32 SignItem(UINT8 conslot, UINT8 itemslot);

	INT32 AuctionSell(UINT8 conslot, UINT8 itemslot, UINT8 byAuctionTimeType, UINT8 byOpen, INT64 llprice, INT64 llbuyoutPrice, INT64 llDepositePrice);
	INT32 AuctionBuy(UINT32 auctionid, INT64 llBidPrice, INT64 llAuctionPrice, INT64 llDepositPrice, UINT8 byBuyType);
	INT32 AuctionPay(UINT32 auctionid, INT64 llprice);

	INT32 ExchangeAddOrder(INT32 nItemIDRequire, INT32 nItemCountRequire, UINT8 byOrderType, INT32 nPriceOrder, INT32 nCountOrder);

	Item* GetItem(UINT8 conslot, UINT8 itemslot);
	INT32 DeleteItemPos(UINT8 conslot, UINT8 itemslot, INT16 itemcount, EItemLog reason, UINT64 qwUserDefinedID);
	INT32 DeleteItemId(INT32 itemid, INT16 itemcount, EItemLog reason, BOOL includebank, UINT64 qwUserDefinedID);
	INT32 RemoveItem(UINT8 conslot, UINT8 itemslot, EItemLog reason);
	INT16 GetItemCount(INT32 itemid, BOOL includebank = FALSE) const;
	UINT32 GetFreeSlots(UINT8 conslot);

	//Transfer item ownership to another player
	INT32 TransferItemTo(CItemBag* dstbag, Item* item, INT16 itemcount, EItemLog reason);

	void OnDisArm();
	void OnDisArmFinish();

	//Called on attacking or being attacked to deduct durability
    void LoseWeaponDur();
	BOOL LoseMineDur(INT32 nItemID);
    void LoseArmorDur(INT32 damage);
	void LoseAllDur(INT32 nPercent, EItemLog reason);

	void LoseHeroWeaponDur();
	void LoseHeroArmorDur();
    void LoseHeroAllDur(INT32 nPercent, EItemLog reason);

	//Get weapon type
	UINT8 GetWeaponType();
	UINT8 GetHeroWeaponType();

	void GetAppearance(INT32 nAvatar[]);
	void GetHeroAppearance(INT32 nAvatar[]);

	//Equip default gear for a new player; only called by the new-player creation script
	BOOL EquipItemOnBirth(INT32 itemid, UINT8 itemslot);

	//Equip default gear for a hero; only called by the hero creation script
	BOOL EquipHeroItemOnBirth(INT32 itemid, UINT8 itemslot);

	//Currency
	void SetUseMoneytype01Only(UINT8 use) { m_use_moneytype01_only = use; }
	UINT8 GetUseMoneytype01Only() const { return m_use_moneytype01_only; }
	//Get available currency
	INT64 GetMoney(INT32 moneytype, BOOL use_moneytype01_only = FALSE) const;
	//Get actual currency amount
	INT64 GetMoneyInfo(INT32 moneytype);
	void GetMoneyAllInfo(
		INT64 allMoneys[],
		INT64 allMoneysLimit[],
		INT32 anDailyEarned[],
		INT32 anDailyEarnedLimit[],
		INT32 anDailyUsed[],
		INT32 anDailyUsedLimit[],
		INT32 anWeeklyEarned[],
		INT32 anWeeklyEarnedLimit[],
		INT32 anWeeklyUsed[],
		INT32 anWeeklyUsedLimit[]);

	INT32 AddMoney(INT32 moneytype, INT32 nCount, EMoneyLog reason, UINT32 dwSourceID);
	INT32 SubMoney(INT32 moneytype, INT32 nCount, EMoneyLog reason, UINT32 dwTargetID);

	//Note: SetMoney is for GM use only
	INT32 SetMoney(INT32 moneytype, INT32 nCount);

    void AddGoldPool(INT32 money);
    void SubGoldPool(INT32 money);
    INT32 GetGoldPool() const;
    INT32 GetChanceByGoldPool() const;

	//Buy slots
	INT32 BuySlots(UINT8 conslot, UINT8 slotcount);

	//Soul fusion
	INT32 UpgradeSoul(UINT8 targetconslot, UINT8 targetitemslot, UINT8 srccount, UINT8 srcconslot[], UINT8 srcitemslot[]);
	INT32 AddSoul(UINT8 equipconslot, UINT8 equipitemslot, UINT8 socketindex, UINT8 soulconslot, UINT8 soulitemslot);
	INT32 RemoveSoul(UINT8 conslot, UINT8 itemslot, UINT8 socketindex);

	//Soul forging - normal inscription refinement
	INT32 RuneItem(UINT8 conslot, UINT8 itemslot, INT32 itemid);

	// Advanced inscription refinement
	INT32 RuneItemAdvance(UINT8 conslot, UINT8 itemslot, INT32 itemid);

	// Confirm advanced refinement
	INT32 RuneItemConfirm(UINT8 conslot, UINT8 itemslot);

    //Equipment upgrade
    INT32 WeaponLevelUpPutIn();
    INT32 WeaponLevelUpTakeOut();
	INT32 WeaponLevelUpTakeOutImmediately();
    void OnPhyAttack();

	//Decomposition and crafting
	INT32 Decompose(UINT8 conslot, UINT8 itemslot);
	INT32 Compose(INT32 formulaid);

	void OpenHeroContainers(void);
	void CloseHeroContainers(void);
	void ApplyHeroEquipments(void);

	UINT32 GetUsedSlotCount(UINT8 conslot);

	//Equipment drops on PvP death
	void LoseItemOnDeath(BOOL is_player);
    void DestroyItemOnDeath();

	//Organize bag
	INT32 OrganizeBag(UINT8 conslot);

	//Luck value
	void SetWeaponLuck(INT8 v);
	void IncreaseWeaponLuck(INT8 v);
	void DecreaseWeaponLuck();

	//Equipment set
	INT32 GetSetItemCountBefore(const SET_DATA* data, INT32 itemid, UINT8 itemslot);
    INT32 GetSetItemCountAfter(const SET_DATA* data);

	//Enhancement activation effect
	UINT8 GetRefineFx();

	//Combat power
	INT32 GetPow();

    //Legend feature called by Li Xingjia’s editor
    UINT8 SearchDefaultContainer(INT32 itemid, INT16 dur) const;
    UINT8 SearchDefaultContainer(UINT8 itemtype, UINT8 itemsubtype, INT16 dur) const;
    BOOL LoseItemDur(INT32 itemid, INT16 dur, EItemLog reason);
    BOOL LoseItemDur(UINT8 conslot, UINT8 itemslot, INT16 dur, EItemLog reason);
    BOOL LoseItemDur(UINT8 conslot, UINT8 itemslot, INT32 itemid, INT16 dur, EItemLog reason);

    //Black market
    struct BMRoleLimitInfo
    {
        INT32 nCount;
        UINT32 dwNextRefreshTime;
    };
    void UpdateBlackMarketLimit();
    INT32 DecreaseBlackMarketLimit(const BLACK_MARKET_DATA* data);
    void UpdateBlackMarketCooldown();
    const std::map<INT32, BMRoleLimitInfo>& GetBlackMarketLimitInfo() const { return m_black_market_limit_map; }
    const std::map<INT32, UINT32>& GetBlackMarketCooldownInfo() const { return m_black_market_cooldown_map; }
    INT32 OnBlackMarketBuy(INT32 productid);
    INT32 OnMsBlackMarketBuy(INT32 productid, INT32 count);

    //gamble
    INT32 Gamble(UINT8 equiptype);
	INT32 GambleAdvance(INT32 nGambleType, INT32 nGambleLevel);
	INT32 SpellBookGamble();

	// ========== Custom code begins

	BOOL CheckTemplateIDIsTimeCard(INT32 nTemplateID);
	INT32 RuneTest(INT32 nRuneID);

	INT32 EquipAddSocket(INT32 nIndex);
	INT32 SetSocketColor(INT32 nIndex, INT32 nColor);
	INT32 GetSetSocketColorCost(int id, int column);

	// Destiny gift box
	INT32 AddDestinyWeapon(INT32 nItemID, INT32 nLevel);

	// Upgrade equipment to the specified maximum level
	INT32 EquipLevelUpToSpecifiedLevel(Item* item, INT32 nLevel);

	// ========== Custom code ends

#ifdef _ROBOT
	void SetContainerSize(UINT8 conslot, UINT8 consize);
	void OnItemChange(const ItemInfo& iteminfo);
	void OnItemDelete(UINT8 conslot, UINT8 itemslot);
	void OnItemSwap(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot);
#endif // _ROBOT

private:
	typedef std::map<UINT8, Item*> Container;
	typedef Container::iterator ConIt;
    typedef Container::const_iterator CConIt;

	INT32 AddItemToContainer(Item* item, UINT8 conslot, EItemLog reason, UINT64 userdefine);

	inline BOOL _CheckValidItemPos(UINT8 conslot, UINT8 itemslot);
	inline BOOL _SrcDstSame(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot);

	BOOL _Satisfied(CCharacter* poChar, const Item* item) const;
	BOOL _CorrectSlot(const Item* item, UINT8 itemslot);
    BOOL _CorrectDepositSlot(const Item* item, UINT8 itemslot);
	INT32 _MoveItem(UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot);
    void _LoseDur(Item* item, INT16 dur, EItemLog reason);
	void _AddItemToSoldList(Item* item);
	void _OnUseItemSuccess(UINT8 conslot, UINT8 itemslot, Item* item);
	void _ClearRandomizeItem();
	INT32 _GetPow(const Item* item) const;
    INT32 _GetSellPrice(const Item* item) const;
	UINT32 _GetPkDropChance(Item* item, UINT8 isplayer, UINT8 namecolor);
    INT32 _GetArmorWeight() const;
    INT32 _GetBagWeight() const;

	CRole* m_pOwner;


	UINT16 m_refine_levels[NES_TOTAL];

	Container m_cons[CONSLOT_COUNT];
	UINT8 m_con_sizes[CONSLOT_COUNT];


	//for iteration
	std::list<const Item*> m_allitem;

	//Currency
	INT64 m_moneys[MONEYTYPE_COUNT];
	INT64 m_moneys_limit[MONEYTYPE_COUNT];

	INT32 m_moneys_daily_earned[MONEYTYPE_COUNT];
	INT32 m_moneys_daily_earned_limit[MONEYTYPE_COUNT];

	INT32 m_moneys_daily_used[MONEYTYPE_COUNT];
	INT32 m_moneys_daily_used_limit[MONEYTYPE_COUNT];

	INT32 m_moneys_weekly_earned[MONEYTYPE_COUNT];
	INT32 m_moneys_weekly_earned_limit[MONEYTYPE_COUNT];

	INT32 m_moneys_weekly_used[MONEYTYPE_COUNT];
	INT32 m_moneys_weekly_used_limit[MONEYTYPE_COUNT];

	UINT8 m_use_moneytype01_only;

    INT32 m_gold_pool;

	//Buyback
	std::list<Item*> m_soldlist;

	//Last organization time
	UINT32 m_dwLastOrganizeTime;

	//for randomize item
	Item* m_randomize_item;

	//pk
	UINT32 m_dwFirstDeathTime;
	UINT32 m_dwDeathCountFromFirst;
	UINT32 m_dwLastDeathTime;

    //Weapon upgrade
    UINT32 m_dwWeaponLevelUpStartTime;
    Item* m_WeaponItem;
    INT32 m_nWeaponDur;
    INT32 m_nWeaponPhy, m_nWeaponMag, m_nWeaponTao;
    UINT8 m_byMailNotified;

    //Overweight movement penalty
    CAuraInstance* m_pWeaponAura;
    CAuraInstance* m_pArmorAura;
    CAuraInstance* m_pBagAura;

    //Black-market purchase limits and cooldowns
    std::map<INT32, BMRoleLimitInfo> m_black_market_limit_map;
    std::map<INT32, UINT32> m_black_market_cooldown_map;

    //Experience bottles used today
    INT32 m_nExpBottleTimes;


	// ========== Custom code begins

	


	// ========== Custom code ends


};

#endif // _ITEM_BAG_H_
