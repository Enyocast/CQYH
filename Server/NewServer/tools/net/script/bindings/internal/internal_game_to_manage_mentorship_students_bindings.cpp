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

void register_internal_game_to_manage_mentorship_students_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_mst_submit_stud_app_ack_type = cqyh::lua::usertype<InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK>(L, internal_message_namespace, "G2M_MST_SUBMIT_STUD_APP_ACK", "InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_mst_submit_stud_app_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK(); });
    internal_message_g2m_mst_submit_stud_app_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK>(new InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK()); });
    internal_message_g2m_mst_submit_stud_app_ack_type["dwTeacherID"] = sol::property([](const InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK& self) { return self.dwTeacherID; }, [](InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK& self, decltype(InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK::dwTeacherID) value) { self.dwTeacherID = value; });
    internal_message_g2m_mst_submit_stud_app_ack_type["dwStudentID"] = sol::property([](const InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK& self) { return self.dwStudentID; }, [](InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK& self, decltype(InternalMessage::G2M_MST_SUBMIT_STUD_APP_ACK::dwStudentID) value) { self.dwStudentID = value; });
    auto internal_message_g2m_mst_agree_stud_app_ack_type = cqyh::lua::usertype<InternalMessage::G2M_MST_AGREE_STUD_APP_ACK>(L, internal_message_namespace, "G2M_MST_AGREE_STUD_APP_ACK", "InternalMessage::G2M_MST_AGREE_STUD_APP_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_mst_agree_stud_app_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_MST_AGREE_STUD_APP_ACK(); });
    internal_message_g2m_mst_agree_stud_app_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_MST_AGREE_STUD_APP_ACK>(new InternalMessage::G2M_MST_AGREE_STUD_APP_ACK()); });
    internal_message_g2m_mst_agree_stud_app_ack_type["dwTeacherID"] = sol::property([](const InternalMessage::G2M_MST_AGREE_STUD_APP_ACK& self) { return self.dwTeacherID; }, [](InternalMessage::G2M_MST_AGREE_STUD_APP_ACK& self, decltype(InternalMessage::G2M_MST_AGREE_STUD_APP_ACK::dwTeacherID) value) { self.dwTeacherID = value; });
    internal_message_g2m_mst_agree_stud_app_ack_type["dwStudentID"] = sol::property([](const InternalMessage::G2M_MST_AGREE_STUD_APP_ACK& self) { return self.dwStudentID; }, [](InternalMessage::G2M_MST_AGREE_STUD_APP_ACK& self, decltype(InternalMessage::G2M_MST_AGREE_STUD_APP_ACK::dwStudentID) value) { self.dwStudentID = value; });
}

}
