#ifndef __SGDP_MMO_DEFINES_
#define __SGDP_MMO_DEFINES_

#include "sdtype.h"


#define   ELEMENT_HOLDAUTH                    "HoldAuthTime"
#define   ELEMENT_BROADCAST_SERVERLIST        "BroadcastSvrListTime"

#define   USERID_SPILITTER                    _SDT("~^")

// 错误类型枚举定义
enum ECenterServerErrors
{
    CS_NO_ERROR=0,
    CS_FINDUSER_FAILED,
    CS_USER_REPEATED_LOGIN,
    CS_USER_FAILED_LOGIN,
    CS_SYSTEM_FAILED
};
// Center Server相关定义
enum ESubscriptState
{
	CANCELED_SUBSCRIPTED=0,
	SUBSCRIPTED,
};

//  订阅类型
enum ESubscriptType
{
	SUBSCRIPT_BYTYPE=0,//  订阅的是类型服务器，则m_dwSubscriptID指向的是服务器的类型；
};

#endif

