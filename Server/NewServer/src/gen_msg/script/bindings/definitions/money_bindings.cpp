#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/money_def.h"

namespace cqyh::gen_msg::bindings {

void register_money_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table money_type_namespace = globals["MONEY_TYPE"].get_or_create<sol::table>();
    money_type_namespace["MONEYTYPE_INVALID"] = static_cast<lua_Number>(MONEYTYPE_INVALID);
    money_type_namespace["MONEYTYPE_01"] = static_cast<lua_Number>(MONEYTYPE_01);
    money_type_namespace["MONEYTYPE_02"] = static_cast<lua_Number>(MONEYTYPE_02);
    money_type_namespace["MONEYTYPE_03"] = static_cast<lua_Number>(MONEYTYPE_03);
    money_type_namespace["MONEYTYPE_04"] = static_cast<lua_Number>(MONEYTYPE_04);
    money_type_namespace["MONEYTYPE_FATIGUE"] = static_cast<lua_Number>(MONEYTYPE_FATIGUE);
    money_type_namespace["MONEYTYPE_SOUL_PTS"] = static_cast<lua_Number>(MONEYTYPE_SOUL_PTS);
    money_type_namespace["MONEYTYPE_MASTER_EXP"] = static_cast<lua_Number>(MONEYTYPE_MASTER_EXP);
    money_type_namespace["MONEYTYPE_AIR"] = static_cast<lua_Number>(MONEYTYPE_AIR);
    money_type_namespace["MONEYTYPE_BF"] = static_cast<lua_Number>(MONEYTYPE_BF);
    money_type_namespace["MONEYTYPE_GUILD"] = static_cast<lua_Number>(MONEYTYPE_GUILD);
    money_type_namespace["MONEYTYPE_SPELL_PTS"] = static_cast<lua_Number>(MONEYTYPE_SPELL_PTS);
    money_type_namespace["MONEYTYPE_MORAL"] = static_cast<lua_Number>(MONEYTYPE_MORAL);
    money_type_namespace["MONEYTYPE_ARENA"] = static_cast<lua_Number>(MONEYTYPE_ARENA);
    money_type_namespace["MONEYTYPE_ACHIEVEMENTPTS"] = static_cast<lua_Number>(MONEYTYPE_ACHIEVEMENTPTS);
    money_type_namespace["MONEYTYPE_COUNT"] = static_cast<lua_Number>(MONEYTYPE_COUNT);
}

}
