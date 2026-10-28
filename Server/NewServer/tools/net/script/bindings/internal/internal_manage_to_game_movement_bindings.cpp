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

namespace cqyh::net_tools::bindings {

void register_internal_manage_to_game_movement_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_jump_arena_scene_type = cqyh::lua::usertype<InternalMessage::M2G_JUMP_ARENA_SCENE>(L, internal_message_namespace, "M2G_JUMP_ARENA_SCENE", "InternalMessage::M2G_JUMP_ARENA_SCENE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_jump_arena_scene_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_JUMP_ARENA_SCENE(); });
    internal_message_m2g_jump_arena_scene_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_JUMP_ARENA_SCENE>(new InternalMessage::M2G_JUMP_ARENA_SCENE()); });
    internal_message_m2g_jump_arena_scene_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_JUMP_ARENA_SCENE& self) { return self.dwRoleID; }, [](InternalMessage::M2G_JUMP_ARENA_SCENE& self, decltype(InternalMessage::M2G_JUMP_ARENA_SCENE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_jump_arena_scene_type["dwSceneTempID"] = sol::property([](const InternalMessage::M2G_JUMP_ARENA_SCENE& self) { return self.dwSceneTempID; }, [](InternalMessage::M2G_JUMP_ARENA_SCENE& self, decltype(InternalMessage::M2G_JUMP_ARENA_SCENE::dwSceneTempID) value) { self.dwSceneTempID = value; });
    internal_message_m2g_jump_arena_scene_type["dwSceneID"] = sol::property([](const InternalMessage::M2G_JUMP_ARENA_SCENE& self) { return self.dwSceneID; }, [](InternalMessage::M2G_JUMP_ARENA_SCENE& self, decltype(InternalMessage::M2G_JUMP_ARENA_SCENE::dwSceneID) value) { self.dwSceneID = value; });
    internal_message_m2g_jump_arena_scene_type["bySide"] = sol::property([](const InternalMessage::M2G_JUMP_ARENA_SCENE& self) { return self.bySide; }, [](InternalMessage::M2G_JUMP_ARENA_SCENE& self, decltype(InternalMessage::M2G_JUMP_ARENA_SCENE::bySide) value) { self.bySide = value; });
}

}
