class MMOGFXPlayer_WeaponSkillSetting extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIWeaponSkillSetting _WeaponSkillSettingPanel;

//
function RegisterWeaponSkillSetting( MMOUIWeaponSkillSetting mc )
{
	_WeaponSkillSettingPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_WeaponSkillSetting);
}
//

final native function ASLevleUpWeaponSkill( int skillSlotIdx );
//final native function ASReplaceWeaponSkill( int skillSlotIdx );

DefaultProperties
{
	MovieInfoStr="UI_WeaponSkillSetting.WeaponSkillSetting"
	Priority=5
}
