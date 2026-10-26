class MMOGFXPlayer_NoticeInfo extends MMOGFXPlayer
	native(UI)
	config(MMOGame);

var MMOUINoticeInfo            NoticeInfo;

function RegisterNoticeInfo( MMOUINoticeInfo mc )
{
	NoticeInfo = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_NoticeInfo);
}

//native function PostAdvance(float DeltaTime );

DefaultProperties
{
	MovieInfoStr="UI_NoticeInfo.NoticeInfo"
	Priority=12
	bAllowFocus=false
	bAllowInput=false
}
