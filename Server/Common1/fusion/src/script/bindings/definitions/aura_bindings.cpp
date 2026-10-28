#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/aura_def.h"

namespace cqyh::fusion::bindings {

void register_aura_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_AURA_EX_EVT"] = static_cast<lua_Number>(MAX_AURA_EX_EVT);
    globals["acInvalid"] = static_cast<lua_Number>(acInvalid);
    globals["acNone"] = static_cast<lua_Number>(acNone);
    globals["acPositive"] = static_cast<lua_Number>(acPositive);
    globals["acNegative"] = static_cast<lua_Number>(acNegative);
    globals["acTotal"] = static_cast<lua_Number>(acTotal);
    globals["auetInvalid"] = static_cast<lua_Number>(auetInvalid);
    globals["auetNone"] = static_cast<lua_Number>(auetNone);
    globals["auetType01"] = static_cast<lua_Number>(auetType01);
    globals["auetType02"] = static_cast<lua_Number>(auetType02);
    globals["auetType03"] = static_cast<lua_Number>(auetType03);
    globals["auetType04"] = static_cast<lua_Number>(auetType04);
    globals["auetType05"] = static_cast<lua_Number>(auetType05);
    globals["auetType06"] = static_cast<lua_Number>(auetType06);
    globals["auetType07"] = static_cast<lua_Number>(auetType07);
    globals["auetType08"] = static_cast<lua_Number>(auetType08);
    globals["auetType09"] = static_cast<lua_Number>(auetType09);
    globals["auetType10"] = static_cast<lua_Number>(auetType10);
    globals["auetType11"] = static_cast<lua_Number>(auetType11);
    globals["auetType12"] = static_cast<lua_Number>(auetType12);
    globals["auetType13"] = static_cast<lua_Number>(auetType13);
    globals["auetType14"] = static_cast<lua_Number>(auetType14);
    globals["auetType15"] = static_cast<lua_Number>(auetType15);
    globals["auetType16"] = static_cast<lua_Number>(auetType16);
    globals["auetType17"] = static_cast<lua_Number>(auetType17);
    globals["auetType18"] = static_cast<lua_Number>(auetType18);
    globals["auetType19"] = static_cast<lua_Number>(auetType19);
    globals["auetType20"] = static_cast<lua_Number>(auetType20);
    globals["auetType21"] = static_cast<lua_Number>(auetType21);
    globals["auetType22"] = static_cast<lua_Number>(auetType22);
    globals["auetType23"] = static_cast<lua_Number>(auetType23);
    globals["auetType24"] = static_cast<lua_Number>(auetType24);
    globals["auetTotal"] = static_cast<lua_Number>(auetTotal);
    globals["austInvalid"] = static_cast<lua_Number>(austInvalid);
    globals["austNone"] = static_cast<lua_Number>(austNone);
    globals["austSubstitute"] = static_cast<lua_Number>(austSubstitute);
    globals["austStack"] = static_cast<lua_Number>(austStack);
    globals["austCoexist"] = static_cast<lua_Number>(austCoexist);
    globals["austTotal"] = static_cast<lua_Number>(austTotal);
    globals["adgInvalid"] = static_cast<lua_Number>(adgInvalid);
    globals["adgBegin"] = static_cast<lua_Number>(adgBegin);
    globals["adgGroupA"] = static_cast<lua_Number>(adgGroupA);
    globals["adgGroupB"] = static_cast<lua_Number>(adgGroupB);
    globals["adgGroupC"] = static_cast<lua_Number>(adgGroupC);
    globals["adgGroupD"] = static_cast<lua_Number>(adgGroupD);
    globals["adgGroupE"] = static_cast<lua_Number>(adgGroupE);
    globals["adgTotal"] = static_cast<lua_Number>(adgTotal);
    globals["aurtNone"] = static_cast<lua_Number>(aurtNone);
    globals["aurtPoison"] = static_cast<lua_Number>(aurtPoison);
    globals["aurtDazzy"] = static_cast<lua_Number>(aurtDazzy);
    globals["aurtFreeze"] = static_cast<lua_Number>(aurtFreeze);
    globals["aurtBurn"] = static_cast<lua_Number>(aurtBurn);
    globals["aurtRepel"] = static_cast<lua_Number>(aurtRepel);
    globals["aurtTotal"] = static_cast<lua_Number>(aurtTotal);
}

}
