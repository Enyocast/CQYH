#ifndef __MMOSHOPMANAGER_H__
#define __MMOSHOPMANAGER_H__

struct MMOGameEvent_Shop_ShowMessage : public MMOGameEvent
{
public:

	MMOGameEvent_Shop_ShowMessage(BOOL v)
		: show(v)
	{}

	virtual EGameEvent GetEventType() const{ return GameEvent_ShowShopMessage; }

	BOOL show;
};

struct MMOGameEvent_Shop_UpdateMessageMoney : public MMOGameEvent
{
public:

	MMOGameEvent_Shop_UpdateMessageMoney(FString money1, FString money2)
		: const1(money1)
		, const2(money2)
	{}

	virtual EGameEvent GetEventType() const{ return GameEvent_UpdateShopMessageMoney; }

	FString const1;
	FString const2;
};

struct MMOGameEvent_Bag_TabChange : public MMOGameEvent
{
public:

	MMOGameEvent_Bag_TabChange(INT tab)
		: curTab(tab)
	{}

	virtual EGameEvent GetEventType() const{ return GaemEvent_BagTabChange; }

	INT curTab;
};

class MMOShopManager : public SingletonMeyers<MMOShopManager>, public INativeGameEventHandler
{
public:
	MMOShopManager();
	virtual ~MMOShopManager();

	void Init();

	void OnNativeGameEvent(struct MMOGameEvent* evt);

	INT getShopId(){return _shopId;}
	void setShopId(INT id){_shopId = id;}

	void notifyShowShopMessage(BOOL v);
	void notifyUpdateShopMessageMoney(FString const1,FString const2);
private:
	INT _shopId;

};

#endif