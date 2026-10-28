/********************************************************************
	created:	3:12:2013   20:03
	file:		gm_predefine.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GM_SVR_DEF_H_
#define _H_GM_SVR_DEF_H_

#define GM_COMMAND_TABLE_PATH      "globalconfig/gmsecurityconfig.lua"
#define MAX_GM_USER     (128)

#define MAX_ITEM_BUFFER_SIZE        (32 * 1024)
#define MAX_GMSVR_ROLE_KEY_NUM      (2048)
 
enum GM_COMMAND
{
    GM_CMD_NONE = 0,

    GM_CMD_PRE_QUERY,
    GM_CMD_QUERY_ROLE_ID ,
    GM_CMD_QUERY_ROLE_DATA,
    GM_CMD_FORBID_CHAT ,
    GM_CMD_FREEZE_ROLE ,
    GM_CMD_KICK_ROLE ,
    GM_CMD_ANNOUNCE,
    GM_CMD_GET_ANNOUNCE_LIST,
    GM_CMD_DEL_ANNOUNCE,
    GM_CMD_SEND_MAIL,

    GM_CMD_LOG,
    GM_CMD_EXE_GM_STR,
    GM_CMD_LOAD_ROLE,
    GM_CMD_MODIFY_ROLE,
    GM_CMD_QUERY_NAME_TO_ID,
    GM_CMD_ROLE_EXE_GM_CMD,

    GM_CMD_SYS_EXCHANGE_INFO,


    GM_CMD_NUM,
};


enum CMD_STEP
{
    CMD_STEP_1      = 1,
    CMD_STEP_2      ,
    CMD_STEP_3,
    CMD_STEP_4,
    CMD_STEP_5,
    CMD_STEP_6,
    CMD_STEP_7,
    CMD_STEP_8,
};


enum GM_RECORD_TYPE
{
    GM_RECORD_FORBID_CHAT = 1,
    GM_RECORD_FREEZE_ROLE = 2,
    GM_RECORD_FREEZE_CHEAT_ROLE = 3,
};

enum TL_STATE
{
    TL_STATE_BUSY       = 1,
    TL_STATE_IDLE       = 2,
};

enum GM_ROLE_STATE
{
    GM_ROLE_PRE_LOCK    = 1,
    GM_ROLE_LOCK        = 2,
    GM_ROLE_PRE_UNLOCK  = 3,
    GM_ROLE_UNLOCK      = 4,
};

//

enum GM_PERMISSION
{
    GM_PERMISSION_A         = 100,        // admin
    GM_PERMISSION_PM        = 50,        // pm
    GM_PERMISSION_3         = 40,
    GM_PERMISSION_4         = 30,
    GM_PERMISSION_L         = 20,        // leader
    GM_PERMISSION_6         = 8,
    GM_PERMISSION_GM        = 7,        // gm
    GM_PERMISSION_8         = 6,
    GM_PERMISSION_9         = 5,
    GM_PERMISSION_GUEST     = 1,           // guest
};





enum GM_LOGIC_STATE
{
    GM_LS_TIMEOUT               = 2,

    GM_LS_PRE_QUERY_ROLE_ID = 3,

    GM_LS_MS_QUERY_ROLE_INFO    = 21,
    GM_LS_MS_QUERY_ROLE_INFO_ACK    = 22,



    GM_LS_MS_CHECK_ROLE_FREEZE  = 50,
    GM_LS_MS_CHECK_ROLE_FREEZE_ACK  = 51,


    GM_LS_MS_DEL_ROLE_CACHE     = 89,
    GM_LS_MS_DEL_ROLE_CACHE_ACK = 90,

    GM_LS_MS_QUERY_ANNOUNCE     = 91,
    GM_LS_MS_QUERY_ANNOUNCE_ACK = 92,


    GM_LS_FORBID_CHAT           = 101,
    GM_LS_FORBID_CHAT_ACK       = 102,

    GM_LS_FREEZE_ROLE           = 103,
    GM_LS_FREEZE_ROLE_ACK       = 104,

    GM_LS_KICK_ROLE             = 105,
    GM_LS_KICK_ROLE_ACK         = 106,

    GM_LS_SEND_MAIL             = 107,
    GM_LS_SEND_MAIL_ACK         = 108,

    GM_LS_ANNOUNCE              = 109,
    GM_LS_ANNOUNCE_ACK          = 110,

    GM_LS_DEL_ANNOUNCE          = 113,
    GM_LS_DEL_ANNOUNCE_ACK      = 114,


    GM_LS_QUERY_ROLE_NAME       = 111,
    GM_LS_QUERY_ROLE_NAME_ACK   = 112,


    GM_LS_QUERY_LOG             = 131,
    GM_LS_QUERY_LOG_ACK         = 132,

    GM_LS_EXE_SYS_CMD           = 133,
    GM_LS_EXE_SYS_CMD_ACK       = 134,


    GM_LS_QUERY_GUILD_ID = 171,
    GM_LS_QUERY_GUILD_ID_ACK = 172,

    GM_LS_QUERY_GM_FORBID = 181,
    GM_LS_QUERY_GM_FORBID_ACK = 182,


    GM_LS_MS_DEL_MAIL           = 209,
    GM_LS_MS_DEL_MAIL_ACK       = 210,

    GM_LS_LOAD_ROLE           = 260,
    GM_LS_LOAD_ROLE_ACK = 261,

    GM_LS_LOAD_MAIL         = 263,
    GM_LS_LOAD_MAIL_ACK     = 264,

    GM_LS_MODIFY_ROLE      = 280,
    GM_LS_MODIFY_ROLE_ACK  = 281,




    GM_LS_QUERY_NAME_LIST       = 301,
    GM_LS_QUERY_NAME_LIST_ACK   = 302,



    // exchange

    GM_LS_SYS_EXCHANGE_ORDER        = 1001,
    GM_LS_SYS_EXCHANGE_ORDER_ACK    = 1002,

    GM_LS_SYS_EXCHANGE_LOG          = 1003,
    GM_LS_SYS_EXCHANGE_LOG_ACK      = 1004,

};






#endif //_H_GM_SVR_DEF_H_


