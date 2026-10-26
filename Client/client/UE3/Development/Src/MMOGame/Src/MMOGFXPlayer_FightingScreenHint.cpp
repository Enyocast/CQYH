#include "stdafx.h"
#include "MMOGameUIClasses.h"
//#include "MMOScreenMsgMgr.h"
#include "ScreenMsgQueue.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_FightingScreenHint)


void UMMOGFXPlayer_FightingScreenHint::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_FightingScreenHint::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_FightingScreenHint);
}

//===================================================================================
void UMMOGFXPlayer_FightingScreenHint::ASBeforeFightTenSecCountDownEnd()
{
	if( _FightingScreenHint != NULL ){
		_FightingScreenHint->Show( FALSE );
	}
}

//===================================================================================
void UMMOGFXPlayer_FightingScreenHint::ASOnExitCountDownTimeOver()
{
	if( _FightingScreenHint != NULL ){
		_FightingScreenHint->Show( FALSE );
	}
}

//===================================================================================
void UMMOGFXPlayer_FightingScreenHint::ASScreenPopUpBoxMsgPlayEnd()
{
	ScreenMessageQueue::getSingleton().NotifyEndPlayMsg();
}