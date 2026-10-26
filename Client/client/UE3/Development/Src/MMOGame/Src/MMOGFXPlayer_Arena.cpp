#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOArenaManager.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Arena)

void UMMOGFXPlayer_Arena::PostAdvance(FLOAT dt)
{

}
//========================================================================================
void UMMOGFXPlayer_Arena::ASOnActionButtonClick()
{
	if( _ArenaEntrance == NULL ){
		return;
	}

	//
	EArenaState curArenaSta = MMOArenaManager::getSingleton().GetCurArenaState();
	switch( curArenaSta )
	{
	case EAnaSta_Applied:
		{
			_ArenaEntrance->CanelApplyForArena();
		}
		break;
	case EAnaSta_WaitApply:
		{
			_ArenaEntrance->ApplyForArena();
		}
		break;
	case EAnaSta_ToGetAward:
		{
			_ArenaEntrance->ToGetArenaReward();
		}
		break;
	default:
		break;
	}
}
//========================================================================================
void UMMOGFXPlayer_Arena::ASToggleShowBonusPanel( UBOOL isToShow )
{
	if( _ArenaEntrance == NULL ){
		return;
	}

	if( isToShow == TRUE ){
		//竞技场胜负奖励
		_ArenaEntrance->UpdateArenaMnyReward();
		//竞技场胜负
		_ArenaEntrance->UpdateArenaWinResult();
	}

}
//========================================================================================
void UMMOGFXPlayer_Arena::ASOnFightingButtonClick()
{
	if( _ArenaState == NULL ){
		return;
	}

	//
	_ArenaState->TryNextRound();
}
//========================================================================================
void UMMOGFXPlayer_Arena::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_Arena::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Arena);

	__OnPostAdvance__Delegate = FScriptDelegate(this, TEXT("PostAdvance"));
}

//========================================================================================
void UMMOGFXPlayer_Arena::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm);
	__OnPostAdvance__Delegate = nullDelgate;
}