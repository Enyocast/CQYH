/*
** Lua binding: scene_def
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_scene_def_open (lua_State* tolua_S);

#include "../../../Common/define/scene_def.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ABSOLUTE_SCENE_POS");
 tolua_usertype(tolua_S,"ENTER_POS");
}

/* get function: nSceneTempID of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_get_ABSOLUTE_SCENE_POS_nSceneTempID
static int tolua_get_ABSOLUTE_SCENE_POS_nSceneTempID(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneTempID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneTempID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneTempID of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_set_ABSOLUTE_SCENE_POS_nSceneTempID
static int tolua_set_ABSOLUTE_SCENE_POS_nSceneTempID(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneTempID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSceneTempID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSceneID of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_get_ABSOLUTE_SCENE_POS_nSceneID
static int tolua_get_ABSOLUTE_SCENE_POS_nSceneID(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneID of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_set_ABSOLUTE_SCENE_POS_nSceneID
static int tolua_set_ABSOLUTE_SCENE_POS_nSceneID(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nX of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_get_ABSOLUTE_SCENE_POS_nX
static int tolua_get_ABSOLUTE_SCENE_POS_nX(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nX'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nX of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_set_ABSOLUTE_SCENE_POS_nX
static int tolua_set_ABSOLUTE_SCENE_POS_nX(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nX'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nX = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nY of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_get_ABSOLUTE_SCENE_POS_nY
static int tolua_get_ABSOLUTE_SCENE_POS_nY(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nY'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nY of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_set_ABSOLUTE_SCENE_POS_nY
static int tolua_set_ABSOLUTE_SCENE_POS_nY(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nY'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nY = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nZ of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_get_ABSOLUTE_SCENE_POS_nZ
static int tolua_get_ABSOLUTE_SCENE_POS_nZ(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nZ'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nZ);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nZ of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_set_ABSOLUTE_SCENE_POS_nZ
static int tolua_set_ABSOLUTE_SCENE_POS_nZ(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nZ'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nZ = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFaceDirection of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_get_ABSOLUTE_SCENE_POS_nFaceDirection
static int tolua_get_ABSOLUTE_SCENE_POS_nFaceDirection(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFaceDirection'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nFaceDirection);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFaceDirection of class  ABSOLUTE_SCENE_POS */
#ifndef TOLUA_DISABLE_tolua_set_ABSOLUTE_SCENE_POS_nFaceDirection
static int tolua_set_ABSOLUTE_SCENE_POS_nFaceDirection(lua_State* tolua_S)
{
  ABSOLUTE_SCENE_POS* self = (ABSOLUTE_SCENE_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFaceDirection'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFaceDirection = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSceneTempID of class  ENTER_POS */
#ifndef TOLUA_DISABLE_tolua_get_ENTER_POS_nSceneTempID
static int tolua_get_ENTER_POS_nSceneTempID(lua_State* tolua_S)
{
  ENTER_POS* self = (ENTER_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneTempID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneTempID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneTempID of class  ENTER_POS */
#ifndef TOLUA_DISABLE_tolua_set_ENTER_POS_nSceneTempID
static int tolua_set_ENTER_POS_nSceneTempID(lua_State* tolua_S)
{
  ENTER_POS* self = (ENTER_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneTempID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSceneTempID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSceneID of class  ENTER_POS */
#ifndef TOLUA_DISABLE_tolua_get_ENTER_POS_nSceneID
static int tolua_get_ENTER_POS_nSceneID(lua_State* tolua_S)
{
  ENTER_POS* self = (ENTER_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSceneID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSceneID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSceneID of class  ENTER_POS */
#ifndef TOLUA_DISABLE_tolua_set_ENTER_POS_nSceneID
static int tolua_set_ENTER_POS_nSceneID(lua_State* tolua_S)
{
  ENTER_POS* self = (ENTER_POS*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: bySide of class  ENTER_POS */
#ifndef TOLUA_DISABLE_tolua_get_ENTER_POS_unsigned_bySide
static int tolua_get_ENTER_POS_unsigned_bySide(lua_State* tolua_S)
{
  ENTER_POS* self = (ENTER_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bySide'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->bySide);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bySide of class  ENTER_POS */
#ifndef TOLUA_DISABLE_tolua_set_ENTER_POS_unsigned_bySide
static int tolua_set_ENTER_POS_unsigned_bySide(lua_State* tolua_S)
{
  ENTER_POS* self = (ENTER_POS*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bySide'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bySide = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: I64_2_Double */
#ifndef TOLUA_DISABLE_tolua_scene_def_I64_2_Double00
static int tolua_scene_def_I64_2_Double00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int llPos = (( signed int)  tolua_tonumber(tolua_S,1,0));
 {
  double tolua_ret = (double)  I64_2_Double(llPos);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'I64_2_Double'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ConvertCoordS2N */
#ifndef TOLUA_DISABLE_tolua_scene_def_ConvertCoordS2N00
static int tolua_scene_def_ConvertCoordS2N00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int llCoordination = (( signed int)  tolua_tonumber(tolua_S,1,0));
 {
  unsigned short tolua_ret = ( unsigned short)  ConvertCoordS2N(llCoordination);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ConvertCoordS2N'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ConvertCoordN2S */
#ifndef TOLUA_DISABLE_tolua_scene_def_ConvertCoordN2S00
static int tolua_scene_def_ConvertCoordN2S00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  unsigned short wCoordination = (( unsigned short)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  ConvertCoordN2S(wCoordination);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ConvertCoordN2S'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ConvertCoordO2N */
#ifndef TOLUA_DISABLE_tolua_scene_def_ConvertCoordO2N00
static int tolua_scene_def_ConvertCoordO2N00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int rnX = (( signed int)  tolua_tonumber(tolua_S,1,0));
  signed int rnY = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int rnZ = (( signed int)  tolua_tonumber(tolua_S,3,0));
 {
  ConvertCoordO2N(rnX,rnY,rnZ);
 tolua_pushnumber(tolua_S,(lua_Number)rnX);
 tolua_pushnumber(tolua_S,(lua_Number)rnY);
 tolua_pushnumber(tolua_S,(lua_Number)rnZ);
 }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ConvertCoordO2N'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ConvertCoordN2O */
#ifndef TOLUA_DISABLE_tolua_scene_def_ConvertCoordN2O00
static int tolua_scene_def_ConvertCoordN2O00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int rnX = (( signed int)  tolua_tonumber(tolua_S,1,0));
  signed int rnY = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int rnZ = (( signed int)  tolua_tonumber(tolua_S,3,0));
 {
  ConvertCoordN2O(rnX,rnY,rnZ);
 tolua_pushnumber(tolua_S,(lua_Number)rnX);
 tolua_pushnumber(tolua_S,(lua_Number)rnY);
 tolua_pushnumber(tolua_S,(lua_Number)rnZ);
 }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ConvertCoordN2O'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_scene_def_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"POINT_PER_CM",POINT_PER_CM);
 tolua_constant(tolua_S,"POINT_PER_METER",POINT_PER_METER);
 tolua_constant(tolua_S,"GAME_FPS",GAME_FPS);
 tolua_constant(tolua_S,"GRID_WIDTH",GRID_WIDTH);
 tolua_constant(tolua_S,"GRID_LAYER_HEIGHT",GRID_LAYER_HEIGHT);
 tolua_constant(tolua_S,"ZONE_WIDTH",ZONE_WIDTH);
 tolua_constant(tolua_S,"REGION_WIDTH",REGION_WIDTH);
 tolua_constant(tolua_S,"MAX_SCENE_WIDTH",MAX_SCENE_WIDTH);
 tolua_constant(tolua_S,"MAX_REGION_PER_SCENE",MAX_REGION_PER_SCENE);
 tolua_constant(tolua_S,"MAX_ZONE_PER_SCENE",MAX_ZONE_PER_SCENE);
 tolua_constant(tolua_S,"GRID_PER_ZONE",GRID_PER_ZONE);
 tolua_constant(tolua_S,"MAX_MOVE_SPEED",MAX_MOVE_SPEED);
 tolua_constant(tolua_S,"MAX_NPC_SPAWN_POINT_PER_SMALL_GROUP",MAX_NPC_SPAWN_POINT_PER_SMALL_GROUP);
 tolua_constant(tolua_S,"MAX_NPC_SMALL_GROUP_PER_MEDIUM_GROUP",MAX_NPC_SMALL_GROUP_PER_MEDIUM_GROUP);
 tolua_constant(tolua_S,"MAX_NPC_MEDIUM_GROUP_PER_LARGE_GROUP",MAX_NPC_MEDIUM_GROUP_PER_LARGE_GROUP);
 tolua_constant(tolua_S,"MAX_NPC_MEDIUM_GROUP_COUNT",MAX_NPC_MEDIUM_GROUP_COUNT);
 tolua_constant(tolua_S,"MAX_NPC_LARGE_GROUP_COUNT",MAX_NPC_LARGE_GROUP_COUNT);
 tolua_constant(tolua_S,"MAX_NPC_TEMPLATE_COUNT",MAX_NPC_TEMPLATE_COUNT);
 tolua_constant(tolua_S,"MAX_SINGLE_NPC_COUNT",MAX_SINGLE_NPC_COUNT);
 tolua_constant(tolua_S,"MAX_DOODAD_SPAWN_GROUP_COUNT",MAX_DOODAD_SPAWN_GROUP_COUNT);
 tolua_constant(tolua_S,"MAX_DOODAD_SPAWN_POINT_COUNT",MAX_DOODAD_SPAWN_POINT_COUNT);
 tolua_constant(tolua_S,"MAX_DOODAD_COUNT_PER_GROUP",MAX_DOODAD_COUNT_PER_GROUP);
 tolua_constant(tolua_S,"MAX_SCENE_ENTER_DISTANCE",MAX_SCENE_ENTER_DISTANCE);
 tolua_constant(tolua_S,"MAX_DOOR_ID",MAX_DOOR_ID);
 tolua_constant(tolua_S,"MAX_SCENE_TEMPLATE_COUNT",MAX_SCENE_TEMPLATE_COUNT);
 tolua_constant(tolua_S,"MAX_VOLUME_COUNT",MAX_VOLUME_COUNT);
 tolua_constant(tolua_S,"MAX_RANDOM_WEATHER_COUNT",MAX_RANDOM_WEATHER_COUNT);
 tolua_constant(tolua_S,"MAX_SYNC_CHAR_COUNT",MAX_SYNC_CHAR_COUNT);
 tolua_constant(tolua_S,"MAX_SYNC_DOODAD_COUNT",MAX_SYNC_DOODAD_COUNT);
 tolua_constant(tolua_S,"MAX_VELOCITY_Z",MAX_VELOCITY_Z);
 tolua_constant(tolua_S,"GLOBAL_GRAVITY",GLOBAL_GRAVITY);
 tolua_constant(tolua_S,"SCENE_READY_TIME",SCENE_READY_TIME);
 tolua_constant(tolua_S,"MAX_SIDE_COUNT",MAX_SIDE_COUNT);
 tolua_constant(tolua_S,"MAX_FACTION_COUNT",MAX_FACTION_COUNT);
 tolua_constant(tolua_S,"ROLE_HEIGHT",ROLE_HEIGHT);
 tolua_constant(tolua_S,"SYNC_BATTLE_MEMBER_TIME",SYNC_BATTLE_MEMBER_TIME);
 tolua_constant(tolua_S,"MAX_LINE_SCENE_NUMBER",MAX_LINE_SCENE_NUMBER);
 tolua_constant(tolua_S,"DAYTIME_HOURS",DAYTIME_HOURS);
 tolua_constant(tolua_S,"DL_RECORD_ROLET_INTERVAL",DL_RECORD_ROLET_INTERVAL);
 tolua_constant(tolua_S,"MAX_MINE_DROP_GROUP",MAX_MINE_DROP_GROUP);
 tolua_constant(tolua_S,"MAX_MINE_LEVEL",MAX_MINE_LEVEL);
  tolua_constant(tolua_S,"swtInvalid",swtInvalid);
  tolua_constant(tolua_S,"swtNormal",swtNormal);
  tolua_constant(tolua_S,"swtFog",swtFog);
  tolua_constant(tolua_S,"swtThunder",swtThunder);
  tolua_constant(tolua_S,"swtRain",swtRain);
  tolua_constant(tolua_S,"swtSnow",swtSnow);
  tolua_constant(tolua_S,"swtStorm",swtStorm);
  tolua_constant(tolua_S,"swtEclipse",swtEclipse);
  tolua_constant(tolua_S,"swtTotal",swtTotal);
  tolua_constant(tolua_S,"sdtInvalid",sdtInvalid);
  tolua_constant(tolua_S,"sdtDay",sdtDay);
  tolua_constant(tolua_S,"sdtNight",sdtNight);
  tolua_constant(tolua_S,"sdtTotal",sdtTotal);
  tolua_constant(tolua_S,"estInvalid",estInvalid);
  tolua_constant(tolua_S,"estStatic",estStatic);
  tolua_constant(tolua_S,"estDungeon",estDungeon);
  tolua_constant(tolua_S,"estBattleField",estBattleField);
  tolua_constant(tolua_S,"estArena",estArena);
  tolua_constant(tolua_S,"estLine",estLine);
  tolua_constant(tolua_S,"estBirth",estBirth);
  tolua_constant(tolua_S,"estGuild",estGuild);
  tolua_constant(tolua_S,"estGuildDungeon",estGuildDungeon);
  tolua_constant(tolua_S,"estUnique",estUnique);
  tolua_constant(tolua_S,"estSoloDungeon",estSoloDungeon);
  tolua_constant(tolua_S,"estTotal",estTotal);
  tolua_constant(tolua_S,"lssInvalid",lssInvalid);
  tolua_constant(tolua_S,"lssNormal",lssNormal);
  tolua_constant(tolua_S,"lssBusy",lssBusy);
  tolua_constant(tolua_S,"lssFull",lssFull);
  tolua_constant(tolua_S,"lssTotal",lssTotal);
  tolua_constant(tolua_S,"bodyInvalid",bodyInvalid);
  tolua_constant(tolua_S,"body0x0",body0x0);
  tolua_constant(tolua_S,"body1x1",body1x1);
  tolua_constant(tolua_S,"body3x3",body3x3);
  tolua_constant(tolua_S,"bodyTotal",bodyTotal);
 tolua_cclass(tolua_S,"ABSOLUTE_SCENE_POS","ABSOLUTE_SCENE_POS","",NULL);
 tolua_beginmodule(tolua_S,"ABSOLUTE_SCENE_POS");
  tolua_variable(tolua_S,"nSceneTempID",tolua_get_ABSOLUTE_SCENE_POS_nSceneTempID,tolua_set_ABSOLUTE_SCENE_POS_nSceneTempID);
  tolua_variable(tolua_S,"nSceneID",tolua_get_ABSOLUTE_SCENE_POS_nSceneID,tolua_set_ABSOLUTE_SCENE_POS_nSceneID);
  tolua_variable(tolua_S,"nX",tolua_get_ABSOLUTE_SCENE_POS_nX,tolua_set_ABSOLUTE_SCENE_POS_nX);
  tolua_variable(tolua_S,"nY",tolua_get_ABSOLUTE_SCENE_POS_nY,tolua_set_ABSOLUTE_SCENE_POS_nY);
  tolua_variable(tolua_S,"nZ",tolua_get_ABSOLUTE_SCENE_POS_nZ,tolua_set_ABSOLUTE_SCENE_POS_nZ);
  tolua_variable(tolua_S,"nFaceDirection",tolua_get_ABSOLUTE_SCENE_POS_nFaceDirection,tolua_set_ABSOLUTE_SCENE_POS_nFaceDirection);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"ENTER_POS","ENTER_POS","",NULL);
 tolua_beginmodule(tolua_S,"ENTER_POS");
  tolua_variable(tolua_S,"nSceneTempID",tolua_get_ENTER_POS_nSceneTempID,tolua_set_ENTER_POS_nSceneTempID);
  tolua_variable(tolua_S,"nSceneID",tolua_get_ENTER_POS_nSceneID,tolua_set_ENTER_POS_nSceneID);
  tolua_variable(tolua_S,"bySide",tolua_get_ENTER_POS_unsigned_bySide,tolua_set_ENTER_POS_unsigned_bySide);
 tolua_endmodule(tolua_S);
#ifndef TOLUA_DISABLE_tolua_scene_def_I64_2_Double00
 tolua_function(tolua_S,"I64_2_Double",tolua_scene_def_I64_2_Double00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_def_ConvertCoordS2N00
 tolua_function(tolua_S,"ConvertCoordS2N",tolua_scene_def_ConvertCoordS2N00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_def_ConvertCoordN2S00
 tolua_function(tolua_S,"ConvertCoordN2S",tolua_scene_def_ConvertCoordN2S00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_def_ConvertCoordO2N00
 tolua_function(tolua_S,"ConvertCoordO2N",tolua_scene_def_ConvertCoordO2N00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_def_ConvertCoordN2O00
 tolua_function(tolua_S,"ConvertCoordN2O",tolua_scene_def_ConvertCoordN2O00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_scene_def (lua_State* tolua_S) {
 return tolua_scene_def_open(tolua_S);
};
#endif

