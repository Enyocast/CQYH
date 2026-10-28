#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/ai_def.h"

namespace cqyh::gen_msg::bindings {

void register_ai_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table signal_type_namespace = globals["SIGNAL_TYPE"].get_or_create<sol::table>();
    signal_type_namespace["sigInvalid"] = static_cast<lua_Number>(sigInvalid);
    signal_type_namespace["sigSpreadHate"] = static_cast<lua_Number>(sigSpreadHate);
    signal_type_namespace["sigAssistOnce"] = static_cast<lua_Number>(sigAssistOnce);
    signal_type_namespace["sigAssist"] = static_cast<lua_Number>(sigAssist);
    signal_type_namespace["sigHelpSpellHeal"] = static_cast<lua_Number>(sigHelpSpellHeal);
    signal_type_namespace["sigHelpSpellHarm"] = static_cast<lua_Number>(sigHelpSpellHarm);
    signal_type_namespace["sigUserDefine"] = static_cast<lua_Number>(sigUserDefine);
    signal_type_namespace["sigEnd"] = static_cast<lua_Number>(sigEnd);
    sol::table ai_patrol_style_namespace = globals["AI_PATROL_STYLE"].get_or_create<sol::table>();
    ai_patrol_style_namespace["apsInvalid"] = static_cast<lua_Number>(apsInvalid);
    ai_patrol_style_namespace["apsLine"] = static_cast<lua_Number>(apsLine);
    ai_patrol_style_namespace["apsLineBack"] = static_cast<lua_Number>(apsLineBack);
    ai_patrol_style_namespace["apsCircle"] = static_cast<lua_Number>(apsCircle);
    ai_patrol_style_namespace["apsTotal"] = static_cast<lua_Number>(apsTotal);
}

}
