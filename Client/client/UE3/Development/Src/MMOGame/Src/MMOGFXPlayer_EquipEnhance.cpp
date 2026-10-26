#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_EquipEnhance)


void UMMOGFXPlayer_EquipEnhance::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_EquipEnhance::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_EquipEnhance);
}

void UMMOGFXPlayer_EquipEnhance::UnInit()
{
	Super::UnInit();
}