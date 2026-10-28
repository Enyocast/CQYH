#ifndef _M2C_MESSAGE_H_
#define _M2C_MESSAGE_H_

#include "external_message_header.h"

#pragma pack(push, 1)
namespace ExternalMessage
{
    enum M2C_MESSAGE_ID
    {
        m2c_message_begin = 512,

        // common
        m2c_sync_role_info,
		m2c_error_notify,
		m2c_queue_info,

        // team
        m2c_team_join,
        m2c_team_leave,
        m2c_team_add_member,
        m2c_team_remove_member,
        m2c_team_answer,
        m2c_team_changeinfo,
        m2c_team_sync_memberinfo,
		m2c_team_sync_memberstate,

		m2c_activity_query_team,
		m2c_activity_change_dungeon,

        // friend
        m2c_self_info,
        m2c_friend_list,
        m2c_friend_info_change,
        m2c_friend_add,
        m2c_friend_del,
        m2c_friend_added_by,
        m2c_friend_deleted_by,
        m2c_friend_chat,
        m2c_personal_enemy_add,
        m2c_personal_enemy_del,

		// chat
        m2c_chat_message,

		// quest
		m2c_publish_quest,

		//line
		m2c_query_line_ack,

        // master
        m2c_master_twitter_ack,
        m2c_master_hello_teacher,
        m2c_master_recruit_list,        // Send mentorship recruitment list
        //m2c_master_recruit_ack,         // Result of applying for or canceling recruitment
        m2c_master_get_solo_list_ack,       // Return list of prospective students

        m2c_master_info,
        m2c_master_sync_lvl,

        m2c_master_stud_submit_app_ack,
        m2c_master_stud_submit_app_ntf,         // Mentor receives a student application
        m2c_master_agree_stud_app_ack,
        m2c_master_refuse_stud_app_ack,         // Sent to the mentor
        m2c_master_refuse_stud_app_ntf,         // Sent to the student when rejected by the mentor
        m2c_master_cancel_stud_app_ack,
        m2c_master_cancel_stud_app_ntf,

        m2c_master_teacher_submit_app_ack,
        m2c_master_teacher_submit_app_ntf,
        m2c_master_agree_teacher_app_ack,
        m2c_master_refuse_teacher_app_ack,
        m2c_master_refuse_teacher_app_ntf,
        m2c_master_cancel_teacher_app_ack,
        m2c_master_cancel_teacher_app_ntf,

        m2c_master_leave_teacher_ack,
        m2c_master_leave_teacher_ntf,
        m2c_master_fire_student_ack,
        m2c_master_fire_student_ntf,

        m2c_master_add_student_ntf,
        m2c_master_del_student_ntf,
        m2c_master_clear_info,

        m2c_master_cz_level,
        m2c_master_cz_ack,
        m2c_master_grad,

        // mail
        m2c_mail_write_success,
        m2c_mail_list_recv,
        m2c_mail_read,
        m2c_mail_delete_success,
        m2c_mail_new_count,
        m2c_mail_get_attach_success,

		//battle
		m2c_join_battle_queue,
		m2c_cancel_join_battle_ack,
		m2c_join_battle_confirm_req,

        // guild
        m2c_query_guild_name_ack,
        m2c_create_guild_ack,
        m2c_view_guild_list_ack,
        m2c_more_guild_info_ack,
        m2c_find_guild_ack,
        m2c_guild_info_ntf,
        m2c_apply_to_join_guild_ack,
        m2c_get_apply_guild_list_ack,
        m2c_revert_guild_apply_ack,
        m2c_del_guild_app,
        m2c_guild_add_member_ntf,
        m2c_guild_del_member_ntf,
        m2c_be_invited_to_join_guild,
        m2c_invite_to_join_guild_ack,
        m2c_disband_guild_ntf,
        m2c_guild_notice_change,
        m2c_guild_forbid_chat_ntf,
        m2c_guild_change_position_ntf,
        m2c_guild_role_leave_ntf,
        m2c_guild_role_leave_ack,
        m2c_guild_demise_ntf,
        m2c_guild_contribute_ack,
        m2c_guild_attr_modify_ntf,
        m2c_guild_apply_alliance_ack,
        m2c_guild_get_apply_union_list_ack,
        m2c_guild_reply_union_app_ack,
        m2c_guild_add_diplomat_ntf,
        m2c_guild_del_diplomat_ntf,

        m2c_guild_notify_ntf,

        m2c_guild_change_storage_right_ntf,
        m2c_guild_view_storage_ack,
        m2c_guild_storage_event,
        m2c_guild_push_item_ack,
        m2c_guild_pop_item_ack,
        m2c_guild_move_item_ack,
        m2c_guild_add_history_event_ntf,
        m2c_guild_add_storage_event_ntf,

        m2c_guild_member_salary_change,
        m2c_guild_more_history,
        m2c_guild_more_chest,
        m2c_guild_join_guild_ntf,

        m2c_guild_upgrade_welfare_ntf,
        m2c_guild_update_welfare_ntf,
        m2c_guild_cancel_welfare_upgrade_ntf,
        m2c_guild_upgrade_building_ntf,
        m2c_guild_update_building_ntf,
        m2c_guild_cancel_building_upgrade_ntf,
        m2c_guild_del_building_ntf,

        m2c_guild_get_dungeon_list_ack,
        m2c_guild_open_dungeon_ack,
        m2c_guild_dungeon_award,
        m2c_guild_battle_achievement,
        m2c_guild_building_state_ntf,
        m2c_guild_sync_war_cd_ntf,

        m2c_guild_achievement_ack,

        m2c_guild_join_war_ntf,

        // arena
        m2c_arena_get_data_ack,
        m2c_arena_end,
        m2c_arena_match_begin_ntf,

