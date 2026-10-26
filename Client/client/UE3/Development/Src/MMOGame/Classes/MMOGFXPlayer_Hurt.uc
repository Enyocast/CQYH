class MMOGFXPlayer_Hurt extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIHurt _hurtPanel;
var GFxObject ConfirmMsgBox;//moved

function ASRegisterHurtPopUp(MMOUIHurt mc)//moved
{
	_hurtPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_Hurt);
}

native final function ASViewPage_ClickHurtClear();//moved
native function PostAdvance(float DeltaTime);//moved

native final function ASShowHurtTips(GFxObject mc);//moved
native final function ASHideHurtTips();//moved

native final function OnClearHurt();//moved

native final function ASCloseHurtTips();//moved
DefaultProperties
{
	MovieInfoStr="UI_Hurt.Hurt"
	Priority=5
}
