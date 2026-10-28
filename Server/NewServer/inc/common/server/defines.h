#ifndef __SGDP_MMO_DEFINES_
#define __SGDP_MMO_DEFINES_

#include "sdtype.h"


#define   ELEMENT_HOLDAUTH                    "HoldAuthTime"
#define   ELEMENT_BROADCAST_SERVERLIST        "BroadcastSvrListTime"

#define   USERID_SPILITTER                    _SDT("~^")

// Error type enumeration
enum ECenterServerErrors
{
    CS_NO_ERROR=0,
    CS_FINDUSER_FAILED,
    CS_USER_REPEATED_LOGIN,
    CS_USER_FAILED_LOGIN,
    CS_SYSTEM_FAILED
};
// Center Server definitions
enum ESubscriptState
{
	CANCELED_SUBSCRIPTED=0,
	SUBSCRIPTED,
};

//  Subscription type
enum ESubscriptType
{
	SUBSCRIPT_BYTYPE=0,//  When subscribing by server type, m_dwSubscriptID identifies the server type;
};

#endif

