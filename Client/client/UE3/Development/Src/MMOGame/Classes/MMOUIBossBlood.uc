class MMOUIBossBlood extends MMOUIBase
	config(MMOGame)
	native(UI);

native function NPCHpChange( NPC npc , int hp );

event CallSetInitBlood(string title,int nCur,int nMax,int nlevel,int nQuality)
{
	ActionScriptVoid("SetInitBlood");
}

event CallUpdateBlood(int nCur)
{
	ActionScriptVoid("UpdateBlood");
}
native function TickForDistance(float deltaTime);
native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);
native function PostAdvance(float DeltaTime);
DefaultProperties
{
	DefaultVisible=false
	CloseOnEsc=false
}
