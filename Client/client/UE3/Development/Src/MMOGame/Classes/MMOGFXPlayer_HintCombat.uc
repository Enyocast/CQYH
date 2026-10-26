class MMOGFXPlayer_HintCombat extends MMOGFXPlayer
	native(UI)
	config(MMOGame);


var MMOUIBossQTE            BossQTE;

function RegisterBossQTE( MMOUIBossQTE mc )
{        
	BossQTE = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_HintCombat_BossQTE);
}

native function AsCloseBossQTEPanel();
//{
//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_HintCombat_BossQTE, FALSE, "");
//}


function UpdateBossQTE(int CounterNum , int CounterDownNum)
{
	if(BossQTE!=none){
		BossQTE.CallUpdateQte( CounterNum , CounterDownNum);
	}
}

event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	return false;
}

DefaultProperties
{
	MovieInfoStr="UI_HintCombat.HintCombat"
	//TurnButton=TBS_None
}
