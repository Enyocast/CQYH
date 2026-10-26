class MMOUICenterStaticNotice extends MMOUIBase
	native(UI);

//
event CallASSetNoticeContents( int type, string content )
{
	ActionScriptVoid("UCSetNoticeContents");
}

native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible = false
	CloseOnEsc=false
}