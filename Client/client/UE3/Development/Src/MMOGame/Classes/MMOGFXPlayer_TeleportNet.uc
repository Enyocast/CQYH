class MMOGFXPlayer_TeleportNet extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUITeleportNet _TeleportNet;

function RegisterTeleportNet( MMOUITeleportNet mc )
{
	_TeleportNet = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_TeleportNet);
}

// event UnRegister()
// {
// 	super.UnRegister();
// 	RegisterUI( none, class'MMOUIManager'.default.Panel_TeleportNet);
// 	MMOUI::RegisterMoviePlayer(class'MMOUIManager'.default.MoviePlayer_TeleportNet);
// 
// 	//class'MMOUIManager'.static.SetToggleTeleportNetDelegate(none);
// }
//
//function ToggleTeleportNet()
//{
//	if( !_TeleportNet.IsVisible ){
//		_TeleportNet.NativeShow( true );
//	}
//	else{
//		_TeleportNet.NativeShow( false );
//	}
//}
//
function ASUpdateTeleportNetPanel( int regionIdx )
{
	`log( ">>>>>>ASUpdateTeleportNetPanel called<<<<<<<<<"$regionIdx );
	_TeleportNet.UpdateTeleportNetList( EWorldRegion(regionIdx) );
}
native function ASToThisTeleportNode( int destNodeID );


//test
exec function TestTeleportNode( int srcNodeID, int destNodeID )
{
	TestToTeleportNode( srcNodeID, destNodeID );
}
native function TestToTeleportNode( int srcNodeID, int destNodeID );
//end
//
DefaultProperties
{
	MovieInfoStr="UI_TeleportNet.TeleportNet"
	Priority=5
}
