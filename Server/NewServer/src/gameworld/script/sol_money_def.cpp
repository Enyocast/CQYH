#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../../Common/define/money_def.h"

int sol_money_def_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MONEYTYPE_INVALID"] = static_cast<lua_Number>(MONEYTYPE_INVALID);
    globals["MONEYTYPE_01"] = static_cast<lua_Number>(MONEYTYPE_01);
    globals["MONEYTYPE_02"] = static_cast<lua_Number>(MONEYTYPE_02);
    globals["MONEYTYPE_03"] = static_cast<lua_Number>(MONEYTYPE_03);
    globals["MONEYTYPE_04"] = static_cast<lua_Number>(MONEYTYPE_04);
    globals["MONEYTYPE_FATIGUE"] = static_cast<lua_Number>(MONEYTYPE_FATIGUE);
    globals["MONEYTYPE_SOUL_PTS"] = static_cast<lua_Number>(MONEYTYPE_SOUL_PTS);
    globals["MONEYTYPE_MASTER_EXP"] = static_cast<lua_Number>(MONEYTYPE_MASTER_EXP);
    globals["MONEYTYPE_AIR"] = static_cast<lua_Number>(MONEYTYPE_AIR);
    globals["MONEYTYPE_BF"] = static_cast<lua_Number>(MONEYTYPE_BF);
    globals["MONEYTYPE_GUILD"] = static_cast<lua_Number>(MONEYTYPE_GUILD);
    globals["MONEYTYPE_SPELL_PTS"] = static_cast<lua_Number>(MONEYTYPE_SPELL_PTS);
    globals["MONEYTYPE_MORAL"] = static_cast<lua_Number>(MONEYTYPE_MORAL);
    globals["MONEYTYPE_ARENA"] = static_cast<lua_Number>(MONEYTYPE_ARENA);
    globals["MONEYTYPE_ACHIEVEMENTPTS"] = static_cast<lua_Number>(MONEYTYPE_ACHIEVEMENTPTS);
    globals["MONEYTYPE_COUNT"] = static_cast<lua_Number>(MONEYTYPE_COUNT);
    return 1;
}
