class MMOGFXPlayer_FightingScreenHint extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIFightingScreenHint _FightingScreenHint;
var MMOUIScreenPopUpBoxMsg	_ScreenPopUpBoxMsg;

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	return false;
}

//
function RegisterFightingScreenHint( MMOUIFightingScreenHint mc )
{
	_FightingScreenHint = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_FightingScreenHint);
}


function RegisterScreenPopUpBoxMsg( MMOUIScreenPopUpBoxMsg mc )
{
	_ScreenPopUpBoxMsg = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_FightingScreenHint_ScreenPopUpBoxMsg);
}

native function ASBeforeFightTenSecCountDownEnd();
native function ASScreenPopUpBoxMsgPlayEnd();

native function ASOnExitCountDownTimeOver();

DefaultProperties
{
	MovieInfoStr="UI_FightingScreenHint.FightingScreenHint"
	bCloseOnLevelChange=FALSE
	bAllowFocus=FALSE
	Priority=6
}
