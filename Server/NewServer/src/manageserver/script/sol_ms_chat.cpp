#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../../Common/define/chat_def.h"
#include "./chat/ms_chat.h"

int sol_ms_chat_open(lua_State* L)
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
    auto type1 = cqyh::lua::usertype<CMSChatMgr>(L, globals, "CMSChatMgr", "CMSChatMgr");
    type1.set_function("GetInstance", []() -> decltype(auto) { return CMSChatMgr::GetInstance(); });
    type1.set_function("Say", [](CMSChatMgr* self, unsigned int dwSourceRoleID, unsigned int dwTargetRoleID, signed int nShowLocation, const char* pText, signed int nGroupID) -> decltype(auto) { return self->Say(dwSourceRoleID,dwTargetRoleID,nShowLocation,pText,nGroupID); });
    return 1;
}
