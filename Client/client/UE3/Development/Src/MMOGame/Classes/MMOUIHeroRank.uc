class MMOUIHeroRank extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

var float currentTime;
var float currentRefreshTime;
var bool refresh;

native function NativeInitLoad();
native function NativeInitOnce();

native function ASPrevHeroRankPageClick();
native function ASNextHeroRankPageClick();
native function BeforeViewUpdate( float DeltaTime );

event CallUCUpdateHeroRankData(GFxObject Provider)
{
	ActionScriptVoid("UCUpdateHeroRankData");
}

event CallUCUpdateMyHeroRank(string rank)
{
	ActionScriptVoid("UCUpdateMyHeroRank");
}

event CallUpdateHeroRankPage(GFxObject page)
{
	ActionScriptVoid("UpdateHeroRankPage");
}

event CallUpdateMyRank(string rank, int currentIndex,int lastIndex)
{
	ActionScriptVoid("UCUpdateMyRank");
}


DefaultProperties
{
	IsDynamicLoad=true
}
