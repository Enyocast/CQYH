#include "stdafx.h"
#include "robot_message_handler.h"

#include "irobot_message_notifier.h"
#include "game_world.h"

#include "rsa_sign.h"
#include "chat.h"
#include "guild_def.h"
#include "scene_data.h"
#include "npc_def.h"
#include "item.h"
#include "zlib.h"
#include "server_def.h"
#include "achievement_data.h"
#include "gs_guild.h"
#include "guild_mgr.h"
#include "spell_config.h"
#include "../asimov/user.h"
#include "../asimov/user_mgr.h"
#include "general_mgr.h"
#include "guild_config.h"
#include "script_mgr.h"

#ifdef _ROBOT

#define MAX_ROBOT_CACHE_COUNT	(16 * 1024)

using namespace ExternalMessage;

CRobotMessageHandler CRobotMessageHandler::ms_Instance;

ROLE_CACHE	s_RoleCache;

CRobotMessageHandler::CRobotMessageHandler()
{
	m_poNotifier = NULL;
	m_pPacketAllocator = NULL;
}

CRobotMessageHandler::~CRobotMessageHandler()
{

}

CRobotMessageHandler& CRobotMessageHandler::GetInstance(void)
{
	return ms_Instance;
}

void CRobotMessageHandler::OnRecv(CRole* poRole, const char* pData)
{
	MESSAGE_HEADER* pHeader = (MESSAGE_HEADER*)pData;

	if (m_RobotMessageFuncList[pHeader->wMsg])
	{
		(this->*m_RobotMessageFuncList[pHeader->wMsg])(poRole, pData);
	}

	if (poRole->GetAIProcessor())
		poRole->GetAIProcessor()->CheckMsgID(pHeader->wMsg);

Exit0:
	return;
}

BOOL CRobotMessageHandler::Init(IRobotMessageNotifier* poNotifier, IPacketAllocator* poPacketAllocator)
{
	LOG_PROCESS_ERROR(poNotifier);
	LOG_PROCESS_ERROR(poPacketAllocator);

	m_poNotifier = poNotifier;
	m_pPacketAllocator = poPacketAllocator;
	m_bTeamAuto = FALSE;
	m_nSuccTradeTendency = 0;

	s_RoleCache.RoleInfoCache.clear();
	s_RoleCache.RoleDataCache.clear();
	s_RoleCache.NpcDataCache.clear();
	s_RoleCache.GuildInfoCache.clear();
	s_RoleCache.GuildDataCache.clear();

	memset(m_RobotMessageFuncList, 0, sizeof(m_RobotMessageFuncList));

	// login
	m_RobotMessageFuncList[m2c_error_notify] = &CRobotMessageHandler::OnMSErrorNotify;
	m_RobotMessageFuncList[g2c_sync_frame] = &CRobotMessageHandler::OnSyncFrame;
	m_RobotMessageFuncList[g2c_enter_scene] = &CRobotMessageHandler::OnEnterScene;
	m_RobotMessageFuncList[g2c_leave_scene] = &CRobotMessageHandler::OnLeaveScene;

	m_RobotMessageFuncList[g2c_sync_game_data_begin] = &CRobotMessageHandler::OnSyncGameDataBegin;
	m_RobotMessageFuncList[g2c_sync_attr_list] = &CRobotMessageHandler::OnSyncAttrList;
	m_RobotMessageFuncList[g2c_sync_spell_book] = &CRobotMessageHandler::OnSyncSpellBook;
	m_RobotMessageFuncList[g2c_sync_spell_slot] = &CRobotMessageHandler::OnSyncSpellSlot;
	m_RobotMessageFuncList[g2c_equip_spell] = &CRobotMessageHandler::OnCharEquipSpell;
	m_RobotMessageFuncList[g2c_sync_client_variables] = &CRobotMessageHandler::OnSyncClientVariables;

	m_RobotMessageFuncList[g2c_changescene_enter] = &CRobotMessageHandler::OnChangeSceneEnter;
	m_RobotMessageFuncList[g2c_sync_money] = &CRobotMessageHandler::OnSyncMoney;
	m_RobotMessageFuncList[g2c_sync_container_sizes] = &CRobotMessageHandler::OnSyncContainerSizes;
	m_RobotMessageFuncList[g2c_container_size_change] = &CRobotMessageHandler::OnContainerSizeChange;
	m_RobotMessageFuncList[g2c_sync_item_bag] = &CRobotMessageHandler::OnSyncItemBag;
	m_RobotMessageFuncList[g2c_sync_game_data_end] = &CRobotMessageHandler::OnSyncGameDataEnd;
	m_RobotMessageFuncList[g2c_sync_npc_data] = &CRobotMessageHandler::OnSyncNpcData;
	m_RobotMessageFuncList[g2c_sync_role_data] = &CRobotMessageHandler::OnSyncRoleData;

	m_RobotMessageFuncList[g2c_sync_drop_list] = &CRobotMessageHandler::OnSyncDropList;

	// attribute
	m_RobotMessageFuncList[g2c_role_level_up] = &CRobotMessageHandler::OnRoleLevelUp;
	m_RobotMessageFuncList[g2c_exp_change] = &CRobotMessageHandler::OnExpChange;
	m_RobotMessageFuncList[g2c_modify_reputation] = &CRobotMessageHandler::OnModifyReputation;
	m_RobotMessageFuncList[g2c_sync_faction] = &CRobotMessageHandler::OnSyncFaction;
	m_RobotMessageFuncList[g2c_sync_pk_mode] = &CRobotMessageHandler::OnSyncPkMode;
	m_RobotMessageFuncList[g2c_sync_pk_value] = &CRobotMessageHandler::OnSyncPkValue;

	// stall
	m_RobotMessageFuncList[g2c_stall_state_change] = &CRobotMessageHandler::OnStallStateChange;
	m_RobotMessageFuncList[g2c_add_stall_item] = &CRobotMessageHandler::OnAddStallItem;
	m_RobotMessageFuncList[g2c_remove_stall_item] = &CRobotMessageHandler::OnRemoveStallItem;
	m_RobotMessageFuncList[g2c_change_stall_name] = &CRobotMessageHandler::OnChangeStallName; 
	m_RobotMessageFuncList[g2c_buy_stall_item] = &CRobotMessageHandler::OnBuyStallItem;
	m_RobotMessageFuncList[g2c_sold_stall_item] = &CRobotMessageHandler::OnSoldStallItem; 
	m_RobotMessageFuncList[g2c_sync_stall] = &CRobotMessageHandler::OnSyncStallLevel;
	m_RobotMessageFuncList[g2c_view_stall_item] = &CRobotMessageHandler::OnViewStallItem;

	// move
	m_RobotMessageFuncList[g2c_char_appear] = &CRobotMessageHandler::OnCharAppear;
	m_RobotMessageFuncList[g2c_sync_char_list] = &CRobotMessageHandler::OnSyncCharList;
	m_RobotMessageFuncList[g2c_object_disappear] = &CRobotMessageHandler::OnObjectDisappear;
	m_RobotMessageFuncList[g2c_object_disappear_list] = &CRobotMessageHandler::OnObjectDisappearList;
	m_RobotMessageFuncList[g2c_char_walk] = &CRobotMessageHandler::OnCharWalk;
	m_RobotMessageFuncList[g2c_char_run] = &CRobotMessageHandler::OnCharRun;
	m_RobotMessageFuncList[g2c_sync_role_pos] = &CRobotMessageHandler::OnSyncRolePos;
	m_RobotMessageFuncList[g2c_char_passive_move] = &CRobotMessageHandler::OnCharPassiveMove;
	m_RobotMessageFuncList[g2c_char_die] = &CRobotMessageHandler::OnCharDie;
	m_RobotMessageFuncList[g2c_char_revive] = &CRobotMessageHandler::OnCharRevive;
	//m_RobotMessageFuncList[g2c_revive_response] = &CRobotMessageHandler::OnReviveResponse;
	m_RobotMessageFuncList[g2c_object_rotate] = &CRobotMessageHandler::OnObjectRotate;

	// spell
	m_RobotMessageFuncList[g2c_sync_attr_change] = &CRobotMessageHandler::OnSyncAttrChange;
	m_RobotMessageFuncList[g2c_role_learn_spell] = &CRobotMessageHandler::OnRoleLearnSpell;
	m_RobotMessageFuncList[g2c_char_prepare_spell] = &CRobotMessageHandler::OnCharPrepareSpell;
	m_RobotMessageFuncList[g2c_char_cast_spell] = &CRobotMessageHandler::OnCharCastSpell;
	m_RobotMessageFuncList[g2c_char_spell_effect] = &CRobotMessageHandler::OnCharSpellEffect;
	m_RobotMessageFuncList[g2c_role_cast_over] = &CRobotMessageHandler::OnCastOver;
	m_RobotMessageFuncList[g2c_new_aura] = &CRobotMessageHandler::OnNewAura;
	m_RobotMessageFuncList[g2c_aura_change] = &CRobotMessageHandler::OnAuraChange;
	m_RobotMessageFuncList[g2c_del_aura] = &CRobotMessageHandler::OnDelAura;
	m_RobotMessageFuncList[g2c_char_select_focus] = &CRobotMessageHandler::OnCharSelectFocus;

	// item
	m_RobotMessageFuncList[g2c_money_change] = &CRobotMessageHandler::OnMoneyChange;
	m_RobotMessageFuncList[g2c_item_change] = &CRobotMessageHandler::OnItemChange;
	m_RobotMessageFuncList[g2c_item_swap] = &CRobotMessageHandler::OnItemSwap;
	m_RobotMessageFuncList[g2c_item_delete] = &CRobotMessageHandler::OnItemDelete;

	m_RobotMessageFuncList[g2c_refine] = &CRobotMessageHandler::OnRefine;

	// chat
	m_RobotMessageFuncList[m2c_chat_message] = &CRobotMessageHandler::OnMSChatMsg;

	// title
	m_RobotMessageFuncList[g2c_sync_title] = &CRobotMessageHandler::OnSyncTitle;
	m_RobotMessageFuncList[g2c_add_title] = &CRobotMessageHandler::OnAddTitle;
	m_RobotMessageFuncList[g2c_del_title] = &CRobotMessageHandler::OnDelTitle;
    m_RobotMessageFuncList[g2c_sync_equip_title] = &CRobotMessageHandler::OnSyncEquipTitle;

	//scene
	m_RobotMessageFuncList[g2c_query_scene_difficulty] = &CRobotMessageHandler::OnQuerySceneDifficulty;
	//friend
	m_RobotMessageFuncList[m2c_friend_add] = &CRobotMessageHandler::OnMSFriendAdd;
	//score
	m_RobotMessageFuncList[g2c_scene_finish] = &CRobotMessageHandler::OnGSSceneFinish;
	m_RobotMessageFuncList[g2c_dungeon_finish_score] = &CRobotMessageHandler::OnGSDungeonFinishScore;
	m_RobotMessageFuncList[g2c_dungeon_reward] = &CRobotMessageHandler::OnGSDungeonReward;
	//quest
	m_RobotMessageFuncList[g2c_complete_quest] = &CRobotMessageHandler::OnCompleteQuest;
	//variables
	m_RobotMessageFuncList[g2c_update_variable] = &CRobotMessageHandler::OnUpdateVariable;

	//trade
	m_RobotMessageFuncList[g2c_trade_set_item] = &CRobotMessageHandler::OnGSTradeSetItem;
	m_RobotMessageFuncList[g2c_trade_set_money] = &CRobotMessageHandler::OnGSTradeSetMoney;
	m_RobotMessageFuncList[g2c_trade_state_change] = &CRobotMessageHandler::OnGSTradeStateChange;

	//team
	m_RobotMessageFuncList[m2c_team_join] = &CRobotMessageHandler::OnMSTeamJoin;
	m_RobotMessageFuncList[m2c_team_leave] = &CRobotMessageHandler::OnMSTeamLeave;
	m_RobotMessageFuncList[m2c_team_answer] = &CRobotMessageHandler::OnMSTeamAnswer;
	m_RobotMessageFuncList[m2c_team_add_member] = &CRobotMessageHandler::OnMSTeamAddMember;
	m_RobotMessageFuncList[m2c_team_remove_member] = &CRobotMessageHandler::OnMSTeamRemoveMember;
	m_RobotMessageFuncList[m2c_team_changeinfo] = &CRobotMessageHandler::OnMSTeamChangeInfo;
	m_RobotMessageFuncList[m2c_team_sync_memberinfo] = &CRobotMessageHandler::OnMSTeamSyncMemberInfo;
	m_RobotMessageFuncList[m2c_team_sync_memberstate] = &CRobotMessageHandler::OnMSTeamSyncMemberState;
	m_RobotMessageFuncList[g2c_team_sync_member] = &CRobotMessageHandler::OnGSTeamSyncMemberInfo;

	m_RobotMessageFuncList[g2c_battle_team_join] = &CRobotMessageHandler::OnGSBattleTeamJoin;
	m_RobotMessageFuncList[g2c_battle_team_add] = &CRobotMessageHandler::OnGSBattleTeamAddMember;
	m_RobotMessageFuncList[g2c_battle_team_remove] = &CRobotMessageHandler::OnGSBattleTeamRemoveMember;

	////arena_team
	//m_RobotMessageFuncList[m2c_join_arena_team] = &CRobotMessageHandler::OnJoinArenaTeam;
	//m_RobotMessageFuncList[m2c_join_arena_team_ask] = &CRobotMessageHandler::OnJoinArenaTeamAsk;
	//m_RobotMessageFuncList[m2c_leave_arena_team] = &CRobotMessageHandler::OnLeaveArenaTeam;
	//m_RobotMessageFuncList[m2c_arena_team_info] = &CRobotMessageHandler::OnArenaTeamInfo;

	//m_RobotMessageFuncList[m2c_join_arena_queue] = &CRobotMessageHandler::OnJoinArenaQueue;
	//m_RobotMessageFuncList[m2c_cancel_join_arena_ack] = &CRobotMessageHandler::OnCancelJoinArenaAck;
	//m_RobotMessageFuncList[m2c_join_arena_confirm_req] = &CRobotMessageHandler::OnJoinArenaConfirmReq;

	//battle
	m_RobotMessageFuncList[m2c_join_battle_queue] = &CRobotMessageHandler::OnJoinBattleQueue;
	m_RobotMessageFuncList[m2c_cancel_join_battle_ack] = &CRobotMessageHandler::OnCancelJoinBattleAck;
	m_RobotMessageFuncList[m2c_join_battle_confirm_req] = &CRobotMessageHandler::OnJoinBattleConfirmReq;

	//m_RobotMessageFuncList[m2c_sync_arena_score_for_role] = &CRobotMessageHandler::OnMSSyncArenaScoreForRole;
	//m_RobotMessageFuncList[m2c_sync_arena_score_for_team] = &CRobotMessageHandler::OnMSSyncArenaScoreForTeam;

    m_RobotMessageFuncList[g2c_complete_achievement] = &CRobotMessageHandler::OnGSCompleteAchievement;

    m_RobotMessageFuncList[g2c_shield_ack] = &CRobotMessageHandler::OnShieldRole;
    m_RobotMessageFuncList[g2c_unshield_ack] = &CRobotMessageHandler::OnUnshieldRole;

	// master 
	m_RobotMessageFuncList[g2c_sync_master] = &CRobotMessageHandler::OnMasterSync;
	m_RobotMessageFuncList[m2c_master_info] = &CRobotMessageHandler::OnMasterInfo;
	m_RobotMessageFuncList[m2c_master_sync_lvl] = &CRobotMessageHandler::OnMasterLvlUp;
	m_RobotMessageFuncList[m2c_master_recruit_list] = &CRobotMessageHandler::OnMSGetRecruitList;
	m_RobotMessageFuncList[m2c_master_get_solo_list_ack] = &CRobotMessageHandler::OnMSGetSoloList;
	m_RobotMessageFuncList[m2c_master_stud_submit_app_ack] = &CRobotMessageHandler::OnMSApplyTeacherAck;
	m_RobotMessageFuncList[m2c_master_stud_submit_app_ntf] = &CRobotMessageHandler::OnMSApplyTeacherNtf;
	m_RobotMessageFuncList[m2c_master_agree_stud_app_ack] = &CRobotMessageHandler::OnMSTeacherAgreeAppAck;

	m_RobotMessageFuncList[m2c_master_add_student_ntf] = &CRobotMessageHandler::OnMSTeacherAddStudent;
	m_RobotMessageFuncList[m2c_master_del_student_ntf] = &CRobotMessageHandler::OnMSTeacherDelStudent;

	m_RobotMessageFuncList[m2c_master_refuse_stud_app_ack] = &CRobotMessageHandler::OnMSTeacherRefuseAppAck;
	m_RobotMessageFuncList[m2c_master_refuse_stud_app_ntf] = &CRobotMessageHandler::OnMSStudBeRefusedAppAck;
	m_RobotMessageFuncList[m2c_master_cancel_stud_app_ack] = &CRobotMessageHandler::OnMSSoloCancelAppAck;
	m_RobotMessageFuncList[m2c_master_cancel_stud_app_ntf] = &CRobotMessageHandler::OnMSSoloCancelAppNtf;
	m_RobotMessageFuncList[m2c_master_teacher_submit_app_ack] = &CRobotMessageHandler::OnMSApplyToSoloAck;
	m_RobotMessageFuncList[m2c_master_teacher_submit_app_ntf] = &CRobotMessageHandler::OnMSApplyToSoloNtf;
	m_RobotMessageFuncList[m2c_master_agree_teacher_app_ack] = &CRobotMessageHandler::OnMSSoloAgreeAppAck;
	m_RobotMessageFuncList[m2c_master_refuse_teacher_app_ack] = &CRobotMessageHandler::OnMSSoloRefuseAppAck;
	m_RobotMessageFuncList[m2c_master_refuse_teacher_app_ntf] = &CRobotMessageHandler::OnMSSoloRefuseAppNtf;
	m_RobotMessageFuncList[m2c_master_cancel_teacher_app_ack] = &CRobotMessageHandler::OnMSTeacherCancelAppAck;
	m_RobotMessageFuncList[m2c_master_cancel_teacher_app_ntf] = &CRobotMessageHandler::OnMSTeacherCancelAppNtf;

	m_RobotMessageFuncList[m2c_master_clear_info] = &CRobotMessageHandler::OnMSStudentClear;
	m_RobotMessageFuncList[m2c_master_leave_teacher_ack] = &CRobotMessageHandler::OnMSStudentLeaveTeacherAck;
	m_RobotMessageFuncList[m2c_master_leave_teacher_ntf] = &CRobotMessageHandler::OnMSStudentLeaveTeacherNtf;
	m_RobotMessageFuncList[m2c_master_fire_student_ack] = &CRobotMessageHandler::OnMSFireStudentAck;
	m_RobotMessageFuncList[m2c_master_fire_student_ntf] = &CRobotMessageHandler::OnMSFireStudentNtf;
	m_RobotMessageFuncList[m2c_master_cz_ack] = &CRobotMessageHandler::OnMSMasterCZAck;
	m_RobotMessageFuncList[m2c_master_cz_level] = &CRobotMessageHandler::OnMSCZCount;
	m_RobotMessageFuncList[m2c_master_grad] = &CRobotMessageHandler::OnMSAgreeGraduate;

	m_RobotMessageFuncList[m2c_query_guild_name_ack] = &CRobotMessageHandler::OnMSGQueryInfo;
	m_RobotMessageFuncList[m2c_create_guild_ack] = &CRobotMessageHandler::OnMSCreateGuildAck;
	m_RobotMessageFuncList[m2c_view_guild_list_ack] = &CRobotMessageHandler::OnMSGViewListAck;
	m_RobotMessageFuncList[m2c_more_guild_info_ack] = &CRobotMessageHandler::OnMSGMoreInfoAck;
	m_RobotMessageFuncList[m2c_find_guild_ack] = &CRobotMessageHandler::OnMSGFindAck;
	m_RobotMessageFuncList[m2c_guild_info_ntf] = &CRobotMessageHandler::OnMSGuildInfo;
	m_RobotMessageFuncList[m2c_apply_to_join_guild_ack] = &CRobotMessageHandler::OnMSGApplyToJoinAck;
	m_RobotMessageFuncList[m2c_get_apply_guild_list_ack] = &CRobotMessageHandler::OnMSGuildGetAppList;
	m_RobotMessageFuncList[m2c_revert_guild_apply_ack] = &CRobotMessageHandler::OnMSGRevertAppAck;
	m_RobotMessageFuncList[m2c_del_guild_app] = &CRobotMessageHandler::OnMSGuildDelGuildApp;
	m_RobotMessageFuncList[m2c_guild_add_member_ntf] = &CRobotMessageHandler::OnMSAddMemberNtf;
	m_RobotMessageFuncList[m2c_guild_del_member_ntf] = &CRobotMessageHandler::OnMSDelMemberNtf;
	m_RobotMessageFuncList[m2c_be_invited_to_join_guild] = &CRobotMessageHandler::OnMSGInviteToJoinGuild;
	m_RobotMessageFuncList[m2c_invite_to_join_guild_ack] = &CRobotMessageHandler::OnMSGRevertGuildInvitationAck;
	m_RobotMessageFuncList[m2c_disband_guild_ntf] = &CRobotMessageHandler::OnMSGuildDisband;
	m_RobotMessageFuncList[m2c_guild_notice_change] = &CRobotMessageHandler::OnMSGuildChangeNotice;
	m_RobotMessageFuncList[m2c_guild_change_position_ntf] = &CRobotMessageHandler::OnMSGuildChangePosition;
	m_RobotMessageFuncList[m2c_guild_role_leave_ntf] = &CRobotMessageHandler::OnMSDelMemberNtf;
	m_RobotMessageFuncList[m2c_guild_role_leave_ack] = &CRobotMessageHandler::OnMSGuildLeaveGuildAck;
	m_RobotMessageFuncList[m2c_guild_demise_ntf] = &CRobotMessageHandler::OnMSDemise;
	m_RobotMessageFuncList[m2c_guild_contribute_ack] = &CRobotMessageHandler::OnGuildCongAck;
	m_RobotMessageFuncList[m2c_guild_attr_modify_ntf] = &CRobotMessageHandler::OnGuildAttrModifyAck;
    m_RobotMessageFuncList[m2c_guild_get_apply_union_list_ack] = &CRobotMessageHandler::OnGuildGetUnionAppListAck;


	// achievement
	m_RobotMessageFuncList[g2c_complete_achievement] = &CRobotMessageHandler::OnCompleteAchievement;
	m_RobotMessageFuncList[g2c_compare_achievement] = &CRobotMessageHandler::OnCompareAchievement;
	m_RobotMessageFuncList[g2c_reward_achievement] = &CRobotMessageHandler::OnRewardAchievement; 
	m_RobotMessageFuncList[g2c_update_achievement_variable] = &CRobotMessageHandler::OnUpdateAchievementVariable; 
	m_RobotMessageFuncList[g2c_sync_achievement_list] = &CRobotMessageHandler::OnSyncAchievementList;
	m_RobotMessageFuncList[g2c_activate_hankbook] = &CRobotMessageHandler::OnActivateHandBook;

	// spirit
	m_RobotMessageFuncList[g2c_spirit_blood_open] = &CRobotMessageHandler::OnSpiritBloodOpen;
	m_RobotMessageFuncList[g2c_spirit_exp_change] = &CRobotMessageHandler::OnSpiritExpChange;
	m_RobotMessageFuncList[g2c_spirit_up] = &CRobotMessageHandler::OnSpiritUp;
	m_RobotMessageFuncList[g2c_spirit_air_change] = &CRobotMessageHandler::OnSpiritAirChange;
	m_RobotMessageFuncList[g2c_spirit_air_levelup] = &CRobotMessageHandler::OnSpiritAirLevelUp;
	m_RobotMessageFuncList[g2c_spirit_slot_size_change] = &CRobotMessageHandler::OnSpiritSlotSizeChange;
	m_RobotMessageFuncList[g2c_spirit_brush_slot] = &CRobotMessageHandler::OnSpiritBrushSlot;
	m_RobotMessageFuncList[g2c_spirit_notify_exp_change_time] = &CRobotMessageHandler::OnSpiritNotiryExpChangeTime;

	// hero
	m_RobotMessageFuncList[g2c_hire_hero] = &CRobotMessageHandler::OnHireHero;
	m_RobotMessageFuncList[g2c_hero_level_up] = &CRobotMessageHandler::OnHeroLevelUp;

	// Soul forging
	m_RobotMessageFuncList[g2c_rune_item] = &CRobotMessageHandler::OnRuneItem;

	// vip
	m_RobotMessageFuncList[g2c_sync_vip_state] = &CRobotMessageHandler::OnSyncVipState;
	m_RobotMessageFuncList[g2c_sync_vip_level] = &CRobotMessageHandler::OnSyncVipLevel;

	// mail
	m_RobotMessageFuncList[m2c_mail_write_success] = &CRobotMessageHandler::OnMailWriteSuccess;
	m_RobotMessageFuncList[m2c_mail_list_recv] = &CRobotMessageHandler::OnMailListRecv;
	m_RobotMessageFuncList[m2c_mail_read] = &CRobotMessageHandler::OnMailRead;
	m_RobotMessageFuncList[m2c_mail_delete_success] = &CRobotMessageHandler::OnMailDeleteSuccess;
	m_RobotMessageFuncList[m2c_mail_new_count] = &CRobotMessageHandler::OnMailNewCount;
	m_RobotMessageFuncList[m2c_mail_get_attach_success] = &CRobotMessageHandler::OnMailGetAttachSuccess;

	// auction
	m_RobotMessageFuncList[m2c_auction_search_type] = &CRobotMessageHandler::OnAuctionSearchType;
	m_RobotMessageFuncList[m2c_auction_search] = &CRobotMessageHandler::OnAuctionSearch;
	m_RobotMessageFuncList[m2c_auction_query] = &CRobotMessageHandler::OnAuctionQuery;
	m_RobotMessageFuncList[m2c_auction_sell] = &CRobotMessageHandler::OnAuctionSell;
	m_RobotMessageFuncList[m2c_auction_cancel_sell] = &CRobotMessageHandler::OnAuctionCancelSell;
	m_RobotMessageFuncList[m2c_auction_buy] = &CRobotMessageHandler::OnAuctionBuy;
	m_RobotMessageFuncList[m2c_auction_finished] = &CRobotMessageHandler::OnAuctionFinished;
	m_RobotMessageFuncList[m2c_auction_list_my_selling] = &CRobotMessageHandler::OnAuctionListMySelling;
	m_RobotMessageFuncList[m2c_auction_list_my_buying] = &CRobotMessageHandler::OnAuctionListMyBuying;

	// mount
	m_RobotMessageFuncList[g2c_activate_mount] = &CRobotMessageHandler::OnActivateMount;
	m_RobotMessageFuncList[g2c_char_on_mount] = &CRobotMessageHandler::OnOnMount;
	m_RobotMessageFuncList[g2c_char_off_mount] = &CRobotMessageHandler::OnOffMount;


	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRobotMessageHandler::UnInit(void)
{
	m_poNotifier = NULL;
	m_pPacketAllocator = NULL;

	return TRUE;
}

void CRobotMessageHandler::OnSyncGameDataBegin(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SYNC_GAME_DATA_BEGIN * pMsg = (G2C_SYNC_GAME_DATA_BEGIN *)pData;
	LOG_PROCESS_ERROR(pMsg);

	poRole->SetLevel(pMsg->byLevel);
	poRole->SetClass(pMsg->byClass);

	poRole->SetSex(pMsg->bySex);
	poRole->SetX(ConvertCoordN2S(pMsg->wPosX));
	poRole->SetY(ConvertCoordN2S(pMsg->wPosY));
	poRole->SetZ(ConvertCoordN2S(pMsg->wPosZ));
	poRole->SetFaceDirection(pMsg->wFaceDirection);

	poRole->SetHome(pMsg->dwSceneID, poRole->GetX(), poRole->GetY(), poRole->GetZ());

	poRole->SetSceneTempID(pMsg->dwSceneTempID);
	poRole->SetSceneID(pMsg->dwSceneID);
	poRole->ChangePkMode(pMsg->byPkMode);

	switch (pMsg->byMoveState)
	{
	case CMS_STAND:
		poRole->Stand(TRUE);
		break;
	case CMS_DIE:
		poRole->SetHp(0);
		poRole->Die(0);
		break;
	default:
		CRI("error move state %d in sync game data begin", pMsg->byMoveState);
		break;
	}

	return;
Exit0:
	return;
}
void CRobotMessageHandler::OnSyncGameDataEnd(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_GAME_DATA_END* poRoleInfo = (G2C_SYNC_GAME_DATA_END*)pData;
	LOG_PROCESS_ERROR(poRole);

	return;
Exit0:
	return;
}

BOOL CRobotMessageHandler::_OnCharAppear(CRole* poRole, CHAR_APPEAR_DATA* pAppearData)
{
	INT32 nRetCode = 0;
	CCharacter* poChar = NULL;
	CRole* poNewRole = NULL;
	CNpc* poNewNpc = NULL;
	INT32 nReferCount = 0;

	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetScene());

	poChar = CGameWorld::GetInstance().FindCharacter(pAppearData->dwCharID);

	if (poChar == NULL)
	{
		if (GetTypeFromID(pAppearData->dwCharID) == otRole)
		{
			poNewRole = CGameWorld::GetInstance().NewRole(pAppearData->dwCharID);
			LOG_PROCESS_ERROR(poNewRole);

			DBG("role #%s:%d# <%08X> New a Role %d when _OnCharAppear() ",
				poRole->GetName(), poRole->GetObjID(), poRole->GetSessionID(), pAppearData->dwCharID);

			poChar = poNewRole;
		}
		else if (GetTypeFromID(pAppearData->dwCharID) == otNpc)
		{
			poNewNpc = CGameWorld::GetInstance().NewNpc(pAppearData->dwCharID);
			LOG_PROCESS_ERROR(poNewNpc);

			//DBG("role #%s:%d# <%08X> New a Npc %d when _OnCharAppear() ",
			//	poRole->GetName(), poRole->GetObjID(), poRole->GetSessionID(), pAppearData->dwCharID);

			poChar = poNewNpc;
		}
	}
	else
	{
		nReferCount = poChar->GetReferCount();
		//PROCESS_SUCCESS(poChar->GetObjType() == otRole && ((CRole*)poChar)->IsRobot());
		if (poChar->GetObjType() == otRole)
		{
			poNewRole = (CRole*)poChar;
			PROCESS_SUCCESS(poNewRole->IsRobot());
			{
				CScene* pScene = poNewRole->GetScene();
				if ( pScene )
				{
					pScene->RemoveRole(poNewRole);
				}
				nRetCode = poNewRole->UnInit();
				LOG_PROCESS_ERROR(nRetCode);

				DBG("role #%s:%d# <%08X> UnInit a Role %d when _OnCharAppear() ",
					poRole->GetName(), poRole->GetObjID(), poRole->GetSessionID(), pAppearData->dwCharID);
			}
		}
		if (poChar->GetObjType() == otNpc)
		{
			poNewNpc = ((CNpc*)poChar);

			CScene* pScene = poNewNpc->GetScene();
			if (pScene)
			{
				pScene->RemoveNpc(poNewNpc);
			}

			nRetCode = poNewNpc->UnInit();
			LOG_PROCESS_ERROR(nRetCode);

			//DBG("role #%s:%d# <%08X> UnInit a Npc %d when _OnCharAppear() ",
			//	poRole->GetName(), poRole->GetObjID(), poRole->GetSessionID(), pAppearData->dwCharID);
		}
	}
	LOG_PROCESS_ERROR(poChar);

	if (poNewRole)
	{
		nRetCode = poNewRole->Init(pAppearData->dwCharID, NULL);
		LOG_PROCESS_ERROR(nRetCode);
	}

	if (poNewNpc)
	{
		nRetCode = poNewNpc->Init(pAppearData->dwCharID, NULL, INVALID_OBJECT_ID);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = poNewNpc->SetTemplateData(0);
		LOG_PROCESS_ERROR(nRetCode);
	}

	poChar->SetX(ConvertCoordN2S(pAppearData->wCurrentX));
	poChar->SetY(ConvertCoordN2S(pAppearData->wCurrentY));
	poChar->SetZ(ConvertCoordN2S(pAppearData->wCurrentZ));
	poChar->GetAttrList().SetAttrBase(poChar, catMaxHp, 100);
	poChar->SetHp(pAppearData->byLifePercent);
	poChar->GetAttrList().SetAttrA(poChar, catWalkSpeed, 0);
	poChar->GetAttrList().SetAttrA(poChar, catRunSpeed, 0);

	if (poNewRole)
	{
		nRetCode = poRole->GetScene()->AddRole(poNewRole, 0);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = DoQueryRoleData(poRole, poNewRole);
		LOG_CHECK_ERROR(nRetCode);
	}

	if (poNewNpc)
	{
		nRetCode = poRole->GetScene()->AddNpc(poNewNpc, 0);
		LOG_PROCESS_ERROR(nRetCode);

		nRetCode = DoQueryNpcData(poRole, poNewNpc);
		LOG_CHECK_ERROR(nRetCode);
	}

	nRetCode = poChar->Stand(TRUE);
	LOG_PROCESS_ERROR(nRetCode);
	poChar->SetReferCount(nReferCount + 1);

Exit1:
	//INF("Char[%d] appear at [%d, %d, %d], template [%d, %d].",
	//    pAppearData->dwCharID, (INT32)(pAppearData->nCurrentX / POINT_PER_CM),
	//    (INT32)(pAppearData->nCurrentY / POINT_PER_CM), (INT32)(pAppearData->nCurrentZ / POINT_PER_CM),
	//    poRole->GetSceneTempID(), poRole->GetSceneID());

	return TRUE;
Exit0:
	if (poNewNpc)
	{
		CScene* pScene = poNewNpc->GetScene();
		if (pScene)
		{
			pScene->RemoveNpc(poNewNpc);
		}
		//INF("CRobotMessageHandler::_OnCharAppear() Exit0: UnInit poNewNpc %d", poNewNpc->GetObjID());
		poNewNpc->UnInit();
		CGameWorld::GetInstance().DelNpc(poNewNpc);
	}
	if (poNewRole)
	{
		CScene* pScene = poNewRole->GetScene();
		if (pScene)
		{
			pScene->RemoveRole(poNewRole);
		}
		INF("CRobotMessageHandler::_OnCharAppear() Exit0: UnInit poNewRole %d", poNewRole->GetObjID());
		poNewRole->UnInit();
		CGameWorld::GetInstance().DelRole(poNewRole);
	}
	return FALSE;
}

