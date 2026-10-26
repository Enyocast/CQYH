class MMOGFXPlayer_TradeP2P extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUITradeP2P _TradeP2P;

native function PostAdvance(float DeltaTime);

function RegisterTradeP2P( MMOUITradeP2P mc )
{
	_TradeP2P = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_TradeP2P );

	//_TradeP2P.Show( false );
	//self.OnPostAdvance = _TradeP2P.TickForTestInteractNPCDistance;
}

// event UnRegister()
// {
// 	super.UnRegister();
// 	RegisterUI( none, class'MMOUIManager'.default.Panel_TradeP2P);
// 	MMOUI::RegisterMoviePlayer(class'MMOUIManager'.default.MoviePlayer_TradeP2P);
// 
// 	class'MMOUIManager'.static.SetApplyDoTradeDelegate( none );
// }

//
function ASInputP2PTradeMoney()
{
	_TradeP2P.InputP2PTradeMoney();
}
//
function ASConfirmP2PTrade()
{
	_TradeP2P.ConfirmP2PTrade();
}
//
function ASCancelP2PTrade()
{
	_TradeP2P.NativeShow( false );
}
//
function ASLockP2PTrade()
{
	_TradeP2P.LockP2PTrade();
}
//
DefaultProperties
{
	MovieInfoStr="UI_TradeP2P.TradeP2P"
	Priority=5
}
