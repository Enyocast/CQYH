#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_FBTask)


void UMMOGFXPlayer_FBTask::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_FBTask::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_FBTask);
}

void UMMOGFXPlayer_FBTask::UnInit()
{
	Super::UnInit();
}
