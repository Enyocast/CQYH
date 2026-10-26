#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_WeaponSkill)

//===============================================================================================================
void UMMOGFXPlayer_WeaponSkill::ASClickToTryGetWeaponSkill()
{
	if( _WeaponSkillPanel == NULL ){
		return;
	}

	_WeaponSkillPanel->TryGetWeaponSkill( TRUE );
}
//===============================================================================================================
void UMMOGFXPlayer_WeaponSkill::ASShowTips_WeaponSkill( UGFxObject *mc )
{
	if( mc == NULL ){
		return;
	}

	INT uniqueSkillID = mc->GetInt( TEXT("UniqueSkillID") );
	if( uniqueSkillID > 0 ){
		MMOUI::GetUIManager()->delegateShowTipsHTML(TFT_SkillTemplate, mc);
	}
}

//--------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_WeaponSkill::ASHideTips_WeaponSkill()
{
	MMOUI::GetUIManager()->delegateHideTips();
}

//===============================================================================================================
void UMMOGFXPlayer_WeaponSkill::ASShowTips_ConsumeItem( UGFxObject *mc )
{
	if( mc == NULL ){
		return;
	}
	
	MMOUI::GetUIManager()->delegateShowTipsHTML( TFT_AwardIcon, mc );
}

//--------------------------------------------------------------------------------------------------------------
void UMMOGFXPlayer_WeaponSkill::ASHideTips_ConsumeItem()
{
	MMOUI::GetUIManager()->delegateHideTips();
}
//===============================================================================================================
void UMMOGFXPlayer_WeaponSkill::ASOnClickAutoChangeSkillChkBtn()
{
	if( _WeaponSkillPanel == NULL ){
		return;
	}

	_WeaponSkillPanel->OnClickAutoChangeSkillChkBtn();
}

//===============================================================================================================
void UMMOGFXPlayer_WeaponSkill::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_WeaponSkill::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_WeaponSkill);
}

void UMMOGFXPlayer_WeaponSkill::UnInit()
{
	Super::UnInit();
}