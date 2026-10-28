#include "stdafx.h"
#include "sol_bindings.h"
#include "asimov_message_handler.h"

int sol_asimov_message_handler_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type = cqyh::lua::usertype<CAsimovMessageHandler>(L, globals, "CAsimovMessageHandler", "CAsimovMessageHandler", sol::base_classes, sol::bases<INetEventHandler>());
    type.set_function("GetInstance", []() -> decltype(auto) { return CAsimovMessageHandler::GetInstance(); });
    return 1;
}
