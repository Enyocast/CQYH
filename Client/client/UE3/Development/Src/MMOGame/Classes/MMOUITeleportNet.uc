class MMOUITeleportNet extends MMOUIBase
	dependson(TeleportNetNode)
	native(UI);

var EWorldRegion _CurTab;
var GFxObject _TeleportReginTab[4];
var GFxObject _TeleportNodesListMc;
//
//event OnShow(bool show)
//{
//	super.OnShow(show);
//	if( show ){
//		UpdateTeleportNetList( _CurTab );
//	}
//	else{

//	}
//}
//
event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	//
	//InitMc();
}

native function Open( EWorldRegion regionID, int nodeID );
event UpdateTab( EWorldRegion tabIdx )
{
	ActionScriptVoid( "UCUpdateTab" );
}
native function UpdateTeleportNetList( EWorldRegion regionID );
event FlashTeleportNetList( GFxObject Provider )
{
	ActionScriptVoid( "UCUpdateTeleportNodesList" );
}

//native function ToThisTeleportNode( int destNodeID );

//===============================================================================================================
//===============================================================================================================
//var MMOUITeleportNet _TeleportNet;

//function RegisterTeleportNet( MMOUITeleportNet mc )
//{
//	_TeleportNet = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_TeleportNet);
//}

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
	UpdateTeleportNetList( EWorldRegion(regionIdx) );
}
native function ASToThisTeleportNode( int destNodeID );

//test
exec function TestTeleportNode( int srcNodeID, int destNodeID )
{
	TestToTeleportNode( srcNodeID, destNodeID );
}
native function TestToTeleportNode( int srcNodeID, int destNodeID );
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=TeleportNet
	IsDynamicLoad=true
}
