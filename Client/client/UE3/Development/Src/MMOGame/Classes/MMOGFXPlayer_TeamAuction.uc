class MMOGFXPlayer_TeamAuction extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUITeamAuctionPanel TeamAuction;
var MMOUITeamAuctionList TeamAuctionList;

function RegisterTeamAuctionPanel( MMOUITeamAuctionPanel mc )
{

	TeamAuction = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_TeamAuction );
}

function RegisterTeamAuctionList( MMOUITeamAuctionList mc )
{
	TeamAuctionList = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_TeamAuctionList );
}

native function ASTeamAuctionBid( int bidMoney );
native function ASTeamAuctionGiveup( );
native function ASTeamAuctionClickItemList();
native function ASTeamAuctionClickBidMoneyUp( int bidMoney );
native function ASTeamAuctionClickBidMoneyDown( int bidMoney );
native function ASTeamAuctionGiveUpAll();//moved teamAuctionList
native function ASTeamAuctionListGiveUp( int index );

DefaultProperties
{
	MovieInfoStr="UI_TeamAuction.TeamAuction"
	Priority=5
}
