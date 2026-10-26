/*
** Lua binding: teleport
** Generated automatically by tolua++-1.0.92 on 04/02/25 20:04:31.
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_teleport_open (lua_State* tolua_S);

#include "../../../Common/define/teleport_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SCENE_TELEPORTS");
 tolua_usertype(tolua_S,"TELEPORT_PLATFORM");
}

/* get function: ID of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_ID
static int tolua_get_SCENE_TELEPORTS_ID(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ID of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_ID
static int tolua_set_SCENE_TELEPORTS_ID(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SrcSceneID of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_SrcSceneID
static int tolua_get_SCENE_TELEPORTS_SrcSceneID(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcSceneID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->SrcSceneID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SrcSceneID of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_SrcSceneID
static int tolua_set_SCENE_TELEPORTS_SrcSceneID(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcSceneID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SrcSceneID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SrcRadius of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_SrcRadius
static int tolua_get_SCENE_TELEPORTS_SrcRadius(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcRadius'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->SrcRadius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SrcRadius of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_SrcRadius
static int tolua_set_SCENE_TELEPORTS_SrcRadius(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcRadius'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SrcRadius = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SrcSceneX of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_SrcSceneX
static int tolua_get_SCENE_TELEPORTS_SrcSceneX(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcSceneX'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->SrcSceneX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SrcSceneX of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_SrcSceneX
static int tolua_set_SCENE_TELEPORTS_SrcSceneX(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcSceneX'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SrcSceneX = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SrcSceneY of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_SrcSceneY
static int tolua_get_SCENE_TELEPORTS_SrcSceneY(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcSceneY'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->SrcSceneY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SrcSceneY of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_SrcSceneY
static int tolua_set_SCENE_TELEPORTS_SrcSceneY(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcSceneY'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SrcSceneY = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SrcSceneZ of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_SrcSceneZ
static int tolua_get_SCENE_TELEPORTS_SrcSceneZ(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcSceneZ'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->SrcSceneZ);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SrcSceneZ of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_SrcSceneZ
static int tolua_set_SCENE_TELEPORTS_SrcSceneZ(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SrcSceneZ'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SrcSceneZ = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: TargetSceneID of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_TargetSceneID
static int tolua_get_SCENE_TELEPORTS_TargetSceneID(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetSceneID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->TargetSceneID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TargetSceneID of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_TargetSceneID
static int tolua_set_SCENE_TELEPORTS_TargetSceneID(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetSceneID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TargetSceneID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: TargetSceneX of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_TargetSceneX
static int tolua_get_SCENE_TELEPORTS_TargetSceneX(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetSceneX'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->TargetSceneX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TargetSceneX of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_TargetSceneX
static int tolua_set_SCENE_TELEPORTS_TargetSceneX(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetSceneX'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TargetSceneX = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: TargetSceneY of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_TargetSceneY
static int tolua_get_SCENE_TELEPORTS_TargetSceneY(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetSceneY'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->TargetSceneY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TargetSceneY of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_TargetSceneY
static int tolua_set_SCENE_TELEPORTS_TargetSceneY(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetSceneY'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TargetSceneY = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: TargetSceneZ of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_TargetSceneZ
static int tolua_get_SCENE_TELEPORTS_TargetSceneZ(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetSceneZ'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->TargetSceneZ);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TargetSceneZ of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_TargetSceneZ
static int tolua_set_SCENE_TELEPORTS_TargetSceneZ(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetSceneZ'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TargetSceneZ = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: TargetRotationYaw of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_TargetRotationYaw
static int tolua_get_SCENE_TELEPORTS_TargetRotationYaw(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetRotationYaw'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->TargetRotationYaw);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TargetRotationYaw of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_TargetRotationYaw
static int tolua_set_SCENE_TELEPORTS_TargetRotationYaw(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetRotationYaw'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TargetRotationYaw = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: TargetRadius of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_get_SCENE_TELEPORTS_TargetRadius
static int tolua_get_SCENE_TELEPORTS_TargetRadius(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetRadius'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->TargetRadius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TargetRadius of class  SCENE_TELEPORTS */
#ifndef TOLUA_DISABLE_tolua_set_SCENE_TELEPORTS_TargetRadius
static int tolua_set_SCENE_TELEPORTS_TargetRadius(lua_State* tolua_S)
{
  SCENE_TELEPORTS* self = (SCENE_TELEPORTS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TargetRadius'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TargetRadius = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ID of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_ID
static int tolua_get_TELEPORT_PLATFORM_ID(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ID of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_ID
static int tolua_set_TELEPORT_PLATFORM_ID(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nInitEnable of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_nInitEnable
static int tolua_get_TELEPORT_PLATFORM_nInitEnable(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nInitEnable'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nInitEnable);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nInitEnable of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_nInitEnable
static int tolua_set_TELEPORT_PLATFORM_nInitEnable(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nInitEnable'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nInitEnable = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nMoneyType of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_nMoneyType
static int tolua_get_TELEPORT_PLATFORM_nMoneyType(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMoneyType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMoneyType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMoneyType of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_nMoneyType
static int tolua_set_TELEPORT_PLATFORM_nMoneyType(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMoneyType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nMoneyType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nMoney of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_nMoney
static int tolua_get_TELEPORT_PLATFORM_nMoney(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMoney'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMoney);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMoney of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_nMoney
static int tolua_set_TELEPORT_PLATFORM_nMoney(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMoney'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nMoney = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSceneID of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_nSceneID
static int tolua_get_TELEPORT_PLATFORM_nSceneID(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneID of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_nSceneID
static int tolua_set_TELEPORT_PLATFORM_nSceneID(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSceneID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRadius of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_nRadius
static int tolua_get_TELEPORT_PLATFORM_nRadius(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRadius'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRadius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRadius of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_nRadius
static int tolua_set_TELEPORT_PLATFORM_nRadius(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRadius'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRadius = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSceneX of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_nSceneX
static int tolua_get_TELEPORT_PLATFORM_nSceneX(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneX'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneX of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_nSceneX
static int tolua_set_TELEPORT_PLATFORM_nSceneX(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneX'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSceneX = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSceneY of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_nSceneY
static int tolua_get_TELEPORT_PLATFORM_nSceneY(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneY'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneY of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_nSceneY
static int tolua_set_TELEPORT_PLATFORM_nSceneY(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneY'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSceneY = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSceneZ of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_nSceneZ
static int tolua_get_TELEPORT_PLATFORM_nSceneZ(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneZ'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneZ);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneZ of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_nSceneZ
static int tolua_set_TELEPORT_PLATFORM_nSceneZ(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneZ'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSceneZ = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRotationYaw of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_get_TELEPORT_PLATFORM_nRotationYaw
static int tolua_get_TELEPORT_PLATFORM_nRotationYaw(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRotationYaw'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRotationYaw);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRotationYaw of class  TELEPORT_PLATFORM */
#ifndef TOLUA_DISABLE_tolua_set_TELEPORT_PLATFORM_nRotationYaw
static int tolua_set_TELEPORT_PLATFORM_nRotationYaw(lua_State* tolua_S)
{
  TELEPORT_PLATFORM* self = (TELEPORT_PLATFORM*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRotationYaw'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRotationYaw = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_teleport_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_TELEPORT_POINT_PER_SCENE",MAX_TELEPORT_POINT_PER_SCENE);
 tolua_constant(tolua_S,"INVALID_TELEPORT_ID",INVALID_TELEPORT_ID);
 tolua_constant(tolua_S,"MAX_TELEPORT_PLATFORM_COUNT",MAX_TELEPORT_PLATFORM_COUNT);
 tolua_cclass(tolua_S,"SCENE_TELEPORTS","SCENE_TELEPORTS","",NULL);
 tolua_beginmodule(tolua_S,"SCENE_TELEPORTS");
  tolua_variable(tolua_S,"ID",tolua_get_SCENE_TELEPORTS_ID,tolua_set_SCENE_TELEPORTS_ID);
  tolua_variable(tolua_S,"SrcSceneID",tolua_get_SCENE_TELEPORTS_SrcSceneID,tolua_set_SCENE_TELEPORTS_SrcSceneID);
  tolua_variable(tolua_S,"SrcRadius",tolua_get_SCENE_TELEPORTS_SrcRadius,tolua_set_SCENE_TELEPORTS_SrcRadius);
  tolua_variable(tolua_S,"SrcSceneX",tolua_get_SCENE_TELEPORTS_SrcSceneX,tolua_set_SCENE_TELEPORTS_SrcSceneX);
  tolua_variable(tolua_S,"SrcSceneY",tolua_get_SCENE_TELEPORTS_SrcSceneY,tolua_set_SCENE_TELEPORTS_SrcSceneY);
  tolua_variable(tolua_S,"SrcSceneZ",tolua_get_SCENE_TELEPORTS_SrcSceneZ,tolua_set_SCENE_TELEPORTS_SrcSceneZ);
  tolua_variable(tolua_S,"TargetSceneID",tolua_get_SCENE_TELEPORTS_TargetSceneID,tolua_set_SCENE_TELEPORTS_TargetSceneID);
  tolua_variable(tolua_S,"TargetSceneX",tolua_get_SCENE_TELEPORTS_TargetSceneX,tolua_set_SCENE_TELEPORTS_TargetSceneX);
  tolua_variable(tolua_S,"TargetSceneY",tolua_get_SCENE_TELEPORTS_TargetSceneY,tolua_set_SCENE_TELEPORTS_TargetSceneY);
  tolua_variable(tolua_S,"TargetSceneZ",tolua_get_SCENE_TELEPORTS_TargetSceneZ,tolua_set_SCENE_TELEPORTS_TargetSceneZ);
  tolua_variable(tolua_S,"TargetRotationYaw",tolua_get_SCENE_TELEPORTS_TargetRotationYaw,tolua_set_SCENE_TELEPORTS_TargetRotationYaw);
  tolua_variable(tolua_S,"TargetRadius",tolua_get_SCENE_TELEPORTS_TargetRadius,tolua_set_SCENE_TELEPORTS_TargetRadius);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"TELEPORT_PLATFORM","TELEPORT_PLATFORM","",NULL);
 tolua_beginmodule(tolua_S,"TELEPORT_PLATFORM");
  tolua_variable(tolua_S,"ID",tolua_get_TELEPORT_PLATFORM_ID,tolua_set_TELEPORT_PLATFORM_ID);
  tolua_variable(tolua_S,"nInitEnable",tolua_get_TELEPORT_PLATFORM_nInitEnable,tolua_set_TELEPORT_PLATFORM_nInitEnable);
  tolua_variable(tolua_S,"nMoneyType",tolua_get_TELEPORT_PLATFORM_nMoneyType,tolua_set_TELEPORT_PLATFORM_nMoneyType);
  tolua_variable(tolua_S,"nMoney",tolua_get_TELEPORT_PLATFORM_nMoney,tolua_set_TELEPORT_PLATFORM_nMoney);
  tolua_variable(tolua_S,"nSceneID",tolua_get_TELEPORT_PLATFORM_nSceneID,tolua_set_TELEPORT_PLATFORM_nSceneID);
  tolua_variable(tolua_S,"nRadius",tolua_get_TELEPORT_PLATFORM_nRadius,tolua_set_TELEPORT_PLATFORM_nRadius);
  tolua_variable(tolua_S,"nSceneX",tolua_get_TELEPORT_PLATFORM_nSceneX,tolua_set_TELEPORT_PLATFORM_nSceneX);
  tolua_variable(tolua_S,"nSceneY",tolua_get_TELEPORT_PLATFORM_nSceneY,tolua_set_TELEPORT_PLATFORM_nSceneY);
  tolua_variable(tolua_S,"nSceneZ",tolua_get_TELEPORT_PLATFORM_nSceneZ,tolua_set_TELEPORT_PLATFORM_nSceneZ);
  tolua_variable(tolua_S,"nRotationYaw",tolua_get_TELEPORT_PLATFORM_nRotationYaw,tolua_set_TELEPORT_PLATFORM_nRotationYaw);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_teleport (lua_State* tolua_S) {
 return tolua_teleport_open(tolua_S);
};
#endif

