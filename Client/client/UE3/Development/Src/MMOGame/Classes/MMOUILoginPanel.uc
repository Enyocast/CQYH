class MMOUILoginPanel extends MMOUIBase
native(UI)
config(UIVisibleMask);


event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event InitOnce()
{
	super.InitOnce();
}

native function OnFocusGained();
native function OnFocusLost();

native function funCancel();
native function funOk();

native function ShowFreePkDlg();

native final function LoginGame( GFxObject loginData);

native function EnterScene();
native function ChangeScene();
native function EnterLogin();
//---------------------------------------------------------------------------
event CallSetServerList(String strServerList)
{
	ActionScriptVoid("SplitData");
}

event CallPlayLogo()
{
	ActionScriptVoid("PlayLogo");
}

event CallResetFocus()
{
	ActionScriptVoid("ResetFocus");
}

event CallEffectshow()
{
	ActionScriptVoid("Effectshow");
}

event CallUpdateUser(String strUser)
{
	ActionScriptVoid("UpdateUser");
}

event CallShowLoginInputBoxes(bool v)
{
	ActionScriptVoid("ShowLoginInputBoxes");
}

event CallShowLoginSetup(bool v)
{
	ActionScriptVoid("ShowLoginSetup");
}

event CallSetLeftGameTime( string title, int leftSec )
{
	ActionScriptVoid("SetLeftGameTime");
}

function ASLogoEnd()
{        
	ShowFreePkDlg();
}

function ASLoginGame(GFxObject loginData)
{
	LoginGame(loginData);
}

native final function ASOpenSystemSetting();
native final function ASGameRecharge();
native final function ASQuitGame();
native final function ASPlayCGBik();

DefaultProperties
{
	IsDynamicLoad=true
	DefaultVisible=true
}
