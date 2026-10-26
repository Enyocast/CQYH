class MMOUIRClickMenu extends MMOUIBase
	//dependson(TeamManager)
	native(UI);

var GFxObject _ConfirmBox;

enum ERClickMenuType
{
	ERCMType_TargetInfo,    //目标
	ERCMType_TeamMember,
	ERCMType_TeamMate,
	ERCMType_ChatPlayer, //聊天中的名字
	ERCMType_TeamNearby,
	ERCMType_Friend,            //好友
	ERCMType_Contact,       //好友界面非好友和关注的页签
	ERCMType_BattleMember, //战队队友
	ERCMType_FriendGroup, //好友分组
	ERCMType_Attention, //关注列表
	ERCMType_Black,
	ERCMType_GuildMember, //家族成员
	ERCMType_Dungeon,//副本右键
	ERCMType_BattleEnter,//战场排队
	ERCMType_RankListPlayer, //玩家排行榜
	ERCMType_RankListGuild, //公会排行榜
	ERCMType_MasterStudent, //师徒右键
	ERCMType_ChangeMapLine, //地图分线列表
	ERCMType_GuildAlliance, //公会联盟
	ERCMType_AuctionPlayer,
	ERCMType_GuildEnemy, //公会敌对
};

enum ERClickMenuLevel
{
	ERCMLevel_Main, //主
	ERCMLevel_Child, //二级
};

var array<delegate<ClickFunc> > FuncList;
var array<delegate<ClickFunc> > FuncListChild; // 二级的
var const int ButtonMaxNum;
var String OwnerName; // 右键指向目标玩家，id或者name？
var MMOActor OwnerActor;
//var MMOTeamMember OwnerMember;
//var MMONearbyPlayer OwnerNearPlayer;
//var TeamManager TM;
//var FriendManager FM;
var int OwnerRoleId;
var int OwnerIndex;//序号
var int OwnerGroupId;//组号
var int high;//
var int lineStep;//
var int step;
var MMOUIRClickMenuChild MenuChild; //二级右键菜单
var GFxObject CurClickButton; //点击的按钮
var GFxObject RCMenuBg; //bg
var GFxObject MenuOwnerTF; //拥有者名textField

var int ChildStep;
var int ChildHigh;

var int curType;

var int GuildId;

event InitLoad(MMOGFXPlayer pl)
{
	super.InitLoad(pl);
	//TM = player.TeamManager;
	//FM = Player.FriendManager;

	RCMenuBg = GetObject("RCMenuBg");
	MenuOwnerTF = GetObject("tF_menuOwner");
	SetInt( "MenuLevel" , ERCMLevel_Main );

	class'MMOUIManager'.static.SetOpenRClickMenuDelegate(OpenRClickMenu);
	class'MMOUIManager'.static.SetCloseRClickMenuDelegate(CloseRClickMenu);
}

function InitWidget()
{

}

event CallResetChildMenuButton()
{
	ActionScriptVoid("ResetChildMenuButton");		
}

delegate ClickFunc( int idx );

native function MMOActor GetActorByRoleId( int RoleId );
native function AddMenuItem( delegate<ClickFunc> func , string StrName , optional bool UseStringMap = true );
//native function AddChildMenuItem( delegate<ClickFunc> func , string StrName , optional bool UseStringMap = true );//move
native function bool SkipCaptureInputKey(String key, EInputEvent eIE, const string strHoverControllerName, Vector2D ClickPosInMovieSpace);


//native function ChangeMenu(  int RoleId , String RoleName , int index , ERClickMenuType type );
//{
//	local GFxObject lineBase;
//	step = 0;
//	lineStep = 0;

//	high = 0;
//	lineBase = GetObject("splitLine");
	
//	if( lineBase != none )
//	{
//		high = lineBase.GetInt( "height" ) + lineBase.GetInt("y");
//	}
//	curType = type;
//	switch( type )
//	{
//	case ERCMType_TargetInfo:
//		MenuByTargetInfo(RoleId,RoleName);
//		break;
//	case ERCMType_TeamMember:
//		MenuByMyTeam( index );
//		break;
//	case ERCMType_TeamMate:
//		MenuByTeamMate( index );
//		break;
//	case ERCMType_TeamNearby:
//		MenuByNearPlayer( index );
//		break;	
//	case ERCMType_Friend:
//		MenuByFriend( RoleId , RoleName ); //这里RoleId的字段是GroupId
//		break;
//	case ERCMType_Attention:
//		MenuByAttention( index , RoleName ); 
//		break;
//	case ERCMType_FriendGroup:
//		MenuByFriendGroup( index , RoleName );
//		break;
//	case ERCMType_BattleMember:
//		MenuByBattleMember( index );
//		break;
//	//case ERCMType_Black:
//	//	MenuByBlack( index );
//	//	break;
//	case ERCMType_GuildMember:
//		MenuByGuildMember(RoleId);
//		break;
//	case ERCMType_ChatPlayer:
//		MenuByChatPlayer( RoleId , RoleName );
//		break;
//	}

//}

native function OpenRClickMenu( ERClickMenuType type, int x, int y , int RoleId  ,String RoleName  ,int index );
native function CloseRClickMenu( ERClickMenuType type);
native function ShowClickItem( string label  ); //move
//native function ShowChildClickItem( string label  );// move

