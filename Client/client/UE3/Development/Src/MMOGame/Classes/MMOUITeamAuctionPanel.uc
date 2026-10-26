class MMOUITeamAuctionPanel extends MMOUIBase
	native(UI)
	config(UIVisibleMask);

event CallUpdatePanel( GFxObject data )
{
	ActionScriptVoid("updateData");
}

event CallUpdatePanelFast( GFxObject data )
{
	ActionScriptVoid("updateDataFast");
}

event CallUpdateItemNum( string itemNum )
{
	ActionScriptVoid("updateItemNum");
}

event CallSetInputPrice( int price )
{
	ActionScriptVoid("SetInputPrice");
}

//-----------------moved-----------------------
native function ASTeamAuctionListGiveUp( int index );
native function ASTeamAuctionBid( int bidMoney );
native function ASTeamAuctionGiveup( );
native function ASTeamAuctionClickItemList();
native function ASTeamAuctionClickBidMoneyUp( int bidMoney );
native function ASTeamAuctionClickBidMoneyDown( int bidMoney );

defaultproperties
{
	CloseOnEsc=false
}