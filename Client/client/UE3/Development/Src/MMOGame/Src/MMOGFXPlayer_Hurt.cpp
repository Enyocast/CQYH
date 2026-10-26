#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOHurtManager.h"
#include "UITextParser.h"
#include "MMOMsgBoxManager.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Hurt)

	void UMMOGFXPlayer_Hurt::PostAdvance ( FLOAT DeltaTime )
{

	UGFxMoviePlayer::PostAdvance(DeltaTime);

}

void UMMOGFXPlayer_Hurt::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Hurt::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Hurt);
}

void UMMOGFXPlayer_Hurt::UnInit()
{
	Super::UnInit();
}

void UMMOGFXPlayer_Hurt::ASViewPage_ClickHurtClear()
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

void UMMOGFXPlayer_Hurt::OnClearHurt()
{
	MMOHurtManager::getSingleton().RestHurt();
}

void UMMOGFXPlayer_Hurt::ASShowHurtTips(UGFxObject *mc)
{
	if( mc == NULL ){
		return;
	}

	FString hint= TEXT("");
	hint += FString::Printf( *MMOUI::ParseLocalizedPropertyPath( TEXT("MMOGame.Hurt.AllHurt") ), MMOHurtManager::getSingleton().GetAllhurt() );
	mc->SetString( TEXT("tipsHtml"),hint);
	MMOUI::GetUIManager()->delegateShowTipsHTML(TFT_PlainText, mc);
}
void UMMOGFXPlayer_Hurt::ASHideHurtTips()
{
	MMOUI::GetUIManager()->delegateHideTips();
}

void UMMOGFXPlayer_Hurt::ResetMsg()
{
	if( ConfirmMsgBox != NULL )
	{
		ConfirmMsgBox->SetVisible( FALSE );
		ConfirmMsgBox = NULL;
	}
}

void UMMOGFXPlayer_Hurt::ASCloseHurtTips()
{
	UMMOUIManager* uimgr = MMOUI::GetUIManager();
	if (uimgr)
	{
		uimgr->DrawHurt = FALSE;
		MMOUI::GetUIManager()->ShowHurtPanel(uimgr->DrawHurt);
		uimgr->SaveConfigToServer();
	}

}