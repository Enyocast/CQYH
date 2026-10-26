#ifndef _G2M_MESSAGE_H_
#define _G2M_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
// tolua_begin
namespace InternalMessage
{
    enum G2M_MESSAGE_ID
    {
        g2m_begin = g2m_message_begin,

        g2m_register,
        g2m_ready,
        g2m_server_info,
        g2m_close_ack,
		g2m_broadcast_group_client,

        // login
        g2m_pre_enter_gs_ack,
        g2m_enter_gs,
		g2m_leave_gs_ack,
        g2m_reset_scene,
        g2m_query_scene,
        g2m_create_scene_ack,
		g2m_close_scene,
        g2m_destroy_scene_ack,

		// chat
		g2m_chat_message,	

        // team
        g2m_leave_team,
        g2m_team_sync_member,
        g2m_clear_team_dungeon,

		// quest
		g2m_publish_quest,

		// role_info
		g2m_update_role_info,

        // mail
        g2m_mail_cost_check,
        g2m_send_system_mail,
        g2m_send_system_mail_with_simple_attach,
        g2m_send_system_mail_with_buffer_attach,
        g2m_mail_get_attach,

		// lua_function
		g2m_call_lua_function,

		//battle

        // master
        g2m_mst_submit_teacher_app_ack,
        g2m_mst_agree_teacher_app_ack,
        g2m_mst_submit_stud_app_ack,
        g2m_mst_agree_stud_app_ack,
        g2m_sync_master_exp,
        g2m_master_cz,
        g2m_try_to_find_teacher,
        g2m_master_twitter,

        // guild
        g2m_guild_create,
        g2m_pre_create_guild_ack,
        g2m_guild_draw_salary,
        g2m_guild_contribute,
        g2m_guild_view_storage,
        g2m_guild_pre_push_item,
        g2m_guild_push_item,
        g2m_guild_pre_pop_item,
        g2m_guild_pop_item,

        g2m_guild_create_building,
        g2m_guild_upgrade_building,
        g2m_guild_del_building,

        g2m_guild_pre_open_dungeon,
        g2m_guild_open_dungeon,
        g2m_guild_enter_dungeon,
        g2m_guild_close_dungeon_commission,

        g2m_guild_change_res,
        g2m_guild_end_war,
        g2m_guild_change_building_state,

        g2m_guild_achievement_reward,

        g2m_guild_leave_guild,

        // arena
        g2m_arena_sync_data,
        g2m_arena_join_season,
        g2m_arena_match,
        g2m_arena_win,
        g2m_arena_defeated,
        g2m_arena_reward,

        // personal enemy
        g2m_add_kill_list,

        // gm
        g2m_gm_log,

        // item drop control
        g2m_drop_limit,

        // auction
        g2m_auction_sell,
        g2m_auction_buy,
        g2m_auction_pay,

        // exchange
        g2m_exchange_add_order,

		// ranklist
		g2m_ranklist_role_data,
		g2m_update_ranklist_node,

        // adventure
        g2m_adventure_trigger,

		// award
		g2m_send_award_to_ump,

		// sabac
		g2m_enroll_sabac,
		g2m_occupy_sabac,
		g2m_erect_statue,

        g2m_query_role_location,
        g2m_query_role_location_ack,
        g2m_take_role,
		g2m_recall_team_member,

		g2m_set_server_variable,

        // black market
        g2m_get_black_market_limit_info,
        g2m_check_black_market_product,

        // exercise
        g2m_add_exercise_time,

		// anti-cheat freeze login
		g2m_freeze_login,

        // temporary charge funciont
        g2m_temporary_charge,

        // real money
        g2m_query_real_money_ack,
        g2m_role_rela_money_shop_buy_item_ack,

        g2m_end = g2m_message_end
    };

    struct G2M_REGISTER : MESSAGE_HEADER
    {
		UINT32			dwCRCList[0];
    };

    struct G2M_READY : MESSAGE_HEADER
    {

    };

    struct G2M_PRE_ENTER_GS_ACK : MESSAGE_HEADER
    {
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
        INT32           nErrCode;
    };

