#include "stdafx.h"
#include "RClickFormatter.h"
#include "UITextParser.h"
#include "MMOFacade.h"
#include "MMOBuffManager.h"
#include "MMOAttributeAccountManager.h"
#include "MMOEquipManager.h"
#include "MMOSkillManager.h"
#include "MMOHeavenManager.h"
#include "AbilityProcessor.h"
#include "FriendManager.h"
#include "BattleTeamManager.h"
#include "MMOQuestManager.h"
#include "TeamManager.h"
#include "MMOGuildManager.h"
#include "MasterStudentManager.h"
#include "client_option_def.h"

RClickFormatter::RClickFormatterMap RClickFormatter::_RClickFormatterMap;


bool InitRClickFormatterMap()
{
#define M_RGE_FMTTER(e, cls) { static cls g_##cls; RClickFormatter::RegRClickFormatter(e, &g_##cls); }

	M_RGE_FMTTER(ERCMType_TargetInfo    , RClickFormatter_TargetInfo    );
	M_RGE_FMTTER(ERCMType_TeamMember    , RClickFormatter_TeamMember    );
	M_RGE_FMTTER(ERCMType_TeamMate      , RClickFormatter_TeamMate      );
	M_RGE_FMTTER(ERCMType_ChatPlayer    , RClickFormatter_ChatPlayer    );
	M_RGE_FMTTER(ERCMType_TeamNearby    , RClickFormatter_TeamNearby    );
	M_RGE_FMTTER(ERCMType_Friend        , RClickFormatter_Friend        );
	M_RGE_FMTTER(ERCMType_BattleMember  , RClickFormatter_BattleMember  );
	M_RGE_FMTTER(ERCMType_FriendGroup   , RClickFormatter_FriendGroup   );
	M_RGE_FMTTER(ERCMType_Attention     , RClickFormatter_Attention     );
	M_RGE_FMTTER(ERCMType_Black         , RClickFormatter_Black         );
	M_RGE_FMTTER(ERCMType_GuildMember   , RClickFormatter_GuildMember   );
	M_RGE_FMTTER(ERCMType_Dungeon       , RClickFormatter_Dungeon       );
	M_RGE_FMTTER(ERCMType_RankListPlayer, RClickFormatter_RankListPlayer);
	M_RGE_FMTTER(ERCMType_RankListGuild , RClickFormatter_RankListGuild );
	M_RGE_FMTTER(ERCMType_GuildAlliance , RClickFormatter_GuildAlliance );
	M_RGE_FMTTER(ERCMType_AuctionPlayer , RClickFormatter_AuctionPlayer);
	M_RGE_FMTTER(ERCMType_GuildEnemy	, RClickFormatter_GuildEnemy);
    return true;
}

static bool g_InitRClickFormatter = InitRClickFormatterMap();

void RClickFormatter::RegRClickFormatter( ERClickMenuType RClickType, IRClickFormatter* fmt )
{
    _RClickFormatterMap[RClickType] = fmt;
}

IRClickFormatter* RClickFormatter::GetRClickFormatter( ERClickMenuType RClickType )
{
    RClickFormatterMap::iterator i = _RClickFormatterMap.find(RClickType);
    if(i != _RClickFormatterMap.end())
    {
        return i->second;
    }
    return 0;
}

void RClickFormatter::FormatRClick(ERClickMenuType RClickType, class UMMOUIRClickMenu* RClickMenu)
{
    IRClickFormatter* fmt = RClickFormatter::GetRClickFormatter(RClickType);
    if(fmt)
    {
        fmt->FormatRClick(RClickMenu);
    }
    else
    {
        warnf(NAME_Error, TEXT("[RClickFormatter::FormatRClick] formater not found:%d"), (INT)RClickType);
    }

}


//检查自己
UBOOL RClick_CheckSelf(class UMMOUIRClickMenu* RClickMenu , FScriptDelegate &func)
{
	if(RClickMenu==NULL)return TRUE;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if(Player==NULL)return TRUE;


	//点的就是我
	if( RClickMenu->OwnerRoleId == Player->ServerID  )
	{
		//自己离开队伍
		if( TeamManager::getSingleton().HasTeam() )
		{
			func.FunctionName = "ClickLeaveTeam";
			RClickMenu->AddMenuItem( func , TEXT("LeaveTeam") );
		}
		//查看自己资料
		func.FunctionName = "ClickViewProfile";
		RClickMenu->AddMenuItem( func , TEXT("ViewProfile") );
		return TRUE;
	}	
	return FALSE;
}

