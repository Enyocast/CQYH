#ifndef _C2M_MESSAGE_H_
#define _C2M_MESSAGE_H_

#include "external_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace ExternalMessage
{
    enum C2M_MESSAGE_ID
    {
        c2m_message_begin = 512,

        // common
        c2m_query_role_info,

        // team
        c2m_team_join,
        c2m_team_leave,
        c2m_team_answer,
        c2m_team_changeinfo,

		c2m_team_change_activity_info,		// obsoleted
		c2m_team_query_activity_team,		// obsoleted
		c2m_team_remove_activity_team,		// obsoleted

        // friend
        c2m_friend_add,
        c2m_friend_del,
        c2m_friend_change_group,
        c2m_change_info,
        c2m_friend_chat,
        c2m_personal_enemy_add,
        c2m_personal_enemy_del,

		// chat
		c2m_chat_message,

		c2m_query_line_req,

        // master
        c2m_master_teacher_ignore,      // 师傅无视or拒绝推送请求师傅信息
        c2m_master_get_recruit_list,    // 拉取师徒招募榜
        //c2m_master_apply_recruit,       // 申请招募徒弟
        //c2m_master_cancel_recruit,      // 取消招募徒弟
        c2m_master_get_solo_list,       // 拉取没有拜师的玩家列表

        c2m_master_stud_submit_app,     // 申请拜师
        c2m_master_agree_stud_app,      // 同意拜师申请
        c2m_master_refuse_stud_app,     // 师傅拒绝徒弟拜师申请
        c2m_master_cancel_stud_app,     // 徒弟主动取消拜师申请

        c2m_master_teacher_submit_app,
        c2m_master_agree_teacher_app,
        c2m_master_refuse_teacher_app,
        c2m_master_cancel_teacher_app,

        c2m_master_leave_teacher,        // 徒弟叛师
        c2m_master_fire_stud,           // 师傅开除徒弟

        c2m_master_info,     // 拉取师徒数据

        c2m_master_cz,
        c2m_master_grad,

        
        //c2m_master_cong_level_up,  // 恭喜升级

        // mail
        c2m_mail_write,
        c2m_mail_list_recv,
        c2m_mail_read,
        c2m_mail_delete,
        c2m_mail_get_attach,

        //battle
		c2m_join_battle,					// obsoleted	
		c2m_cancel_join_battle_req,			// obsoleted
		c2m_join_battle_confirm_ack,		// obsoleted

        // guild
        c2m_query_guild_name,
        c2m_view_guild_list,
        c2m_more_guild_info,
        c2m_find_guild,
        c2m_apply_to_join_guild,
        c2m_get_apply_guild_list,
        c2m_revert_guild_apply,
        c2m_invite_to_join_guild,
        c2m_revert_guild_invitation,
        c2m_disband_guild,
        c2m_guild_notice_change,
        c2m_guild_announce_change,
        c2m_guild_forbid_chat,
        c2m_guild_change_position,
        c2m_guild_role_leave,
        c2m_guild_banish_role,
        c2m_guild_demise,
        c2m_guild_diplomat_app,
        c2m_guild_get_apply_union_list,      // only alliance
        c2m_guild_reply_union_app,
        c2m_guild_cancel_alliance,
        c2m_guild_change_storage_right,
        c2m_guild_move_item,
        c2m_guild_more_history,
        c2m_guild_more_chest,

        c2m_guild_upgrade_welfare,
        c2m_guild_cancel_welfare_upgrade,
        c2m_guild_cancel_building_upgrade,
        //c2m_guild_del_building,

        c2m_guild_get_dungeon_list,			// obsoleted
        c2m_guild_declare_war,
        c2m_guild_achievement,

        c2m_guild_activity,

        // arena
        c2m_arena_get_data,					// obsoleted

        // shield list
        c2m_shield,

        // auction
        c2m_auction_search_type,			// obsoleted
        c2m_auction_search,					// obsoleted
        c2m_auction_query,					// obsoleted
        c2m_auction_sell,					// obsoleted
        c2m_auction_cancel_sell,			// obsoleted
        c2m_auction_buy,					// obsoleted
        c2m_auction_list_my_selling,		// obsoleted
        c2m_auction_list_my_buying,			// obsoleted

        // exchange
        c2m_exchange_add_order,
        c2m_exchange_cancel_order,
        c2m_exchange_list_prices,
        c2m_exchange_list_my_orders,
        c2m_exchange_list_my_logs,

        // real money shop
        c2m_check_real_money,
        c2m_check_real_money_shop_data,		// obsoleted
        c2m_real_money_buy,					// obsoleted
        c2m_real_money_shop_log,			// obsoleted
        c2m_sale_info,						// obsoleted

        // gm
        c2m_gm_command,

		// ranklist
		c2m_query_ranklist,

		// award
		c2m_award_use_number,

        // time
        c2m_buy_time,

		c2m_change_recall_state,

        c2m_message_end = 900,
    };

    struct C2M_QUERY_ROLE_INFO : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
        UINT32              dwCRC;
    };

    struct C2M_TEAM_JOIN : MESSAGE_HEADER
    {
        UINT32              dwTargetRoleID;
    };

    struct C2M_TEAM_LEAVE : MESSAGE_HEADER
    {
        UINT32              dwLeaveRoleID;
    };

    struct C2M_TEAM_ANSWER : MESSAGE_HEADER
    {
        UINT32              dwAnswerRequestRoleID;
        UINT8               byAnswerType;
        UINT8               byAnswerResult;
    };

    struct C2M_TEAM_CHANGEINFO : MESSAGE_HEADER
    {
        INT32               nTeamMemberLimit;
        UINT8               byAssignType;
		UINT8				byItemAuctionColorLimit;
        UINT32              dwLeadID;
        char                szTeamName[TEAM_NAME_LEN];
    };

    struct C2M_FRIEND_ADD : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
        char                szRoleName[ROLE_NAME_LEN];
    };

    struct C2M_FRIEND_DEL : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
    };

    struct C2M_FRIEND_CHANGE_GROUP : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
        UINT8               byGroupID;
    };

    struct C2M_CHANGE_INFO : MESSAGE_HEADER
    {
        char                szSignature[SIGNATURE_LEN];
        UINT8               byFriendState;
    };

    struct C2M_FRIEND_CHAT : FLEX_MESSAGE_HEADER
    {
        UINT32              dwTargetID;
        UINT8               byColor;
        char                szMessage[0];
    };

    struct C2M_PERSONAL_ENEMY_ADD : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
    };

    struct C2M_PERSONAL_ENEMY_DEL : MESSAGE_HEADER
    {
        UINT32              dwRoleID;
    };

	struct C2M_CHAT_MESSAGE : FLEX_MESSAGE_HEADER
	{
		UINT32				dwTargetID;
		char				szMessage[0];
	};

	struct C2M_TEAM_CHANGE_ACTIVITY_INFO : MESSAGE_HEADER
	{
		UINT32				dwActivityType;
		INT32				nActivityID;
	};

	struct C2M_TEAM_QUERY_ACTIVITY_TEAM: MESSAGE_HEADER
	{
		INT32				nPgae;
		INT32				nActivityID;
		UINT32				dwActivityType;
	};

	struct C2M_TEAM_REMOVE_ACTIVITY_TEAM : MESSAGE_HEADER
	{
	};

	struct C2M_QUERY_LINE_REQ : MESSAGE_HEADER
	{
	};

    struct C2M_MASTER_TEACHER_IGNORE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct C2M_MASTER_GET_RECRUIT_LIST : MESSAGE_HEADER
    {

    };

    //struct C2M_MASTER_APPLY_RECRUIT : MESSAGE_HEADER
    //{
    //};

    //struct C2M_MASTER_CANCEL_RECRUIT : MESSAGE_HEADER
    //{
    //    
    //};

    struct C2M_MASTER_GET_SOLO_LIST : MESSAGE_HEADER 
    {
    };

    struct C2M_MASTER_STUD_SUBMIT_APP : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
    };

    struct C2M_MASTER_AGREE_STUD_APP : MESSAGE_HEADER
    {
        UINT32      dwStudentID;
    };

    struct C2M_MASTER_REFUSE_STUD_APP : MESSAGE_HEADER
    {
        UINT32      dwStudentID;
    };

    struct C2M_MASTER_CANCEL_STUD_APP : MESSAGE_HEADER 
    {
        UINT32      dwTeacherID;
    };

    struct C2M_MASTER_TEACHER_SUBMIT_APP : MESSAGE_HEADER 
    {
        UINT8       bySourceType;       // enum MASTER_TEACHER_APP_TYPE
        UINT32      dwStudentID;
    };

    struct C2M_MASTER_AGREE_TEACHER_APP : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
    };

    struct C2M_MASTER_REFUSE_TEACHER_APP : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
    };

    struct C2M_MASTER_CANCEL_TEACHER_APP : MESSAGE_HEADER
    {
        UINT32      dwStudentID;
    };


    struct C2M_MASTER_LEAVE_TEACHER : MESSAGE_HEADER
    {
    };

    struct C2M_MASTER_FIRE_STUD : MESSAGE_HEADER
    {
        UINT32      dwStudentID;
    };

    struct C2M_MASTER_INFO : MESSAGE_HEADER
    {

    };

    struct C2M_MASTER_CZ : FLEX_MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        UINT32      dwTargetID;
        UINT8       byCZType;
        UINT8       byCZLevel;
        char        szText[0];
    };

    struct C2M_MASTER_GRAD : MESSAGE_HEADER
    {
    };


    //struct C2M_MASTER_CONG_LEVEL_UP : MESSAGE_HEADER
    //{
    //    UINT8       byCongType;
    //    UINT32      dwStudentID;
    //};

    struct C2M_MAIL_WRITE : FLEX_MESSAGE_HEADER
    {
        char        szRoleName[ROLE_NAME_LEN];
        char        szMailSubject[MAIL_SUBJECT_LEN];
        UINT32      dwMailContentLen;
        char        szMailContent[0];
    };

    struct C2M_MAIL_LIST_RECV : MESSAGE_HEADER
    {

    };

    struct C2M_MAIL_READ : MESSAGE_HEADER
    {
        UINT32      dwMailID;
    };

    struct C2M_MAIL_DELETE : MESSAGE_HEADER
    {
        UINT32      dwMailID;
    };

    struct C2M_MAIL_GET_ATTACH : MESSAGE_HEADER
    {
        UINT32      dwMailID;
    };

	struct C2M_JOIN_BATTLE : MESSAGE_HEADER
	{
		UINT32		dwBattleMatch;
	};

	struct C2M_CANCEL_JOIN_BATTLE_REQ : MESSAGE_HEADER
	{
	};

	struct C2M_JOIN_BATTLE_CONFIRM_ACK : MESSAGE_HEADER
	{
		UINT8		byResult;
	};

    struct C2M_QUERY_GUILD_NAME : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        UINT32      dwCRC;
    };

    struct C2M_VIEW_GUILD_LIST : MESSAGE_HEADER
    {
        UINT8       byViewType;
        UINT32      dwLastGuildID;
    };

    struct C2M_MORE_GUILD_INFO : MESSAGE_HEADER 
    {

    };

    struct C2M_FIND_GUILD : MESSAGE_HEADER 
    {
        UINT32      dwGuildID;
        char        szGuildName[GUILD_NAME_LEN];
    };

    struct C2M_APPLY_TO_JOIN_GUILD :MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        char        szGuildName[GUILD_NAME_LEN];
    };

    struct C2M_GET_APPLY_GUILD_LIST : MESSAGE_HEADER
    {

    };

    struct C2M_REVERT_GUILD_APPLY : MESSAGE_HEADER
    {
        UINT8       byRevert;           // GUILD_REVERT_APPLY_ENUM
        UINT32      dwRoleID;
    };

    struct C2M_INVITE_TO_JOIN_GUILD : MESSAGE_HEADER 
    {
        char        szRoleName[ROLE_NAME_LEN];
    };

    struct C2M_REVERT_GUILD_INVITATION : MESSAGE_HEADER
    {
        UINT8       byResult;       // GUILD_REVERT_APPLY_ENUM
        UINT32      dwRoleID;
    };

    struct C2M_DISBAND_GUILD : MESSAGE_HEADER
    {

    };

    struct C2M_GUILD_NOTICE_CHANGE : FLEX_MESSAGE_HEADER
    {
        char        szNotice[0];        // GUILD_NOTICE_LEN
    };

    struct C2M_GUILD_ANNOUNCE_CHANGE : FLEX_MESSAGE_HEADER
    {
        char        szAnnounce[0];
    };

    struct C2M_GUILD_FORBID_CHAT : MESSAGE_HEADER
    {
        UINT8       byOperation;        // GUILD_FORBID_CHAT_ENUM
        UINT32      dwRoleID;
    };

    struct C2M_GUILD_CHANGE_POSITION : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT8       byPosition;      
    };

    struct C2M_GUILD_ROLE_LEAVE : MESSAGE_HEADER 
    {
    };

    struct C2M_GUILD_BANISH_ROLE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct C2M_GUILD_DEMISE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct C2M_GUILD_DIPLOMAT_APP : MESSAGE_HEADER
    {
        UINT8       byOpType;           // GUILD_DIPLOMAT_OP_TYPE
        UINT8       byTimeType;
        char        szGuildName[GUILD_NAME_LEN];
    };
    
    struct C2M_GUILD_GET_APPLY_UNION_LIST : MESSAGE_HEADER
    {
    };

    struct C2M_GUILD_REPLY_UNION_APP : MESSAGE_HEADER 
    {
        UINT8       byOp;
        UINT32      dwGuildID;
    };

    struct C2M_GUILD_CANCEL_ALLIANCE : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
    };

    struct C2M_GUILD_CHANGE_STORAGE_RIGHT : MESSAGE_HEADER
    {
        UINT8       byPosition;
        UINT16      wRight;
    };

    struct C2M_GUILD_MOVE_ITEM : MESSAGE_HEADER
    {
        UINT8       bySourceConSlot;
        UINT8       bySourceSlot;
        UINT8       byTargetConSlot;
        UINT8       byTargetSlot;
    };

    struct C2M_GUILD_MORE_HISTORY : MESSAGE_HEADER
    {
    };

    struct C2M_GUILD_MORE_CHEST : MESSAGE_HEADER 
    {
    };

    struct C2M_GUILD_UPGRADE_WELFARE : MESSAGE_HEADER
    {
        INT8        byType;
    };

    struct C2M_GUILD_CANCEL_WELFARE_UPGRADE  : MESSAGE_HEADER
    {
        INT8        byType;
    };

    struct C2M_GUILD_UPGRADE_BUILDING : MESSAGE_HEADER
    {
        INT8        byType;
    };

    struct C2M_GUILD_CANCEL_BUILDING_UPGRADE : MESSAGE_HEADER
    {
        UINT64      qwNameID;
        INT8        byType;
    };

    //struct C2M_GUILD_DEL_BUILDING : MESSAGE_HEADER 
    //{
    //    UINT64      qwNameID;
    //    INT8        byType;
    //};

    struct C2M_GUILD_GET_DUNGEON_LIST : MESSAGE_HEADER
    {

    };

    struct C2M_GUILD_DECLARE_WAR : MESSAGE_HEADER
    {
        char        szGuildName[GUILD_NAME_LEN];
    };

    struct C2M_GUILD_ACHIEVEMENT : MESSAGE_HEADER
    {
    };

    struct C2M_GUILD_ACTIVITY : MESSAGE_HEADER
    {
        INT32       nActivityID;
    };

    struct C2M_ARENA_GET_DATA : MESSAGE_HEADER 
    {

    };

    struct C2M_SHIELD : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
        char    szRoleName[ROLE_NAME_LEN];
    };

    struct C2M_AUCTION_SEARCH_TYPE : MESSAGE_HEADER
    {
        UINT8       byAuctionType;
        UINT8       byAuctionSubType;
    };

    struct C2M_AUCTION_SEARCH : MESSAGE_HEADER
    {
        UINT8       bySortBy;
        INT32       nItemTemplateID;
    };

    struct C2M_AUCTION_QUERY : MESSAGE_HEADER
    {
        UINT32      dwAuctionID;
    };

    struct C2M_AUCTION_SELL : MESSAGE_HEADER
    {
        UINT8       byConSlot;
        UINT8       byItemSlot;
        INT32       nPrice;
        INT32       nBuyoutPrice;
    };

    struct C2M_AUCTION_CANCEL_SELL : MESSAGE_HEADER
    {
        UINT32      dwAuctionID;
    };

    struct C2M_AUCTION_BUY : MESSAGE_HEADER
    {
        UINT32      dwAuctionID;
        INT32       nPrice;
    };

    struct C2M_AUCTION_LIST_MY_SELLING : MESSAGE_HEADER
    {
    };

    struct C2M_AUCTION_LIST_MY_BUYING : MESSAGE_HEADER
    {
    };

    struct C2M_EXCHANGE_ADD_ORDER : MESSAGE_HEADER
    {
        UINT8       byOrderType;
        INT32       nItemID;
        INT32       nPrice;
        INT32       nCount;
    };

    struct C2M_EXCHANGE_CANCEL_ORDER : MESSAGE_HEADER
    {
        UINT64      qwOrderID;
    };

    struct C2M_EXCHANGE_LIST_PRICES : MESSAGE_HEADER
    {
    };

    struct C2M_EXCHANGE_LIST_MY_ORDERS : MESSAGE_HEADER
    {
    };

    struct C2M_EXCHANGE_LIST_MY_LOGS : MESSAGE_HEADER
    {
    };

    struct C2M_CHECK_REAL_MONEY : MESSAGE_HEADER
    {
    };

    struct C2M_CHECK_REAL_MONEY_SHOP_DATA : MESSAGE_HEADER
    {
        UINT32      dwCrc;
    };

    struct C2M_REAL_MONEY_BUY : MESSAGE_HEADER
    {
        INT32       nItemID;
        INT32       nCount;
        char        szRoleName[ROLE_NAME_LEN];
    };

    struct C2M_REAL_MONEY_SHOP_LOG : MESSAGE_HEADER
    {
    };

    struct C2M_SALE_INFO : MESSAGE_HEADER
    {
    };

    struct C2M_GM_COMMAND : FLEX_MESSAGE_HEADER
    {
        char        szRoleName[ROLE_NAME_LEN];
        char        szGMCommand[0];
    };

	struct C2M_QUERY_RANKLIST : MESSAGE_HEADER
	{
		INT32		nRanklistID;
		INT32		nPageSize;
	};

	struct C2M_AWARD_USE_NUMBER : MESSAGE_HEADER
	{
		char		chAwardNumber[32];
	};

    struct C2M_BUY_TIME : MESSAGE_HEADER
    {
        UINT32      dwBuyTimeCost;
    };

	struct C2M_CHANGE_RECALL_STATE : MESSAGE_HEADER
	{
		UINT8		byEnabled;
	};
};


// tolua_end
#pragma pack(pop)

#endif  // _C2M_MESSAGE_H_
