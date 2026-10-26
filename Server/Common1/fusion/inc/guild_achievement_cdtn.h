#ifndef _H_GUILD_ACHI_CDTN_H_
#define _H_GUILD_ACHI_CDTN_H_

#include "data_manager.h"

#define GACDTN_ID(__type__, __level__)		(((__type__) << 16) | (__level__))

//tolua_begin


struct GUILD_ACHI_CDTN
{
    INT32   nCdtnType;
    INT32   nParam1;

    INT32   nPos;

    static BOOL HasName(void)	{ return FALSE; }

    static BOOL ReadLine(INT32& rnID, const char*& rpcszName, GUILD_ACHI_CDTN* pData, CTabFile* pTabConfig, INT32 nRow);
};

//tolua_end


const GUILD_ACHI_CDTN * GetGuildAchiCdtn(INT32 nCdtnType, INT32 nParam1);






#endif //_H_GUILD_ACHI_CDTN_H_

