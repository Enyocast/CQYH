#ifndef _USER_H_
#define _USER_H_

#include "string_def.h"
#include "scene_def.h"
#include "base_list.h"

enum EUserState
{
    USER_STATE_INVALID = 0,
    USER_STATE_AUTHED,

    USER_STATE_QUEUEFINISHED,
	USER_STATE_LOGIN_WAIT_CREATE_SCENE,
    USER_STATE_LOGIN_PRE_ENTER_GS,
    USER_STATE_LOGIN_GSREADY,

    USER_STATE_INGAME,

    USER_STATE_EXIT_GS_PREENTER,	// remove?
    USER_STATE_EXIT_GS,
    USER_STATE_EXIT_2GS,
    USER_STATE_WAIT_EXIT_DB,
    USER_STATE_EXIT_DB,
    USER_STATE_EXIT_GS_RETURN,
    USER_STATE_EXIT_DB_RETURN,
    USER_STATE_JUMP_EXIT_TGT,

    USER_STATE_JUMP_WAIT_CREATE_SCENE, 
    USER_STATE_JUMP_PRE_ENTER_GS,	//should rename as USER_STATE_JUMP_PRE_ENTER_TGT to keep consistence.
    USER_STATE_JUMP_EXIT_SRC,		//should rename as USER_STATE_JUMP_LEAVE_GS, EXIT means exception path, and SRC is current GS.
	USER_STATE_JUMP_ENTER_TARGET,	//should rename as USER_STATE_JUMP_ENTER_TGT to keep consistence.
	USER_STATE_JUMP_GSREADY,
};

struct MS_USER
{
	char                    szUserName[USER_NAME_LEN];
    UINT32   		        dwCliSessionID;
    UINT32					dwClientIp;
	BOOL					bIpWhiteList;
	BOOL					bUserWhiteList;
    CHAR                    szMac[MAC_ADDRESS_LEN];
	BASE_LIST_NODE			WaitListNode;
	UINT32					dwLoginTime;

    char                    szOASessionID[OA_SESSION_ID_LEN];
	char                    szPGT[OA_PGT_FIELD_LEN];
    UINT8                   bAdult;
    UINT8                   byFcmState;

    EUserState              eState;
    UINT64                  qwTimer;
    UINT32                  dwCurRoleID;

    INT32					nShutdownType;
    BOOL                    bKicked;

    BOOL                    bFreeMode;
    UINT32                  dwFreeModeLastCheckTime;
    INT32                   nDianquan;
    INT32                   nTimeLeft;
    UINT32                  dwBeginTime;

    void                    SetFreeMode(BOOL fm);
};

#endif


