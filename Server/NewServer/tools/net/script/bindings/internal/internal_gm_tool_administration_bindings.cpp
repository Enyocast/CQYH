#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_tool_administration_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_tl2_gm_exe_gm_str_type = cqyh::lua::usertype<InternalMessage::TL2GM_EXE_GM_STR>(L, internal_message_namespace, "TL2GM_EXE_GM_STR", "InternalMessage::TL2GM_EXE_GM_STR", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_tl2_gm_exe_gm_str_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::TL2GM_EXE_GM_STR(); });
    internal_message_tl2_gm_exe_gm_str_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::TL2GM_EXE_GM_STR>(new InternalMessage::TL2GM_EXE_GM_STR()); });
    internal_message_tl2_gm_exe_gm_str_type["szStr"] = cqyh::lua::string_property(&InternalMessage::TL2GM_EXE_GM_STR::szStr);
    auto internal_message_gm2_tl_exe_gm_str_ack_type = cqyh::lua::usertype<InternalMessage::GM2TL_EXE_GM_STR_ACK>(L, internal_message_namespace, "GM2TL_EXE_GM_STR_ACK", "InternalMessage::GM2TL_EXE_GM_STR_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_exe_gm_str_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_EXE_GM_STR_ACK(); });
    internal_message_gm2_tl_exe_gm_str_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_EXE_GM_STR_ACK>(new InternalMessage::GM2TL_EXE_GM_STR_ACK()); });
}

}
