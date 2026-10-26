class MMOGFXPlayer_JourneyView extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIJourneyViewPanel _JourneyViewPanel;
var MMOUIJourneyCompletePanel _JourneyCompletePanel;

function RegisterJourneyViewPanel(MMOUIJourneyViewPanel mc)
{
	_JourneyViewPanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_JourneyView);
}

function RegisterJourneyCompletePanel(MMOUIJourneyCompletePanel mc)
{
	_JourneyCompletePanel = mc;
	RegisterUI(mc, class'MMOUIManager'.default.Panel_JourneyComplete);
}

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

native function ASUpdateJourneyInfo(int journeyId);
native function ASGetCompleteAwards(int journeyId);
native function ASJourneyComplete();

DefaultProperties
{
	MovieInfoStr="UI_JourneyView.JourneyView"
	Priority=7
}
