#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmsvr_message.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_gm_server_audit_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2gm_gm_str_cmd_log_type = cqyh::lua::usertype<InternalMessage::M2GM_GM_STR_CMD_LOG>(L, internal_message_namespace, "M2GM_GM_STR_CMD_LOG", "InternalMessage::M2GM_GM_STR_CMD_LOG", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2gm_gm_str_cmd_log_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2GM_GM_STR_CMD_LOG(); });
    internal_message_m2gm_gm_str_cmd_log_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2GM_GM_STR_CMD_LOG>(new InternalMessage::M2GM_GM_STR_CMD_LOG()); });
    internal_message_m2gm_gm_str_cmd_log_type["dwTime"] = sol::property([](const InternalMessage::M2GM_GM_STR_CMD_LOG& self) { return self.dwTime; }, [](InternalMessage::M2GM_GM_STR_CMD_LOG& self, decltype(InternalMessage::M2GM_GM_STR_CMD_LOG::dwTime) value) { self.dwTime = value; });
    internal_message_m2gm_gm_str_cmd_log_type["byGroupID"] = sol::property([](const InternalMessage::M2GM_GM_STR_CMD_LOG& self) { return self.byGroupID; }, [](InternalMessage::M2GM_GM_STR_CMD_LOG& self, decltype(InternalMessage::M2GM_GM_STR_CMD_LOG::byGroupID) value) { self.byGroupID = value; });
    internal_message_m2gm_gm_str_cmd_log_type["nResult"] = sol::property([](const InternalMessage::M2GM_GM_STR_CMD_LOG& self) { return self.nResult; }, [](InternalMessage::M2GM_GM_STR_CMD_LOG& self, decltype(InternalMessage::M2GM_GM_STR_CMD_LOG::nResult) value) { self.nResult = value; });
    internal_message_m2gm_gm_str_cmd_log_type["dwRoleID"] = sol::property([](const InternalMessage::M2GM_GM_STR_CMD_LOG& self) { return self.dwRoleID; }, [](InternalMessage::M2GM_GM_STR_CMD_LOG& self, decltype(InternalMessage::M2GM_GM_STR_CMD_LOG::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2gm_gm_str_cmd_log_type["dwIP"] = sol::property([](const InternalMessage::M2GM_GM_STR_CMD_LOG& self) { return self.dwIP; }, [](InternalMessage::M2GM_GM_STR_CMD_LOG& self, decltype(InternalMessage::M2GM_GM_STR_CMD_LOG::dwIP) value) { self.dwIP = value; });
    internal_message_m2gm_gm_str_cmd_log_type["szRoleName"] = cqyh::lua::string_property(&InternalMessage::M2GM_GM_STR_CMD_LOG::szRoleName);
    internal_message_m2gm_gm_str_cmd_log_type["szGMCommand"] = cqyh::lua::string_property(&InternalMessage::M2GM_GM_STR_CMD_LOG::szGMCommand);
}

}
