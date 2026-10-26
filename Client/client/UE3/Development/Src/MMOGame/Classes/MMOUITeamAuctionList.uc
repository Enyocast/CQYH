class MMOUITeamAuctionList extends MMOUIBase
	native(UI)
	config(UIVisibleMask);



event CallUpdateData( GFxObject dataArray )
{
	ActionScriptVoid("updateData");
}
//----------------------------moved----------------------------
native function ASTeamAuctionGiveUpAll();

defaultproperties
{
	
}