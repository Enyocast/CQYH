class MMOUIUnlockAOGString extends MMOUIBase
	config(MMOGame)
	native(UI);
	
event InitOnce()
{
	super.InitOnce();

	//class'MMOUIManager'.static.SetShowEnterBattleDelegate(ShowEnterBattle);
}

//native function ShowEnterBattle( bool Enter );


event CallUCSetRenownUnlockAOGString(string content)
{
	ActionScriptVoid("UCSetRenownUnlockAOGString");
}

event CallUCPlayHideAnimation()
{
	ActionScriptVoid("UCPlayHideAnimation");
}

native function ASRenownUnlockAOGShowEnd();

DefaultProperties
{
	DefaultVisible=true
	CloseOnEsc=false
}
