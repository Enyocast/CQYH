// gs guild data for asimov & gameserver Allan Tao[12.8.2014] 

#ifndef _H_GS_GUILD_DATA_H_
#define _H_GS_GUILD_DATA_H_

// tolua_begin

struct GUILD_WAR_DATA
{
    UINT32  dwIntruderID;
    UINT32  dwDefenderID;
};

struct GS_G_B_DATA
{
    GS_G_B_DATA() : qwNameID(0), nType(0), nLevel(0), dwReviveTime(0)    { }
    GS_G_B_DATA(NAMEID qwID, INT32 nT, INT32 nL) : qwNameID(qwID), nType(nT), nLevel(nL), dwReviveTime(0)    { }

    NAMEID      qwNameID;
    INT32       nType;
    INT32       nLevel;
    UINT32      dwReviveTime;
};

// tolua_end


#endif //_H_GS_GUILD_DATA_H_