void CRobotMessageHandler::OnCharAppear(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CHAR_APPEAR * pMsg = (G2C_CHAR_APPEAR *)pData;

	nRetCode = _OnCharAppear(poRole, &(pMsg->stAppearData));
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncCharList(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_CHAR_LIST* pMsg = (G2C_SYNC_CHAR_LIST *)pData;
	UINT32 nCharCount = (pMsg->wSize - sizeof(G2C_SYNC_CHAR_LIST)) / sizeof(CHAR_APPEAR_DATA);
	CHAR_APPEAR_DATA* AppearDataList = pMsg->astAppearData;

	for (int nIndex = 0; nIndex < nCharCount; nIndex++)
	{
		nRetCode = _OnCharAppear(poRole, &(AppearDataList[nIndex]));
		LOG_PROCESS_ERROR(nRetCode);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnObjectDisappear(CRole* poRole, const char* pData)
{
	BOOL bRetCode = FALSE;
	BOOL bToDelete = FALSE;

	G2C_OBJECT_DISAPPEAR * pMsg = (G2C_OBJECT_DISAPPEAR *)pData;
	CCharacter * poChar = CGameWorld::GetInstance().FindCharacter(pMsg->dwObjID);
	PROCESS_SUCCESS(poChar == NULL);

	INT32 nIDType = GetTypeFromID(pMsg->dwObjID);
	if (nIDType == otRole)
	{
		CRole * poDisappearRole = (CRole *)poChar;
		if (!poDisappearRole->IsRobot())
		{
			if (pMsg->byDisappearType == sodtLeaveScene)
			{
				bToDelete = TRUE;
			}
			else if (pMsg->byDisappearType == sodtOutOfRange)
			{
				poDisappearRole->SetReferCount(poDisappearRole->GetReferCount() - 1);
				if (poDisappearRole->GetReferCount() <= 0)
				{
					bToDelete = TRUE;
				}
			}

			if (bToDelete &&poDisappearRole->GetScene())
			{
				poDisappearRole->GetScene()->RemoveRole(poDisappearRole);
				poDisappearRole->UnInit();
				CGameWorld::GetInstance().DelRole(poDisappearRole);
			}
		}
	}
	else if (nIDType == otNpc)
	{
		CNpc * poDisappearNpc = (CNpc *)poChar;
		//LOG_PROCESS_ERROR(poDisappearNpc->GetScene());
		if (pMsg->byDisappearType == sodtLeaveScene)
		{
			bToDelete = TRUE;
		}
		else if (pMsg->byDisappearType == sodtOutOfRange)
		{
			if (poDisappearNpc->GetReferCount() <= 1)
			{
				bToDelete = TRUE;
			}
		}
		if (bToDelete && poDisappearNpc->GetScene())
		{
			poDisappearNpc->GetScene()->RemoveNpc(poDisappearNpc);
			poDisappearNpc->UnInit();
			CGameWorld::GetInstance().DelNpc(poDisappearNpc);
		}
	}

Exit1:
	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnObjectDisappearList(CRole* poRole, const char* pData)
{
	G2C_OBJECT_DISAPPEAR_LIST * pMsg = (G2C_OBJECT_DISAPPEAR_LIST *)pData;
	INT32 nObjCount = (pMsg->wSize - sizeof(G2C_OBJECT_DISAPPEAR_LIST)) / sizeof(pMsg->dwObjIDList[0]);

	for (INT32 nIndex = 0; nIndex < nObjCount; nIndex++)
	{
		CSceneObject* poSceneObject = CGameWorld::GetInstance().FindObj(pMsg->dwObjIDList[nIndex]);
		PROCESS_SUCCESS(poSceneObject == NULL);

		INT32 nIDType = GetTypeFromID(pMsg->dwObjIDList[nIndex]);
		if (nIDType == otRole)
		{
		}
		else if (nIDType == otNpc)
		{
		}
	}

Exit1:
	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCharWalk(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CHAR_WALK * pMsg = (G2C_CHAR_WALK*)pData;

	CCharacter* poChar = CGameWorld::GetInstance().FindValidCharacter(pMsg->dwCharID);
	PROCESS_ERROR(poChar);

	if (poChar->GetObjType() == otRole)
	{
		CRole* poTempRole = (CRole*)poChar;

		PROCESS_ERROR(!poTempRole->IsRobot());
	}

	nRetCode = poChar->MoveTo(ConvertCoordN2S(pMsg->wDestX), ConvertCoordN2S(pMsg->wDestY));
	LOG_PROCESS_ERROR(nRetCode);

	//if (poChar->GetObjType() == otRole)
	//{
	//	DBG("char %s:%d walk to (%d, %d)", poRole->GetName(), poRole->GetObjID(),
	//		(INT32)(ConvertCoordN2S(pMsg->wDestX) / POINT_PER_CM), (INT32)(ConvertCoordN2S(pMsg->wDestY) / POINT_PER_CM));
	//}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCharRun(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CHAR_RUN * pMsg = (G2C_CHAR_RUN*)pData;

	CCharacter* poChar = CGameWorld::GetInstance().FindValidCharacter(pMsg->dwCharID);
	PROCESS_ERROR(poChar);

	if (poChar->GetObjType() == otRole)
	{
		CRole* poTempRole = (CRole*)poChar;

		PROCESS_ERROR(!poTempRole->IsRobot());
	}

	nRetCode = poChar->MoveTo(ConvertCoordN2S(pMsg->wDestX), ConvertCoordN2S(pMsg->wDestY));
	LOG_PROCESS_ERROR(nRetCode);

	//if (poChar->GetObjType() == otRole)
	//{
	//	DBG("char %s:%d run to (%d, %d)", poRole->GetName(), poRole->GetObjID(),
	//		(INT32)(ConvertCoordN2S(pMsg->wDestX) / POINT_PER_CM), (INT32)(ConvertCoordN2S(pMsg->wDestY) / POINT_PER_CM));
	//}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCharStop(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CHAR_STOP * pMsg = (G2C_CHAR_STOP*)pData;
	LOG_PROCESS_ERROR(poRole != NULL);

	CCharacter* poChar = CGameWorld::GetInstance().FindValidCharacter(pMsg->dwCharID);
	PROCESS_ERROR(poChar);

	if (poChar->GetObjType() == otRole)
	{
		CRole* poTempRole = (CRole*)poChar;

		if (poTempRole->IsRobot())
			PROCESS_ERROR(poTempRole == poRole);
	}

	nRetCode = poChar->MoveTo(ConvertCoordN2S(pMsg->wCurrentX), ConvertCoordN2S(pMsg->wCurrentY));
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnObjectRotate(CRole* poRole, const char* pData)
{
	G2C_OBJECT_ROTATE* pMsg = (G2C_OBJECT_ROTATE*)pData;

	CSceneObject* poSceneObject = CGameWorld::GetInstance().FindObj(pMsg->dwCharID);
	PROCESS_ERROR(poSceneObject);

	if (poSceneObject->GetObjType() == otRole)
	{
		CRole* poTempRole = (CRole*)poSceneObject;

		if (poTempRole->IsRobot())
			PROCESS_ERROR(poTempRole == poRole);
	}

	poSceneObject->RotateTo(pMsg->wFaceDirection, pMsg->wDuration);

Exit0:
	return;
}

void CRobotMessageHandler::OnCharPassiveMove(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CHAR_PASSIVE_MOVE * pMsg = (G2C_CHAR_PASSIVE_MOVE*)pData;

	LOG_PROCESS_ERROR(poRole != NULL);

	CCharacter* poChar = CGameWorld::GetInstance().FindValidCharacter(pMsg->dwCharID);
	PROCESS_ERROR(poChar);

	if (poChar->GetObjType() == otRole)
	{
		CRole* poTempRole = (CRole*)poChar;
		PROCESS_ERROR(poTempRole == poRole);
	}

	switch (pMsg->byMoveState)
	{
	case CMS_DASH:
		{
			nRetCode = poChar->Dash(pMsg->wDuration, ConvertCoordN2S(pMsg->wDestX), ConvertCoordN2S(pMsg->wDestY));
			PROCESS_ERROR(nRetCode);
		}
		break;
	case CMS_KNOCK_BACK:
		{
			nRetCode = poChar->KnockBack(pMsg->wDuration, ConvertCoordN2S(pMsg->wDestX), ConvertCoordN2S(pMsg->wDestY));
			PROCESS_ERROR(nRetCode);
		}
		break;
	case CMS_THROWN:
		{
			nRetCode = poChar->Thrown(pMsg->wDuration, ConvertCoordN2S(pMsg->wDestX), ConvertCoordN2S(pMsg->wDestY));
			PROCESS_ERROR(nRetCode);
		}
		break;
	default:
		LOG_PROCESS_ERROR(FALSE);
		break;
	}

	//if (poChar->GetObjType() == otRole)
	//{
	//    DBG("role %s:%d passive move to (%d, %d, %d)",poChar->GetName(), poChar->GetObjID(), 
	//        (INT32)(ConvertCoordN2S(pMsg->wDestX) / POINT_PER_CM),
	//        (INT32)(ConvertCoordN2S(pMsg->wDestY) / POINT_PER_CM),
	//        (INT32)(ConvertCoordN2S(pMsg->wDestZ) / POINT_PER_CM));
	//}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCharDie(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CHAR_DIE * pMsg = (G2C_CHAR_DIE*)pData;
	const SCENE_DATA* poSceneData = NULL;

	CCharacter* poChar = NULL;
	LOG_PROCESS_ERROR(poRole != NULL);

   poChar = CGameWorld::GetInstance().FindValidCharacter(pMsg->dwCharID);
   PROCESS_ERROR(poChar);

	//PROCESS_ERROR(poRole->GetObjID() == pMsg->dwCharID);
	//poRole->Die(pMsg->byType);

    if (poChar->GetObjType() == otRole)
    {
        CRole* poTempoRole = (CRole*)poChar;
        LOG_PROCESS_ERROR(poTempoRole);

		if (poTempoRole->IsRobot())
		{
			PROCESS_ERROR(poTempoRole == poRole);
			INF("role %s got self die when OnCharDie", poRole->GetName());
		}
    }

	if(poChar->GetMoveState() != CMS_DIE)
	{
		poChar->SetHp(0);
		poChar->Die(0);
		INF("char %s OnCharDie died", poChar->GetName());
	}
	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCharRevive(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CHAR_REVIVE * pMsg = (G2C_CHAR_REVIVE*)pData;
	LOG_PROCESS_ERROR(poRole != NULL);

	CCharacter* poChar = CGameWorld::GetInstance().FindValidCharacter(pMsg->dwCharID);
	if (poChar)
	{
		if (poChar->GetObjType() == otRole)
		{
			CRole* poTempRole = (CRole*)poChar;
			LOG_PROCESS_ERROR(poTempRole);

			if (poTempRole->IsRobot())
			{
				PROCESS_ERROR(poTempRole == poRole);
				INF("role %s got self revive when OnCharRevive", poRole->GetName());
			}
        }

		if (poChar->GetMoveState() == CMS_DIE)// else has been revived by other robot
		{
			nRetCode = poChar->Revive(pMsg->byType, RATE_MAX);
			LOG_PROCESS_ERROR(nRetCode);

			INF("char %s OnCharRevive revived", poChar->GetName());
		}
	}
	return;
Exit0:
	return;
}

//void CRobotMessageHandler::OnReviveResponse(CRole* pRole, const char* pData)
//{
//	G2C_REVIVE_RESPONSE* pMsg = (G2C_REVIVE_RESPONSE*)pData;
//
//	INF("role %s will revive in %d ms", pRole->GetName(), pMsg->nDelayTime);
//
//	return;
//}

void CRobotMessageHandler::OnSyncRoleData(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_ROLE_DATA * pMsg = (G2C_SYNC_ROLE_DATA*)pData;

	LOG_PROCESS_ERROR(poRole);

	CRole* poSyncRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poSyncRole);
	PROCESS_ERROR(!poSyncRole->IsRobot());

	poSyncRole->SetName(pMsg->szName);
	poSyncRole->SetSex(pMsg->bySex);
	poSyncRole->SetClass(pMsg->byClass);
	poSyncRole->SetLevel(20);
	poSyncRole->GetAttrList().SetAttrBase(poSyncRole, catMaxHp, pMsg->nMaxHp);
	poSyncRole->GetAttrList().SetAttrBase(poSyncRole, catMaxMp, pMsg->nMaxMp);
	poSyncRole->SetHp(pMsg->nMaxHp * poSyncRole->GetHp() / 100);

	if (s_RoleCache.RoleDataCache.size() >= MAX_ROBOT_CACHE_COUNT)
	{
		s_RoleCache.RoleDataCache.clear();
	}

	s_RoleCache.RoleDataCache[pMsg->dwRoleID] = *pMsg;

	if (0 != pMsg->dwGuildID)
	{
		nRetCode = DoQueryGuildInfo(poRole, pMsg->dwGuildID);
		LOG_CHECK_ERROR(nRetCode);
	}
Exit0:
	return;
}

void CRobotMessageHandler::OnRoleLevelUp(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_ROLE_LEVEL_UP * pMsg = (G2C_ROLE_LEVEL_UP*)pData;

	LOG_PROCESS_ERROR(pRole);

	CRole* poTargetRole = CGameWorld::GetInstance().FindRole(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(poTargetRole);

	if (poTargetRole->IsRobot())
	{
		if (poTargetRole == pRole)
		{
			poTargetRole->SetLevel(pMsg->byLevel);
		}
	}
	else
	{
		poTargetRole->SetLevel(pMsg->byLevel);
	}

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poTargetRole->GetAchievementList(), adLevel, 0);

Exit0:
	return;
}

void CRobotMessageHandler::OnSyncDropList(CRole* pRole, const char* pData)
{
	G2C_SYNC_DROP_LIST* pMsg = (G2C_SYNC_DROP_LIST*)pData;
	LOG_PROCESS_ERROR(pMsg);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncNpcData(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_NPC_DATA * pMsg = (G2C_SYNC_NPC_DATA*)pData;
	CNpc* poSyncNpc = NULL;

	LOG_PROCESS_ERROR(poRole);

	poSyncNpc = CGameWorld::GetInstance().FindNpc(pMsg->dwNpcID);
	PROCESS_ERROR(poSyncNpc);

	//nRetCode = poSyncNpc->SetTemplateData(pMsg->nTemplateID, pMsg->byQuality, poScene->GetSceneDifficulty());
	nRetCode = poSyncNpc->SetTemplateData(pMsg->nTemplateID);
	LOG_PROCESS_ERROR(nRetCode);
	poSyncNpc->GetAttrList().SetAttrBase(poSyncNpc, catMaxHp, pMsg->nMaxHp);
	poSyncNpc->SetHp(poSyncNpc->GetHp() * pMsg->nMaxHp / 100);
	poSyncNpc->GetAttrList().SetAttrA(poSyncNpc, catWalkSpeed, 0);
	poSyncNpc->GetAttrList().SetAttrA(poSyncNpc, catRunSpeed, 0);

	if (s_RoleCache.NpcDataCache.size() >= MAX_ROBOT_CACHE_COUNT)
	{
		s_RoleCache.NpcDataCache.clear();
	}
	s_RoleCache.NpcDataCache[pMsg->dwNpcID] = *pMsg;


    if (poRole->GetWaitNpcTemplateID() == pMsg->nTemplateID)
    {
        CLuaScript* poScript = CScriptMgr::GetInstance().FindScript("script/newai/robot/main.lua");
        if (poScript)
        {
            BOOL bRet = poScript->CallFunction(poRole->GetCBFuncName(), "o", poSyncNpc, "CNpc");
            LOG_CHECK_ERROR(bRet);
        }
        poRole->SetCBFuncName("");
        poRole->SetWaitNpcTemplateID(0);
    }

	return;
Exit0:
	if (poSyncNpc)
	{
		CScene* pScene = poSyncNpc->GetScene();
		if (pScene)
		{
			pScene->RemoveNpc(poSyncNpc);
		}
		CRI("CRobotMessageHandler::OnSyncNpcData() failed: remove NewNpc %d due to template %d", poSyncNpc->GetObjID(), pMsg->nTemplateID);
		poSyncNpc->UnInit();
		CGameWorld::GetInstance().DelNpc(poSyncNpc);
	}
	return;
}

void CRobotMessageHandler::OnSyncClientVariables(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_CLIENT_VARIABLES * pMsg = (G2C_SYNC_CLIENT_VARIABLES *)pData;

	LOG_PROCESS_ERROR(poRole);

	for (INT32 nIndex = 0; nIndex < MAX_CLIENT_VARIABLE_COUNT; nIndex++)
	{
		poRole->SetClientVariable(nIndex, pMsg->nVariableList[nIndex]);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncFrame(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_FRAME * pMsg = (G2C_SYNC_FRAME *)pData;
	LOG_PROCESS_ERROR(poRole != NULL);

	poRole->SetServerFrame(pMsg->nFrame);

	return;
Exit0:
	return;
}


void CRobotMessageHandler::OnEnterScene(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_ENTER_SCENE * pMsg = (G2C_ENTER_SCENE *)pData;
	CScene* poScene = NULL;
	LOG_PROCESS_ERROR(poRole != NULL);

	INF("role %d enter scene", poRole->GetObjID());

	poScene = CGameWorld::GetInstance().FindScene(MakeSceneObjID(pMsg->nSceneTempID, pMsg->nSceneID));
	if (poScene == NULL)
	{
		poScene = CGameWorld::GetInstance().NewScene(
			MakeSceneObjID(pMsg->nSceneTempID, pMsg->nSceneID));
		LOG_PROCESS_ERROR(poScene);

		nRetCode = poScene->Init(poRole->GetServerGroup(), pMsg->nSceneTempID, pMsg->nSceneID);
		LOG_PROCESS_ERROR(nRetCode);
	}
	LOG_PROCESS_ERROR(poScene != NULL);

	poRole->SetX(ConvertCoordN2S(pMsg->wX));
	poRole->SetY(ConvertCoordN2S(pMsg->wY));
	poRole->SetZ(ConvertCoordN2S(pMsg->wZ));

	nRetCode = poScene->AddRole(poRole, 0);
	LOG_PROCESS_ERROR(nRetCode);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adEnterScene, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adExplore, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnChangeSceneEnter(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CHANGESCENE_ENTER* pMsg = (G2C_CHANGESCENE_ENTER*)pData;
	UINT32 dwSessionID = 0;
	INT32 nSceneTempID = 0;
	INT32 nSceneID = 0;

	LOG_PROCESS_ERROR(poRole);

	dwSessionID = poRole->GetSessionID();
	nSceneTempID = pMsg->nSceneTempID;
	nSceneID = pMsg->nSceneID;

	poRole->SetSceneTempID(nSceneTempID);
	poRole->SetSceneID(nSceneID);
	poRole->SetX(ConvertCoordN2S(pMsg->wDestX));
	poRole->SetY(ConvertCoordN2S(pMsg->wDestY));
	poRole->SetZ(ConvertCoordN2S(pMsg->wDestZ));

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncMoney(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_MONEY* pMsg = (G2C_SYNC_MONEY*)pData;
	LOG_PROCESS_ERROR(poRole);

	for (INT32 i = 0; i < MONEYTYPE_COUNT; i++)
	{
		LOG_PROCESS_ERROR(pMsg->allMoneys[i] < (1LL << 31));
		poRole->GetItemBag()->AddMoney(i, (INT32)pMsg->allMoneys[i], MONEYLOG_INVALID, 0);
	}

	return;
Exit0:
	return;

}
void CRobotMessageHandler::OnSyncContainerSizes(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_CONTAINER_SIZES* pMsg = (G2C_SYNC_CONTAINER_SIZES*)pData;
	LOG_PROCESS_ERROR(poRole);


	poRole->GetItemBag()->Clear();
	for (UINT8 i = 0; i < CONSLOT_COUNT; i++)
		poRole->GetItemBag()->SetContainerSize(i, pMsg->abySizes[i]);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adBankSlotCount, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adBagSlotCount, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adItemBagSlotCount, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnContainerSizeChange(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CONTAINER_SIZE_CHANGE* pMsg = (G2C_CONTAINER_SIZE_CHANGE*)pData;

	pRole->GetItemBag()->SetContainerSize(pMsg->byConSlot, pMsg->byConSize);

	if (CONSLOT_BANK == pMsg->byConSlot)
	{
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adBankSlotCount, 0);
	}

	if (CONSLOT_DEFAULT == pMsg->byConSlot)
	{
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adBagSlotCount, 0);
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adItemBagSlotCount, 0);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncItemBag(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_ITEM_BAG* pMsg = (G2C_SYNC_ITEM_BAG*)pData;
	//LOG_PROCESS_ERROR(poRole);

	ItemInfo iteminfo;
	UINT32 itemlen = 0;
	const char* itembuf = pMsg->acItems;
	for (UINT8 i = 0; i < pMsg->byItemCount; i++)
	{
		itemlen = iteminfo.Load(itembuf);
		LOG_PROCESS_ERROR(itemlen > 0);
		itembuf += itemlen;
		poRole->GetItemBag()->OnItemChange(iteminfo);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMoneyChange(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_MONEY_CHANGE* pMsg = (G2C_MONEY_CHANGE*)pData;
	LOG_PROCESS_ERROR(poRole);

	LOG_PROCESS_ERROR(pMsg->llMoney < (1LL<<31) );
	poRole->GetItemBag()->AddMoney(pMsg->nMoneyType, (INT32)pMsg->llMoney, MONEYLOG_INVALID, 0);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adTotalMoneyType, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnItemChange(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_ITEM_CHANGE* pMsg = (G2C_ITEM_CHANGE*)pData;
	//LOG_PROCESS_ERROR(poRole);

	Item* item = NULL;
	const ITEM_DATA* pNewItemTemplate = NULL;
	const ITEM_DATA* pOldItemTemplate = NULL;

	BOOL bNewAddItem = FALSE;
	BOOL bNewAddEquip = FALSE;
	BOOL bEquipColorChange = FALSE;
	BOOL bItemLuckChange = FALSE;

	ItemInfo iteminfo;
	UINT32 itemlen = iteminfo.Load(pMsg->acItem);
	LOG_PROCESS_ERROR(itemlen > 0);

	//Achievement processing
	item = poRole->GetItemBag()->GetItem(iteminfo.m_byConSlot, iteminfo.m_byItemSlot);
	pNewItemTemplate = GetItemData(iteminfo.m_nTemplateID);
	LOG_PROCESS_ERROR(pNewItemTemplate);
	if (item == NULL)
	{
		//Item is NULL,
		bNewAddItem = TRUE;

		//Check luck increase
		if (iteminfo.m_byLuck > 0)
		{
			bItemLuckChange = TRUE;
		}

		if (pNewItemTemplate->m_byType == ITEMTYPE_EQUIP)
		{
			bNewAddEquip = TRUE;
			bEquipColorChange = TRUE;
		}
	}
	else
	{
		//Check luck increase
		if (iteminfo.m_byLuck != item->m_iteminfo.m_byLuck)
		{
			bItemLuckChange = TRUE;
		}

		//Check new item
		if (item->m_iteminfo.m_nCurDur < iteminfo.m_nCurDur)
		{
			bNewAddItem = TRUE;
			if (item->m_pTemplate->m_byType == ITEMTYPE_EQUIP)
			{
				bNewAddEquip = TRUE;
			}
		}

		//Check equipment quality change
		pOldItemTemplate = GetItemData(item->m_iteminfo.m_nTemplateID);
		LOG_PROCESS_ERROR(pOldItemTemplate);
		if ((pOldItemTemplate->m_byColor != pNewItemTemplate->m_byColor) 
			&& (item->m_pTemplate->m_byType == ITEMTYPE_EQUIP))
		{
			bEquipColorChange = TRUE;
		}
	}

	poRole->GetItemBag()->OnItemChange(iteminfo);


	if (bNewAddItem)
	{
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adGetItem, 0);
	}
	if (bNewAddEquip)
	{
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adEquip, 0);
	}
	if (bEquipColorChange)
	{
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adEquipColor, 0);
	}
	if (bItemLuckChange)
	{
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adItemLuck, 0);
	}

Exit0:
	return;
}

void CRobotMessageHandler::OnMSFriendList(CRole* poRole, const char* pData)
{
	M2C_FRIEND_LIST* pMsg = (M2C_FRIEND_LIST*)pData;

	return;
}

void CRobotMessageHandler::OnMSFriendAdd(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	M2C_FRIEND_ADD* pMsg = (M2C_FRIEND_ADD*)pData;
	LOG_PROCESS_ERROR(pRole);

	pRole->GetFriend()->AddFriend(0, pMsg->dwRoleID);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adFriendCount, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnItemSwap(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_ITEM_SWAP* pMsg = (G2C_ITEM_SWAP*)pData;
	LOG_PROCESS_ERROR(poRole);

	poRole->GetItemBag()->OnItemSwap(pMsg->bySrcConSlot, pMsg->bySrcItemSlot, pMsg->byDstConSlot, pMsg->byDstItemSlot);

	if (CONSLOT_EQUIPPED == pMsg->byDstConSlot)
	{
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adEquipBodyColor, 0);
	}

	return;
Exit0:
	return;

}
void CRobotMessageHandler::OnItemDelete(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_ITEM_DELETE* pMsg = (G2C_ITEM_DELETE*)pData;
	LOG_PROCESS_ERROR(poRole);

	poRole->GetItemBag()->OnItemDelete(pMsg->byConSlot, pMsg->byItemSlot);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnRefine(CRole* pRole, const char* pData)
{
	G2C_REFINE* pMsg = (G2C_REFINE*)pData;
	LOG_PROCESS_ERROR(pRole);

	if (errSuccess == pMsg->byResult)
	{
		pRole->GetItemBag()->SetRefineLevel(pMsg->bySlot, pMsg->wRefineLevel);
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adItemRefine, 0);
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adRefineLevel, 0);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSChatMsg(CRole* poRole, const char* pData)
{
	INT32       nRetCode = 0;
	CUser       *poUser = NULL;
	char        szRoleName[ROLE_NAME_LEN] = { 0 };

	M2C_CHAT_MESSAGE    *pMsg = (M2C_CHAT_MESSAGE*)pData;
	LOG_PROCESS_ERROR(pMsg);

	strxcpy(szRoleName, (pMsg->szMessage + strlen(pMsg->szMessage) + 1), ROLE_NAME_LEN);

	if (GetTypeFromID(pMsg->dwSrcID) == otRole)
		CGeneralMgr::GetInstance().AddRandRole(pMsg->dwSrcID, szRoleName);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncTitle(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_TITLE* pMsg = (G2C_SYNC_TITLE*)pData;
	LOG_PROCESS_ERROR(poRole);

	for (UINT8 i = 0; i < pMsg->nTitleCount; ++i)
	{
		poRole->GetTitle().OnAddTitle(pMsg->stTitleList[i].m_nTemplateID, pMsg->stTitleList[i].m_nExpireTime);
	}
	poRole->GetTitle().OnEquipTitle(pMsg->nEquipedTitleID);
	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnAddTitle(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_ADD_TITLE* pMsg = (G2C_ADD_TITLE*)pData;
	LOG_PROCESS_ERROR(poRole);

	poRole->GetTitle().OnAddTitle(pMsg->nTitleID, pMsg->nExpireTime);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adTitle, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adTitleCount, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnDelTitle(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_DEL_TITLE* pMsg = (G2C_DEL_TITLE*)pData;
	LOG_PROCESS_ERROR(poRole);

	poRole->GetTitle().OnAddTitle(pMsg->nTitleID, pMsg->nDelType);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncEquipTitle(CRole* poRole, const char* pData)
{
    INT32 nRetCode = 0;
    G2C_SYNC_EQUIP_TITLE* pMsg = (G2C_SYNC_EQUIP_TITLE*)pData;
    LOG_PROCESS_ERROR(poRole);

    if (poRole->GetObjID() == pMsg->dwRoleID)
    {
        poRole->GetTitle().OnEquipTitle(pMsg->byTitleID);
    }

    return;
Exit0:
    return;
}

void CRobotMessageHandler::OnSyncRolePos(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_SYNC_ROLE_POS * pMsg = (G2C_SYNC_ROLE_POS *)pData;

	WRN("[%4d]role %d sync pos (%d, %d, %d)", CGameWorld::GetInstance().GetGameFrame(), poRole->GetObjID(),
		(INT32)(ConvertCoordN2S(pMsg->wCurrentX) / POINT_PER_CM),
		(INT32)(ConvertCoordN2S(pMsg->wCurrentY) / POINT_PER_CM),
		(INT32)(ConvertCoordN2S(pMsg->wCurrentZ) / POINT_PER_CM));

	LOG_PROCESS_ERROR(poRole->GetScene());

	nRetCode = poRole->JumpTo(ConvertCoordN2S(pMsg->wCurrentX),
		ConvertCoordN2S(pMsg->wCurrentY), ConvertCoordN2S(pMsg->wCurrentZ), pMsg->wFaceDirection);
	LOG_PROCESS_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncSpellBook(CRole* poRole, const char* pData)
{
	G2C_SYNC_SPELL_BOOK * pMsg = NULL;
	LOG_PROCESS_ERROR(poRole != NULL);
	pMsg = (G2C_SYNC_SPELL_BOOK *)pData;
	UINT32 dwMsgSize = pMsg->wSize;

	UINT32 nSpellCount = (dwMsgSize - sizeof(FLEX_MESSAGE_HEADER)) / sizeof(SPELL_DATA);
	SPELL_DATA* SpellDataList = pMsg->astSpellData;

	for (INT32 nIdx = 0; nIdx < nSpellCount; ++nIdx)
	{
		CSpellSet* poSet = NULL;

		poRole->LearnSpell(SpellDataList[nIdx].wID, SpellDataList[nIdx].bySpellLevel, FALSE);
	}

	poRole->GetSpellBook().BeginSpellSet();

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncSpellSlot(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	CSpellSlot* poSpellSlot = NULL;

	G2C_SYNC_SPELL_SLOT * pMsg = (G2C_SYNC_SPELL_SLOT*)pData;
	LOG_PROCESS_ERROR(poRole != NULL);

	for (INT32 i = qssSlotBegin; i < qssSlotCount; ++i)
	{
		if (pMsg->astSlot[i].byLocked)
			continue;

		nRetCode = poRole->UnlockSpellSlot(i);
		LOG_CHECK_ERROR(nRetCode);

		poSpellSlot = poRole->GetSpellSlot(pMsg->astSlot[i].bySlotID);
		LOG_PROCESS_ERROR(poSpellSlot);

		poSpellSlot->Equip(poRole, pMsg->astSlot[i].wSpellID);
	}
	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCharEquipSpell(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	CSpellSlot* poSpellSlot = NULL;
	G2C_EQUIP_SPELL * pMsg = (G2C_EQUIP_SPELL*)pData;
	LOG_PROCESS_ERROR(pRole != NULL);

	pRole->UnlockSpellSlot(pMsg->bySlot);

	poSpellSlot = pRole->GetSpellSlot(pMsg->bySlot);
	LOG_PROCESS_ERROR(poSpellSlot);

	poSpellSlot->Equip(pRole, pMsg->wSpellID);
	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnRoleLearnSpell(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_ROLE_LEARN_SPELL * pMsg = (G2C_ROLE_LEARN_SPELL *)pData;
	LOG_PROCESS_ERROR(poRole != NULL);

	if (poRole->GetObjID() != pMsg->dwRoleID)
	{
		return;
	}

	nRetCode = poRole->LearnSpell(pMsg->wSpellID, pMsg->bySpellLevel, FALSE);
	LOG_PROCESS_ERROR(nRetCode);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adSpellLevelSpecified, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adSpellLevel, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adLearnSpell, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adSpellCount, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adActiveSpellCount, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adEquipPassiveSpellCount, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adEquipPassiveSpellIDCount, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCharPrepareSpell(CRole* poRole, const char* pData)
{
	LOG_PROCESS_ERROR(poRole != NULL);

	CSpellTemplate* t = NULL;
	CSpellInstance* s = NULL;
	INT32 nCurFrame = CGameWorld::GetInstance().GetGameFrame();

	G2C_CHAR_PREPARE_SPELL * pMsg = (G2C_CHAR_PREPARE_SPELL*)pData;
	PROCESS_ERROR(pMsg->dwCasterID == poRole->GetObjID());

	t = CSpellConfig::GetInstance().FindSpellTemplate(pMsg->wSpellID, pMsg->bySpellLevel, pMsg->byRuneSlot);
	LOG_PROCESS_ERROR(t);

	PROCESS_ERROR(t->GetAttr(satCastType) == spctActive);//

	s = CGameWorld::GetInstance().NewSpellInstance();
	LOG_PROCESS_ERROR(s);

	s->Init(t, poRole, pMsg->dwCasterID, 0, poRole->GetX(), poRole->GetY(), poRole->GetZ());
	s->GetScanner().SetTargetPt(pMsg->wTargetX, pMsg->wTargetY, pMsg->wTargetZ);

	poRole->SetCastingSpell(s, nCurFrame + 10 * GAME_FPS);
	//poRole->SetCastingSpell(s);

	//DBG("role %s SetCastingSpell %d when OnCharPrepareSpell", poRole->GetName(), s->GetID() );

	return;
Exit0:
	return;

}

void CRobotMessageHandler::OnCharCastSpell(CRole* poRole, const char* pData)
{
	G2C_CHAR_CAST_SPELL * pMsg = (G2C_CHAR_CAST_SPELL *)pData;
	LOG_PROCESS_ERROR(poRole != NULL);

	PROCESS_ERROR(pMsg->SpellCastInfo.dwCasterID == poRole->GetObjID());

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCharSpellEffect(CRole* poRole, const char* pData)
{
	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCastOver(CRole* poRole, const char* pData)
{
	CSpellInstance* s = NULL;

	G2C_ROLE_CAST_OVER* pMsg = (G2C_ROLE_CAST_OVER*)pData;
	LOG_PROCESS_ERROR(poRole != NULL);

	s = poRole->GetCastingSpell();
	LOG_PROCESS_ERROR(s);

	//DBG("role %s OnCastOver, SetCastingSpell %d null", poRole->GetName(), s->GetID());

	s->Release();

	poRole->SetCastingSpell(NULL);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnBreakCast(CRole* poRole, const char* pData)
{
	CSpellInstance* s = NULL;

	G2C_CHAR_BREAK_CAST* pMsg = (G2C_CHAR_BREAK_CAST*)pData;
	LOG_PROCESS_ERROR(poRole != NULL);

	s = poRole->GetCastingSpell();
	LOG_PROCESS_ERROR(s);

	INF("Break Cast: %d, [%u]", s->GetID(), poRole->GetObjID());

	return;
Exit0:
	return;
}



void CRobotMessageHandler::OnNewAura(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_NEW_AURA* pMsg = (G2C_NEW_AURA*)pData;

	CAuraList& AuraList = poRole->GetAuraList();
	PROCESS_ERROR(poRole->GetObjID() == pMsg->dwCharID);

	CAuraTemplate* poAuraInfo = NULL;
	CAuraInstance* poAura = CGameWorld::GetInstance().NewAuraInstance();
	LOG_PROCESS_ERROR(poAura);

	poAuraInfo = CSpellConfig::GetInstance().FindAuraTemplate(pMsg->wAuraID);
	LOG_PROCESS_ERROR(poAuraInfo);

	nRetCode = poAura->Init(poAuraInfo, NULL, NULL, pMsg->dwCasterID, pMsg->dwInstanceID, pMsg->byStackCount);
	LOG_PROCESS_ERROR(nRetCode);

	nRetCode = AuraList.AddNewAura(poAura);
	LOG_PROCESS_ERROR(nRetCode);

	DBG("add aura: %u, id: %d", pMsg->dwInstanceID, pMsg->wAuraID);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnAuraChange(CRole* poRole, const char* pData)
{

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnDelAura(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_DEL_AURA* pMsg = (G2C_DEL_AURA*)pData;

	CAuraList& AuraList = poRole->GetAuraList();
	PROCESS_ERROR(poRole->GetObjID() == pMsg->dwCharID);

	CAuraInstance* poAura = poRole->GetAura(pMsg->dwInstanceID);
	LOG_PROCESS_ERROR(poAura);

	poRole->RemoveAura(poAura, FALSE);

	DBG("del aura: %u", pMsg->dwInstanceID);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCharSelectFocus(CRole* poRole, const char* pData)
{
	G2C_CHAR_SELECT_FOCUS* pMsg = (G2C_CHAR_SELECT_FOCUS*)pData;

	CCharacter* poChar = CGameWorld::GetInstance().FindValidCharacter(pMsg->dwCharID);
	LOG_PROCESS_ERROR(poChar);

	poChar->SelectFocus(pMsg->dwFocusID);

Exit0:
	return;
}


void CRobotMessageHandler::OnSyncAttrList(CRole* poRole, const char* pData)
{
	G2C_SYNC_ATTR_LIST* pMsg = (G2C_SYNC_ATTR_LIST*)pData;

	for (INT32 i = catDefault + 1; i < catTotal; i++)
	{
		poRole->GetAttrList().SetAttrBase((CCharacter*)poRole, i, pMsg->astAttrData[i].nAttrValue);
	}

	return;
}

void CRobotMessageHandler::OnSyncAttrChange(CRole* poRole, const char* pData)
{
	G2C_SYNC_ATTR_CHANGE* pMsg = (G2C_SYNC_ATTR_CHANGE*)pData;

	poRole->GetAttrList().SetAttrBase((CCharacter*)poRole, pMsg->byAttrID, pMsg->nAttrValue);

	return;
}

void CRobotMessageHandler::OnSyncFaction(CRole* poRole, const char* pData)
{
	G2C_SYNC_FACTION* pMsg = (G2C_SYNC_FACTION*)pData;

	poRole->SetFaction(pMsg->byFaction);
	return;
}

void CRobotMessageHandler::OnSyncPkMode(CRole* pRole, const char* pData)
{
	G2C_SYNC_PK_MODE* pMsg = (G2C_SYNC_PK_MODE*)pData;

	if (pRole->GetObjID() == pMsg->dwRoleID && pRole->IsRobot())
		pRole->ChangePkMode(pMsg->byPkMode);
	else
	{
		CRole* poTargetRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
		LOG_PROCESS_ERROR(poTargetRole);

		poTargetRole->ChangePkMode(pMsg->byPkMode);
	}

Exit0:
	return;
}

void CRobotMessageHandler::OnSyncPkValue(CRole* pRole, const char* pData)
{
	G2C_SYNC_PK_VALUE* pMsg = (G2C_SYNC_PK_VALUE*)pData;

	LOG_PROCESS_ERROR(pRole);

	if (pRole->GetObjID() == pMsg->dwRoleID && pRole->IsRobot())
	{
		pRole->SetPkValue(pMsg->dwPkValue);

		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adPkValue, 0);
	}
	else
	{
		CRole* poTargetRole = CGameWorld::GetInstance().FindValidRole(pMsg->dwRoleID);
		LOG_PROCESS_ERROR(poTargetRole);
		poTargetRole->SetPkValue(pMsg->dwPkValue);
	}


	return;
Exit0:
	return;
}

//////////////////////////////////////////////////////////////////////////
// master
//////////////////////////////////////////////////////////////////////////
void CRobotMessageHandler::OnMasterSync(CRole *poRole, const char *pData)
{
	INT32   nRetCode = 0;
	G2C_SYNC_MASTER     *pMsg = (G2C_SYNC_MASTER*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().SetState(pMsg->byState);
	poRole->GetMaster().SetCD(pMsg->dwCD);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMasterInfo(CRole *poRole, const char *pData)
{
	INT32           nRetCode = 0;
	M2C_MASTER_INFO *pMsg = (M2C_MASTER_INFO*)pData;

	LOG_PROCESS_ERROR(poRole);

	//poRole->GetMaster().AsimovLoadTeacher(pMsg->dwTeacherID, pMsg->byCZCount);
    //
    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwTeacherID);
    LOG_CHECK_ERROR(nRetCode);

	for (INT32 i = 0; i < pMsg->byStudentNum; ++i)
	{
		nRetCode = poRole->GetMaster().AsimovLoadStudent(pMsg->arrInfo[i].dwStudentID, pMsg->arrInfo[i].byCZCount);
		LOG_PROCESS_ERROR(nRetCode);

        nRetCode = DoQueryRoleInfo(poRole, pMsg->arrInfo[i].dwStudentID);
        LOG_CHECK_ERROR(nRetCode);
	}

	{
		poRole->GetMaster().AsimovClearSendAppList();
		poRole->GetMaster().AsimovClearRecvAppList();
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMasterLvlUp(CRole *poRole, const char *pData)
{
	INT32           nRetCode = 0;
	M2C_MASTER_SYNC_LVL *pMsg = (M2C_MASTER_SYNC_LVL*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovUpdateLevel(pMsg->dwRoleID, pMsg->byLevel);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwRoleID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGetRecruitList(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_RECRUIT_LIST* pMsg = (M2C_MASTER_RECRUIT_LIST*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovClearRecruitList();
	for (INT32 i = 0; i < pMsg->byCount; ++i)
	{
		poRole->GetMaster().AsimovLoadRecuritList(pMsg->szListData[i].dwRoleID);

        nRetCode = DoQueryRoleInfo(poRole, pMsg->szListData[i].dwRoleID);
        LOG_CHECK_ERROR(nRetCode);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGetSoloList(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_GET_SOLO_LIST_ACK* pMsg = (M2C_MASTER_GET_SOLO_LIST_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovClearSoloList();
	for (INT32 i = 0; i < pMsg->byCount; ++i)
	{
		poRole->GetMaster().AsimovLoadSoloList(pMsg->szListData[i].dwRoleID);

        nRetCode = DoQueryRoleInfo(poRole, pMsg->szListData[i].dwRoleID);
        LOG_CHECK_ERROR(nRetCode);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSApplyTeacherAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_STUD_SUBMIT_APP_ACK* pMsg = (M2C_MASTER_STUD_SUBMIT_APP_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovAddSendAppList(pMsg->dwMasterID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwMasterID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSApplyTeacherNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_STUD_SUBMIT_APP_NTF* pMsg = (M2C_MASTER_STUD_SUBMIT_APP_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovAddRecvAppList(pMsg->dwRoleID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwRoleID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSTeacherAgreeAppAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_AGREE_STUD_APP_ACK* pMsg = (M2C_MASTER_AGREE_STUD_APP_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	//poRole->GetMaster().AddStudent(pMsg->dwStudentID);
	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSTeacherAddStudent(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_ADD_STUDENT_NTF* pMsg = (M2C_MASTER_ADD_STUDENT_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AddStudent(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSTeacherDelStudent(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_DEL_STUDENT_NTF* pMsg = (M2C_MASTER_DEL_STUDENT_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().DelStudent(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSTeacherRefuseAppAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_REFUSE_STUD_APP_ACK* pMsg = (M2C_MASTER_REFUSE_STUD_APP_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovDelRecvAppList(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSStudBeRefusedAppAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_REFUSE_STUD_APP_NTF* pMsg = (M2C_MASTER_REFUSE_STUD_APP_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovDelSendAppList(pMsg->dwTeacherID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwTeacherID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSSoloCancelAppAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_CANCEL_STUD_APP_ACK* pMsg = (M2C_MASTER_CANCEL_STUD_APP_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovDelSendAppList(pMsg->dwTeacherID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwTeacherID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSSoloCancelAppNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_CANCEL_STUD_APP_NTF* pMsg = (M2C_MASTER_CANCEL_STUD_APP_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovDelRecvAppList(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSApplyToSoloAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_TEACHER_SUBMIT_APP_ACK* pMsg = (M2C_MASTER_TEACHER_SUBMIT_APP_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovAddSendAppList(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSApplyToSoloNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_TEACHER_SUBMIT_APP_NTF* pMsg = (M2C_MASTER_TEACHER_SUBMIT_APP_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovAddRecvAppList(pMsg->dwTeacherID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwTeacherID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSSoloAgreeAppAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_AGREE_TEACHER_APP_ACK* pMsg = (M2C_MASTER_AGREE_TEACHER_APP_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwTeacherID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSSoloRefuseAppAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_REFUSE_TEACHER_APP_ACK* pMsg = (M2C_MASTER_REFUSE_TEACHER_APP_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovDelRecvAppList(pMsg->dwTeacherID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwTeacherID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSSoloRefuseAppNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_REFUSE_TEACHER_APP_NTF* pMsg = (M2C_MASTER_REFUSE_TEACHER_APP_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovDelSendAppList(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSTeacherCancelAppAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_CANCEL_TEACHER_APP_ACK* pMsg = (M2C_MASTER_CANCEL_TEACHER_APP_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovDelSendAppList(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSTeacherCancelAppNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_CANCEL_TEACHER_APP_NTF* pMsg = (M2C_MASTER_CANCEL_TEACHER_APP_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().AsimovDelRecvAppList(pMsg->dwTeacherID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwTeacherID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSStudentClear(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_CLEAR_INFO* pMsg = (M2C_MASTER_CLEAR_INFO*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().DelTeacher(poRole->GetMaster().GetTeacherID());
	poRole->GetMaster().SetState(MASTER_NONE);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSStudentLeaveTeacherAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_LEAVE_TEACHER_ACK* pMsg = (M2C_MASTER_LEAVE_TEACHER_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSStudentLeaveTeacherNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_LEAVE_TEACHER_NTF* pMsg = (M2C_MASTER_LEAVE_TEACHER_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().DelStudent(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);


	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSFireStudentAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_FIRE_STUDENT_ACK* pMsg = (M2C_MASTER_FIRE_STUDENT_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().DelStudent(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSFireStudentNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_FIRE_STUDENT_NTF* pMsg = (M2C_MASTER_FIRE_STUDENT_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().DelStudent(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSMasterCZAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_CZ_ACK* pMsg = (M2C_MASTER_CZ_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwTargetRoleID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSCZCount(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	//M2C_MASTER_CZ_COUNT* pMsg = (M2C_MASTER_CZ_COUNT*)pData;

	//LOG_PROCESS_ERROR(poRole);

	//poRole->GetMaster().AsimovUpdateCZCount(pMsg->dwRoleID, pMsg->byCZCount);

 //   nRetCode = DoQueryRoleInfo(poRole, pMsg->dwRoleID);
 //   LOG_CHECK_ERROR(nRetCode);


	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSDesireGraduateAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	//M2C_MASTER_DESIRE_GRAD_ACK* pMsg = (M2C_MASTER_DESIRE_GRAD_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSDesireGraduateNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	//M2C_MASTER_DESIRE_GRAD_NTF* pMsg = (M2C_MASTER_DESIRE_GRAD_NTF*)pData;

	//LOG_PROCESS_ERROR(poRole);

	//poRole->GetMaster().AsimovSetGraduateRoleID(pMsg->dwStudentID);

 //   nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
 //   LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSAgreeGraduate(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	M2C_MASTER_GRAD* pMsg = (M2C_MASTER_GRAD*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->GetMaster().DelStudent(pMsg->dwStudentID);

    nRetCode = DoQueryRoleInfo(poRole, pMsg->dwStudentID);
    LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}


// guild
void CRobotMessageHandler::OnMSGQueryInfo(CRole *poRole, const char *pData)
{
	INT32   nRetCode = 0;
	M2C_QUERY_GUILD_NAME_ACK    *pMsg = (M2C_QUERY_GUILD_NAME_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	if (s_RoleCache.GuildInfoCache.size() >= MAX_ROBOT_CACHE_COUNT)
	{
		s_RoleCache.GuildInfoCache.clear();
		s_RoleCache.GuildDataCache.clear();
	}

	s_RoleCache.GuildInfoCache[pMsg->dwGuildID] = crc32(0, (const Bytef*)pMsg, sizeof(M2C_QUERY_GUILD_NAME_ACK));
	s_RoleCache.GuildDataCache[pMsg->dwGuildID].dwGuildID = pMsg->dwGuildID;
	s_RoleCache.GuildDataCache[pMsg->dwGuildID].dwLeaderID = pMsg->dwLeaderID;
	s_RoleCache.GuildDataCache[pMsg->dwGuildID].dwCreateTime = pMsg->dwCreateTime;
	s_RoleCache.GuildDataCache[pMsg->dwGuildID].byMainLevel = pMsg->byMainLevel;
	s_RoleCache.GuildDataCache[pMsg->dwGuildID].byHouseLevel = pMsg->byHouseLevel;
	s_RoleCache.GuildDataCache[pMsg->dwGuildID].byMemberCount = pMsg->byMemberCount;
	s_RoleCache.GuildDataCache[pMsg->dwGuildID].bySabacState = pMsg->bySabacState;
	strxcpy(s_RoleCache.GuildDataCache[pMsg->dwGuildID].szGuildName, pMsg->szGuildName,
		sizeof(s_RoleCache.GuildDataCache[pMsg->dwGuildID].szGuildName));

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGuildInfo(CRole *poRole, const char *pData)
{
	INT32       nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;
	M2C_GUILD_INFO_NTF  *pMsg = (M2C_GUILD_INFO_NTF*)pData;

	LOG_PROCESS_ERROR(poRole);

	poRole->SetGuildID(pMsg->dwGuildID);

	poGSGuild = CGuildMgr::GetInstance().FindGuild(pMsg->dwGuildID);
	if (!poGSGuild)
	{
		poGSGuild = CGuildMgr::GetInstance().NewGuild(pMsg->dwGuildID);
		LOG_PROCESS_ERROR(poGSGuild);

		ASIMOV_GUILD_DATA       tempData;

		tempData.dwGuildID = pMsg->dwGuildID;
		strxcpy(tempData.szGuildName, pMsg->szGuildName, sizeof(tempData.szGuildName));
		tempData.byLevel = pMsg->byLevel;
		tempData.byMemberCount = pMsg->byMemberCount;
		tempData.dwGuildMoney = pMsg->dwGuildMoney;
		tempData.dwCreateTime = pMsg->dwCreateTime;
		tempData.dwLeaderID = pMsg->dwLeaderID;
		strxcpy(tempData.szLeaderName, pMsg->szLeaderName, sizeof(tempData.szLeaderName));
		strxcpy(tempData.szCreaterName, pMsg->szCreaterName, sizeof(tempData.szCreaterName));
		strxcpy(tempData.szNotice, pMsg->szNotice, sizeof(tempData.szNotice));
		for (INT32 i = 0; i < GUILD_POSITION_COUNT; ++i)
			tempData.wStorageRight[i] = pMsg->wStorageRight[i];

		tempData.stEventInfo;
		tempData.stChestInfo;

		tempData.byAllianceCount = pMsg->byAllianceCount;
		for (INT32 i = 0; i < GUILD_MAX_ALLIANCE_NUM && i < pMsg->byAllianceCount; ++i)
		{
			tempData.stAlliance[i].dwGuildID = pMsg->stAlliance[i].dwGuildID;
			tempData.stAlliance[i].byLevel = pMsg->stAlliance[i].byLevel;
			tempData.stAlliance[i].byMemberCount = pMsg->stAlliance[i].byMemberCount;
			tempData.stAlliance[i].byType = pMsg->stAlliance[i].byType;
			tempData.stAlliance[i].dwLastTime = pMsg->stAlliance[i].dwLastTime;
			strxcpy(tempData.stAlliance[i].szGuildName,
				pMsg->stAlliance[i].szGuildName, sizeof(tempData.stAlliance[i].szGuildName));

			nRetCode = DoQueryGuildInfo(poRole, tempData.stAlliance[i].dwGuildID);
			LOG_CHECK_ERROR(nRetCode);
		}

		tempData.byEnemyCount = pMsg->byEnemyCount;
		for (INT32 i = 0; i < GUILD_MAX_ENEMY_NUM && i < pMsg->byEnemyCount; ++i)
		{
			tempData.stEnemy[i].dwGuildID = pMsg->stEnemy[i].dwGuildID;
			tempData.stEnemy[i].byLevel = pMsg->stEnemy[i].byLevel;
			tempData.stEnemy[i].byMemberCount = pMsg->stEnemy[i].byMemberCount;
			tempData.stEnemy[i].byType = pMsg->stEnemy[i].byType;
			tempData.stEnemy[i].dwLastTime = pMsg->stEnemy[i].dwLastTime;
			strxcpy(tempData.stEnemy[i].szGuildName,
				pMsg->stEnemy[i].szGuildName, sizeof(tempData.stEnemy[i].szGuildName));

			nRetCode = DoQueryGuildInfo(poRole, tempData.stEnemy[i].dwGuildID);
			LOG_CHECK_ERROR(nRetCode);
		}

		tempData.nHerb = pMsg->nHerb;
		tempData.nWood = pMsg->nWood;
		tempData.nCrystal = pMsg->nCrystal;
		tempData.nSilver = pMsg->nSilver;
		tempData.nProsperity = pMsg->nProsperity;

		for (INT32 i = 0; i < MAX_GUILD_VARIABLE_COUNT; ++i)
			tempData.arrVariables[i] = pMsg->arrVariables[i];

		for (INT32 i = 0; i < GUILD_MAX_BUILDING_NUM; ++i)
		{
			tempData.arrBData[i].qwNameID = pMsg->arrBData[i].qwNameID;
			tempData.arrBData[i].nType = pMsg->arrBData[i].nType;
			tempData.arrBData[i].nLevel = pMsg->arrBData[i].nLevel;
		}

		for (INT32 i = 0; i < GUILD_MAX_UPGRADE_BUILDING_COUNT; ++i)
		{
			tempData.arrBUData[i].qwNameID = pMsg->arrBUData[i].qwNameID;
			tempData.arrBUData[i].nTime = pMsg->arrBUData[i].nTime;
		}

		for (INT32 i = 0; i < GUILD_MAX_WELFARE_AURA_COUNT; ++i)
			tempData.arrWelfareAuraLvl[i] = pMsg->arrWelfareAuraLvl[i];
		for (INT32 i = 0; i < GUILD_MAX_UPGRADE_AURA_COUNT; ++i)
			tempData.arrWelfareUpgradeAuraID[i] = pMsg->arrWelfareUpgradeAuraID[i];
		for (INT32 i = 0; i < GUILD_MAX_UPGRADE_AURA_COUNT; ++i)
			tempData.arrWelfareAuraUpgradeTime[i] = pMsg->arrWelfareAuraUpgradeTime[i];

		for (INT32 i = 0; i < pMsg->byMemberCount && i < GUILD_MAX_MEMBER_COUNT; ++i)
		{
			tempData.arrMemberData[i].dwRoleID = pMsg->arrMemberData[i].dwRoleID;
			tempData.arrMemberData[i].byPosition = pMsg->arrMemberData[i].byPosition;
			tempData.arrMemberData[i].byGuildFlag = pMsg->arrMemberData[i].byFlag;
			tempData.arrMemberData[i].nSalary = pMsg->arrMemberData[i].nNextSalary;
		}
		poGSGuild->Load(tempData);
	}



	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGMoreInfoAck(CRole *poRole, const char *pData)
{
	INT32       nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;
	M2C_MORE_GUILD_INFO_ACK *pMsg = (M2C_MORE_GUILD_INFO_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);

	poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
	LOG_PROCESS_ERROR(poGSGuild);

	poGSGuild->SetMatchWarCnsptn(pMsg->nMatchWarConsumption);
	poGSGuild->SetMatchCount(pMsg->byMatchCount);

Exit0:
	return;
}

void CRobotMessageHandler::OnMSGViewListAck(CRole *poRole, const char *pData)
{
	INT32       nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;
	M2C_VIEW_GUILD_LIST_ACK *pMsg = (M2C_VIEW_GUILD_LIST_ACK*)pData;

	LOG_PROCESS_ERROR(poRole);
    LOG_PROCESS_ERROR(poRole->GetAsimovRole());

    poRole->GetAsimovRole()->ClearViewList();
    for (INT32 i = 0; i < pMsg->byCount; ++i)
    {
        poRole->GetAsimovRole()->AddViewList(pMsg->info[i].dwGuildID);

        nRetCode = DoQueryGuildInfo(poRole, pMsg->info[i].dwGuildID);
        LOG_CHECK_ERROR(nRetCode);
    }

Exit0:
	return;
}

void CRobotMessageHandler::OnMSGFindAck(CRole *poRole, const char *pData)
{
	INT32       nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;
	M2C_FIND_GUILD_ACK  *pMsg = (M2C_FIND_GUILD_ACK*)pData;



}

void CRobotMessageHandler::OnMSCreateGuildAck(CRole *poRole, const char *pData)
{
	INT32       nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;
	M2C_CREATE_GUILD_ACK  *pMsg = (M2C_CREATE_GUILD_ACK*)pData;



}

void CRobotMessageHandler::OnMSGApplyToJoinAck(CRole *poRole, const char *pData)
{
	INT32       nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;

	M2C_APPLY_TO_JOIN_GUILD_ACK *pMsg = (M2C_APPLY_TO_JOIN_GUILD_ACK *)pData;

	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetAsimovRole());

	poRole->GetAsimovRole()->LuaAddGuildApp(pMsg->dwGuildID);

	nRetCode = DoQueryGuildInfo(poRole, pMsg->dwGuildID);
	LOG_CHECK_ERROR(nRetCode);

Exit0:
	return;
}

void CRobotMessageHandler::OnMSGuildGetAppList(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;

	M2C_GET_APPLY_GUILD_LIST_ACK  *pMsg = (M2C_GET_APPLY_GUILD_LIST_ACK *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);

	poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
	LOG_PROCESS_ERROR(poGSGuild);

	poGSGuild->ClearApp();
	for (INT32 i = 0; i < pMsg->wAppCount; ++i)
	{
		poGSGuild->AddApp(pMsg->info[i].dwRoleID);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGuildDelGuildApp(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;

	M2C_DEL_GUILD_APP  *pMsg = (M2C_DEL_GUILD_APP *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetAsimovRole());

	poRole->GetAsimovRole()->DelGuildApp(pMsg->dwGuildID);

    DBG("Del Guild APP %d %d", poRole->GetObjID(), pMsg->dwGuildID);

	nRetCode = DoQueryGuildInfo(poRole, pMsg->dwGuildID);
	LOG_CHECK_ERROR(nRetCode);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGRevertAppAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;

	M2C_REVERT_GUILD_APPLY_ACK  *pMsg = (M2C_REVERT_GUILD_APPLY_ACK *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetAsimovRole());
	LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);

	poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
	LOG_PROCESS_ERROR(poGSGuild);

	poGSGuild->DelApp(pMsg->dwRoleID);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGInviteToJoinGuild(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CRole       *poInviterRole = NULL;
	CGSGuild    *poGSGuild = NULL;

	M2C_BE_INVITED_TO_JOIN_GUILD  *pMsg = (M2C_BE_INVITED_TO_JOIN_GUILD *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetAsimovRole());
    PROCESS_ERROR(poRole->GetGuildCD() < time(NULL));

	poRole->GetAsimovRole()->SetInviteGuildRoleID(pMsg->dwRoleID);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGRevertGuildInvitationAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CRole       *poInviterRole = NULL;
	CGSGuild    *poGSGuild = NULL;

	M2C_INVITE_TO_JOIN_GUILD_ACK  *pMsg = (M2C_INVITE_TO_JOIN_GUILD_ACK *)pData;
	LOG_PROCESS_ERROR(poRole);


	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGuildDisband(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CRole       *poInviterRole = NULL;
	CGSGuild    *poGSGuild = NULL;

	M2C_DISBAND_GUILD_NTF  *pMsg = (M2C_DISBAND_GUILD_NTF *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);


	poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
	if (poGSGuild)
	{
		poGSGuild->UnInit();
		CGuildMgr::GetInstance().DelGuild(poGSGuild);
	}

	poRole->SetGuildID(0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGuildChangeNotice(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CRole       *poInviterRole = NULL;
	CGSGuild    *poGSGuild = NULL;

	M2C_GUILD_NOTICE_CHANGE  *pMsg = (M2C_GUILD_NOTICE_CHANGE *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);

	poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
	LOG_PROCESS_ERROR(poGSGuild);

	poGSGuild->SetNotice(pMsg->szNotice);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGuildChangePosition(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CRole       *poInviterRole = NULL;
	CGSGuild    *poGSGuild = NULL;
	ASIMOV_GUILD_MEMBER * pMember = NULL;

	M2C_GUILD_CHANGE_POSITION_NTF  *pMsg = (M2C_GUILD_CHANGE_POSITION_NTF *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);

	poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
	LOG_PROCESS_ERROR(poGSGuild);

	pMember = poGSGuild->GetMember(pMsg->dwRoleID);
	LOG_PROCESS_ERROR(pMember);

	pMember->byPosition = pMsg->byPosition;

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSGuildLeaveGuildAck(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CRole       *poInviterRole = NULL;
	CGSGuild    *poGSGuild = NULL;

	M2C_GUILD_ROLE_LEAVE_ACK  *pMsg = (M2C_GUILD_ROLE_LEAVE_ACK *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);

	poRole->SetGuildID(0);
    poRole->SetGuildCD(g_GuildConfig.dwReJoinGuildCD + time(NULL));

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSDelMemberNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CRole       *poInviterRole = NULL;
	CGSGuild    *poGSGuild = NULL;

	M2C_GUILD_ROLE_LEAVE_NTF  *pMsg = (M2C_GUILD_ROLE_LEAVE_NTF *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);

	poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
	LOG_PROCESS_ERROR(poGSGuild);

	poGSGuild->DelMember(pMsg->dwRoleID);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSAddMemberNtf(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;

	M2C_GUILD_ADD_MEMBER_NTF  *pMsg = (M2C_GUILD_ADD_MEMBER_NTF *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);

	poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
	LOG_PROCESS_ERROR(poGSGuild);

	poGSGuild->AddMember(pMsg->info.dwRoleID, pMsg->info.byPosition, pMsg->info.byFlag, pMsg->info.nNextSalary);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMSDemise(CRole *poRole, const char *pData)
{
	INT32 nRetCode = 0;
	CGSGuild    *poGSGuild = NULL;
	ASIMOV_GUILD_MEMBER       *pOldleader = NULL;
	ASIMOV_GUILD_MEMBER       *pNewLeader = NULL;

	M2C_GUILD_DEMISE_NTF  *pMsg = (M2C_GUILD_DEMISE_NTF *)pData;
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);

	poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
	LOG_PROCESS_ERROR(poGSGuild);

	PROCESS_ERROR(poGSGuild->GetLeaderID() != pMsg->dwNewLeaderID);

	pOldleader = poGSGuild->GetMember(poGSGuild->GetLeaderID());
	LOG_PROCESS_ERROR(pOldleader);

	pNewLeader = poGSGuild->GetMember(pMsg->dwNewLeaderID);
	LOG_PROCESS_ERROR(pNewLeader);

	pOldleader->byPosition = GUILD_POSITION_CIVILIAN;
	pNewLeader->byPosition = GUILD_POSITION_LEADER;
	poGSGuild->SetLeaderID(pNewLeader->dwRoleID);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnGuildCongAck(CRole *poRole, const char *pData)
{

}

void CRobotMessageHandler::OnGuildAttrModifyAck(CRole *poRole, const char *pData)
{

}

void CRobotMessageHandler::OnGuildGetUnionAppListAck(CRole *poRole, const char *pData)
{
    INT32 nRetCode = 0;
    CGSGuild    *poGSGuild = NULL;

    M2C_GUILD_GET_APPLY_UNION_LIST_ACK  *pMsg = (M2C_GUILD_GET_APPLY_UNION_LIST_ACK *)pData;
    LOG_PROCESS_ERROR(poRole);
    LOG_PROCESS_ERROR(poRole->GetGuildID() != 0);

    poGSGuild = CGuildMgr::GetInstance().FindGuild(poRole->GetGuildID());
    LOG_PROCESS_ERROR(poGSGuild);

    poGSGuild->ClearUnionApp();

    for (INT32 i = 0; i < pMsg->byCount; i++)
    {
        poGSGuild->AddUnionApp(pMsg->info[i].dwGuildID);
    }

Exit0:
    return;
}








/************************************************************************/
// attribute
void CRobotMessageHandler::OnExpChange(CRole* poRole, const char* pData)
{
	G2C_EXP_CHANGE* pMsg = (G2C_EXP_CHANGE*)pData;

	poRole->SetExp(pMsg->nExp);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adExperience, 0);
}

void CRobotMessageHandler::OnModifyReputation(CRole* poRole, const char* pData)
{
	G2C_MODIFY_REPUTATION* pMsg = (G2C_MODIFY_REPUTATION*)pData;

	poRole->GetReputation().SetValue(pMsg->byForceID, pMsg->nReputation);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adForceReputation, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(poRole->GetAchievementList(), adVariousForceCount, 0);
}

/************************************************************************/
// stall
void CRobotMessageHandler::OnStallStateChange(CRole* pRole, const char* pData)
{
	INT32 nResult = 0;
	G2C_STALL_STATE_CHANGE* msg = (G2C_STALL_STATE_CHANGE*)pData;

	if (msg->dwRoleID == pRole->GetObjID())
	{
		switch (pRole->GetStall()->GetStallState())
		{
		case essNotOpen:
			{
				switch (msg->btStallState)
				{
				case essPreparing:
					pRole->GetStall()->Open();
					break;
				case essNotOpen:
				case essOpen:
				default:
					LOG_PROCESS_ERROR(FALSE);
					break;
				}
			}
			break;
		case essPreparing:
			{
				switch (msg->btStallState)
				{
				case essNotOpen:
					pRole->GetStall()->RealClose();
					break;
				case essOpen:
					pRole->GetStall()->RealOpen();
					break;
				case essPreparing:
				default:
					LOG_PROCESS_ERROR(FALSE);
					break;
				}
			}
			break;
		case essOpen:
			{
				switch (msg->btStallState)
				{
				case essNotOpen:
					pRole->GetStall()->RealClose();
					break;
				case essPreparing:
					pRole->GetStall()->Close();
					break;
				case essOpen:
				default:
					LOG_PROCESS_ERROR(FALSE);
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnAddStallItem(CRole* pRole, const char* pData)
{
	INT32 nResult = 0;
	G2C_ADD_STALL_ITEM* msg = (G2C_ADD_STALL_ITEM*)pData;

	nResult = pRole->GetStall()->AddGood(msg->btStallSlot, msg->byConSlot, msg->byItemSlot, msg->shItemCount, msg->nPrice);
	LOG_PROCESS_ERROR(nResult == errSuccess);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnRemoveStallItem(CRole* pRole, const char* pData)
{
	INT32 nResult = 0;
	G2C_REMOVE_STALL_ITEM* msg = (G2C_REMOVE_STALL_ITEM*)pData;

	nResult = pRole->GetStall()->RemoveGood(msg->btStallSlot);
	LOG_PROCESS_ERROR(nResult == errSuccess);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnChangeStallName(CRole* pRole, const char* pData)
{
	INT32 nResult = 0;
	G2C_CHANGE_STALL_NAME* msg = (G2C_CHANGE_STALL_NAME*)pData;

	if (pRole->GetObjID() == msg->dwRoleID)
	{
		nResult = pRole->GetStall()->ChangeName(msg->szStallName);
		LOG_PROCESS_ERROR(nResult == errSuccess);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnBuyStallItem(CRole* pRole, const char* pData)
{
	INT32 nResult = 0;
	G2C_BUY_STALL_ITEM* msg = (G2C_BUY_STALL_ITEM*)pData;

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSoldStallItem(CRole* pRole, const char* pData)
{
	INT32 nResult = 0;
	G2C_SOLD_STALL_ITEM* msg = (G2C_SOLD_STALL_ITEM*)pData;

	nResult = pRole->GetStall()->SoldStallItem(msg->btStallSlot, msg->nItemCount);
	LOG_PROCESS_ERROR(nResult);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncStallLevel(CRole* pRole, const char* pData)
{
	INT32 nResult = 0;
	G2C_SYNC_STALL* msg = (G2C_SYNC_STALL*)pData;

	pRole->GetStall()->SetStallLevelUpExpireTime(msg->dwUpgradeExpireTime);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnViewStallItem(CRole* pRole, const char* pData)
{
	INT32 nResult = 0;
	char* stallbuf = NULL;
	ItemInfo iteminfo;
	UINT32 dwLen = 0;
	G2C_VIEW_STALL_ITEM* msg = (G2C_VIEW_STALL_ITEM*)pData;

	if (pRole->GetObjID() == msg->dwRoleID)
	{
		stallbuf = msg->acStallItems;
		for (UINT8 i = 0; i < msg->btStallItemCount; ++i)
		{
			STALL_ITEM_INFO* sinfo = (STALL_ITEM_INFO*)stallbuf;
			stallbuf += sizeof(STALL_ITEM_INFO);
			dwLen = iteminfo.Load(stallbuf);
			stallbuf += dwLen;

			pRole->GetStall()->SyncStallItem(sinfo->btStallSlot, sinfo->llModifyFrame);
		}
	}
	else
	{

	}

	return;
Exit0:
	return;
}

/************************************************************************/
// quest
void CRobotMessageHandler::OnCompleteQuest(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_COMPLETE_QUEST* pMsg = (G2C_COMPLETE_QUEST*)pData;

	nRetCode = pRole->GetQuestList().Complete(pMsg->nQuestID);
	LOG_PROCESS_ERROR(nRetCode);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adCompleteQuest, 0);

	return;
Exit0:
	return;
}

/************************************************************************/
// variables
void CRobotMessageHandler::OnUpdateVariable(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_UPDATE_VARIABLE* pMsg = (G2C_UPDATE_VARIABLE*)pData;

	if (pMsg->nReferID == pRole->GetObjID())
	{
		if (vtRole == pMsg->byType)
		{
			pRole->SetVariable(pMsg->wIndex, pMsg->nValue);
			ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adRoleVariable, pMsg->wIndex);
		}
	}

	return;
Exit0:
	return;
}

/************************************************************************/

void CRobotMessageHandler::OnMSTeamJoin(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	CTeamInGS* poTeam = NULL;
	M2C_TEAM_JOIN* pMsg = (M2C_TEAM_JOIN*)pData;
	LOG_PROCESS_ERROR(poRole->GetTeamID() == 0);
	poRole->SetTeamID(pMsg->dwTeamID);

	poTeam = CGameWorld::GetInstance().FindTeam(pMsg->dwTeamID);
	if (!poTeam)
	{
		poTeam = CGameWorld::GetInstance().NewTeam(pMsg->dwTeamID);
		LOG_PROCESS_ERROR(poTeam);

		nRetCode = poTeam->Init();
		LOG_CHECK_ERROR(nRetCode);

		poTeam->SetTeamID(pMsg->dwTeamID);
		poTeam->SetLeaderID(pMsg->dwLeadID);
		poTeam->SetMemberCount(pMsg->byMemberCount);
		poTeam->SetMaxMemberCount(pMsg->nMemberSizeLimit);
	}
	else
	{
		poTeam->SetLeaderID(pMsg->dwLeadID);
		poTeam->SetMemberCount(pMsg->byMemberCount);
		poTeam->SetMaxMemberCount(pMsg->nMemberSizeLimit);
	}

Exit0:
	return;
}

void CRobotMessageHandler::OnMSTeamLeave(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	CTeamInGS* poTeam = NULL;

	M2C_TEAM_LEAVE* pMsg = (M2C_TEAM_LEAVE*)pData;
	LOG_PROCESS_ERROR(pMsg->dwTeamID == poRole->GetTeamID());

	poRole->SetTeamID(0);

	poTeam = CGameWorld::GetInstance().FindTeam(pMsg->dwTeamID);
	if (poTeam)
	{
		poTeam->SetMemberCount(poTeam->GetMemberCount() - 1);
		if (poTeam->GetMemberCount() == 0)
		{
			nRetCode = poTeam->UnInit();
			LOG_CHECK_ERROR(nRetCode);

			nRetCode = CGameWorld::GetInstance().DelTeam(poTeam);
			LOG_PROCESS_ERROR(nRetCode);
		}
	}

Exit0:
	return;
}

void CRobotMessageHandler::OnMSTeamAnswer(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	M2C_TEAM_ANSWER* pMsg = (M2C_TEAM_ANSWER*)pData;

	if (m_bTeamAuto)
	{
		nRetCode = DoTeamAnswer(poRole, pMsg->dwAnswerRequestRoleID, pMsg->byAnswerType, etarAgree);
		LOG_PROCESS_ERROR(nRetCode);
	}

Exit0:
	return;
}

void CRobotMessageHandler::OnMSTeamAddMember(CRole* poRole, const char* pData)
{
	M2C_TEAM_ADD_MEMBER* pMsg = (M2C_TEAM_ADD_MEMBER*)pData;

	return;
}

void CRobotMessageHandler::OnMSTeamRemoveMember(CRole* poRole, const char* pData)
{
	M2C_TEAM_REMOVE_MEMBER* pMsg = (M2C_TEAM_REMOVE_MEMBER*)pData;

	return;
}

void CRobotMessageHandler::OnMSTeamChangeInfo(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	CTeamInGS* poTeam = NULL;
	M2C_TEAM_CHANGEINFO* pMsg = (M2C_TEAM_CHANGEINFO*)pData;

	poTeam = CGameWorld::GetInstance().FindTeam(pMsg->dwTeamID);
	if (poTeam)
	{
		poTeam->SetLeaderID(pMsg->dwLeadID);
		poTeam->SetMaxMemberCount(pMsg->nTeamMemberLimit);
		poTeam->SetAssignType(pMsg->byAssignType);
		poTeam->SetAuctionItemColorLimit(pMsg->byAuctionItemColorLimit);
	}
	return;
}

void CRobotMessageHandler::OnMSTeamSyncMemberInfo(CRole* poRole, const char* pData)
{
	M2C_TEAM_SYNC_MEMBERINFO* pMsg = (M2C_TEAM_SYNC_MEMBERINFO*)pData;

	return;
}

void CRobotMessageHandler::OnMSTeamSyncMemberState(CRole* pRole, const char* pData)
{
	M2C_TEAM_SYNC_MEMBERSTATE* pMsg = (M2C_TEAM_SYNC_MEMBERSTATE*)pData;

	return;
}

void CRobotMessageHandler::OnGSTeamSyncMemberInfo(CRole* pRole, const char* pData)
{
	G2C_TEAM_SYNC_MEMBER* pMsg = (G2C_TEAM_SYNC_MEMBER*)pData;

	return;
}

void CRobotMessageHandler::OnGSBattleTeamJoin(CRole* pRole, const char* pData)
{
	G2C_BATTLE_TEAM_JOIN* pMsg = (G2C_BATTLE_TEAM_JOIN*)pData;

	return;
}

void CRobotMessageHandler::OnGSBattleTeamAddMember(CRole* pRole, const char* pData)
{
	G2C_BATTLE_TEAM_ADD* pMsg = (G2C_BATTLE_TEAM_ADD*)pData;

	return;
}

void CRobotMessageHandler::OnGSBattleTeamRemoveMember(CRole* pRole, const char* pData)
{
	G2C_BATTLE_TEAM_REMOVE* pMsg = (G2C_BATTLE_TEAM_REMOVE*)pData;

	return;

}

void CRobotMessageHandler::OnMSErrorNotify(CRole* poRole, const char* pData)
{
	M2C_ERROR_NOTIFY* pMsg = (M2C_ERROR_NOTIFY*)pData;

	return;
}

void CRobotMessageHandler::OnGSCompleteAchievement(CRole* pRole, const char* pData)
{
    INT32       nRetCode = 0;
    const ACHIEVEMENT_DATA* pAchievementData = NULL;
    G2C_COMPLETE_ACHIEVEMENT    *pMsg = (G2C_COMPLETE_ACHIEVEMENT*)pData;

    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(pRole->GetAsimovRole());

    pAchievementData = CDataManager<ACHIEVEMENT_DATA>::GetInstance().GetData(pMsg->nAchievementID);
    LOG_PROCESS_ERROR(pData);

	pRole->GetAchievementList().Complete(pMsg->nAchievementID);

Exit0:
    return;
}

void CRobotMessageHandler::OnShieldRole(CRole* pRole, const char* pData)
{
    INT32       nRetCode = 0;
    G2C_SHIELD_ACK  *pMsg = (G2C_SHIELD_ACK*)pData;

    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(pRole->GetShieldList());

    pRole->GetShieldList()->ShieldRole(pMsg->dwRoleID);

Exit0:
    return;
}

void CRobotMessageHandler::OnUnshieldRole(CRole* pRole, const char* pData)
{
    INT32       nRetCode = 0;
    G2C_UNSHIELD_ACK  *pMsg = (G2C_UNSHIELD_ACK*)pData;

    LOG_PROCESS_ERROR(pRole);
    LOG_PROCESS_ERROR(pRole->GetShieldList());

    pRole->GetShieldList()->UnShieldRole(pMsg->dwRoleID);

Exit0:
    return;
}

void CRobotMessageHandler::OnAdjacentNoTeamRole(CRole* poRole, const char* pData)
{
	G2C_SYNC_ADJACENT_ROLE_NOTEAM* pMsg = (G2C_SYNC_ADJACENT_ROLE_NOTEAM*)pData;

	return;
}

void CRobotMessageHandler::OnAdjacentTeam(CRole* poRole, const char* pData)
{
	G2C_SYNC_ADJACENT_TEAM* pMsg = (G2C_SYNC_ADJACENT_TEAM*)pData;

	return;
}

BOOL CRobotMessageHandler::DoLogout(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_LOGOUT* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (C2G_LOGOUT*)m_pPacketAllocator->Alloc(sizeof(C2G_LOGOUT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_logout;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_LOGOUT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoLogoutCancel(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_LOGOUT_CANCEL* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (C2G_LOGOUT_CANCEL*)m_pPacketAllocator->Alloc(sizeof(C2G_LOGOUT_CANCEL));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_logout_cancel;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_LOGOUT_CANCEL));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}


BOOL CRobotMessageHandler::DoUpdatePos(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_UPDATE_POS* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (C2G_UPDATE_POS*)m_pPacketAllocator->Alloc(sizeof(C2G_UPDATE_POS));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_update_pos;
	pMsg->wCurrentX = ConvertCoordS2N(poRole->GetX());
	pMsg->wCurrentY = ConvertCoordS2N(poRole->GetY());
	pMsg->wCurrentZ = ConvertCoordS2N(poRole->GetZ());

	//DBG("[%4d]update pos (%d, %d, %d)", CGameWorld::GetInstance().GetGameFrame(),
	//   	(INT32)(pMsg->nCurrentX / POINT_PER_CM), (INT32)(pMsg->nCurrentY / POINT_PER_CM), 
	//      (INT32)(pMsg->nCurrentZ / POINT_PER_CM));

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_UPDATE_POS));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoQueryRoleData(CRole* poRole, CRole* poQueryRole)
{
	INT32 nRetCode = 0;
	UINT32 dwCRC = 0;
	C2G_QUERY_CHAR_DATA* pMsg = NULL;
	ROLE_DATA_CACHE::iterator it;

	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poQueryRole);

	it = s_RoleCache.RoleDataCache.find(poQueryRole->GetObjID());
	if (it != s_RoleCache.RoleDataCache.end())
	{
		OnSyncRoleData(poRole, (const char*)&it->second);

		dwCRC = crc32(0, (const Bytef*)&it->second, sizeof(G2C_SYNC_ROLE_DATA));
	}

	pMsg = (C2G_QUERY_CHAR_DATA*)m_pPacketAllocator->Alloc(sizeof(C2G_QUERY_CHAR_DATA));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_query_char_data;
	pMsg->dwCharID = poQueryRole->GetObjID();
	pMsg->dwCRC = dwCRC;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_QUERY_CHAR_DATA));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoQueryNpcData(CRole* poRole, CNpc* poQueryNpc)
{
	INT32 nRetCode = 0;
	UINT32 dwCRC = 0;
	C2G_QUERY_CHAR_DATA* pMsg = NULL;
	NPC_DATA_CACHE::iterator it;

	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(poQueryNpc);

	it = s_RoleCache.NpcDataCache.find(poQueryNpc->GetObjID());
	if (it != s_RoleCache.NpcDataCache.end())
	{
		OnSyncNpcData(poRole, (const char*)&it->second);

		dwCRC = crc32(0, (const Bytef*)&it->second, sizeof(G2C_SYNC_NPC_DATA));
	}

	pMsg = (C2G_QUERY_CHAR_DATA*)m_pPacketAllocator->Alloc(sizeof(C2G_QUERY_CHAR_DATA));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_query_char_data;
	pMsg->dwCharID = poQueryNpc->GetObjID();
	pMsg->dwCRC = dwCRC;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_QUERY_CHAR_DATA));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}
//
//BOOL CRobotMessageHandler::DoCastSpell(CRole* poRole, INT32 nSpellID, CCharacter* poTarget, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ)
//{
//	BOOL bRet;
//	UINT8 bySlotID = 0xFF;
//	INT32 nSize = sizeof(C2G_ROLE_CAST_SPELL);
//	C2G_ROLE_CAST_SPELL* pMsg = (C2G_ROLE_CAST_SPELL*)m_pPacketAllocator->Alloc(nSize);
//	LOG_PROCESS_ERROR(pMsg);
//	LOG_PROCESS_ERROR(poRole);
//
//	for (INT32 i = qssSlotBegin; i < qssSlotCount; ++i)
//	{
//		CSpellSlot* poSlot = poRole->GetSpellSlot(i);
//		LOG_PROCESS_ERROR(poSlot);
//
//		if (poSlot->GetMainSpellID() == nSpellID)
//		{
//			bySlotID = i;
//			break;
//		}
//	}
//
//	PROCESS_ERROR(bySlotID != 0xFF);
//
//	pMsg->wMsg = c2g_role_cast_spell;
//	pMsg->bySpellSlot = bySlotID;
//	pMsg->wTargetX = ConvertCoordS2N(nTargetX);
//	pMsg->wTargetY = ConvertCoordS2N(nTargetY);
//	pMsg->wTargetZ = ConvertCoordS2N(nTargetZ);
//	pMsg->dwTargetID = 0;
//
//	if (poTarget != NULL)
//	{
//		pMsg->dwTargetID = poTarget->GetObjID();
//	}
//
//	bRet = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
//	LOG_PROCESS_ERROR(bRet);
//	return TRUE;
//
//Exit0:
//	if (pMsg)
//		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//	return FALSE;
//}

BOOL CRobotMessageHandler::DoCastSpell(CRole* poRole, INT32 nSpellID, CCharacter* poTarget, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ)
{
	BOOL bRet;
	//UINT8 bySlotID = 0xFF;
	INT32 nSize = sizeof(C2G_CAST_SPELL_EX);
	C2G_CAST_SPELL_EX* pMsg = (C2G_CAST_SPELL_EX*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);
	LOG_PROCESS_ERROR(nSpellID < (1<<16) && nSpellID > 0);

	//for (INT32 i = qssSlotBegin; i < qssSlotCount; ++i)
	//{
	//	CSpellSlot* poSlot = poRole->GetSpellSlot(i);
	//	LOG_PROCESS_ERROR(poSlot);
	//	if (poSlot->GetMainSpellID() == nSpellID)
	//	{
	//		bySlotID = i;
	//		break;
	//	}
	//}
	//PROCESS_ERROR(bySlotID != 0xFF);

	pMsg->wMsg = c2g_cast_spell_ex;
	pMsg->wSpellID = (INT16)nSpellID;
	pMsg->bySerial = 1;
	pMsg->byRotateToTarget = TRUE;
	pMsg->wTargetX = ConvertCoordS2N(nTargetX);
	pMsg->wTargetY = ConvertCoordS2N(nTargetY);
	pMsg->wTargetZ = ConvertCoordS2N(nTargetZ);
	pMsg->dwTargetID = 0;
	if (poTarget != NULL)
	{
		pMsg->dwTargetID = poTarget->GetObjID();
	}

	bRet = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(bRet);
	return TRUE;

Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoDirectCastSpell(CRole* poRole, INT32 nSpellID, INT32 nSpellLevel, UINT32 dwTargetID, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ)
{
	BOOL bRet;
	INT32 nSize = sizeof(C2G_DIRECTLY_CAST_SPELL);
	C2G_DIRECTLY_CAST_SPELL* pMsg = (C2G_DIRECTLY_CAST_SPELL*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);

	pMsg->wMsg = c2g_directly_cast_spell;
	pMsg->dwSpellID = nSpellID;
	pMsg->bySpellLevel = nSpellLevel;
	pMsg->dwTargetID = dwTargetID;
	pMsg->wTargetX = ConvertCoordS2N(nTargetX);
	pMsg->wTargetY = ConvertCoordS2N(nTargetY);
	pMsg->wTargetZ = ConvertCoordS2N(nTargetZ);
	pMsg->dwTargetID = dwTargetID;

	bRet = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
	LOG_PROCESS_ERROR(bRet);
	return TRUE;

Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSelectFocus(CRole* poRole, INT32 nFocusID)
{
	BOOL bRet;
	C2G_SELECT_FOCUS* pMsg = (C2G_SELECT_FOCUS*)m_pPacketAllocator->Alloc(sizeof(C2G_SELECT_FOCUS));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_select_focus;
	pMsg->dwFocusID = nFocusID;

	bRet = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_SELECT_FOCUS));
	LOG_PROCESS_ERROR(bRet);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoLearnSpell(CRole* poRole, INT32 nSpellID, INT32 nSpellLevel)
{
	INT32 nSize = sizeof(C2G_LEARN_SPELL);
	C2G_LEARN_SPELL* pMsg = (C2G_LEARN_SPELL*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);


	pMsg->wMsg = c2g_learn_spell;

	pMsg->wSpellID = nSpellID;
	pMsg->bySpellLevel = nSpellLevel;

	return m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoPickUpItem(CRole* poRole, UINT32 dwDropID, UINT8 byPickMode)
{
	INT32 nSize = sizeof(C2G_PICKUP_ITEM);
	C2G_PICKUP_ITEM* pMsg = (C2G_PICKUP_ITEM*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);

	pMsg->wMsg = c2g_pickup_item;
	pMsg->dwDropID = dwDropID;
	pMsg->byPickMode = byPickMode;

	return m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
Exit0:

	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoUseItem(CRole* poRole, UINT8 conslot, UINT8 itemslot)
{
	INT32 nSize = sizeof(C2G_USE_ITEM);
	C2G_USE_ITEM* pMsg = (C2G_USE_ITEM*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);


	pMsg->wMsg = c2g_use_item;
	pMsg->byConSlot = conslot;
	pMsg->byItemSlot = itemslot;
	return m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
Exit0:

	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoMoveItem(CRole* poRole, UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot)
{
	INT32 nSize = sizeof(C2G_MOVE_ITEM);
	C2G_MOVE_ITEM* pMsg = (C2G_MOVE_ITEM*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);


	pMsg->wMsg = c2g_move_item;
	pMsg->bySrcConSlot = srcconslot;
	pMsg->bySrcItemSlot = srcitemslot;
	pMsg->byDstConSlot = dstconslot;
	pMsg->byDstItemSlot = dstitemslot;
	return m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
Exit0:

	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSplitItem(CRole* poRole, UINT8 srcconslot, UINT8 srcitemslot, UINT8 dstconslot, UINT8 dstitemslot, INT16 itemcount)
{
	INT32 nSize = sizeof(C2G_SPLIT_ITEM);
	C2G_SPLIT_ITEM* pMsg = (C2G_SPLIT_ITEM*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);


	pMsg->wMsg = c2g_split_item;

	pMsg->bySrcConSlot = srcconslot;
	pMsg->bySrcItemSlot = srcitemslot;
	pMsg->byDstConSlot = dstconslot;
	pMsg->byDstItemSlot = dstitemslot;
	pMsg->shItemCount = itemcount;
	return m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoDeleteItem(CRole* poRole, UINT8 conslot, UINT8 itemslot, INT16 itemcount)
{
	INT32 nSize = sizeof(C2G_DELETE_ITEM);
	C2G_DELETE_ITEM* pMsg = (C2G_DELETE_ITEM*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(poRole);


	pMsg->wMsg = c2g_delete_item;
	pMsg->byConSlot = conslot;
	pMsg->byItemSlot = itemslot;
	pMsg->shItemCount = itemcount;
	return m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

void CRobotMessageHandler::OnLeaveScene(CRole* poRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_LEAVE_SCENE * pMsg = (G2C_LEAVE_SCENE *)pData;
	CScene* poScene = NULL;
	LOG_PROCESS_ERROR(poRole);

	poScene = poRole->GetScene();
	LOG_PROCESS_ERROR(poScene);

	nRetCode = poScene->RemoveRole(poRole);
	LOG_PROCESS_ERROR(nRetCode);

	poRole->SetState(rsInJump);

	return;
Exit0:
	return;
}

BOOL CRobotMessageHandler::DoCancelCast(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_ROLE_CANCEL_CAST* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (C2G_ROLE_CANCEL_CAST*)m_pPacketAllocator->Alloc(sizeof(C2G_ROLE_CANCEL_CAST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_role_cancel_cast;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_ROLE_CANCEL_CAST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoChangePkMode(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_CHANGE_PK_MODE* pMsg = NULL;

	LOG_PROCESS_ERROR(poRole);

	pMsg = (C2G_CHANGE_PK_MODE*)m_pPacketAllocator->Alloc(sizeof(C2G_CHANGE_PK_MODE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_change_pk_mode;
	pMsg->byMode = poRole->GetPkMode();

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_CHANGE_PK_MODE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTradeAsk(CRole* poRole, UINT32 dwTargetRoleID)
{
	INT32 nRetCode = 0;

	C2G_TRADE_ASK* pMsg = (C2G_TRADE_ASK*)m_pPacketAllocator->Alloc(sizeof(C2G_TRADE_ASK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_ask;
	pMsg->dwRoleID = dwTargetRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_ASK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTradeAccept(CRole* poRole, UINT32 dwTargetRoleID)
{
	INT32 nRetCode = 0;

	C2G_TRADE_ACCEPT* pMsg = (C2G_TRADE_ACCEPT*)m_pPacketAllocator->Alloc(sizeof(C2G_TRADE_ACCEPT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_accept;
	pMsg->dwRoleID = dwTargetRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_ACCEPT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTradeSetMoney(CRole* pRole, INT32 nMoneyCount)
{
	INT32 nRetCode = 0;

	C2G_TRADE_SET_MONEY* pMsg = (C2G_TRADE_SET_MONEY*)m_pPacketAllocator->Alloc(sizeof(C2G_TRADE_SET_MONEY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_set_money;
	pMsg->nMoney = nMoneyCount;

	nRetCode = m_poNotifier->SendToServer(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_SET_MONEY));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}
BOOL CRobotMessageHandler::DoTradeSetItem(CRole* pRole, UINT8 bAdd, UINT8 byTradeSlot, UINT8 byConSlot, UINT8 byItemSlot)
{
	INT32 nRetCode = 0;

	C2G_TRADE_SET_ITEM* pMsg = (C2G_TRADE_SET_ITEM*)m_pPacketAllocator->Alloc(sizeof(C2G_TRADE_SET_ITEM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_set_item;
	pMsg->bAdd = bAdd; // g_Random(0, 1) > 0 ? TRUE : FALSE;
	pMsg->byConSlot = byConSlot;
	pMsg->byItemSlot = byItemSlot;
	pMsg->byTradeSlot = byTradeSlot;
	nRetCode = m_poNotifier->SendToServer(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_SET_ITEM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}
BOOL CRobotMessageHandler::DoTradeLock(CRole* pRole)
{
	INT32 nRetCode = 0;

	C2G_TRADE_LOCK* pMsg = (C2G_TRADE_LOCK*)m_pPacketAllocator->Alloc(sizeof(C2G_TRADE_LOCK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_lock;

	nRetCode = m_poNotifier->SendToServer(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_LOCK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}
BOOL CRobotMessageHandler::DoTradeUnlock(CRole* pRole)
{
	INT32 nRetCode = 0;

	C2G_TRADE_UNLOCK* pMsg = (C2G_TRADE_UNLOCK*)m_pPacketAllocator->Alloc(sizeof(C2G_TRADE_UNLOCK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_unlock;

	nRetCode = m_poNotifier->SendToServer(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_UNLOCK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}
BOOL CRobotMessageHandler::DoTradeConfirm(CRole* pRole)
{
	INT32 nRetCode = 0;

	C2G_TRADE_CONFIRM* pMsg = (C2G_TRADE_CONFIRM*)m_pPacketAllocator->Alloc(sizeof(C2G_TRADE_CONFIRM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_confirm;

	nRetCode = m_poNotifier->SendToServer(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_CONFIRM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}
BOOL CRobotMessageHandler::DoTradeCancel(CRole* pRole)
{
	INT32 nRetCode = 0;

	C2G_TRADE_CANCEL* pMsg = (C2G_TRADE_CANCEL*)m_pPacketAllocator->Alloc(sizeof(C2G_TRADE_CANCEL));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_trade_cancel;

	nRetCode = m_poNotifier->SendToServer(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_TRADE_CANCEL));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTeamJoinRand(CRole* poRole)
{
	INT32 nRetCode = 0;
	CTraverseTeam stTraverseTeam;
	UINT32 dwTargetID = poRole->GetObjID();

	if (CGameWorld::GetInstance().GetTeamCount() > 0)
	{
		stTraverseTeam.m_dwLeaderID = 0;
        stTraverseTeam.m_dwSessionID = poRole->GetSessionID();
        stTraverseTeam.m_nIndex = poRole->GetObjID() % CGameWorld::GetInstance().GetTeamCount();
		CGameWorld::GetInstance().TraverseTeam(stTraverseTeam);
        LOG_PROCESS_ERROR(stTraverseTeam.m_dwLeaderID > 0);
        dwTargetID = stTraverseTeam.m_dwLeaderID;
	}

	nRetCode = DoTeamJoin(poRole, dwTargetID);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	return FALSE;

}


BOOL CRobotMessageHandler::DoTeamJoin(CRole* poRole, UINT32 dwTargetRoleID)
{
	INT32 nRetCode = 0;

	C2M_TEAM_JOIN* pMsg = (C2M_TEAM_JOIN*)m_pPacketAllocator->Alloc(sizeof(C2M_TEAM_JOIN));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_team_join;
	pMsg->dwTargetRoleID = dwTargetRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_TEAM_JOIN));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTeamLeave(CRole* poRole, UINT32 dwLeaveRoleID)
{
	INT32 nRetCode = 0;

	C2M_TEAM_LEAVE* pMsg = (C2M_TEAM_LEAVE*)m_pPacketAllocator->Alloc(sizeof(C2M_TEAM_LEAVE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_team_leave;
	pMsg->dwLeaveRoleID = dwLeaveRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_TEAM_LEAVE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTeamAnswer(CRole* poRole, UINT32 dwAnswerReqRoleID, UINT8 byType, UINT8 byAnswerResult)
{
	INT32 nRetCode = 0;

	C2M_TEAM_ANSWER* pMsg = (C2M_TEAM_ANSWER*)m_pPacketAllocator->Alloc(sizeof(C2M_TEAM_ANSWER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_team_answer;
	pMsg->dwAnswerRequestRoleID = dwAnswerReqRoleID;
	pMsg->byAnswerType = byType;
	pMsg->byAnswerResult = byAnswerResult;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_TEAM_ANSWER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTeamChangeInfo(CRole* poRole, INT32 nTeamMemberLimit, UINT8 byAssignType, UINT8 dwLeadID, UINT8 byAuctionItemColorLimit)
{
	INT32 nRetCode = 0;

	C2M_TEAM_CHANGEINFO* pMsg = (C2M_TEAM_CHANGEINFO*)m_pPacketAllocator->Alloc(sizeof(C2M_TEAM_CHANGEINFO));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_team_changeinfo;
	pMsg->dwLeadID = dwLeadID;
	pMsg->byAssignType = byAssignType;
	pMsg->nTeamMemberLimit = nTeamMemberLimit;
	pMsg->byItemAuctionColorLimit = byAuctionItemColorLimit;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_TEAM_CHANGEINFO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTeamChangeActivityInfo(CRole* poRole, UINT32 dwActivityType, INT32 nActivityID)
{
	INT32 nRetCode = 0;
	C2M_TEAM_CHANGE_ACTIVITY_INFO* pMsg = (C2M_TEAM_CHANGE_ACTIVITY_INFO*)m_pPacketAllocator->Alloc(sizeof(C2M_TEAM_CHANGE_ACTIVITY_INFO));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_team_change_activity_info;

	pMsg->dwActivityType = dwActivityType;
	pMsg->nActivityID = nActivityID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_TEAM_CHANGE_ACTIVITY_INFO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTeamQueryActivityTeam(CRole* poRole, UINT32 dwActivityType, INT32 nActivityID, INT32 nPgae)
{
	INT32 nRetCode = 0;
	C2M_TEAM_QUERY_ACTIVITY_TEAM* pMsg = (C2M_TEAM_QUERY_ACTIVITY_TEAM*)m_pPacketAllocator->Alloc(sizeof(C2M_TEAM_QUERY_ACTIVITY_TEAM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_team_query_activity_team;

	pMsg->dwActivityType = dwActivityType;
	pMsg->nActivityID = nActivityID;
	pMsg->nPgae = nPgae;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_TEAM_QUERY_ACTIVITY_TEAM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoTeamRemoveActivityTeam(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2M_TEAM_REMOVE_ACTIVITY_TEAM* pMsg = (C2M_TEAM_REMOVE_ACTIVITY_TEAM*)m_pPacketAllocator->Alloc(sizeof(C2M_TEAM_REMOVE_ACTIVITY_TEAM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_team_remove_activity_team;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_TEAM_REMOVE_ACTIVITY_TEAM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoAdjacentNoTeamRole(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_ADJACENT_ROLE_NOTEAM* pMsg = (C2G_ADJACENT_ROLE_NOTEAM*)m_pPacketAllocator->Alloc(sizeof(C2G_ADJACENT_ROLE_NOTEAM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_adjacent_role_noteam;
	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_ADJACENT_ROLE_NOTEAM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoAdjacentTeam(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_ADJACENT_TEAM* pMsg = (C2G_ADJACENT_TEAM*)m_pPacketAllocator->Alloc(sizeof(C2G_ADJACENT_TEAM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_adjacent_team;
	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_ADJACENT_TEAM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

// team auction
BOOL CRobotMessageHandler::DoTeamAuctionBid(CRole* poRole, INT32 nItemID, UINT32 dwBidMoneyCount)
{
	INT32 nRetCode = 0;
	C2G_TEAM_AUCTION_BID* pMsg = (C2G_TEAM_AUCTION_BID*)m_pPacketAllocator->Alloc(sizeof(C2G_TEAM_AUCTION_BID));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_team_auction_bid;
//	pMsg->nItemID = nItemID;
//	pMsg->dwBidMoneyCount = dwBidMoneyCount;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_TEAM_AUCTION_BID));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

// master
BOOL CRobotMessageHandler::DoMstGetRecruit(CRole *poRole)
{
	INT32 nRetCode = 0;
	C2M_MASTER_GET_RECRUIT_LIST* pMsg = (C2M_MASTER_GET_RECRUIT_LIST*)m_pPacketAllocator->Alloc(sizeof(C2M_MASTER_GET_RECRUIT_LIST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_get_recruit_list;
	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_GET_RECRUIT_LIST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoMstGetSoloList(CRole *poRole)
{
	INT32       nRetCode = 0;
	C2M_MASTER_GET_SOLO_LIST *pMsg = (C2M_MASTER_GET_SOLO_LIST*)m_pPacketAllocator->Alloc(sizeof(C2M_MASTER_GET_SOLO_LIST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_get_solo_list;
	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_GET_SOLO_LIST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoMstSubmitStudApp(CRole* poRole, UINT32 dwTeacherID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_STUD_SUBMIT_APP* pMsg = (C2M_MASTER_STUD_SUBMIT_APP*)m_pPacketAllocator->Alloc(sizeof(C2M_MASTER_STUD_SUBMIT_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_stud_submit_app;
	pMsg->dwTeacherID = dwTeacherID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_STUD_SUBMIT_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoMstAgreeStudApp(CRole* poRole, UINT32 dwStudentID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_AGREE_STUD_APP* pMsg = (C2M_MASTER_AGREE_STUD_APP*)m_pPacketAllocator->Alloc(sizeof(C2M_MASTER_AGREE_STUD_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_agree_stud_app;
	pMsg->dwStudentID = dwStudentID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_AGREE_STUD_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoMstCancelStudApp(CRole* poRole, UINT32 dwMasterID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_CANCEL_STUD_APP* pMsg = (C2M_MASTER_CANCEL_STUD_APP*)m_pPacketAllocator->Alloc(sizeof(C2M_MASTER_CANCEL_STUD_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_cancel_stud_app;
	pMsg->dwTeacherID = dwMasterID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_CANCEL_STUD_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoMstRefuseStudApp(CRole* poRole, UINT32 dwStudentID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_REFUSE_STUD_APP* pMsg = (C2M_MASTER_REFUSE_STUD_APP*)m_pPacketAllocator->Alloc(sizeof(C2M_MASTER_REFUSE_STUD_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_refuse_stud_app;
	pMsg->dwStudentID = dwStudentID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_REFUSE_STUD_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}


//BOOL CRobotMessageHandler::DoMstLeaveMaster(CRole* poRole)
//{
//    INT32 nRetCode = 0;
//    C2M_MASTER_LEAVE_MASTER* pMsg = (C2M_MASTER_LEAVE_MASTER*)m_pPacketAllocator->Alloc(sizeof(C2M_MASTER_LEAVE_MASTER));
//    LOG_PROCESS_ERROR(pMsg);
//
//    pMsg->wMsg = c2m_master_leave_master;
//
//    nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_LEAVE_MASTER));
//    LOG_PROCESS_ERROR(nRetCode);
//
//    return TRUE;
//Exit0:
//    if (pMsg)
//        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//    return FALSE;
//}

BOOL CRobotMessageHandler::DoMstFireStudent(CRole* poRole, UINT32 dwStudentID)
{
	INT32 nRetCode = 0;
	C2M_MASTER_FIRE_STUD* pMsg = (C2M_MASTER_FIRE_STUD*)m_pPacketAllocator->Alloc(sizeof(C2M_MASTER_FIRE_STUD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_master_fire_stud;
	pMsg->dwStudentID = dwStudentID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_FIRE_STUD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

//BOOL CRobotMessageHandler::DoMstCongLevelUp(CRole* poRole, UINT32 dwStudentID, UINT8 byCongType)
//{
//    INT32 nRetCode = 0;
//    C2M_MASTER_CONG_LEVEL_UP* pMsg = (C2M_MASTER_CONG_LEVEL_UP*)m_pPacketAllocator->Alloc(sizeof(C2M_MASTER_CONG_LEVEL_UP));
//    LOG_PROCESS_ERROR(pMsg);
//
//    pMsg->wMsg = c2m_master_cong_level_up;
//    pMsg->byCongType = byCongType;
//    pMsg->dwStudentID = dwStudentID;
//
//    nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_MASTER_CONG_LEVEL_UP));
//    LOG_PROCESS_ERROR(nRetCode);
//
//    return TRUE;
//Exit0:
//    if (pMsg)
//        m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//    return FALSE;
//}

BOOL CRobotMessageHandler::DoGuildCreate(CRole *poRole, char *guild_name, char *announce)
{
	INT32   nRetCode = 0;
    INT32   nSize = 0;
	C2G_GUILD_CREATE* pMsg = (C2G_GUILD_CREATE*)m_pPacketAllocator->Alloc(sizeof(C2G_GUILD_CREATE) + GUILD_ANNOUNCE_LEN);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_guild_create;
	strxcpy(pMsg->szGuildName, guild_name, GUILD_NAME_LEN);
    nSize = strlen(announce) + 1;
    strxcpy(pMsg->szAnnounce, announce, nSize);
    pMsg->wSize = sizeof(C2G_GUILD_CREATE) + nSize;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildView(CRole *poRole, UINT32 lastGuildID)
{
	INT32 nRetCode = 0;
	C2M_VIEW_GUILD_LIST* pMsg = (C2M_VIEW_GUILD_LIST*)m_pPacketAllocator->Alloc(sizeof(C2M_VIEW_GUILD_LIST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_view_guild_list;
	pMsg->byViewType = GUILD_VIEW_DOWN;
	pMsg->dwLastGuildID = lastGuildID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_VIEW_GUILD_LIST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoFindGuild(CRole *poRole, char *guild_name)
{
	INT32 nRetCode = 0;
	C2M_FIND_GUILD* pMsg = (C2M_FIND_GUILD*)m_pPacketAllocator->Alloc(sizeof(C2M_FIND_GUILD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_find_guild;
	pMsg->dwGuildID = 0;
	strxcpy(pMsg->szGuildName, guild_name, GUILD_NAME_LEN);

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_FIND_GUILD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildApplyToJoinGuild(CRole *poRole, UINT32 dwGuildID)
{
	INT32 nRetCode = 0;
	C2M_APPLY_TO_JOIN_GUILD* pMsg = (C2M_APPLY_TO_JOIN_GUILD*)m_pPacketAllocator->Alloc(sizeof(C2M_APPLY_TO_JOIN_GUILD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_apply_to_join_guild;
	pMsg->dwGuildID = dwGuildID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_APPLY_TO_JOIN_GUILD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGetApplyGuildList(CRole *poRole)
{
	INT32 nRetCode = 0;
	C2M_GET_APPLY_GUILD_LIST* pMsg = (C2M_GET_APPLY_GUILD_LIST*)m_pPacketAllocator->Alloc(sizeof(C2M_GET_APPLY_GUILD_LIST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_get_apply_guild_list;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GET_APPLY_GUILD_LIST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGetRevertGuildApp(CRole *poRole, UINT8 byRevertType, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	C2M_REVERT_GUILD_APPLY* pMsg = (C2M_REVERT_GUILD_APPLY*)m_pPacketAllocator->Alloc(sizeof(C2M_REVERT_GUILD_APPLY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_revert_guild_apply;
	pMsg->byRevert = byRevertType;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_REVERT_GUILD_APPLY));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoInviteToJointGuild(CRole *poRole, char *szRoleName)
{
	INT32 nRetCode = 0;
	C2M_INVITE_TO_JOIN_GUILD* pMsg = (C2M_INVITE_TO_JOIN_GUILD*)m_pPacketAllocator->Alloc(sizeof(C2M_INVITE_TO_JOIN_GUILD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_invite_to_join_guild;
	strxcpy(pMsg->szRoleName, szRoleName, ROLE_NAME_LEN);

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_INVITE_TO_JOIN_GUILD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoRevertTheInvitation(CRole *poRole, UINT8 byRevertType, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	C2M_REVERT_GUILD_INVITATION* pMsg = (C2M_REVERT_GUILD_INVITATION*)m_pPacketAllocator->Alloc(sizeof(C2M_REVERT_GUILD_INVITATION));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_revert_guild_invitation;
	pMsg->byResult = byRevertType;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_REVERT_GUILD_INVITATION));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoDisbandGuild(CRole *poRole)
{
	INT32 nRetCode = 0;
	C2M_DISBAND_GUILD* pMsg = (C2M_DISBAND_GUILD*)m_pPacketAllocator->Alloc(sizeof(C2M_DISBAND_GUILD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_disband_guild;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_DISBAND_GUILD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildChangeNotice(CRole *poRole, char *pNotice)
{
	INT32   nRetCode = 0;
    INT32   nSize = 0;
	C2M_GUILD_NOTICE_CHANGE* pMsg = (C2M_GUILD_NOTICE_CHANGE*)m_pPacketAllocator->Alloc(MAX_MESSAGE_SIZE);
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pNotice);

	pMsg->wMsg = c2m_guild_notice_change;
	nSize = strlen(pNotice) + 1;
    strxcpy(pMsg->szNotice, pNotice, nSize);
    pMsg->wSize = sizeof(C2M_GUILD_NOTICE_CHANGE) + nSize;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, pMsg->wSize);
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildForbidChat(CRole *poRole, UINT8 byOp, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	C2M_GUILD_FORBID_CHAT* pMsg = (C2M_GUILD_FORBID_CHAT*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_FORBID_CHAT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_forbid_chat;
	pMsg->byOperation = byOp;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_FORBID_CHAT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildChangePosition(CRole *poRole, UINT8 byPosition, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	C2M_GUILD_CHANGE_POSITION* pMsg = (C2M_GUILD_CHANGE_POSITION*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_CHANGE_POSITION));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_change_position;
	pMsg->byPosition = byPosition;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_CHANGE_POSITION));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildRoleLeave(CRole *poRole)
{
	INT32 nRetCode = 0;
	C2M_GUILD_ROLE_LEAVE* pMsg = (C2M_GUILD_ROLE_LEAVE*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_ROLE_LEAVE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_role_leave;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_ROLE_LEAVE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildBanish(CRole *poRole, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	C2M_GUILD_BANISH_ROLE* pMsg = (C2M_GUILD_BANISH_ROLE*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_BANISH_ROLE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_banish_role;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_BANISH_ROLE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildDemise(CRole *poRole, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	C2M_GUILD_DEMISE* pMsg = (C2M_GUILD_DEMISE*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_DEMISE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_demise;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_DEMISE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildDonation(CRole *poRole, UINT32 dwType, UINT32 dwMoney)
{
	INT32 nRetCode = 0;
	C2G_GUILD_CONTRIBUTE_FUND* pMsg = (C2G_GUILD_CONTRIBUTE_FUND*)m_pPacketAllocator->Alloc(sizeof(C2G_GUILD_CONTRIBUTE_FUND));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_guild_contribute_fund;
	//pMsg->nType = dwType;
	pMsg->nMoney = dwMoney;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_CONTRIBUTE_FUND));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}


BOOL CRobotMessageHandler::DoGuildStorageRight(CRole *poRole, UINT8 byPosition, UINT16 wRight)
{
	INT32 nRetCode = 0;
	C2M_GUILD_CHANGE_STORAGE_RIGHT* pMsg = (C2M_GUILD_CHANGE_STORAGE_RIGHT*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_CHANGE_STORAGE_RIGHT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_change_storage_right;
	pMsg->byPosition = byPosition;
	pMsg->wRight = wRight;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_CHANGE_STORAGE_RIGHT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildDiplomatApply(CRole *poRole, UINT8 byOpType, UINT8 byTimeType, char *szGuildName)
{
	INT32 nRetCode = 0;
	C2M_GUILD_DIPLOMAT_APP* pMsg = (C2M_GUILD_DIPLOMAT_APP*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_DIPLOMAT_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_diplomat_app;
	pMsg->byOpType = byOpType;
	pMsg->byTimeType = byTimeType;
	strxcpy(pMsg->szGuildName, szGuildName, GUILD_NAME_LEN);
	//pMsg->dwGuildID = dwGuildID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_DIPLOMAT_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildGetApplyUnionList(CRole *poRole)
{
	INT32 nRetCode = 0;
	C2M_GUILD_GET_APPLY_UNION_LIST* pMsg = (C2M_GUILD_GET_APPLY_UNION_LIST*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_GET_APPLY_UNION_LIST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_get_apply_union_list;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_GET_APPLY_UNION_LIST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildRevertUnionApp(CRole *poRole, UINT8 byOpType, UINT32 dwGuildID)
{
	INT32 nRetCode = 0;
	C2M_GUILD_REPLY_UNION_APP* pMsg = (C2M_GUILD_REPLY_UNION_APP*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_REPLY_UNION_APP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_reply_union_app;
	pMsg->byOp = byOpType;
	pMsg->dwGuildID = dwGuildID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_REPLY_UNION_APP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildDrawSalary(CRole *poRole)
{
	INT32 nRetCode = 0;
	C2G_GUILD_DRAW_SALARY* pMsg = (C2G_GUILD_DRAW_SALARY*)m_pPacketAllocator->Alloc(sizeof(C2G_GUILD_DRAW_SALARY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_guild_draw_salary;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_DRAW_SALARY));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildViewStorage(CRole *poRole, UINT8 byStorageTag)
{
	INT32 nRetCode = 0;
	C2G_GUILD_VIEW_STORAGE* pMsg = (C2G_GUILD_VIEW_STORAGE*)m_pPacketAllocator->Alloc(sizeof(C2G_GUILD_VIEW_STORAGE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_guild_view_storage;
	pMsg->byStorageTag = byStorageTag;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_VIEW_STORAGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildPushItem(CRole *poRole, UINT16 wConSlot, UINT16 wItemSlot, UINT8 byConSlot, UINT8 bySlot)
{
	INT32 nRetCode = 0;
	C2G_GUILD_PUSH_ITEM* pMsg = (C2G_GUILD_PUSH_ITEM*)m_pPacketAllocator->Alloc(sizeof(C2G_GUILD_PUSH_ITEM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_guild_push_item;
	pMsg->wItemConSlot = wConSlot;
	pMsg->wItemSlot = wItemSlot;
	pMsg->byStorageConSlot = byConSlot;
	pMsg->byStorageSlot = bySlot;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_PUSH_ITEM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildPopItem(CRole *poRole, UINT8 byConSlot, UINT8 bySlot, UINT16 wConSlot, UINT16 wItemSlot)
{
	INT32 nRetCode = 0;
	C2G_GUILD_POP_ITEM* pMsg = (C2G_GUILD_POP_ITEM*)m_pPacketAllocator->Alloc(sizeof(C2G_GUILD_POP_ITEM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_guild_pop_item;
	pMsg->wItemConSlot = wConSlot;
	pMsg->wItemSlot = wItemSlot;
	pMsg->byStorageConSlot = byConSlot;
	pMsg->byStorageSlot = bySlot;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_POP_ITEM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildMoveItem(CRole *poRole, UINT8 bySourceConSlot, UINT8 bySourceSlot, UINT8 byTargetConSlot, UINT8 byTargetSlot)
{
	INT32 nRetCode = 0;
	C2M_GUILD_MOVE_ITEM* pMsg = (C2M_GUILD_MOVE_ITEM*)m_pPacketAllocator->Alloc(sizeof(C2M_GUILD_MOVE_ITEM));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_guild_move_item;
	pMsg->bySourceConSlot = bySourceConSlot;
	pMsg->bySourceSlot = bySourceSlot;
	pMsg->byTargetConSlot = byTargetConSlot;
	pMsg->byTargetSlot = byTargetSlot;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_GUILD_MOVE_ITEM));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildEnterMap(CRole *poRole)
{
	INT32 nRetCode = 0;
	C2G_GUILD_ENTER_MAP* pMsg = (C2G_GUILD_ENTER_MAP*)m_pPacketAllocator->Alloc(sizeof(C2G_GUILD_ENTER_MAP));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_guild_enter_map;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_ENTER_MAP));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoGuildChangeWeather(CRole *poRole, INT8 byWeatherType, INT8 byTimeType)
{
	INT32   nRetCode = 0;
	C2G_GUILD_CHANGE_WEATHER* pMsg = (C2G_GUILD_CHANGE_WEATHER*)m_pPacketAllocator->Alloc(sizeof(C2G_GUILD_CHANGE_WEATHER));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_guild_change_weather;
	pMsg->byTimeType = byTimeType;
	pMsg->byWeatherType = byWeatherType;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_GUILD_CHANGE_WEATHER));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;

}

BOOL CRobotMessageHandler::DoShieldRole(CRole *poRole, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;
	C2M_SHIELD* pMsg = (C2M_SHIELD*)m_pPacketAllocator->Alloc(sizeof(C2M_SHIELD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_shield;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_SHIELD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoRoleRevive(CRole* pRole)
{
	INT32 nRetCode = 0;
	C2G_REVIVE* pMsg = (C2G_REVIVE*)m_pPacketAllocator->Alloc(sizeof(C2G_REVIVE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_revive;
	pMsg->byType = crtFree;

	nRetCode = m_poNotifier->SendToServer(pRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_REVIVE));
	LOG_PROCESS_ERROR(nRetCode);

	INF("role %s send revive message", pRole->GetName());

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoSendChatToMS(CRole* poSrcRole, UINT32 dwTargetID, const char* pcszMessage)
{
	INT32 nRetCode = 0;
	INT32 nMessageSize = 0;
	INT32 nSize = 0;

	LOG_PROCESS_ERROR(poSrcRole);
	LOG_PROCESS_ERROR(pcszMessage);

	nMessageSize = strnlen(pcszMessage, MAX_CHAT_MESSAGE_LEN) + 1;
	PROCESS_ERROR(pcszMessage[nMessageSize - 1] == '\0');

	nSize = sizeof(C2M_CHAT_MESSAGE) + nMessageSize;
	C2M_CHAT_MESSAGE* pMsg = (C2M_CHAT_MESSAGE*)m_pPacketAllocator->Alloc(nSize);
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_chat_message;
	pMsg->wSize = nSize;
	pMsg->dwTargetID = dwTargetID;
	strxcpy(pMsg->szMessage, pcszMessage, nMessageSize);

	nRetCode = m_poNotifier->SendToServer(poSrcRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nSize);
	PROCESS_ERROR(nRetCode);
	return TRUE;

Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoSendChatToGS(CRole* poSrcRole, UINT32 dwTargetID, const char* pcszMessage)
{
	INT32 nRetCode = 0;
	INT32 nMessageSize = 0;
	INT32 nwSize = 0;

	nMessageSize = strnlen(pcszMessage, MAX_CHAT_MESSAGE_LEN) + 1;
	PROCESS_ERROR(pcszMessage[nMessageSize - 1] == '\0');

	nwSize = nMessageSize + sizeof(C2G_CHAT_MESSAGE);
	C2G_CHAT_MESSAGE* pMsg = (C2G_CHAT_MESSAGE*)m_pPacketAllocator->Alloc(nwSize);
	PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_chat_message;
	pMsg->byLocation = cltNormal;
	pMsg->wSize = nwSize;
	pMsg->dwTargetID = dwTargetID;
	strxcpy(pMsg->szMessage, pcszMessage, nMessageSize);
	nRetCode = m_poNotifier->SendToServer(poSrcRole->GetSessionID(), (PACKET_BUFFER*)pMsg, nwSize);
	PROCESS_ERROR(nRetCode);
	return TRUE;

Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoLeaveScene(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_LEAVE_SCENE* pMsg = (C2G_LEAVE_SCENE*)m_pPacketAllocator->Alloc(sizeof(C2G_LEAVE_SCENE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_leave_scene;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_LEAVE_SCENE));
	LOG_PROCESS_ERROR(nRetCode);
	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoRoleWalk(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_ROLE_WALK* pMsg = (C2G_ROLE_WALK*)m_pPacketAllocator->Alloc(sizeof(C2G_ROLE_WALK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_role_walk;
	pMsg->wDestX = ConvertCoordS2N(poRole->GetX());
	pMsg->wDestY = ConvertCoordS2N(poRole->GetY());

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_ROLE_WALK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoRoleRun(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_ROLE_RUN* pMsg = (C2G_ROLE_RUN*)m_pPacketAllocator->Alloc(sizeof(C2G_ROLE_RUN));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_role_run;
	pMsg->wDestX = ConvertCoordS2N(poRole->GetX());
	pMsg->wDestY = ConvertCoordS2N(poRole->GetY());

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_ROLE_RUN));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoRoleRotate(CRole* poRole, INT32 nFaceDirection)
{
	INT32 nRetCode = 0;
	C2G_ROLE_ROTATE* pMsg = (C2G_ROLE_ROTATE*)m_pPacketAllocator->Alloc(sizeof(C2G_ROLE_ROTATE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_role_rotate;
	pMsg->wFaceDirection = (UINT16)nFaceDirection;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_ROLE_ROTATE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoReplayDungeon(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2G_DUNGEON_REPLAY* pMsg = (C2G_DUNGEON_REPLAY*)m_pPacketAllocator->Alloc(sizeof(C2G_DUNGEON_REPLAY));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_dungeon_replay;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_DUNGEON_REPLAY));
	LOG_PROCESS_ERROR(nRetCode);
	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoSelectReward(CRole* poRole, INT32 nType)
{
	INT32 nRetCode = 0;
	C2G_DUNGEON_SELECT_REWARD* pMsg = (C2G_DUNGEON_SELECT_REWARD*)m_pPacketAllocator->Alloc(sizeof(C2G_DUNGEON_SELECT_REWARD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_dungeon_select_reward;
	pMsg->byRewardType = nType;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_DUNGEON_SELECT_REWARD));
	LOG_PROCESS_ERROR(nRetCode);
	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
	return FALSE;
}

BOOL CRobotMessageHandler::DoQueryLineReq(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2M_QUERY_LINE_REQ* pMsg = (C2M_QUERY_LINE_REQ*)m_pPacketAllocator->Alloc(sizeof(C2M_QUERY_LINE_REQ));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_query_line_req;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_QUERY_LINE_REQ));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoChangeLine(CRole* poRole, UINT8 byLineIndex)
{
	INT32 nRetCode = 0;
	C2G_CHANGE_LINE* pMsg = (C2G_CHANGE_LINE*)m_pPacketAllocator->Alloc(sizeof(C2G_CHANGE_LINE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_change_line;
	pMsg->byLineIndex = byLineIndex;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_CHANGE_LINE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

void CRobotMessageHandler::OnQuerySceneDifficulty(CRole* poRole, const char* pData)
{
	G2C_QUERY_SCENE_DIFFICULTY* pMsg = (G2C_QUERY_SCENE_DIFFICULTY*)pData;

	return;
}
//
//BOOL CRobotMessageHandler::DoCreateArenaTeam(CRole* poRole, UINT16 wIConID, const char* pzArenaTeamName)
//{
//	INT32 nRetCode = 0;
//	C2G_CREATE_ARENA_TEAM* pMsg = (C2G_CREATE_ARENA_TEAM*)m_pPacketAllocator->Alloc(sizeof(C2G_CREATE_ARENA_TEAM));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2g_create_arena_team;
//	pMsg->wIconID = wIConID;
//	strxcpy(pMsg->szName, pzArenaTeamName, ROLE_NAME_LEN);
//
//	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_CREATE_ARENA_TEAM));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//
//	return FALSE;
//}
//
//BOOL CRobotMessageHandler::DoJoinArenaTeam(CRole* poRole, UINT32 dwInvitedRoleID)
//{
//	INT32 nRetCode = 0;
//	C2M_JOIN_ARENA_TEAM* pMsg = (C2M_JOIN_ARENA_TEAM*)m_pPacketAllocator->Alloc(sizeof(C2M_JOIN_ARENA_TEAM));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2m_join_arena_team;
//	pMsg->dwInviteRoleID = dwInvitedRoleID;
//
//	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_JOIN_ARENA_TEAM));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//
//	return FALSE;
//}
//
//BOOL CRobotMessageHandler::DoJoinArenaTeamAnswer(CRole* poRole, UINT32 dwInviteRoleID, UINT8 byAnswer)
//{
//	INT32 nRetCode = 0;
//	C2M_JOIN_ARENA_TEAM_ANSWER* pMsg = (C2M_JOIN_ARENA_TEAM_ANSWER*)m_pPacketAllocator->Alloc(sizeof(C2M_JOIN_ARENA_TEAM_ANSWER));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2m_join_arena_team_answer;
//	pMsg->dwTargetRoleID = dwInviteRoleID;
//	pMsg->byAnswer = byAnswer;
//
//	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_JOIN_ARENA_TEAM_ANSWER));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//
//	return FALSE;
//}
//
//BOOL CRobotMessageHandler::DoLeaveArenaTeam(CRole* poRole, UINT32 dwLeaveRoleID)
//{	
//	INT32 nRetCode = 0;
//	C2M_LEAVE_ARENA_TEAM* pMsg = (C2M_LEAVE_ARENA_TEAM*)m_pPacketAllocator->Alloc(sizeof(C2M_LEAVE_ARENA_TEAM));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2m_leave_arena_team;
//	pMsg->dwRoleID = dwLeaveRoleID;
//
//	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_LEAVE_ARENA_TEAM));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//
//	return FALSE;
//}
//
//BOOL CRobotMessageHandler::DoQueryArenaTeamInfo(CRole* poRole)
//{
//	INT32 nRetCode = 0;
//	C2M_QUERY_ARENA_TEAM_INFO* pMsg = (C2M_QUERY_ARENA_TEAM_INFO*)m_pPacketAllocator->Alloc(sizeof(C2M_QUERY_ARENA_TEAM_INFO));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2m_query_arena_team_info;
//
//	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_QUERY_ARENA_TEAM_INFO));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//
//	return FALSE;
//}
//
//BOOL CRobotMessageHandler::DoJoinArena(CRole* poRole, INT32 nArenaType)
//{
//	INT32 nRetCode = 0;
//	C2M_JOIN_ARENA* pMsg = (C2M_JOIN_ARENA*)m_pPacketAllocator->Alloc(sizeof(C2M_JOIN_ARENA));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2m_join_arena;
//	pMsg->byType = nArenaType;
//
//	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_JOIN_ARENA));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//
//	return FALSE;
//}
//
//BOOL CRobotMessageHandler::DoCancelJoinArenaReq(CRole* poRole)
//{
//	INT32 nRetCode = 0;
//	C2M_CANCEL_JOIN_ARENA_REQ* pMsg = (C2M_CANCEL_JOIN_ARENA_REQ*)m_pPacketAllocator->Alloc(sizeof(C2M_CANCEL_JOIN_ARENA_REQ));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2m_cancel_join_arena_req;
//
//	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_CANCEL_JOIN_ARENA_REQ));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//
//	return FALSE;
//}
//
//BOOL CRobotMessageHandler::DoJoinArenaConfirm(CRole* poRole, INT32 nResult)
//{
//	INT32 nRetCode = 0;
//	C2M_JOIN_ARENA_CONFIRM_ACK* pMsg = (C2M_JOIN_ARENA_CONFIRM_ACK*)m_pPacketAllocator->Alloc(sizeof(C2M_JOIN_ARENA_CONFIRM_ACK));
//	LOG_PROCESS_ERROR(pMsg);
//
//	pMsg->wMsg = c2m_join_arena_confirm_ack;
//	pMsg->byResult = nResult;
//
//	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_JOIN_ARENA_CONFIRM_ACK));
//	LOG_PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	if (pMsg)
//		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);
//
//	return FALSE;
//}


BOOL CRobotMessageHandler::DoJoinBattle(CRole* poRole, UINT32 dwBattleMatch)
{
	INT32 nRetCode = 0;
	C2M_JOIN_BATTLE* pMsg = (C2M_JOIN_BATTLE*)m_pPacketAllocator->Alloc(sizeof(C2M_JOIN_BATTLE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_join_battle;
	pMsg->dwBattleMatch = dwBattleMatch;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_JOIN_BATTLE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoCancelJoinBattleReq(CRole* poRole)
{
	INT32 nRetCode = 0;
	C2M_CANCEL_JOIN_BATTLE_REQ* pMsg = (C2M_CANCEL_JOIN_BATTLE_REQ*)m_pPacketAllocator->Alloc(sizeof(C2M_CANCEL_JOIN_BATTLE_REQ));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_cancel_join_battle_req;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_CANCEL_JOIN_BATTLE_REQ));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoJoinBattleConfirm(CRole* poRole, INT32 nResult)
{
	INT32 nRetCode = 0;
	C2M_JOIN_BATTLE_CONFIRM_ACK* pMsg = (C2M_JOIN_BATTLE_CONFIRM_ACK*)m_pPacketAllocator->Alloc(sizeof(C2M_JOIN_BATTLE_CONFIRM_ACK));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_join_battle_confirm_ack;
	pMsg->byResult = nResult;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_JOIN_BATTLE_CONFIRM_ACK));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSpiritChangeExp(CRole* poRole, BOOL bOnline, BOOL bUseMoney)
{
	INT32 nRetCode = 0;
	C2G_SPIRIT_EXP_CHANGE* pMsg = (C2G_SPIRIT_EXP_CHANGE*)m_pPacketAllocator->Alloc(sizeof(C2G_SPIRIT_EXP_CHANGE));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_exp_change;
	pMsg->bIsOnline = bOnline;
	pMsg->bUseMoney = bUseMoney;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_SPIRIT_EXP_CHANGE));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSpiritMoveAir(CRole* poRole, INT32 nSrcBagType, INT32 nSrcIndex, INT32 nTarBagType, INT32 nTarIndex)
{
	INT32 nRetCode = 0;

	C2G_SPIRIT_MOVE_AIR* pMsg = (C2G_SPIRIT_MOVE_AIR*)m_pPacketAllocator->Alloc(sizeof(C2G_SPIRIT_MOVE_AIR));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_move_air;

	pMsg->nSrcBagType = nSrcBagType;
	pMsg->nSrcIndex = nSrcIndex;
	pMsg->nTarBagType = nTarBagType;
	pMsg->nTarIndex = nTarIndex;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_SPIRIT_MOVE_AIR));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSpiritBuyAirSlot(CRole* poRole, INT32 nBagType, INT32 nCount)
{
	INT32 nRetCode = 0;

	C2G_SPIRIT_BUY_AIR_SLOT* pMsg = (C2G_SPIRIT_BUY_AIR_SLOT*)m_pPacketAllocator->Alloc(sizeof(C2G_SPIRIT_BUY_AIR_SLOT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_buy_air_slot;

	pMsg->nBagType = nBagType;
	pMsg->nCount = nCount;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_SPIRIT_BUY_AIR_SLOT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSpiritMergeAir(CRole* poRole, INT32 nSrcIndex)
{
	INT32 nRetCode = 0;

	C2G_SPIRIT_MERGE_AIR* pMsg = (C2G_SPIRIT_MERGE_AIR*)m_pPacketAllocator->Alloc(sizeof(C2G_SPIRIT_MERGE_AIR));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_merge_air;
	pMsg->nSrcCon = nSrcIndex;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_SPIRIT_MERGE_AIR));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSpiritOpenBlood(CRole* poRole, INT32 nPage)
{
	INT32 nRetCode = 0;

	C2G_SPIRIT_BLOOD_OPEN* pMsg = (C2G_SPIRIT_BLOOD_OPEN*)m_pPacketAllocator->Alloc(sizeof(C2G_SPIRIT_BLOOD_OPEN));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_blood_open;
	pMsg->nPage = nPage;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_SPIRIT_BLOOD_OPEN));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSpiritBrushSlot(CRole* poRole, INT32 nPage, INT32 nIndex)
{
	INT32 nRetCode = 0;

	C2G_SPIRIT_BRUSH_SLOT* pMsg = (C2G_SPIRIT_BRUSH_SLOT*)m_pPacketAllocator->Alloc(sizeof(C2G_SPIRIT_BRUSH_SLOT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_brush_slot;
	pMsg->nPage = nPage;
	pMsg->nIndex = nIndex;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_SPIRIT_BRUSH_SLOT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSpiritAddAir(CRole* poRole, INT32 nIndex, INT32 bQuick)
{
	INT32 nRetCode = 0;

	C2G_SPIRIT_ADD_AIR* pMsg = (C2G_SPIRIT_ADD_AIR*)m_pPacketAllocator->Alloc(sizeof(C2G_SPIRIT_ADD_AIR));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_add_air;
	pMsg->bQuick = bQuick;
	pMsg->dwIndex = nIndex;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_SPIRIT_ADD_AIR));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoSpiritExchangeAir(CRole* poRole, INT32 nAirId)
{
	INT32 nRetCode = 0;

	C2G_SPIRIT_EXCHANGE_AIR* pMsg = (C2G_SPIRIT_EXCHANGE_AIR*)m_pPacketAllocator->Alloc(sizeof(C2G_SPIRIT_EXCHANGE_AIR));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_spirit_exchange_air;
	pMsg->wAirID = nAirId;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_SPIRIT_EXCHANGE_AIR));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

//achievement

BOOL CRobotMessageHandler::DoCompleteAchievement(CRole* poRole, INT32 nAchievementID)
{
	INT32 nRetCode = 0;

	C2G_COMPLETE_ACHIEVEMENT* pMsg = (C2G_COMPLETE_ACHIEVEMENT*)m_pPacketAllocator->Alloc(sizeof(C2G_COMPLETE_ACHIEVEMENT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_complete_achievement;
	pMsg->nAchievementID = nAchievementID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_COMPLETE_ACHIEVEMENT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoCompareAchievement(CRole* poRole, UINT32 dwRoleID)
{
	INT32 nRetCode = 0;

	C2G_COMPARE_ACHIEVEMENT* pMsg = (C2G_COMPARE_ACHIEVEMENT*)m_pPacketAllocator->Alloc(sizeof(C2G_COMPARE_ACHIEVEMENT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_compare_achievement;
	pMsg->dwRoleID = dwRoleID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_COMPARE_ACHIEVEMENT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoRewardAchievement(CRole* poRole, INT32 nAchievementID)
{
	INT32 nRetCode = 0;

	C2G_REWARD_ACHIEVEMENT* pMsg = (C2G_REWARD_ACHIEVEMENT*)m_pPacketAllocator->Alloc(sizeof(C2G_REWARD_ACHIEVEMENT));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_reward_achievement;
	pMsg->nAchievementID = nAchievementID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_REWARD_ACHIEVEMENT));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}


// ranklist

BOOL CRobotMessageHandler::DoQueryRanklist(CRole* poRole, INT32 nRankType, INT32 nPage)
{
	INT32 nRetCode = 0;

	C2M_QUERY_RANKLIST* pMsg = (C2M_QUERY_RANKLIST*)m_pPacketAllocator->Alloc(sizeof(C2M_QUERY_RANKLIST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_query_ranklist;
	pMsg->nRanklistID = nRankType;
	pMsg->nPageSize = nPage;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_QUERY_RANKLIST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

// activity

BOOL CRobotMessageHandler::DoActivityReward(CRole* poRole, INT32 nRewardIndex)
{
	INT32 nRetCode = 0;

	C2G_ACTIVITY_REWARD* pMsg = (C2G_ACTIVITY_REWARD*)m_pPacketAllocator->Alloc(sizeof(C2G_ACTIVITY_REWARD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_activity_reward;
	pMsg->nIndex = nRewardIndex;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_ACTIVITY_REWARD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoQueryRoleInfo(CRole* poRole, UINT32 dwTargetRoleID)
{
	INT32 nRetCode = 0;
	ROLE_INFO_CACHE::iterator it;

	C2M_QUERY_ROLE_INFO* pMsg = (C2M_QUERY_ROLE_INFO*)m_pPacketAllocator->Alloc(sizeof(C2M_QUERY_ROLE_INFO));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_query_role_info;
	pMsg->dwRoleID = dwTargetRoleID;
	pMsg->dwCRC = 0;

	it = s_RoleCache.RoleInfoCache.find(dwTargetRoleID);
	if (it != s_RoleCache.RoleInfoCache.end())
	{
		pMsg->dwCRC = it->second;
	}

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_QUERY_ROLE_INFO));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoQueryGuildInfo(CRole* poRole, UINT32 dwGuildID)
{
	INT32 nRetCode = 0;
	GUILD_INFO_CACHE::iterator it;

	C2M_QUERY_GUILD_NAME* pMsg = (C2M_QUERY_GUILD_NAME*)m_pPacketAllocator->Alloc(sizeof(C2M_QUERY_GUILD_NAME));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2m_query_guild_name;
	pMsg->dwGuildID = dwGuildID;
	pMsg->dwCRC = 0;

	it = s_RoleCache.GuildInfoCache.find(dwGuildID);
	if (it != s_RoleCache.GuildInfoCache.end())
	{
		pMsg->dwCRC = it->second;
	}

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2M_QUERY_GUILD_NAME));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

// quest	

BOOL CRobotMessageHandler::DoAcceptQuest(CRole* poRole, INT32 nQuestID, INT32 nAcceptType, INT32 nAcceptSrcID)
{
	INT32 nRetCode = 0;

	C2G_ACCEPT_QUEST* pMsg = (C2G_ACCEPT_QUEST*)m_pPacketAllocator->Alloc(sizeof(C2G_ACCEPT_QUEST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_accept_quest;
	pMsg->nQuestID = nQuestID;
	pMsg->nAcceptType = nAcceptType;
	pMsg->nAcceptSrcID = nAcceptSrcID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_ACTIVITY_REWARD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoCompleteQuest(CRole* poRole, INT32 nQuestID, INT32 nSelectedAwardIdx)
{
	INT32 nRetCode = 0;

	C2G_COMPLETE_QUEST* pMsg = (C2G_COMPLETE_QUEST*)m_pPacketAllocator->Alloc(sizeof(C2G_COMPLETE_QUEST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_complete_quest;
	pMsg->nQuestID = nQuestID;
	pMsg->nSelectedAwardIdx = nSelectedAwardIdx;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_COMPLETE_QUEST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoAbandonQuest(CRole* poRole, INT32 nQuestID)
{
	INT32 nRetCode = 0;

	C2G_ABANDON_QUEST* pMsg = (C2G_ABANDON_QUEST*)m_pPacketAllocator->Alloc(sizeof(C2G_ABANDON_QUEST));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_abandon_quest;
	pMsg->nQuestID = nQuestID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_ABANDON_QUEST));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoInteractWithNpc(CRole* poRole, UINT32 dwNpcID)
{
	INT32 nRetCode = 0;

	C2G_INTERACT_WITH_NPC* pMsg = (C2G_INTERACT_WITH_NPC*)m_pPacketAllocator->Alloc(sizeof(C2G_INTERACT_WITH_NPC));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_interact_with_npc;
	pMsg->dwNpcID = dwNpcID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_INTERACT_WITH_NPC));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;
}

BOOL CRobotMessageHandler::DoOperateDoodad(CRole* poRole, UINT32 dwDoodadID)
{
	INT32 nRetCode = 0;

	C2G_OPERATE_DOODAD* pMsg = (C2G_OPERATE_DOODAD*)m_pPacketAllocator->Alloc(sizeof(C2G_OPERATE_DOODAD));
	LOG_PROCESS_ERROR(pMsg);

	pMsg->wMsg = c2g_operate_doodad;
	pMsg->dwDoodadID = dwDoodadID;

	nRetCode = m_poNotifier->SendToServer(poRole->GetSessionID(), (PACKET_BUFFER*)pMsg, sizeof(C2G_OPERATE_DOODAD));
	LOG_PROCESS_ERROR(nRetCode);

	return TRUE;
Exit0:
	if (pMsg)
		m_pPacketAllocator->Free((PACKET_BUFFER*)pMsg);

	return FALSE;

}

/*****************************************************************************/

void CRobotMessageHandler::OnGSSceneFinish(CRole* poRole, const char* pData)
{
	G2C_SCENE_FINISH* pMsg = (G2C_SCENE_FINISH*)pData;

	return;
}

void CRobotMessageHandler::OnGSDungeonFinishScore(CRole* poRole, const char* pData)
{
	G2C_DUNGEON_FINISH_SCORE* pMsg = (G2C_DUNGEON_FINISH_SCORE*)pData;

	return;
}

void CRobotMessageHandler::OnGSDungeonReward(CRole* poRole, const char* pData)
{
	G2C_DUNGEON_REWARD* pMsg = (G2C_DUNGEON_REWARD*)pData;

	return;
}
//
//void CRobotMessageHandler::OnJoinArenaTeam(CRole* poRole, const char* pData)
//{
//	M2C_JOIN_ARENA_TEAM* pMsg = (M2C_JOIN_ARENA_TEAM*)pData;
//	LOG_PROCESS_ERROR(poRole);
//	
//	if(pMsg->stJoinMember.dwRoleID == poRole->GetObjID())
//		poRole->SetArenaTeamID(pMsg->dwArenaTeamID);
//
//Exit0:
//	return;
//}
//
//void CRobotMessageHandler::OnJoinArenaTeamAsk(CRole* poRole, const char* pData)
//{
//	M2C_JOIN_ARENA_TEAM_ASK* pMsg = (M2C_JOIN_ARENA_TEAM_ASK*)pData;
//
//	return;
//}
//
//void CRobotMessageHandler::OnLeaveArenaTeam(CRole* poRole, const char* pData)
//{
//	M2C_LEAVE_ARENA_TEAM* pMsg = (M2C_LEAVE_ARENA_TEAM*)pData;
//	LOG_PROCESS_ERROR(poRole);
//
//	if(pMsg->dwRoleID == poRole->GetObjID())
//		poRole->SetArenaTeamID(0);
//Exit0:
//	return;
//}
//
//void CRobotMessageHandler::OnArenaTeamInfo(CRole* poRole, const char* pData)
//{
//	M2C_ARENA_TEAM_INFO* pMsg = (M2C_ARENA_TEAM_INFO*)pData;
//
//	return;
//}
//
//void CRobotMessageHandler::OnJoinArenaQueue(CRole* poRole, const char* pData)
//{
//	M2C_JOIN_ARENA_QUEUE* pMsg = (M2C_JOIN_ARENA_QUEUE*)pData;
//	LOG_PROCESS_ERROR(poRole);
//
//	poRole->SetArenaQueueState(TRUE);
//
//Exit0:
//	return;
//}
//
//void CRobotMessageHandler::OnCancelJoinArenaAck(CRole* poRole, const char* pData)
//{
//	M2C_CANCEL_JOIN_ARENA_ACK* pMsg = (M2C_CANCEL_JOIN_ARENA_ACK*)pData;
//	LOG_PROCESS_ERROR(poRole);
//
//	poRole->SetArenaQueueState(FALSE);
//Exit0:
//	return;
//}
//
//void CRobotMessageHandler::OnJoinArenaConfirmReq(CRole* poRole, const char* pData)
//{
//	M2C_JOIN_ARENA_CONFIRM_REQ* pMsg = (M2C_JOIN_ARENA_CONFIRM_REQ*)pData;
//
//	poRole->SetArenaQueueState(FALSE);
//Exit0:
//	return;
//}
//
//void CRobotMessageHandler::OnMSSyncArenaScoreForRole(CRole* pRole, const char* pData)
//{
//	M2C_SYNC_ARENA_SCORE_FOR_ROLE* pMsg = (M2C_SYNC_ARENA_SCORE_FOR_ROLE*)pData;
//	LOG_PROCESS_ERROR(pRole);
//	
//	if(pRole->GetObjID() == pMsg->dwRoleID_win)
//		pRole->SetPersonalArenaScore(pRole->GetPersonalArenaScore() + pMsg->nScoreGain);
//	else if(pRole->GetObjID() == pMsg->dwRoleID_lose)
//		pRole->SetPersonalArenaScore(pRole->GetPersonalArenaScore() - pMsg->nScoreGain);
//	else
//		LOG_PROCESS_ERROR(FALSE);
//Exit0:
//	return;
//
//}
//
//void CRobotMessageHandler::OnMSSyncArenaScoreForTeam(CRole* pRole, const char* pData)
//{
//	M2C_SYNC_ARENA_SCORE_FOR_TEAM* pMsg = (M2C_SYNC_ARENA_SCORE_FOR_TEAM*)pData;
//	LOG_PROCESS_ERROR(pRole);
//
//	if(pRole->GetTeamID() == pMsg->dwTeamID_win)
//		pRole->SetPersonalArenaScore(pRole->GetPersonalArenaScore() + pMsg->nScoreGain);
//	else if(pRole->GetTeamID() == pMsg->dwTeamID_lose)
//		pRole->SetPersonalArenaScore(pRole->GetPersonalArenaScore() - pMsg->nScoreGain);
//	else
//		LOG_PROCESS_ERROR(FALSE);
//Exit0:
//	return;
//}

void CRobotMessageHandler::OnJoinBattleQueue(CRole* poRole, const char* pData)
{
	M2C_JOIN_BATTLE_QUEUE* pMsg = (M2C_JOIN_BATTLE_QUEUE*)pData;
	LOG_PROCESS_ERROR(poRole);

	poRole->SetBattleQueueState(TRUE);

Exit0:
	return;

}

void CRobotMessageHandler::OnCancelJoinBattleAck(CRole* poRole, const char* pData)
{
	M2C_CANCEL_JOIN_BATTLE_ACK* pMsg = (M2C_CANCEL_JOIN_BATTLE_ACK*)pData;
	LOG_PROCESS_ERROR(poRole);

	poRole->SetBattleQueueState(FALSE);
Exit0:
	return;
}

void CRobotMessageHandler::OnJoinBattleConfirmReq(CRole* poRole, const char* pData)
{
	M2C_JOIN_BATTLE_CONFIRM_REQ* pMsg = (M2C_JOIN_BATTLE_CONFIRM_REQ*)pData;

	poRole->SetBattleQueueState(FALSE);
Exit0:
	return;
}

void CRobotMessageHandler::OnLogoutInfo(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_LOGOUT_TIMER* pMsg = (G2C_LOGOUT_TIMER*)pData;
Exit0:
	return;
}

void CRobotMessageHandler::OnCompleteAchievement(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	C2G_COMPLETE_ACHIEVEMENT* pMsg = (C2G_COMPLETE_ACHIEVEMENT*)pData;

	nRetCode = pRole->GetAchievementList().Complete(pMsg->nAchievementID);
	LOG_PROCESS_ERROR(nRetCode);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adAchievement, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adAchievementCount, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnCompareAchievement(CRole* pRole, const char* pData)
{
	return;
}

void CRobotMessageHandler::OnRewardAchievement(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_REWARD_ACHIEVEMENT* pMsg = (G2C_REWARD_ACHIEVEMENT*)pData;

	pRole->GetAchievementList().Reward(pMsg->nAchievementID);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnUpdateAchievementVariable(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_UPDATE_ACHIEVEMENT_VARIABLE* pMsg = (G2C_UPDATE_ACHIEVEMENT_VARIABLE*)pData;

	pRole->GetAchievementList().SetVariable(pMsg->nIndex, pMsg->nValue);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adVariable, pMsg->nIndex);

	switch (pMsg->nIndex)
	{
		case avdKillWarriorCount:
		case avdKillMageCount:
		case avdKillRogueCount:
		case avdKillArcherCount:
			ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adKillPlayerTotalCount, 0);
			break;
		case avdCompleteQuestTotalCount:
			ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adCompleteQuestCount, 0);
			break;
		case avdComposePurpleItem:
		case avdComposeOrangeItem:
			ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adColorItemCompose, 0);
			break;
		case avdDecomposePurpleItem:
		case avdDecomposeOrangeItem:
			ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adColorItemDeCompose, 0);
			break;
		case avdLeaveMaster:
			ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adLeaveStudentCount, 0);
			break;
		default:
			break;
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncAchievementList(CRole* pRole, const char* pData)
{
	G2C_SYNC_ACHIEVEMENT_LIST* pMsg = (G2C_SYNC_ACHIEVEMENT_LIST*)pData;
	pRole->GetAchievementList().RobotSyncAchievementList(pMsg->szData, pMsg->wSize - sizeof(G2C_SYNC_ACHIEVEMENT_LIST), pMsg->nCount);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnActivateHandBook(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_ACTIVATE_HANKBOOK* pMsg = (G2C_ACTIVATE_HANKBOOK*)pData;

	pRole->GetAchievementList().ActivateHandbook(pMsg->nType, pMsg->nIndex);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adHandbook, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSpiritBloodOpen(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_BLOOD_OPEN* pMsg = (G2C_SPIRIT_BLOOD_OPEN*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	pRole->GetSpirit().SetBloodOpen(pMsg->nPage);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSpiritBloodPageCount, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSpiritExpChange(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_EXP_CHANGE* pMsg = (G2C_SPIRIT_EXP_CHANGE*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	pRole->GetSpirit().SetExp(pMsg->nExp);
	pRole->GetSpirit().ChangeSoul2Pts(FALSE, FALSE);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSpiritUp(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_UP* pMsg = (G2C_SPIRIT_UP*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	pRole->GetSpirit().SetLevel(pMsg->nLevel);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSpiritLevel, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSpiritAirChange(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	CAir* pAir = NULL;
	BOOL bNewBagAir = FALSE;

	G2C_SPIRIT_AIR_CHANGE* pMsg = (G2C_SPIRIT_AIR_CHANGE*)pData;

	//Check for newly acquired qi in the qi bag
	pAir = pRole->GetSpirit().GetAir(sasbtBag, pMsg->nIndex);
	if ((NULL == pAir || pAir->nTemplateID != pMsg->nAirID) && sasbtBag == pMsg->nBagType)
	{
		bNewBagAir = TRUE;
	}

	nRetCode = pRole->GetSpirit().SetAir(pMsg->nBagType, pMsg->nAirID, pMsg->nExp, pMsg->nIndex);
	LOG_PROCESS_ERROR(nRetCode);

	if (bNewBagAir)
	{
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSpiritAirColorLevel, 0);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSpiritAirLevelUp(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_AIR_LEVELUP* pMsg = (G2C_SPIRIT_AIR_LEVELUP*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	pRole->GetSpirit().SetProductAirLevel(pMsg->byLevel);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSpiritSlotSizeChange(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_SLOT_SIZE_CHANGE* pMsg = (G2C_SPIRIT_SLOT_SIZE_CHANGE*)pData;

	switch (pMsg->nType)
	{
		case sasbtBag:
			{
				LOG_PROCESS_ERROR(pMsg->nSize >= 0 && pMsg->nSize <= MAX_AIRSEA_BAG_CONTAINER_SIZE);
				pRole->GetSpirit().SetBagContainerSize(pMsg->nSize);
				ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSpiritBuyAirBagSlotCount, 0);
			}
			break;
		case sasbtEquip:
			{
				LOG_PROCESS_ERROR(pMsg->nSize >= 0 && pMsg->nSize <= MAX_AIRSEA_EQUIP_CONTAINER_SIZE);
				pRole->GetSpirit().SetEquipContainerSize(pMsg->nSize);
				ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSpiritBuyAirEquipSlotCount, 0);
			}
			break;
		case sasbtStall:
			{
				LOG_PROCESS_ERROR(pMsg->nSize >= 0 && pMsg->nSize <= MAX_AIRSEA_STALL_CONTAINER_SIZE);
				pRole->GetSpirit().SetStallContainerSize(pMsg->nSize);
				ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSpiritBuyAirStallSlotCount, 0);
			}
			break;
		default:
			{
				LOG_PROCESS_ERROR(FALSE);
			}
			break;
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSpiritBrushSlot(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_BRUSH_SLOT* pMsg = (G2C_SPIRIT_BRUSH_SLOT*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	nRetCode = pRole->GetSpirit().SetBlood(pMsg->nPage - 1, pMsg->nIndex - 1, pMsg->nNumber);
	LOG_PROCESS_ERROR(nRetCode);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSpiritBloodPageCompleteCount, 0);
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSpiritBloodPageLevel, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSpiritNotiryExpChangeTime(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SPIRIT_NOTIFY_EXP_CHANGE_TIME* pMsg = (G2C_SPIRIT_NOTIFY_EXP_CHANGE_TIME*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	if (pMsg->nResultCode == errSpiritChangeCDTime)
	{
		pRole->GetSpirit().SetNextExp2PtsTime(CGameWorld::GetInstance().GetGameTime() + pMsg->nRemainTime);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnHireHero(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_HIRE_HERO* pMsg = (G2C_HIRE_HERO*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	nRetCode = pRole->HireHero(pMsg->byHeroLevel, pMsg->byHeroClass, pMsg->byHeroSex, 0, pMsg->byHeroAiType, FALSE);
	LOG_PROCESS_ERROR(nRetCode);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adHero, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnHeroLevelUp(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_HERO_LEVEL_UP* pMsg = (G2C_HERO_LEVEL_UP*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	if (pRole->GetHero()->GetObjID() == pMsg->dwHeroID)
	{
		nRetCode = pRole->GetHero()->SetLevel(pMsg->byLevel);
		LOG_PROCESS_ERROR(nRetCode);

		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adHero, 0);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnRuneItem(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_RUNE_ITEM* pMsg = (G2C_RUNE_ITEM*)pData;

	if (errSuccess == pMsg->byResult)
	{
		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adRuneWeaponCount, 0);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncVipState(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SYNC_VIP_STATE* pMsg = (G2C_SYNC_VIP_STATE*)pData;

	for (INT32 nVipLevel = vlLevel1; nVipLevel < vlTotal; ++nVipLevel)
	{
		LOG_PROCESS_ERROR(pRole->SetVIPTime(nVipLevel, pMsg->dwVIPTime[nVipLevel]));
	}
	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adVip, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnSyncVipLevel(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;

	G2C_SYNC_VIP_LEVEL* pMsg = (G2C_SYNC_VIP_LEVEL*)pData;
	LOG_PROCESS_ERROR(pMsg);
	LOG_PROCESS_ERROR(pRole);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnMailWriteSuccess(CRole* pRole, const char* pData)
{
	// nothing to do
}

void CRobotMessageHandler::OnMailListRecv(CRole* pRole, const char* pData)
{
	M2C_MAIL_LIST_RECV* pMsg = (M2C_MAIL_LIST_RECV*)pData;

	pRole->ClearMail();
	pRole->ClearAttach();

	for (UINT16 i = 0; i < pMsg->wMailCount; i++)
	{
		pRole->AddMail(pMsg->stBriefMailInfo[i].dwMailID);

		if (pMsg->stBriefMailInfo[i].byAttachment)
			pRole->AddAttach(pMsg->stBriefMailInfo[i].dwMailID);
	}
}

void CRobotMessageHandler::OnMailRead(CRole* pRole, const char* pData)
{
	// nothing to do
}

void CRobotMessageHandler::OnMailDeleteSuccess(CRole* pRole, const char* pData)
{
	M2C_MAIL_DELETE_SUCCESS* pMsg = (M2C_MAIL_DELETE_SUCCESS*)pData;

	pRole->DelMail(pMsg->dwMailID);
}

void CRobotMessageHandler::OnMailNewCount(CRole* pRole, const char* pData)
{
	// nothing to do
}

void CRobotMessageHandler::OnMailGetAttachSuccess(CRole* pRole, const char* pData)
{
	M2C_MAIL_GET_ATTACH_SUCCESS* pMsg = (M2C_MAIL_GET_ATTACH_SUCCESS*)pData;

	pRole->DelAttach(pMsg->dwMailID);
}

void CRobotMessageHandler::OnAuctionSearchType(CRole* pRole, const char* pData)
{
	M2C_AUCTION_SEARCH_TYPE* pMsg = (M2C_AUCTION_SEARCH_TYPE*)pData;
	for (INT32 i = 0; i < pMsg->nItemCount; i++)
	{
		pRole->AddAuctionItemID(pMsg->nItemID[i]);
	}
}

void CRobotMessageHandler::OnAuctionSearch(CRole* pRole, const char* pData)
{
	M2C_AUCTION_SEARCH* pMsg = (M2C_AUCTION_SEARCH*)pData;
}

void CRobotMessageHandler::OnAuctionQuery(CRole* pRole, const char* pData)
{
	// nothing to do
}

void CRobotMessageHandler::OnAuctionSell(CRole* pRole, const char* pData)
{
	M2C_AUCTION_SELL* pMsg = (M2C_AUCTION_SELL*)pData;

	pRole->AddSellingAuction(pMsg->stAuction.dwAuctionID);
}

void CRobotMessageHandler::OnAuctionCancelSell(CRole* pRole, const char* pData)
{
	M2C_AUCTION_CANCEL_SELL* pMsg = (M2C_AUCTION_CANCEL_SELL*)pData;

	pRole->DelSellingAuction(pMsg->dwAuctionID);
}

void CRobotMessageHandler::OnAuctionBuy(CRole* pRole, const char* pData)
{
	M2C_AUCTION_BUY* pMsg = (M2C_AUCTION_BUY*)pData;

	pRole->AddBuyingAuction(pMsg->stAuction.dwAuctionID);
}

void CRobotMessageHandler::OnAuctionFinished(CRole* pRole, const char* pData)
{
	M2C_AUCTION_FINISHED* pMsg = (M2C_AUCTION_FINISHED*)pData;

	pRole->DelSellingAuction(pMsg->dwAuctionID);
	pRole->DelBuyingAuction(pMsg->dwAuctionID);
}

void CRobotMessageHandler::OnAuctionListMySelling(CRole* pRole, const char* pData)
{
	M2C_AUCTION_LIST_MY_SELLING* pMsg = (M2C_AUCTION_LIST_MY_SELLING*)pData;
	UINT32 datalen = 0;
	ItemInfo iteminfo;

	pRole->ClearSellingAuction();

	for (UINT8 i = 0; i < pMsg->byCount; i++)
	{
		AUCTION_ITEM_INFO* aii = (AUCTION_ITEM_INFO*)(pMsg->acAuctionItems + datalen);
		pRole->AddSellingAuction(aii->dwAuctionID);

		datalen += sizeof(AUCTION_ITEM_INFO);
		datalen += iteminfo.Load(aii->acItem);
	}
}

void CRobotMessageHandler::OnAuctionListMyBuying(CRole* pRole, const char* pData)
{
	M2C_AUCTION_LIST_MY_BUYING* pMsg = (M2C_AUCTION_LIST_MY_BUYING*)pData;
	UINT32 datalen = 0;
	ItemInfo iteminfo;

	pRole->ClearBuyingAuction();

	for (UINT8 i = 0; i < pMsg->byCount; i++)
	{
		AUCTION_ITEM_INFO* aii = (AUCTION_ITEM_INFO*)(pMsg->acAuctionItems + datalen);
		pRole->AddBuyingAuction(aii->dwAuctionID);

		datalen += sizeof(AUCTION_ITEM_INFO);
		datalen += iteminfo.Load(aii->acItem);
	}
}

void CRobotMessageHandler::OnMSSyncRoleInfo(CRole* pRole, const char* pData)
{
	M2C_SYNC_ROLE_INFO* pMsg = (M2C_SYNC_ROLE_INFO*)pData;

	if (s_RoleCache.RoleInfoCache.size() >= MAX_ROBOT_CACHE_COUNT)
	{
		s_RoleCache.RoleInfoCache.clear();
	}

	s_RoleCache.RoleInfoCache[pMsg->dwRoleID] = crc32(0, (const Bytef*)pMsg, sizeof(M2C_SYNC_ROLE_INFO));
}

void CRobotMessageHandler::OnActivateMount(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_ACTIVATE_MOUNT* pMsg = (G2C_ACTIVATE_MOUNT*)pData;

	nRetCode = pRole->ActivateMount(pMsg->nMountID);
	LOG_PROCESS_ERROR(nRetCode);

	ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSetCount, 0);

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnOnMount(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	G2C_CHAR_ON_MOUNT* pMsg = (G2C_CHAR_ON_MOUNT*)pData;

	LOG_PROCESS_ERROR(pRole);

	if (pRole->GetObjID() == pMsg->dwCharID && pRole->IsRobot())
	{
		nRetCode = pRole->OnMount(pMsg->byMountID);
		LOG_PROCESS_ERROR(nRetCode);

		ROBOT_ACHIEVEMENT_COMPLETED_CHECK(pRole->GetAchievementList(), adSet, 0);
	}
	else
	{
		nRetCode = pRole->OnMount(pMsg->byMountID);
		LOG_PROCESS_ERROR(nRetCode);
	}

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnOffMount(CRole* pRole, const char* pData)
{
	G2C_CHAR_OFF_MOUNT* pMsg = (G2C_CHAR_OFF_MOUNT*)pData;

	LOG_PROCESS_ERROR(pRole);

	pRole->OffMount();

	return;
Exit0:
	return;
}

void CRobotMessageHandler::OnGSTradeSetMoney(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	CTeamInGS* poTeam = NULL;
	G2C_TRADE_SET_MONEY* pMsg = (G2C_TRADE_SET_MONEY*)pData;

	LOG_PROCESS_ERROR(pRole);
	if (pRole->GetObjID() == pMsg->dwRoleID) // self state sync
	{
		LOG_PROCESS_ERROR(pRole->GetTrade());
		nRetCode = pRole->GetTrade()->SetMoney(pMsg->nMoney);
		LOG_PROCESS_ERROR(nRetCode);
	}
	else // target made a  new change
	{
		if (m_nSuccTradeTendency)
		{
			//INT32 nRandom = g_Random(0, 1);
			//if (nRandom > 0)
			if (pMsg->nMoney % 2 == 0)
			{
				nRetCode = DoTradeSetItem(pRole, TRUE, 1, 1, 1);
				LOG_PROCESS_ERROR(nRetCode);
			}
			else
			{
				nRetCode = DoTradeSetItem(pRole, TRUE, 2, 1, 1);
				LOG_PROCESS_ERROR(nRetCode);
			}
			INT32 nRandom = g_Random(0, 10);
			if (nRandom > 0)
			{
				nRetCode = DoTradeLock(pRole);
				LOG_PROCESS_ERROR(nRetCode);
			}
		}
	}

Exit0:
	return;

}

void CRobotMessageHandler::OnGSTradeSetItem(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	CTeamInGS* poTeam = NULL;
	G2C_TRADE_SET_ITEM* pMsg = (G2C_TRADE_SET_ITEM*)pData;

	LOG_PROCESS_ERROR(pRole);
	if (pRole->GetObjID() == pMsg->dwRoleID) // self state sync
	{
		LOG_PROCESS_ERROR(pRole->GetTrade());

		ItemInfo iteminfo;
		UINT32 itemlen = 0;

		itemlen = iteminfo.Load(pMsg->acItem);
		LOG_PROCESS_ERROR(itemlen > 0);

		nRetCode = pRole->GetTrade()->SetItem(pMsg->byTradeSlot, pMsg->bAdd, iteminfo.m_byConSlot, iteminfo.m_byItemSlot);
		LOG_PROCESS_ERROR(nRetCode);
	}
	else // target made a  new change
	{
		if (m_nSuccTradeTendency)
		{
			LOG_PROCESS_ERROR(pRole->GetItemBag());
			INT32 nMoneyCount = pRole->GetItemBag()->GetMoney(MONEYTYPE_02);
			if (pMsg->bAdd)
			{
				nRetCode = DoTradeSetMoney(pRole, g_Random(1, nMoneyCount));
				LOG_PROCESS_ERROR(nRetCode);
			}
			else
			{
				nRetCode = DoTradeSetMoney(pRole, 0); // sensitive
				LOG_PROCESS_ERROR(nRetCode);
			}
			INT32 nRandom = g_Random(0, 10);
			if (nRandom > 0)
			{
				nRetCode = DoTradeLock(pRole);
				LOG_PROCESS_ERROR(nRetCode);
			}
		}
	}
Exit0:
	return;

}

void CRobotMessageHandler::OnGSTradeStateChange(CRole* pRole, const char* pData)
{
	INT32 nRetCode = 0;
	CTeamInGS* poTeam = NULL;
	G2C_TRADE_STATE_CHANGE* pMsg = (G2C_TRADE_STATE_CHANGE*)pData;

	LOG_PROCESS_ERROR(pRole->IsRobot());

	if (pRole->GetObjID() == pMsg->dwRoleID) // self state sync
	{
		LOG_PROCESS_ERROR(pRole->GetTrade());
		switch (pMsg->byTradeState)	// ETradeState
		{
		case etsFree:
			pRole->GetTrade()->Clear(TRUE);
			break;
		case etsAsking:
			// do nothing
			break;
		case etsBeingAsked:
			break;
		case etsTrading:
			break;
		case etsLocked:
			nRetCode = pRole->GetTrade()->LockTrade();
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case etsConfirmed:
			nRetCode = pRole->GetTrade()->ConfirmTrade();
			LOG_PROCESS_ERROR(nRetCode);
			break;
		case etsSuccess:
			pRole->GetTrade()->Clear(TRUE);
			break;
		}
	}
	else // target made a  new change
	{
		if (m_nSuccTradeTendency)
		{
			INT32 nRandom = 0;
			switch (pMsg->byTradeState)	// ETradeState
			{
			case etsAsking:
				// do nothing
				break;
			case etsBeingAsked:
				nRetCode = pRole->GetTrade()->AskTrade(pMsg->dwRoleID);
				LOG_PROCESS_ERROR(nRetCode);

				nRetCode = DoTradeAccept(pRole, pMsg->dwRoleID);
				LOG_PROCESS_ERROR(nRetCode);
				break;
			case etsTrading:
				nRetCode = pRole->GetTrade()->AcceptTrade(pMsg->dwRoleID);
				LOG_PROCESS_ERROR(nRetCode);

				nRandom = g_Random(0, 1);
				if (nRandom > 0)
				{
					LOG_PROCESS_ERROR(pRole->GetItemBag());
					INT32 nMoneyCount = pRole->GetItemBag()->GetMoney(MONEYTYPE_02);
					nRetCode = DoTradeSetMoney(pRole, g_Random(1, nMoneyCount));
					LOG_PROCESS_ERROR(nRetCode);
				}
				else
				{
					nRandom = g_Random(0, 1);
					if (nRandom > 0)
					{
						nRetCode = DoTradeSetItem(pRole, TRUE, 1, 1, 1);
						LOG_PROCESS_ERROR(nRetCode);
					}
					else
					{
						nRetCode = DoTradeSetItem(pRole, FALSE, 1, 1, 1);
						LOG_PROCESS_ERROR(nRetCode);
					}
				}
				nRandom = g_Random(0, 10);
				if (nRandom > 0)
				{
					nRetCode = DoTradeLock(pRole);
					LOG_PROCESS_ERROR(nRetCode);
				}

				break;
			case etsLocked:
				nRetCode = pRole->GetTrade()->LockTrade();
				LOG_PROCESS_ERROR(nRetCode);

				nRandom = g_Random(0, 10);
				if (nRandom > 0)
				{
					nRetCode = DoTradeLock(pRole);
					LOG_PROCESS_ERROR(nRetCode);

					nRandom = g_Random(0, 10);
					if (nRandom > 0)
					{
						nRetCode = DoTradeConfirm(pRole);
						LOG_PROCESS_ERROR(nRetCode);
					}
				}
				else
				{
					nRetCode = DoTradeUnlock(pRole);
					LOG_PROCESS_ERROR(nRetCode);
				}
				break;
			case etsConfirmed:
				nRetCode = pRole->GetTrade()->ConfirmTrade();
				LOG_PROCESS_ERROR(nRetCode);

				nRandom = g_Random(0, 10000);
				if (nRandom > m_nSuccTradeTendency)
				{
					nRetCode = DoTradeConfirm(pRole);
					LOG_PROCESS_ERROR(nRetCode);
				}
				else
				{
					nRetCode = DoTradeCancel(pRole);
					LOG_PROCESS_ERROR(nRetCode);
				}
				break;
			case etsSuccess:
				pRole->GetTrade()->Clear(true);
				
				INF("role %d completely finish trade with %d", pRole->GetObjID(), pMsg->dwRoleID);
				break;
			}
		}
	}
Exit0:
	return;

}

BOOL CRobotMessageHandler::CTraverseTeam::operator()(UINT32 dwTeamID, CTeamInGS* pstTeam)
{
    PROCESS_SUCCESS(m_nIndex > 0 && m_dwLeaderID > 0);

	LOG_PROCESS_ERROR(pstTeam);
	//     if (GET_GROUP_INDEX_FROM_SESSION_ID(pstTeam->GetLeaderID()) == (GET_GROUP_INDEX_FROM_SESSION_ID(dwSessionID)))
	//     {
	//         if(dwLeaderID == 0 && pstTeam->GetMemberCount() < pstTeam->GetMaxMemberCount())
	//             dwLeaderID = pstTeam->GetLeaderID();
	// 
	//         if(nIndex == 0 && pstTeam->GetMemberCount() < pstTeam->GetMaxMemberCount())
	//         {
	//             dwLeaderID = pstTeam->GetLeaderID();
	//             PROCESS_ERROR(FALSE);
	//         }
	//     }

    m_nIndex--;
Exit1:
	return TRUE;
Exit0:
	return FALSE;
};

#endif
