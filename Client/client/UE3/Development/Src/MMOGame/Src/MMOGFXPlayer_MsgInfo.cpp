#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_MsgInfo)


//------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_MsgInfo::PostAdvance(FLOAT DeltaTime)
{
	if( MsgInfo )
	{
		MsgInfo->TickWidget(DeltaTime);
	}
}

void UMMOGFXPlayer_MsgInfo::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_MsgInfo::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_MsgInfo);

}