        // 
        m2c_sync_social_attr_ntf,

        // auction
        m2c_auction_search_type,
        m2c_auction_search,
        m2c_auction_query,
        m2c_auction_sell,
        m2c_auction_cancel_sell,
        m2c_auction_buy,
        m2c_auction_finished,
        m2c_auction_list_my_selling,
        m2c_auction_list_my_buying,

        // exchange
        m2c_exchange_add_order,
        m2c_exchange_cancel_order,
        m2c_exchange_list_prices,
        m2c_exchange_list_my_orders,
        m2c_exchange_list_my_logs,

        // real money shop
        m2c_sync_real_money,
        m2c_sync_real_money_shop_data,
        m2c_real_money_buy,
        m2c_real_money_shop_log,
        m2c_sale_info,

		// ranklist
		m2c_query_ranklist,

		// sabac
		m2c_occupy_sabac,
		m2c_enroll_sabac,
		m2c_erect_statue,
		m2c_sabac_winner_login,

        // fcm
        m2c_fcm_state,

        // time
        m2c_time_info,
        m2c_buy_time,
        m2c_free_mode,

        m2c_message_end = 1000,
    };

    struct M2C_SYNC_ROLE_INFO : MESSAGE_HEADER
    {
        UINT32                  dwRoleID;
        char                    szRoleName[ROLE_NAME_LEN];
        UINT8                   byClass;
        UINT8                   bySex;
        UINT8                   byVIPLevel;
		char					szGuildName[GUILD_NAME_LEN];
    };

    struct TEAM_MEMBER_BASEINFO
    {
        UINT32                  dwRoleID;
        char                    szRoleName[ROLE_NAME_LEN];
        UINT8                   bySex;
        UINT8                   byClass;
		UINT8					byState;
    };

    struct TEAM_SYNC_MEMBERINFO
    {
        UINT32                  dwRoleID;
        INT32                   nLevel;
        INT32                   nMaxHp;
        INT32                   nMaxMp;
        INT32                   nCurHp;
        INT32                   nCurMp;
		UINT32					dwSceneTempID;
		INT32					nSceneID;
		INT32					nX;
		INT32					nY;
		INT32					nZ;
    };

    struct M2C_TEAM_JOIN : FLEX_MESSAGE_HEADER
    {
        UINT32                  dwTeamID;
        char                    szTeamName[TEAM_NAME_LEN];
        UINT8                   byAssignType;
        UINT32                  dwLeadID;
        INT32                   nMemberSizeLimit;
        UINT8                   byMemberCount;
		UINT8					byActivityType;
		UINT32					dwActivityID;
        TEAM_MEMBER_BASEINFO    stTeamMemberList[0];
    };

    struct M2C_TEAM_LEAVE : MESSAGE_HEADER
    {
        UINT32                  dwTeamID;
    };

    struct M2C_TEAM_ADD_MEMBER : MESSAGE_HEADER
    {
        UINT32                  dwTeamID;
        TEAM_MEMBER_BASEINFO    stAddMember;
    };

    struct M2C_TEAM_REMOVE_MEMBER : MESSAGE_HEADER
    {
        UINT32                  dwTeamID;
        UINT32                  dwRemoveMemberID;
    };

    struct M2C_TEAM_ANSWER : MESSAGE_HEADER
    {
        UINT32                  dwAnswerRequestRoleID;
        UINT8                   byAnswerType;
        char                    szRequestRoleName[ROLE_NAME_LEN];
    };

    struct M2C_TEAM_CHANGEINFO : MESSAGE_HEADER
    {
        UINT32                  dwTeamID;
        char                    szTeamName[TEAM_NAME_LEN];
        INT32                   nTeamMemberLimit;
        UINT8                   byAssignType;
		UINT8					byAuctionItemColorLimit;
        UINT32                  dwLeadID;
        UINT32                  dwRoomID;
    };

    struct M2C_TEAM_SYNC_MEMBERINFO : MESSAGE_HEADER
    {
        UINT32                  dwTeamID;
        TEAM_SYNC_MEMBERINFO    stMember;
    };

	struct M2C_TEAM_SYNC_MEMBERSTATE : MESSAGE_HEADER
	{
		UINT32                  dwRoleID;
		UINT8					byState;
	};

    struct FRIEND_INFO
    {
        UINT32                  dwRoleID;
        char                    szRoleName[ROLE_NAME_LEN];
        char                    szSignature[SIGNATURE_LEN];
        UINT8                   byClass;
        UINT8                   bySex;
        UINT8                   byFriendState;
        INT32		            nSceneTempID;
    };

    struct FRIEND_INFO_WITH_GROUP
    {
        FRIEND_INFO             stFriendInfo;
        UINT8                   byGroup;
        UINT8                   bMutual;
    };

    struct M2C_SELF_INFO : MESSAGE_HEADER
    {
        char                    szSignature[SIGNATURE_LEN];
    };

    struct M2C_FRIEND_LIST : FLEX_MESSAGE_HEADER
    {
        UINT8                   byFansCount;
        UINT8                   byFriendCount;
        FRIEND_INFO_WITH_GROUP  stFriendInfoWithGroup[0];
    };

    struct M2C_FRIEND_INFO_CHANGE : MESSAGE_HEADER
    {
        FRIEND_INFO             stFriendInfo;
    };

    struct M2C_FRIEND_ADD : MESSAGE_HEADER
    {
        UINT32                  dwRoleID;
        char                    szRoleName[ROLE_NAME_LEN];
        UINT8                   bMutual;
    };

    struct M2C_FRIEND_DEL : MESSAGE_HEADER
    {
        UINT32                  dwRoleID;
    };

    struct M2C_FRIEND_ADDED_BY : MESSAGE_HEADER
    {
        UINT32                  dwRoleID;
        char                    szRoleName[ROLE_NAME_LEN];
    };

