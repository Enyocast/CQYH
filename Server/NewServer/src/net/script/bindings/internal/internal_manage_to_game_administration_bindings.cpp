#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/m2g_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"
#include "../../../../../../Common/define/variable_def.h"

namespace cqyh::net::bindings {

void register_internal_manage_to_game_administration_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_call_lua_function_type = cqyh::lua::usertype<InternalMessage::M2G_CALL_LUA_FUNCTION>(L, internal_message_namespace, "M2G_CALL_LUA_FUNCTION", "InternalMessage::M2G_CALL_LUA_FUNCTION", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_call_lua_function_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_CALL_LUA_FUNCTION(); });
    internal_message_m2g_call_lua_function_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_CALL_LUA_FUNCTION>(new InternalMessage::M2G_CALL_LUA_FUNCTION()); });
    internal_message_m2g_call_lua_function_type["chFileName"] = cqyh::lua::string_property(&InternalMessage::M2G_CALL_LUA_FUNCTION::chFileName);
    internal_message_m2g_call_lua_function_type["chFuncName"] = cqyh::lua::string_property(&InternalMessage::M2G_CALL_LUA_FUNCTION::chFuncName);
    internal_message_m2g_call_lua_function_type["nValue1"] = sol::property([](const InternalMessage::M2G_CALL_LUA_FUNCTION& self) { return self.nValue1; }, [](InternalMessage::M2G_CALL_LUA_FUNCTION& self, decltype(InternalMessage::M2G_CALL_LUA_FUNCTION::nValue1) value) { self.nValue1 = value; });
    internal_message_m2g_call_lua_function_type["nValue2"] = sol::property([](const InternalMessage::M2G_CALL_LUA_FUNCTION& self) { return self.nValue2; }, [](InternalMessage::M2G_CALL_LUA_FUNCTION& self, decltype(InternalMessage::M2G_CALL_LUA_FUNCTION::nValue2) value) { self.nValue2 = value; });
    internal_message_m2g_call_lua_function_type["nValue3"] = sol::property([](const InternalMessage::M2G_CALL_LUA_FUNCTION& self) { return self.nValue3; }, [](InternalMessage::M2G_CALL_LUA_FUNCTION& self, decltype(InternalMessage::M2G_CALL_LUA_FUNCTION::nValue3) value) { self.nValue3 = value; });
    auto internal_message_m2g_call_gm_command_type = cqyh::lua::usertype<InternalMessage::M2G_CALL_GM_COMMAND>(L, internal_message_namespace, "M2G_CALL_GM_COMMAND", "InternalMessage::M2G_CALL_GM_COMMAND", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_call_gm_command_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_CALL_GM_COMMAND(); });
    internal_message_m2g_call_gm_command_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_CALL_GM_COMMAND>(new InternalMessage::M2G_CALL_GM_COMMAND()); });
    internal_message_m2g_call_gm_command_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_CALL_GM_COMMAND& self) { return self.dwRoleID; }, [](InternalMessage::M2G_CALL_GM_COMMAND& self, decltype(InternalMessage::M2G_CALL_GM_COMMAND::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_call_gm_command_type["szGMCommand"] = cqyh::lua::string_property(&InternalMessage::M2G_CALL_GM_COMMAND::szGMCommand);
}

}