	struct G2M_ENTER_GS : MESSAGE_HEADER
	{
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
        INT64			llMasterExp;
        UINT32          dwMasterCD;
        UINT32          dwGuildCD;
        UINT8           byGMLevel;
        UINT8           byTwitter;
        UINT32          dwMasterTwitterCD;
        char            szSignature[SIGNATURE_LEN];
	};

	struct G2M_LEAVE_GS_ACK : MESSAGE_HEADER
	{
        UINT32          dwClientSessionID;
        UINT32          dwRoleID;
	};

	struct G2M_SERVER_INFO : MESSAGE_HEADER
	{
	};

	struct G2M_CLOSE_ACK : MESSAGE_HEADER
	{
	};

	struct G2M_BROADCAST_GROUP_CLIENT : MESSAGE_HEADER
	{
		UINT8	byServerGroup;
		char	MessageData[0];
	};

    struct G2M_CREATE_SCENE_ACK : MESSAGE_HEADER
    {
        INT32           nErrCode;
        UINT8           byGroupID;
        INT32           nSceneTempID;
        INT32           nSceneID;
    };

	struct G2M_CLOSE_SCENE : MESSAGE_HEADER
	{
		UINT8           byServerGroup;
		INT32           nSceneTempID;
		INT32           nSceneID;
	};

    struct G2M_DESTROY_SCENE_ACK : MESSAGE_HEADER
    {
        INT32           nErrCode;
        UINT8           byGroupID;
        INT32           nSceneTempID;
        INT32           nSceneID;
    };

    struct G2M_RESET_SCENE : MESSAGE_HEADER
    {

    };

    struct G2M_QUERY_SCENE : MESSAGE_HEADER
    {
        UINT32           dwClientSessionID;
        UINT32           dwRoleID;
        INT32            nSceneTempID;
        INT32            nSceneID;
        INT32            nDestX;
        INT32            nDestY;
        INT32            nDestZ;
        INT32            nFaceDirection;
    };

    struct G2M_TEAM_SYNC_MEMBER : MESSAGE_HEADER
    {
        UINT32                  dwRoleID;
        INT32                   nLevel;
        INT32                   nMaxHp;
        INT32                   nMaxMp;
        INT32                   nCurHp;
        INT32                   nCurMp;
		INT32					nX;
		INT32					nY;
		INT32					nZ;
    };

    struct G2M_LEAVE_TEAM : MESSAGE_HEADER
    {
        UINT32 dwRoleID;
    };

    struct G2M_CLEAR_TEAM_DUNGEON : MESSAGE_HEADER
    {
        UINT32 dwRoleID;
    };

	struct G2M_CHAT_MESSAGE : MESSAGE_HEADER
	{
		UINT32					dwSourceID;
		UINT32					dwTargetID;
		UINT8					byLocation;
		UINT8					byServerGroupID;
		UINT8					bGM;
		char					szName[ROLE_NAME_LEN];
		char					szMessage[0];
	};

	struct G2M_PUBLISH_QUEST : MESSAGE_HEADER
	{
		INT32					nQuestID;
		INT32					nNum;
		UINT32					dwRoleID;
		UINT32					dwStudentList[MAX_STUDENT_NUM];		
	};

	
	struct G2M_UPDATE_ROLE_INFO : MESSAGE_HEADER
	{
		UINT32					dwRoleID;
		UINT8					byLevel;
        UINT8                   byVIPLevel;
	};

    struct G2M_MAIL_COST_CHECK : MESSAGE_HEADER
    {
        INT32   nResult;
        UINT32  dwSenderRoleID;
        UINT32  dwReceiverRoleID;
        char    szMailSubject[MAIL_SUBJECT_LEN];
        char    szMailContent[MAIL_CONTENT_LEN];
    };

    struct G2M_SEND_SYSTEM_MAIL : MESSAGE_HEADER
    {
        UINT32  dwReceiverRoleID;
        char    szMailSubject[MAIL_SUBJECT_LEN];
        char    szMailContent[MAIL_CONTENT_LEN];
    };

