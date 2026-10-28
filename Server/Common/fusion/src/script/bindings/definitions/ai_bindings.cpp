#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/ai_def.h"

namespace cqyh::fusion::bindings {

void register_ai_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["sigInvalid"] = static_cast<lua_Number>(sigInvalid);
    globals["sigSpreadHate"] = static_cast<lua_Number>(sigSpreadHate);
    globals["sigAssistOnce"] = static_cast<lua_Number>(sigAssistOnce);
    globals["sigAssist"] = static_cast<lua_Number>(sigAssist);
    globals["sigHelpSpellHeal"] = static_cast<lua_Number>(sigHelpSpellHeal);
    globals["sigHelpSpellHarm"] = static_cast<lua_Number>(sigHelpSpellHarm);
    globals["sigUserDefine"] = static_cast<lua_Number>(sigUserDefine);
    globals["sigEnd"] = static_cast<lua_Number>(sigEnd);
    globals["apsInvalid"] = static_cast<lua_Number>(apsInvalid);
    globals["apsLine"] = static_cast<lua_Number>(apsLine);
    globals["apsLineBack"] = static_cast<lua_Number>(apsLineBack);
    globals["apsCircle"] = static_cast<lua_Number>(apsCircle);
    globals["apsTotal"] = static_cast<lua_Number>(apsTotal);
}

}
