#include "std_type.h"
#include "sol_bindings.h"
#include "external_message_header.h"
#include <cstdio>

extern int sol_external_message_open(lua_State* L);
extern int sol_internal_message_open(lua_State* L);

int main() {
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    cqyh::lua::initialize(lua);
    sol_external_message_open(lua);
    sol_internal_message_open(lua);
    const char* script = R"(
        assert(type(ExternalMessage.c2g_message_begin) == 'number')
        local packet = ExternalMessage.C2G_ROLE_STOP:new_local()
        packet.wMsg = 123
        assert(packet.wMsg == 123)
        local header = Cast(packet, 'ExternalMessage::MESSAGE_HEADER')
        assert(header.wMsg == 123)
        header.wMsg = 124
        assert(packet.wMsg == 124)
        local server = InternalMessage.SERVER_INFO:new_local()
        assert(server ~= nil)
        local inventory = ExternalMessage.C2G_MOVE_ITEM:new_local()
        inventory.bySrcConSlot = 1
        inventory.byDstConSlot = 2
        assert(inventory.bySrcConSlot == 1 and inventory.byDstConSlot == 2)
        local registration = InternalMessage.M2G_REGISTER_ACK:new_local()
        registration.dwGSSessionID = 42
        assert(registration.dwGSSessionID == 42)
        local database = InternalMessage.M2D_REGISTER_ACK:new_local()
        database.szDBName = 'protocol_test'
        assert(database.szDBName == 'protocol_test')
    )";
    if (luaL_dostring(lua, script) != 0) {
        std::fprintf(stderr, "%s\n", lua_tostring(lua, -1));
        return 1;
    }
    std::puts("Production protocol bindings passed");
    return 0;
}
