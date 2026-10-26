#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
//#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_BattleSummary)

//void UMMOGFXPlayer_BattleSummary::PlayTenSecCountDownAfter()
//{
//	UGFxObject *parentMc = GetVariableObject("root.TenSecCountDown_mc");
//	if( parentMc == NULL ){
//		return;
//	}
//	parentMc->SetVisible( TRUE );
//
//	UGFxObject *animMc = parentMc->GetObject( TEXT("anim_mc") );
//	if( animMc == NULL ){
//		return;
//	}
//	animMc->GotoAndPlayI( 2 );
//}

//==========================================================================================================
void UMMOGFXPlayer_BattleSummary::ToggleBattleSummary()
{
	if( _BattleSummary == NULL ){
		return;
	}
	//
	if( !_BattleSummary->IsVisible ){
		//_BattleSummary.NativeShow( true );
		_BattleSummary->QueryData();
	}
	else{
		_BattleSummary->NativeShow( FALSE );
	}
}
//==========================================================================================================
void UMMOGFXPlayer_BattleSummary::ASUpdateBattleSummary( INT tabIdx )
{
	if( _BattleSummary == NULL ){
		return;
	}
	//
	_BattleSummary->UpdateBattleSummary( tabIdx );
}
//==========================================================================================================
void UMMOGFXPlayer_BattleSummary::ASLeaveBattle()
{
	if( _BattleSummary == NULL ){
		return;
	}
	//
	_BattleSummary->LeaveBattle();
}
//==========================================================================================================
void UMMOGFXPlayer_BattleSummary::ASNotifyBattleTimesUp()
{

}
//==========================================================================================================
void UMMOGFXPlayer_BattleSummary::Init()
{
	Super::Init();

	MMOUI::GetUIManager()->SetToggleBattleSummaryDelegate(FScriptDelegate(this, TEXT("ToggleBattleSummary")));
	check(FALSE && "UMMOGFXPlayer_BattleSummary::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_BattleSummary);
}

void UMMOGFXPlayer_BattleSummary::UnInit()
{
	Super::UnInit();

	MMOUI::GetUIManager()->SetToggleBattleSummaryDelegate(FScriptDelegate(EC_EventParm));
}