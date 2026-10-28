#pragma once

// Shared policy for the server's sol2 bindings. Lua still owns its state in CLuaScript.
#ifndef SOL_ALL_SAFETIES_ON
#define SOL_ALL_SAFETIES_ON 1
#endif
#define SOL_NO_EXCEPTIONS 1
#include <sol/sol.hpp>
#include <algorithm>
#include <cstring>
#include <memory>
#include <string>
#include <type_traits>

namespace cqyh { namespace lua {

// The legacy variadic callback interface supplies void* plus a C++ type name.
// Keep the dispatch table in each Lua registry so states can be destroyed independently.
inline void push_object(lua_State* L, void* object, const char* type) {
    if (!object) {
        lua_pushnil(L);
        return;
    }
    sol::state_view lua(L);
    sol::table pushers = lua.registry()["cqyh.object_pushers"].get_or_create<sol::table>();
    sol::optional<sol::function> push = pushers[type];
    if (!push) {
        luaL_error(L, "Unregistered script object type: %s", type);
        return;
    }
    sol::object value = (*push)(sol::lightuserdata_value(object));
    value.push();
}

template <typename T, typename Parent, typename... Args>
sol::usertype<T> usertype(lua_State* L, Parent&& parent_source, const char* name,
                         const char* cpp_name, Args&&... args) {
    parent_source.push();
    sol::table parent(L, -1);
    lua_pop(L, 1);
    sol::state_view lua(L);
    sol::table types = lua.registry()["cqyh.usertypes"].get_or_create<sol::table>();
    sol::optional<sol::table> existing = types[cpp_name];
    if (existing) {
        parent[name] = *existing;
        return sol::usertype<T>(*existing);
    }
    auto result = parent.new_usertype<T>(name, sol::no_constructor, std::forward<Args>(args)...);
    result[sol::meta_function::equal_to] = [](const T* left, const T* right) { return left == right; };
    if (!existing) {
        result.push();
        sol::table type_table(L, -1);
        lua_pop(L, 1);
        types[cpp_name] = type_table;
        sol::table pushers = lua.registry()["cqyh.object_pushers"].get_or_create<sol::table>();
        pushers.set_function(cpp_name, [](sol::lightuserdata_value p) {
            return static_cast<T*>(p.value);
        });
    }
    return result;
}

template <typename C, typename M, std::size_t N = std::extent_v<M> * (std::extent_v<M, 1> == 0 ? 1 : std::extent_v<M, 1>)>
auto string_property(M C::*member) {
    return sol::property(
        [member](const C& self) { return std::string(reinterpret_cast<const char*>(self.*member)); },
        [member](C& self, const std::string& value, sol::this_state state) {
            // Flexible packet tails have no writable capacity in a standalone object.
            if constexpr (N == 0) {
                luaL_error(state, "cannot assign a flexible packet string without a capacity");
                return;
            }
            const auto size = (std::min)(N - 1, value.size());
            std::memcpy(self.*member, value.data(), size);
            reinterpret_cast<char*>(self.*member)[size] = '\0';
        });
}

// The existing scripts index C arrays from zero. A table proxy also preserves
// references to nested structs, so assignments update the original C++ data.
template <typename C, typename M, std::size_t N = std::extent_v<M>>
auto array_property(M C::*member) {
    using T = std::remove_pointer_t<decltype(std::declval<C&>().*member + 0)>;
    return sol::property([member](C& self, sol::this_state state) {
        sol::state_view lua(state);
        auto data = &(self.*member)[0];
        sol::table proxy = lua.create_table();
        sol::table meta = lua.create_table();
        meta.set_function(sol::meta_function::index, [data](sol::table, int index, sol::this_state s) -> sol::object {
            if (index < 0 || (N != 0 && index >= static_cast<int>(N))) {
                luaL_error(s, "array indexing out of range");
                return sol::nil;
            }
            if constexpr (std::is_arithmetic_v<T> || std::is_enum_v<T>)
                return sol::make_object(s, data[index]);
            else if constexpr (std::is_array_v<T> && std::is_same_v<std::remove_extent_t<T>, char>)
                return sol::make_object(s, static_cast<const char*>(data[index]));
            else
                return sol::make_object(s, std::ref(data[index]));
        });
        if constexpr (!std::is_array_v<T>) {
            meta.set_function(sol::meta_function::new_index, [data](sol::table, int index, T value, sol::this_state s) {
                if (index < 0 || (N != 0 && index >= static_cast<int>(N))) {
                    luaL_error(s, "array indexing out of range");
                    return;
                }
                data[index] = value;
            });
        }
        proxy[sol::metatable_key] = meta;
        return proxy;
    });
}

// Cast is retained for scripts that receive a base pointer or an untyped packet.
// sol2 stores the object pointer at the start of its userdata allocation.
inline void* object_pointer(lua_State* L, int index) {
    if (lua_isnil(L, index)) return nullptr;
    void* pointer = lua_touserdata(L, index);
    if (!lua_islightuserdata(L, index)) {
        luaL_checktype(L, index, LUA_TUSERDATA);
        pointer = *static_cast<void**>(pointer);
    }
    return pointer;
}

inline int cast_object(lua_State* L) {
    const char* type = luaL_checkstring(L, 2);
    push_object(L, object_pointer(L, 1), type);
    return 1;
}

inline void initialize(lua_State* L) {
    lua_register(L, "Cast", cast_object);
}

} } // namespace cqyh::lua
