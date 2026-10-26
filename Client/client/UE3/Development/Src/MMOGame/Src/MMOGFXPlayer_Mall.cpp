#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "net/message_handler.h"
#include "UITextParser.h"
#include "MallManager.h"
#include "MallController.h"
#include "MMOMsgBoxManager.h"
#include "LinkManager.h"
#include <Windows.h>

IMPLEMENT_CLASS(UMMOGFXPlayer_Mall)

void UMMOGFXPlayer_Mall::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Mall::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Mall);
	MallGiveFriendConfirmBox = NULL;
	MallBuyConfirmBox = NULL;

	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_MallStore);
	EventAdapter = new TGameEventAdapter<UMMOGFXPlayer_Mall>(this, evts);
	TurnButton = TBS_None;
}

void UMMOGFXPlayer_Mall::UnInit()
{
	Super::UnInit();
}

void UMMOGFXPlayer_Mall::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	if(evt == NULL)
		return;
	MMOGameEvent_MallStore* pkEvent = (MMOGameEvent_MallStore*)evt;

	if(pkEvent->EventType == MMOGameEvent_MallStore::EMallStoreEvent_PageChange)
	{
		if(_mallPanel)
			_mallPanel->UpdateMallGoodsPanel();
	}
	else if (pkEvent->EventType == MMOGameEvent_MallStore::EMallStoreEvent_GoldChange)
	{
		if(_mallPanel)
			_mallPanel->UpdateGoldMoney(MallManager::getSingleton().GetRealMoney());

		if(_mallBuyPanel&&_mallBuyPanel->IsVisible)
			_mallBuyPanel->eventCallUpdateGoldMoney(MallManager::getSingleton().GetRealMoney());
	}
	else if (pkEvent->EventType == MMOGameEvent_MallStore::EMallStoreEvent_TypeChange)
	{
		if(_mallPanel)
			_mallPanel->UpdateMallGoodsPanel();
		if(_mallPanel)
			_mallPanel->UpdateMallHomePanel();
	}
	else if (pkEvent->EventType == MMOGameEvent_MallStore::EMallStoreEvent_BuyInfoChange)
	{
		if(_mallPanel)
			_mallPanel->UpdateNoticeBuy();
	}
	else if (pkEvent->EventType == MMOGameEvent_MallStore::EMallStoreEvent_NeedReqBuyInfo)
	{
		if(_mallPanel&&_mallPanel->IsVisible)
			MallController::getSingleton().SendReqUpdateBuyInfo();
	}
}

