
#ifndef _H_GMSVR_MESSAGE_H_
#define _H_GMSVR_MESSAGE_H_


#include "internal_message_header.h"

#pragma pack(push, 1)

// tolua_begin


namespace InternalMessage
{
    enum GMSVR_MESSAGE_ID
    {
        gmsvr_begin = gmsvr_message_begin,

        // ms 2 gm server
        m2gm_register,
        m2gm_clear_role_cache_ack,
        m2gm_unlock_role_ack,
        m2gm_query_role_data_ack,
        m2gm_forbid_chat_ack,
        m2gm_freeze_role_ack,
        m2gm_kick_role_ack,
        m2gm_send_mail_ack,
        m2gm_announce_ack,
        m2gm_get_announce_list_ack,
        m2gm_del_announce_ack,
        m2gm_exe_gm_str_ack,

        m2gm_gm_str_cmd_log,
        m2gm_del_mail_ack,
        m2gm_check_role_freeze_ack,

        m2gm_get_exchange_price_ack,
        m2gm_get_exchange_price_detail_ack,
        m2gm_add_system_order_ack,
        m2gm_cancel_system_order_ack,
        m2gm_get_exchange_limit_ack,
        m2gm_set_exchange_limit_ack,


        // gm server 2 ms 
        gm2m_register_ack,
        gm2m_clear_role_cache,
        gm2m_unlock_role,
        gm2m_query_role_data,
        gm2m_forbid_chat,
        gm2m_freeze_role,
        gm2m_kick_role,
        gm2m_send_mail,
        gm2m_announce,
        gm2m_get_announce_list,
        gm2m_del_announce,
        gm2m_exe_gm_str,
        gm2m_del_mail,
        gm2m_check_role_freeze,
        gm2m_get_exchange_price,
        gm2m_get_exchange_price_detail,
        gm2m_add_system_order,
        gm2m_cancel_system_order,
        gm2m_get_exchange_limit,
        gm2m_set_exchange_limit,


        gmsvr_end = gmsvr_message_end,
    };



    struct M2GM_REGISTER : MESSAGE_HEADER 
    {
        char        szName[MS_NAME_LEN];
    };


