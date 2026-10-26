class MMOUIDeathMessage extends MMOUIBase
	native(UI);


event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

native function NativeCallShowWaitingRevive(int CountDownTime);

event CallShowWaitingRevive(int CountDownTime)
{
	ActionScriptVoid("ShowWaitingRevive");
}


event CallUpdateData(GFxObject data)
{
	ActionScriptVoid("updateData");
}

native function Refresh();
native function NativeOnShow(bool v);

//---------------moved-----------------------
native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);
native function ASRelife(int inReviveType,int itemID);

DefaultProperties
{
	IsDynamicLoad=true
	CloseOnEsc=false
}