//联系大类
void RClick_Contant(class UMMOUIRClickMenu* RClickMenu , FScriptDelegate &func)
{
	LOG_PROCESS_ERROR(RClickMenu);
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	LOG_PROCESS_ERROR(Player);

	//联系大类
	//弹框聊天
	if( FriendManager::getSingleton().IsMyFriend( RClickMenu->OwnerRoleId )  )
	{
		func.FunctionName = "ClickOpenContactDialog";
		RClickMenu->AddMenuItem( func , TEXT("EnterChat") );
	}	
	//私聊
	func.FunctionName = "ClickEnterPrivateChat"; 
	RClickMenu->AddMenuItem( func , TEXT("PrivateChat") );	
	//邮件
	func.FunctionName = "ClickSendMail";
	RClickMenu->AddMenuItem( func , TEXT("SendMail") );
	//师徒
	if (E_MASTER_NONE == MasterStudentManager::getSingleton().GetMasterStudentState())
	{
		int PlayerLv = Player->ActorAttributes->LevelAttributes.Level;
		if(GRADUATE_LEVEL > PlayerLv&& PlayerLv >= STUD_LEVEL_LOWER_LIMIT)
		{
			func.FunctionName = "ClickApplyMaster";
			RClickMenu->AddMenuItem(func, TEXT("ApplyMaster"));
		}
	}
	else if (E_MASTER_STUDENT == MasterStudentManager::getSingleton().GetMasterStudentState())
	{
		const MasterDetailInfo& pMasterInfo = MasterStudentManager::getSingleton().GetMasterDetailInfo();
		if(pMasterInfo.nRoleID > 0)
		{
			if(appStrcmp(*pMasterInfo.masterName,*RClickMenu->OwnerName) == 0)
			{
				func.FunctionName = "ClickBetryMaster";
				RClickMenu->AddMenuItem(func, TEXT("BetryMaster"));
			}
		}
	}
	else if (E_MASTER_TEACHER == MasterStudentManager::getSingleton().GetMasterStudentState())
	{
		const StudentListData* pStudent = MasterStudentManager::getSingleton().GetStudentDataByID(RClickMenu->OwnerRoleId);
		if (NULL != pStudent)
		{
			func.FunctionName = "ClickExpell";
			RClickMenu->AddMenuItem(func, TEXT("Expell"));
		}
		else
		{
			func.FunctionName = "ClickApplyStudent";
			RClickMenu->AddMenuItem(func, TEXT("Readmastermsg"));
		}
	}

Exit0:
	return;
}


//联系大类
UBOOL RClick_Cooperate(class UMMOUIRClickMenu* RClickMenu , FScriptDelegate &func)
{
	LOG_PROCESS_ERROR(RClickMenu);
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	LOG_PROCESS_ERROR(Player);
	//合作大类
	RClickMenu->AddLine();
	//组队类
	{
		//点的就是我
		if( RClickMenu->OwnerRoleId == Player->ServerID && TeamManager::getSingleton().HasTeam() )
		{
			//自己离开队伍
			func.FunctionName = "ClickLeaveTeam";
			RClickMenu->AddMenuItem( func , TEXT("LeaveTeam") );
			return TRUE;
		}

		if( RClickMenu->OwnerActor /*&& OwnerActor->TeamID > 0*/ && !TeamManager::getSingleton().HasTeam() ) //我无队
		{
			//申请入队
			func.FunctionName = "ClickInvitePlayerIntoTeam";
			RClickMenu->AddMenuItem(  func , TEXT("ApplyTeam") );
		}
		else if( RClickMenu->OwnerActor /*&& OwnerActor->TeamID <= 0*/ && TeamManager::getSingleton().HasTeam() /*&& TeamManager::getSingleton().IsTeamLeader()*/ )
		{
			//邀请入队
			func.FunctionName = "ClickInvitePlayerIntoTeam";
			RClickMenu->AddMenuItem( func , TEXT("InviteTeam") );
		}
		else if( RClickMenu->OwnerActor /*&& OwnerActor->TeamID <= 0*/ && !TeamManager::getSingleton().HasTeam() )
		{
			func.FunctionName = "ClickInvitePlayerIntoTeam";
			RClickMenu->AddMenuItem( func , TEXT("InviteTeam") );
		}

		//if( BattleTeamManager::getSingleton().HasTeam() && BattleTeamManager::getSingleton().IsTeamLeader() )
		//{
		//	func.FunctionName = "ClickInviteBattleTeam";
		//	RClickMenu->AddMenuItem( func , TEXT("InviteBattleTeam") );
		//}

		if( TeamManager::getSingleton().HasTeam() && TeamManager::getSingleton().IsTeamLeader() )
		{
			if(TeamManager::getSingleton().GetMemberById(RClickMenu->OwnerRoleId))//如果在队伍中
			{
				//踢出队伍
				func.FunctionName = "ClickLeaveTeam";
				RClickMenu->AddMenuItem( func , TEXT("KickOutTeam") );
				//移交队长
				func.FunctionName = "ClickMoveLeader";
				RClickMenu->AddMenuItem( func , TEXT("MoveLeader") );
			}
		}
	}

Exit0:
	return FALSE;
}