    struct G2M_SEND_SYSTEM_MAIL_WITH_SIMPLE_ATTACH : MESSAGE_HEADER
    {
        UINT32  dwReceiverRoleID;
        char    szMailSubject[MAIL_SUBJECT_LEN];
        char    szMailContent[MAIL_CONTENT_LEN];
        INT32   nItemID;
        INT32   nItemCount;
    };

    struct G2M_SEND_SYSTEM_MAIL_WITH_BUFFER_ATTACH : MESSAGE_HEADER
    {
        UINT32  dwReceiverRoleID;
        char    szMailSubject[MAIL_SUBJECT_LEN];
        char    szMailContent[MAIL_CONTENT_LEN];
        UINT8   byBufferLen;
        char    ItemBuffer[0];
    };

    struct G2M_MAIL_GET_ATTACH : MESSAGE_HEADER
    {
        UINT32  nResult;
        UINT32  dwMailID;
    };

	struct G2M_CALL_LUA_FUNCTION : MESSAGE_HEADER
	{
		char  chFileName[PATH_LEN];
		char  chFuncName[fUNC_NAME_LEN];
		INT32 nValue1;
		INT32 nValue2;
		INT32 nValue3;
	};

    struct G2M_MST_SUBMIT_TEACHER_APP_ACK : MESSAGE_HEADER
    {
        UINT8       bySourceType;
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct G2M_MST_AGREE_TEACHER_APP_ACK : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct G2M_MST_SUBMIT_STUD_APP_ACK : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct G2M_MST_AGREE_STUD_APP_ACK : MESSAGE_HEADER 
    {
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct G2M_SYNC_MASTER_EXP : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT64       llMasterExp;
    };

    struct G2M_MASTER_CZ : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        UINT32      dwTargetID;
        UINT8       byCZLevel;
        UINT8       byCZType;
        char        szText[0];
    };

