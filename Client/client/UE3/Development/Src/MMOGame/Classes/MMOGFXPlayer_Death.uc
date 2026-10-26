class MMOGFXPlayer_Death extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIDeathMessage     _Death;

function RegisterDeath( MMOUIDeathMessage mc )
{
	_Death = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Death);
}

function ASRelife(int inReviveType,int itemID)//moved
{
	MMOPlayerController( GetPC()).RequestRevive( inReviveType, itemID);
}

native function CallShowWaitingRevive(int CountDownTime);//moved

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	if(strHoverControllerName=="btn_Revive_Coin" || strHoverControllerName=="btn_Revive_Around" || strHoverControllerName=="btn_Revive_Free" || strHoverControllerName=="ReviveCtrl_mc")
	{
		`log("----------------strHoverControllerName==null");
		return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
	}
	else
	{
		return false;
	}
}

DefaultProperties
{
	MovieInfoStr="UI_DeathWidget.DeathWidget"
	Priority=10
}
