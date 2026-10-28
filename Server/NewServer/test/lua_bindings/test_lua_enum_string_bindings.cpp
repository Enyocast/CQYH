#include "sol_bindings.h"
#include <cstdio>

extern int sol_enum_str_open(lua_State* L);

int main() {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::string);
    sol_enum_str_open(lua);
    const char* script = R"(
        -- These tables are consumed by the GM and log enum-name lookup code.
        assert(ERROR_CODE_DEF.errSuccess == 1)
        assert(type(EItemLog.ITEMLOG_GM) == 'number')
        local names = {}
        for name, value in pairs(ERROR_CODE_DEF) do names[value] = name end
        assert(names[ERROR_CODE_DEF.errDatabase] == 'errDatabase')
        local itemNames = {}
        for name, value in pairs(EItemLog) do itemNames[value] = name end
        assert(itemNames[EItemLog.ITEMLOG_GM] == 'ITEMLOG_GM')
    )";
    if (luaL_dostring(lua, script) != 0) {
        std::fprintf(stderr, "%s\n", lua_tostring(lua, -1));
        return 1;
    }
    std::puts("Enum-string namespaces and reverse lookups passed");
    return 0;
}
