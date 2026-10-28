#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_game_to_manage_guild_storage_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_guild_view_storage_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_VIEW_STORAGE>(L, internal_message_namespace, "G2M_GUILD_VIEW_STORAGE", "InternalMessage::G2M_GUILD_VIEW_STORAGE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_view_storage_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_VIEW_STORAGE(); });
    internal_message_g2m_guild_view_storage_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_VIEW_STORAGE>(new InternalMessage::G2M_GUILD_VIEW_STORAGE()); });
    internal_message_g2m_guild_view_storage_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_VIEW_STORAGE& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_VIEW_STORAGE& self, decltype(InternalMessage::G2M_GUILD_VIEW_STORAGE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_view_storage_type["byStorageTag"] = sol::property([](const InternalMessage::G2M_GUILD_VIEW_STORAGE& self) { return self.byStorageTag; }, [](InternalMessage::G2M_GUILD_VIEW_STORAGE& self, decltype(InternalMessage::G2M_GUILD_VIEW_STORAGE::byStorageTag) value) { self.byStorageTag = value; });
    auto internal_message_g2m_guild_pre_push_item_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_PRE_PUSH_ITEM>(L, internal_message_namespace, "G2M_GUILD_PRE_PUSH_ITEM", "InternalMessage::G2M_GUILD_PRE_PUSH_ITEM", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_pre_push_item_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_PRE_PUSH_ITEM(); });
    internal_message_g2m_guild_pre_push_item_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_PRE_PUSH_ITEM>(new InternalMessage::G2M_GUILD_PRE_PUSH_ITEM()); });
    internal_message_g2m_guild_pre_push_item_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_PUSH_ITEM::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_pre_push_item_type["wSourceConSlot"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self) { return self.wSourceConSlot; }, [](InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_PUSH_ITEM::wSourceConSlot) value) { self.wSourceConSlot = value; });
    internal_message_g2m_guild_pre_push_item_type["wSourceSlot"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self) { return self.wSourceSlot; }, [](InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_PUSH_ITEM::wSourceSlot) value) { self.wSourceSlot = value; });
    internal_message_g2m_guild_pre_push_item_type["byTargetConSlot"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self) { return self.byTargetConSlot; }, [](InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_PUSH_ITEM::byTargetConSlot) value) { self.byTargetConSlot = value; });
    internal_message_g2m_guild_pre_push_item_type["byTargetSlot"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self) { return self.byTargetSlot; }, [](InternalMessage::G2M_GUILD_PRE_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_PUSH_ITEM::byTargetSlot) value) { self.byTargetSlot = value; });
    auto internal_message_g2m_guild_push_item_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_PUSH_ITEM>(L, internal_message_namespace, "G2M_GUILD_PUSH_ITEM", "InternalMessage::G2M_GUILD_PUSH_ITEM", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_push_item_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_PUSH_ITEM(); });
    internal_message_g2m_guild_push_item_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_PUSH_ITEM>(new InternalMessage::G2M_GUILD_PUSH_ITEM()); });
    internal_message_g2m_guild_push_item_type["nResult"] = sol::property([](const InternalMessage::G2M_GUILD_PUSH_ITEM& self) { return self.nResult; }, [](InternalMessage::G2M_GUILD_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PUSH_ITEM::nResult) value) { self.nResult = value; });
    internal_message_g2m_guild_push_item_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_PUSH_ITEM& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PUSH_ITEM::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_push_item_type["byConSlot"] = sol::property([](const InternalMessage::G2M_GUILD_PUSH_ITEM& self) { return self.byConSlot; }, [](InternalMessage::G2M_GUILD_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PUSH_ITEM::byConSlot) value) { self.byConSlot = value; });
    internal_message_g2m_guild_push_item_type["bySlot"] = sol::property([](const InternalMessage::G2M_GUILD_PUSH_ITEM& self) { return self.bySlot; }, [](InternalMessage::G2M_GUILD_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PUSH_ITEM::bySlot) value) { self.bySlot = value; });
    internal_message_g2m_guild_push_item_type["wItemSize"] = sol::property([](const InternalMessage::G2M_GUILD_PUSH_ITEM& self) { return self.wItemSize; }, [](InternalMessage::G2M_GUILD_PUSH_ITEM& self, decltype(InternalMessage::G2M_GUILD_PUSH_ITEM::wItemSize) value) { self.wItemSize = value; });
    internal_message_g2m_guild_push_item_type["buff"] = cqyh::lua::string_property(&InternalMessage::G2M_GUILD_PUSH_ITEM::buff);
    auto internal_message_g2m_guild_pre_pop_item_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_PRE_POP_ITEM>(L, internal_message_namespace, "G2M_GUILD_PRE_POP_ITEM", "InternalMessage::G2M_GUILD_PRE_POP_ITEM", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_pre_pop_item_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_PRE_POP_ITEM(); });
    internal_message_g2m_guild_pre_pop_item_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_PRE_POP_ITEM>(new InternalMessage::G2M_GUILD_PRE_POP_ITEM()); });
    internal_message_g2m_guild_pre_pop_item_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_POP_ITEM& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_PRE_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_POP_ITEM::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_pre_pop_item_type["byConSlot"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_POP_ITEM& self) { return self.byConSlot; }, [](InternalMessage::G2M_GUILD_PRE_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_POP_ITEM::byConSlot) value) { self.byConSlot = value; });
    internal_message_g2m_guild_pre_pop_item_type["bySlot"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_POP_ITEM& self) { return self.bySlot; }, [](InternalMessage::G2M_GUILD_PRE_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_POP_ITEM::bySlot) value) { self.bySlot = value; });
    internal_message_g2m_guild_pre_pop_item_type["wTargetConSlot"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_POP_ITEM& self) { return self.wTargetConSlot; }, [](InternalMessage::G2M_GUILD_PRE_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_POP_ITEM::wTargetConSlot) value) { self.wTargetConSlot = value; });
    internal_message_g2m_guild_pre_pop_item_type["wTargetSlot"] = sol::property([](const InternalMessage::G2M_GUILD_PRE_POP_ITEM& self) { return self.wTargetSlot; }, [](InternalMessage::G2M_GUILD_PRE_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_PRE_POP_ITEM::wTargetSlot) value) { self.wTargetSlot = value; });
    auto internal_message_g2m_guild_pop_item_type = cqyh::lua::usertype<InternalMessage::G2M_GUILD_POP_ITEM>(L, internal_message_namespace, "G2M_GUILD_POP_ITEM", "InternalMessage::G2M_GUILD_POP_ITEM", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_guild_pop_item_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GUILD_POP_ITEM(); });
    internal_message_g2m_guild_pop_item_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GUILD_POP_ITEM>(new InternalMessage::G2M_GUILD_POP_ITEM()); });
    internal_message_g2m_guild_pop_item_type["nResult"] = sol::property([](const InternalMessage::G2M_GUILD_POP_ITEM& self) { return self.nResult; }, [](InternalMessage::G2M_GUILD_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_POP_ITEM::nResult) value) { self.nResult = value; });
    internal_message_g2m_guild_pop_item_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GUILD_POP_ITEM& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GUILD_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_POP_ITEM::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_guild_pop_item_type["byConSlot"] = sol::property([](const InternalMessage::G2M_GUILD_POP_ITEM& self) { return self.byConSlot; }, [](InternalMessage::G2M_GUILD_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_POP_ITEM::byConSlot) value) { self.byConSlot = value; });
    internal_message_g2m_guild_pop_item_type["bySlot"] = sol::property([](const InternalMessage::G2M_GUILD_POP_ITEM& self) { return self.bySlot; }, [](InternalMessage::G2M_GUILD_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_POP_ITEM::bySlot) value) { self.bySlot = value; });
    internal_message_g2m_guild_pop_item_type["wConSlot"] = sol::property([](const InternalMessage::G2M_GUILD_POP_ITEM& self) { return self.wConSlot; }, [](InternalMessage::G2M_GUILD_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_POP_ITEM::wConSlot) value) { self.wConSlot = value; });
    internal_message_g2m_guild_pop_item_type["wSlot"] = sol::property([](const InternalMessage::G2M_GUILD_POP_ITEM& self) { return self.wSlot; }, [](InternalMessage::G2M_GUILD_POP_ITEM& self, decltype(InternalMessage::G2M_GUILD_POP_ITEM::wSlot) value) { self.wSlot = value; });
}

}
