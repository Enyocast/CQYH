class MMOGFXPlayer_KillRecord extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIKillCountPanel       _killCountPanel;
var MMOUIKillRecordPanel      _killRecordPanel;



function RegisterKillRecordPanel(MMOUIKillRecordPanel mc)
{
	_killRecordPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_KillRecordPanel);
}


function RegisterKillCountPanel(MMOUIKillCountPanel mc)
{
	_killCountPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_KillCountPanel);
}
event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	return true;	
}
final native function ASClosedKillRecordPanel();
final native function ASClosedKillCountPanel();

DefaultProperties
{
	MovieInfoStr="UI_KillRecord.KillRecord"
	IsLockedDynamicLoad=true
	Priority=5
}
