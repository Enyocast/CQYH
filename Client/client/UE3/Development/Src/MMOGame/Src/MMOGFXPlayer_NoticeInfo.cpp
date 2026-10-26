#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_NoticeInfo)


//------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_NoticeInfo::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_NoticeInfo::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_NoticeInfo);

}

