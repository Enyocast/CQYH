
#ifndef _MMO_MALL_CONTROLLER_H_
#define _MMO_MALL_CONTROLLER_H_

#include "MMOSingleton.h"
#include "MMOGameUIClasses.h"
#include "MMOGameEvent.h "


struct MMOGameEvent_MallStore : public MMOGameEvent
{
public:
	enum EMallStoreEventType
	{
		EMallStoreEvent_PageChange,
		EMallStoreEvent_GoldChange,
		EMallStoreEvent_TypeChange,
		EMallStoreEvent_ListChange,
		EMallStoreEvent_NewBuyInfo,
		EMallStoreEvent_BuyInfoChange,
		EMallStoreEvent_NeedReqBuyInfo
	};

	MMOGameEvent_MallStore(EMallStoreEventType eventType)
		: EventType(eventType)
	{
	}

	virtual EGameEvent GetEventType() const
	{
		return GameEvent_MallStore;
	}

	EMallStoreEventType	EventType;
};
enum MallBuyOperateCode
{
	eMallBuyValid = 0,
	eMallBuytoSelf,
	eMallBuytoFriend,
};
class MallController : public SingletonMeyers<MallController>, public INativeGameEventHandler
{
public:

	MallController();
	virtual ~MallController(){}

	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

	void							DecPage();
	void							AddPage();
	void							SetSortType(INT nSortType);
	void							SetShowType(INT nShowType);
	//BOOL							SetBuyGoodsInfo(UMMOGFXPlayer* gpkPlayer,UGFxObject* object,INT nGoodsID);

	void							NotifyPageChange();
	void							NotifyRealMoneyChange();
	void							NotifyGoodsListChange();
	void							NotifyBuyResult(INT nGoodsID);
	void							NotifyBuyInfoChange();
	void							NotifyReqBuyInfoChange();

	void							SendMallRealMoney();
	void							SendMallGoodsList();
	void							SendBuyGoods(INT nGoodsID,INT nNum);
	void							SendGiveFriendGoods(FString roleName, INT nGoodsID,INT nNum);
	void							SendReqUpdateBuyInfo();
	void							PopupGoodsBuyPanel(INT nGoodsID);

private:
	void							ShowGoodsInfo();
	BOOL							CheckEnoughGold(INT nGoodsID, INT nNum);
private:
	BOOL							bAskGoodIng;
	INT								nShowGoodsID;
	MallBuyOperateCode				nOperateCode;
	INT								nGoodsNum;
};
#endif