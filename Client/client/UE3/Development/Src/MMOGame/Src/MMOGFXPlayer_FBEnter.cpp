#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_FBEnter)
	
void UMMOGFXPlayer_FBEnter::BeforeViewUpdate(float DeltaTime)
{
	//Super::PostAdvance(DeltaTime);
	//mini Map
	if( _FBEnter && _FBEnter->IsVisible ){
		_FBEnter->TickPanel(DeltaTime);
	}
}

void UMMOGFXPlayer_FBEnter::Init()
{
	Super::Init();
	check(FALSE && "UMMOGFXPlayer_FBEnter::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_FBEnter);
}

void UMMOGFXPlayer_FBEnter::UnInit()
{
	Super::UnInit();
}
