#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "MMOArenaManager.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_PVP)

void UMMOGFXPlayer_PVP::PostAdvance(FLOAT dt)
{
	if( _PVP != NULL ){
		_PVP->TickForTestInteractNPCDistance(dt);
	}
	//
	if( _PVPBattle != NULL ){
		if( !_PVPBattle->IsWaitingBattle() ){
			_PVPBattle->TickForTestInteractNPCDistance(dt);
		}

		if( _PVPBattle->ConfirmMsgBox != NULL ){
			_PVPBattle->UpdateTime( dt );
		}
	}
	////
	//if( dt >= 0 )
	//{
	//	if(_ArenaQueue)
	//	{
	//		_ArenaQueue->UpdateTime(dt);
	//	}

	//	if(_ArenaHint)
	//	{
	//		_ArenaHint->UpdateTime(dt);
	//	}
	//}

}


void UMMOGFXPlayer_PVP::ASArenaLeave()
{
	//MMOArenaManager::getSingleton().LeaveArena();
}


void UMMOGFXPlayer_PVP::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_PVP::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_PVP);

	__OnPostAdvance__Delegate = FScriptDelegate(this, TEXT("PostAdvance"));
}

void UMMOGFXPlayer_PVP::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm);
	//MMOUI::GetUIManager()->SetOpenShopDelegate(nullDelgate);


	//MMOUI::GetUIManager()->SetOpenArenaScoreSingleDelegate(nullDelgate);
	MMOUI::GetUIManager()->SetCloseArenaScoreDelegate(nullDelgate);

	__OnPostAdvance__Delegate = nullDelgate;
}