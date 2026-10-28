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

void register_internal_manage_to_game_mentorship_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_mst_cz_type = cqyh::lua::usertype<InternalMessage::M2G_MST_CZ>(L, internal_message_namespace, "M2G_MST_CZ", "InternalMessage::M2G_MST_CZ", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mst_cz_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MST_CZ(); });
    internal_message_m2g_mst_cz_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MST_CZ>(new InternalMessage::M2G_MST_CZ()); });
    internal_message_m2g_mst_cz_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_MST_CZ& self) { return self.dwRoleID; }, [](InternalMessage::M2G_MST_CZ& self, decltype(InternalMessage::M2G_MST_CZ::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_mst_cz_type["dwTargetID"] = sol::property([](const InternalMessage::M2G_MST_CZ& self) { return self.dwTargetID; }, [](InternalMessage::M2G_MST_CZ& self, decltype(InternalMessage::M2G_MST_CZ::dwTargetID) value) { self.dwTargetID = value; });
    internal_message_m2g_mst_cz_type["byCZType"] = sol::property([](const InternalMessage::M2G_MST_CZ& self) { return self.byCZType; }, [](InternalMessage::M2G_MST_CZ& self, decltype(InternalMessage::M2G_MST_CZ::byCZType) value) { self.byCZType = value; });
    internal_message_m2g_mst_cz_type["byCZLevel"] = sol::property([](const InternalMessage::M2G_MST_CZ& self) { return self.byCZLevel; }, [](InternalMessage::M2G_MST_CZ& self, decltype(InternalMessage::M2G_MST_CZ::byCZLevel) value) { self.byCZLevel = value; });
    internal_message_m2g_mst_cz_type["nConsumption"] = sol::property([](const InternalMessage::M2G_MST_CZ& self) { return self.nConsumption; }, [](InternalMessage::M2G_MST_CZ& self, decltype(InternalMessage::M2G_MST_CZ::nConsumption) value) { self.nConsumption = value; });
    internal_message_m2g_mst_cz_type["szText"] = cqyh::lua::string_property(&InternalMessage::M2G_MST_CZ::szText);
    auto internal_message_m2g_mst_sync_state_type = cqyh::lua::usertype<InternalMessage::M2G_MST_SYNC_STATE>(L, internal_message_namespace, "M2G_MST_SYNC_STATE", "InternalMessage::M2G_MST_SYNC_STATE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mst_sync_state_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MST_SYNC_STATE(); });
    internal_message_m2g_mst_sync_state_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MST_SYNC_STATE>(new InternalMessage::M2G_MST_SYNC_STATE()); });
    internal_message_m2g_mst_sync_state_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_MST_SYNC_STATE& self) { return self.dwRoleID; }, [](InternalMessage::M2G_MST_SYNC_STATE& self, decltype(InternalMessage::M2G_MST_SYNC_STATE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_mst_sync_state_type["nState"] = sol::property([](const InternalMessage::M2G_MST_SYNC_STATE& self) { return self.nState; }, [](InternalMessage::M2G_MST_SYNC_STATE& self, decltype(InternalMessage::M2G_MST_SYNC_STATE::nState) value) { self.nState = value; });
    auto internal_message_m2g_mst_sync_data_type = cqyh::lua::usertype<InternalMessage::M2G_MST_SYNC_DATA>(L, internal_message_namespace, "M2G_MST_SYNC_DATA", "InternalMessage::M2G_MST_SYNC_DATA", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mst_sync_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MST_SYNC_DATA(); });
    internal_message_m2g_mst_sync_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MST_SYNC_DATA>(new InternalMessage::M2G_MST_SYNC_DATA()); });
    internal_message_m2g_mst_sync_data_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_MST_SYNC_DATA& self) { return self.dwRoleID; }, [](InternalMessage::M2G_MST_SYNC_DATA& self, decltype(InternalMessage::M2G_MST_SYNC_DATA::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_mst_sync_data_type["dwTeacherID"] = sol::property([](const InternalMessage::M2G_MST_SYNC_DATA& self) { return self.dwTeacherID; }, [](InternalMessage::M2G_MST_SYNC_DATA& self, decltype(InternalMessage::M2G_MST_SYNC_DATA::dwTeacherID) value) { self.dwTeacherID = value; });
    internal_message_m2g_mst_sync_data_type["byStudNum"] = sol::property([](const InternalMessage::M2G_MST_SYNC_DATA& self) { return self.byStudNum; }, [](InternalMessage::M2G_MST_SYNC_DATA& self, decltype(InternalMessage::M2G_MST_SYNC_DATA::byStudNum) value) { self.byStudNum = value; });
    internal_message_m2g_mst_sync_data_type["arrStudentID"] = cqyh::lua::array_property(&InternalMessage::M2G_MST_SYNC_DATA::arrStudentID);
    auto internal_message_m2g_mst_create_relation_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_MST_CREATE_RELATION_NTF>(L, internal_message_namespace, "M2G_MST_CREATE_RELATION_NTF", "InternalMessage::M2G_MST_CREATE_RELATION_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mst_create_relation_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MST_CREATE_RELATION_NTF(); });
    internal_message_m2g_mst_create_relation_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MST_CREATE_RELATION_NTF>(new InternalMessage::M2G_MST_CREATE_RELATION_NTF()); });
    internal_message_m2g_mst_create_relation_ntf_type["dwTeacherID"] = sol::property([](const InternalMessage::M2G_MST_CREATE_RELATION_NTF& self) { return self.dwTeacherID; }, [](InternalMessage::M2G_MST_CREATE_RELATION_NTF& self, decltype(InternalMessage::M2G_MST_CREATE_RELATION_NTF::dwTeacherID) value) { self.dwTeacherID = value; });
    internal_message_m2g_mst_create_relation_ntf_type["dwStudentID"] = sol::property([](const InternalMessage::M2G_MST_CREATE_RELATION_NTF& self) { return self.dwStudentID; }, [](InternalMessage::M2G_MST_CREATE_RELATION_NTF& self, decltype(InternalMessage::M2G_MST_CREATE_RELATION_NTF::dwStudentID) value) { self.dwStudentID = value; });
    auto internal_message_m2g_mst_del_relation_ntf_type = cqyh::lua::usertype<InternalMessage::M2G_MST_DEL_RELATION_NTF>(L, internal_message_namespace, "M2G_MST_DEL_RELATION_NTF", "InternalMessage::M2G_MST_DEL_RELATION_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mst_del_relation_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MST_DEL_RELATION_NTF(); });
    internal_message_m2g_mst_del_relation_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MST_DEL_RELATION_NTF>(new InternalMessage::M2G_MST_DEL_RELATION_NTF()); });
    internal_message_m2g_mst_del_relation_ntf_type["dwTeacherID"] = sol::property([](const InternalMessage::M2G_MST_DEL_RELATION_NTF& self) { return self.dwTeacherID; }, [](InternalMessage::M2G_MST_DEL_RELATION_NTF& self, decltype(InternalMessage::M2G_MST_DEL_RELATION_NTF::dwTeacherID) value) { self.dwTeacherID = value; });
    internal_message_m2g_mst_del_relation_ntf_type["dwStudentID"] = sol::property([](const InternalMessage::M2G_MST_DEL_RELATION_NTF& self) { return self.dwStudentID; }, [](InternalMessage::M2G_MST_DEL_RELATION_NTF& self, decltype(InternalMessage::M2G_MST_DEL_RELATION_NTF::dwStudentID) value) { self.dwStudentID = value; });
    auto internal_message_m2g_mst_update_data_type = cqyh::lua::usertype<InternalMessage::M2G_MST_UPDATE_DATA>(L, internal_message_namespace, "M2G_MST_UPDATE_DATA", "InternalMessage::M2G_MST_UPDATE_DATA", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mst_update_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MST_UPDATE_DATA(); });
    internal_message_m2g_mst_update_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MST_UPDATE_DATA>(new InternalMessage::M2G_MST_UPDATE_DATA()); });
    internal_message_m2g_mst_update_data_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_MST_UPDATE_DATA& self) { return self.dwRoleID; }, [](InternalMessage::M2G_MST_UPDATE_DATA& self, decltype(InternalMessage::M2G_MST_UPDATE_DATA::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_mst_update_data_type["nType"] = sol::property([](const InternalMessage::M2G_MST_UPDATE_DATA& self) { return self.nType; }, [](InternalMessage::M2G_MST_UPDATE_DATA& self, decltype(InternalMessage::M2G_MST_UPDATE_DATA::nType) value) { self.nType = value; });
    internal_message_m2g_mst_update_data_type["nValue"] = sol::property([](const InternalMessage::M2G_MST_UPDATE_DATA& self) { return self.nValue; }, [](InternalMessage::M2G_MST_UPDATE_DATA& self, decltype(InternalMessage::M2G_MST_UPDATE_DATA::nValue) value) { self.nValue = value; });
}

}
