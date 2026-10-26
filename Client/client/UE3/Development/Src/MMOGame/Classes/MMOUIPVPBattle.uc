class MMOUIPVPBattle extends MMOUIBase
	native(UI);

//战场
//var int JoinedBtlID;
//var bool IsBtlWaiting;
var bool IsRandomMode;
var int SelectedBtlID;
var int SelectedBtnIdx;
var int CurBtlListPage;

//var GFxObject BattlePanelMC;
var const int BtlListMax;//1
var GFxObject BtlBtns[2];
var GFxObject BtlQuickSelectBtn;
//单选战场面板
//var GFxObject BtlPageTf;
var GFxObject BtlFreeSelectPanel;

var GFxObject BattleNameTf;
var GFxObject BtlPicImgLoder;
var GFxObject BtlDescTf;
var const int BtlItemMax;//1
var GFxObject BtlAwardItemsIcon[2];
var GFxObject BtlAwardExpTf;
var GFxObject BtlLevelTf;
//随机战场面板
var GFxObject RdmBtlSelectPanel;

var GFxObject RdmBtlDescTf;
var const int RdmBtlItemMax;//1
var GFxObject RdmBtlAwardItemsIcon[2];
var GFxObject RdmBtlAwardExpTf;
var GFxObject RdmBtlLevelTf;
//按钮
var GFxObject BtlSingleJoinBtn;
var GFxObject BtlTeamJoinBtn;
var GFxObject BtlLeaveBtn;

var GFxObject ConfirmMsgBox;
var string ConfirmMsgBoxString;
var float ConfirmMsgBoxCountDownTime;

//
native function ClearUI();
//
native function ResetBattleData();
native function ResetBattleShow();
native function ResetCurBattleShow();
native function CheckJoinButtons();
native function bool IsWaitingBattle();
//
native function UpdateMyTeam();
native function PlayerLevelChange( int lastLv , int newLv );
//
native function UpdateBattleList();
native function UpdateCurBattle( int battleID );
//
native function UpdateTime( float dt );
//
native function UpdateRandomBattleList();
event FlashRandomBattleList( GFxObject Provider )
{
	ActionScriptVoid( "UCFlashRandomBattleList" );
}
event SetBattlePanelMode( bool isRandomSelect )
{
	ActionScriptVoid( "UCSetBattlePanelMode" );
}
//
native function NotifyEnterBattle();
native function NotifyJoinedBattle( int battleID );
native function NotifyLeaveBattle();
//native function TeamJoinBattle();
//native function SingleJoinBattle();
native function JoinSingleBattle();
native function QuickSelectBattle();
native function UpdateRandomBattlePanel();
native function LeaveBattle();
native function AgreeEnterBattle();
native function DiagreeEnterBattle();
//
native function SelectBattle( int idx );
native function MultiSelectBattle( int id, bool isCheck );
native function BattlePageUp();
native function BattlePageDown();
native function bool ChkIsMyLevelForBattle( int battleID );

//===============================================================================================================
//===============================================================================================================
native function PostAdvance ( float DeltaTime );

function ASQuickSelectBattle()
{
	QuickSelectBattle();
}
//
function ASSelectBattle( int idx )
{
	SelectBattle( idx );
}
//随机战场列表勾选
function ASToggleBattle( int id, bool isSelected )
{
	MultiSelectBattle( id, isSelected );
}
//
function ASBattlePageUp()
{
	BattlePageUp();
}
//
function ASBattlePageDown()
{
	BattlePageDown();
}
//
function ASTeamJoinBattle()
{
	//_PVP.TeamJoinBattle();
	JoinSingleBattle();
}
//
function ASSingleJoinBattle()
{
	//_PVP.SingleJoinBattle();
	JoinSingleBattle();
}
//
function ASLeaveBattle()
{
	LeaveBattle();
}
//===============================================================================================================
//===============================================================================================================

//
defaultproperties
{
	//FriendlyName=PVPBattle
	IsDynamicLoad=true
	BtlListMax=1
	BtlItemMax=1
	RdmBtlItemMax=1
}