//公会大类
UBOOL RClick_Guild(class UMMOUIRClickMenu* RClickMenu, FScriptDelegate &func)
{
	if (RClickMenu)
	{
		RClickMenu->AddMenuItem_Guild(func);
	}
	return FALSE;
}

void RClickFormatter_TargetInfo::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if(Player==NULL)return;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	//查看资料

	func.FunctionName = "ClickViewProfile";
	RClickMenu->AddMenuItem( func , TEXT("ViewProfile") );

	//点击跟随/取消跟随
	if(1){
		func.FunctionName = "ClickFollow";
		RClickMenu->AddMenuItem( func , TEXT("Follow") );
	}
	else
	{
		func.FunctionName = "ClickNullFollow";
		RClickMenu->AddMenuItem( func , TEXT("NullFollow") );
	}
	

	//加为好友

		if( FriendManager::getSingleton().IsMyFriend(RClickMenu->OwnerRoleId) || FriendManager::getSingleton().IsMyAttention(RClickMenu->OwnerRoleId) )
		{   //取消关注
			func.FunctionName = "ClickDeleteFriend";
			RClickMenu->AddMenuItem( func , TEXT("DelAttention") );	
		}
		else
		{
			//加为关注
			func.FunctionName = "ClickAddFriend";
			RClickMenu->AddMenuItem( func , TEXT("AddAttention") );	
		}
		if(FriendManager::getSingleton().InMyEnemyList(RClickMenu->OwnerRoleId))
		{
			func.FunctionName = "ClickRemoveEnemy";
			RClickMenu->AddMenuItem( func , TEXT("RemoveEnemy") );	
		}
		else
		{
			func.FunctionName = "ClickAddEnemy";
			RClickMenu->AddMenuItem( func , TEXT("AddEnemy") );	
		}

	
	//申请交易

		func.FunctionName = "ClickApplyDoTrade";
		RClickMenu->AddMenuItem( func, TEXT("ApplyDoTrade") );
	
	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );

	//公会类
	RClick_Guild(RClickMenu, func);

	//常规类设置

	RClickMenu->AddLine();
}


void RClickFormatter_TeamMember::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;

	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );

	//常规类设置
	RClickMenu->AddLine();
}

void RClickFormatter_TeamMate::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{

	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	//常规类设置
	RClickMenu->AddLine();
}


void RClickFormatter_ChatPlayer::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if(Player==NULL)return;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;

	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	//查看资料

	//加为好友

	if( FriendManager::getSingleton().IsMyFriend(RClickMenu->OwnerRoleId) || FriendManager::getSingleton().IsMyAttention(RClickMenu->OwnerRoleId) )
	{   //取消关注
		func.FunctionName = "ClickDeleteFriend";
		RClickMenu->AddMenuItem( func , TEXT("DelAttention") );	
	}
	else
	{
		//加为关注
		func.FunctionName = "ClickAddFriend";
		RClickMenu->AddMenuItem( func , TEXT("AddAttention") );	
	}
	if(FriendManager::getSingleton().InMyEnemyList(RClickMenu->OwnerRoleId))
	{
		func.FunctionName = "ClickRemoveEnemy";
		RClickMenu->AddMenuItem( func , TEXT("RemoveEnemy") );	
	}
	else
	{
		func.FunctionName = "ClickAddEnemy";
		RClickMenu->AddMenuItem( func , TEXT("AddEnemy") );	
	}

	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );

	//公会类
	RClick_Guild(RClickMenu, func);
	
	//常规类设置
	RClickMenu->AddLine();


	if( FriendManager::getSingleton().InMyBlackList(RClickMenu->OwnerRoleId) )
	{
		//取消屏蔽
		func.FunctionName = "ClickRemoveFromBlackList";
		RClickMenu->AddMenuItem( func , TEXT("RemoveBlack") );
	}
	else
	{
		//屏蔽聊天
		func.FunctionName = "ClickMoveToBlackList";
		RClickMenu->AddMenuItem( func , TEXT("MoveToBlack") );
	}


	RClickMenu->AddLine();
}


