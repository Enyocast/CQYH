#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../define/string_def.h"

int sol_string_table_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["SERVER_STRING_START_ID"] = static_cast<lua_Number>(SERVER_STRING_START_ID);
    globals["STRING_TABLE_STR_LEN"] = static_cast<lua_Number>(STRING_TABLE_STR_LEN);
    globals["STRING_TABLE_STR_COUNT"] = static_cast<lua_Number>(STRING_TABLE_STR_COUNT);
    globals["essInvalid"] = static_cast<lua_Number>(essInvalid);
    globals["essItemRefineSuccess"] = static_cast<lua_Number>(essItemRefineSuccess);
    globals["essItemComposeSuccess"] = static_cast<lua_Number>(essItemComposeSuccess);
    globals["essItemComposeSuccessDouble"] = static_cast<lua_Number>(essItemComposeSuccessDouble);
    globals["essItemRuneSuccess"] = static_cast<lua_Number>(essItemRuneSuccess);
    globals["essItemMaterial"] = static_cast<lua_Number>(essItemMaterial);
    globals["essAwardOpenDialog"] = static_cast<lua_Number>(essAwardOpenDialog);
    globals["essRoleKilled"] = static_cast<lua_Number>(essRoleKilled);
    globals["essTotal"] = static_cast<lua_Number>(essTotal);
    return 1;
}
