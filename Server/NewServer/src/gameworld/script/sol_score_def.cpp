#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "scene_def.h"
#include "../../../Common/define/score_def.h"

int sol_score_def_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_SCORE_REWARD_COUNT"] = static_cast<lua_Number>(MAX_SCORE_REWARD_COUNT);
    globals["SCORE_REWARD_MAX_TIME"] = static_cast<lua_Number>(SCORE_REWARD_MAX_TIME);
    globals["NORMAl_EXP"] = static_cast<lua_Number>(NORMAl_EXP);
    globals["edstInvalid"] = static_cast<lua_Number>(edstInvalid);
    globals["edstRuning"] = static_cast<lua_Number>(edstRuning);
    globals["edstPreClosing"] = static_cast<lua_Number>(edstPreClosing);
    globals["edstClosing"] = static_cast<lua_Number>(edstClosing);
    globals["edstTotal"] = static_cast<lua_Number>(edstTotal);
    globals["edrInvalid"] = static_cast<lua_Number>(edrInvalid);
    globals["edrFirst"] = static_cast<lua_Number>(edrFirst);
    globals["edrSecond"] = static_cast<lua_Number>(edrSecond);
    globals["edrThird"] = static_cast<lua_Number>(edrThird);
    globals["edrTotal"] = static_cast<lua_Number>(edrTotal);
    globals["edsInvalid"] = static_cast<lua_Number>(edsInvalid);
    globals["edsC"] = static_cast<lua_Number>(edsC);
    globals["edsB"] = static_cast<lua_Number>(edsB);
    globals["edsA"] = static_cast<lua_Number>(edsA);
    globals["edsS"] = static_cast<lua_Number>(edsS);
    globals["edsSS"] = static_cast<lua_Number>(edsSS);
    globals["edsSSS"] = static_cast<lua_Number>(edsSSS);
    globals["edsTotal"] = static_cast<lua_Number>(edsTotal);
    return 1;
}