    struct M2C_FRIEND_DELETED_BY : MESSAGE_HEADER
    {
        UINT32                  dwRoleID;
        char                    szRoleName[ROLE_NAME_LEN];
    };

    struct M2C_FRIEND_CHAT : FLEX_MESSAGE_HEADER
    {
        UINT32                  dwFrom;
        UINT8                   byColor;
        char                    szMessage[0];
    };

    struct M2C_PERSONAL_ENEMY_ADD : MESSAGE_HEADER
    {
        UINT32                  dwRoleID;
    };

    struct M2C_PERSONAL_ENEMY_DEL : MESSAGE_HEADER
    {
        UINT32                  dwRoleID;
    };

	struct ACTIVITY_TEAM
	{
		char	szTeamName[TEAM_NAME_LEN];
		INT32	nTeamID;
		UINT32	dwLeaderID;
		UINT32	nMemberID[MAX_TEAM_MEMBER_COUNT];
	};

	struct M2C_ACTIVITY_QUERY_TEAM : MESSAGE_HEADER
	{
		UINT32	dwActivityType;
		INT32	nActivityID;
		INT32	nPage;
		ACTIVITY_TEAM	stRoomTeam[MAX_TEAM_COUNT_PER_PAGE];
	};

	struct M2C_ACTIVITY_CHANGE_DUNGEON : MESSAGE_HEADER
	{
		UINT32				dwActivityType;
		INT32				nActivityID;
		BOOL	bResult;
	};

    struct M2C_ERROR_NOTIFY : MESSAGE_HEADER
    {
        INT32       nErrorCode;
        INT32       nParam1;
        INT32       nParam2;
    };

	struct M2C_QUEUE_INFO : MESSAGE_HEADER
	{
		INT32		nTotal;
		INT32		nSelfPos;
	};

	struct M2C_CHAT_MESSAGE : FLEX_MESSAGE_HEADER
	{
		UINT32				dwSrcID;
		UINT32				dwTargetID;
		unsigned			uLocation	: 4;
		unsigned			bGM			: 1;
		unsigned			uReserved	: 3;
		char				szMessage[0];
	};
	struct M2C_PUBLISH_QUEST : MESSAGE_HEADER
	{
		UINT32				dwMasterRoleID;
		INT32				nQuestID;
	};

	struct LINE_SCENE_DATA
	{
		UINT32		dwSceneID;
		UINT8		byState;
	};

	struct M2C_QUERY_LINE_ACK : FLEX_MESSAGE_HEADER
	{
		UINT16			wCount;
		UINT32			dwSceneTempID;
		LINE_SCENE_DATA	LineSceneData[0];
	};

    // master
    //struct M2C_MASTER_RECRUIT_ACK : MESSAGE_HEADER
    //{
    //    UINT32          dwType;
    //};

    struct M2C_MASTER_TWITTER_ACK : MESSAGE_HEADER
    {
        UINT8       byTwitter;
    };

