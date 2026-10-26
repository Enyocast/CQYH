#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_RClickMenu)

//--------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_RClickMenu::ASClickRightMenuItem(INT MenuLevel,INT ItemId)
{
	if( RClickMenu )
	{
		RClickMenu->eventClickItem( MenuLevel , ItemId );
	}
}

void UMMOGFXPlayer_RClickMenu::Init()
{
	Super::Init();
		
	check(FALSE && "UMMOGFXPlayer_RClickMenu::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_RClickMenu);
}