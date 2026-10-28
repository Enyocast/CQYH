
#ifndef _H_GMTOOL_MESSAGE_H_
#define _H_GMTOOL_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)

namespace InternalMessage
{
    enum GMTOOL_MESSAGE_ID
    {
        tl_begin = gmtl_message_begin,

        tl2gm_register,
        tl2gm_verify,
        tl2gm_login,
        tl2gm_logout,

        tl2gm_pre_query,
        tl2gm_query_role_id,
        tl2gm_query_role_data,
        tl2gm_forbid_chat,
        tl2gm_freeze_role,
        tl2gm_kick_role,
        tl2gm_send_mail,
        tl2gm_announce,
        tl2gm_get_announce_list,
        tl2gm_del_announce,
        tl2gm_log,
        tl2gm_exe_gm_str,
        tl2gm_load_role_data,
        tl2gm_modify_role_data,
        tl2gm_release_role,
        tl2gm_query_name_to_id,
        tl2gm_role_exe_cmd,

        tl2gm_select_group,
        tl2gm_exchange_price,
        tl2gm_order_detail,
        tl2gm_exchange_history,
        tl2gm_add_system_order,
        tl2gm_del_system_order,
        tl2gm_sys_exchange_info,
        tl2gm_get_exchange_limit,
        tl2gm_set_exchange_limit,

        //
        gm2tl_register_ack,
        gm2tl_verify_ack,
        gm2tl_login_ack,
        gm2tl_item_list_ntf,
        gm2tl_logout_ack,
        gm2tl_pre_query_ack,
        gm2tl_query_role_id_ack,
        gm2tl_query_role_data_ack,
        gm2tl_forbid_chat_ack,
        gm2tl_freeze_role_ack,
        gm2tl_kick_role_ack,
        gm2tl_send_mail_ack,
        gm2tl_announce_ack,
        gm2tl_get_announce_list_ack,
        gm2tl_del_announce_ack,
        gm2tl_log_ack,
        gm2tl_exe_gm_str_ack,
        gm2tl_load_role_data_ack,
        gm2tl_modify_role_data_ack,
        gm2tl_query_name_to_id_ack,
        gm2tl_error_str,
        gm2tl_role_exe_gm_cmd,

        gm2tl_select_group_ack,
        gm2tl_query_exchange_log_ack,
        gm2tl_query_exchange_history_ack,
        gm2tl_exchange_price,
        gm2tl_query_order_detail_ack,
        gm2tl_add_system_order_ack,
        gm2tl_del_system_order_ack,
        gm2tl_query_sys_exchange_info_ack,
        gm2tl_get_exchange_limit_ack,
        gm2tl_set_exchange_limit_ack,

        tl_end = gmtl_message_end
    };

    struct TL2GM_REGISTER : MESSAGE_HEADER 
    {
        UINT32          dwIP;
        UINT16          wPort;
        char            szComputerName[128];
    };

    struct TL2GM_VERIFY : MESSAGE_HEADER
    {
        char            szName[USER_NAME_LEN];
        char            szPwd[GM_TOOL_PASSWORD_LEN];
    };

    struct TL2GM_LOGIN : MESSAGE_HEADER 
    {
        INT32           nVersion;
        INT32           nDependVersion;
        char            szName[USER_NAME_LEN];
        char            szPwd[GM_TOOL_PASSWORD_LEN];
    };

    struct TL2GM_LOGOUT : MESSAGE_HEADER 
    {
    };


    struct TL2GM_PRE_QUERY : MESSAGE_HEADER 
    {
        char        szRoleName[ROLE_NAME_LEN];
    };

    struct TL2GM_QUERY_ROLE_ID : MESSAGE_HEADER 
    {
        INT32       nQueryType;
        char        szName[USER_NAME_LEN];
    };

