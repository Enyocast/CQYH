#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_Death)


void UMMOGFXPlayer_Death::Init()
{
	Super::Init();

	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_Death);

	//MMOUI::GetUIManager()->SetCallShowWaitingReviveDelegate(FScriptDelegate(this, TEXT("CallShowWaitingRevive")));

}

void UMMOGFXPlayer_Death::UnInit()
{
	Super::UnInit();

	FScriptDelegate nullDelgate(EC_EventParm) ;
	//MMOUI::GetUIManager()->SetCallShowWaitingReviveDelegate(nullDelgate);
}

void UMMOGFXPlayer_Death::CallShowWaitingRevive(INT CountDownTime)
{
	//if(_Death)
	//{
	//	_Death->NativeCallShowWaitingRevive(CountDownTime);
	//}
}