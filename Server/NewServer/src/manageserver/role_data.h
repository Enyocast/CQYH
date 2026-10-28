#ifndef _ROLE_DATA_H_
#define _ROLE_DATA_H_

#include "linux_map.h"
#include "string_def.h"
#include "mail/mail.h"
#include "item_def.h"
#include "role_db_def.h"

struct Auction;

struct ROLE_NAME_KEY
{
    UINT64 qwKey0;
    UINT64 qwKey1;
    UINT64 qwKey2;
    UINT32 dwPadding;

    inline bool operator < (ROLE_NAME_KEY& right)
    {
        if (qwKey0 != right.qwKey0)
            return qwKey0 < right.qwKey0;
        if (qwKey1 != right.qwKey1)
            return qwKey1 < right.qwKey1;
        return qwKey2 < right.qwKey2;
    }
    inline bool operator > (ROLE_NAME_KEY& right)
    {
        if (qwKey0 != right.qwKey0)
            return qwKey0 > right.qwKey0;
        if (qwKey1 != right.qwKey1)
            return qwKey1 > right.qwKey1;
        return qwKey2 > right.qwKey2;
    }
};

#pragma pack(push, 1)

struct MS_ROLE_DATA
{
    UINT32          dwRoleID;
    union
    {
        CHAR                        szRoleName[ROLE_NAME_LEN];
        LM_MAP_NODE<ROLE_NAME_KEY>  RoleNameNode;
    };
    char            szUserName[USER_NAME_LEN];
    UINT8			byGroup;
	UINT8           byLevel;
    UINT8           bySex;
    UINT8           byClass;
    UINT8           byVIPLevel;
    INT32           nLastLoginTime; // Unused elsewhere; temporarily assigned to guild. Allan Tao [9.6.2013]

    UINT32          dwForbidChatTime;
    UINT32          dwLoginFrozenTime;

	INT32		    nSceneTempID;
	INT32		    nSceneID;
    
    UINT32          dwTeamID;
    
    UINT32          dwMailCounts;
    CBaseList       lstMails;

	//UINT32        dwArenaTeamID;
	//INT32		    nPersonalArenaScore;

    // auction
    Auction*        pSellingAuction;
    Auction*        pBuyingAuction;

    // exchange


    enum EQueryStatus
    {
        eqsFree,
        eqsGsAuctionSell,
        eqsGsAuctionBuy,
        eqsGsAuctionPay,
        eqsAuctionSearch,
        eqsGsExchange,
        eqsBillFreeze,
    };
    UINT8 eAuctionQueryStatus;

    // guild
    // todo_tq guild: consider reusing this field. Allan Tao [22.4.2013]
    UINT32      dwGuildID;
    UINT32      dwJoinGuildCD;
    UINT8       byApplicationCount;
    //G_GUILD_APPLICANTION_DATA       *pGuildAppList;

    BOOL LoadBaseData(ROLE_DB_BASE_DATA* base_data);
};

#pragma pack(pop)

#endif  // _ROLE_DATA_H_
