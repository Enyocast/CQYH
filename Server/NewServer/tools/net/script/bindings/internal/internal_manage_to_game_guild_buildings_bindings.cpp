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

void register_internal_manage_to_game_guild_buildings_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g_b_data_type = cqyh::lua::usertype<InternalMessage::G_B_DATA>(L, internal_message_namespace, "G_B_DATA", "InternalMessage::G_B_DATA");
    internal_message_g_b_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G_B_DATA(); });
    internal_message_g_b_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G_B_DATA>(new InternalMessage::G_B_DATA()); });
    internal_message_g_b_data_type["qwNameID"] = sol::property([](const InternalMessage::G_B_DATA& self) { return self.qwNameID; }, [](InternalMessage::G_B_DATA& self, decltype(InternalMessage::G_B_DATA::qwNameID) value) { self.qwNameID = value; });
    internal_message_g_b_data_type["nType"] = sol::property([](const InternalMessage::G_B_DATA& self) { return self.nType; }, [](InternalMessage::G_B_DATA& self, decltype(InternalMessage::G_B_DATA::nType) value) { self.nType = value; });
    internal_message_g_b_data_type["nLevel"] = sol::property([](const InternalMessage::G_B_DATA& self) { return self.nLevel; }, [](InternalMessage::G_B_DATA& self, decltype(InternalMessage::G_B_DATA::nLevel) value) { self.nLevel = value; });
    auto internal_message_m2g_guild_upgrade_building_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF>(L, internal_message_namespace, "M2G_GUILD_UPGRADE_BUILDING_NTF", "InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_upgrade_building_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF(); });
    internal_message_m2g_guild_upgrade_building_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF>(new InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF()); });
    internal_message_m2g_guild_upgrade_building_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_upgrade_building_ntf_type["qwNameID"] = sol::property([](const InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF& self) { return self.qwNameID; }, [](InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF::qwNameID) value) { self.qwNameID = value; });
    internal_message_m2g_guild_upgrade_building_ntf_type["nType"] = sol::property([](const InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF& self) { return self.nType; }, [](InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF::nType) value) { self.nType = value; });
    internal_message_m2g_guild_upgrade_building_ntf_type["nLevel"] = sol::property([](const InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF& self) { return self.nLevel; }, [](InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_UPGRADE_BUILDING_NTF::nLevel) value) { self.nLevel = value; });
    auto internal_message_m2g_guild_update_building_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF>(L, internal_message_namespace, "M2G_GUILD_UPDATE_BUILDING_NTF", "InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_update_building_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF(); });
    internal_message_m2g_guild_update_building_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF>(new InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF()); });
    internal_message_m2g_guild_update_building_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_update_building_ntf_type["qwNameID"] = sol::property([](const InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF& self) { return self.qwNameID; }, [](InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF::qwNameID) value) { self.qwNameID = value; });
    internal_message_m2g_guild_update_building_ntf_type["nType"] = sol::property([](const InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF& self) { return self.nType; }, [](InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF::nType) value) { self.nType = value; });
    internal_message_m2g_guild_update_building_ntf_type["nLevel"] = sol::property([](const InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF& self) { return self.nLevel; }, [](InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_UPDATE_BUILDING_NTF::nLevel) value) { self.nLevel = value; });
    auto internal_message_m2g_guild_del_building_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_DEL_BUILDING_NTF>(L, internal_message_namespace, "M2G_GUILD_DEL_BUILDING_NTF", "InternalMessage::M2G_GUILD_DEL_BUILDING_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_del_building_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_DEL_BUILDING_NTF(); });
    internal_message_m2g_guild_del_building_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_DEL_BUILDING_NTF>(new InternalMessage::M2G_GUILD_DEL_BUILDING_NTF()); });
    internal_message_m2g_guild_del_building_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_DEL_BUILDING_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_DEL_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_DEL_BUILDING_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_del_building_ntf_type["qwNameID"] = sol::property([](const InternalMessage::M2G_GUILD_DEL_BUILDING_NTF& self) { return self.qwNameID; }, [](InternalMessage::M2G_GUILD_DEL_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_DEL_BUILDING_NTF::qwNameID) value) { self.qwNameID = value; });
    internal_message_m2g_guild_del_building_ntf_type["nType"] = sol::property([](const InternalMessage::M2G_GUILD_DEL_BUILDING_NTF& self) { return self.nType; }, [](InternalMessage::M2G_GUILD_DEL_BUILDING_NTF& self, decltype(InternalMessage::M2G_GUILD_DEL_BUILDING_NTF::nType) value) { self.nType = value; });
    auto internal_message_m2g_guild_update_welfare_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF>(L, internal_message_namespace, "M2G_GUILD_UPDATE_WELFARE_NTF", "InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_update_welfare_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF(); });
    internal_message_m2g_guild_update_welfare_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF>(new InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF()); });
    internal_message_m2g_guild_update_welfare_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF& self, decltype(InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_update_welfare_ntf_type["nType"] = sol::property([](const InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF& self) { return self.nType; }, [](InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF& self, decltype(InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF::nType) value) { self.nType = value; });
    internal_message_m2g_guild_update_welfare_ntf_type["nLevel"] = sol::property([](const InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF& self) { return self.nLevel; }, [](InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF& self, decltype(InternalMessage::M2G_GUILD_UPDATE_WELFARE_NTF::nLevel) value) { self.nLevel = value; });
    auto internal_message_m2g_guild_sync_building_state_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF>(L, internal_message_namespace, "M2G_GUILD_SYNC_BUILDING_STATE_NTF", "InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_guild_sync_building_state_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF(); });
    internal_message_m2g_guild_sync_building_state_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF>(new InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF()); });
    internal_message_m2g_guild_sync_building_state_ntf_type["dwGuildID"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF& self) { return self.dwGuildID; }, [](InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_m2g_guild_sync_building_state_ntf_type["qwNameID"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF& self) { return self.qwNameID; }, [](InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF::qwNameID) value) { self.qwNameID = value; });
    internal_message_m2g_guild_sync_building_state_ntf_type["dwReviveTime"] = sol::property([](const InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF& self) { return self.dwReviveTime; }, [](InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF& self, decltype(InternalMessage::M2G_GUILD_SYNC_BUILDING_STATE_NTF::dwReviveTime) value) { self.dwReviveTime = value; });
}

}
