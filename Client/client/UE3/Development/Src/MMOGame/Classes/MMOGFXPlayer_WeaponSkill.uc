class MMOGFXPlayer_WeaponSkill extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIWeaponSkill _WeaponSkillPanel;
//
function RegisterWeaponSkill( MMOUIWeaponSkill mc )
{
	_WeaponSkillPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_WeaponSkill);
}
//
final native function ASClickToTryGetWeaponSkill();

final native function ASShowTips_WeaponSkill( GFxObject mc );
final native function ASHideTips_WeaponSkill();

final native function ASShowTips_ConsumeItem( GFxObject mc );
final native function ASHideTips_ConsumeItem();

final native function ASOnClickAutoChangeSkillChkBtn();

DefaultProperties
{
	MovieInfoStr="UI_WeaponSkill.WeaponSkill"
	Priority=5
}