void RClickFormatter_TeamNearby::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	//查看资料
	//加为好友
	//申请交易

	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );

	//公会类

	//常规类设置
	RClickMenu->AddLine();
}


void RClickFormatter_Friend::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if(Player==NULL)return;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);


	//加为好友

	if( FriendManager::getSingleton().IsMyFriend(RClickMenu->OwnerRoleId) || FriendManager::getSingleton().IsMyAttention(RClickMenu->OwnerRoleId) )
	{   //取消关注
		func.FunctionName = "ClickDeleteFriend";
		RClickMenu->AddMenuItem( func , TEXT("DelAttention") );	
	}
	else
	{
		//加为关注
		func.FunctionName = "ClickAddFriend";
		RClickMenu->AddMenuItem( func , TEXT("AddAttention") );	
	}
	if(FriendManager::getSingleton().InMyEnemyList(RClickMenu->OwnerRoleId))
	{
		func.FunctionName = "ClickRemoveEnemy";
		RClickMenu->AddMenuItem( func , TEXT("RemoveEnemy") );	
	}
	else
	{
		func.FunctionName = "ClickAddEnemy";
		RClickMenu->AddMenuItem( func , TEXT("AddEnemy") );	
	}

	func.FunctionName = "ClickMoveFriend";
	RClickMenu->AddMenuItem( func , TEXT("MoveFriend") );
		
	

	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );

	//公会类
	RClick_Guild(RClickMenu, func);

	//常规类设置
	RClickMenu->AddLine();
	if( FriendManager::getSingleton().InMyBlackList(RClickMenu->OwnerRoleId) )
	{
		//取消屏蔽
		func.FunctionName = "ClickRemoveFromBlackList";
		RClickMenu->AddMenuItem( func , TEXT("RemoveBlack") );
	}
	else
	{
		//屏蔽聊天
		func.FunctionName = "ClickMoveToBlackList";
		RClickMenu->AddMenuItem( func , TEXT("MoveToBlack") );
	}
	RClickMenu->AddLine();
}


void RClickFormatter_BattleMember::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	//查看资料

	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );

	//公会类

	//常规类设置
	RClickMenu->AddLine();

}


void RClickFormatter_FriendGroup::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;

	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );


	//常规类设置
	RClickMenu->AddLine();
}


void RClickFormatter_Attention::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;

	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	//加为好友

	if( FriendManager::getSingleton().IsMyFriend(RClickMenu->OwnerRoleId) || FriendManager::getSingleton().IsMyAttention(RClickMenu->OwnerRoleId) )
	{   //取消关注
		func.FunctionName = "ClickDeleteFriend";
		RClickMenu->AddMenuItem( func , TEXT("DelAttention") );	
	}
	else
	{
		//加为关注
		func.FunctionName = "ClickAddFriend";
		RClickMenu->AddMenuItem( func , TEXT("AddAttention") );	
	}
	if(FriendManager::getSingleton().InMyEnemyList(RClickMenu->OwnerRoleId))
	{
		func.FunctionName = "ClickRemoveEnemy";
		RClickMenu->AddMenuItem( func , TEXT("RemoveEnemy") );	
	}
	else
	{
		func.FunctionName = "ClickAddEnemy";
		RClickMenu->AddMenuItem( func , TEXT("AddEnemy") );	
	}
	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );


	//常规类设置

	RClickMenu->AddLine();
}

void RClickFormatter_Black::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );


	//常规类设置
	RClickMenu->AddLine();
}

void RClickFormatter_GuildMember::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if(Player==NULL)return;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );

	//公会类
	RClick_Guild(RClickMenu, func);

	//常规类设置
	RClickMenu->AddLine();
}