    struct M2C_MASTER_HELLO_TEACHER : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        UINT8       byLevel;
    };

    struct M2C_MASTER_RECRUIT_LIST : FLEX_MESSAGE_HEADER
    {
        struct RECRUIT_MASTER_INFO
        {
            UINT8       byLevel;
            UINT8       byClass;
            UINT32      dwRoleID;
			INT64		llMasterExp;
        };
        UINT8               byCount;
        RECRUIT_MASTER_INFO szListData[0];
    };

    struct M2C_MASTER_GET_SOLO_LIST_ACK : FLEX_MESSAGE_HEADER 
    {
        struct MASTER_SOLO_INFO
        {
            UINT32      dwRoleID;
            UINT8       byLevel;
            UINT8       byClass;
        };
        UINT8               byCount;
        MASTER_SOLO_INFO    szListData[0];
    };

    struct MASTER_STUDENT_INFO 
    {
        UINT32      dwStudentID;
        UINT8       byCZCount;
        UINT8       byLevel;
    };

    struct M2C_MASTER_INFO : FLEX_MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
        UINT8       byTeacherLevel;
        UINT8       byStudentNum;
        MASTER_STUDENT_INFO arrInfo[0];
    };

    struct M2C_MASTER_SYNC_LVL : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        UINT8       byLevel;
    };

    struct M2C_MASTER_STUD_SUBMIT_APP_ACK : MESSAGE_HEADER
    {
        UINT32          dwMasterID;
    };

    struct M2C_MASTER_STUD_SUBMIT_APP_NTF : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
    };

    struct M2C_MASTER_AGREE_STUD_APP_ACK : MESSAGE_HEADER 
    {
        UINT32          dwStudentID;
    };

    struct M2C_MASTER_REFUSE_STUD_APP_ACK : MESSAGE_HEADER 
    {
        UINT32          dwStudentID;
    };

    struct M2C_MASTER_REFUSE_STUD_APP_NTF : MESSAGE_HEADER 
    {
        UINT32          dwTeacherID;
    };

    struct M2C_MASTER_CANCEL_STUD_APP_ACK : MESSAGE_HEADER 
    {
        UINT32          dwTeacherID;
    };

    struct M2C_MASTER_CANCEL_STUD_APP_NTF : MESSAGE_HEADER 
    {
        UINT32          dwStudentID;
    };

    struct M2C_MASTER_TEACHER_SUBMIT_APP_ACK : MESSAGE_HEADER
    {
        UINT32          dwStudentID;
    };

    struct M2C_MASTER_TEACHER_SUBMIT_APP_NTF : MESSAGE_HEADER
    {
        UINT8           bySourceType;       // enum MASTER_TEACHER_APP_TYPE
        UINT8           byLevel;
        UINT32          dwTeacherID;
        INT32           nMasterExp;
    };

    struct M2C_MASTER_AGREE_TEACHER_APP_ACK : MESSAGE_HEADER 
    {
        UINT32          dwTeacherID;
    };

    struct M2C_MASTER_REFUSE_TEACHER_APP_ACK : MESSAGE_HEADER
    {
        UINT32          dwTeacherID;
    };

    struct M2C_MASTER_REFUSE_TEACHER_APP_NTF : MESSAGE_HEADER
    {
        UINT32          dwStudentID;
    };

    struct M2C_MASTER_CANCEL_TEACHER_APP_ACK : MESSAGE_HEADER
    {
        UINT32          dwStudentID;
    };

    struct M2C_MASTER_CANCEL_TEACHER_APP_NTF : MESSAGE_HEADER
    {
        UINT32          dwTeacherID;
    };

    struct M2C_MASTER_LEAVE_TEACHER_ACK : MESSAGE_HEADER 
    {
    };

    struct M2C_MASTER_LEAVE_TEACHER_NTF : MESSAGE_HEADER
    {
        UINT32          dwStudentID;
    };

    struct M2C_MASTER_FIRE_STUDENT_ACK : MESSAGE_HEADER
    {
        UINT32          dwStudentID;
    };

    struct M2C_MASTER_FIRE_STUDENT_NTF : MESSAGE_HEADER
    {
        UINT32          dwStudentID;
    };


    struct M2C_MASTER_CANCEL_STUD_APP : MESSAGE_HEADER
    {
        UINT32          dwRoleID;
    };

    struct M2C_MASTER_REFUSE_STUD_APP : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct M2C_MASTER_ADD_MASTER : MESSAGE_HEADER
    {
        UINT32          dwMasterID;
        UINT8           byLevel;
        UINT8           byClass;
        UINT32          dwMasterExp;
    };

    struct M2C_MASTER_LEAVE_MASTER : MESSAGE_HEADER
    {
        UINT8       byDealType;
        UINT32      dwOtherID;
    };

    struct M2C_MASTER_FIRE_STUD : MESSAGE_HEADER
    {
        UINT32      dwStudentID;
    };

    struct M2C_MASTER_ADD_STUDENT_NTF : MESSAGE_HEADER
    {
        UINT32              dwStudentID;
    };

    struct M2C_MASTER_DEL_STUDENT_NTF : MESSAGE_HEADER 
    {
        UINT32              dwStudentID;
    };

    struct M2C_MASTER_CLEAR_INFO : MESSAGE_HEADER 
    {
    };

    struct M2C_MASTER_CZ_LEVEL : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
        UINT8               byCZLevel;
    };

    struct M2C_MASTER_CZ_ACK : MESSAGE_HEADER 
    {
        UINT32              dwTargetRoleID;
    };

    struct M2C_MASTER_GRAD : MESSAGE_HEADER 
    {
        UINT32          dwStudentID;
    };

    struct M2C_MAIL_WRITE_SUCCESS : MESSAGE_HEADER
    {

    };

    struct BriefMailInfo
    {
        UINT32          dwMailID;
        UINT32          dwMailTime;
        UINT8           byMailType;
        UINT8           byNew;
        UINT8           byAttachment;
        char            szSenderRoleName[ROLE_NAME_LEN];
        char            szMailSubject[MAIL_SUBJECT_LEN];
    };

    struct M2C_MAIL_LIST_RECV : FLEX_MESSAGE_HEADER
    {
        UINT16          wMailCount;
        BriefMailInfo   stBriefMailInfo[0];
    };

    struct M2C_MAIL_READ : MESSAGE_HEADER
    {
        UINT32          dwMailID;
        UINT32          dwMailTime;
        UINT8           byMailType;
        INT32           nAttachmentItemID;
        INT32           nAttachmentItemCount;
        char            szSenderRoleName[ROLE_NAME_LEN];
        char            szMailSubject[MAIL_SUBJECT_LEN];
        char            szMailContent[MAIL_CONTENT_LEN];
    };

    struct M2C_MAIL_DELETE_SUCCESS : MESSAGE_HEADER
    {
        UINT32          dwMailID;
    };

    struct M2C_MAIL_NEW_COUNT : MESSAGE_HEADER
    {
        UINT32          dwMailNewCount;
    };

    struct M2C_MAIL_GET_ATTACH_SUCCESS : MESSAGE_HEADER
    {
        UINT32          dwMailID;
    };

	struct M2C_JOIN_BATTLE_QUEUE : MESSAGE_HEADER
	{
		UINT32	dwAverageQueueTime;
	};
	struct M2C_CANCEL_JOIN_BATTLE_ACK : MESSAGE_HEADER
	{
		UINT32 dwCancelJoinRoleID;
	};
	struct M2C_JOIN_BATTLE_CONFIRM_REQ : MESSAGE_HEADER
	{
		UINT32 dwSceneTempID;
	};

    struct M2C_QUERY_GUILD_NAME_ACK : MESSAGE_HEADER 
    {
		UINT32		dwGuildID;
		char		szGuildName[GUILD_NAME_LEN];
		UINT32		dwLeaderID;
        UINT32      dwCreateTime;
		UINT8		byMemberCount;
		UINT8		byMainLevel;
		UINT8		byHouseLevel;
		unsigned	bySabacState;
    };

    struct M2C_CREATE_GUILD_ACK : MESSAGE_HEADER
    {
        char    szGuildName[GUILD_NAME_LEN];
    };

    struct GUILD_VIEW_SUMMARY
    {
        UINT32  dwGuildID;
        char    szGuildName[GUILD_NAME_LEN];
        UINT8   byGuildLevel;
        UINT8   byCurrentMemberCount;
        UINT32  dwProtectionTime;
        char    szLeaderName[ROLE_NAME_LEN];
        char    szCreaterName[ROLE_NAME_LEN];
        UINT32  dwCreateTime;
        char    szAnnounce[GUILD_ANNOUNCE_LEN];
        UINT8   arrBuildingLevel[GUILD_B_NUM];
    };

    struct M2C_VIEW_GUILD_LIST_ACK : FLEX_MESSAGE_HEADER
    {
        UINT8       byViewType;
        UINT8       byCount;
        GUILD_VIEW_SUMMARY     info[0];
    };

    struct M2C_MORE_GUILD_INFO_ACK : MESSAGE_HEADER 
    {
        INT32       nMatchWarConsumption;
        UINT8       byMatchCount;
    };

    struct M2C_FIND_GUILD_ACK : MESSAGE_HEADER
    {
        GUILD_VIEW_SUMMARY     data;
    };

    struct GUILD_MEMBER_INFO 
    {
        UINT32  dwRoleID;
        char    szRoleName[ROLE_NAME_LEN];
        UINT8   byPosition;
        UINT8   byLevel;
        UINT8   byClass;
        INT32   nSceneID;
        INT32   nLastLoginTime;
        INT32   nNextSalary;
        UINT8   byFlag;
    };

    struct GUILD_EVENT_INFO 
    {
        UINT8       byType;
        UINT32      param1;
        UINT32      param2;
        UINT32      param3;
        UINT32      param4;
        UINT32      dwTime;
    };

    struct GUILD_HISTORY_EVENT_INFO 
    {
        UINT8       byEventCount;
        GUILD_EVENT_INFO    stEventInfo[50];        // GUILD_DATA_NTF_HISTORY_NUM
    };

    struct GUILD_CHEST_EVENT_INFO 
    {
        UINT8       byCount;
        GUILD_EVENT_INFO    stEvent[50];
    };

    struct GUILD_DIPLOMAT_INFO
    {
        UINT8       byType;         //GUILD_DIPLOMAT_OP_TYPE
        UINT32      dwGuildID;
        UINT32      dwLastTime;
        UINT8       byLevel;
        UINT8       byMemberCount;
        char        szGuildName[GUILD_NAME_LEN];
    };

    struct G_B_DATA
    {
        UINT64      qwNameID;
        INT32       nType;
        INT32       nLevel;
    };

    struct G_B_U_DATA 
    {
        UINT64      qwNameID;
        INT32       nTime;
    };

    struct M2C_GUILD_INFO_NTF : FLEX_MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        char        szGuildName[GUILD_NAME_LEN];
        UINT8       byLevel;
        UINT8       byMemberCount;          // num of GUILD_MEMBER_INFO
        UINT32      dwGuildMoney;
        UINT32      dwCreateTime;
        UINT32      dwLeaderID;
        char        szLeaderName[ROLE_NAME_LEN];
        char        szCreaterName[ROLE_NAME_LEN];
        char        szNotice[GUILD_NOTICE_LEN];

        UINT32      dwAttackCD;
        UINT32      dwProtectionTime;

        // manager
        UINT16      wStorageRight[GUILD_POSITION_COUNT];           // GUILD_POSITION_COUNT
        // history event info
        GUILD_HISTORY_EVENT_INFO    stEventInfo;
        GUILD_CHEST_EVENT_INFO      stChestInfo;

        // diplomat
        UINT8       byAllianceCount;
        GUILD_DIPLOMAT_INFO     stAlliance[GUILD_MAX_ALLIANCE_NUM];
        UINT8       byEnemyCount;
        GUILD_DIPLOMAT_INFO     stEnemy[GUILD_MAX_ENEMY_NUM];

        INT32       nHerb;
        INT32       nWood;
        INT32       nCrystal;
        INT32       nSilver;

        INT32       nProsperity;

        INT32       arrVariables[MAX_GUILD_VARIABLE_COUNT];

        G_B_DATA    arrBData[GUILD_MAX_BUILDING_NUM];       // Changed to a variable-length packet, Allan Tao [19.3.2014]
        G_B_U_DATA  arrBUData[GUILD_MAX_UPGRADE_BUILDING_COUNT];
        INT8        arrWelfareAuraLvl[GUILD_MAX_WELFARE_AURA_COUNT];
        INT8        arrWelfareUpgradeAuraID[GUILD_MAX_UPGRADE_AURA_COUNT];
        INT32       arrWelfareAuraUpgradeTime[GUILD_MAX_UPGRADE_AURA_COUNT];

        GUILD_MEMBER_INFO   arrMemberData[0];
    };

    struct M2C_APPLY_TO_JOIN_GUILD_ACK : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
    };

    struct GUILD_APPLICANT_INFO
    {
        UINT32      dwRoleID;
        char        szRoleName[ROLE_NAME_LEN];
        UINT8       byLevel;
        UINT8       byClass;
        UINT32      dwEndTime;
    };

    struct M2C_GET_APPLY_GUILD_LIST_ACK : FLEX_MESSAGE_HEADER
    {
        UINT16      wAppCount;
        GUILD_APPLICANT_INFO    info[0];
    };

    struct M2C_REVERT_GUILD_APPLY_ACK : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct M2C_DEL_GUILD_APP : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
    };

    struct M2C_GUILD_ADD_MEMBER_NTF : MESSAGE_HEADER
    {
        GUILD_MEMBER_INFO   info;
    };

    struct M2C_GUILD_DEL_MEMBER_NTF : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
    };

    struct M2C_BE_INVITED_TO_JOIN_GUILD : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
        char    szRoleName[ROLE_NAME_LEN];
        char    szGuildName[GUILD_NAME_LEN];
    };

    struct M2C_INVITE_TO_JOIN_GUILD_ACK : MESSAGE_HEADER
    {
        UINT8   byReplyType;
        char    szRoleName[ROLE_NAME_LEN];
    };

    struct M2C_DISBAND_GUILD_NTF : MESSAGE_HEADER
    {
    };

    struct M2C_GUILD_NOTICE_CHANGE : FLEX_MESSAGE_HEADER
    {
        char        szNotice[0];        // GUILD_NOTICE_LEN
    };

    struct M2C_GUILD_FORBID_CHAT_NTF : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
        UINT8   byOp;                   // GUILD_FORBID_CHAT_ENUM
    };

    struct M2C_GUILD_CHANGE_POSITION_NTF : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
        UINT8   byPosition;
    };

    struct M2C_GUILD_ROLE_LEAVE_NTF : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct M2C_GUILD_ROLE_LEAVE_ACK : MESSAGE_HEADER
    {
        UINT8       byLeaveType;
    };

    struct M2C_GUILD_DEMISE_NTF : MESSAGE_HEADER
    {
        UINT32      dwOldLeaderID;
        UINT32      dwNewLeaderID;
    };

    struct M2C_GUILD_CONTRIBUTE_ACK : MESSAGE_HEADER 
    {
        INT32       nType;
        INT32       nValue;
    };

    struct M2C_GUILD_ATTR_MODIFY_NTF : MESSAGE_HEADER
    {
        INT32       nGuildAttrType;            // GUILD_ATTR_ENUM
        INT32       dwGuildAttrValue;
    };

    struct M2C_GUILD_APPLY_ALLIANCE_ACK : MESSAGE_HEADER 
    {
        UINT32      dwGuildID;
    };

    struct APPLY_ALLIANCE_INFO 
    {
        UINT32      dwGuildID;
        char        szGuildName[GUILD_NAME_LEN];
        UINT8       byLevel;
        UINT8       byMemberCount;
        char        szLeaderName[ROLE_NAME_LEN];
        UINT32      dwWashoutTime;
    };

    struct M2C_GUILD_GET_APPLY_UNION_LIST_ACK : FLEX_MESSAGE_HEADER 
    {
        UINT8       byCount;
        APPLY_ALLIANCE_INFO      info[0];
    };

    struct M2C_GUILD_REPLY_UNION_APP_ACK : MESSAGE_HEADER 
    {
        UINT32      dwGuildID;
    };

    struct M2C_GUILD_ADD_DIPLOMAT_NTF : MESSAGE_HEADER 
    {
        UINT8       byType;
        UINT32      dwGuildID;
        UINT32      dwLastTime;
        UINT8       byLevel;
        UINT8       byMemberCount;
        char        szGuildName[GUILD_NAME_LEN];
    };

    struct M2C_GUILD_DEL_DIPLOMAT_NTF : MESSAGE_HEADER 
    {
        UINT8       byType;
        UINT32      dwGuildID;
    };

    struct M2C_GUILD_NOTIFY_NTF : MESSAGE_HEADER 
    {
        UINT8       byType;
    };

    struct M2C_GUILD_CHANGE_STORAGE_RIGHT_NTF : MESSAGE_HEADER 
    {
        UINT8       byPosition;
        UINT16      wRight;
    };

    struct GUILD_STORAGE_ITEM_INFO
    {
        UINT8       byConSlot;
        UINT8       byItemSlot;
        char        szItemBuffer[GUILD_MAX_ITEM_BUFFER_LENGTH];
    };

    struct M2C_GUILD_VIEW_STORAGE_ACK : FLEX_MESSAGE_HEADER 
    {
        UINT8       byStorageTag;
        UINT16      wItemCount;
        GUILD_STORAGE_ITEM_INFO        info[0];
    };

    struct MSG_GUILD_STORAGE_EVENT
    {
        UINT8       byType;
        UINT32      dwRoleID;
        UINT32      dwTime;
        char        szItemBuffer[GUILD_MAX_ITEM_BUFFER_LENGTH];
    };

    struct M2C_GUILD_STORAGE_EVENT : FLEX_MESSAGE_HEADER
    {
        UINT8       byEventCount;
        MSG_GUILD_STORAGE_EVENT     info[0];
    };

    struct M2C_GUILD_PUSH_ITEM_ACK : FLEX_MESSAGE_HEADER 
    {
        UINT8       byStorageConSlot;
        UINT8       byStorageSlot;
        UINT16      wItemSize;
        char        buff[0];
    };

    struct M2C_GUILD_POP_ITEM_ACK : MESSAGE_HEADER 
    {
        UINT8       byStorageConSlot;
        UINT8       byStorageSlot;
    };

    struct M2C_GUILD_MOVE_ITEM_ACK : MESSAGE_HEADER 
    {
        UINT8       bySourceConSlot;
        UINT8       bySourceSlot;
        UINT8       byTargetConSlot;
        UINT8       byTargetSlot;
    };

    struct M2C_GUILD_ADD_HISTORY_EVENT_NTF : MESSAGE_HEADER 
    {
        UINT8       byType;
        UINT32      dwParam1;
        UINT32      dwParam2;
        UINT32      dwParam3;
        UINT32      dwParam4;
        UINT32      dwOccurTime;
    };

    struct M2C_GUILD_ADD_STORAGE_EVENT_NTF : MESSAGE_HEADER
    {
        UINT8       byType;
        UINT32      dwRoleID;
        UINT32      dwOccurTime;
        char        szItemBuffer[GUILD_MAX_ITEM_BUFFER_LENGTH];
    };

    struct M2C_GUILD_MEMBER_SALARY_CHANGE : MESSAGE_HEADER
    {
        UINT32      dwSalary;
    };

    struct M2C_GUILD_MORE_HISTORY : FLEX_MESSAGE_HEADER
    {
        UINT16      wEventNum;
        GUILD_EVENT_INFO    stEventInfo[0];
    };

    struct M2C_GUILD_MORE_CHEST : FLEX_MESSAGE_HEADER 
    {
        UINT16      wEventNum;
        GUILD_EVENT_INFO    stEvent[0];
    };

    struct M2C_GUILD_JOIN_GUILD_NTF : MESSAGE_HEADER 
    {
        char        szGuildName[GUILD_NAME_LEN];
    };

    struct M2C_GUILD_UPGRADE_WELFARE_NTF : MESSAGE_HEADER 
    {
        INT8        byType;
        INT32       nTime;
    };

    struct M2C_GUILD_UPDATE_WELFARE_NTF : MESSAGE_HEADER
    {
        INT8        byType;
        UINT8       byLevel;
    };

    struct M2C_GUILD_CANCEL_WELFARE_UPGRADE_NTF: MESSAGE_HEADER
    {
        UINT32      dwID;
    };

    struct M2C_GUILD_UPGRADE_BUILDING_NTF : MESSAGE_HEADER
    {
        UINT64      qwNpcNameID;
        INT8        byType;
        INT32       nTime;
    };

    struct M2C_GUILD_UPDATE_BUILDING_NTF : MESSAGE_HEADER
    {
        UINT64      qwNpcNameID;
        INT8        byType;
    };

    struct M2C_GUILD_CANCEL_BUILDING_UPGRADE_NTF : MESSAGE_HEADER
    {
        UINT64      qwNpcNameID;
        INT8        byType;
    };

    struct M2C_GUILD_DEL_BUILDING_NTF : MESSAGE_HEADER 
    {
        UINT64      qwNpcNameID;
        INT8        byType;
    };

    struct GUILD_DUNGEON_INFO 
    {
        UINT32  dwTemplateID;
        UINT32  dwOwnerID;
        INT32   nCreateTime;
    };

    struct M2C_GUILD_GET_DUNGEON_LIST_ACK : FLEX_MESSAGE_HEADER 
    {
        UINT8       byDungeonCount;
        GUILD_DUNGEON_INFO  info[0];
    };

    struct M2C_GUILD_OPEN_DUNGEON_ACK : MESSAGE_HEADER
    {
    };

    struct GUILD_DUNGEON_AWARD_INFO 
    {
        UINT32      dwItemID;
        UINT8       byCount;
    };

    struct M2C_GUILD_DUNGEON_AWARD : FLEX_MESSAGE_HEADER 
    {
        UINT32      dwOwnerID;
        UINT8       byItemCount;
        GUILD_DUNGEON_AWARD_INFO      arrItem[GUILD_DUNGEON_AWARD_NUM];
    };

    struct M2C_GUILD_BUILDING_STATE_NTF : MESSAGE_HEADER
    {
        UINT64      qwNameID;
        UINT32      dwReviveTime;
    };

    struct GUILD_BATTLE_ACHIEVEMENT_DATA 
    {
        UINT32  dwRoleID;
        INT32   nKillNum;
        INT32   nDealCount;
        INT32   nSalary;
    };

    struct M2C_GUILD_BATTLE_ACHIEVEMENT : FLEX_MESSAGE_HEADER 
    {
        UINT8   byNum;
        GUILD_BATTLE_ACHIEVEMENT_DATA   info[0];
    };

    struct M2C_GUILD_SYNC_WAR_CD_NTF : MESSAGE_HEADER 
    {
        UINT32      dwWarCD;
    };

    struct M2C_GUILD_ACHIEVEMENT_ACK : MESSAGE_HEADER
    {
        char        acAchievement[GUILD_ACHI_TYPE_NUM];
    };

    struct M2C_GUILD_JOIN_WAR_NTF : MESSAGE_HEADER 
    {
        UINT8       byWarCharacter;
        UINT32      dwTargetGuildID;
    };

    struct M2C_ARENA_GET_DATA_ACK : MESSAGE_HEADER 
    {
        UINT64      qwTotalFund;
        UINT8       byChampionMaxVictoryTimes;
        UINT8       byRank;
        INT32       nRewardMoney;
        UINT32      dwRewardItemID;
    };

    struct M2C_ARENA_END : MESSAGE_HEADER 
    {
    };

    struct M2C_ARENA_MATCH_BEGIN_NTF : MESSAGE_HEADER
    {
    };

    struct M2C_SYNC_SOCIAL_ATTR_NTF : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        UINT32      dwValue;
        UINT8       byLevel;
    };

    struct AUCTION_ITEM_INFO
    {
        UINT32      dwAuctionID;
        UINT32      dwSellerRoleID;
        UINT32      dwBuyerRoleID;
        INT32       nPrice;
        INT32       nBuyoutPrice;
        UINT32      dwFinishTime;
        char        acItem[0];
    };

    struct M2C_AUCTION_SEARCH_TYPE : FLEX_MESSAGE_HEADER
    {
        UINT8       byAuctionType;
        UINT8       byAuctionSubType;
        INT32       nItemCount;
        INT32       nItemID[0];
    };

    struct M2C_AUCTION_SEARCH : FLEX_MESSAGE_HEADER
    {
        UINT8       btAuctionItemCount;
        char        acAuctionItems[0];
    };

    struct M2C_AUCTION_QUERY : FLEX_MESSAGE_HEADER
    {
        UINT32      dwAuctionID;
        UINT8       byFound;
        AUCTION_ITEM_INFO stAuction;
    };

    struct M2C_AUCTION_SELL : FLEX_MESSAGE_HEADER
    {
        AUCTION_ITEM_INFO stAuction;
    };

    struct M2C_AUCTION_CANCEL_SELL : MESSAGE_HEADER
    {
        UINT32      dwAuctionID;
    };

    struct M2C_AUCTION_BUY : FLEX_MESSAGE_HEADER
    {
        AUCTION_ITEM_INFO stAuction;
    };

    struct M2C_AUCTION_FINISHED : MESSAGE_HEADER
    {
        UINT32      dwAuctionID;
        UINT8       bySuccess;
    };

    struct M2C_AUCTION_LIST_MY_SELLING : FLEX_MESSAGE_HEADER
    {
        UINT8       byCount;
        char        acAuctionItems[0];
    };

    struct M2C_AUCTION_LIST_MY_BUYING : FLEX_MESSAGE_HEADER
    {
        UINT8       byCount;
        char        acAuctionItems[0];
    };

    struct EXCHANGE_ORDER_INFO
    {
        UINT64      qwOrderID;
        UINT32      dwOrderTime;
        UINT8       byOrderType;
        UINT8       byOrderStatus;
        INT32       nPrice;
        INT32       nCount;
        INT32       nCurCount;
    };

    struct M2C_EXCHANGE_ADD_ORDER : MESSAGE_HEADER
    {
        EXCHANGE_ORDER_INFO stOrder;
    };

    struct M2C_EXCHANGE_CANCEL_ORDER : MESSAGE_HEADER
    {
        UINT64      qwOrderID;
    };

    struct EXCHANGE_PRICE_INFO
    {
        INT32       nPrice;
        INT32       nCount;
    };

    struct M2C_EXCHANGE_LIST_PRICES : FLEX_MESSAGE_HEADER
    {
        UINT8       bySellCount;
        UINT8       byBuyCount;
        EXCHANGE_PRICE_INFO stPrices[0];
    };

    struct M2C_EXCHANGE_LIST_MY_ORDERS : FLEX_MESSAGE_HEADER
    {
        UINT8       byOrderType;
        UINT8       byMoneyOrder;
        UINT8       byCount;
        EXCHANGE_ORDER_INFO stOrders[0];
    };

    struct EXCHANGE_LOG_INFO
    {
        UINT32      dwTime;
        UINT8       byOrderType;
        INT32       nPrice;
        INT32       nCount;
    };

    struct M2C_EXCHANGE_LIST_MY_LOGS : FLEX_MESSAGE_HEADER
    {
        INT32       nCount;
        EXCHANGE_LOG_INFO stLogs[0];
    };

    struct M2C_SYNC_REAL_MONEY : MESSAGE_HEADER
    {
        INT32       nBalance;
    };

    struct REAL_MONEY_ITEM_INFO
    {
        INT32       m_nItemTemplateID;
        INT16       m_shItemCount;
        UINT8       m_byPage;
        UINT8       m_byFlag;
        INT32       m_nCurrentPrice;
        INT32       m_nOriginalPrice;
        INT32       m_nRenQi;
    };

    struct M2C_SYNC_REAL_MONEY_SHOP_DATA : FLEX_MESSAGE_HEADER
    {
        UINT32      dwCrc;
        UINT32      dwItemCount;
        REAL_MONEY_ITEM_INFO Items[0];
    };

    struct M2C_REAL_MONEY_BUY : MESSAGE_HEADER
    {
        INT32       nItemID;
        INT32       nMoneyLeft;
    };

    struct SHOP_LOG
    {
        INT32 nItemID;
        INT32 nItemCount;
        INT32 nCost;
        UINT32 dwShopTime;
    };

    struct M2C_REAL_MONEY_SHOP_LOG : FLEX_MESSAGE_HEADER
    {
        INT32 nShopLogCount;
        SHOP_LOG stShopLog[0];
    };

    struct SALE_INFO
    {
        UINT32      dwTime;
        INT32       nItemID;
        char        szRoleName[ROLE_NAME_LEN];
    };

    struct M2C_SALE_INFO : FLEX_MESSAGE_HEADER
    {
        INT32       nSaleInfoCount;
        SALE_INFO   stSaleInfo[0];
    };

	struct M2C_QUERY_RANKLIST : MESSAGE_HEADER
	{
		UINT8	byRankListType;
		UINT16	wSelfRank;
		UINT16	wLastSelfRank;
		INT32	nTotalPage;
		INT64	llKey[MAX_RANK_NODE_NUM_PER_PAGE];
		INT64	llValue[MAX_RANK_NODE_NUM_PER_PAGE];
		UINT16	wLastRank[MAX_RANK_NODE_NUM_PER_PAGE];
	};

	struct M2C_ENROLL_SABAC : MESSAGE_HEADER
	{
		UINT32	dwGuildID;
	};

	struct M2C_OCCUPY_SABAC : MESSAGE_HEADER
	{
		UINT32	dwOldGuildID;
		UINT32	dwNewGuildID;
	};

	struct M2C_ERECT_STATUE : MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		char		szRoleName[ROLE_NAME_LEN];
		UINT8		byClass;
		UINT8		bySex;
		UINT8       byHairType;
		UINT8       byHairColor;
		UINT8       byFaceType;
		UINT8       bySkinColor;
		UINT8       byTitleID;
		UINT8       byRefineFx;
		INT32       anAvatar[NES_VISIBLE_TOTAL];
	};

	struct M2C_SABAC_WINNER_LOGIN : MESSAGE_HEADER
	{
		char		szRoleName[ROLE_NAME_LEN];
	};

    struct M2C_FCM_STATE : MESSAGE_HEADER
    {
        INT32   nOnlineMinutes;
        INT32   nOfflineMinutes;
    };

    struct M2C_TIME_INFO : MESSAGE_HEADER
    {
        INT32   nPlayTimeLeft;
    };

    struct M2C_BUY_TIME : MESSAGE_HEADER
    {
        UINT8   bAuto;
        UINT8   byResult;
    };

    struct M2C_FREE_MODE : MESSAGE_HEADER
    {
        UINT8   byFreeMode;
    };
};
#pragma pack(pop)

#endif  // _M2C_MESSAGE_H_
