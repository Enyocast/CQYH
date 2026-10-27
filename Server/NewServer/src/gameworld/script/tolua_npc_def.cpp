/*
** Lua binding: npc_def
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_npc_def_open (lua_State* tolua_S);

#include "../../../Common/define/npc_def.h"
#include "../../../common/fusion/inc/npc_data.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CTabFile");
 tolua_usertype(tolua_S,"ADVENTURE_DATA");
 tolua_usertype(tolua_S,"NPC_DATA");
}

/* get function: nTemplateID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nTemplateID
static int tolua_get_NPC_DATA_nTemplateID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTemplateID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nTemplateID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nTemplateID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nTemplateID
static int tolua_set_NPC_DATA_nTemplateID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTemplateID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nClientTemplateID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nClientTemplateID
static int tolua_get_NPC_DATA_nClientTemplateID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nClientTemplateID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nClientTemplateID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nClientTemplateID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nClientTemplateID
static int tolua_set_NPC_DATA_nClientTemplateID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nClientTemplateID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nClientTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szDisplayName of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_szDisplayName
static int tolua_get_NPC_DATA_szDisplayName(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szDisplayName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szDisplayName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szDisplayName of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_szDisplayName
static int tolua_set_NPC_DATA_szDisplayName(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szDisplayName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szDisplayName,(const char*)tolua_tostring(tolua_S,2,0),MAX_NPC_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szName of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_szName
static int tolua_get_NPC_DATA_szName(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_szName
static int tolua_set_NPC_DATA_szName(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szName,(const char*)tolua_tostring(tolua_S,2,0),MAX_NPC_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nLevel of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nLevel
static int tolua_get_NPC_DATA_nLevel(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLevel'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nLevel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLevel of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nLevel
static int tolua_set_NPC_DATA_nLevel(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLevel'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nLevel = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nPatternID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nPatternID
static int tolua_get_NPC_DATA_nPatternID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPatternID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nPatternID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nPatternID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nPatternID
static int tolua_set_NPC_DATA_nPatternID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPatternID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nPatternID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nQuality of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nQuality
static int tolua_get_NPC_DATA_nQuality(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nQuality'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nQuality);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nQuality of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nQuality
static int tolua_set_NPC_DATA_nQuality(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nQuality'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nQuality = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nBroadcast of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nBroadcast
static int tolua_get_NPC_DATA_nBroadcast(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBroadcast'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nBroadcast);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nBroadcast of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nBroadcast
static int tolua_set_NPC_DATA_nBroadcast(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBroadcast'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nBroadcast = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nForceID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nForceID
static int tolua_get_NPC_DATA_nForceID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nForceID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nForceID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nForceID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nForceID
static int tolua_set_NPC_DATA_nForceID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nForceID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nForceID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bReduceReputation of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bReduceReputation
static int tolua_get_NPC_DATA_bReduceReputation(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bReduceReputation'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bReduceReputation);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bReduceReputation of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bReduceReputation
static int tolua_set_NPC_DATA_bReduceReputation(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bReduceReputation'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bReduceReputation = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSpecies of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nSpecies
static int tolua_get_NPC_DATA_nSpecies(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpecies'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSpecies);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSpecies of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nSpecies
static int tolua_set_NPC_DATA_nSpecies(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpecies'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSpecies = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRivalForceID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nRivalForceID
static int tolua_get_NPC_DATA_nRivalForceID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRivalForceID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRivalForceID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRivalForceID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nRivalForceID
static int tolua_set_NPC_DATA_nRivalForceID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRivalForceID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRivalForceID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGroupID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nGroupID
static int tolua_get_NPC_DATA_nGroupID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGroupID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nGroupID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGroupID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nGroupID
static int tolua_set_NPC_DATA_nGroupID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGroupID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nBodyType of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nBodyType
static int tolua_get_NPC_DATA_nBodyType(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBodyType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nBodyType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nBodyType of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nBodyType
static int tolua_set_NPC_DATA_nBodyType(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBodyType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nBodyType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSpellEffectGroup of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nSpellEffectGroup
static int tolua_get_NPC_DATA_nSpellEffectGroup(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpellEffectGroup'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSpellEffectGroup);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSpellEffectGroup of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nSpellEffectGroup
static int tolua_set_NPC_DATA_nSpellEffectGroup(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpellEffectGroup'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSpellEffectGroup = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSpawnTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nSpawnTime
static int tolua_get_NPC_DATA_nSpawnTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpawnTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSpawnTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSpawnTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nSpawnTime
static int tolua_set_NPC_DATA_nSpawnTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpawnTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSpawnTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nReviveTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nReviveTime
static int tolua_get_NPC_DATA_nReviveTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nReviveTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nReviveTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nReviveTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nReviveTime
static int tolua_set_NPC_DATA_nReviveTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nReviveTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nReviveTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nCorpseTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nCorpseTime
static int tolua_get_NPC_DATA_nCorpseTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCorpseTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCorpseTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCorpseTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nCorpseTime
static int tolua_set_NPC_DATA_nCorpseTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCorpseTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nCorpseTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nMinRespawnTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nMinRespawnTime
static int tolua_get_NPC_DATA_nMinRespawnTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMinRespawnTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMinRespawnTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMinRespawnTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nMinRespawnTime
static int tolua_set_NPC_DATA_nMinRespawnTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMinRespawnTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nMinRespawnTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nMaxRespawnTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nMaxRespawnTime
static int tolua_get_NPC_DATA_nMaxRespawnTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMaxRespawnTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMaxRespawnTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMaxRespawnTime of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nMaxRespawnTime
static int tolua_set_NPC_DATA_nMaxRespawnTime(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMaxRespawnTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nMaxRespawnTime = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nAIID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nAIID
static int tolua_get_NPC_DATA_nAIID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAIID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nAIID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nAIID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nAIID
static int tolua_set_NPC_DATA_nAIID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAIID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nAIID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bImmunePassiveMove of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bImmunePassiveMove
static int tolua_get_NPC_DATA_bImmunePassiveMove(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bImmunePassiveMove'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bImmunePassiveMove);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bImmunePassiveMove of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bImmunePassiveMove
static int tolua_set_NPC_DATA_bImmunePassiveMove(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bImmunePassiveMove'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bImmunePassiveMove = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInvincible of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInvincible
static int tolua_get_NPC_DATA_bInvincible(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInvincible'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInvincible);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInvincible of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInvincible
static int tolua_set_NPC_DATA_bInvincible(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInvincible'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInvincible = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAlwaysRun of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bAlwaysRun
static int tolua_get_NPC_DATA_bAlwaysRun(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAlwaysRun'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bAlwaysRun);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAlwaysRun of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bAlwaysRun
static int tolua_set_NPC_DATA_bAlwaysRun(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAlwaysRun'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAlwaysRun = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bCanbeThrown of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bCanbeThrown
static int tolua_get_NPC_DATA_bCanbeThrown(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCanbeThrown'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bCanbeThrown);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bCanbeThrown of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bCanbeThrown
static int tolua_set_NPC_DATA_bCanbeThrown(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCanbeThrown'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bCanbeThrown = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bIgnoreInvisible of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bIgnoreInvisible
static int tolua_get_NPC_DATA_bIgnoreInvisible(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bIgnoreInvisible'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bIgnoreInvisible);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bIgnoreInvisible of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bIgnoreInvisible
static int tolua_set_NPC_DATA_bIgnoreInvisible(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bIgnoreInvisible'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bIgnoreInvisible = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bCounterInvisible of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bCounterInvisible
static int tolua_get_NPC_DATA_bCounterInvisible(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCounterInvisible'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bCounterInvisible);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bCounterInvisible of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bCounterInvisible
static int tolua_set_NPC_DATA_bCounterInvisible(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCounterInvisible'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bCounterInvisible = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nAttackRange of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nAttackRange
static int tolua_get_NPC_DATA_nAttackRange(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAttackRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nAttackRange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nAttackRange of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nAttackRange
static int tolua_set_NPC_DATA_nAttackRange(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAttackRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nAttackRange = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bExclusive of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bExclusive
static int tolua_get_NPC_DATA_bExclusive(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bExclusive'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bExclusive);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bExclusive of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bExclusive
static int tolua_set_NPC_DATA_bExclusive(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bExclusive'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bExclusive = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bNeverBeHit of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bNeverBeHit
static int tolua_get_NPC_DATA_bNeverBeHit(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bNeverBeHit'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bNeverBeHit);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bNeverBeHit of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bNeverBeHit
static int tolua_set_NPC_DATA_bNeverBeHit(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bNeverBeHit'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bNeverBeHit = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bProfit of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bProfit
static int tolua_get_NPC_DATA_bProfit(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bProfit'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bProfit);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bProfit of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bProfit
static int tolua_set_NPC_DATA_bProfit(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bProfit'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bProfit = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nExpRate of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nExpRate
static int tolua_get_NPC_DATA_nExpRate(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nExpRate'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nExpRate);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nExpRate of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nExpRate
static int tolua_set_NPC_DATA_nExpRate(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nExpRate'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nExpRate = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSoulRate of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nSoulRate
static int tolua_get_NPC_DATA_nSoulRate(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSoulRate'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSoulRate);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSoulRate of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nSoulRate
static int tolua_set_NPC_DATA_nSoulRate(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSoulRate'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSoulRate = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bDailyExp of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bDailyExp
static int tolua_get_NPC_DATA_bDailyExp(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bDailyExp'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bDailyExp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bDailyExp of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bDailyExp
static int tolua_set_NPC_DATA_bDailyExp(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bDailyExp'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bDailyExp = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAuraInvalid of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bAuraInvalid
static int tolua_get_NPC_DATA_bAuraInvalid(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAuraInvalid'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bAuraInvalid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAuraInvalid of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bAuraInvalid
static int tolua_set_NPC_DATA_bAuraInvalid(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAuraInvalid'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAuraInvalid = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nKillPlayerVarIndex of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nKillPlayerVarIndex
static int tolua_get_NPC_DATA_nKillPlayerVarIndex(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nKillPlayerVarIndex'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nKillPlayerVarIndex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nKillPlayerVarIndex of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nKillPlayerVarIndex
static int tolua_set_NPC_DATA_nKillPlayerVarIndex(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nKillPlayerVarIndex'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nKillPlayerVarIndex = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nBeKilledVarIndex of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nBeKilledVarIndex
static int tolua_get_NPC_DATA_nBeKilledVarIndex(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBeKilledVarIndex'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nBeKilledVarIndex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nBeKilledVarIndex of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nBeKilledVarIndex
static int tolua_set_NPC_DATA_nBeKilledVarIndex(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBeKilledVarIndex'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nBeKilledVarIndex = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nShopID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nShopID
static int tolua_get_NPC_DATA_nShopID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nShopID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nShopID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nShopID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nShopID
static int tolua_set_NPC_DATA_nShopID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nShopID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nShopID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nBlackMarketID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nBlackMarketID
static int tolua_get_NPC_DATA_nBlackMarketID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBlackMarketID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nBlackMarketID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nBlackMarketID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nBlackMarketID
static int tolua_set_NPC_DATA_nBlackMarketID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBlackMarketID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nBlackMarketID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractBank of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractBank
static int tolua_get_NPC_DATA_bInteractBank(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractBank'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractBank);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractBank of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractBank
static int tolua_set_NPC_DATA_bInteractBank(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractBank'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractBank = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractGuildBank of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractGuildBank
static int tolua_get_NPC_DATA_bInteractGuildBank(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractGuildBank'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractGuildBank);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractGuildBank of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractGuildBank
static int tolua_set_NPC_DATA_bInteractGuildBank(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractGuildBank'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractGuildBank = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractRewardQuest of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractRewardQuest
static int tolua_get_NPC_DATA_bInteractRewardQuest(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractRewardQuest'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractRewardQuest);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractRewardQuest of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractRewardQuest
static int tolua_set_NPC_DATA_bInteractRewardQuest(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractRewardQuest'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractRewardQuest = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractCreateGuild of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractCreateGuild
static int tolua_get_NPC_DATA_bInteractCreateGuild(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractCreateGuild'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractCreateGuild);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractCreateGuild of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractCreateGuild
static int tolua_set_NPC_DATA_bInteractCreateGuild(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractCreateGuild'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractCreateGuild = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractGuildSalary of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractGuildSalary
static int tolua_get_NPC_DATA_bInteractGuildSalary(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractGuildSalary'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractGuildSalary);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractGuildSalary of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractGuildSalary
static int tolua_set_NPC_DATA_bInteractGuildSalary(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractGuildSalary'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractGuildSalary = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractAuction of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractAuction
static int tolua_get_NPC_DATA_bInteractAuction(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractAuction'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractAuction);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractAuction of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractAuction
static int tolua_set_NPC_DATA_bInteractAuction(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractAuction'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractAuction = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractRune of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractRune
static int tolua_get_NPC_DATA_bInteractRune(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractRune'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractRune);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractRune of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractRune
static int tolua_set_NPC_DATA_bInteractRune(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractRune'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractRune = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractSoul of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractSoul
static int tolua_get_NPC_DATA_bInteractSoul(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractSoul'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractSoul);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractSoul of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractSoul
static int tolua_set_NPC_DATA_bInteractSoul(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractSoul'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractSoul = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractWeaponLevelUpPutIn of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractWeaponLevelUpPutIn
static int tolua_get_NPC_DATA_bInteractWeaponLevelUpPutIn(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractWeaponLevelUpPutIn'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractWeaponLevelUpPutIn);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractWeaponLevelUpPutIn of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractWeaponLevelUpPutIn
static int tolua_set_NPC_DATA_bInteractWeaponLevelUpPutIn(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractWeaponLevelUpPutIn'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractWeaponLevelUpPutIn = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractWeaponLevelUpTakeOut of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractWeaponLevelUpTakeOut
static int tolua_get_NPC_DATA_bInteractWeaponLevelUpTakeOut(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractWeaponLevelUpTakeOut'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractWeaponLevelUpTakeOut);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractWeaponLevelUpTakeOut of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractWeaponLevelUpTakeOut
static int tolua_set_NPC_DATA_bInteractWeaponLevelUpTakeOut(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractWeaponLevelUpTakeOut'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractWeaponLevelUpTakeOut = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractSpecialRepair of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractSpecialRepair
static int tolua_get_NPC_DATA_bInteractSpecialRepair(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractSpecialRepair'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractSpecialRepair);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractSpecialRepair of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractSpecialRepair
static int tolua_set_NPC_DATA_bInteractSpecialRepair(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractSpecialRepair'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractSpecialRepair = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractGamble of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractGamble
static int tolua_get_NPC_DATA_bInteractGamble(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractGamble'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractGamble);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractGamble of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractGamble
static int tolua_set_NPC_DATA_bInteractGamble(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractGamble'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractGamble = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractExercise of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractExercise
static int tolua_get_NPC_DATA_bInteractExercise(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractExercise'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractExercise);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractExercise of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractExercise
static int tolua_set_NPC_DATA_bInteractExercise(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractExercise'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractExercise = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractSpellBookGamble of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractSpellBookGamble
static int tolua_get_NPC_DATA_bInteractSpellBookGamble(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractSpellBookGamble'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractSpellBookGamble);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractSpellBookGamble of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractSpellBookGamble
static int tolua_set_NPC_DATA_bInteractSpellBookGamble(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractSpellBookGamble'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractSpellBookGamble = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bInteractArenaReward of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bInteractArenaReward
static int tolua_get_NPC_DATA_bInteractArenaReward(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractArenaReward'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bInteractArenaReward);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bInteractArenaReward of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bInteractArenaReward
static int tolua_set_NPC_DATA_bInteractArenaReward(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bInteractArenaReward'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bInteractArenaReward = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nCorpseDoodadID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nCorpseDoodadID
static int tolua_get_NPC_DATA_nCorpseDoodadID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCorpseDoodadID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCorpseDoodadID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCorpseDoodadID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nCorpseDoodadID
static int tolua_set_NPC_DATA_nCorpseDoodadID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCorpseDoodadID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nCorpseDoodadID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bDieIDMonitor of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bDieIDMonitor
static int tolua_get_NPC_DATA_bDieIDMonitor(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bDieIDMonitor'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bDieIDMonitor);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bDieIDMonitor of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bDieIDMonitor
static int tolua_set_NPC_DATA_bDieIDMonitor(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bDieIDMonitor'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bDieIDMonitor = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bStatMoney of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_bStatMoney
static int tolua_get_NPC_DATA_bStatMoney(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bStatMoney'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bStatMoney);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bStatMoney of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_bStatMoney
static int tolua_set_NPC_DATA_bStatMoney(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bStatMoney'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bStatMoney = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nBigDropInterval of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nBigDropInterval
static int tolua_get_NPC_DATA_nBigDropInterval(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBigDropInterval'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nBigDropInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nBigDropInterval of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nBigDropInterval
static int tolua_set_NPC_DATA_nBigDropInterval(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nBigDropInterval'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nBigDropInterval = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRuneGroup of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nRuneGroup
static int tolua_get_NPC_DATA_nRuneGroup(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRuneGroup'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRuneGroup);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRuneGroup of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nRuneGroup
static int tolua_set_NPC_DATA_nRuneGroup(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRuneGroup'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRuneGroup = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nHandbookType of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nHandbookType
static int tolua_get_NPC_DATA_nHandbookType(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nHandbookType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nHandbookType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nHandbookType of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nHandbookType
static int tolua_set_NPC_DATA_nHandbookType(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nHandbookType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nHandbookType = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nHandbookIndex of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nHandbookIndex
static int tolua_get_NPC_DATA_nHandbookIndex(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nHandbookIndex'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nHandbookIndex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nHandbookIndex of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nHandbookIndex
static int tolua_set_NPC_DATA_nHandbookIndex(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nHandbookIndex'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nHandbookIndex = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nKillNpcQuestID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_nKillNpcQuestID
static int tolua_get_NPC_DATA_nKillNpcQuestID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nKillNpcQuestID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nKillNpcQuestID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nKillNpcQuestID of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_nKillNpcQuestID
static int tolua_set_NPC_DATA_nKillNpcQuestID(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nKillNpcQuestID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nKillNpcQuestID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pAdventureData of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_pAdventureData_ptr
static int tolua_get_NPC_DATA_pAdventureData_ptr(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pAdventureData'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->pAdventureData,"const ADVENTURE_DATA");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szScriptName of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_get_NPC_DATA_szScriptName
static int tolua_get_NPC_DATA_szScriptName(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szScriptName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->szScriptName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szScriptName of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_set_NPC_DATA_szScriptName
static int tolua_set_NPC_DATA_szScriptName(lua_State* tolua_S)
{
  NPC_DATA* self = (NPC_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szScriptName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szScriptName,(const char*)tolua_tostring(tolua_S,2,0),COMMON_NAME_LEN-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReadLine of class  NPC_DATA */
