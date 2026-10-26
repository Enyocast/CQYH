class MMOUIMutiLineMsgBox extends MMOUIBase
	native(UI)
	dependson(TypeDefine)
	config(UIVisibleMask);

var int PanelHalfWidth;
var int PanelHalfHeight;

event CallASSetPopUpBox( GFxObject data )
{
	ActionScriptVoid( "UCSetUpgradeResultData" );
}

DefaultProperties
{
	//FriendlyName=MutiLineMsgBox
	IsDynamicLoad=true
	//CloseOnEsc=false
}
