#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

#include "MMOHintButtonManager.h"


IMPLEMENT_CLASS(UMMOGFXPlayer_HintButtonBar)

void UMMOGFXPlayer_HintButtonBar::ASHintButtonClick(INT id)
{
	MMOHintButtonManager::getSingleton().ClickButton(id);
}

void UMMOGFXPlayer_HintButtonBar::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_HintButtonBar::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_HintButtonBar);
}
