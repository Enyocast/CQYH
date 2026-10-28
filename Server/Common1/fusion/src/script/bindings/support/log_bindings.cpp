#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../NewServer/inc/baselib/log.h"
#include "../../../../../../NewServer/inc/baselib/circle_list.h"
#include "../../../../../../NewServer/inc/baselib/thread.h"

namespace cqyh::fusion::bindings {

void register_log_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["lotNone"] = static_cast<lua_Number>(lotNone);
    globals["lotConsole"] = static_cast<lua_Number>(lotConsole);
    globals["lotFile"] = static_cast<lua_Number>(lotFile);
    globals["lotTrace"] = static_cast<lua_Number>(lotTrace);
    globals["lotCustom"] = static_cast<lua_Number>(lotCustom);
    globals["lotAll"] = static_cast<lua_Number>(lotAll);
    globals["lltNone"] = static_cast<lua_Number>(lltNone);
    globals["lltDebug"] = static_cast<lua_Number>(lltDebug);
    globals["lltInfo"] = static_cast<lua_Number>(lltInfo);
    globals["lltWarning"] = static_cast<lua_Number>(lltWarning);
    globals["lltError"] = static_cast<lua_Number>(lltError);
    globals["lltCritical"] = static_cast<lua_Number>(lltCritical);
    globals["lltSDU"] = static_cast<lua_Number>(lltSDU);
    globals["lltMove"] = static_cast<lua_Number>(lltMove);
    globals["lltLua"] = static_cast<lua_Number>(lltLua);
    globals["lltSpell"] = static_cast<lua_Number>(lltSpell);
    globals["lltSys"] = static_cast<lua_Number>(lltSys);
    globals["lltAll"] = static_cast<lua_Number>(lltAll);
}

}
