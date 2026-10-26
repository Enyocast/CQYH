#include "stdafx.h"
#include "MMOGameUIClasses.h"
#include "MMOFacade.h"

IMPLEMENT_CLASS(UMMOGFXPlayer_WeaponSkillSetting)


//===============================================================================================================
void UMMOGFXPlayer_WeaponSkillSetting::ASLevleUpWeaponSkill( INT skillSlotIdx )
{
	if( _WeaponSkillSettingPanel == NULL ){
		return;
	}

	_WeaponSkillSettingPanel->LevleUpWeaponSkill( skillSlotIdx );
}

//===============================================================================================================
void UMMOGFXPlayer_WeaponSkillSetting::Init()
{
	Super::Init();

	check(FALSE && "UMMOGFXPlayer_WeaponSkillSetting::Init()");
	//MMOUI::RegisterMoviePlayer(this, MMOUI::GetUIManager()->MoviePlayer_WeaponSkillSetting);
}

void UMMOGFXPlayer_WeaponSkillSetting::UnInit()
{
	Super::UnInit();
}