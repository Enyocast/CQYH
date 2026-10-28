#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/chat_def.h"

namespace cqyh::fusion::bindings {

void register_chat_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_CHAT_MESSAGE_LEN"] = static_cast<lua_Number>(MAX_CHAT_MESSAGE_LEN);
    globals["CHAT_SYSTEM_ID"] = static_cast<lua_Number>(CHAT_SYSTEM_ID);
    globals["cctInvalid"] = static_cast<lua_Number>(cctInvalid);
    globals["cctScreen"] = static_cast<lua_Number>(cctScreen);
    globals["cctScene"] = static_cast<lua_Number>(cctScene);
    globals["cctGroup"] = static_cast<lua_Number>(cctGroup);
    globals["cctServer"] = static_cast<lua_Number>(cctServer);
    globals["cctTotal"] = static_cast<lua_Number>(cctTotal);
    globals["cltInvalid"] = static_cast<lua_Number>(cltInvalid);
    globals["cltNormal"] = static_cast<lua_Number>(cltNormal);
    globals["cltLighting"] = static_cast<lua_Number>(cltLighting);
    globals["cltTvShow"] = static_cast<lua_Number>(cltTvShow);
    globals["cltUrl"] = static_cast<lua_Number>(cltUrl);
    globals["cltDialog"] = static_cast<lua_Number>(cltDialog);
    globals["cltTrumpet"] = static_cast<lua_Number>(cltTrumpet);
    globals["cltGMTrumpet"] = static_cast<lua_Number>(cltGMTrumpet);
    globals["cltTotal"] = static_cast<lua_Number>(cltTotal);
}

}
