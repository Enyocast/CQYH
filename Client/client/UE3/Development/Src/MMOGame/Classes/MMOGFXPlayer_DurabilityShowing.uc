class MMOGFXPlayer_DurabilityShowing extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIDurabilityShowing _DurabilityShowing;

//native function PostAdvance(float DeltaTime);

function RegisterDurabilityShowing( MMOUIDurabilityShowing mc )
{
	_DurabilityShowing = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DurabilityShowing);
}

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	return false;
}

native function ASHintDurabilityDetail( GFxObject mc );
native function ASHideDurabilityDetail();

//End
DefaultProperties
{
	MovieInfoStr="UI_Durability.Durability"
	bCloseOnLevelChange=FALSE
	bAllowFocus=FALSE
	Priority=5
}
