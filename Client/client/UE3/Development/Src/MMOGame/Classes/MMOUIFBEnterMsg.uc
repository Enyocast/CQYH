class MMOUIFBEnterMsg extends MMOUIBase
	native(UI);

var bool bPrepared;
var int FBEntranceLinkID;
var string FBEntranceMapName;
var int CurDiff;

//var GFxObject FBMsgImg_mc;
//var GFxObject FBMsgMonsterImg_mc;
//
var GFxObject tF_FBMsgMapName;
var GFxObject tf_FBMsgCurrentDiff;
var GFxObject tF_FBMsgLvRequired;
var GFxObject tF_FBMsgRecmmend;
var GFxObject tF_FBMsgDescrible;
const FB_MEMBER_CNT = 4;
var GFxObject mc_FBMsgMember[FB_MEMBER_CNT];
var int prepareMemID[FB_MEMBER_CNT];
var int curPrepared;
//
var GFxObject btn_Prepare;
var GFxObject btn_CancelPrepare;
//
native function PrepareEnter();
native function CancelPrepare();
native function NoticeFBEnter( string mapName, int linkID, int iCurDiff );
native function UpdateCurFBInfo();
native function UpdateMemberStatus();
native function bool TogglePrepare();
native function ResponsePrepareEnter();
native function ResponseCancelPrepare();
native function UpdateTeamMate( int UIPos, int Pos );

event ResetPanel()
{
	bPrepared = false;
	btn_Prepare.SetBool( "enabled", !bPrepared );
	btn_CancelPrepare.SetBool( "enabled", bPrepared );
	prepareMemID[0] = 0;
	prepareMemID[1] = 0;
	prepareMemID[2] = 0;
	prepareMemID[3] = 0;
	curPrepared = 0;
}
//
event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	//
	//FBMsgImg_mc = GetObject( "FBMsgImg_mc" );
	//FBMsgMonsterImg_mc = GetObject( "FBMsgMonsterImg_mc" );
	//
	tF_FBMsgMapName = GetObject( "tF_FBMsgMapName" );
	tf_FBMsgCurrentDiff = GetObject( "tf_FBMsgCurrentDiff" );
	tF_FBMsgLvRequired = GetObject( "tF_FBMsgLvRequired" );
	tF_FBMsgRecmmend = GetObject( "tF_FBMsgRecmmend" );
	//tF_FBMsgDescrible = GetObject( "tF_FBMsgDescrible" );
	//
	mc_FBMsgMember[0] = GetObject( "mc_FBMsgMember0" );
	mc_FBMsgMember[1] = GetObject( "mc_FBMsgMember1" );
	mc_FBMsgMember[2] = GetObject( "mc_FBMsgMember2" );
	mc_FBMsgMember[3] = GetObject( "mc_FBMsgMember3" );
	//
	btn_Prepare = GetObject( "btn_Prepare" );
	btn_Prepare.SetVisible( false );
	btn_CancelPrepare = GetObject( "btn_CancelPrepare" );
	btn_CancelPrepare.SetVisible( false );
}

//===============================================================================================================
//===============================================================================================================
function UCPrepareEnter()
{
	PrepareEnter();
}
//
function UCCancelPrepare()
{
	CancelPrepare();
}
//===============================================================================================================
//===============================================================================================================

DefaultProperties
{
	//FriendlyName=FBEnterMsg
	IsDynamicLoad=true
}