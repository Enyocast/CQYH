#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOShopManager.h"
#include "TeamManager.h"
#include "MMOStats.h"
#include "MMOMsgBoxManager.h"
#include "MMOShopManager.h"
#include "Shop.h"
IMPLEMENT_CLASS(UMMOUIShopMessage)

	void UMMOUIShopMessage::Init()
{
	Super::Init();
	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_ShowShopMessage);
	evts.AddItem(GameEvent_UpdateShopMessageMoney);
	EventAdapter = new TGameEventAdapter<UMMOUIShopMessage>(this, evts);
	this->SetVisible(FALSE);
}

void UMMOUIShopMessage::PreOnShow(UBOOL show)
{

	if (show)
	{
		if(MMOUI::GetUIManager()->FindUIPanel(MMOUI::GetUIManager()->Panel_Shop)->GetVisible() == FALSE)
		{
			this->SetVisible(FALSE);
		}
		else
		{
			eventCallResetShopMessage();
			Super::PostOnShow(show);
		}

		eventCallSelectFilter(ShopManager::getSingleton().GetCurShopId());
	}


}
void UMMOUIShopMessage::UnInit()
{
	Super::UnInit();
}
void UMMOUIShopMessage::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	switch (evt->GetEventType())
	{
	case GameEvent_ShowShopMessage:
		{
			MMOGameEvent_Shop_ShowMessage* shopMessageEvt = (MMOGameEvent_Shop_ShowMessage*)evt;
			this->Show(shopMessageEvt->show);
			this->LastVisible = shopMessageEvt->show;
		}
		break;
	case GameEvent_UpdateShopMessageMoney:
		{
			MMOGameEvent_Shop_UpdateMessageMoney* shopMessageEvt = (MMOGameEvent_Shop_UpdateMessageMoney*)evt;
			eventCallUpdateShopMessageMoney(shopMessageEvt->const1,shopMessageEvt->const2);
		}
		break;
	}
}

void UMMOUIShopMessage::ASShopMsgAck(UBOOL agree,INT count)
{
	UMMOUINPCShop* shop = (UMMOUINPCShop*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_Shop);
	if (shop)
	{
		shop->ShopMsgAck(agree,count);
	}
}


void UMMOUIShopMessage::ASShopMsgNumChange(INT num)
{
	UMMOUINPCShop* shop = (UMMOUINPCShop*)MMOUI::FindUIPanelEx(MMOUI::GetUIManager()->Panel_Shop);
	if (shop)
	{
		shop->NumChange(num);
	}
}