event ClickItem( int MenuLevel , int itemid )
{
	local delegate<ClickFunc> tClickFunc;
		
	/*if ( MenuLevel == ERCMLevel_Child  )
	{
		CurClickButton = MenuChild.GetObject("RClicklistItem"$itemid);
		if( FuncListChild.Length >itemid  && FuncListChild[itemid]!= none)
		{
			tClickFunc = FuncListChild[itemid];
			tClickFunc( itemid );
		}
	}*/
	/*else*/ if( MenuLevel ==  ERCMLevel_Main  )
	{
		CurClickButton = GetObject("RClicklistItem"$itemid);
			if( FuncList.Length >itemid  && FuncList[itemid]!= none)
		{
			tClickFunc = FuncList[itemid];
			tClickFunc( itemid );
		}
	}
}

native function ClearUI();
function AddChangeNameOk(GFxObject mc)
{
	local int GroupId;
	local string textInput;
	GroupId = mc.GetInt("iteminfoid");
	textInput = mc.GetObject( "textInput" ).GetString("text");
	class'MMOUIManager'.static.ChangeGroupName( textInput , GroupId );
}

native function AddNewGroupOk(GFxObject mc);
native function DelFriendOk( GFxObject mc );

function MsgBoxNo( GFxObject mc ) //不处理
{
//
}

native function ClickDelGroup( int inMenuIdx );
native function DelGroupOk( GFxObject mc );
native function MoveBlackOk( GFxObject mc );

final native function ClickOpenContactDialog( int inMenuIdx );
final native function ClickInvitePlayerIntoTeam( int inMenuIdx );
final native function ClickApplyDoTrade( int inMenuIdx );
final native function ClickLeaveFB( int inMenuIdx );
final native function ClickLeaveBattleEnterQueue( int inMenuIdx );
final native function ClickChangeMapLine( int inMenuIdx );
final native function ClickAddFriend( int inMenuIdx );
final native function ClickAddEnemy( int inMenuIdx );
final native function ClickRemoveEnemy( int inMenuIdx );
final native function ClickAchievementCompare( int inMenuIdx );
final native function ClickLeaveTeam( int inMenuIdx );
final native function ClickMoveLeader( int inMenuIdx );
final native function ClickChangeTeamAuctionLimit( int inMenuIdx );
//final native function ClickChangeTeamAuctionLimitColor( int inMenuIdx );//move
final native function ClickEnterPrivateChat( int inMenuIdx );
final native function ClickMoveToBlackList( int inMenuIdx );
final native function ClickRemoveFromBlackList( int inMenuIdx );
//final native function ClickMoveFriendToGroup( int inMenuIdx ); //move
final native function ClickSendMail( int inMenuIdx );
final native function ClickMoveFriend( int inMenuIdx ); //点击移动好友
final native function ClickInviteBattleTeam( int inMenuIdx );//邀请来战队
final native function ClickRemoveBattleTeam( int inMenuIdx );//踢掉战队成员
final native function ClickNewGroup( int inMenuIdx );
final native function ClickChangeGroupName( int inMenuIdx );

//常规类
	native function ClickDeleteFriend( int inMenuIdx );
	//查看资料
	native function ClickViewProfile( int inMenuIdx );
	//查看简易资料
	native function ClickSimpleProfile( int inMenuIdx );
	//点击跟随/取消跟随
	native function ClickFollow( int inMenuIdx );
	native function ClickNullFollow( int inMenuIdx );

//公会类
	//邀请加入公会
native function ClickInviteToJoinGuild( int inMenuIdx );
	//推荐加入公会
native function ClickRecommendJoinGuild( int inMenuIdx );
	//申请加入公会
native function ClickApplyToJoinGuild( int inMenuIdx );
	//踢出公会
native function ClickKickOutGuild( int inMenuIdx );
	//公会禁言
native function ClickForbidChatOn( int inMenuIdx );
native function ClickForbidChatOff( int inMenuIdx );
	//公会联盟
native function ClickCancelAlliance( int inMenuIdx );
	//复制公会名称(通过玩家)
native function ClickCopyGuildName(int inMenuIdx);
	//复制公会名称(通过界面)
native function ClickCopyGuildNameByPanel(int inMenuIdx);
	//公会宣战
native function ClickGuildWar(int inMenuIdx);

//打开公会信息页面
native function ClickOpenGuild( int inMenuIdx );

//师徒类
	//拜师
native function ClickApplyMaster( int inMenuIdx );
native function ClickApplyStudent( int inMenuIdx );
	//收徒
native function ClickReadmastermsg( int inMenuIdx );
	//逐出师门
native function ClickExpell( int inMenuIdx );
//背叛师门
native function ClickBetryMaster( int inMenuIdx );

//结婚
	//求婚
native function ClickMerry( int inMenuIdx );
	//离婚
native function ClickDivorce( int inMenuIdx );

//常规类设置
	//屏蔽聊天
native function ClickCommon1( int inMenuIdx );
	//取消屏蔽
native function ClickCommon2( int inMenuIdx );
	//举报玩家
native function ClickCommon3( int inMenuIdx );
	//追踪位置
native function ClickCommon4( int inMenuIdx );
//复制名字
	//复制名字
native function ClickCopyName( int inMenuIdx );

//查看角色信息
native function ClickViewProfileOnRank( int inMenuIdx );

native function FireStudent(GFxObject m);
native function OnFireStudentCancel();

//背叛师门
native function LeaveMaster(GFxObject m);
native function LeaveMasterCancel();

//-------------------moved----------------------
native function ASClickRightMenuItem( int MenuLevel, int ItemId );

DefaultProperties
{
	ButtonMaxNum = 20
	OwnerActor=none
	DefaultVisible=false
	CloseOnEsc=false
}
