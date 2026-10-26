#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_WeaponExp)


void UMMOGFXPlayer_WeaponExp::Init()
{
	Super::Init();
	check(FALSE && "UMMOGFXPlayer_WeaponExp::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_WeaponExp);
}

void UMMOGFXPlayer_WeaponExp::UnInit()
{
	Super::UnInit();

}

