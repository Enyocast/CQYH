#include "stdafx.h"
#include "lua_script.h"
extern int sol_enum_open(lua_State* L);
int sol_e_enum_open(lua_State* L) { return sol_enum_open(L); }
