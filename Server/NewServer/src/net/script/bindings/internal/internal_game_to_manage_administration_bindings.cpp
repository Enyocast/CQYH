#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_game_to_manage_administration_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_call_lua_function_type = cqyh::lua::usertype<InternalMessage::G2M_CALL_LUA_FUNCTION>(L, internal_message_namespace, "G2M_CALL_LUA_FUNCTION", "InternalMessage::G2M_CALL_LUA_FUNCTION", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_call_lua_function_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_CALL_LUA_FUNCTION(); });
    internal_message_g2m_call_lua_function_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_CALL_LUA_FUNCTION>(new InternalMessage::G2M_CALL_LUA_FUNCTION()); });
    internal_message_g2m_call_lua_function_type["chFileName"] = cqyh::lua::string_property(&InternalMessage::G2M_CALL_LUA_FUNCTION::chFileName);
    internal_message_g2m_call_lua_function_type["chFuncName"] = cqyh::lua::string_property(&InternalMessage::G2M_CALL_LUA_FUNCTION::chFuncName);
    internal_message_g2m_call_lua_function_type["nValue1"] = sol::property([](const InternalMessage::G2M_CALL_LUA_FUNCTION& self) { return self.nValue1; }, [](InternalMessage::G2M_CALL_LUA_FUNCTION& self, decltype(InternalMessage::G2M_CALL_LUA_FUNCTION::nValue1) value) { self.nValue1 = value; });
    internal_message_g2m_call_lua_function_type["nValue2"] = sol::property([](const InternalMessage::G2M_CALL_LUA_FUNCTION& self) { return self.nValue2; }, [](InternalMessage::G2M_CALL_LUA_FUNCTION& self, decltype(InternalMessage::G2M_CALL_LUA_FUNCTION::nValue2) value) { self.nValue2 = value; });
    internal_message_g2m_call_lua_function_type["nValue3"] = sol::property([](const InternalMessage::G2M_CALL_LUA_FUNCTION& self) { return self.nValue3; }, [](InternalMessage::G2M_CALL_LUA_FUNCTION& self, decltype(InternalMessage::G2M_CALL_LUA_FUNCTION::nValue3) value) { self.nValue3 = value; });
}

}
