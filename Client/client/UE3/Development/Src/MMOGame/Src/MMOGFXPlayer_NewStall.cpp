#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "UStallManager.h"
#include "MMOMsgBoxManager.h"


IMPLEMENT_CLASS(UMMOGFXPlayer_NewStall)

//------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_NewStall::ASOnPanelClose(const FString& PanelName)
{
	AMMOPlayer* pl = MMOFacade::getSingleton().GetMainPlayer();

	if( PanelName == MMOUI::GetUIManager()->Panel_Stall_StallSetting.GetNameString() && pl->MoveType == EMT_PrepareStall )
	{
		CMessageHandler::GetInstance().Send_RealCloseStall(); 
		return;
	}
	Super::ASOnPanelClose( PanelName );
}

void UMMOGFXPlayer_NewStall::RequireOpenStall()
{
	AMMOPlayer* pl;
	pl = MMOFacade::getSingleton().GetMainPlayer();
	if( !pl )
		return;
	if( pl->MoveType >= EMT_PrepareStall )
	{
		MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_Stall_StallSetting,TRUE, "");
	}
	else
	{
		AMMOPlayer* mainPlayer = MMOFacade::getSingleton().GetMainPlayer();
		if (mainPlayer)
		{
			UActorAttribute* attri = mainPlayer->ActorAttributes;
			if (attri)
			{
				if (attri && attri->LevelAttributes.Level >= OPEN_STALL_LEVEL)
				{
					UStallManager::getSingleton().RequestOpenStall();
				}
				else
				{
					FString text = FString::Printf(*MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Stall.LevelLimit")), OPEN_STALL_LEVEL);
					MMOUI::GetUIManager()->delegateAddScreenMessage(text,MsgInfoType_Table,TEXT("MMOGame.Quest.LevelLimit"));
				}
			}
		}
	}
}

void UMMOGFXPlayer_NewStall::Init()
{
	Super::Init();
	check(FALSE && "UMMOGFXPlayer_NewStall::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Stall );
}

void UMMOGFXPlayer_NewStall::ASOnCloseStallSetting()
{
	AMMOPlayer* pl = MMOFacade::getSingleton().GetMainPlayer();

	if(pl->MoveType == EMT_PrepareStall )
	{
		CMessageHandler::GetInstance().Send_RealCloseStall(); 
	}
}

void UMMOGFXPlayer_NewStall::ASStallSettingSetYes(INT stallSlot,INT conSlot,INT itemSlot,INT count,INT price)
{
	if (price < MIN_STALL_PRICE)
	{
		FString text = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Stall.BuyItemPriceError"));
		MMOUI::GetUIManager()->delegateAddScreenMessage(text, MsgInfoType_Table, text);
		return;
	}

	if (count < 1)
	{
		FString text = MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Stall.BuyItemCountError"));
		MMOUI::GetUIManager()->delegateAddScreenMessage(text, MsgInfoType_Table, text);
		return;
	}

	CMessageHandler::GetInstance().Send_AddStallItem(stallSlot, conSlot, itemSlot, count, price); 
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_Stall_StallMsg, FALSE, "");
}

void UMMOGFXPlayer_NewStall::ASStallBuySetYes(INT stallSlot, INT Count)
{
	StallItemInfo stallItemInfo;
	if (UStallManager::getSingleton().GetStallBuyItem(stallSlot, stallItemInfo))
	{
		CMessageHandler::GetInstance().Send_BuyStallItem(UStallManager::getSingleton().GetStallBuyPlayerId(), stallSlot, Count, stallItemInfo.ModifyTime); 
		MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_Stall_StallMsg, FALSE, "");
	}
}

void UMMOGFXPlayer_NewStall::ASStallMsgBoxSetNo()
{
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_Stall_StallMsg, FALSE, "");
}

void UMMOGFXPlayer_NewStall::ASStallStart(const FString& inStallName,const FString& inStallAd)
{
	if( !UStallManager::getSingleton().CheckStartStallSetting() )
	{
		FScriptDelegate funcOk(EC_EventParm);
		MMOMsgBoxManager::getSingleton().AddModalMessageBox(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.GamePlay.NotHasAnyToSell")),0,funcOk,funcOk,FALSE);
		return;
	}

	//FString& stallAd = UStallManager::getSingleton().GetStallAdd();
	//FString& stallName = UStallManager::getSingleton().GetStallName();
	UStallManager::getSingleton().SetStallName(inStallName);

	if(MMOUI::HasCensoredWord(inStallAd))
	{
		//@!TODO
		MMOUI::GetUIManager()->delegateAddScreenMessage(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOErrorInfo.ERROR_CODE_DEF.errStallInvalidAdv")),MsgInfoType_Table,TEXT("MMOErrorInfo.ERROR_CODE_DEF.errStallInvalidAdv"));
		return;
	}

	CMessageHandler::GetInstance().Send_ChangeStallName(*inStallName); 
	CMessageHandler::GetInstance().Send_RealOpenStall();
}

void UMMOGFXPlayer_NewStall::ASCloaseStall()
{
	FScriptDelegate funCancel(EC_EventParm);
	FScriptDelegate funOk(EC_EventParm);
	funOk.FunctionName = TEXT("CloseStall");
	funOk.Object = this;
	MMOMsgBoxManager::getSingleton().AddModalMessageBox(MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.GamePlay.NotHasAnyToSell")),0,funOk,funCancel);
}

void UMMOGFXPlayer_NewStall::ASStallSetNPC()
{

}

void UMMOGFXPlayer_NewStall::CloseStall()
{
	CMessageHandler::GetInstance().Send_CloseStall() ; 
}

void UMMOGFXPlayer_NewStall::UnInit()
{
	Super::UnInit();
}