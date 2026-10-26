#ifndef _H_YY_GUILD_H_
#define _H_YY_GUILD_H_

#include "string_def.h"


class CSqlMgr;

#pragma pack(push, 1)
struct YY_GUILD_DB
{
    char            szCreateTime[21];
    char            szDeleteTime[21];

    UINT32          dwGuildID;
    UINT16          wVersion;
    CHAR            szGuildName[GUILD_NAME_LEN];
    UINT8           byGroupID;
    UINT32          dwLeaderID;

    CHAR            szCreaterName[ROLE_NAME_LEN];
    UINT32          dwCreateTime;
    CHAR            szAnnounce[GUILD_ANNOUNCE_LEN];         // 家族宣言
    CHAR            szNotice[GUILD_NOTICE_LEN];             // 家族公告
    char            BlobBuffer[0];
};
#pragma pack(pop)


struct YY_GUILD_DATA 
{
    char    szCreateTime[21];
    char    szDeleteTime[21];

    INT32           nMemberCount;

    UINT32          dwGuildID;
    CHAR            szGuildName[GUILD_NAME_LEN];
    INT32           nGroupID;
    UINT32          dwLeaderID;

    CHAR            szCreaterName[ROLE_NAME_LEN];
    UINT32          dwCreateTime;

    INT32           nGuildLevel;

    INT32           nGuildMoney;
    INT32           nWood;
    INT32           nHerb;
    INT32           nCrystal;
    INT32           nSilver;

    BOOL Load(const char *pcData);
};

struct YY_GUILD_STAT 
{
    typedef std::list<YY_GUILD_DATA*>    GUILD_LIST;
    GUILD_LIST  GuildList;
};


struct YY_GUILD_MEMBER 
{
    UINT32      dwRoleID;
    UINT32      dwGuildID;
    char        szGuildName[GUILD_NAME_LEN];
    char        szRoleName[ROLE_NAME_LEN];
    char        szUserName[USER_NAME_LEN];
};


typedef std::list<YY_GUILD_MEMBER>    MEMBER_LIST;




void _LoadGuild(CSqlMgr& sqlmgr);

BOOL CB_ExportGuild(std::list<void*>& rResult, void* pUserData);
BOOL CB_ExportGuildMember(std::list<void*>& rResult, void* pUserData);

BOOL TemporaryLoadGuild();

extern YY_GUILD_STAT  g_GuildStat;




// member

void _LoadMember(CSqlMgr& sqlmgr);
BOOL CB_ExportGuildMemberInfo(std::list<void*>& rResult, void* pUserData);





#endif //_H_YY_GUILD_H_
