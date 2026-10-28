#ifndef _M2G_MESSAGE_H_
#define _M2G_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
    enum M2G_MESSAGE_ID
    {
        m2g_begin = m2g_message_begin,

        // open & close
        m2g_register_ack,
        m2g_sync_rsakey,

        // login & change
        m2g_pre_enter_gs,
        m2g_enter_gs_ack,
        m2g_leave_gs,
        m2g_query_scene_ack,
        m2g_create_scene,
        m2g_destroy_scene,
        m2g_close_scene,
        m2g_change_scene,
        m2g_jump_arena_scene,

        // team
        m2g_team_new,
        m2g_team_add_member,
        m2g_team_remove_member,
        m2g_team_changeinfo,

        // friend
        m2g_change_info,
        m2g_friend_add,
        m2g_friend_del,

        //room
        m2g_room_enter_dungeon,

        // master
        m2g_mst_submit_teacher_app,
        m2g_mst_agree_teacher_app,
        m2g_mst_submit_stud_app,
        m2g_mst_agree_stud_app,
        m2g_mst_cz,
        m2g_mst_sync_state,
        m2g_mst_sync_data,
        m2g_mst_create_relation_ntf,
        m2g_mst_del_relation_ntf,
        m2g_mst_update_data,

        // mail
        m2g_mail_cost_check,
        m2g_mail_get_simple_attach,
        m2g_mail_get_buffer_attach,

        // call lua_function
        m2g_call_lua_function,

        //battle
        m2g_join_battle,

        // guild
        m2g_pre_create_guild,
        m2g_role_add_guild,
        m2g_guild_disband,
        m2g_guild_add_member,
        m2g_guild_del_member,
        m2g_sync_guild_data_ntf,
        m2g_guild_sync_attr_ntf,
        m2g_guild_sync_variable_ntf,
        m2g_guild_draw_salary,
        m2g_guild_add_diplomat_ntf,
        m2g_guild_del_diplomat_ntf,
        m2g_guild_pre_push_item_ack,
        m2g_guild_pre_pop_item_ack,
        m2g_guild_pop_item_ack,
        m2g_guild_upgrade_building_ntf,
        m2g_guild_update_building_ntf,
        m2g_guild_del_building_ntf,
        m2g_guild_update_welfare_ntf,
        m2g_guild_update_state_ntf,
        m2g_guild_change_position_ntf,

        m2g_guild_pre_open_dungeon_ack,
        m2g_guild_enter_dungeon,

        m2g_guild_sync_war_relation,
        m2g_guild_sync_war_char,
        m2g_guild_change_res_ack,
        m2g_guild_war_end,
        m2g_guild_sync_building_state_ntf,
        m2g_guild_sync_member_salary_ntf,
        m2g_sync_role_social_data,

        m2g_guild_achievement_reward,

        // arena
        m2g_arena_reward,

        // shield
        m2g_shield,

        // gm
        m2g_sync_gm_data,

        // statistic
        m2g_update_statistic_value,

        // 
        m2g_call_gm_command,

        // item drop control
        m2g_drop_limit,

        // auction
        m2g_auction_sell,
        m2g_auction_buy,
        m2g_auction_pay,

        // exchange
        m2g_exchange_add_order,

        // adventure
        m2g_adventure_reward,

        // achivement
        m2g_complete_achievement,

        m2g_enroll_sabac,
        m2g_occupy_sabac,

        // gm
        m2g_query_role_location,
        m2g_query_role_location_ack,
        m2g_take_role,
        m2g_arrest_role,

        // 商城购买成功
        m2g_query_real_money_req,
        m2g_real_money_buy_success,

        // fcm
        m2g_fcm_state,

        // FreeMode
        m2g_free_mode,

        // award
        m2g_award,

        m2g_spawn_npc,

        m2g_sync_server_variable,
        m2g_update_server_variable,

        m2g_update_average_level,

        // black market
        m2g_get_black_market_limit_info,
        m2g_check_black_market_product,

        // exercise
        m2g_add_exercise_time,

        // 自己新增代码
        m2g_role_real_money_shop_buy_item_req,
        m2g_custom_role_buy_time,    // 自定义购买点卡

        m2g_end = m2g_message_end
    };

    struct M2G_REGISTER_ACK : MESSAGE_HEADER
    {
        UINT32           dwGSSessionID;
    };

    struct M2G_PRE_ENTER_GS : MESSAGE_HEADER
    {
        UINT32			dwCliSessionID;
        UINT32          dwRoleID;
        char            szUserName[USER_NAME_LEN];
        UINT8           byFcmState;
        UINT8			bIpWhiteList;
        UINT8			bUserWhiteList;
        UINT32			dwIpAddr;

        INT32           nSceneTempID;
        INT32           nSceneID;
        INT32           nDestX;
        INT32           nDestY;
        INT32           nDestZ;
        UINT16          wFaceDirection;
    };

    struct M2G_ENTER_GS_ACK : MESSAGE_HEADER
    {
        UINT32      dwClientSessionID;
        UINT32      dwRoleID;
    };

    struct M2G_LEAVE_GS : MESSAGE_HEADER
    {
        UINT32      dwClientSessionID;
        UINT32      dwRoleID;
    };

    struct M2G_QUERY_SCENE_ACK : MESSAGE_HEADER
    {
        UINT32			 dwCliSessionID;
        INT32            nErrCode;
        UINT32           dwRoleID;
        INT32            nSceneTempID;
        INT32            nSceneID;
        INT32            nDestX;
        INT32            nDestY;
        INT32            nDestZ;
        INT32            nFaceDirection;
    };

    struct M2G_CREATE_SCENE : MESSAGE_HEADER
    {
        UINT8            byGroupID;
        INT32            nSceneTempID;
        INT32            nSceneID;
    };

    struct M2G_DESTROY_SCENE : MESSAGE_HEADER
    {
        UINT8            byGroupID;
        INT32            nSceneTempID;
        INT32            nSceneID;
    };

    struct M2G_CLOSE_SCENE : MESSAGE_HEADER
    {
        UINT8            byServerGroup;
        INT32            nSceneTempID;
        INT32            nSceneID;
    };

    struct M2G_CHANGE_SCENE : MESSAGE_HEADER
    {
        UINT32			 dwCliSessionID;
        UINT32           dwRoleID;
    };

    struct TEAM_MEMBER_CONTENT : MESSAGE_HEADER
    {
        UINT32 dwMemberID;
        CHAR   szRoleName[ROLE_NAME_LEN];
        UINT8  btLevel;
        UINT8  btSex;
        UINT8  btClass;
    };

    struct M2G_TEAM_NEW : MESSAGE_HEADER
    {
        UINT8               byGroupID;
        UINT32              dwTeamID;
        char                szTeamName[TEAM_NAME_LEN];
        INT32               nMemberSizeLimit;
        UINT8               byAssignType;
        UINT32              dwLeadID;
        UINT32              dwCreateTime;

        UINT8               byCount;
        TEAM_MEMBER_CONTENT stTeamMemberList[0];
    };

    struct M2G_TEAM_ADD_MEMBER : MESSAGE_HEADER
    {
        UINT32              dwTeamID;
        TEAM_MEMBER_CONTENT stMemberInfo;
    };

    struct M2G_TEAM_REMOVE_MEMBER : MESSAGE_HEADER
    {
        UINT32              dwTeamID;
        UINT32              dwRoleID;
    };

    struct M2G_TEAM_CHANGEINFO : MESSAGE_HEADER
    {
        UINT32              dwTeamID;
        char                szTeamName[TEAM_NAME_LEN];
        INT32               nTeamMemberLimit;
        UINT8               byAssignType;
        UINT8				byAuctionItemColorLimit;
        UINT32              dwLeadID;
        UINT32              dwRoomID;
        UINT32				dwActivityType;
        UINT32				dwActivityID;
    };

    struct M2G_CHANGE_INFO : MESSAGE_HEADER
    {
        UINT32              dwCliSessionID;
        UINT32              dwRoleID;
        char                szSignature[SIGNATURE_LEN];
    };

    struct M2G_FRIEND_ADD : MESSAGE_HEADER
    {
        UINT32              dwCliSessionID;
        UINT32              dwRoleID;
        UINT32              dwFriendID;
        UINT8               byGroupID;
    };

    struct M2G_FRIEND_DEL : MESSAGE_HEADER
    {
        UINT32              dwCliSessionID;
        UINT32              dwRoleID;
        UINT32              dwFriendID;
        UINT8               byGroupID;
    };

    struct M2G_SYNC_RSAKEY : MESSAGE_HEADER
    {
        char                szData[0];
    };

    struct M2G_ROOM_ENTER_DUNGEON : MESSAGE_HEADER
    {
        UINT32			 dwCliSessionID;
        UINT32           dwRoleID;

        INT32            nSceneTempID;
        INT32            nSceneID;
    };

    struct M2G_SPAWN_NPC : MESSAGE_HEADER
    {
        INT32			nSceneTempID;
        INT32			nX;
        INT32			nY;
        INT32			nZ;
        INT32			nRange;
        INT32			nNpcTemplateID;
        INT32			nNpcCount;
        INT32			dwSuicideTime;
    };

    struct M2G_MST_SUBMIT_TEACHER_APP : MESSAGE_HEADER
    {
        UINT8       bySourceType;
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct M2G_MST_AGREE_TEACHER_APP : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct M2G_MST_SUBMIT_STUD_APP : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct M2G_MST_AGREE_STUD_APP : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct M2G_MST_CZ : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwTargetID;
        UINT8       byCZType;
        UINT8       byCZLevel;
        INT32       nConsumption;
        char        szText[0];
    };

    struct M2G_MST_SYNC_STATE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nState;
    };

    struct M2G_MST_SYNC_DATA : MESSAGE_HEADER
    {
        UINT32          dwRoleID;
        UINT32          dwTeacherID;
        UINT8           byStudNum;
        UINT32          arrStudentID[MAX_STUDENT_NUM];
    };

    struct M2G_MST_CREATE_RELATION_NTF : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct M2G_MST_DEL_RELATION_NTF : MESSAGE_HEADER
    {
        UINT32      dwTeacherID;
        UINT32      dwStudentID;
    };

    struct M2G_MST_UPDATE_DATA : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nType;
        INT32       nValue;
    };

    struct M2G_MAIL_COST_CHECK : MESSAGE_HEADER
    {
        UINT32  dwSenderRoleID;
        UINT32  dwReceiverRoleID;
        char    szMailSubject[MAIL_SUBJECT_LEN];
        char    szMailContent[MAIL_CONTENT_LEN];
    };

    struct M2G_MAIL_GET_SIMPLE_ATTACH : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
        UINT32  dwMailID;
        INT32   nItemID;
        INT32   nItemCount;
    };

    struct M2G_MAIL_GET_BUFFER_ATTACH : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
        UINT32  dwMailID;
        UINT8   byBufferLen;
        char    acBuffer[0];
    };

    struct M2G_CALL_LUA_FUNCTION : MESSAGE_HEADER
    {
        char  chFileName[PATH_LEN];
        char  chFuncName[fUNC_NAME_LEN];
        INT32 nValue1;
        INT32 nValue2;
        INT32 nValue3;
    };

    struct M2G_JOIN_BATTLE : MESSAGE_HEADER
    {
        UINT32	dwCliSessionID;
        UINT32  dwRoleID;
        UINT32	dwSceneTempID;
        UINT32	dwSceneID;
        UINT8	bySide;
    };

    struct M2G_PRE_CREATE_GUILD : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
        char    szGuildName[GUILD_NAME_LEN];
        UINT8   byIsNeedToConsume;
    };

    struct G_B_DATA
    {
        UINT64      qwNameID;
        INT32       nType;
        INT32       nLevel;
    };

    struct M2G_ROLE_ADD_GUILD_NTF : MESSAGE_HEADER
    {
        UINT32  dwGuildID;
        INT32   nState;
        UINT32  dwLeaderID;
        char    szGuildName[GUILD_NAME_LEN];
        //INT8    arrBuildingLvl[GUILD_B_NUM];      // GUILD_B_NUM
        UINT8       byBuildingNum;
        UINT8       byUpgradeBuildingNum;
        UINT8		byServerGroup;
        G_B_DATA    arrBData[0];
    };

    struct M2G_GUILD_DELETE_NTF : MESSAGE_HEADER
    {
        UINT32  dwGuildID;
    };

    struct M2G_GUILD_ADD_MEMBER_NTF : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
        UINT8   byPosition;
        UINT32  dwGuildID;
    };

    struct M2G_GUILD_DEL_MEMBER_NTF : MESSAGE_HEADER
    {
        UINT32  dwRoleID;
        UINT32  dwGuildID;
        UINT32  dwCD;
    };

    //struct M2G_GUILD_DEMISE : MESSAGE_HEADER
    //{
    //    UINT32      dwGuildID;
    //    UINT32      dwNewLeaderID;
    //    UINT32      dwOldLeaderID;
    //};

    struct GUILD_MEMBER_INFO
    {
        UINT32  dwRoleID;
        UINT8   byPosition;
    };

    struct M2G_SYNC_GUILD_DATA_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        INT32       nState;
        UINT32      dwLeaderID;
        char        szGuildName[GUILD_NAME_LEN];
        UINT8       byMemberNum;
        GUILD_MEMBER_INFO   memberList[GUILD_MAX_MEMBER_COUNT];
        UINT8       byAllianceNum;
        UINT32      arrAllianceID[GUILD_MAX_ALLIANCE_NUM];
        UINT8       byEnemyNum;
        UINT32      arrEnemyID[GUILD_MAX_ENEMY_NUM];
        INT8        arrWelfareAuraLvl[GUILD_MAX_WELFARE_AURA_COUNT];
        INT32       arrVariables[MAX_GUILD_VARIABLE_COUNT];
        UINT8       byBuildingNum;
        UINT8       byUpgradeBuildingNum;
        UINT32		dwSabacEnrollTime[MAX_SABAC_ENROLL_COUNT];
        UINT8		bySabacOccupied;
        UINT8		byServerGroup;
        G_B_DATA    arrBData[0];       // todo_tq 暂时这样，之后想办法改成变长包把 Allan Tao[19.3.2014] 
    };

    struct M2G_GUILD_SYNC_ATTR_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        INT32       nAttrType;
        UINT32      dwAttrValue;
    };

    struct M2G_GUILD_SYNC_VARIABLE_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        INT32       nIndex;
        INT32       nValue;
    };

    struct M2G_GUILD_DRAW_SALARY : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nSalary;
    };

    struct M2G_GUILD_ADD_DIPLOMAT_NTF : MESSAGE_HEADER
    {
        UINT8       byType;
        UINT32      dwGuildID;
        UINT32      dwTargetGuildID;
    };

    struct M2G_GUILD_DEL_DIPLOMAT_NTF : MESSAGE_HEADER
    {
        UINT8       byType;
        UINT32      dwGuildID;
        UINT32      dwTargetGuildID;
    };

    struct M2G_GUILD_PRE_PUSH_ITEM_ACK : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT16      wConSlot;
        UINT16      wSlot;
        UINT8       byConSlot;
        UINT8       bySlot;
    };

    struct M2G_GUILD_PRE_POP_ITEM_ACK : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT16      wConSlot;
        UINT16      wSlot;
        UINT8       byConSlot;
        UINT8       bySlot;
    };

    struct M2G_GUILD_POP_ITEM_ACK : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT16      wConSlot;
        UINT16      wSlot;
        INT16       nLength;
        char        buff[512];
    };

    struct M2G_GUILD_UPGRADE_BUILDING_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        UINT64      qwNameID;
        INT32       nType;
        INT32       nLevel;
    };

    struct M2G_GUILD_UPDATE_BUILDING_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        UINT64      qwNameID;
        INT32       nType;
        INT32       nLevel;
    };

    struct M2G_GUILD_DEL_BUILDING_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        UINT64      qwNameID;
        INT32       nType;
    };

    struct M2G_GUILD_UPDATE_WELFARE_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        INT32       nType;
        INT32       nLevel;
    };

    struct M2G_GUILD_UPDATE_STATE_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        INT32       nState;
    };

    struct M2G_GUILD_CHANGE_POSITION_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        UINT32      dwRoleID;
        INT32       nPosition;
    };

    struct M2G_GUILD_PRE_OPEN_DUNGEON_ACK : MESSAGE_HEADER
    {
        UINT32      dwTemplateID;
        UINT32      dwOwnerID;
        UINT32      dwLeaderID;
        INT32       nConsumeMoney;
    };

    struct M2G_GUILD_ENTER_DUNGEON : MESSAGE_HEADER
    {
        UINT32      dwTemplateID;
        UINT32      dwRoleID;
        UINT32      dwDungeonLeaderID;
    };

    struct M2G_GUILD_SYNC_WAR_RELATION : MESSAGE_HEADER
    {
        UINT32      dwIntruderID;
        UINT32      dwDefenderID;
    };

    struct M2G_GUILD_SYNC_WAR_CHAR : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        UINT8       byCharacter;
    };

    struct M2G_GUILD_CHANGE_RES_ACK : MESSAGE_HEADER
    {
        UINT32      dwNpcID;
        UINT32      dwGuildID;
        BOOL        bAdd;
        INT32       nResType;
        INT32       nCount;
        UINT8       byCtxType;
    };

    struct M2G_GUILD_WAR_END : MESSAGE_HEADER
    {
        UINT32      dwDefenderID;
    };

    struct M2G_GUILD_SYNC_BUILDING_STATE_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        UINT64      qwNameID;
        UINT32      dwReviveTime;
    };

    struct M2G_GUILD_SYNC_MEMBER_SALARY_NTF : MESSAGE_HEADER
    {
        UINT32      dwGuildID;
        UINT32      dwRoleID;
        INT32       nSalary;
    };

    struct M2G_SYNC_ROLE_SOCIAL_DATA : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwGuildID;
        UINT32      dwForbidChatTime;
    };

    struct M2G_GUILD_ACHIEVEMENT_REWARD : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nID;
    };

    struct M2G_JUMP_ARENA_SCENE : MESSAGE_HEADER
    {
        UINT32          dwRoleID;
        UINT32          dwSceneTempID;
        UINT32          dwSceneID;
        UINT8           bySide;
    };

    struct M2G_ARENA_REWARD : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwItemID;
        INT32       nMoney;
    };

    struct M2G_SHIELD : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwTargetRoleID;
        char        szTargetRoleName[ROLE_NAME_LEN];
    };

    struct M2G_SYNC_GM_DATA : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwForbidChatTime;
    };

    struct	M2G_UPDATE_STATISTIC_VALUE : MESSAGE_HEADER
    {
        UINT32		dwID;
        UINT32		dwType;
        UINT32		dwIndex;
        INT32		nValue;
    };

    struct M2G_CALL_GM_COMMAND : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        char        szGMCommand[0];
    };

    struct M2G_DROP_LIMIT : MESSAGE_HEADER
    {
        INT32       nItemID;
        INT32       nLimit;
    };

    struct M2G_AUCTION_SELL : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT8       byConSlot;
        UINT8       byItemSlot;
        UINT8       byAuctionTimeType;
        UINT8       byOpen;
        INT64       llPrice;
        INT64       llBuyoutPrice;
        INT64       llDepositePrice;
    };

    struct M2G_AUCTION_BUY : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwAuctionID;
        INT64       llBidPrice;
        INT64       llAuctionPrice;
        INT64       llDepositPrice;
        UINT8       byBuyType;
    };

    struct M2G_AUCTION_PAY : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwAuctionID;
        INT64       llPrice;
    };

    struct M2G_EXCHANGE_ADD_ORDER : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nItemIDRequire;
        INT32       nItemCountRequire;
        UINT8       byOrderType;
        INT32       nPriceOrder;
        INT32       nCountOrder;
    };

    struct M2G_ADVENTURE_REWARD : MESSAGE_HEADER
    {
        INT32       nServerGroup;
        UINT32      dwRoleID;
        INT32       nGroupID;
        INT32       nAdventureID;
    };

    struct M2G_COMPLETE_ACHIEVEMENT : MESSAGE_HEADER
    {
        UINT32		dwRoleID;
        INT32		nAchievementID;
    };

    struct M2G_ENROLL_SABAC : MESSAGE_HEADER
    {
        UINT32		dwGuildID;
        UINT32		dwEnrollTime;
    };

    struct M2G_OCCUPY_SABAC : MESSAGE_HEADER
    {
        UINT32		dwOldGuildID;
        UINT32		dwNewGuildID;
    };

    struct M2G_QUERY_ROLE_LOCATION : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwClientSessionID;
        UINT32      dwTargetRoleID;
        UINT8		bFromItem;
    };

    struct M2G_QUERY_ROLE_LOCATION_ACK : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwClientSessionID;
        INT32       nSceneTempID;
        INT32       nSceneID;
        INT32       nX;
        INT32       nY;
        INT32       nZ;
        UINT8		bFromItem;
    };

    struct M2G_TAKE_ROLE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwClientSessionID;
        INT32       nSceneTempID;
        INT32       nSceneID;
        INT32       nX;
        INT32       nY;
        INT32       nZ;
    };

    struct M2G_ARREST_ROLE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwClientSessionID;
        INT32		nDuration;
    };

    struct M2G_QUERY_REAL_MONEY_REQ : MESSAGE_HEADER
    {
        UINT32      dwCliSessionID;
        UINT32      dwRoleID;
    };

    struct M2G_REAL_MONEY_BUY_SUCCESS : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nItemID;
        INT32       nStackCount;
        INT32       nItemCount;
        INT32		nOriginalPrice;
        char        szGiverRoleName[ROLE_NAME_LEN];
        UINT32		dwGiveRoleID;
    };

    struct M2G_FCM_STATE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT8       byFcmState;
    };

    struct M2G_FREE_MODE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT8       byFreeMode;
    };

    struct M2G_AWARD : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nItemID;
        INT32       nItemCount;
    };

    struct SERVER_VAR_DATA
    {
        UINT64	qwKey;
        INT32	nValue;
    };

    struct M2G_SYNC_SERVER_VARIABLE : MESSAGE_HEADER
    {
        UINT8			byServerGroup;
        SERVER_VAR_DATA	VarList[0];
    };

    struct M2G_UPDATE_SERVER_VARIABLE : MESSAGE_HEADER
    {
        UINT8		byServerGroup;
        UINT64		qwKey;
        INT32		nValue;
    };

    struct M2G_UPDATE_AVERAGE_LEVEL : MESSAGE_HEADER
    {
        INT32		nAverageLevel[MAX_SERVER_GROUP_COUNT];
    };

    struct BLACK_MARKET_LIMIT_INFO
    {
        INT32       nBlackMarketProductID;
        UINT32      dwCount;
    };

    struct M2G_GET_BLACK_MARKET_LIMIT_INFO : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nLimitInfoCount;
        BLACK_MARKET_LIMIT_INFO LimitInfo[0];
    };

    struct M2G_CHECK_BLACK_MARKET_PRODUCT : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nBlackMarketProductID;
        INT32       nResult;
        INT32       nCount;
    };

    struct M2G_ADD_EXERCISE_TIME : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nHour;
        INT32       nResult;
    };

    struct M2G_ROLE_REAL_MONEY_SHOP_BUY_ITEM_REQ : MESSAGE_HEADER
    {
        UINT32      dwCliSessionID;
        CHAR        szRoleName[ROLE_NAME_LEN];
        UINT32      dwRoleID;
        INT32       nTotalCost;
        INT32       nItemID;
        INT32       nItemCount;
    };

    struct M2G_CUSTOM_ROLE_BUY_TIME : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwBuyTimeCost;
    };

};
#pragma pack(pop)

#endif  // _M2G_MESSAGE_H_
