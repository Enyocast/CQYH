class MMOGFXPlayer_Soul extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUISoulEmbed _SoulEmbedPanel;

//
function RegisterSoulEmbed( MMOUISoulEmbed mc )
{
	_SoulEmbedPanel = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_SoulEmbed);
}

//soul embed
final native function ASOnEmbedPanelTabBtnClick( int tabIdx );

final native function ASConfirmSoulEmbed();
final native function ASResetSoulEmbed();
//soul unembed
final native function ASConfirmUnEmbed();
final native function ASCancelUnEmbed();
final native function ASSelectUnEmbedSoul( int idx );
//soul level up
final native function ASConfirmSoulLevelUp();
final native function ASResetSoulLevelUp();

DefaultProperties
{
	MovieInfoStr="UI_Soul.Soul"
	Priority=5
}
