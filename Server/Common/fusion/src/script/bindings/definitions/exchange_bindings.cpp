#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/exchange_def.h"

namespace cqyh::fusion::bindings {

void register_exchange_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["eotInvalid"] = static_cast<lua_Number>(eotInvalid);
    globals["eotBuy"] = static_cast<lua_Number>(eotBuy);
    globals["eotSell"] = static_cast<lua_Number>(eotSell);
    globals["eosInvalid"] = static_cast<lua_Number>(eosInvalid);
    globals["eosEffective"] = static_cast<lua_Number>(eosEffective);
    globals["eosCanceled"] = static_cast<lua_Number>(eosCanceled);
    globals["eosExpired"] = static_cast<lua_Number>(eosExpired);
    globals["eosFinished"] = static_cast<lua_Number>(eosFinished);
    globals["eosError"] = static_cast<lua_Number>(eosError);
    globals["eosTotal"] = static_cast<lua_Number>(eosTotal);
    globals["MAX_ORDER_DETAIL_NUM"] = static_cast<lua_Number>(MAX_ORDER_DETAIL_NUM);
}

}
