class MMOUILevelUp extends MMOUIBase
	config(MMOGame)
	native(UI);

var GFxObject TipsText;

//var MMOUIGFXPlayer _UIPlayer;

event InitOnce()
{

	super.InitOnce();
	TipsText =  GetObject("tips_lv_text");	
}

event ShowLvUp()
{
	NativeShow(true);
	class'WorldInfo'.static.GetWorldInfo().SetTimer(4.0f, false, 'CloseLevelUpUI');
}

function CloseLevelUpUI()
{
	NativeShow(false);
}

native function PlayerLevelUp(int NewLv);

DefaultProperties
{
	CloseOnEsc=false
}
