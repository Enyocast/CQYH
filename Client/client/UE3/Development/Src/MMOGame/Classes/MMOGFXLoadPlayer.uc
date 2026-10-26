class MMOGFXLoadPlayer extends GFxMoviePlayer
	native(UI);

//var MMOUIHudLevel BgLoader;
var MMOUILoadingBar loadingBar;

function RegisterLoadingProgressBar(MMOUILoadingBar mc)
{
	loadingBar = mc;
}

native function ASPreEnterCompleted();
native function ASPreLeaveCompleted();

native function ASCallBackSetAlpha(float alphaValue);

//function ASPreEnterCompleted()
//{
//	loadingBar.PreEnterCompleted();
//}
//function ASPreLeaveCompleted()
//{
//	loadingBar.PreLeaveCompleted();
//}

event PreEnter()
{
	loadingBar.CallSet_PreEnter();
}

event PreLeave()
{
	loadingBar.CallSet_PreLeave();
}

event AftEnter()
{
	loadingBar.CallSet_AftEnter();
}

event SetVisible( bool show)
{
	GetVariableObject("root").SetVisible(show);
}

function Init(optional LocalPlayer player)
{
//	local int j;
	local GFxObject TempWidget;
	
	super.Init(player);

	//CreateNPCDialogManager();

	Start();
    Advance(0); 

	TempWidget = GetVariableObject("root");
	if ( TempWidget != None ) 
	{ 

		//`log("************_root");
		//TempWidget.SetBool("visible", false);
	}

	//if( BgLoader == none )
	//{
	//	//PawnArchetypeToUse = Pawn(DynamicLoadObject(PlayerPawnArchetypeName,class'MMOPlayer'));
	//	BgLoader = new class'MMOUIHudLevel';
	//}
	SetVisible(false);
}

native final function NativeOnClose();

native function OnEnter();
native function OnLeave();
native function OnUpdate();
native function PostAdvance(float DeltaTime);

event OnClose()
{
	NativeOnClose();
}

// added by JimZhang@snda
event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	return false;
}

DefaultProperties
{
	MovieInfoStr="MMO_UI.GameLoading"
	bCloseOnLevelChange=false
	bEnableGammaCorrection=false

	SoundThemes(0)=(ThemeName=default, Theme=UISoundTheme'MMO_UISoundTheme.Default')

	
	bAllowInput=false
	bAllowFocus=false
	bCaptureInput=false
	Priority=50
}
