class MMOGFXPlayer_Helper extends MMOGFXPlayer
	native(UI);

var MMOUIHelperPanel _HelperPanel;
var MMOUIHelperPlayerPanel _HelperPlayerPanel;

native function PostAdvance( float dt );

// AS->UC
function ASRegisterHelperPanel(MMOUIHelperPanel mc)
{ 
	_HelperPanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Helper);
}

function ASRegisterHelperPlayerPanel(MMOUIHelperPlayerPanel mc)
{
	_HelperPlayerPanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_HelperPlayer);
}

native final function ASUpdateHelperDetail(int baseClass, int subClass);
native final function ASPlayHelperSound();
native final function ASPauseHelperSound();

DefaultProperties
{
	MovieInfoStr="UI_Helper.Helper"
	Priority = 5
}
