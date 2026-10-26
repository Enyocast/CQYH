#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_EquipLevelUp)

	//==================================================================================================
void UMMOGFXPlayer_EquipLevelUp::ASConfirmUpgrade()
{
	if( _EquipLevelUp == NULL ){
		return;
	}
	_EquipLevelUp->ConfirmLevelUpEquip();
}

//==================================================================================================
void UMMOGFXPlayer_EquipLevelUp::ASCancelUpgrade()
{
	if( _EquipLevelUp == NULL ){
		return;
	}
	_EquipLevelUp->ResetCurOperation();
}

//==================================================================================================
void UMMOGFXPlayer_EquipLevelUp::ASShowResultConfirmBox( UBOOL isToShow )
{
	if( _EquipLevelUp == NULL ){
		return;
	}
	_EquipLevelUp->ShowLevelUpResultConfirmBox( isToShow );
}
//
void UMMOGFXPlayer_EquipLevelUp::ASConfirmMessage()
{
	if( _EquipLevelUp == NULL ){
		return;
	}
	_EquipLevelUp->ShowLevelUpResultConfirmBox( FALSE );
}

//==================================================================================================
void UMMOGFXPlayer_EquipLevelUp::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_EquipLevelUp::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_EquipLevelUp);
}

//==================================================================================================
void UMMOGFXPlayer_EquipLevelUp::UnInit()
{
	Super::UnInit();
}