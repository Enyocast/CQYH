class MMOGFXPlayer_DynamicUI extends MMOGFXPlayer
	dependson(MMOUIBase, TypeDefine)
	native(UI)
	config(MMOGame);

//var MMOUIBuffPanel                  _Buff;
var MMOUIProgressBarWidget          _ProgressBar;
//var MMOUIFBSummaryProgressBar       _FBSummaryProgressBar;
var MMOUIProgressBarWidget          _FBSummaryProgressBar;
var MMOUIProgressBarStrengthWidget  _StrengthBar;
var MMOUIProgressBarQTEWidget       _QTEBar;
var MMOUIHintLevelUpWidget          _LevelUp;
var MMOUIHintSceneWidget            _Scene;
var MMOUITips                       _Tips;
var MMOUITransducerInfo             _TransducerInfo;
var MMOUIBattleState	            _BattleState;
//var MMOUICombatMsg	                _CombatMsg;
var MMOUIWeatherChangePanel         _WeatherChange;
var MMOUIBossBlood					_BossBlood;
var MMOUINewEventPanel              _NewEvent;
var MMOUIUnlockAOGString            _UnlockAOGString;

function RegisterBattleState( MMOUIBattleState mc )
{
	_BattleState = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_BattleState);
}

function RegisterRenownUnlockAOG( MMOUIUnlockAOGString mc )
{
	_UnlockAOGString = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_UnlockAOGString);
}




//function RegisterBuff( MMOUIBuffPanel mc )
//{
//	_Buff = mc;
//	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_Buff);
//}

function RegisterProgressBar( MMOUIProgressBarWidget mc )
{
	_ProgressBar = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_ProgressBar);
}

function RegisterFBSummaryProgressBar( MMOUIProgressBarWidget mc )
{
	_FBSummaryProgressBar = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_FBSummaryProgressBar );
}

function RegisterStrengthBar( MMOUIProgressBarStrengthWidget mc )
{
	_StrengthBar = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_StrengthBar);
}

function RegisterQTEBar( MMOUIProgressBarQTEWidget mc )
{
	_QTEBar = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_QTEBar);
}

function RegisterLevelUp( MMOUIHintLevelUpWidget mc )
{
	_LevelUp = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_LevelUp);
}

function RegisterScene( MMOUIHintSceneWidget mc )
{
	_Scene = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_Scene);
}

function RegisterTransducerInfo( MMOUITransducerInfo mc )
{
	_TransducerInfo = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_Transducer);
}

function registerTips( MMOUITips mc)
{
	
	_Tips = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_Tips);
}

function RegisterWeatherChange( MMOUIWeatherChangePanel mc )
{
	_WeatherChange = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_WeatherChange);
}

function RegisterNewEvent( MMOUINewEventPanel mc )
{
	_NewEvent = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_NewEvent);
}

function RegisterBossBloodBar( MMOUIBossBlood mc )
{
	_BossBlood = mc;
	RegisterUI( mc, class'MMOUIManager'.default.Panel_DynamicUI_BossBlood);
}

native function OnPostRender( Canvas cvs, float fDelta);

//native function ASClickQTE();

native function PostAdvance(float DeltaTime);
native function OnHUDLoaded();
//
//function ProgressBarTimeUpCallback()
//{
//	`log("ProgressBar TimeUp Callback called"$_ProgressBar.DelegateTimeUp);
//	if( _ProgressBar.DelegateTimeUp == none ){
//		return;
//	}
//	_ProgressBar.DelegateTimeUp();
//	_ProgressBar.DelegateTimeUp = none;
//}

//function FBSummaryProgressBarTimeUpCallback()
//{
//	`log("FBSummaryProgressBar TimeUp Callback called"$_FBSummaryProgressBar.DelegateTimeUp);
//	if( _FBSummaryProgressBar.DelegateTimeUp == none ){
//		return;
//	}
//	_FBSummaryProgressBar.DelegateTimeUp();
//	_FBSummaryProgressBar.DelegateTimeUp = none;
//}

//native function ShowProgressBar( int countDownTime,string strTitle, int type );
//native function CloseProgressBar(int closeType);

