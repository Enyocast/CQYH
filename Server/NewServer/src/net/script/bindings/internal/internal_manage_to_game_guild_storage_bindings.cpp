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

void register_internal_manage_to_game_guild_storage_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_guild_pre_push_item_ack_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK>(L, internal_message_namespace, "M2G_GUILD_PRE_PUSH_ITEM_ACK", "InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_pre_push_item_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK(); });
    internal_message_m2g_guild_pre_push_item_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK>(new InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK()); });
    internal_message_m2g_guild_pre_push_item_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_pre_push_item_ack_type["wConSlot"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self) { return self.wConSlot; }, [](InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK::wConSlot) value) { self.wConSlot = value; });
    internal_message_m2g_guild_pre_push_item_ack_type["wSlot"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self) { return self.wSlot; }, [](InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK::wSlot) value) { self.wSlot = value; });
    internal_message_m2g_guild_pre_push_item_ack_type["byConSlot"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self) { return self.byConSlot; }, [](InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK::byConSlot) value) { self.byConSlot = value; });
    internal_message_m2g_guild_pre_push_item_ack_type["bySlot"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self) { return self.bySlot; }, [](InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_PUSH_ITEM_ACK::bySlot) value) { self.bySlot = value; });
    auto internal_message_m2g_guild_pre_pop_item_ack_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK>(L, internal_message_namespace, "M2G_GUILD_PRE_POP_ITEM_ACK", "InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_pre_pop_item_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK(); });
    internal_message_m2g_guild_pre_pop_item_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK>(new InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK()); });
    internal_message_m2g_guild_pre_pop_item_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_pre_pop_item_ack_type["wConSlot"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self) { return self.wConSlot; }, [](InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK::wConSlot) value) { self.wConSlot = value; });
    internal_message_m2g_guild_pre_pop_item_ack_type["wSlot"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self) { return self.wSlot; }, [](InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK::wSlot) value) { self.wSlot = value; });
    internal_message_m2g_guild_pre_pop_item_ack_type["byConSlot"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self) { return self.byConSlot; }, [](InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK::byConSlot) value) { self.byConSlot = value; });
    internal_message_m2g_guild_pre_pop_item_ack_type["bySlot"] = sol::property([](const InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self) { return self.bySlot; }, [](InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_PRE_POP_ITEM_ACK::bySlot) value) { self.bySlot = value; });
    auto internal_message_m2g_guild_pop_item_ack_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_POP_ITEM_ACK>(L, internal_message_namespace, "M2G_GUILD_POP_ITEM_ACK", "InternalMessage::M2G_GUILD_POP_ITEM_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_pop_item_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_POP_ITEM_ACK(); });
    internal_message_m2g_guild_pop_item_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_POP_ITEM_ACK>(new InternalMessage::M2G_GUILD_POP_ITEM_ACK()); });
    internal_message_m2g_guild_pop_item_ack_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GUILD_POP_ITEM_ACK& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GUILD_POP_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_POP_ITEM_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_guild_pop_item_ack_type["wConSlot"] = sol::property([](const InternalMessage::M2G_GUILD_POP_ITEM_ACK& self) { return self.wConSlot; }, [](InternalMessage::M2G_GUILD_POP_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_POP_ITEM_ACK::wConSlot) value) { self.wConSlot = value; });
    internal_message_m2g_guild_pop_item_ack_type["wSlot"] = sol::property([](const InternalMessage::M2G_GUILD_POP_ITEM_ACK& self) { return self.wSlot; }, [](InternalMessage::M2G_GUILD_POP_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_POP_ITEM_ACK::wSlot) value) { self.wSlot = value; });
    internal_message_m2g_guild_pop_item_ack_type["nLength"] = sol::property([](const InternalMessage::M2G_GUILD_POP_ITEM_ACK& self) { return self.nLength; }, [](InternalMessage::M2G_GUILD_POP_ITEM_ACK& self, decltype(InternalMessage::M2G_GUILD_POP_ITEM_ACK::nLength) value) { self.nLength = value; });
    internal_message_m2g_guild_pop_item_ack_type["buff"] = cqyh::lua::string_property(&InternalMessage::M2G_GUILD_POP_ITEM_ACK::buff);
}

}
