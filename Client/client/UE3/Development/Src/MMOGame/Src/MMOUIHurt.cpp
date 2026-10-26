#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOHurtManager.h"
#include "TeamManager.h"
#include "MMOStats.h"
#include "MMOMsgBoxManager.h"


IMPLEMENT_CLASS(UMMOUIHurt)

void UMMOUIHurt::Init()
{
	Super::Init();
	check(EventAdapter == NULL);
	TArray<EGameEvent> evts;
	evts.AddItem(GameEvent_ResetHurt);
	EventAdapter = new TGameEventAdapter<UMMOUIHurt>(this, evts);
}

void UMMOUIHurt::PreOnShow(UBOOL show)
{
	Super::PostOnShow(show);
	if (show)
	{
		MMOHurtManager::getSingleton().PostUpdateEvent();
	}

}
void UMMOUIHurt::UnInit()
{
	Super::UnInit();
}
void UMMOUIHurt::OnNativeGameEvent(struct MMOGameEvent* evt)
{
	//check(NULL != evt);
	if (NULL != evt)
	{
		switch(evt->GetEventType())
		{
		case  GameEvent_ResetHurt:
			{
				FString hurt = appItoa(MMOHurtManager::getSingleton().GetAllhurt());
				this->eventUCSetHurtViewPage_AllData(hurt,MMOHurtManager::getSingleton().GetHurtTime());
			}
			break;
		}
	}
}

//-----------Moved----------------

void UMMOUIHurt::ASViewPage_ClickHurtClear()
{
	ResetMsg();
	FScriptDelegate HurtClearDelegate(EC_EventParm);
	HurtClearDelegate.FunctionName = TEXT("OnClearHurt");
	HurtClearDelegate.Object = this;

	FScriptDelegate Nofunction(EC_EventParm);
	Nofunction.FunctionName = TEXT("");
	Nofunction.Object = this;

	FString text =  MMOUI::ParseLocalizedPropertyPath(TEXT("MMOGame.Hurt.ClearHurt"));

	ConfirmMsgBox = MMOMsgBoxManager::getSingleton().AddMessageBox( text , 0 , HurtClearDelegate , Nofunction );

}

void UMMOUIHurt::OnClearHurt()
{
	MMOHurtManager::getSingleton().RestHurt();
}

void UMMOUIHurt::ASShowHurtTips(UGFxObject *mc)
{
	if( mc == NULL ){
		return;
	}

	FString hint= TEXT("");
	hint += FString::Printf( *MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Hurt.AllHurt") ), MMOHurtManager::getSingleton().GetAllhurt() );
	mc->SetString( TEXT("tipsHtml"),hint);
	MMOUI::GetUIManager()->delegateShowTipsHTML(TFT_PlainText, mc);
}
void UMMOUIHurt::ASHideHurtTips()
{
	MMOUI::GetUIManager()->delegateHideTips();
}

void UMMOUIHurt::ResetMsg()
{
	if( ConfirmMsgBox != NULL )
	{
		ConfirmMsgBox->SetVisible( FALSE );
		ConfirmMsgBox = NULL;
	}
}

void UMMOUIHurt::ASCloseHurtTips()
{
	UMMOUIManager* uimgr = MMOUI::GetUIManager();
	if (uimgr)
	{
		uimgr->DrawHurt = FALSE;
		MMOUI::GetUIManager()->ShowHurtPanel(uimgr->DrawHurt);
		uimgr->SaveConfigToServer();
	}

}