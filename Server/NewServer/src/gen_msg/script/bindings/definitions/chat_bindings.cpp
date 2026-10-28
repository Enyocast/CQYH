#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/chat_def.h"

namespace cqyh::gen_msg::bindings {

void register_chat_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_CHAT_MESSAGE_LEN"] = static_cast<lua_Number>(MAX_CHAT_MESSAGE_LEN);
    globals["CHAT_SYSTEM_ID"] = static_cast<lua_Number>(CHAT_SYSTEM_ID);
    sol::table chat_channel_type_namespace = globals["CHAT_CHANNEL_TYPE"].get_or_create<sol::table>();
    chat_channel_type_namespace["cctInvalid"] = static_cast<lua_Number>(cctInvalid);
    chat_channel_type_namespace["cctScreen"] = static_cast<lua_Number>(cctScreen);
    chat_channel_type_namespace["cctScene"] = static_cast<lua_Number>(cctScene);
    chat_channel_type_namespace["cctGroup"] = static_cast<lua_Number>(cctGroup);
    chat_channel_type_namespace["cctServer"] = static_cast<lua_Number>(cctServer);
    chat_channel_type_namespace["cctTotal"] = static_cast<lua_Number>(cctTotal);
    sol::table chat_location_type_namespace = globals["CHAT_LOCATION_TYPE"].get_or_create<sol::table>();
    chat_location_type_namespace["cltInvalid"] = static_cast<lua_Number>(cltInvalid);
    chat_location_type_namespace["cltNormal"] = static_cast<lua_Number>(cltNormal);
    chat_location_type_namespace["cltLighting"] = static_cast<lua_Number>(cltLighting);
    chat_location_type_namespace["cltTvShow"] = static_cast<lua_Number>(cltTvShow);
    chat_location_type_namespace["cltUrl"] = static_cast<lua_Number>(cltUrl);
    chat_location_type_namespace["cltDialog"] = static_cast<lua_Number>(cltDialog);
    chat_location_type_namespace["cltTrumpet"] = static_cast<lua_Number>(cltTrumpet);
    chat_location_type_namespace["cltGMTrumpet"] = static_cast<lua_Number>(cltGMTrumpet);
    chat_location_type_namespace["cltTotal"] = static_cast<lua_Number>(cltTotal);
}

}
