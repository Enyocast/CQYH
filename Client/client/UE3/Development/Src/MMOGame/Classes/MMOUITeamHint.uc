class MMOUITeamHint extends MMOUIBase
	native(UI);


event InitOnce()
{
	super.InitOnce();
}

event CallSetData( GFxObject data )
{
	ActionScriptVoid("SetData");
}

event CallHideWidget( bool hide )
{
	ActionScriptVoid("HideWidget");
}

native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

event CallShowByExpand(bool v)
{
	ActionScriptVoid("ShowByExpand");
}

native function ASTeamHintLeave();
native function ASTeamExpand(bool v);

DefaultProperties
{
	
	DefaultVisible=true
	CloseOnEsc=false
}
