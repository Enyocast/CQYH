/*
** Lua binding: online_role_data
** Generated automatically by tolua++-1.0.92 on (timestamp omitted).
*/

#include "stdafx.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int tolua_online_role_data_open (lua_State* tolua_S);

#include "onlinerole/online_role_data.h"
#include "onlinerole/online_role_data_mgr.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"COnlineRoleDataMgr");
 tolua_usertype(tolua_S,"MS_ROLE_DATA");
 tolua_usertype(tolua_S,"MS_ONLINE_ROLE_DATA");
 tolua_usertype(tolua_S,"MS_USER");
}

/* get function: pUser of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_pUser_ptr
static int tolua_get_MS_ONLINE_ROLE_DATA_pUser_ptr(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pUser'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->pUser,"MS_USER");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pUser of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_pUser_ptr
static int tolua_set_MS_ONLINE_ROLE_DATA_pUser_ptr(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pUser'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MS_USER",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pUser = ((MS_USER*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pRoleData of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_pRoleData_ptr
static int tolua_get_MS_ONLINE_ROLE_DATA_pRoleData_ptr(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pRoleData'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->pRoleData,"MS_ROLE_DATA");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pRoleData of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_pRoleData_ptr
static int tolua_set_MS_ONLINE_ROLE_DATA_pRoleData_ptr(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pRoleData'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MS_ROLE_DATA",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pRoleData = ((MS_ROLE_DATA*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGMLevel of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_nGMLevel
static int tolua_get_MS_ONLINE_ROLE_DATA_nGMLevel(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGMLevel'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nGMLevel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGMLevel of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_nGMLevel
static int tolua_set_MS_ONLINE_ROLE_DATA_nGMLevel(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGMLevel'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGMLevel = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nCurrentHp of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_nCurrentHp
static int tolua_get_MS_ONLINE_ROLE_DATA_nCurrentHp(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentHp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCurrentHp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCurrentHp of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_nCurrentHp
static int tolua_set_MS_ONLINE_ROLE_DATA_nCurrentHp(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nCurrentMp of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_nCurrentMp
static int tolua_get_MS_ONLINE_ROLE_DATA_nCurrentMp(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nCurrentMp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nCurrentMp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nCurrentMp of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_nCurrentMp
static int tolua_set_MS_ONLINE_ROLE_DATA_nCurrentMp(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nMaxHp of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_nMaxHp
static int tolua_get_MS_ONLINE_ROLE_DATA_nMaxHp(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMaxHp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMaxHp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMaxHp of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_nMaxHp
static int tolua_set_MS_ONLINE_ROLE_DATA_nMaxHp(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMaxHp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nMaxHp = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nMaxMp of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_nMaxMp
static int tolua_get_MS_ONLINE_ROLE_DATA_nMaxMp(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMaxMp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nMaxMp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nMaxMp of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_nMaxMp
static int tolua_set_MS_ONLINE_ROLE_DATA_nMaxMp(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nMaxMp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nMaxMp = (( signed int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwLastSpeakTime of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwLastSpeakTime
static int tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwLastSpeakTime(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLastSpeakTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwLastSpeakTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwLastSpeakTime of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwLastSpeakTime
static int tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwLastSpeakTime(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLastSpeakTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwLastSpeakTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwLastQueryRoleInfoTime of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwLastQueryRoleInfoTime
static int tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwLastQueryRoleInfoTime(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLastQueryRoleInfoTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwLastQueryRoleInfoTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwLastQueryRoleInfoTime of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwLastQueryRoleInfoTime
static int tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwLastQueryRoleInfoTime(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwLastQueryRoleInfoTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwLastQueryRoleInfoTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: byQueryRoleInfoCount of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_unsigned_byQueryRoleInfoCount
static int tolua_get_MS_ONLINE_ROLE_DATA_unsigned_byQueryRoleInfoCount(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byQueryRoleInfoCount'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->byQueryRoleInfoCount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: byQueryRoleInfoCount of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_unsigned_byQueryRoleInfoCount
static int tolua_set_MS_ONLINE_ROLE_DATA_unsigned_byQueryRoleInfoCount(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byQueryRoleInfoCount'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byQueryRoleInfoCount = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwCliSessionID of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwCliSessionID
static int tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwCliSessionID(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCliSessionID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwCliSessionID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwCliSessionID of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwCliSessionID
static int tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwCliSessionID(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwCliSessionID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwCliSessionID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwGSSessionID of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwGSSessionID
static int tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwGSSessionID(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwGSSessionID'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwGSSessionID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwGSSessionID of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwGSSessionID
static int tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwGSSessionID(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwGSSessionID'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwGSSessionID = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwSaveTime of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwSaveTime
static int tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwSaveTime(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwSaveTime'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwSaveTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwSaveTime of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwSaveTime
static int tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwSaveTime(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwSaveTime'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwSaveTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dwMasterCD of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwMasterCD
static int tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwMasterCD(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwMasterCD'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dwMasterCD);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dwMasterCD of class  MS_ONLINE_ROLE_DATA */
#ifndef TOLUA_DISABLE_tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwMasterCD
static int tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwMasterCD(lua_State* tolua_S)
{
  MS_ONLINE_ROLE_DATA* self = (MS_ONLINE_ROLE_DATA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dwMasterCD'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dwMasterCD = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  COnlineRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_GetInstance00
static int tolua_online_role_data_COnlineRoleDataMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"COnlineRoleDataMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  COnlineRoleDataMgr& tolua_ret = (COnlineRoleDataMgr&)  COnlineRoleDataMgr::GetInstance();
  tolua_pushusertype(tolua_S,(void*)&tolua_ret,"COnlineRoleDataMgr");
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

/* method: FindOnlineRoleByName of class  COnlineRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByName00
static int tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"COnlineRoleDataMgr",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  COnlineRoleDataMgr* self = (COnlineRoleDataMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszRoleName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindOnlineRoleByName'", NULL);
#endif
 {
  MS_ONLINE_ROLE_DATA* tolua_ret = (MS_ONLINE_ROLE_DATA*)  self->FindOnlineRoleByName(pcszRoleName);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"MS_ONLINE_ROLE_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindOnlineRoleByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindOnlineRoleByRoleID of class  COnlineRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByRoleID00
static int tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByRoleID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"COnlineRoleDataMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  COnlineRoleDataMgr* self = (COnlineRoleDataMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindOnlineRoleByRoleID'", NULL);
#endif
 {
  MS_ONLINE_ROLE_DATA* tolua_ret = (MS_ONLINE_ROLE_DATA*)  self->FindOnlineRoleByRoleID(dwRoleID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"MS_ONLINE_ROLE_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindOnlineRoleByRoleID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindOnlineRoleByNameInGroup of class  COnlineRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByNameInGroup00
static int tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByNameInGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"COnlineRoleDataMgr",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  COnlineRoleDataMgr* self = (COnlineRoleDataMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* pcszRoleName = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned char byGroupID = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindOnlineRoleByNameInGroup'", NULL);
#endif
 {
  MS_ONLINE_ROLE_DATA* tolua_ret = (MS_ONLINE_ROLE_DATA*)  self->FindOnlineRoleByNameInGroup(pcszRoleName,byGroupID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"MS_ONLINE_ROLE_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindOnlineRoleByNameInGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindOnlineRoleByRoleIDInGroup of class  COnlineRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByRoleIDInGroup00
static int tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByRoleIDInGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"COnlineRoleDataMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  COnlineRoleDataMgr* self = (COnlineRoleDataMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned int dwRoleID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned char byGroupID = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindOnlineRoleByRoleIDInGroup'", NULL);
#endif
 {
  MS_ONLINE_ROLE_DATA* tolua_ret = (MS_ONLINE_ROLE_DATA*)  self->FindOnlineRoleByRoleIDInGroup(dwRoleID,byGroupID);
  tolua_pushusertype(tolua_S,(void*)tolua_ret,"MS_ONLINE_ROLE_DATA");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindOnlineRoleByRoleIDInGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoleNumberCount of class  COnlineRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_GetRoleNumberCount00
static int tolua_online_role_data_COnlineRoleDataMgr_GetRoleNumberCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"COnlineRoleDataMgr",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  COnlineRoleDataMgr* self = (COnlineRoleDataMgr*)  tolua_tousertype(tolua_S,1,0);
  unsigned char byGroupIndex = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoleNumberCount'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetRoleNumberCount(byGroupIndex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoleNumberCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoleNumberCount of class  COnlineRoleDataMgr */
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_GetRoleNumberCount01
static int tolua_online_role_data_COnlineRoleDataMgr_GetRoleNumberCount01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"COnlineRoleDataMgr",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  COnlineRoleDataMgr* self = (COnlineRoleDataMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoleNumberCount'", NULL);
#endif
 {
  unsigned int tolua_ret = ( unsigned int)  self->GetRoleNumberCount();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_online_role_data_COnlineRoleDataMgr_GetRoleNumberCount00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_online_role_data_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"MS_ONLINE_ROLE_DATA","MS_ONLINE_ROLE_DATA","",NULL);
 tolua_beginmodule(tolua_S,"MS_ONLINE_ROLE_DATA");
  tolua_variable(tolua_S,"pUser",tolua_get_MS_ONLINE_ROLE_DATA_pUser_ptr,tolua_set_MS_ONLINE_ROLE_DATA_pUser_ptr);
  tolua_variable(tolua_S,"pRoleData",tolua_get_MS_ONLINE_ROLE_DATA_pRoleData_ptr,tolua_set_MS_ONLINE_ROLE_DATA_pRoleData_ptr);
  tolua_variable(tolua_S,"nGMLevel",tolua_get_MS_ONLINE_ROLE_DATA_nGMLevel,tolua_set_MS_ONLINE_ROLE_DATA_nGMLevel);
  tolua_variable(tolua_S,"nCurrentHp",tolua_get_MS_ONLINE_ROLE_DATA_nCurrentHp,tolua_set_MS_ONLINE_ROLE_DATA_nCurrentHp);
  tolua_variable(tolua_S,"nCurrentMp",tolua_get_MS_ONLINE_ROLE_DATA_nCurrentMp,tolua_set_MS_ONLINE_ROLE_DATA_nCurrentMp);
  tolua_variable(tolua_S,"nMaxHp",tolua_get_MS_ONLINE_ROLE_DATA_nMaxHp,tolua_set_MS_ONLINE_ROLE_DATA_nMaxHp);
  tolua_variable(tolua_S,"nMaxMp",tolua_get_MS_ONLINE_ROLE_DATA_nMaxMp,tolua_set_MS_ONLINE_ROLE_DATA_nMaxMp);
  tolua_variable(tolua_S,"dwLastSpeakTime",tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwLastSpeakTime,tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwLastSpeakTime);
  tolua_variable(tolua_S,"dwLastQueryRoleInfoTime",tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwLastQueryRoleInfoTime,tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwLastQueryRoleInfoTime);
  tolua_variable(tolua_S,"byQueryRoleInfoCount",tolua_get_MS_ONLINE_ROLE_DATA_unsigned_byQueryRoleInfoCount,tolua_set_MS_ONLINE_ROLE_DATA_unsigned_byQueryRoleInfoCount);
  tolua_variable(tolua_S,"dwCliSessionID",tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwCliSessionID,tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwCliSessionID);
  tolua_variable(tolua_S,"dwGSSessionID",tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwGSSessionID,tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwGSSessionID);
  tolua_variable(tolua_S,"dwSaveTime",tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwSaveTime,tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwSaveTime);
  tolua_variable(tolua_S,"dwMasterCD",tolua_get_MS_ONLINE_ROLE_DATA_unsigned_dwMasterCD,tolua_set_MS_ONLINE_ROLE_DATA_unsigned_dwMasterCD);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"COnlineRoleDataMgr","COnlineRoleDataMgr","",NULL);
 tolua_beginmodule(tolua_S,"COnlineRoleDataMgr");
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_GetInstance00
  tolua_function(tolua_S,"GetInstance",tolua_online_role_data_COnlineRoleDataMgr_GetInstance00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByName00
  tolua_function(tolua_S,"FindOnlineRoleByName",tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByName00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByRoleID00
  tolua_function(tolua_S,"FindOnlineRoleByRoleID",tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByRoleID00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByNameInGroup00
  tolua_function(tolua_S,"FindOnlineRoleByNameInGroup",tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByNameInGroup00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByRoleIDInGroup00
  tolua_function(tolua_S,"FindOnlineRoleByRoleIDInGroup",tolua_online_role_data_COnlineRoleDataMgr_FindOnlineRoleByRoleIDInGroup00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_GetRoleNumberCount00
  tolua_function(tolua_S,"GetRoleNumberCount",tolua_online_role_data_COnlineRoleDataMgr_GetRoleNumberCount00);
#endif //#ifndef TOLUA_DISABLE
#ifndef TOLUA_DISABLE_tolua_online_role_data_COnlineRoleDataMgr_GetRoleNumberCount01
  tolua_function(tolua_S,"GetRoleNumberCount",tolua_online_role_data_COnlineRoleDataMgr_GetRoleNumberCount01);
#endif //#ifndef TOLUA_DISABLE
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_online_role_data (lua_State* tolua_S) {
 return tolua_online_role_data_open(tolua_S);
};
#endif

