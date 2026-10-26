class MMOUIHurt extends MMOUIBase
	native(UI);

var GFxObject ConfirmMsgBox;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event UCSetHurtViewPage_AllData(string allHurt,float hurtTime)
{
	ActionScriptVoid( "UCSetHurtViewPage_AllData" );
}

//function ASRegisterHurtPopUp(MMOUIHurt mc)
//{
	//_hurtPanel = mc;
	//RegisterUI( mc, class'MMOUIManager'.default.Panel_Hurt);
//}

native final function ASViewPage_ClickHurtClear();

native final function ASShowHurtTips(GFxObject mc);
native final function ASHideHurtTips();

native final function OnClearHurt();

native final function ASCloseHurtTips();

DefaultProperties
{
	IsDynamicLoad=true
	CloseOnEsc=false;
	FriendlyName=Hurt
}
