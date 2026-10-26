class MMOUIFBAward extends MMOUIBase
	native(UI);

enum EAOG_FBAward
{
	enumAOGFbAwardType1,
	enumAOGFbAwardType2,
	enumAOGFbAwardType3
};

var GFxObject MyName_mc;
var GFxObject MyPortrait_mc;
var GFxObject MyScore_mc;

var const int MAX_FB_Award;//3
var int bAwardAnimPlayed[3];
var GFxObject MyFBAward[3];
var GFxObject MyBtnAward[3];
var GFxObject MyAwardHintTf[3];

var GFxObject MemberInfoMc;
var GFxObject MemFBAwards[4];

//是否可以免费抽取第三个奖品（VIP玩家）
var bool bCanFreeGet3;
//是否可以免费抽取第二个奖品（评分S或以上）
var bool bCanFreeGet2;
//此副本中是否未抽过奖
var bool bPlayed;
//
var array<int> MyClickAwardIdx;
//更新
native function UpdateMemberAward();
native function UpdateMyAward();
//
native function InitFBAwardMode();
native function ResetUI();
//开始抽奖（抽奖？）
native function OpenToPlay( int iTime );
//
native function ResetData();
//
event CallASStartPlayCountDown( int CloseTime)
{
	ActionScriptVoid( "StartPlayCountDown" );
}
//抽奖按钮被点击
native function ClickAward( int iIdx );
//向服务器索取奖品
native function GetAward( int iIdx );
//时间到，打开所有可以打开的奖励
native function TimeUpToShowAll();

//===============================================================================================================
//===============================================================================================================
native function ClickGetFBAward( int iIdx );
//Back to FBSummary from FBAward
native function FBAwardPlayTimeOver();
//
native function GetFBAward( int iIdx);

//===============================================================================================================
//===============================================================================================================

//
DefaultProperties
{
	//FriendlyName=FBAward
	MAX_FB_Award=3
	IsDynamicLoad=true
	CloseOnEsc=false
}