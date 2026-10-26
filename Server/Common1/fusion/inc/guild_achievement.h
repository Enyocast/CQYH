#ifndef _H_GUILD_ACHIEVEMENT_H_
#define _H_GUILD_ACHIEVEMENT_H_


#include "data_manager.h"


//tolua_begin

static const INT16  GuildAchiAwardTableSize = 5;
static const INT16  GuildAchiCdtnTableSize = 4;

struct GUILD_ACHIEVEMENT 
{
    INT32       nID;

    struct GA_CDTN_DATA 
    {
        INT32   nCdtnType;
        INT32   nParam1;
    };
    GA_CDTN_DATA    CdtnData[GuildAchiCdtnTableSize];

    struct GA_AWARD_DATA 
    {
        INT32   nAwardType;
        UINT32  dwTemplateID;
        INT32   nNum;
    };
    GA_AWARD_DATA   AwardData[GuildAchiAwardTableSize];

    static BOOL HasName(void)	{ return FALSE; }

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GUILD_ACHIEVEMENT* pData, CTabFile* pTabConfig, INT32 nRow);
};

//tolua_end


const GUILD_ACHIEVEMENT * GetGuildAchievement(INT32 nID);



#endif //_H_GUILD_ACHIEVEMENT_H_

