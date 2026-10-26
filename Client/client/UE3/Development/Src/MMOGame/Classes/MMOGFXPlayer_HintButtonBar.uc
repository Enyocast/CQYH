class MMOGFXPlayer_HintButtonBar extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIHintButtonBar            _HintButtonBar;

function RegisterHintButtonBar( MMOUIHintButtonBar mc )
{
	_HintButtonBar = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_HintButtonBar);
}

native function ASHintButtonClick( int id );//moved


DefaultProperties
{
	MovieInfoStr="UI_HintButtonBar.HintButtonBar"
	Priority=5
}
