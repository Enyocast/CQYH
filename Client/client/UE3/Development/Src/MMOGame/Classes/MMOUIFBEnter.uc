class MMOUIFBEnter extends MMOUIBase
	native(UI);

enum EFBDifficultyType
{
	EFBDTyp_Invalid,
	EFBDTyp_OnePerson,
	EFBDTyp_FivePerson
};

var const int svrTeleportIDMask;
var int TelepOrigID;
var string CurMapName;
var ExportMap FBToMapInfo;
var int CurFBBranchIdx;
var int FBBranchTelepLinkID[5];
//var string strFBDiff[4];
var int CurDiff;
var int CurMaxDiff;

var Vector CurEnterTeleportPos;
var int Distance2ForVisible;
//
const FB_SELECT_DIFF_CNT = 4;
var GFxObject FBDiffBtn[FB_SELECT_DIFF_CNT];
var GFxObject FBDiffMc[FB_SELECT_DIFF_CNT];
var GFxObject FBDiffHintBtn[FB_SELECT_DIFF_CNT];
//
//var GFxObject btn_FBBranch[5];
//
var GFxObject FBBackgroundMc;
var GFxObject EnterFBBtn;
//
var GFxObject DiffcultyTitleTf;
var GFxObject LevelRequiredTf;
var GFxObject FrequencyRequiredTf;
var GFxObject FrequencyRequiredTitleTf;
var GFxObject PeopleRequiredTf;
var GFxObject HuoLiRequiredTf;
var GFxObject OpenTimeRequiredTf;
var GFxObject OpenTimeRequiredTitleTf;
//
var GFxObject FBNameTf;
var GFxObject FBDescribleTf;
//
//const FB_MEMBER_CNT = 4;
//var GFxObject mc_FBMember[FB_Member_CNT];

//
//native function UpdateTeamMate( int UIPos, int Pos );
//
final native function TickPanel( float DeltaTime );
final native function SetUITitleName( string fbName );
final native function PrepareShow( string mapName, int scrTelepID );
final native function UpdateCurFBInfo( string mapName, int scrTelepID );
final native function UpdateCurFBDiff( int newDiff, int newMaxDiff );
final native function UpdateFBAllDiff( int mapID );
//final native function UpdateMemberStatus();
//
final native function EnterMap();
final native function BranchChange( int iBranchIdx );
final native function SendFBBranch( INT iTeleportID );
final native function SendEnterMap( int iDifficulty);
final native function SendMapDiffChange( int iDifficulty );
//
final native function MapDiffChange( int iLevel );
final native function int CvtToServerDiff( int i );
final native function int CvtToUiDiffIdx( int i );
final native function CheckCanEnter();
//
final native function InitFBEnterData();
//
event CallSetFBDescription( string descText )
{
	ActionScriptVoid("SetFBDescription");
}
//function ChangeUIMode( bool bTeamLeader )
//{
//	local int i;
//	//
//	for( i = 0 ;i < FB_SELECT_DIFF_CNT ;i++ ){
//		btn_FBDiff[i].SetVisible( bTeamLeader );
//	}
//	//
//	for( i = 0 ;i < 5 ;i++ ){
//		btn_FBBranch[i].SetVisible( bTeamLeader );
//	}
//	//
//	btn_Enter.SetVisible( bTeamLeader );
//}

//===============================================================================================================
//===============================================================================================================
native function BeforeViewUpdate( float DeltaTime );

function UCEnterMap()
{
	EnterMap();
}
//
function UCMapDiffChange( int Level )
{
	MapDiffChange( Level );
}
//
function UCFBBranchChange( int iBranchIdx )
{
	BranchChange( iBranchIdx );
}
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=FBEnter
	svrTeleportIDMask = 0x0000ffff;
	IsDynamicLoad=true
}