#ifndef TOLUA_DISABLE_tolua_npc_def_NPC_DATA_ReadLine00
static int tolua_npc_def_NPC_DATA_ReadLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"NPC_DATA",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"NPC_DATA",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,5,"CTabFile",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int rnID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  const char* rpcszName = ((const char*)  tolua_tostring(tolua_S,3,0));
  NPC_DATA* pData = ((NPC_DATA*)  tolua_tousertype(tolua_S,4,0));
  CTabFile* pTabConfig = ((CTabFile*)  tolua_tousertype(tolua_S,5,0));
  signed int nRow = (( signed int)  tolua_tonumber(tolua_S,6,0));
 {
 int tolua_ret = (int)
NPC_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 tolua_pushnumber(tolua_S,(lua_Number)rnID);
 tolua_pushstring(tolua_S,(const char*)rpcszName);
 }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReadLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_npc_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"MAX_NPC_ID",MAX_NPC_ID);
 tolua_constant(tolua_S,"MAX_NPC_FORCE_ID",MAX_NPC_FORCE_ID);
 tolua_constant(tolua_S,"INVALID_FORCE_ID",INVALID_FORCE_ID);
 tolua_constant(tolua_S,"MAX_NPC_LEVEL",MAX_NPC_LEVEL);
 tolua_constant(tolua_S,"MIN_NPC_RADIUS",MIN_NPC_RADIUS);
 tolua_constant(tolua_S,"MAX_LEVEL_DIFF",MAX_LEVEL_DIFF);
 tolua_constant(tolua_S,"MAX_PET_LEVEL",MAX_PET_LEVEL);
 tolua_constant(tolua_S,"CASTER_WASHOUT_TIME",CASTER_WASHOUT_TIME);
 tolua_constant(tolua_S,"TARGET_WASHOUT_TIME",TARGET_WASHOUT_TIME);
  tolua_constant(tolua_S,"npcInvalid",npcInvalid);
  tolua_constant(tolua_S,"npcSpawn",npcSpawn);
  tolua_constant(tolua_S,"npcAlive",npcAlive);
  tolua_constant(tolua_S,"npcCorpse",npcCorpse);
  tolua_constant(tolua_S,"npcRespawn",npcRespawn);
  tolua_constant(tolua_S,"npcRevive",npcRevive);
  tolua_constant(tolua_S,"npcTotal",npcTotal);
  tolua_constant(tolua_S,"nqInvalid",nqInvalid);
  tolua_constant(tolua_S,"nqNormal1",nqNormal1);
  tolua_constant(tolua_S,"nqNormal2",nqNormal2);
  tolua_constant(tolua_S,"nqNormal3",nqNormal3);
  tolua_constant(tolua_S,"nqNormal4",nqNormal4);
  tolua_constant(tolua_S,"nqNormal5",nqNormal5);
  tolua_constant(tolua_S,"nqElite",nqElite);
  tolua_constant(tolua_S,"nqRare",nqRare);
  tolua_constant(tolua_S,"nqBoss",nqBoss);
  tolua_constant(tolua_S,"nqTotal",nqTotal);
  tolua_constant(tolua_S,"npctInvalid",npctInvalid);
  tolua_constant(tolua_S,"npctNpc",npctNpc);
  tolua_constant(tolua_S,"npctPet",npctPet);
  tolua_constant(tolua_S,"npctTotal",npctTotal);
  tolua_constant(tolua_S,"petInvalid",petInvalid);
  tolua_constant(tolua_S,"petTotal",petTotal);
  tolua_constant(tolua_S,"petBornInvalid",petBornInvalid);
  tolua_constant(tolua_S,"petBornHoly",petBornHoly);
  tolua_constant(tolua_S,"petBornSkeleton",petBornSkeleton);
  tolua_constant(tolua_S,"petBornByMage",petBornByMage);
  tolua_constant(tolua_S,"petBornTotal",petBornTotal);
  tolua_constant(tolua_S,"psInvalid",psInvalid);
  tolua_constant(tolua_S,"psIdle",psIdle);
  tolua_constant(tolua_S,"psFight",psFight);
  tolua_constant(tolua_S,"psTotal",psTotal);
  tolua_constant(tolua_S,"PET_AIV_MAGE_PET_SPELL_ID",PET_AIV_MAGE_PET_SPELL_ID);
  tolua_constant(tolua_S,"PET_AIV_FIGHT_STATE_INDEX",PET_AIV_FIGHT_STATE_INDEX);
  tolua_constant(tolua_S,"PET_AI_CONTROL",PET_AI_CONTROL);
  tolua_constant(tolua_S,"PET_AI_IS_EXTRA_WALK",PET_AI_IS_EXTRA_WALK);
  tolua_constant(tolua_S,"PET_AI_MAGE_CHASE_THRESHOLD",PET_AI_MAGE_CHASE_THRESHOLD);
  tolua_constant(tolua_S,"PET_AI_MAGE_PREFER_DISTANCE",PET_AI_MAGE_PREFER_DISTANCE);
  tolua_constant(tolua_S,"PET_AI_GO_HOME",PET_AI_GO_HOME);
 tolua_cclass(tolua_S,"NPC_DATA","NPC_DATA","",NULL);
 tolua_beginmodule(tolua_S,"NPC_DATA");
  tolua_variable(tolua_S,"nTemplateID",tolua_get_NPC_DATA_nTemplateID,tolua_set_NPC_DATA_nTemplateID);
  tolua_variable(tolua_S,"nClientTemplateID",tolua_get_NPC_DATA_nClientTemplateID,tolua_set_NPC_DATA_nClientTemplateID);
  tolua_variable(tolua_S,"szDisplayName",tolua_get_NPC_DATA_szDisplayName,tolua_set_NPC_DATA_szDisplayName);
  tolua_variable(tolua_S,"szName",tolua_get_NPC_DATA_szName,tolua_set_NPC_DATA_szName);
  tolua_variable(tolua_S,"nLevel",tolua_get_NPC_DATA_nLevel,tolua_set_NPC_DATA_nLevel);
  tolua_variable(tolua_S,"nPatternID",tolua_get_NPC_DATA_nPatternID,tolua_set_NPC_DATA_nPatternID);
  tolua_variable(tolua_S,"nQuality",tolua_get_NPC_DATA_nQuality,tolua_set_NPC_DATA_nQuality);
  tolua_variable(tolua_S,"nBroadcast",tolua_get_NPC_DATA_nBroadcast,tolua_set_NPC_DATA_nBroadcast);
  tolua_variable(tolua_S,"nForceID",tolua_get_NPC_DATA_nForceID,tolua_set_NPC_DATA_nForceID);
  tolua_variable(tolua_S,"bReduceReputation",tolua_get_NPC_DATA_bReduceReputation,tolua_set_NPC_DATA_bReduceReputation);
  tolua_variable(tolua_S,"nSpecies",tolua_get_NPC_DATA_nSpecies,tolua_set_NPC_DATA_nSpecies);
  tolua_variable(tolua_S,"nRivalForceID",tolua_get_NPC_DATA_nRivalForceID,tolua_set_NPC_DATA_nRivalForceID);
  tolua_variable(tolua_S,"nGroupID",tolua_get_NPC_DATA_nGroupID,tolua_set_NPC_DATA_nGroupID);
  tolua_variable(tolua_S,"nBodyType",tolua_get_NPC_DATA_nBodyType,tolua_set_NPC_DATA_nBodyType);
  tolua_variable(tolua_S,"nSpellEffectGroup",tolua_get_NPC_DATA_nSpellEffectGroup,tolua_set_NPC_DATA_nSpellEffectGroup);
  tolua_variable(tolua_S,"nSpawnTime",tolua_get_NPC_DATA_nSpawnTime,tolua_set_NPC_DATA_nSpawnTime);
  tolua_variable(tolua_S,"nReviveTime",tolua_get_NPC_DATA_nReviveTime,tolua_set_NPC_DATA_nReviveTime);
  tolua_variable(tolua_S,"nCorpseTime",tolua_get_NPC_DATA_nCorpseTime,tolua_set_NPC_DATA_nCorpseTime);
  tolua_variable(tolua_S,"nMinRespawnTime",tolua_get_NPC_DATA_nMinRespawnTime,tolua_set_NPC_DATA_nMinRespawnTime);
  tolua_variable(tolua_S,"nMaxRespawnTime",tolua_get_NPC_DATA_nMaxRespawnTime,tolua_set_NPC_DATA_nMaxRespawnTime);
  tolua_variable(tolua_S,"nAIID",tolua_get_NPC_DATA_nAIID,tolua_set_NPC_DATA_nAIID);
  tolua_variable(tolua_S,"bImmunePassiveMove",tolua_get_NPC_DATA_bImmunePassiveMove,tolua_set_NPC_DATA_bImmunePassiveMove);
  tolua_variable(tolua_S,"bInvincible",tolua_get_NPC_DATA_bInvincible,tolua_set_NPC_DATA_bInvincible);
  tolua_variable(tolua_S,"bAlwaysRun",tolua_get_NPC_DATA_bAlwaysRun,tolua_set_NPC_DATA_bAlwaysRun);
  tolua_variable(tolua_S,"bCanbeThrown",tolua_get_NPC_DATA_bCanbeThrown,tolua_set_NPC_DATA_bCanbeThrown);
  tolua_variable(tolua_S,"bIgnoreInvisible",tolua_get_NPC_DATA_bIgnoreInvisible,tolua_set_NPC_DATA_bIgnoreInvisible);
  tolua_variable(tolua_S,"bCounterInvisible",tolua_get_NPC_DATA_bCounterInvisible,tolua_set_NPC_DATA_bCounterInvisible);
  tolua_variable(tolua_S,"nAttackRange",tolua_get_NPC_DATA_nAttackRange,tolua_set_NPC_DATA_nAttackRange);
  tolua_variable(tolua_S,"bExclusive",tolua_get_NPC_DATA_bExclusive,tolua_set_NPC_DATA_bExclusive);
  tolua_variable(tolua_S,"bNeverBeHit",tolua_get_NPC_DATA_bNeverBeHit,tolua_set_NPC_DATA_bNeverBeHit);
  tolua_variable(tolua_S,"bProfit",tolua_get_NPC_DATA_bProfit,tolua_set_NPC_DATA_bProfit);
  tolua_variable(tolua_S,"nExpRate",tolua_get_NPC_DATA_nExpRate,tolua_set_NPC_DATA_nExpRate);
  tolua_variable(tolua_S,"nSoulRate",tolua_get_NPC_DATA_nSoulRate,tolua_set_NPC_DATA_nSoulRate);
  tolua_variable(tolua_S,"bDailyExp",tolua_get_NPC_DATA_bDailyExp,tolua_set_NPC_DATA_bDailyExp);
  tolua_variable(tolua_S,"bAuraInvalid",tolua_get_NPC_DATA_bAuraInvalid,tolua_set_NPC_DATA_bAuraInvalid);
  tolua_variable(tolua_S,"nKillPlayerVarIndex",tolua_get_NPC_DATA_nKillPlayerVarIndex,tolua_set_NPC_DATA_nKillPlayerVarIndex);
  tolua_variable(tolua_S,"nBeKilledVarIndex",tolua_get_NPC_DATA_nBeKilledVarIndex,tolua_set_NPC_DATA_nBeKilledVarIndex);
  tolua_variable(tolua_S,"nShopID",tolua_get_NPC_DATA_nShopID,tolua_set_NPC_DATA_nShopID);
  tolua_variable(tolua_S,"nBlackMarketID",tolua_get_NPC_DATA_nBlackMarketID,tolua_set_NPC_DATA_nBlackMarketID);
  tolua_variable(tolua_S,"bInteractBank",tolua_get_NPC_DATA_bInteractBank,tolua_set_NPC_DATA_bInteractBank);
  tolua_variable(tolua_S,"bInteractGuildBank",tolua_get_NPC_DATA_bInteractGuildBank,tolua_set_NPC_DATA_bInteractGuildBank);
  tolua_variable(tolua_S,"bInteractRewardQuest",tolua_get_NPC_DATA_bInteractRewardQuest,tolua_set_NPC_DATA_bInteractRewardQuest);
  tolua_variable(tolua_S,"bInteractCreateGuild",tolua_get_NPC_DATA_bInteractCreateGuild,tolua_set_NPC_DATA_bInteractCreateGuild);
  tolua_variable(tolua_S,"bInteractGuildSalary",tolua_get_NPC_DATA_bInteractGuildSalary,tolua_set_NPC_DATA_bInteractGuildSalary);
  tolua_variable(tolua_S,"bInteractAuction",tolua_get_NPC_DATA_bInteractAuction,tolua_set_NPC_DATA_bInteractAuction);
  tolua_variable(tolua_S,"bInteractRune",tolua_get_NPC_DATA_bInteractRune,tolua_set_NPC_DATA_bInteractRune);
  tolua_variable(tolua_S,"bInteractSoul",tolua_get_NPC_DATA_bInteractSoul,tolua_set_NPC_DATA_bInteractSoul);
  tolua_variable(tolua_S,"bInteractWeaponLevelUpPutIn",tolua_get_NPC_DATA_bInteractWeaponLevelUpPutIn,tolua_set_NPC_DATA_bInteractWeaponLevelUpPutIn);
  tolua_variable(tolua_S,"bInteractWeaponLevelUpTakeOut",tolua_get_NPC_DATA_bInteractWeaponLevelUpTakeOut,tolua_set_NPC_DATA_bInteractWeaponLevelUpTakeOut);
  tolua_variable(tolua_S,"bInteractSpecialRepair",tolua_get_NPC_DATA_bInteractSpecialRepair,tolua_set_NPC_DATA_bInteractSpecialRepair);
  tolua_variable(tolua_S,"bInteractGamble",tolua_get_NPC_DATA_bInteractGamble,tolua_set_NPC_DATA_bInteractGamble);
  tolua_variable(tolua_S,"bInteractExercise",tolua_get_NPC_DATA_bInteractExercise,tolua_set_NPC_DATA_bInteractExercise);
  tolua_variable(tolua_S,"bInteractSpellBookGamble",tolua_get_NPC_DATA_bInteractSpellBookGamble,tolua_set_NPC_DATA_bInteractSpellBookGamble);
  tolua_variable(tolua_S,"bInteractArenaReward",tolua_get_NPC_DATA_bInteractArenaReward,tolua_set_NPC_DATA_bInteractArenaReward);
  tolua_variable(tolua_S,"nCorpseDoodadID",tolua_get_NPC_DATA_nCorpseDoodadID,tolua_set_NPC_DATA_nCorpseDoodadID);
  tolua_variable(tolua_S,"bDieIDMonitor",tolua_get_NPC_DATA_bDieIDMonitor,tolua_set_NPC_DATA_bDieIDMonitor);
  tolua_variable(tolua_S,"bStatMoney",tolua_get_NPC_DATA_bStatMoney,tolua_set_NPC_DATA_bStatMoney);
  tolua_variable(tolua_S,"nBigDropInterval",tolua_get_NPC_DATA_nBigDropInterval,tolua_set_NPC_DATA_nBigDropInterval);
  tolua_variable(tolua_S,"nRuneGroup",tolua_get_NPC_DATA_nRuneGroup,tolua_set_NPC_DATA_nRuneGroup);
  tolua_variable(tolua_S,"nHandbookType",tolua_get_NPC_DATA_nHandbookType,tolua_set_NPC_DATA_nHandbookType);
  tolua_variable(tolua_S,"nHandbookIndex",tolua_get_NPC_DATA_nHandbookIndex,tolua_set_NPC_DATA_nHandbookIndex);
  tolua_variable(tolua_S,"nKillNpcQuestID",tolua_get_NPC_DATA_nKillNpcQuestID,tolua_set_NPC_DATA_nKillNpcQuestID);
  tolua_variable(tolua_S,"pAdventureData",tolua_get_NPC_DATA_pAdventureData_ptr,NULL);
  tolua_variable(tolua_S,"szScriptName",tolua_get_NPC_DATA_szScriptName,tolua_set_NPC_DATA_szScriptName);
#ifndef TOLUA_DISABLE_tolua_npc_def_NPC_DATA_ReadLine00
  tolua_function(tolua_S,"ReadLine",tolua_npc_def_NPC_DATA_ReadLine00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_npc_def (lua_State* tolua_S) {
 return tolua_npc_def_open(tolua_S);
};
#endif

