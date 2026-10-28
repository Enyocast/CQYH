#ifndef _SERVER_DEF_H_
#define _SERVER_DEF_H_

enum SERVER_GROUP_STATE
{
    sgsInvalid,

    sgsInitializing,
    sgsSelfReady,
    sgsAllReady,
    sgsUnInitializing,
    sgsClosing,
    sgsClosed,

    sgsTotal
};

enum SESSION_TYPE
{
    stInvalid,

    stGD,
    stMS,
    stDB,
	stBS,
    stLS,
    stGT,
    stGS,
    stGM,
	stDL,
	stMM,
	stMG,
	stClient,
	stMT,
    stCS,
    stNS,
    
    stTL,
    stAll,

    stTotal
};

enum CLIENT_SHUTDOWN_TYPE
{
	csdtInvalid,

	csdtLogout,
	csdtTimeout,
	csdtClient,
	csdtDB,
	csdtGS,
	csdtGT,
	csdtMS,
	csdtMG,
	csdtMM,

	csdtTotal,
};

enum KICK_TYPE
{
    ktInvalid,

    ktImmediately,
    ktDelayed,
    ktLogged,

    ktTotal
};

enum SERVER_GROUP_INDEX
{
	Group0 = (1 << 0),
	Group1 = (1 << 1),
	Group2 = (1 << 2),
	Group3 = (1 << 3),
	Group4 = (1 << 4),
	Group5 = (1 << 5),
	Group6 = (1 << 6),
	Group7 = (1 << 7),
	Group8 = (1 << 8),
	Group9 = (1 << 9),
	Group10 = (1 << 10),
	Group11 = (1 << 11),
	Group12 = (1 << 12),
	Group13 = (1 << 13),
	Group14 = (1 << 14),
	Group15 = (1 << 15),
	Group16 = (1 << 16),
	Group17 = (1 << 17),
	Group18 = (1 << 18),
	Group19 = (1 << 19),
	Group20 = (1 << 20),
	Group21 = (1 << 21),
	Group22 = (1 << 22),
	Group23 = (1 << 23),
	Group24 = (1 << 24),
	Group25 = (1 << 25),
	Group26 = (1 << 26),
	Group27 = (1 << 27),
	Group28 = (1 << 28),
	Group29 = (1 << 29),
	Group30 = (1 << 30),
	Group31 = (1 << 31),

	GroupAll = 0xFFFF
};

#define SNDA_APPID					(991002359)
#define FCM_APPID                   (3001)  //防沉迷的appid只有2个bytes，所以防沉迷新开了一个appid，仅用于防沉迷
#define MAX_GS_SESSION_COUNT        (64)    // MAX_GS_SESSION_COUNT + MAX_GT_SESSION_COUNT <= 64 (FD_SETSIZE)
#define MAX_GT_SESSION_COUNT        (32)
#define MAX_MS_SESSION_COUNT        (32)
#define MAX_GM_SESSION_COUNT        (128)
#define MAX_GM_TL_SESSION_COUNT     (8)
#define MAX_MG_SESSION_COUNT		(8)
#define MAX_REMOTE_SESSION_COUNT    (64)
#define MAX_SERVER_GROUP_COUNT      (32)
#define MAX_AREA_COUNT				(1024)
#define MAX_GUARD_COUNT_PER_AREA	(16)
#define MAX_CLIENT_SESSION_COUNT    (0xFFFF)
#define MAX_BS_CLIENT_SESSION_COUNT (0x0FFF)
#define MAX_EXTERNAL_IP_COUNT		(8)

static const char* DEFAULT_PAK_PATH	= "data";

union CLIENT_SESSION_ID
{
    struct  
    {
        unsigned        SessionID       : 16;
        unsigned        GroupID         : 8;
        unsigned        GTSessionID     : 7;
		unsigned		IsMobile		: 1;
    };
    UINT32              dwSessionID;
};

#define IS_MOBILE_CLIENT(__session_id__)								(((CLIENT_SESSION_ID*)&(__session_id__))->IsMobile)
#define GET_GT_INDEX_FROM_SESSION_ID(__session_id__)					(((CLIENT_SESSION_ID*)&(__session_id__))->GTSessionID)
#define GET_GROUP_INDEX_FROM_SESSION_ID(__session_id__)					(((CLIENT_SESSION_ID*)&(__session_id__))->GroupID)
#define SET_GROUP_INDEX_TO_SESSION_ID(__session_id__, __group_id__)		((((CLIENT_SESSION_ID*)&(__session_id__))->GroupID) = (__group_id__))

#endif  // _SERVER_DEF_H_
