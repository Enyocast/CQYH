#include "std_type.h"
#include "sol_bindings.h"
#include "tl_config.h"
#include "script/sol_tl_config.h"
#include <cstdio>
#include <cstdint>
#ifdef _WIN32
#include <windows.h>
#include <crtdbg.h>
#endif

struct Entry { int value = 0; };
struct Base {
    virtual ~Base() = default;
    int base_value = 7;
};
struct Object : Base {
    char name[8] = {};
    int values[3] = {};
    Entry entries[2];
    std::int64_t position = 0;
};
TL_CONFIG g_TLConfig = {};

int main() {
#ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
#endif
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    std::puts("Creating Lua state");
    sol::state lua;
    lua_atpanic(lua, [](lua_State* L) -> int { std::fprintf(stderr, "Lua panic: %s\n", lua_tostring(L, -1)); std::exit(4); });
    lua.open_libraries(sol::lib::base);
    cqyh::lua::initialize(lua);
    sol_tl_config_open(lua);
    auto base = cqyh::lua::usertype<Base>(lua, lua.globals(), "Base", "Base");
    std::puts("Registered base");
    base["base_value"] = &Base::base_value;
    auto entry = cqyh::lua::usertype<Entry>(lua, lua.globals(), "Entry", "Entry");
    entry["value"] = &Entry::value;
    auto object = cqyh::lua::usertype<Object>(lua, lua.globals(), "Object", "Object",
        sol::base_classes, sol::bases<Base>());
    object["name"] = cqyh::lua::string_property(&Object::name);
    object["values"] = cqyh::lua::array_property(&Object::values);
    object["entries"] = cqyh::lua::array_property(&Object::entries);
    object["position"] = &Object::position;
    object.set_function("new_local", [] { return std::make_unique<Object>(); });
    object.set_function("GetInstance", []() -> Object& { static Object instance; return instance; });
    Object native;
    std::puts("Registered properties");
    cqyh::lua::push_object(lua, &native, "Object");
    if (cqyh::lua::object_pointer(lua, -1) != &native) return 6;
    lua_setglobal(lua, "native");
    lua["base"] = static_cast<Base*>(&native);
    cqyh::lua::push_object(lua, nullptr, "Object");
    lua_setglobal(lua, "null_object");
    const char* script = R"(
        assert(null_object == nil)
        assert(native.base_value == 7)
        native.name = '1234567890'
        assert(native.name == '1234567')
        native.name = 'a'
        assert(native.name == 'a')
        native.values[0] = 41
        native.values[2] = 43
        assert(native.values[0] == 41 and native.values[2] == 43)
        native.entries[0].value = 99
        assert(native.entries[0].value == 99)
        assert(not pcall(function() return native.values[-1] end))
        assert(not pcall(function() native.values[3] = 1 end))
        local derived = Cast(base, 'Object')
        assert(derived == native)
        derived.position = 4294967296
        assert(native.position == 4294967296)
        local owned = Object:new_local()
        owned.values[1] = 3
        assert(owned.values[1] == 3)
        assert(Object:GetInstance() ~= nil)
        local config = GetTLConfig()
        config.ServerList.nSvrNum = 1
        config.ServerList.arrGMList[0].nSvrID = 12
        config.ServerList.arrGMList[0].szName = 'Test server'
        config.ServerList.arrGMList[0].groupList[0].szGroupName = 'Test group'
        assert(GetTLConfig().ServerList.arrGMList[0].nSvrID == 12)
    )";
    std::puts("Running Lua assertions");
    if (luaL_dostring(lua, script) != 0) {
        std::fprintf(stderr, "%s\n", lua_tostring(lua, -1));
        return 1;
    }
    // Registering an included base type again must preserve existing members.
    cqyh::lua::usertype<Base>(lua, lua.globals(), "Base", "Base");
    if (luaL_dostring(lua, "assert(native.base_value == 7)") != 0) return 2;
    if (native.values[0] != 41 || native.entries[0].value != 99 || native.position != 4294967296LL) return 3;
    if (g_TLConfig.ServerList.nSvrNum != 1 || g_TLConfig.ServerList.arrGMList[0].nSvrID != 12) return 5;
    std::puts("sol2 bindings: callbacks, inheritance, casts, ownership, strings and arrays passed");
    return 0;
}
