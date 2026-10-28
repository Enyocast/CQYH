#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../../Common/define/hero_def.h"

int sol_hero_def_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["hatInvalid"] = static_cast<lua_Number>(hatInvalid);
    globals["hatFollow"] = static_cast<lua_Number>(hatFollow);
    globals["hatActive"] = static_cast<lua_Number>(hatActive);
    globals["hatPassive"] = static_cast<lua_Number>(hatPassive);
    globals["hatStandstill"] = static_cast<lua_Number>(hatStandstill);
    globals["hatTotal"] = static_cast<lua_Number>(hatTotal);
    return 1;
}
