#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_SoulLevelUp)

//===============================================================================================================
//soul level up
void UMMOGFXPlayer_SoulLevelUp::ASConfirmSoulLevelUp()
{
	if( _SoulLevelUpPanel == NULL ){
		return;
	}

	//
	_SoulLevelUpPanel->ConfirmSoulLevelUp();
}

//===============================================================================================================
void UMMOGFXPlayer_SoulLevelUp::ASResetSoulLevelUp()
{
	if( _SoulLevelUpPanel == NULL ){
		return;
	}

	//
	_SoulLevelUpPanel->ResetSoulLevelUp();
}

//===============================================================================================================
void UMMOGFXPlayer_SoulLevelUp::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_SoulLevelUp::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_SoulLevelUp);
}

void UMMOGFXPlayer_SoulLevelUp::UnInit()
{
	Super::UnInit();
}