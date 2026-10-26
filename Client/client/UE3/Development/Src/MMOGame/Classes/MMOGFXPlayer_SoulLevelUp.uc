class MMOGFXPlayer_SoulLevelUp extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUISoulLevelUp _SoulLevelUpPanel;
//
function RegisterSoulLevelUp( MMOUISoulLevelUp mc )
{
	_SoulLevelUpPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_SoulLevelUp);
}


//soul level up
final native function ASConfirmSoulLevelUp();
final native function ASResetSoulLevelUp();

DefaultProperties
{
	MovieInfoStr="UI_SoulLevelUp.SoulLevelUp"
	Priority=5
}
