class MMOGFXPlayer_JourneyTrace extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIJourneyTracePanel _JourneyTracePanel;

function ASRegisterJourneyTracePanel(MMOUIJourneyTracePanel mc)
{
	_JourneyTracePanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_Journey);
}


event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	if (GetlockMouseCursorForUI() == false && (key == "LeftMouseButton" || key == "RightMouseButton"))
	{
		if (strHoverControllerName == "list_bg_mc" )
		{
			return false;
		}
	}

	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

native function ASGotoChapter(int journeyId);
native function ASUpdateNPCTips(int index);
native function ASShowAwardsPanel(int journeyId);
native function ASSetCurItemState(int journeyType, bool expand);

DefaultProperties
{
	MovieInfoStr="UI_Journey.Journey"
	Priority=1
}
