class MMOGFXPlayer_Arena extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIArenaEntrance _ArenaEntrance;
var MMOUIArenaState _ArenaState;

function RegisterArenaEntrance( MMOUIArenaEntrance mc )
{
	_ArenaEntrance = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Arena_ArenaEntrance);
}

function RegisterArenaState( MMOUIArenaState mc )
{
	_ArenaState = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Arena_ArenaState);
}

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	//`log( "strHoverControllerName : "$strHoverControllerName );
	if( strHoverControllerName == "panelMask" ){
		return false;
	}

	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

native function PostAdvance( float dt );

native function ASOnActionButtonClick();
native function ASToggleShowBonusPanel( bool isToShow );
native function ASOnFightingButtonClick();

DefaultProperties
{
	MovieInfoStr="UI_PVP_Bonus.UI_PVP_Bonus"
	Priority=4
}
