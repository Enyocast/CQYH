#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_tool_common_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_ms_info_type = cqyh::lua::usertype<InternalMessage::MS_INFO>(L, internal_message_namespace, "MS_INFO", "InternalMessage::MS_INFO");
    internal_message_ms_info_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::MS_INFO(); });
    internal_message_ms_info_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::MS_INFO>(new InternalMessage::MS_INFO()); });
    internal_message_ms_info_type["dwIndex"] = sol::property([](const InternalMessage::MS_INFO& self) { return self.dwIndex; }, [](InternalMessage::MS_INFO& self, decltype(InternalMessage::MS_INFO::dwIndex) value) { self.dwIndex = value; });
    internal_message_ms_info_type["szMSName"] = cqyh::lua::string_property(&InternalMessage::MS_INFO::szMSName);
    auto internal_message_gm2_tl_error_str_type = cqyh::lua::usertype<InternalMessage::GM2TL_ERROR_STR>(L, internal_message_namespace, "GM2TL_ERROR_STR", "InternalMessage::GM2TL_ERROR_STR", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_error_str_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_ERROR_STR(); });
    internal_message_gm2_tl_error_str_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_ERROR_STR>(new InternalMessage::GM2TL_ERROR_STR()); });
    internal_message_gm2_tl_error_str_type["szErr"] = cqyh::lua::string_property(&InternalMessage::GM2TL_ERROR_STR::szErr);
}

}