    struct G2M_TRY_TO_FIND_TEACHER : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
    };

    struct G2M_MASTER_TWITTER : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        BOOL        bTwitter;
    };

    struct G2M_GUILD_CREATE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        char        szGuildName[GUILD_NAME_LEN];
        char        szAnnounce[GUILD_ANNOUNCE_LEN];
    };

    struct G2M_PRE_CREATE_GUILD_ACK : MESSAGE_HEADER
    {
        INT32       nResult;
        UINT32      dwRoleID;
        char        szName[GUILD_NAME_LEN];
    };

    struct G2M_GUILD_DRAW_SALARY : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct G2M_GUILD_CONTRIBUTE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nType;
        INT32       nMoney;
    };

    struct G2M_GUILD_VIEW_STORAGE : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        UINT8       byStorageTag;
    };

    struct G2M_GUILD_PRE_PUSH_ITEM : MESSAGE_HEADER 
    {
        UINT32  dwRoleID;
        UINT16  wSourceConSlot;
        UINT16  wSourceSlot;
        UINT8   byTargetConSlot;
        UINT8   byTargetSlot;
    };

    struct G2M_GUILD_PUSH_ITEM : MESSAGE_HEADER 
    {
        INT32       nResult;
        UINT32      dwRoleID;
        UINT8       byConSlot;
        UINT8       bySlot;
        UINT16      wItemSize;
        char        buff[512];
    };

    struct G2M_GUILD_PRE_POP_ITEM : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        UINT8       byConSlot;
        UINT8       bySlot;
        UINT16      wTargetConSlot;
        UINT16      wTargetSlot;
    };

    struct G2M_GUILD_POP_ITEM : MESSAGE_HEADER 
    {
        INT32       nResult;
        UINT32      dwRoleID;
        UINT8       byConSlot;
        UINT8       bySlot;
        UINT16      wConSlot;
        UINT16      wSlot;
    };

    struct G2M_GUILD_CREATE_BUILDING : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT64      qwNpcNameID;
        INT32       nType;
    };

    struct G2M_GUILD_UPGRADE_BUILDING : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT64      qwNpcNameID;
        INT32       nType;
    };

    struct G2M_GUILD_DEL_BUILDING : MESSAGE_HEADER 
    {
        INT32       nType;
        UINT32      dwRoleID;
        UINT64      qwNameID;
    };

    struct G2M_GUILD_PRE_OPEN_DUNGEON : MESSAGE_HEADER 
    {
        UINT32      dwGuildID;
        UINT32      dwTemplateID;
        UINT32      dwOwnerID;
        UINT32      dwLeaderID;
        INT64       llMoney;
    };

    struct G2M_GUILD_OPEN_DUNGEON : MESSAGE_HEADER 
    {
        UINT32      dwOwnerID;
        UINT32      dwLeaderID;
        UINT32      dwTemplateID;
    };

    struct G2M_GUILD_ENTER_DUNGEON : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        //UINT32      dwLeaderID;
        UINT32      dwTemplateID;
    };

    struct G2M_GUILD_CLOSE_DUNGEON_COMMISSION : MESSAGE_HEADER
    {
        UINT32      dwTemplateID;
        UINT32      dwSceneID;
        INT32       nItemNum;
        UINT32      arrItemID[GUILD_DUNGEON_AWARD_NUM];
        UINT32      arrItemCount[GUILD_DUNGEON_AWARD_NUM];
    };

    struct G2M_GUILD_CHANGE_RES : MESSAGE_HEADER
    {
        UINT32      dwNpcID;
        UINT32      dwGuildID;
        INT32       nResourceType;
        INT32       nChangeType;
        INT32       nCount;
        INT32       nReason;        // GUILD_HISTORY_EVENT_TYPE
        UINT8       byCtxType;
    };

    struct G2M_GUILD_END_WAR : MESSAGE_HEADER 
    {
        UINT32      dwDefenderID;
        INT32       nWarDefenderResult;
    };

    struct G2M_GUILD_CHANGE_BUILDING_STATE : MESSAGE_HEADER 
    {
        UINT32      dwGuildID;
        UINT64      qwNameID;
        UINT32      dwReviveTime;
    };

    struct ROLE_KILL
    {
        UINT32      dwRoleID;
        INT32       nKillNum;
        INT32       nDeadCount;
    };

    struct G2M_GUILD_ACHIEVEMENT_REWARD : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nID;
    };

    struct G2M_GUILD_LEAVE_GUILD : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct G2M_ARENA_SYNC_DATA : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT8       byPointSeasonTimes;
        INT32       nPointSeasonEndTime;
    };

    struct G2M_ARENA_JOIN_SEASON : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
    };

    struct G2M_ARENA_MATCH : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
    };

    struct G2M_ARENA_WIN : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
    };

    struct G2M_ARENA_DEFEATED : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        UINT8       byPointSeasonTimes;
        INT32       nPointSeasonEndTime;
    };

    struct G2M_ARENA_REWARD : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
    };

    struct G2M_ADD_KILL_LIST : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwKillerID;
    };


    struct G2M_GM_LOG : MESSAGE_HEADER 
    {
        UINT32      dwTime;
        INT32       nResult;
        UINT32      dwRoleID;
        char        szGMCmd[0];
    };

    struct G2M_DROP_LIMIT : MESSAGE_HEADER
    {
        INT32       nItemID;
        INT32       nDropCount;
    };

    struct G2M_AUCTION_SELL : MESSAGE_HEADER
    {
        INT32       nResult;
        UINT32      dwRoleID;
        UINT8       byTimeType;
        UINT8       byOpen;
        INT64       llPrice;
        INT64       llBuyoutPrice;
        INT64       llDepositePrice;
        char        acItem[0];
    };

    struct G2M_AUCTION_BUY : MESSAGE_HEADER
    {
        INT32       nResult;
        UINT32      dwRoleID;
        UINT32      dwAuctionID;
        INT64       llPrice;
    };

    struct G2M_AUCTION_PAY : MESSAGE_HEADER
    {
        INT32       nResult;
        UINT32      dwRoleID;
        UINT32      dwAuctionID;
        INT64       llPrice;
    };

    struct G2M_EXCHANGE_ADD_ORDER : MESSAGE_HEADER
    {
        INT32       nResult;
        UINT32      dwRoleID;
        INT32       nItemIDRequire;
        INT32       nItemCountRequire;
        UINT8       byOrderType;
        INT32       nPriceOrder;
        INT32       nCountOrder;
    };

	struct G2M_RANKLIST_ROLE_DATA : MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		INT32		nExp;
		INT32		nLevel;
		INT32		nArmerPower;
		INT32		nSpiritPower;
		INT32		nTotalPower;
		INT32		nMoney;
		INT32		nAchievement;
		INT32		nMaster;
		INT32		nPkValue;
		INT32		nTotalKillCount;
		INT32		nClass;
		INT32		nItemPower;
	};

	struct G2M_UPDATE_RANKLIST_NODE : MESSAGE_HEADER
	{
		UINT8		byServerGroup;
		INT32		nRankListType;
		INT64		llKey;
		INT64		llValue;
	};

    struct G2M_ADVENTURE_TRIGGER : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nAdventureID;
        INT32       nVarID;
        INT32       nMaxCount;
        INT32       nChance;
    };

	struct G2M_SEND_AWARD_TO_UMP : MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		INT32		nAwardType;
		char		chAwardNumber[32];
	};

	struct G2M_ENROLL_SABAC : MESSAGE_HEADER
	{
		UINT32		dwGuildID;
		UINT32		dwEnrollTime;
	};

	struct G2M_OCCUPY_SABAC : MESSAGE_HEADER
	{
		UINT8		byServerGroup;
		UINT32		dwOldGuildID;
		UINT32		dwNewGuildID;
	};

	struct G2M_ERECT_STATUE : MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		UINT8       byHairType;
		UINT8       byHairColor;
		UINT8       byFaceType;
		UINT8       bySkinColor;
		UINT8       byTitleID;
		UINT8       byRefineFx;
		INT32       anAvatar[NES_VISIBLE_TOTAL];
	};

    struct G2M_QUERY_ROLE_LOCATION : MESSAGE_HEADER
    {
        UINT32		dwRoleID;
        UINT32      dwClientSessionID;
        char        szRoleName[ROLE_NAME_LEN];
		UINT8		bFromItem;
    };

    struct G2M_QUERY_ROLE_LOCATION_ACK : MESSAGE_HEADER
    {
        UINT32		dwRoleID;
        UINT32      dwClientSessionID;
        INT32       nSceneTempID;
        INT32       nSceneID;
        INT32       nX;
        INT32       nY;
        INT32       nZ;
		UINT8		bFromItem;
	};

    struct G2M_TAKE_ROLE : MESSAGE_HEADER
    {
        char        szRoleName[ROLE_NAME_LEN];
        INT32       nSceneTempID;
        INT32       nSceneID;
        INT32       nX;
        INT32       nY;
        INT32       nZ;
    };

	struct G2M_RECALL_TEAM_MEMBER : MESSAGE_HEADER
	{
		UINT32		dwLeaderID;
		INT32       nSceneTempID;
		INT32       nSceneID;
		INT32       nX;
		INT32       nY;
		INT32       nZ;
	};

	struct G2M_SET_SERVER_VARIABLE : MESSAGE_HEADER
	{
		UINT8		byServerGroup;
		UINT64		qwKey;
		UINT8		bAbsoluteValue;
		INT32		nVarValue;
	};

    struct G2M_GET_BLACK_MARKET_LIMIT_INFO : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct G2M_CHECK_BLACK_MARKET_PRODUCT : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nBlackMarketProductID;
    };

    struct G2M_ADD_EXERCISE_TIME : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nHour;
    };

    struct G2M_FREEZE_LOGIN : MESSAGE_HEADER
    {
        UINT32		dwRoleID;
        UINT32		dwFreezeTime;
    };

    struct G2M_TEMPORARY_CHARGE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct G2M_QUERY_REAL_MONEY_ACK : MESSAGE_HEADER
    {
        UINT32      dwCliSessionID;
        UINT32      dwRoleID;
        INT64       llRealMoney;
    };

    struct G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK : MESSAGE_HEADER
    {
        INT32       nResult;
        UINT32      dwCliSessionID;
        CHAR        szRoleName[ROLE_NAME_LEN];
        UINT32      dwRoleID;
        INT32       nItemID;
        INT32       nItemCount;
    };

};
// tolua_end
#pragma pack(pop)

#endif  // _G2M_MESSAGE_H_
