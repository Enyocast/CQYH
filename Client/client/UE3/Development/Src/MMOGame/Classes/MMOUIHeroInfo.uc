class MMOUIHeroInfo extends MMOUIBase
	native(UI);

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
}

event CallSetHeroInfo(GFxObject HeroData)
{
	ActionScriptVoid("SetHeroInfo");
}

native function int GetMode(int HeroAi);
native function OtherPlayerHpChange( MMOPlayer pl ,int hp );
native function HeroUpdateData();

native function ASHeroUncall();
native function ASHeroBag();
native function FunMode(int Mode);

native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);

DefaultProperties
{
	DefaultVisible=true
	CloseOnEsc=false
}
