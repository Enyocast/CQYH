#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOGoldStoreManager.h"
#include "UITextParser.h"
#include "MMOMsgBoxManager.h"
#include "exchange_def.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_GoldStore)

void UMMOGFXPlayer_GoldStore::Init()
{
	Super::Init();
	check(FALSE && "UMMOGFXPlayer_GoldStore::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_GoldStore);
}

void UMMOGFXPlayer_GoldStore::UnInit()
{
	Super::UnInit();
}

void  UMMOGFXPlayer_GoldStore::ASGoldStoreClickTabPage(int nIndex,int type)
{
	MMOGoldStoreManager::getSingleton().SetCurrentTabPage((EGoldTabType)nIndex);
	//ASFreshListView(type);
}

void UMMOGFXPlayer_GoldStore::ASFreshListView(int type)
{
	switch(MMOGoldStoreManager::getSingleton().GetCurrentTabPage())
	{
	case EGTT_buyView:
		{
			CMessageHandler::GetInstance().Send_ListPrice();
		}
		break;
	case EGTT_historyView:
		{
			CMessageHandler::GetInstance().Send_ListPrice();
		}
		break;
	case EGTT_myOrderView:
		{
			CMessageHandler::GetInstance().Send_List_MyOrder();
		}
		break;
	}
}

void UMMOGFXPlayer_GoldStore::ASGoldStoreBuy(class UGFxObject* dt)
{
	UINT32 price = dt->GetInt(TEXT("buy_UnitPrice"));
	UINT32 count = dt->GetInt(TEXT("buy_Number"));

	/*if(CheckGoldStoreOrder(price,count))
	{
	return;
	}*/

	HideGoldStore_Msg();

	FScriptDelegate GoldStoreDelegate(EC_EventParm);
	GoldStoreDelegate.FunctionName = TEXT("OnGoldStoreMsg_Buy_Ok");
	GoldStoreDelegate.Object = this;

	FScriptDelegate Nofunction(EC_EventParm);
	Nofunction.FunctionName = TEXT("OnGoldStoreMsg_Buy_No");
	Nofunction.Object = this;

	ConfirmMsgBox = MMOMsgBoxManager::getSingleton().AddMessageBox(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Exchange.Order.Buy") )  , price , GoldStoreDelegate , Nofunction );

	if(ConfirmMsgBox)
		ConfirmMsgBox->SetInt( TEXT("itemdataid") , count);
	
}

void UMMOGFXPlayer_GoldStore::OnGoldStoreMsg_Buy_Ok(UGFxObject* mc)
{
	ASSERT_CHECK_ERROR_RETURN(mc);
	UINT32 price = mc->GetInt(TEXT("iteminfoid"));
	UINT32 count = mc->GetInt(TEXT("itemdataid"));
	CMessageHandler::GetInstance().Send_AddOrder(eotBuy,MONEYTYPE_02,price,count);
}

void UMMOGFXPlayer_GoldStore::OnGoldStoreMsg_Buy_No(UGFxObject* mc)
{
	ConfirmMsgBox = NULL;
}

void UMMOGFXPlayer_GoldStore::ASGoldStoreSell(class UGFxObject* dt)
{
	UINT32 price = dt->GetInt(TEXT("sell_UnitPrice"));
	UINT32 count = dt->GetInt(TEXT("sell_Number"));

	HideGoldStore_Msg();

	FScriptDelegate GoldStoreDelegate(EC_EventParm);
	GoldStoreDelegate.FunctionName = TEXT("OnGoldStoreMsg_Sell_Ok");
	GoldStoreDelegate.Object = this;

	FScriptDelegate Nofunction(EC_EventParm);
	Nofunction.FunctionName = TEXT("OnGoldStoreMsg_Sell_No");
	Nofunction.Object = this;

	ConfirmMsgBox = MMOMsgBoxManager::getSingleton().AddMessageBox(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Exchange.Order.Sell") )  , price , GoldStoreDelegate , Nofunction );

	if(ConfirmMsgBox)
		ConfirmMsgBox->SetInt( TEXT("itemdataid") , count);

	
}

void UMMOGFXPlayer_GoldStore::OnGoldStoreMsg_Sell_Ok(UGFxObject* mc)
{
	ASSERT_CHECK_ERROR_RETURN(mc);
	UINT32 price = mc->GetInt(TEXT("iteminfoid"));
	UINT32 count = mc->GetInt(TEXT("itemdataid"));
	CMessageHandler::GetInstance().Send_AddOrder(eotSell,MONEYTYPE_02,price,count);
}
void UMMOGFXPlayer_GoldStore::OnGoldStoreMsg_Sell_No(UGFxObject* mc)
{
	ConfirmMsgBox = NULL;
}

void UMMOGFXPlayer_GoldStore::ASGoldStoreShowMyOrder(int type)
{
	CMessageHandler::GetInstance().Send_List_MyOrder();
	MMOGoldStoreManager::getSingleton().SetIsUpdateOrderCount(FALSE);
}

void UMMOGFXPlayer_GoldStore::ASGoldStoreCancelSell(int type,int id)
{
	HideGoldStore_Msg();

	FScriptDelegate GoldStoreDelegate(EC_EventParm);
	GoldStoreDelegate.FunctionName = TEXT("OnGoldStoreMsg_Cancel_Ok");
	GoldStoreDelegate.Object = this;

	FScriptDelegate Nofunction(EC_EventParm);
	Nofunction.FunctionName = TEXT("OnGoldStoreMsg_Cancel");
	Nofunction.Object = this;

	ConfirmMsgBox = MMOMsgBoxManager::getSingleton().AddMessageBox(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Exchange.CancelOrder") )  , id , GoldStoreDelegate , Nofunction );

	
}

void UMMOGFXPlayer_GoldStore::OnGoldStoreMsg_Cancel_Ok(UGFxObject* mc)
{
	ASSERT_CHECK_ERROR_RETURN(mc);
	INT id = mc->GetInt(TEXT("iteminfoid"));
	CMessageHandler::GetInstance().Send_CancelOrder(id);
}

void UMMOGFXPlayer_GoldStore::OnGoldStoreMsg_Cancel(UGFxObject* mc)
{
	ConfirmMsgBox = NULL;
}

void UMMOGFXPlayer_GoldStore::HideGoldStore_Msg()
{
	if( ConfirmMsgBox != NULL )
	{
		ConfirmMsgBox->SetVisible( FALSE );
		ConfirmMsgBox = NULL;
	}
}

void UMMOGFXPlayer_GoldStore::ASBuyMoney()
{
	MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Mall.GoldAddHint")),MsgInfoType_Table,TEXT("MMOGame.Mall.GoldAddHint"));
}

bool UMMOGFXPlayer_GoldStore::CheckGoldStoreOrder(INT money,INT count)
{
	bool v = false;

	if (money <= 0)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.GoldStore.MoneyNotEnough")),MsgInfoType_Table,TEXT("MMOGame.GoldStore.MoneyNotEnough"));
		v = true;
	}
	else if(count <= 0)
	{
		MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.GoldStore.CountNotEnough")),MsgInfoType_Table,TEXT("MMOGame.GoldStore.CountNotEnough"));
		v = true;
	}
	return v;
	
}