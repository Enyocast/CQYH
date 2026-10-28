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

void register_internal_manage_to_game_world_objects_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_spawn_npc_type = cqyh::lua::usertype<InternalMessage::M2G_SPAWN_NPC>(L, internal_message_namespace, "M2G_SPAWN_NPC", "InternalMessage::M2G_SPAWN_NPC", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_spawn_npc_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_SPAWN_NPC(); });
    internal_message_m2g_spawn_npc_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_SPAWN_NPC>(new InternalMessage::M2G_SPAWN_NPC()); });
    internal_message_m2g_spawn_npc_type["nSceneTempID"] = sol::property([](const InternalMessage::M2G_SPAWN_NPC& self) { return self.nSceneTempID; }, [](InternalMessage::M2G_SPAWN_NPC& self, decltype(InternalMessage::M2G_SPAWN_NPC::nSceneTempID) value) { self.nSceneTempID = value; });
    internal_message_m2g_spawn_npc_type["nX"] = sol::property([](const InternalMessage::M2G_SPAWN_NPC& self) { return self.nX; }, [](InternalMessage::M2G_SPAWN_NPC& self, decltype(InternalMessage::M2G_SPAWN_NPC::nX) value) { self.nX = value; });
    internal_message_m2g_spawn_npc_type["nY"] = sol::property([](const InternalMessage::M2G_SPAWN_NPC& self) { return self.nY; }, [](InternalMessage::M2G_SPAWN_NPC& self, decltype(InternalMessage::M2G_SPAWN_NPC::nY) value) { self.nY = value; });
    internal_message_m2g_spawn_npc_type["nZ"] = sol::property([](const InternalMessage::M2G_SPAWN_NPC& self) { return self.nZ; }, [](InternalMessage::M2G_SPAWN_NPC& self, decltype(InternalMessage::M2G_SPAWN_NPC::nZ) value) { self.nZ = value; });
    internal_message_m2g_spawn_npc_type["nRange"] = sol::property([](const InternalMessage::M2G_SPAWN_NPC& self) { return self.nRange; }, [](InternalMessage::M2G_SPAWN_NPC& self, decltype(InternalMessage::M2G_SPAWN_NPC::nRange) value) { self.nRange = value; });
    internal_message_m2g_spawn_npc_type["nNpcTemplateID"] = sol::property([](const InternalMessage::M2G_SPAWN_NPC& self) { return self.nNpcTemplateID; }, [](InternalMessage::M2G_SPAWN_NPC& self, decltype(InternalMessage::M2G_SPAWN_NPC::nNpcTemplateID) value) { self.nNpcTemplateID = value; });
    internal_message_m2g_spawn_npc_type["nNpcCount"] = sol::property([](const InternalMessage::M2G_SPAWN_NPC& self) { return self.nNpcCount; }, [](InternalMessage::M2G_SPAWN_NPC& self, decltype(InternalMessage::M2G_SPAWN_NPC::nNpcCount) value) { self.nNpcCount = value; });
    internal_message_m2g_spawn_npc_type["dwSuicideTime"] = sol::property([](const InternalMessage::M2G_SPAWN_NPC& self) { return self.dwSuicideTime; }, [](InternalMessage::M2G_SPAWN_NPC& self, decltype(InternalMessage::M2G_SPAWN_NPC::dwSuicideTime) value) { self.dwSuicideTime = value; });
}

}
