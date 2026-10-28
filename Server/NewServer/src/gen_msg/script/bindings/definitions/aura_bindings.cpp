#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/aura_def.h"

namespace cqyh::gen_msg::bindings {

void register_aura_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_AURA_EX_EVT"] = static_cast<lua_Number>(MAX_AURA_EX_EVT);
    sol::table aura_category_namespace = globals["AURA_CATEGORY"].get_or_create<sol::table>();
    aura_category_namespace["acInvalid"] = static_cast<lua_Number>(acInvalid);
    aura_category_namespace["acNone"] = static_cast<lua_Number>(acNone);
    aura_category_namespace["acPositive"] = static_cast<lua_Number>(acPositive);
    aura_category_namespace["acNegative"] = static_cast<lua_Number>(acNegative);
    aura_category_namespace["acTotal"] = static_cast<lua_Number>(acTotal);
    sol::table aura_effect_type_namespace = globals["AURA_EFFECT_TYPE"].get_or_create<sol::table>();
    aura_effect_type_namespace["auetInvalid"] = static_cast<lua_Number>(auetInvalid);
    aura_effect_type_namespace["auetNone"] = static_cast<lua_Number>(auetNone);
    aura_effect_type_namespace["auetType01"] = static_cast<lua_Number>(auetType01);
    aura_effect_type_namespace["auetType02"] = static_cast<lua_Number>(auetType02);
    aura_effect_type_namespace["auetType03"] = static_cast<lua_Number>(auetType03);
    aura_effect_type_namespace["auetType04"] = static_cast<lua_Number>(auetType04);
    aura_effect_type_namespace["auetType05"] = static_cast<lua_Number>(auetType05);
    aura_effect_type_namespace["auetType06"] = static_cast<lua_Number>(auetType06);
    aura_effect_type_namespace["auetType07"] = static_cast<lua_Number>(auetType07);
    aura_effect_type_namespace["auetType08"] = static_cast<lua_Number>(auetType08);
    aura_effect_type_namespace["auetType09"] = static_cast<lua_Number>(auetType09);
    aura_effect_type_namespace["auetType10"] = static_cast<lua_Number>(auetType10);
    aura_effect_type_namespace["auetType11"] = static_cast<lua_Number>(auetType11);
    aura_effect_type_namespace["auetType12"] = static_cast<lua_Number>(auetType12);
    aura_effect_type_namespace["auetType13"] = static_cast<lua_Number>(auetType13);
    aura_effect_type_namespace["auetType14"] = static_cast<lua_Number>(auetType14);
    aura_effect_type_namespace["auetType15"] = static_cast<lua_Number>(auetType15);
    aura_effect_type_namespace["auetType16"] = static_cast<lua_Number>(auetType16);
    aura_effect_type_namespace["auetType17"] = static_cast<lua_Number>(auetType17);
    aura_effect_type_namespace["auetType18"] = static_cast<lua_Number>(auetType18);
    aura_effect_type_namespace["auetType19"] = static_cast<lua_Number>(auetType19);
    aura_effect_type_namespace["auetType20"] = static_cast<lua_Number>(auetType20);
    aura_effect_type_namespace["auetType21"] = static_cast<lua_Number>(auetType21);
    aura_effect_type_namespace["auetType22"] = static_cast<lua_Number>(auetType22);
    aura_effect_type_namespace["auetType23"] = static_cast<lua_Number>(auetType23);
    aura_effect_type_namespace["auetType24"] = static_cast<lua_Number>(auetType24);
    aura_effect_type_namespace["auetTotal"] = static_cast<lua_Number>(auetTotal);
    sol::table aura_stack_type_namespace = globals["AURA_STACK_TYPE"].get_or_create<sol::table>();
    aura_stack_type_namespace["austInvalid"] = static_cast<lua_Number>(austInvalid);
    aura_stack_type_namespace["austNone"] = static_cast<lua_Number>(austNone);
    aura_stack_type_namespace["austSubstitute"] = static_cast<lua_Number>(austSubstitute);
    aura_stack_type_namespace["austStack"] = static_cast<lua_Number>(austStack);
    aura_stack_type_namespace["austCoexist"] = static_cast<lua_Number>(austCoexist);
    aura_stack_type_namespace["austTotal"] = static_cast<lua_Number>(austTotal);
    sol::table aura_display_group_namespace = globals["AURA_DISPLAY_GROUP"].get_or_create<sol::table>();
    aura_display_group_namespace["adgInvalid"] = static_cast<lua_Number>(adgInvalid);
    aura_display_group_namespace["adgBegin"] = static_cast<lua_Number>(adgBegin);
    aura_display_group_namespace["adgGroupA"] = static_cast<lua_Number>(adgGroupA);
    aura_display_group_namespace["adgGroupB"] = static_cast<lua_Number>(adgGroupB);
    aura_display_group_namespace["adgGroupC"] = static_cast<lua_Number>(adgGroupC);
    aura_display_group_namespace["adgGroupD"] = static_cast<lua_Number>(adgGroupD);
    aura_display_group_namespace["adgGroupE"] = static_cast<lua_Number>(adgGroupE);
    aura_display_group_namespace["adgTotal"] = static_cast<lua_Number>(adgTotal);
    sol::table aura_resist_type_namespace = globals["AURA_RESIST_TYPE"].get_or_create<sol::table>();
    aura_resist_type_namespace["aurtNone"] = static_cast<lua_Number>(aurtNone);
    aura_resist_type_namespace["aurtPoison"] = static_cast<lua_Number>(aurtPoison);
    aura_resist_type_namespace["aurtDazzy"] = static_cast<lua_Number>(aurtDazzy);
    aura_resist_type_namespace["aurtFreeze"] = static_cast<lua_Number>(aurtFreeze);
    aura_resist_type_namespace["aurtBurn"] = static_cast<lua_Number>(aurtBurn);
    aura_resist_type_namespace["aurtRepel"] = static_cast<lua_Number>(aurtRepel);
    aura_resist_type_namespace["aurtTotal"] = static_cast<lua_Number>(aurtTotal);
}

}