//event ShowProgressBar( int countDownTime,string strTitle, int type )
//{
//	NativeTestShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_ProgressBar,true);
//	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_ProgressBar,true, "");
//	_ProgressBar.Open(countDownTime,strTitle,type);
//}
//event CloseProgressBar(int closeType)
//{
//	_ProgressBar.Close(closeType);
//	NativeTestShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_ProgressBar,false);
//	//class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_ProgressBar,false, "");
//}

//event ShowProgressBarStrength(int time, int max)
//{
//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_StrengthBar,true, "");
//	_StrengthBar.Open(time, max);
//}
//event CloseProgressBarStrength(int closeType)
//{
//	_StrengthBar.Close(closeType);
//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_StrengthBar,false, "");
//}

//event ShowProgressBarQTE(int time,string keyName,string imgName,int nActorID,int nAbilityID)
//{
//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_QTEBar,true, "");
//	_QTEBar.Open( time, keyName, imgName,nActorID,nAbilityID);
//}
//event CloseProgressBarQTE(int closeType)
//{
//	_QTEBar.Close(closeType);
//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_QTEBar,false, "");

//}

//event ShowUnlockAOGString(string content)
//{
//	_UnlockAOGString.CallUCSetRenownUnlockAOGString(content);
//}

//event HideUnlockAOGString()
//{
//	_UnlockAOGString.CallUCPlayHideAnimation();
//}


//event AddBuffPanel(int buffSlotID,string buffIcon,int buffMaxTime,int buffCurTime, int stackCount, int ownerID)
//{
//	_Buff.Open( buffSlotID, buffIcon,  buffMaxTime, buffCurTime,stackCount,ownerID);
//}
//event DeleteBuffPanel(int buffSlotID)
//{
//	_Buff.Close( buffSlotID );
//}


//final native function ShowHintSceneWidget();
//final native function CloseHintSceneWidget();


//event ShowHintLevelUpWidget(string levelUp,INT strengthAdd,INT agilityAdd,	INT intellectAdd,	INT staminaAdd, 	INT spiritAdd,	 INT maxHpAdd )
//{
//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_LevelUp,true, "");
//	_LevelUp.Open(levelUp, strengthAdd, agilityAdd,	intellectAdd,	staminaAdd, spiritAdd,	 maxHpAdd);
//}

//event CloseHintLevelUpWidget()
//{
//	_LevelUp.Close();
//	class'MMOUIManager'.static.ShowPanelEx(class'MMOUIManager'.default.Panel_DynamicUI_LevelUp,false, "");
//}

//event AddSkillLearnedMsg( int msgId , ESkillMsgType type)
//{
//	_SkillLearned.AddSkillLearnedMsg( msgId, type );
//}

//native function ASScreenPopUpBoxMsgPlayEnd();

//native function ASWeatherChangePlayEnd();

//native function ASRenownUnlockAOGShowEnd();

function UpdateTransducerInfo(bool bShow ,int inProgress)
{
	_TransducerInfo.UpdateInfo(bShow,inProgress);
}
 
event bool SkipCaptureInputKey(const string key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace)
{
	//if(_Buff.SkipCaptureInputKey( key,  eIE,  strHoverControllerName, ClickPosInMovieSpace)==0)
	//{
	//	return false;
	//}
	//if(  strHoverControllerName == "hintScene_mc"  || strHoverControllerName == "tF_hintScene" || strHoverControllerName == "ScreenPopUpBoxMsgAOGMc" )
	//{
	//	return false;
	//}
	
	//if(!_BossBlood.SkipCaptureInputKey( key,  eIE,  strHoverControllerName, ClickPosInMovieSpace))
	//	return false;

	return super.SkipCaptureInputKey(key, eIE, strHoverControllerName, ClickPosInMovieSpace);
}

DefaultProperties
{
	//MovieInfoStr="UI_DeathWidget.DeathWidget"
	MovieInfoStr="UI_DynamicUIWidget.DynamicUIWidget"
	IsLockedDynamicLoad=true
	bCloseOnLevelChange=FALSE
	bAllowFocus=FALSE
	Priority=3
}