    struct M2GM_CLEAR_ROLE_CACHE_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        INT32       nResult;
        UINT32      dwCmdSerialID;
    };

    struct M2GM_UNLOCK_ROLE_ACK : MESSAGE_HEADER 
    {
        UINT32      dwRoleID;
        INT32       nResult;
    };

    struct M2GM_QUERY_ROLE_DATA_ACK : MESSAGE_HEADER 
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        UINT32      dwRoleID;
        INT32       nResult;
        UINT32      dwLogoutTime;
    };
 
    struct M2GM_FORBID_CHAT_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        UINT32      dwRoleID;
        INT32       nResult;
    };

    struct M2GM_FREEZE_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        UINT32      dwRoleID;
        INT32       nResult;
    };

    struct M2GM_KICK_ROLE_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        UINT32      dwRoleID;
        INT32       nResult;
    };

    struct M2GM_SEND_MAIL_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        UINT32      dwRoleID;
        INT32       nResult;
    };

    struct M2GM_ANNOUNCE_ACK : MESSAGE_HEADER 
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        INT32       nResult;
    };

    struct ANNOUNCE_DATA 
    {
        INT32       nGroupID;
        UINT32      dwSerial;
        UINT32      dwIntervalTime;
        UINT32      dwRepeatNum;
        char        szText[GM_ANNOUNCE_LENGTH];
    };

    struct M2GM_GET_ANNOUNCE_LIST_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        INT32       nResult;
        INT32       nCount;
        ANNOUNCE_DATA   data[0];
    };

    struct M2GM_DEL_ANNOUNCE_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        INT32       nResult;
        UINT32      dwAnnounceSerial;
    };

    struct M2GM_EXE_GM_STR_ACK : MESSAGE_HEADER 
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        INT32       nResult;
    };

    struct M2GM_GM_STR_CMD_LOG : MESSAGE_HEADER 
    {
        UINT32      dwTime;
        UINT8       byGroupID;
        INT32       nResult;
        UINT32      dwRoleID;
        UINT32      dwIP;
        char        szRoleName[ROLE_NAME_LEN];
        char        szGMCommand[0];
    };


    struct M2GM_DEL_MAIL_ACK : MESSAGE_HEADER 
    {
        UINT32      dwTLUserID;
        UINT32      dwMailID;
        UINT32      dwCmdSerialID;
        INT32       nResult;
        char        szBuffer[0];
    };

    struct M2GM_CHECK_ROLE_FREEZE_ACK : MESSAGE_HEADER 
    {
        UINT32      dwTLUserID;
        UINT32      dwCmdSerialID;
        INT32       nResult;
    };

    struct EXCHANGE_PRICE_INFO
    {
        INT32       nPrice;
        INT32       nCount;
    };

    struct M2GM_GET_EXCHANGE_PRICE_ACK : MESSAGE_HEADER
    {
        UINT8       byGroupID;
        UINT8       bySellPriceCount;
        UINT8       byBuyPriceCount;
        EXCHANGE_PRICE_INFO stPrices[0];
    };

    struct EXCHANGE_COUNT_INFO
    {
        UINT32      dwRoleID;
        char        szRoleName[ROLE_NAME_LEN];
        INT32       nCount;
        UINT64      qwOrderID;
    };

    struct M2GM_GET_EXCHANGE_PRICE_DETAIL_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT8       byGroupID;
        UINT8       byOrderType;
        INT32       nPrice;
        UINT8       byCountCount;
        EXCHANGE_COUNT_INFO stCounts[0];
    };

    struct M2GM_ADD_SYSTEM_ORDER_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT8       byGroupID;
        UINT64      qwOrderID;
        INT32       nResult;
        INT32       nPrice;
        INT32       nCount;
    };

    struct M2GM_CANCEL_SYSTEM_ORDER_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT8       byGroupID;
        UINT64      qwOrderID;
        INT32       nResult;
        INT32       nPrice;
        INT32       nCount;
    };

    struct M2GM_GET_EXCHANGE_LIMIT_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT8       byGroupID;
        INT32       nPriceHigh;
        INT32       nPriceLow;
        INT32       nSingleOrderLimit;
        INT32       nDailyOrderLimit;
    };

    struct M2GM_SET_EXCHANGE_LIMIT_ACK : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT8       byGroupID;
        INT32       nPriceHigh;
        INT32       nPriceLow;
        INT32       nSingleOrderLimit;
        INT32       nDailyOrderLimit;
    };

    struct GM2M_REGISTER_ACK : MESSAGE_HEADER 
    {
    };


    struct GM2M_CLEAR_ROLE_CACHE : MESSAGE_HEADER
    {
        UINT32      dwTLUserID;
        UINT32      dwRoleID;
        UINT32      dwCmdSerialID;
    };

    struct GM2M_UNLOCK_ROLE : MESSAGE_HEADER 
    {
        UINT32  dwRoleID;
        char    szUserName[USER_NAME_LEN];
    };

    struct GM2M_QUERY_ROLE_DATA : MESSAGE_HEADER 
    {
        UINT32          dwTLUser;
        UINT32          dwCmdSerialID;
        UINT32          dwRoleID;
    };

    struct GM_ROLE_NAME_INFO
    {
        char        szRoleName[ROLE_NAME_LEN];
    };

    struct GM2M_FORBID_CHAT : MESSAGE_HEADER
    {
        UINT32          dwTLUser;
        UINT32          dwCmdSerialID;
        UINT32          dwTime;
        UINT32          dwRoleID;
    };

    struct GM2M_FREEZE_ROLE : MESSAGE_HEADER
    {
        UINT32          dwTLUser;
        UINT32          dwCmdSerialID;
        UINT32          dwTime;
        UINT32          dwRoleID;
    };

    struct GM2M_KICK_ROLE : MESSAGE_HEADER
    {
        UINT32          dwTLUser;
        UINT32          dwCmdSerialID;
        UINT32          dwRoleID;
    };

    struct GM2M_SEND_MAIL : MESSAGE_HEADER 
    {
        UINT32          dwTLUserID;
        UINT32          dwCmdSerialID;
        UINT32          dwRoleID;
        char            szSubject[MAIL_SUBJECT_LEN];
        char            szContent[MAIL_CONTENT_LEN];
        UINT32          dwItemID;
        INT32           nItemNum;
    };

    struct GM2M_ANNOUNCE : MESSAGE_HEADER 
    {
        UINT32          dwTLUserID;
        INT32           nGroupID;
        UINT32          dwCmdSerialID;
        UINT32          dwBeginTime;
        INT32           nRepeatNum;
        UINT32          dwIntervalTime;
        char            szText[0];
    };

    struct GM2M_GET_ANNOUNCE_LIST : MESSAGE_HEADER
    {
        INT32           nGroupID;
        UINT32          dwTLUserID;
        UINT32          dwCmdSerialID;
    };

    struct GM2M_DEL_ANNOUNCE : MESSAGE_HEADER
    {
        INT32           nGroupID;
        UINT32          dwTLUserID;
        UINT32          dwCmdSerialID;
        UINT32          dwAnnounceSerial;
    };

    struct GM2M_EXE_GM_STR : MESSAGE_HEADER 
    {
        UINT32          dwTLUserID;
        UINT32          dwCmdSerialID;
        char            szGMStr[0];
    };

    struct GM2M_DEL_MAIL : MESSAGE_HEADER 
    {
        UINT32          dwTLUserID;
        UINT32          dwCmdSerialID;
        UINT32          dwRoleID;
        UINT32          dwMailID;
    };

    struct GM2M_CHECK_ROLE_FREEZE : MESSAGE_HEADER
    {
        UINT32          dwTLUserID;
        UINT32          dwCmdSerialID;
        UINT32          dwRoleID;
    };

    struct GM2M_GET_EXCHANGE_PRICE : MESSAGE_HEADER
    {
        UINT8           byGroupID;
    };

    struct GM2M_GET_EXCHANGE_PRICE_DETAIL : MESSAGE_HEADER
    {
        UINT32          dwTLUserID;
        UINT8           byGroupID;
        UINT8           byOrderType;
        INT32           nPrice;
    };

    struct GM2M_ADD_SYSTEM_ORDER : MESSAGE_HEADER
    {
        UINT32          dwTLUserID;
        UINT8           byGroupID;
        INT32           nPrice;
        INT32           nCount;
    };

    struct GM2M_CANCEL_SYSTEM_ORDER : MESSAGE_HEADER
    {
        UINT32          dwTLUserID;
        UINT8           byGroupID;
        UINT64          qwOrderID;
    };

    struct GM2M_GET_EXCHANGE_LIMIT : MESSAGE_HEADER
    {
        UINT32          dwTLUserID;
        UINT8           byGroupID;
    };

    struct GM2M_SET_EXCHANGE_LIMIT : MESSAGE_HEADER
    {
        UINT32          dwTLUserID;
        UINT8           byGroupID;
        INT32           nPriceHigh;
        INT32           nPriceLow;
        INT32           nSingleOrderLimit;
        INT32           nDailyOrderLimit;
    };
}


// tolua_end

#pragma pack(pop)


#endif //_H_GMSVR_MESSAGE_H_