    struct TL2GM_QUERY_ROLE_DATA : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        char        szRoleName[ROLE_NAME_LEN];
    };

    struct TL2GM_FORBID_CHAT : MESSAGE_HEADER
    {
        UINT32      dwTime;
        UINT32      dwRoleID;
    };

    struct TL2GM_FREEZE_ROLE : MESSAGE_HEADER
    {
        UINT32      dwTime;
        UINT32      dwRoleID;
    };

    struct TL2GM_KICK_ROLE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct TL2GM_SEND_MAIL : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        char        szSubject[MAIL_SUBJECT_LEN];
        char        szContent[MAIL_CONTENT_LEN];
        char        szReason[GM_REASON_LEN];
        UINT32      dwItemID;
        INT32       nItemNum;
    };

    struct TL2GM_ANNOUNCE : MESSAGE_HEADER 
    {
        INT32       nGroupID;
        UINT32      dwBeginTime;
        INT32       nRepeatNum;
        UINT32      dwIntervalTime;
        char        szText[0];
    };

    struct TL2GM_GET_ANNOUNCE_LIST : MESSAGE_HEADER
    {
        INT32 nGroupID;
    };

    struct TL2GM_DEL_ANNOUNCE : MESSAGE_HEADER
    {
        INT32       nGroupID;
        UINT32      dwAnnounceSerial;
    };

    struct TL2GM_LOG : MESSAGE_HEADER 
    {
        INT32       nLogType;
        UINT32      dwBeginTime;
        UINT32      dwEndTime;
        char        szQueryStr[0];
    };

    struct TL2GM_EXE_GM_STR : MESSAGE_HEADER 
    {
        char        szStr[0];
    };

    struct TL2GM_LOAD_ROLE_DATA : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct TL2GM_MODIFY_ROLE_DATA : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        UINT32      dwTargetRoleID;
        INT32       nLength;
        char        szReason[GM_REASON_LEN];
        char        szData[0];
    };

    struct TL2GM_RELEASE_ROLE : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
    };

    struct TL2GM_QUERY_NAME_TO_ID : MESSAGE_HEADER 
    {
        INT32       nIndex;
        char        szRoleName[ROLE_NAME_LEN];
    };

    struct TL2GM_ROLE_EXE_CMD : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        char        szGM[MAX_GM_COMMAND_LEN];
        char        szReason[GM_REASON_LEN];
    };

    struct TL2GM_SELECT_GROUP : MESSAGE_HEADER 
    {
        UINT8       byGroupID;
    };

    struct TL2GM_EXCHANGE_PRICE : MESSAGE_HEADER 
    {
        UINT8       byGroupID;
    };

    struct TL2GM_ORDER_DETAIL : MESSAGE_HEADER
    {
        UINT8       byGroupID;
        UINT8       byOrderType;
        INT32       nPrice;
    };

    struct TL2GM_EXCHANGE_HISTORY : MESSAGE_HEADER
    {
        UINT8       byGroupID;
    };

    struct TL2GM_ADD_SYSTEM_ORDER : MESSAGE_HEADER
    {
        UINT8           byGroupID;
        INT32           nPrice;
        INT32           nCount;
    };

    struct TL2GM_DEL_SYSTEM_ORDER : MESSAGE_HEADER
    {
        UINT8           byGroupID;
        UINT64          qwOrderID;
    };

    struct TL2GM_SYS_EXCHANGE_INFO : MESSAGE_HEADER
    {
        UINT8           byGroupID;
        UINT8           byFlag;
        UINT32          dwBeginDayTime;
        UINT32          dwEndDayTime;
        UINT32          dwBeginHourTime;
        UINT32          dwEndHourTime;
    };

    struct TL2GM_GET_EXCHANGE_LIMIT  : MESSAGE_HEADER
    {
        UINT8           byGroupID;
    };

    struct TL2GM_SET_EXCHANGE_LIMIT : MESSAGE_HEADER
    {
        UINT8       byGroupID;
        INT32       nPriceHigh;
        INT32       nPriceLow;
        INT32       nSingleOrderLimit;
        INT32       nDailyOrderLimit;
    };




    //
    struct GM2TL_REGISTER_ACK : MESSAGE_HEADER 
    {
        INT32   nResult;
    };

    struct MS_INFO 
    {
        UINT32      dwIndex;
        char        szMSName[33];
    };

    struct GM2TL_VERIFY_ACK : MESSAGE_HEADER 
    {
        BOOL        bLD;
        INT32       nResult;
    };


    struct GM2TL_LOGIN_ACK : MESSAGE_HEADER 
    {
        INT32       nResult;
        INT32       nMSCount;
        MS_INFO     stMSInfo[MAX_MS_SESSION_COUNT];
    };

    struct ITEM_TEMPLATE_DATA 
    {
        UINT32      dwTempID;
        char        szName[MAX_ITEM_NAME_LEN];
    };

    struct GM2TL_ITEM_LIST_NTF : MESSAGE_HEADER
    {
        BOOL        bCLS;
        INT32       nCount;
        ITEM_TEMPLATE_DATA  data[0];
    };

    struct GM2TL_LOGOUT_ACK : MESSAGE_HEADER
    {

    };

    struct GM2TL_PRE_QUERY_ACK : MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        char        szRoleName[ROLE_NAME_LEN];
    };

    struct GM_ROLE_KEY_INFO 
    {
        UINT32      dwRoleID;
        char        szRoleName[ROLE_NAME_LEN];
        char        szUserName[USER_NAME_LEN];
    };

    struct GM2TL_QUERY_ROLE_ID_ACK : MESSAGE_HEADER
    {
        INT32       nAreaID;
        INT32       nCount;
        UINT8       byIsEnd;
        GM_ROLE_KEY_INFO    RoleKey[0];
    };


    //struct GM_ITEM_INFO
    //{
    //    UINT64      llGuid;
    //    UINT32      dwTemplateID;
    //    char        szItemName[MAX_ITEM_NAME_LEN];
    //    INT32       nConSlot;
    //    INT32       nItemSlot;
    //    INT32       nType;
    //    INT32       nNum;
    //};

    //struct GM_QUEST_INFO
    //{
    //    UINT32      dwTemplateID;
    //    char        szQuestName[COMMON_NAME_LEN];
    //};

    //struct GM_MAIL_INFO 
    //{
    //    UINT32      dwMailID;
    //    UINT32      dwMailTime;
    //    UINT8       byMailType;
    //    UINT8       byIsNew;
    //    char        szMailSubject[MAIL_SUBJECT_LEN];
    //    UINT8       byAttachType;
    //};

    struct GM2TL_QUERY_ROLE_DATA_ACK : MESSAGE_HEADER
    {
        INT32           nAreaID;
        UINT32          dwRoleID;
        BOOL            bIsOnline;
        INT32           nLength;
        char            szData[32000];
    };

    struct GM2TL_FORBID_CHAT_ACK : MESSAGE_HEADER
    {
        UINT32          dwRoleID;
        INT32           nResult;
    };

    struct GM2TL_FREEZE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32          dwRoleID;
        INT32           nResult;
    };

    struct GM2TL_KICK_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32          dwRoleID;
        INT32           nResult;
    };

    struct GM2TL_SEND_MAIL_ACK : MESSAGE_HEADER 
    {
        UINT32          dwRoleID;
        INT32           nResult;
    };

    struct GM2TL_ANNOUNCE_ACK : MESSAGE_HEADER
    {
        INT32       nGroupID;
        INT32       nAreaID;
        INT32       nResult;
    };

    struct GMTL_ANNOUNCE_DATA
    {
        INT32       nGroupID;
        UINT32      dwSerial;
        UINT32      dwIntervalTime;
        UINT32      dwRepeatNum;
        char        szText[GM_ANNOUNCE_LENGTH];
    };

    struct GM2TL_GET_ANNOUNCE_LIST_ACK : MESSAGE_HEADER
    {
        INT32       nGroupID;
        INT32       nCount;
        GMTL_ANNOUNCE_DATA   data[0];
    };

    struct GM2TL_DEL_ANNOUNCE_ACK : MESSAGE_HEADER
    {
        INT32       nGroupID;
        UINT32      dwAnnounceSerial;
    };

    struct GM2TL_LOG_ACK : MESSAGE_HEADER 
    {
        INT32       nLogType;
        BOOL        bTruncated;
        INT32       nLength;
        char        szBuffer[0];
    };

    struct GM2TL_EXE_GM_STR_ACK : MESSAGE_HEADER 
    {
    };

    struct GM2TL_LOAD_ROLE_DATA_ACK : MESSAGE_HEADER
    {
        INT32           nAreaID;
        UINT32          dwRoleID;
        INT32           nLength;
        char            szData[32000];
    };

    struct GM2TL_MODIFY_ROLE_DATA_ACK : MESSAGE_HEADER
    {
        INT32           nType;
        UINT32          dwRoleID;
        UINT32          dwID1;
    };

    struct GM2TL_QUERY_NAME_TO_ID_ACK : MESSAGE_HEADER 
    {
        INT32           nIndex;
        UINT32          dwRoleID;
    };

    struct GM2TL_ERROR_STR : MESSAGE_HEADER
    {
        char            szErr[0];
    };

    struct GM2TL_ROLE_EXE_GM_CMD : MESSAGE_HEADER 
    {
        UINT32          dwRoleID;
    };

    struct GM2TL_SELECT_GROUP_ACK  : MESSAGE_HEADER
    {
        UINT8       byGroupID;
    };

    struct GM2TL_QUERY_EXCHANGE_LOG_ACK : MESSAGE_HEADER 
    {
        UINT8       byGroupID;
        UINT8       byIsClear;
        INT32       nCount;
        char        pBuffer[0];
    };


    struct GM2TL_QUERY_EXCHANGE_HISTORY_ACK : MESSAGE_HEADER
    {
        UINT8       byGroupID;
        UINT8       byIsClear;
        INT32       nCount;
        char        pBuffer[0];
    };

    struct GMTL_EXCHANGE_PRICE_INFO
    {
        INT32       nPrice;
        INT32       nCount;
    };

    struct GM2TL_EXCHANGE_PRICE : MESSAGE_HEADER
    {
        UINT8       byGroupID;
        UINT8       bySellPriceCount;
        UINT8       byBuyPriceCount;
        GMTL_EXCHANGE_PRICE_INFO stPrices[0];
    };

    struct GM_EXCHANGE_COUNT_INFO
    {
        UINT32      dwRoleID;
        char        szRoleName[ROLE_NAME_LEN];
        UINT64      qwOrderID;
        INT32       nCount;
    };

    struct GM2TL_QUERY_ORDER_DETAIL_ACK : MESSAGE_HEADER
    {
        UINT8       byGroupID;
        UINT8       byOrderType;
        INT32       nPrice;
        UINT8       byCountCount;
        GM_EXCHANGE_COUNT_INFO stCounts[0];
    };
    
    struct GM2TL_ADD_SYSTEM_ORDER_ACK : MESSAGE_HEADER
    {
        UINT8       byGroupID;
        UINT64      qwOrderID;
        INT32       nResult;
        INT32       nPrice;
        INT32       nCount;
    };

    struct GM2TL_DEL_SYSTEM_ORDER_ACK : MESSAGE_HEADER
    {
        UINT8       byGroupID;
        UINT64      qwOrderID;
        INT32       nResult;
        INT32       nPrice;
        INT32       nCount;
    };

    struct GM2TL_QUERY_SYS_EXCHANGE_INFO_ACK : MESSAGE_HEADER 
    {
        UINT32          dwBeginTime;
        UINT32          dwEndTime;
        UINT8           byGroupID;
        UINT8           byFlag;
        INT64           llSysTotalMoney;
        INT64           llTotalMoney;
        INT64           llSysTotalExchangeMoney;
        INT64           llTotalExchangeMoney;
        INT64           llSysExchangeRMB;
        INT64           llExchangeRMB;
        INT32           nAveragePriceToday;
        INT32           nAveragePriceLastHour;
    };

    struct GM2TL_GET_EXCHANGE_LIMIT_ACK : MESSAGE_HEADER 
    {
        UINT8       byGroupID;
        INT32       nPriceHigh;
        INT32       nPriceLow;
        INT32       nSingleOrderLimit;
        INT32       nDailyOrderLimit;
    };

    struct GM2TL_SET_EXCHANGE_LIMIT_ACK : MESSAGE_HEADER 
    {
        UINT8       byGroupID;
        INT32       nPriceHigh;
        INT32       nPriceLow;
        INT32       nSingleOrderLimit;
        INT32       nDailyOrderLimit;
    };

}
#pragma pack(pop)

#endif //_H_GMTOOL_MESSAGE_H_

