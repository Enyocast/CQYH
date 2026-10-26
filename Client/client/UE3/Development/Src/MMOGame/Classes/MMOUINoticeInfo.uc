class MMOUINoticeInfo extends MMOUIBase
	native(UI)
	;

event CallAddMarqueeNoticeInfo( string notice , int movieTime , int repeatTimes , string noticeColor )
{
	ActionScriptVoid("AddMarqueeNoticeInfo");
}

event CallAddRollingNoticeInfo( string notice , string noticeColor )
{
	ActionScriptVoid("AddRollingNoticeInfo");
}

native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

DefaultProperties
{
	DefaultVisible=true
	CloseOnEsc=false
	//bAllowFocus=false
	//bAllowInput=false
}
