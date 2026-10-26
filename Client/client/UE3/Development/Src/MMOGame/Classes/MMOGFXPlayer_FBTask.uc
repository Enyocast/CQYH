class MMOGFXPlayer_FBTask extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIFBTask _FBTask;

function RegisterFBTask( MMOUIFBTask mc )
{
	_FBTask = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_FBTask);
}

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	return false;
}

//
DefaultProperties
{
	MovieInfoStr="UI_FBTask.FBTask"
	bAllowFocus=FALSE
	Priority=3
}
