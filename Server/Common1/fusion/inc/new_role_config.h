#ifndef _NEW_ROLE_CONFIG_H_
#define _NEW_ROLE_CONFIG_H_

#include "char_def.h"

// tolua_begin
#pragma pack(push, 8)

struct NEW_ROLE_CONFIG
{
    INT32       nSceneTempID;
    INT32	    nX;
    INT32	    nY;
    INT32	    nZ;
    UINT16	    wFaceDirection;

    struct NEW_EQUIP
    {
        INT32   nMainHand;
        INT32   nBody;
        INT32   nBack;
    };

    NEW_EQUIP   MaleNewEquip[clsPlayerEnd];
    NEW_EQUIP   FemaleNewEquip[clsPlayerEnd];

};

extern NEW_ROLE_CONFIG g_NewRoleConfig;

#pragma pack(pop)
// tolua_end

#endif  // _NEW_ROLE_CONFIG_H_