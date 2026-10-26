class MMOGFXPlayer_MatineeSubtitle extends MMOGFXPlayer
	native(UI)
	config(MMOGame);


event CallUCUpdateSubtitle(string htmlStr)
{
	ActionScriptVoid("root.UCUpdateSubtitle");
}

event CallUCShow(bool show, int scrW, int scrH)
{
	ActionScriptVoid("root.UCShow");
}

DefaultProperties
{
	MovieInfoStr="UI_MatineeSubtitle.MatineeSubtitle"
	bAllowFocus=false
	Priority=8
}