void UMMOGFXPlayer_Mall::ASClickGiveFriendGoods(const FString& roleName,INT nGoodsID,INT nNum)
{
	if(friendName.IsEmpty())
	{
		if(_mallBuyPanel)
		{
			if(_mallBuyPanel->giveBtn)
				_mallBuyPanel->giveBtn->SetString( TEXT("label") ,MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.GiveFriendBtnText2"))); 
			if(_mallBuyPanel->buyBtn)
				_mallBuyPanel->buyBtn->SetString( TEXT("label"),MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.BuyBtnText2")));
		}
	}
	friendName = roleName;
	if(_mallBuyPanel)
		_mallBuyPanel->eventCallSetBuyAimPlayerName(friendName);
	if( _mallFriendPanel != NULL)
		_mallFriendPanel->Show(FALSE);
	//ConfirmMallGiveFriendHint();
}

void UMMOGFXPlayer_Mall::ASClickGiveFriend(INT nGoodsID,INT nNum)
{
	MallManager::getSingleton().TestMallInfo();
	if(!friendName.IsEmpty())
	{
		friendName = TEXT("");
		if(_mallBuyPanel)
		{
			_mallBuyPanel->eventCallSetBuyAimPlayerName(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.GiveFriendTextHint")));
			if(_mallBuyPanel->giveBtn)
				_mallBuyPanel->giveBtn->SetString( TEXT("label"),MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.GiveFriendBtnText1")));
			if(_mallBuyPanel->buyBtn)
				_mallBuyPanel->buyBtn->SetString( TEXT("label"),MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.BuyBtnText1")));
		}
		if( _mallFriendPanel != NULL)
			_mallFriendPanel->Show(FALSE);
	}
	else
	{
		MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_MallFriend,TRUE, "");
		if( _mallFriendPanel != NULL)
			_mallFriendPanel->OnShowFriendPanel(nGoodsID,nNum);
	}
}

void UMMOGFXPlayer_Mall::ASClickBuyGoods(INT nGoodsID,INT nNum)
{
	//MallController::getSingleton().NotifyBuyResult(1010001);
	ConfirmMallBuyHint();
}

void UMMOGFXPlayer_Mall::ASClickBtnBuyVip()
{

}
void UMMOGFXPlayer_Mall::ASClickBtnCheckIn()
{

}
void UMMOGFXPlayer_Mall::ASAddGoldMoney()
{
	//MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.GoldAddHint")),MsgInfoType_Table,TEXT("MMOGame.Mall.GoldAddHint"));
	ShellExecute(NULL, L"open", L"http://www.cqyh.info", NULL, NULL, SW_SHOWNORMAL);
}
void UMMOGFXPlayer_Mall::ASClickMallTap(INT nIndex)
{
	if(_mallPanel == NULL)
		return;
	MallManager::getSingleton().SetGoodsPageType((MallStorePageType)nIndex);

	if(nIndex == (INT)MallStorePageHome)
		_mallPanel->UpdateMallHomePanel();
	else
		_mallPanel->UpdateMallGoodsPanel();
}
void UMMOGFXPlayer_Mall::ASClickMallGoods(INT nGoodsID)
{
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_MallBuyGoods,TRUE, ""); 
	if( _mallBuyPanel != NULL)
	{
		_mallBuyPanel->OnShowMallBuyPanel(nGoodsID);
		if (_mallEquipRolePanel)
		{
			_mallEquipRolePanel->OnShowMallEquipPanel(nGoodsID);
		}
		GoodsID = nGoodsID;
	}
}
void UMMOGFXPlayer_Mall::ASClickPrePage()
{
	 MallController::getSingleton().DecPage();
}
void UMMOGFXPlayer_Mall::ASClickNextPage()
{
	MallController::getSingleton().AddPage();
}
void UMMOGFXPlayer_Mall::ASClickDropMenuHotType(int nType)
{
	MallController::getSingleton().SetSortType(nType);
}
void UMMOGFXPlayer_Mall::ASClickDropMenuAvaibleType(int nType)
{
	MallController::getSingleton().SetShowType(nType);
}
void UMMOGFXPlayer_Mall:: ASStartDrag(class UGFxObject* SrcItemSlot,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID)
{

}
void UMMOGFXPlayer_Mall::ConfirmMallBuyHint()
{
	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT("ConfirmMallBuy");

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT("CancelMallBuy");	

	const REAL_MONEY_ITEM_INFO*	pkGoodsInfo	= MallManager::getSingleton().GetGoodsByID(GoodsID);
	if(pkGoodsInfo == NULL)
		return;
	UItem* pkItem = MMOFacade::getSingleton().FindItemTemplate( pkGoodsInfo->m_nItemTemplateID );
	if(pkItem == NULL)
		return;

	FString strInfo(TEXT(""));
	INT nNum = GetGoodsNum();
	if(friendName.IsEmpty())
	{
		strInfo = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.MallStore.GoodsBuyself1"));
		strInfo += UITextParser::HTMLBeginFont(UITextParser::HTMLGetItemColor((EItemColor)pkItem->ItemColor));
		strInfo += pkItem->GetDisplayName();
		strInfo += UITextParser::HTMLEndFont();
		strInfo += FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.MallStore.GoodsBuyNum")),nNum);
		strInfo += UITextParser::HTMLNewLine();
		strInfo += MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.MallStore.GoodsBuyCost"));
		strInfo += UITextParser::HTMLMoneyIconString(MONEYTYPE_04, pkGoodsInfo->m_nCurrentPrice*nNum);
		strInfo += "\n";
		strInfo += MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.MallStore.GoodsConfirmBuy1"));
	}
	else
	{
		strInfo = MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.MallStore.GoodsGive"));
		strInfo += UITextParser::HTMLBeginFont(UITextParser::HTMLGetItemColor((EItemColor)pkItem->ItemColor));
		strInfo += pkItem->GetDisplayName();
		strInfo += UITextParser::HTMLEndFont();
		strInfo += FString::Printf(*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.MallStore.GoodsBuyNum")),nNum);
		strInfo += UITextParser::HTMLNewLine();
		strInfo += MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.MallStore.GoodsBuyCost"));
		strInfo += UITextParser::HTMLMoneyIconString(MONEYTYPE_04, pkGoodsInfo->m_nCurrentPrice*nNum);
		strInfo += "\n";
		strInfo += MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.MallStore.GoodsConfirmGive"));
		strInfo += friendName;
		strInfo += TEXT("?");
	}
	MallBuyConfirmBox = MMOMsgBoxManager::getSingleton().AddModalMessageBox(strInfo/*MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.BuyConfirmHint"))*/, 0, funYes, funNo);
}
void UMMOGFXPlayer_Mall::ConfirmMallBuy(class UGFxObject* mc)
{
	if(mc == NULL)
		return;
	if(GoodsID > 0)
	{
		if(friendName.IsEmpty())
			MallController::getSingleton().SendBuyGoods(GoodsID,GetGoodsNum());
		else
			MallController::getSingleton().SendGiveFriendGoods(friendName,GoodsID,GetGoodsNum());
	}
		
	MallBuyConfirmBox = NULL;
}
void UMMOGFXPlayer_Mall::CancelMallBuy(class UGFxObject* mc)
{
	if(mc == NULL)
		return;
	MallBuyConfirmBox = NULL;
}

void UMMOGFXPlayer_Mall::ConfirmMallGiveFriendHint()
{
	FScriptDelegate funYes(EC_EventParm);
	funYes.Object = this;
	funYes.FunctionName = TEXT("ConfirmMallGiveFriend");

	FScriptDelegate funNo(EC_EventParm);
	funNo.Object = this;
	funNo.FunctionName = TEXT("CancelMallGiveFriend");	
	MallGiveFriendConfirmBox = MMOMsgBoxManager::getSingleton().AddModalMessageBox(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.BuyConfirmHint")), 0, funYes, funNo);
}

void UMMOGFXPlayer_Mall::ConfirmMallGiveFriend(class UGFxObject* mc)
{
	if(mc == NULL)
		return;
	if(GoodsID > 0)
		MallController::getSingleton().SendGiveFriendGoods(friendName,GoodsID,GetGoodsNum());
	MallGiveFriendConfirmBox = NULL;
}

void UMMOGFXPlayer_Mall::CancelMallGiveFriend(class UGFxObject* mc)
{
	if(mc == NULL)
		return;
	MallGiveFriendConfirmBox = NULL;
}
INT UMMOGFXPlayer_Mall::GetGoodsNum()
{
	INT nCount = 1;
	if(_mallBuyPanel&& _mallBuyPanel->textNum)
		nCount = appAtoi(*(_mallBuyPanel->textNum->GetText()));
	return nCount;
}
void UMMOGFXPlayer_Mall::ASClickSendToChat()
{
	UItem* item = MMOFacade::getSingleton().FindItemTemplate(GoodsID);
	if(item)
	{
		FString txt = LinkManager::HtmlLink_ColorItem(item);
		UMMOUIChat* Chat = Cast<UMMOUIChat>(MMOUI::FindUIPanel(TEXT("Chat")));
		if (Chat)
		{
			Chat->eventCallAppendInput(txt);
			MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.EquipRoleGoodsNameToChat")),MsgInfoType_Table,TEXT("MMOGame.Mall.EquipRoleGoodsNameToChat"));
		}
	}
}
void UMMOGFXPlayer_Mall::ASClickTakeOnOff()
{
	if(_mallEquipRolePanel)
		_mallEquipRolePanel->OnUpdateRoleEquip(GoodsID);
}
void UMMOGFXPlayer_Mall::ASClickTurnRight()
{
	TurnButton = TBS_Right;
}
void UMMOGFXPlayer_Mall::ASClickTurnLeft()
{
	TurnButton = TBS_Left;
}
void UMMOGFXPlayer_Mall::ASReleasTurn()
{
	TurnButton = TBS_None;
}
void UMMOGFXPlayer_Mall::PostAdvance ( FLOAT DeltaTime )
{
	if(TurnButton == TBS_None)
		return;
	UGFxMoviePlayer::PostAdvance(DeltaTime);
	if(_mallEquipRolePanel)
		_mallEquipRolePanel->OnUpdateTurn(TurnButton);
}