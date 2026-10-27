/*
** Lua binding: scene
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_scene_open (lua_State* tolua_S);

#include "scene.h"
#include "math_ex.h"
#include "scene_file_mgr.h"
#include "../../../Common/define/scene_def.h"
#include "../../inc/gameworld/scene_file_mgr.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"NAMEID");
 tolua_usertype(tolua_S,"ADD_NPC_SPAWN_POINT");
 tolua_usertype(tolua_S,"ABSOLUTE_SCENE_POS");
 tolua_usertype(tolua_S,"CSceneFileMgr");
 tolua_usertype(tolua_S,"GRID_DATA");
 tolua_usertype(tolua_S,"CNpc");
 tolua_usertype(tolua_S,"CWeightRand");
 tolua_usertype(tolua_S,"NPC_SPAWN_POINT");
 tolua_usertype(tolua_S,"SCENE_TELEPORTS");
 tolua_usertype(tolua_S,"BTNod");
 tolua_usertype(tolua_S,"CSceneStaticData");
 tolua_usertype(tolua_S,"CDoodad");
 tolua_usertype(tolua_S,"CRole");
 tolua_usertype(tolua_S,"ENTER_POS");
 tolua_usertype(tolua_S,"CScene");
 tolua_usertype(tolua_S,"SCENE_DATA");
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
#ifndef TOLUA_DISABLE_tolua_scene_I64_2_Double00
static int tolua_scene_I64_2_Double00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_ConvertCoordS2N00
static int tolua_scene_ConvertCoordS2N00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_ConvertCoordN2S00
static int tolua_scene_ConvertCoordN2S00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_ConvertCoordO2N00
static int tolua_scene_ConvertCoordO2N00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_ConvertCoordN2O00
static int tolua_scene_ConvertCoordN2O00(lua_State* tolua_S)
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

/* get function: nID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nID
static int tolua_get_ADD_NPC_SPAWN_POINT_nID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nID
static int tolua_set_ADD_NPC_SPAWN_POINT_nID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nTemplateID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nTemplateID
static int tolua_get_ADD_NPC_SPAWN_POINT_nTemplateID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTemplateID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nTemplateID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nTemplateID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nTemplateID
static int tolua_set_ADD_NPC_SPAWN_POINT_nTemplateID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nX of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nX
static int tolua_get_ADD_NPC_SPAWN_POINT_nX(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nX'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nX of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nX
static int tolua_set_ADD_NPC_SPAWN_POINT_nX(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nY of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nY
static int tolua_get_ADD_NPC_SPAWN_POINT_nY(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nY'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nY of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nY
static int tolua_set_ADD_NPC_SPAWN_POINT_nY(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nZ of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nZ
static int tolua_get_ADD_NPC_SPAWN_POINT_nZ(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nZ'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nZ);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nZ of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nZ
static int tolua_set_ADD_NPC_SPAWN_POINT_nZ(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nDirection of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nDirection
static int tolua_get_ADD_NPC_SPAWN_POINT_nDirection(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDirection'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nDirection);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nDirection of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nDirection
static int tolua_set_ADD_NPC_SPAWN_POINT_nDirection(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDirection'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nDirection = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRange of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nRange
static int tolua_get_ADD_NPC_SPAWN_POINT_nRange(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRange of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nRange
static int tolua_set_ADD_NPC_SPAWN_POINT_nRange(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRange = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nLevelOffset of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nLevelOffset
static int tolua_get_ADD_NPC_SPAWN_POINT_nLevelOffset(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLevelOffset'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nLevelOffset);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLevelOffset of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nLevelOffset
static int tolua_set_ADD_NPC_SPAWN_POINT_nLevelOffset(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLevelOffset'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nLevelOffset = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nQuality of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nQuality
static int tolua_get_ADD_NPC_SPAWN_POINT_nQuality(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nQuality'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nQuality);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nQuality of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nQuality
static int tolua_set_ADD_NPC_SPAWN_POINT_nQuality(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nMinRespawnTime of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nMinRespawnTime
static int tolua_get_ADD_NPC_SPAWN_POINT_nMinRespawnTime(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMinRespawnTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMinRespawnTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMinRespawnTime of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nMinRespawnTime
static int tolua_set_ADD_NPC_SPAWN_POINT_nMinRespawnTime(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nMaxRespawnTime of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nMaxRespawnTime
static int tolua_get_ADD_NPC_SPAWN_POINT_nMaxRespawnTime(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMaxRespawnTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMaxRespawnTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMaxRespawnTime of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nMaxRespawnTime
static int tolua_set_ADD_NPC_SPAWN_POINT_nMaxRespawnTime(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nCurrentHp of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nCurrentHp
static int tolua_get_ADD_NPC_SPAWN_POINT_nCurrentHp(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentHp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCurrentHp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCurrentHp of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nCurrentHp
static int tolua_set_ADD_NPC_SPAWN_POINT_nCurrentHp(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentHp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nCurrentHp = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nCurrentMp of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nCurrentMp
static int tolua_get_ADD_NPC_SPAWN_POINT_nCurrentMp(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentMp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCurrentMp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCurrentMp of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nCurrentMp
static int tolua_set_ADD_NPC_SPAWN_POINT_nCurrentMp(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentMp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nCurrentMp = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bCanDropItem of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_bCanDropItem
static int tolua_get_ADD_NPC_SPAWN_POINT_bCanDropItem(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCanDropItem'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bCanDropItem);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bCanDropItem of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_bCanDropItem
static int tolua_set_ADD_NPC_SPAWN_POINT_bCanDropItem(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCanDropItem'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bCanDropItem = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAutoSpawn of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_bAutoSpawn
static int tolua_get_ADD_NPC_SPAWN_POINT_bAutoSpawn(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoSpawn'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bAutoSpawn);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAutoSpawn of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_bAutoSpawn
static int tolua_set_ADD_NPC_SPAWN_POINT_bAutoSpawn(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoSpawn'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAutoSpawn = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAutoRespawn of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_bAutoRespawn
static int tolua_get_ADD_NPC_SPAWN_POINT_bAutoRespawn(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoRespawn'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bAutoRespawn);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAutoRespawn of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_bAutoRespawn
static int tolua_set_ADD_NPC_SPAWN_POINT_bAutoRespawn(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoRespawn'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAutoRespawn = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSmallGroupID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nSmallGroupID
static int tolua_get_ADD_NPC_SPAWN_POINT_nSmallGroupID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSmallGroupID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSmallGroupID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSmallGroupID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nSmallGroupID
static int tolua_set_ADD_NPC_SPAWN_POINT_nSmallGroupID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSmallGroupID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSmallGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nMediumGroupID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nMediumGroupID
static int tolua_get_ADD_NPC_SPAWN_POINT_nMediumGroupID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMediumGroupID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMediumGroupID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMediumGroupID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nMediumGroupID
static int tolua_set_ADD_NPC_SPAWN_POINT_nMediumGroupID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMediumGroupID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nMediumGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nLargeGroupID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_ADD_NPC_SPAWN_POINT_nLargeGroupID
static int tolua_get_ADD_NPC_SPAWN_POINT_nLargeGroupID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLargeGroupID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nLargeGroupID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLargeGroupID of class  ADD_NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_ADD_NPC_SPAWN_POINT_nLargeGroupID
static int tolua_set_ADD_NPC_SPAWN_POINT_nLargeGroupID(lua_State* tolua_S)
{
  ADD_NPC_SPAWN_POINT* self = (ADD_NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLargeGroupID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nLargeGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nID
static int tolua_get_NPC_SPAWN_POINT_nID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nID
static int tolua_set_NPC_SPAWN_POINT_nID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: qwNameID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_qwNameID
static int tolua_get_NPC_SPAWN_POINT_qwNameID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'qwNameID'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->qwNameID,"NAMEID");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: qwNameID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_qwNameID
static int tolua_set_NPC_SPAWN_POINT_qwNameID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'qwNameID'",NULL);
 if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"NAMEID",0,&tolua_err)))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->qwNameID = *((NAMEID*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nX of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nX
static int tolua_get_NPC_SPAWN_POINT_nX(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nX'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nX of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nX
static int tolua_set_NPC_SPAWN_POINT_nX(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nY of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nY
static int tolua_get_NPC_SPAWN_POINT_nY(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nY'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nY of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nY
static int tolua_set_NPC_SPAWN_POINT_nY(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nZ of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nZ
static int tolua_get_NPC_SPAWN_POINT_nZ(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nZ'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nZ);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nZ of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nZ
static int tolua_set_NPC_SPAWN_POINT_nZ(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nDirection of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nDirection
static int tolua_get_NPC_SPAWN_POINT_nDirection(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDirection'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nDirection);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nDirection of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nDirection
static int tolua_set_NPC_SPAWN_POINT_nDirection(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nDirection'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nDirection = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nRange of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nRange
static int tolua_get_NPC_SPAWN_POINT_nRange(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nRange);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nRange of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nRange
static int tolua_set_NPC_SPAWN_POINT_nRange(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nRange = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RandNpc of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_RandNpc
static int tolua_get_NPC_SPAWN_POINT_RandNpc(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RandNpc'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->RandNpc,"CWeightRand");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RandNpc of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_RandNpc
static int tolua_set_NPC_SPAWN_POINT_RandNpc(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RandNpc'",NULL);
 if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CWeightRand",0,&tolua_err)))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RandNpc = *((CWeightRand*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nLevelOffset of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nLevelOffset
static int tolua_get_NPC_SPAWN_POINT_nLevelOffset(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLevelOffset'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nLevelOffset);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLevelOffset of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nLevelOffset
static int tolua_set_NPC_SPAWN_POINT_nLevelOffset(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLevelOffset'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nLevelOffset = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nAIID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nAIID
static int tolua_get_NPC_SPAWN_POINT_nAIID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nAIID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nAIID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nAIID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nAIID
static int tolua_set_NPC_SPAWN_POINT_nAIID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nQuality of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nQuality
static int tolua_get_NPC_SPAWN_POINT_nQuality(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nQuality'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nQuality);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nQuality of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nQuality
static int tolua_set_NPC_SPAWN_POINT_nQuality(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nMinRespawnTime of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nMinRespawnTime
static int tolua_get_NPC_SPAWN_POINT_nMinRespawnTime(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMinRespawnTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMinRespawnTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMinRespawnTime of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nMinRespawnTime
static int tolua_set_NPC_SPAWN_POINT_nMinRespawnTime(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nMaxRespawnTime of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nMaxRespawnTime
static int tolua_get_NPC_SPAWN_POINT_nMaxRespawnTime(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMaxRespawnTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMaxRespawnTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMaxRespawnTime of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nMaxRespawnTime
static int tolua_set_NPC_SPAWN_POINT_nMaxRespawnTime(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nSpawnTime of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nSpawnTime
static int tolua_get_NPC_SPAWN_POINT_nSpawnTime(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSpawnTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSpawnTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSpawnTime of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nSpawnTime
static int tolua_set_NPC_SPAWN_POINT_nSpawnTime(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nReviveTime of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nReviveTime
static int tolua_get_NPC_SPAWN_POINT_nReviveTime(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nReviveTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nReviveTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nReviveTime of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nReviveTime
static int tolua_set_NPC_SPAWN_POINT_nReviveTime(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nCurrentHp of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nCurrentHp
static int tolua_get_NPC_SPAWN_POINT_nCurrentHp(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentHp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCurrentHp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCurrentHp of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nCurrentHp
static int tolua_set_NPC_SPAWN_POINT_nCurrentHp(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentHp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nCurrentHp = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nCurrentMp of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nCurrentMp
static int tolua_get_NPC_SPAWN_POINT_nCurrentMp(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentMp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCurrentMp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCurrentMp of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nCurrentMp
static int tolua_set_NPC_SPAWN_POINT_nCurrentMp(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentMp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nCurrentMp = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bCanDropItem of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_bCanDropItem
static int tolua_get_NPC_SPAWN_POINT_bCanDropItem(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCanDropItem'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bCanDropItem);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bCanDropItem of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_bCanDropItem
static int tolua_set_NPC_SPAWN_POINT_bCanDropItem(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bCanDropItem'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bCanDropItem = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nPatrolPathID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nPatrolPathID
static int tolua_get_NPC_SPAWN_POINT_nPatrolPathID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPatrolPathID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nPatrolPathID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nPatrolPathID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nPatrolPathID
static int tolua_set_NPC_SPAWN_POINT_nPatrolPathID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPatrolPathID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nPatrolPathID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nPatrolStyle of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nPatrolStyle
static int tolua_get_NPC_SPAWN_POINT_nPatrolStyle(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPatrolStyle'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nPatrolStyle);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nPatrolStyle of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nPatrolStyle
static int tolua_set_NPC_SPAWN_POINT_nPatrolStyle(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nPatrolStyle'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nPatrolStyle = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFollowHostID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nFollowHostID
static int tolua_get_NPC_SPAWN_POINT_nFollowHostID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFollowHostID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nFollowHostID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFollowHostID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nFollowHostID
static int tolua_set_NPC_SPAWN_POINT_nFollowHostID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFollowHostID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFollowHostID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFollowOffsetX of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nFollowOffsetX
static int tolua_get_NPC_SPAWN_POINT_nFollowOffsetX(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFollowOffsetX'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nFollowOffsetX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFollowOffsetX of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nFollowOffsetX
static int tolua_set_NPC_SPAWN_POINT_nFollowOffsetX(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFollowOffsetX'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFollowOffsetX = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nFollowOffsetY of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nFollowOffsetY
static int tolua_get_NPC_SPAWN_POINT_nFollowOffsetY(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFollowOffsetY'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nFollowOffsetY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nFollowOffsetY of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nFollowOffsetY
static int tolua_set_NPC_SPAWN_POINT_nFollowOffsetY(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nFollowOffsetY'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nFollowOffsetY = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAutoSpawn of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_bAutoSpawn
static int tolua_get_NPC_SPAWN_POINT_bAutoSpawn(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoSpawn'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bAutoSpawn);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAutoSpawn of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_bAutoSpawn
static int tolua_set_NPC_SPAWN_POINT_bAutoSpawn(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoSpawn'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAutoSpawn = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bAutoRespawn of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_bAutoRespawn
static int tolua_get_NPC_SPAWN_POINT_bAutoRespawn(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoRespawn'",NULL);
#endif
 tolua_pushboolean(tolua_S,(int)self->bAutoRespawn);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bAutoRespawn of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_bAutoRespawn
static int tolua_set_NPC_SPAWN_POINT_bAutoRespawn(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bAutoRespawn'",NULL);
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bAutoRespawn = ((BOOL)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nSmallGroupID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nSmallGroupID
static int tolua_get_NPC_SPAWN_POINT_nSmallGroupID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSmallGroupID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nSmallGroupID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nSmallGroupID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nSmallGroupID
static int tolua_set_NPC_SPAWN_POINT_nSmallGroupID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nSmallGroupID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nSmallGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nMediumGroupID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nMediumGroupID
static int tolua_get_NPC_SPAWN_POINT_nMediumGroupID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMediumGroupID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMediumGroupID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMediumGroupID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nMediumGroupID
static int tolua_set_NPC_SPAWN_POINT_nMediumGroupID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMediumGroupID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nMediumGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nLargeGroupID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_nLargeGroupID
static int tolua_get_NPC_SPAWN_POINT_nLargeGroupID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLargeGroupID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nLargeGroupID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLargeGroupID of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_nLargeGroupID
static int tolua_set_NPC_SPAWN_POINT_nLargeGroupID(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLargeGroupID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nLargeGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pDeadBTRoot of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_get_NPC_SPAWN_POINT_pDeadBTRoot_ptr
static int tolua_get_NPC_SPAWN_POINT_pDeadBTRoot_ptr(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pDeadBTRoot'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->pDeadBTRoot,"BTNod");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pDeadBTRoot of class  NPC_SPAWN_POINT */
#ifndef TOLUA_DISABLE_tolua_set_NPC_SPAWN_POINT_pDeadBTRoot_ptr
static int tolua_set_NPC_SPAWN_POINT_pDeadBTRoot_ptr(lua_State* tolua_S)
{
  NPC_SPAWN_POINT* self = (NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pDeadBTRoot'",NULL);
 if (!tolua_isusertype(tolua_S,2,"BTNod",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pDeadBTRoot = ((BTNod*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddRole of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_AddRole00
static int tolua_scene_CScene_AddRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  CRole* opRole = ((CRole*)  tolua_tousertype(tolua_S,2,0));
  signed int nAppearType = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddRole'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddRole(opRole,nAppearType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveRole of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_RemoveRole00
static int tolua_scene_CScene_RemoveRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CRole",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  CRole* poRole = ((CRole*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveRole'", NULL);
#endif
 {
 int tolua_ret = (int)
self->RemoveRole(poRole);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddNpc of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_AddNpc00
static int tolua_scene_CScene_AddNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CNpc",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  CNpc* poNpc = ((CNpc*)  tolua_tousertype(tolua_S,2,0));
  signed int nAppearType = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddNpc'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddNpc(poNpc,nAppearType);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveNpc of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_RemoveNpc00
static int tolua_scene_CScene_RemoveNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CNpc",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  CNpc* poNpc = ((CNpc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveNpc'", NULL);
#endif
 {
 int tolua_ret = (int)
self->RemoveNpc(poNpc);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddDoodad of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_AddDoodad00
static int tolua_scene_CScene_AddDoodad00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CDoodad",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  CDoodad* poDoodad = ((CDoodad*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddDoodad'", NULL);
#endif
 {
 int tolua_ret = (int)
self->AddDoodad(poDoodad);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddDoodad'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveDoodad of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_RemoveDoodad00
static int tolua_scene_CScene_RemoveDoodad00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"CDoodad",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  CDoodad* poDoodad = ((CDoodad*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveDoodad'", NULL);
#endif
 {
 int tolua_ret = (int)
self->RemoveDoodad(poDoodad);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveDoodad'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SpawnNpc of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SpawnNpc00
static int tolua_scene_CScene_SpawnNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,8,"const NPC_SPAWN_POINT",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llX = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int llY = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int llZ = (( signed int)  tolua_tonumber(tolua_S,5,0));
  signed int nFaceDirection = (( signed int)  tolua_tonumber(tolua_S,6,0));
  signed int nSpawnerCharID = (( signed int)  tolua_tonumber(tolua_S,7,0));
  const NPC_SPAWN_POINT* pcSpawnPoint = ((const NPC_SPAWN_POINT*)  tolua_tousertype(tolua_S,8,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SpawnNpc'", NULL);
#endif
 {
  CNpc* tolua_ret = (CNpc*)  self->SpawnNpc(nTemplateID,llX,llY,llZ,nFaceDirection,nSpawnerCharID,pcSpawnPoint);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CNpc");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SpawnNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SpawnSingleNpc of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SpawnSingleNpc00
static int tolua_scene_CScene_SpawnSingleNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nSingleNpcID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SpawnSingleNpc'", NULL);
#endif
 {
  CNpc* tolua_ret = (CNpc*)  self->SpawnSingleNpc(nSingleNpcID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CNpc");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SpawnSingleNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SpawnNpcMediumGroup of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SpawnNpcMediumGroup00
static int tolua_scene_CScene_SpawnNpcMediumGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nMediumGroupID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SpawnNpcMediumGroup'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SpawnNpcMediumGroup(nMediumGroupID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SpawnNpcMediumGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindNpc of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_FindNpc00
static int tolua_scene_CScene_FindNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nSingleNpcID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindNpc'", NULL);
#endif
 {
  CNpc* tolua_ret = (CNpc*)  self->FindNpc(nSingleNpcID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CNpc");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SpawnDoodad of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SpawnDoodad00
static int tolua_scene_CScene_SpawnDoodad00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nTemplateID = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llX = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int llY = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int llZ = (( signed int)  tolua_tonumber(tolua_S,5,0));
  signed int nFaceDirection = (( signed int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SpawnDoodad'", NULL);
#endif
 {
  CDoodad* tolua_ret = (CDoodad*)  self->SpawnDoodad(nTemplateID,llX,llY,llZ,nFaceDirection);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDoodad");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SpawnDoodad'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSceneTempID of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetSceneTempID00
static int tolua_scene_CScene_GetSceneTempID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSceneTempID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSceneTempID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSceneTempID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSceneID of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetSceneID00
static int tolua_scene_CScene_GetSceneID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSceneID'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSceneID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSceneID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSceneData of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetSceneData00
static int tolua_scene_CScene_GetSceneData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSceneData'", NULL);
#endif
 {
  const SCENE_DATA* tolua_ret = (const SCENE_DATA*)  self->GetSceneData();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const SCENE_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSceneData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStaticData of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetStaticData00
static int tolua_scene_CScene_GetStaticData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStaticData'", NULL);
#endif
 {
  CSceneStaticData* tolua_ret = (CSceneStaticData*)  self->GetStaticData();
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSceneStaticData");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStaticData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLowerZ of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetLowerZ00
static int tolua_scene_CScene_GetLowerZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nX = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nY = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int nZ = (( signed int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLowerZ'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetLowerZ(nX,nY,nZ);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLowerZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDoorState of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SetDoorState00
static int tolua_scene_CScene_SetDoorState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nDoorID = (( signed int)  tolua_tonumber(tolua_S,2,0));
   bool bClosed = ((  bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoorState'", NULL);
#endif
 {
  self->SetDoorState(nDoorID,bClosed);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoorState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDoorClosed of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_IsDoorClosed00
static int tolua_scene_CScene_IsDoorClosed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nDoorID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDoorClosed'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsDoorClosed(nDoorID);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDoorClosed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SetVariable00
static int tolua_scene_CScene_SetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nValue = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVariable'", NULL);
#endif
 {
  self->SetVariable(nIndex,nValue);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetVariable00
static int tolua_scene_CScene_GetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nIndex = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVariable'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetVariable(nIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetServerGroup of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetServerGroup00
static int tolua_scene_CScene_GetServerGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetServerGroup'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetServerGroup();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetServerGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoleCount of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetRoleCount00
static int tolua_scene_CScene_GetRoleCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoleCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetRoleCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoleCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNpcCount of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetNpcCount00
static int tolua_scene_CScene_GetNpcCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNpcCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetNpcCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNpcCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWeather of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetWeather00
static int tolua_scene_CScene_GetWeather00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWeather'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetWeather();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWeather'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWeather of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SetWeather00
static int tolua_scene_CScene_SetWeather00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  signed int nWeather = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int nDurationFrame = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWeather'", NULL);
#endif
 {
 int tolua_ret = (int)
self->SetWeather(nWeather,nDurationFrame);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWeather'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSabacStarted of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_IsSabacStarted00
static int tolua_scene_CScene_IsSabacStarted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSabacStarted'", NULL);
#endif
 {
 int tolua_ret = (int)
self->IsSabacStarted();
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSabacStarted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Say of class  CScene */
#ifndef TOLUA_DISABLE_tolua_scene_CScene_Say00
static int tolua_scene_CScene_Say00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CScene",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isstring(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CScene* self = (CScene*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwTargetID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dwLocation = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  const char* pcszMessage = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Say'", NULL);
#endif
 {
 int tolua_ret = (int)
self->Say(dwTargetID,dwLocation,pcszMessage);
 tolua_pushboolean(tolua_S,(int)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Say'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindTeleportPoint of class  CSceneStaticData */
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_FindTeleportPoint00
static int tolua_scene_CSceneStaticData_FindTeleportPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneStaticData",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneStaticData* self = (CSceneStaticData*)  tolua_tousertype(tolua_S,1,0);
  signed int nPointID = (( signed int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindTeleportPoint'", NULL);
#endif
 {
  const SCENE_TELEPORTS* tolua_ret = (const SCENE_TELEPORTS*)  self->FindTeleportPoint(nPointID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const SCENE_TELEPORTS");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindTeleportPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSingleNpcCount of class  CSceneStaticData */
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetSingleNpcCount00
static int tolua_scene_CSceneStaticData_GetSingleNpcCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneStaticData",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneStaticData* self = (CSceneStaticData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSingleNpcCount'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetSingleNpcCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSingleNpcCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSingleNpc of class  CSceneStaticData */
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetSingleNpc00
static int tolua_scene_CSceneStaticData_GetSingleNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneStaticData",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneStaticData* self = (CSceneStaticData*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSingleNpc'", NULL);
#endif
 {
  const NPC_SPAWN_POINT* tolua_ret = (const NPC_SPAWN_POINT*)  self->GetSingleNpc(pcszName);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const NPC_SPAWN_POINT");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSingleNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSingleNpcByName of class  CSceneStaticData */
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetSingleNpcByName00
static int tolua_scene_CSceneStaticData_GetSingleNpcByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneStaticData",0,&tolua_err) ||
 (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"NAMEID",0,&tolua_err)) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneStaticData* self = (CSceneStaticData*)  tolua_tousertype(tolua_S,1,0);
  NAMEID qwNameID = *((NAMEID*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSingleNpcByName'", NULL);
#endif
 {
  const NPC_SPAWN_POINT* tolua_ret = (const NPC_SPAWN_POINT*)  self->GetSingleNpcByName(qwNameID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const NPC_SPAWN_POINT");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSingleNpcByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxZoneX of class  CSceneStaticData */
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetMaxZoneX00
static int tolua_scene_CSceneStaticData_GetMaxZoneX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneStaticData",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneStaticData* self = (CSceneStaticData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxZoneX'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMaxZoneX();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxZoneX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxZoneY of class  CSceneStaticData */
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetMaxZoneY00
static int tolua_scene_CSceneStaticData_GetMaxZoneY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneStaticData",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneStaticData* self = (CSceneStaticData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxZoneY'", NULL);
#endif
 {
  signed int tolua_ret = ( signed int)  self->GetMaxZoneY();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxZoneY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGroundGrid of class  CSceneStaticData */
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetGroundGrid00
static int tolua_scene_CSceneStaticData_GetGroundGrid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneStaticData",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneStaticData* self = (CSceneStaticData*)  tolua_tousertype(tolua_S,1,0);
  signed int llX = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llY = (( signed int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGroundGrid'", NULL);
#endif
 {
  const GRID_DATA* tolua_ret = (const GRID_DATA*)  self->GetGroundGrid(llX,llY);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"const GRID_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGroundGrid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  CSceneFileMgr */
#ifndef TOLUA_DISABLE_tolua_scene_CSceneFileMgr_GetInstance00
static int tolua_scene_CSceneFileMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CSceneFileMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CSceneFileMgr& tolua_ret = (CSceneFileMgr&)  CSceneFileMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CSceneFileMgr");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStaticData of class  CSceneFileMgr */
#ifndef TOLUA_DISABLE_tolua_scene_CSceneFileMgr_GetStaticData00
static int tolua_scene_CSceneFileMgr_GetStaticData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CSceneFileMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CSceneFileMgr* self = (CSceneFileMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwSceneTempID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStaticData'", NULL);
#endif
 {
  CSceneStaticData* tolua_ret = (CSceneStaticData*)  self->GetStaticData(dwSceneTempID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSceneStaticData");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStaticData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: g_Sin */
#ifndef TOLUA_DISABLE_tolua_scene_g_Sin00
static int tolua_scene_g_Sin00(lua_State* tolua_S)
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
  signed int nDirection = (( signed int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  g_Sin(nDirection);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'g_Sin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: g_Cos */
#ifndef TOLUA_DISABLE_tolua_scene_g_Cos00
static int tolua_scene_g_Cos00(lua_State* tolua_S)
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
  signed int nDirection = (( signed int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  g_Cos(nDirection);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'g_Cos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NormalizeDirection */
#ifndef TOLUA_DISABLE_tolua_scene_NormalizeDirection00
static int tolua_scene_NormalizeDirection00(lua_State* tolua_S)
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
  signed int nDirection = (( signed int)  tolua_tonumber(tolua_S,1,0));
 {
  signed int tolua_ret = ( signed int)  NormalizeDirection(nDirection);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NormalizeDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: g_GetDistance2D */
#ifndef TOLUA_DISABLE_tolua_scene_g_GetDistance2D00
static int tolua_scene_g_GetDistance2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int llSrcX = (( signed int)  tolua_tonumber(tolua_S,1,0));
  signed int llSrcY = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llDestX = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int llDestY = (( signed int)  tolua_tonumber(tolua_S,4,0));
 {
  signed int tolua_ret = ( signed int)  g_GetDistance2D(llSrcX,llSrcY,llDestX,llDestY);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'g_GetDistance2D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: g_GetDistance3D */
#ifndef TOLUA_DISABLE_tolua_scene_g_GetDistance3D00
static int tolua_scene_g_GetDistance3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  signed int llSrcX = (( signed int)  tolua_tonumber(tolua_S,1,0));
  signed int llSrcY = (( signed int)  tolua_tonumber(tolua_S,2,0));
  signed int llSrcZ = (( signed int)  tolua_tonumber(tolua_S,3,0));
  signed int llDestX = (( signed int)  tolua_tonumber(tolua_S,4,0));
  signed int llDestY = (( signed int)  tolua_tonumber(tolua_S,5,0));
  signed int llDestZ = (( signed int)  tolua_tonumber(tolua_S,6,0));
 {
  signed int tolua_ret = ( signed int)  g_GetDistance3D(llSrcX,llSrcY,llSrcZ,llDestX,llDestY,llDestZ);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'g_GetDistance3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_scene_open (lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_scene_I64_2_Double00
 tolua_function(tolua_S,"I64_2_Double",tolua_scene_I64_2_Double00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_ConvertCoordS2N00
 tolua_function(tolua_S,"ConvertCoordS2N",tolua_scene_ConvertCoordS2N00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_ConvertCoordN2S00
 tolua_function(tolua_S,"ConvertCoordN2S",tolua_scene_ConvertCoordN2S00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_ConvertCoordO2N00
 tolua_function(tolua_S,"ConvertCoordO2N",tolua_scene_ConvertCoordO2N00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_ConvertCoordN2O00
 tolua_function(tolua_S,"ConvertCoordN2O",tolua_scene_ConvertCoordN2O00);
#endif //#ifndef TOLUA_DISABLE
 tolua_cclass(tolua_S,"ADD_NPC_SPAWN_POINT","ADD_NPC_SPAWN_POINT","",NULL);
 tolua_beginmodule(tolua_S,"ADD_NPC_SPAWN_POINT");
  tolua_variable(tolua_S,"nID",tolua_get_ADD_NPC_SPAWN_POINT_nID,tolua_set_ADD_NPC_SPAWN_POINT_nID);
  tolua_variable(tolua_S,"nTemplateID",tolua_get_ADD_NPC_SPAWN_POINT_nTemplateID,tolua_set_ADD_NPC_SPAWN_POINT_nTemplateID);
  tolua_variable(tolua_S,"nX",tolua_get_ADD_NPC_SPAWN_POINT_nX,tolua_set_ADD_NPC_SPAWN_POINT_nX);
  tolua_variable(tolua_S,"nY",tolua_get_ADD_NPC_SPAWN_POINT_nY,tolua_set_ADD_NPC_SPAWN_POINT_nY);
  tolua_variable(tolua_S,"nZ",tolua_get_ADD_NPC_SPAWN_POINT_nZ,tolua_set_ADD_NPC_SPAWN_POINT_nZ);
  tolua_variable(tolua_S,"nDirection",tolua_get_ADD_NPC_SPAWN_POINT_nDirection,tolua_set_ADD_NPC_SPAWN_POINT_nDirection);
  tolua_variable(tolua_S,"nRange",tolua_get_ADD_NPC_SPAWN_POINT_nRange,tolua_set_ADD_NPC_SPAWN_POINT_nRange);
  tolua_variable(tolua_S,"nLevelOffset",tolua_get_ADD_NPC_SPAWN_POINT_nLevelOffset,tolua_set_ADD_NPC_SPAWN_POINT_nLevelOffset);
  tolua_variable(tolua_S,"nQuality",tolua_get_ADD_NPC_SPAWN_POINT_nQuality,tolua_set_ADD_NPC_SPAWN_POINT_nQuality);
  tolua_variable(tolua_S,"nMinRespawnTime",tolua_get_ADD_NPC_SPAWN_POINT_nMinRespawnTime,tolua_set_ADD_NPC_SPAWN_POINT_nMinRespawnTime);
  tolua_variable(tolua_S,"nMaxRespawnTime",tolua_get_ADD_NPC_SPAWN_POINT_nMaxRespawnTime,tolua_set_ADD_NPC_SPAWN_POINT_nMaxRespawnTime);
  tolua_variable(tolua_S,"nCurrentHp",tolua_get_ADD_NPC_SPAWN_POINT_nCurrentHp,tolua_set_ADD_NPC_SPAWN_POINT_nCurrentHp);
  tolua_variable(tolua_S,"nCurrentMp",tolua_get_ADD_NPC_SPAWN_POINT_nCurrentMp,tolua_set_ADD_NPC_SPAWN_POINT_nCurrentMp);
  tolua_variable(tolua_S,"bCanDropItem",tolua_get_ADD_NPC_SPAWN_POINT_bCanDropItem,tolua_set_ADD_NPC_SPAWN_POINT_bCanDropItem);
  tolua_variable(tolua_S,"bAutoSpawn",tolua_get_ADD_NPC_SPAWN_POINT_bAutoSpawn,tolua_set_ADD_NPC_SPAWN_POINT_bAutoSpawn);
  tolua_variable(tolua_S,"bAutoRespawn",tolua_get_ADD_NPC_SPAWN_POINT_bAutoRespawn,tolua_set_ADD_NPC_SPAWN_POINT_bAutoRespawn);
  tolua_variable(tolua_S,"nSmallGroupID",tolua_get_ADD_NPC_SPAWN_POINT_nSmallGroupID,tolua_set_ADD_NPC_SPAWN_POINT_nSmallGroupID);
  tolua_variable(tolua_S,"nMediumGroupID",tolua_get_ADD_NPC_SPAWN_POINT_nMediumGroupID,tolua_set_ADD_NPC_SPAWN_POINT_nMediumGroupID);
  tolua_variable(tolua_S,"nLargeGroupID",tolua_get_ADD_NPC_SPAWN_POINT_nLargeGroupID,tolua_set_ADD_NPC_SPAWN_POINT_nLargeGroupID);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"NPC_SPAWN_POINT","NPC_SPAWN_POINT","",NULL);
 tolua_beginmodule(tolua_S,"NPC_SPAWN_POINT");
  tolua_variable(tolua_S,"nID",tolua_get_NPC_SPAWN_POINT_nID,tolua_set_NPC_SPAWN_POINT_nID);
  tolua_variable(tolua_S,"qwNameID",tolua_get_NPC_SPAWN_POINT_qwNameID,tolua_set_NPC_SPAWN_POINT_qwNameID);
  tolua_variable(tolua_S,"nX",tolua_get_NPC_SPAWN_POINT_nX,tolua_set_NPC_SPAWN_POINT_nX);
  tolua_variable(tolua_S,"nY",tolua_get_NPC_SPAWN_POINT_nY,tolua_set_NPC_SPAWN_POINT_nY);
  tolua_variable(tolua_S,"nZ",tolua_get_NPC_SPAWN_POINT_nZ,tolua_set_NPC_SPAWN_POINT_nZ);
  tolua_variable(tolua_S,"nDirection",tolua_get_NPC_SPAWN_POINT_nDirection,tolua_set_NPC_SPAWN_POINT_nDirection);
  tolua_variable(tolua_S,"nRange",tolua_get_NPC_SPAWN_POINT_nRange,tolua_set_NPC_SPAWN_POINT_nRange);
  tolua_variable(tolua_S,"RandNpc",tolua_get_NPC_SPAWN_POINT_RandNpc,tolua_set_NPC_SPAWN_POINT_RandNpc);
  tolua_variable(tolua_S,"nLevelOffset",tolua_get_NPC_SPAWN_POINT_nLevelOffset,tolua_set_NPC_SPAWN_POINT_nLevelOffset);
  tolua_variable(tolua_S,"nAIID",tolua_get_NPC_SPAWN_POINT_nAIID,tolua_set_NPC_SPAWN_POINT_nAIID);
  tolua_variable(tolua_S,"nQuality",tolua_get_NPC_SPAWN_POINT_nQuality,tolua_set_NPC_SPAWN_POINT_nQuality);
  tolua_variable(tolua_S,"nMinRespawnTime",tolua_get_NPC_SPAWN_POINT_nMinRespawnTime,tolua_set_NPC_SPAWN_POINT_nMinRespawnTime);
  tolua_variable(tolua_S,"nMaxRespawnTime",tolua_get_NPC_SPAWN_POINT_nMaxRespawnTime,tolua_set_NPC_SPAWN_POINT_nMaxRespawnTime);
  tolua_variable(tolua_S,"nSpawnTime",tolua_get_NPC_SPAWN_POINT_nSpawnTime,tolua_set_NPC_SPAWN_POINT_nSpawnTime);
  tolua_variable(tolua_S,"nReviveTime",tolua_get_NPC_SPAWN_POINT_nReviveTime,tolua_set_NPC_SPAWN_POINT_nReviveTime);
  tolua_variable(tolua_S,"nCurrentHp",tolua_get_NPC_SPAWN_POINT_nCurrentHp,tolua_set_NPC_SPAWN_POINT_nCurrentHp);
  tolua_variable(tolua_S,"nCurrentMp",tolua_get_NPC_SPAWN_POINT_nCurrentMp,tolua_set_NPC_SPAWN_POINT_nCurrentMp);
  tolua_variable(tolua_S,"bCanDropItem",tolua_get_NPC_SPAWN_POINT_bCanDropItem,tolua_set_NPC_SPAWN_POINT_bCanDropItem);
  tolua_variable(tolua_S,"nPatrolPathID",tolua_get_NPC_SPAWN_POINT_nPatrolPathID,tolua_set_NPC_SPAWN_POINT_nPatrolPathID);
  tolua_variable(tolua_S,"nPatrolStyle",tolua_get_NPC_SPAWN_POINT_nPatrolStyle,tolua_set_NPC_SPAWN_POINT_nPatrolStyle);
  tolua_variable(tolua_S,"nFollowHostID",tolua_get_NPC_SPAWN_POINT_nFollowHostID,tolua_set_NPC_SPAWN_POINT_nFollowHostID);
  tolua_variable(tolua_S,"nFollowOffsetX",tolua_get_NPC_SPAWN_POINT_nFollowOffsetX,tolua_set_NPC_SPAWN_POINT_nFollowOffsetX);
  tolua_variable(tolua_S,"nFollowOffsetY",tolua_get_NPC_SPAWN_POINT_nFollowOffsetY,tolua_set_NPC_SPAWN_POINT_nFollowOffsetY);
  tolua_variable(tolua_S,"bAutoSpawn",tolua_get_NPC_SPAWN_POINT_bAutoSpawn,tolua_set_NPC_SPAWN_POINT_bAutoSpawn);
  tolua_variable(tolua_S,"bAutoRespawn",tolua_get_NPC_SPAWN_POINT_bAutoRespawn,tolua_set_NPC_SPAWN_POINT_bAutoRespawn);
  tolua_variable(tolua_S,"nSmallGroupID",tolua_get_NPC_SPAWN_POINT_nSmallGroupID,tolua_set_NPC_SPAWN_POINT_nSmallGroupID);
  tolua_variable(tolua_S,"nMediumGroupID",tolua_get_NPC_SPAWN_POINT_nMediumGroupID,tolua_set_NPC_SPAWN_POINT_nMediumGroupID);
  tolua_variable(tolua_S,"nLargeGroupID",tolua_get_NPC_SPAWN_POINT_nLargeGroupID,tolua_set_NPC_SPAWN_POINT_nLargeGroupID);
  tolua_variable(tolua_S,"pDeadBTRoot",tolua_get_NPC_SPAWN_POINT_pDeadBTRoot_ptr,tolua_set_NPC_SPAWN_POINT_pDeadBTRoot_ptr);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CScene","CScene","",NULL);
 tolua_beginmodule(tolua_S,"CScene");
#ifndef TOLUA_DISABLE_tolua_scene_CScene_AddRole00
  tolua_function(tolua_S,"AddRole",tolua_scene_CScene_AddRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_RemoveRole00
  tolua_function(tolua_S,"RemoveRole",tolua_scene_CScene_RemoveRole00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_AddNpc00
  tolua_function(tolua_S,"AddNpc",tolua_scene_CScene_AddNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_RemoveNpc00
  tolua_function(tolua_S,"RemoveNpc",tolua_scene_CScene_RemoveNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_AddDoodad00
  tolua_function(tolua_S,"AddDoodad",tolua_scene_CScene_AddDoodad00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_RemoveDoodad00
  tolua_function(tolua_S,"RemoveDoodad",tolua_scene_CScene_RemoveDoodad00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SpawnNpc00
  tolua_function(tolua_S,"SpawnNpc",tolua_scene_CScene_SpawnNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SpawnSingleNpc00
  tolua_function(tolua_S,"SpawnSingleNpc",tolua_scene_CScene_SpawnSingleNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SpawnNpcMediumGroup00
  tolua_function(tolua_S,"SpawnNpcMediumGroup",tolua_scene_CScene_SpawnNpcMediumGroup00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_FindNpc00
  tolua_function(tolua_S,"FindNpc",tolua_scene_CScene_FindNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SpawnDoodad00
  tolua_function(tolua_S,"SpawnDoodad",tolua_scene_CScene_SpawnDoodad00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetSceneTempID00
  tolua_function(tolua_S,"GetSceneTempID",tolua_scene_CScene_GetSceneTempID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetSceneID00
  tolua_function(tolua_S,"GetSceneID",tolua_scene_CScene_GetSceneID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetSceneData00
  tolua_function(tolua_S,"GetSceneData",tolua_scene_CScene_GetSceneData00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetStaticData00
  tolua_function(tolua_S,"GetStaticData",tolua_scene_CScene_GetStaticData00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetLowerZ00
  tolua_function(tolua_S,"GetLowerZ",tolua_scene_CScene_GetLowerZ00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SetDoorState00
  tolua_function(tolua_S,"SetDoorState",tolua_scene_CScene_SetDoorState00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_IsDoorClosed00
  tolua_function(tolua_S,"IsDoorClosed",tolua_scene_CScene_IsDoorClosed00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SetVariable00
  tolua_function(tolua_S,"SetVariable",tolua_scene_CScene_SetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetVariable00
  tolua_function(tolua_S,"GetVariable",tolua_scene_CScene_GetVariable00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetServerGroup00
  tolua_function(tolua_S,"GetServerGroup",tolua_scene_CScene_GetServerGroup00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetRoleCount00
  tolua_function(tolua_S,"GetRoleCount",tolua_scene_CScene_GetRoleCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetNpcCount00
  tolua_function(tolua_S,"GetNpcCount",tolua_scene_CScene_GetNpcCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_GetWeather00
  tolua_function(tolua_S,"GetWeather",tolua_scene_CScene_GetWeather00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_SetWeather00
  tolua_function(tolua_S,"SetWeather",tolua_scene_CScene_SetWeather00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_IsSabacStarted00
  tolua_function(tolua_S,"IsSabacStarted",tolua_scene_CScene_IsSabacStarted00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CScene_Say00
  tolua_function(tolua_S,"Say",tolua_scene_CScene_Say00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CSceneStaticData","CSceneStaticData","",NULL);
 tolua_beginmodule(tolua_S,"CSceneStaticData");
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_FindTeleportPoint00
  tolua_function(tolua_S,"FindTeleportPoint",tolua_scene_CSceneStaticData_FindTeleportPoint00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetSingleNpcCount00
  tolua_function(tolua_S,"GetSingleNpcCount",tolua_scene_CSceneStaticData_GetSingleNpcCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetSingleNpc00
  tolua_function(tolua_S,"GetSingleNpc",tolua_scene_CSceneStaticData_GetSingleNpc00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetSingleNpcByName00
  tolua_function(tolua_S,"GetSingleNpcByName",tolua_scene_CSceneStaticData_GetSingleNpcByName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetMaxZoneX00
  tolua_function(tolua_S,"GetMaxZoneX",tolua_scene_CSceneStaticData_GetMaxZoneX00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetMaxZoneY00
  tolua_function(tolua_S,"GetMaxZoneY",tolua_scene_CSceneStaticData_GetMaxZoneY00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CSceneStaticData_GetGroundGrid00
  tolua_function(tolua_S,"GetGroundGrid",tolua_scene_CSceneStaticData_GetGroundGrid00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"CSceneFileMgr","CSceneFileMgr","",NULL);
 tolua_beginmodule(tolua_S,"CSceneFileMgr");
#ifndef TOLUA_DISABLE_tolua_scene_CSceneFileMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_scene_CSceneFileMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_CSceneFileMgr_GetStaticData00
  tolua_function(tolua_S,"GetStaticData",tolua_scene_CSceneFileMgr_GetStaticData00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_constant(tolua_S,"SIN_COS_NUMBER",SIN_COS_NUMBER);
#ifndef TOLUA_DISABLE_tolua_scene_g_Sin00
 tolua_function(tolua_S,"g_Sin",tolua_scene_g_Sin00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_g_Cos00
 tolua_function(tolua_S,"g_Cos",tolua_scene_g_Cos00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_NormalizeDirection00
 tolua_function(tolua_S,"NormalizeDirection",tolua_scene_NormalizeDirection00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_g_GetDistance2D00
 tolua_function(tolua_S,"g_GetDistance2D",tolua_scene_g_GetDistance2D00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_scene_g_GetDistance3D00
 tolua_function(tolua_S,"g_GetDistance3D",tolua_scene_g_GetDistance3D00);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_scene (lua_State* tolua_S) {
 return tolua_scene_open(tolua_S);
};
#endif

