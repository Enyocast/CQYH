class MMOGFXPlayer_MsgInfo extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUIMsgInfo            MsgInfo;

function RegisterMessageInfo( MMOUIMsgInfo mc )
{
	MsgInfo = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_MsgInfo);
}

native function PostAdvance(float DeltaTime );

DefaultProperties
{
	MovieInfoStr="UI_MsgInfo.MsgInfo"
	Priority=12
	bAllowFocus=false
	bAllowInput=false
}
