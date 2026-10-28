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

void register_internal_manage_to_game_mentorship_teachers_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_mst_submit_teacher_app_type = cqyh::lua::usertype<InternalMessage::M2G_MST_SUBMIT_TEACHER_APP>(L, internal_message_namespace, "M2G_MST_SUBMIT_TEACHER_APP", "InternalMessage::M2G_MST_SUBMIT_TEACHER_APP", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mst_submit_teacher_app_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MST_SUBMIT_TEACHER_APP(); });
    internal_message_m2g_mst_submit_teacher_app_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MST_SUBMIT_TEACHER_APP>(new InternalMessage::M2G_MST_SUBMIT_TEACHER_APP()); });
    internal_message_m2g_mst_submit_teacher_app_type["bySourceType"] = sol::property([](const InternalMessage::M2G_MST_SUBMIT_TEACHER_APP& self) { return self.bySourceType; }, [](InternalMessage::M2G_MST_SUBMIT_TEACHER_APP& self, decltype(InternalMessage::M2G_MST_SUBMIT_TEACHER_APP::bySourceType) value) { self.bySourceType = value; });
    internal_message_m2g_mst_submit_teacher_app_type["dwTeacherID"] = sol::property([](const InternalMessage::M2G_MST_SUBMIT_TEACHER_APP& self) { return self.dwTeacherID; }, [](InternalMessage::M2G_MST_SUBMIT_TEACHER_APP& self, decltype(InternalMessage::M2G_MST_SUBMIT_TEACHER_APP::dwTeacherID) value) { self.dwTeacherID = value; });
    internal_message_m2g_mst_submit_teacher_app_type["dwStudentID"] = sol::property([](const InternalMessage::M2G_MST_SUBMIT_TEACHER_APP& self) { return self.dwStudentID; }, [](InternalMessage::M2G_MST_SUBMIT_TEACHER_APP& self, decltype(InternalMessage::M2G_MST_SUBMIT_TEACHER_APP::dwStudentID) value) { self.dwStudentID = value; });
    auto internal_message_m2g_mst_agree_teacher_app_type = cqyh::lua::usertype<InternalMessage::M2G_MST_AGREE_TEACHER_APP>(L, internal_message_namespace, "M2G_MST_AGREE_TEACHER_APP", "InternalMessage::M2G_MST_AGREE_TEACHER_APP", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_mst_agree_teacher_app_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_MST_AGREE_TEACHER_APP(); });
    internal_message_m2g_mst_agree_teacher_app_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_MST_AGREE_TEACHER_APP>(new InternalMessage::M2G_MST_AGREE_TEACHER_APP()); });
    internal_message_m2g_mst_agree_teacher_app_type["dwTeacherID"] = sol::property([](const InternalMessage::M2G_MST_AGREE_TEACHER_APP& self) { return self.dwTeacherID; }, [](InternalMessage::M2G_MST_AGREE_TEACHER_APP& self, decltype(InternalMessage::M2G_MST_AGREE_TEACHER_APP::dwTeacherID) value) { self.dwTeacherID = value; });
    internal_message_m2g_mst_agree_teacher_app_type["dwStudentID"] = sol::property([](const InternalMessage::M2G_MST_AGREE_TEACHER_APP& self) { return self.dwStudentID; }, [](InternalMessage::M2G_MST_AGREE_TEACHER_APP& self, decltype(InternalMessage::M2G_MST_AGREE_TEACHER_APP::dwStudentID) value) { self.dwStudentID = value; });
}

}