void RClickFormatter_Dungeon::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;

	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);

	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );


	//常规类设
	RClickMenu->AddLine();
}


void RClickFormatter_RankListPlayer::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if(Player==NULL)return;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);


	if( FriendManager::getSingleton().IsMyFriend(RClickMenu->OwnerRoleId) || FriendManager::getSingleton().IsMyAttention(RClickMenu->OwnerRoleId) )
	{   //取消关注
		func.FunctionName = "ClickDeleteFriend";
		RClickMenu->AddMenuItem( func , TEXT("DelAttention") );	
	}
	else
	{
		//加为关注
		func.FunctionName = "ClickAddFriend";
		RClickMenu->AddMenuItem( func , TEXT("AddAttention") );	
	}
	if(FriendManager::getSingleton().InMyEnemyList(RClickMenu->OwnerRoleId))
	{
		func.FunctionName = "ClickRemoveEnemy";
		RClickMenu->AddMenuItem( func , TEXT("RemoveEnemy") );	
	}
	else
	{
		func.FunctionName = "ClickAddEnemy";
		RClickMenu->AddMenuItem( func , TEXT("AddEnemy") );	
	}
	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );

	// 公会类
	RClick_Guild(RClickMenu, func);
	
	RClickMenu->AddLine();
}

void RClickFormatter_RankListGuild::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if(Player==NULL)return;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//联系大类
	RClick_Contant(RClickMenu , func);

	//合作大类
	RClick_Cooperate(RClickMenu , func);


	// Achievement成就比较
	func.FunctionName = "ClickAchievementCompare";
	RClickMenu->AddMenuItem( func, TEXT("CompareAchievement") );

	// 公会类
	RClick_Guild(RClickMenu, func);

	RClickMenu->AddLine();
}

void RClickFormatter_GuildAlliance::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if(Player==NULL)return;

	//取消联盟
	func.FunctionName = "ClickCancelAlliance";
	RClickMenu->AddMenuItem(func , TEXT("CancelAlliance"));

	//复制公会名
	func.FunctionName = "ClickCopyGuildNameByPanel";
	RClickMenu->AddMenuItem(func, TEXT("CopyGuildName"));

	RClickMenu->AddLine();
}

void RClickFormatter_GuildEnemy::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{
	FScriptDelegate func(EC_EventParm);
	func.Object = RClickMenu;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if (Player == NULL)return;

	//宣战
	UINT32 clientOption = CMessageHandler::GetInstance().GetClientOption();
	if (clientOption & CLIENT_OPTION_BIT_GUILD_WAR)
	{
		func.FunctionName = "ClickGuildWar";
		RClickMenu->AddMenuItem(func, TEXT("GuildWar"));
	}

	//复制公会名
	func.FunctionName = "ClickCopyGuildNameByPanel";
	RClickMenu->AddMenuItem(func, TEXT("CopyGuildName"));

	RClickMenu->AddLine();
}

void RClickFormatter_AuctionPlayer::FormatRClick(class UMMOUIRClickMenu* RClickMenu)
{	
	FScriptDelegate func( EC_EventParm);
	func.Object = RClickMenu;
	class AMMOPlayer* Player = MMOFacade::getSingleton().GetMainPlayer();
	if(Player==NULL)return;

	//检查自己
	UBOOL res = RClick_CheckSelf(RClickMenu , func);
	if(res)return;


	//私聊
	func.FunctionName = "ClickEnterPrivateChat"; 
	RClickMenu->AddMenuItem( func , TEXT("PrivateChat") );	


	if( FriendManager::getSingleton().IsMyFriend(RClickMenu->OwnerRoleId) || FriendManager::getSingleton().IsMyAttention(RClickMenu->OwnerRoleId) )
	{   //取消关注
		func.FunctionName = "ClickDeleteFriend";
		RClickMenu->AddMenuItem( func , TEXT("DelAttention") );	
	}
	else
	{
		//加为关注
		func.FunctionName = "ClickAddFriend";
		RClickMenu->AddMenuItem( func , TEXT("AddAttention") );	
	}

	//复制名字
	func.FunctionName = "ClickCopyName";
	RClickMenu->AddMenuItem( func , TEXT("CopyName") );

	// 公会类
	// 复制公会名字
	func.FunctionName = "ClickCopyGuildName";
	RClickMenu->AddMenuItem(func, TEXT("CopyGuildName"));

	RClickMenu->AddLine();
}

