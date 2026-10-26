class MMOUIBattleState extends MMOUIBase
	config(MMOGame)
	native(UI);
	
var GFxObject _TextField;

event InitOnce()
{
	super.InitOnce();

	`log("class'MMOUIManager'.static.SetShowEnterBattleDelegate(ShowEnterBattle)");
	_TextField = GetObject("textField");
	class'MMOUIManager'.static.SetShowEnterBattleDelegate(ShowEnterBattle);
}

native function ShowEnterBattle( bool Enter );
//{
	

//}

DefaultProperties
{
	DefaultVisible=true
	CloseOnEsc=false
}
