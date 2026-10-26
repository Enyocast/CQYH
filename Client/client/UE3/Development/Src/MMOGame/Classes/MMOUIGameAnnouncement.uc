class MMOUIGameAnnouncement extends MMOUIBase
	native(UI);

//
event CallASSetAnnouncemment( string content )
{
	ActionScriptVoid("SetAnnouncemmentContent");
}

defaultproperties
{
	DefaultVisible = false
}