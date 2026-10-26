class MMOGFXPlayer_GuideOption extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIGuideOption _guideOptionPanel;

function ASRegisterGuideOption(MMOUIGuideOption mc)
{
	_guideOptionPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_GuideOption);
}

native final function ASSetGuideOption(int optionType);//moved

native final function ASShowGuideOptionTips(GFxObject mc);//moved
native final function ASHideGuideOptionTips();//moved

native function ASOnPanelClose( string PanelName );//moved

native final function ASGuideOptionPanelClose();//moved

DefaultProperties
{
	MovieInfoStr="UI_GuideOption.GuideOption"
	Priority=5
}
