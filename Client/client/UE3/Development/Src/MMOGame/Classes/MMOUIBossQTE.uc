class MMOUIBossQTE extends MMOUIBase
	native(UI);



event CallUpdateQte(int CounterNum , int CounterDownNum )
{
	ActionScriptVoid("UpdateQte");
}

//===============================================================================================================
//===============================================================================================================
native function AsCloseBossQTEPanel();
//{
//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_HintCombat_BossQTE, FALSE, "");
//}


function UpdateBossQTE(int CounterNum , int CounterDownNum)
{
	CallUpdateQte( CounterNum , CounterDownNum);
}

native function bool SkipCaptureInputKey( string key, EInputEvent eIE, string strHoverControllerName, Vector2D ClickPosInMovieSpace);

//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=BossQTE
	IsDynamicLoad=true
	DefaultVisible=true
}
