#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"
#include "EquipDecomposeManager.h"



IMPLEMENT_CLASS(UMMOGFXPlayer_EquipDecompose)


void UMMOGFXPlayer_EquipDecompose::Init()
{
	Super::Init();
	check(FALSE && "UMMOGFXPlayer_EquipDecompose::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_EquipDecompose);
}

void UMMOGFXPlayer_EquipDecompose::UnInit()
{
	Super::UnInit();
}

void UMMOGFXPlayer_EquipDecompose::ASCompose()
{
	INT id = EquipDecomposeManager::getSingleton().GetComposedId();
	if( id >= 0 )
	{
		EquipDecomposeManager::getSingleton().ComposeEquip(id);
	}
}

void UMMOGFXPlayer_EquipDecompose::ASDecomposeOk()
{
	UMMOUIEquipDecomposeHintPanel* hintPanel = Cast<UMMOUIEquipDecomposeHintPanel>(MMOUI::FindUIPanel(MMOUI::GetUIManager()->Panel_EquipDecomposeHint));
	if(hintPanel)
	{
		hintPanel->DecomposeOk();
	}

	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_EquipDecomposeHint, FALSE, "");
}

void UMMOGFXPlayer_EquipDecompose::ASDecomposeCancel()
{
	MMOUI::GetUIManager()->ShowPanelEx(MMOUI::GetUIManager()->Panel_EquipDecomposeHint, FALSE, "");
}

void UMMOGFXPlayer_EquipDecompose::ASNotifyComposeSuccessAnimPlayedOver()
{
	if( m_ComposePanel == NULL ){
		return;
	}

	m_ComposePanel->NotifyComposeSuccessAnimPlayedOver();
}
