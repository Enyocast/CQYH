#include "stdafx.h"
#include "MMOGameUIClasses.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_PopUpHintBox)

//========================================================================================================
void UMMOGFXPlayer_PopUpHintBox::ASCloseNewEquipmentHintBox()
{
	if( _EquipGainHintBox == NULL ){
		return;
	}

	//
	//_EquipGainHintBox->TryShowNextOrHide();
	_EquipGainHintBox->Show( FALSE );
}

//==============================================================================================
void UMMOGFXPlayer_PopUpHintBox::ASCheckNewEquipment()
{
	if( _EquipGainHintBox == NULL ){
		return;
	}

	//
	_EquipGainHintBox->CheckNewEquipment();
}

//======================================================================================
void UMMOGFXPlayer_PopUpHintBox::Init()
{
	Super::Init();
	check(FALSE && "UMMOGFXPlayer_PopUpHintBox::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_PopUpHintBox);
}

void UMMOGFXPlayer_PopUpHintBox::UnInit()
{
	Super::UnInit();
}