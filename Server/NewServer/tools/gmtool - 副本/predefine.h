/********************************************************************
	created:	13:8:2013   17:00
	file:		predefine.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_PREDEINE_H_
#define _H_PREDEINE_H_

//#include "./gm_def.h"


#define MAX_SEARCH_ROLE_NUM (32)
#define USER_SEARCH_TYPE_STRING_1 "角色名"

const char cszUserSearchTypeName[]    = "角色名";
const char cszUserSearchTypeID[] = "角色ID";
const char cszUserSearchTypeAccount[] = "账号";

const char cszItemSearchTypeGuid[] = "道具流水号";
const char cszItemSearchTypeTemplateID[] = "道具类型ID";

const char  cszAllSvr[]   = "全区全服";

const INT32 MIN_TIME = 1356969600;


const char cszMoneyTypeName[15][32] = {
    "绑金", 
    "金币", 
    "unused", 
    "unused", 
    "疲劳度", 
    "魂", 
    "名师值", 
    "万法之气", 
    "战场点数", 
    "家族贡献", 
    "修炼点", 
    "道义值", 
    "竞技场点数", 
    "成就点数",
    ""};

const char cszItemBagName[6][32] = {
    "装备",
    "背包一",
    "背包二",
    "背包三",
    "背包四",
    "仓库二"
    };

const char cszMailTypeName[2][32] = {
    "玩家邮件",
    "系统邮件",
};

const char cszMailIsNewName[2][32] = {
    "已领取",
    "未领取",
};

enum SESSION_CONNECT_STATE
{
    SESSION_NONE = 0,
    SESSION_CONNECTING = 1,
    SESSION_CONNECTED = 2,
    SESSION_DISCONNECTED = 3,
    SESSION_DEAD        = 4,
    
};

enum SESSION_LOGIN_STATE
{
    SESSION_CANNOT_LOGIN = 0,
    SESSION_CAN_LOGIN = 1,
};

enum GM_DIALOG_STATE
{
    DIALOG_NONE = 0,
    DIALOG_PRE_SHOW = 1,
    DIALOG_SHOW = 2,
};




enum GM_SVR_STATE
{
    GM_SVR_STATE_NONE = 0,
    //GM_SVR_STATE_CONNECTED = 1,         // yellow
    GM_SVR_STATE_REGISTERED = 2,        // green
    GM_SVR_STATE_LOGIN  = 3,       // white
    //GM_SVR_STATE_LOGIN_FAILED = 4,      // red
    GM_SVR_STATE_DISCONNECT = 5,        // disable
    GM_SVR_STATE_DEAD   = 6,
};


enum CMD_EXE_STATE
{
    CMD_EXE_UNEXECUTE       = 0,
    CMD_EXE_PREEXECUTING    = 1,
    CMD_EXE_EXECUTING       = 2,
    CMD_EXE_COMPLETE        = 3,
};





enum ROLE_SEARCH_TYPE
{
    ROLE_SEARCH_NONE        = 0,
    ROLE_SEARCH_BY_NAME     = 1,
    ROLE_SEARCH_BY_ID       = 2,
};








#endif //_H_PREDEINE_H_


