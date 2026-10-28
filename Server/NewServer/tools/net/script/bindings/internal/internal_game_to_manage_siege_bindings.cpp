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

void register_internal_game_to_manage_siege_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_enroll_sabac_type = cqyh::lua::usertype<InternalMessage::G2M_ENROLL_SABAC>(L, internal_message_namespace, "G2M_ENROLL_SABAC", "InternalMessage::G2M_ENROLL_SABAC", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_enroll_sabac_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ENROLL_SABAC(); });
    internal_message_g2m_enroll_sabac_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ENROLL_SABAC>(new InternalMessage::G2M_ENROLL_SABAC()); });
    internal_message_g2m_enroll_sabac_type["dwGuildID"] = sol::property([](const InternalMessage::G2M_ENROLL_SABAC& self) { return self.dwGuildID; }, [](InternalMessage::G2M_ENROLL_SABAC& self, decltype(InternalMessage::G2M_ENROLL_SABAC::dwGuildID) value) { self.dwGuildID = value; });
    internal_message_g2m_enroll_sabac_type["dwEnrollTime"] = sol::property([](const InternalMessage::G2M_ENROLL_SABAC& self) { return self.dwEnrollTime; }, [](InternalMessage::G2M_ENROLL_SABAC& self, decltype(InternalMessage::G2M_ENROLL_SABAC::dwEnrollTime) value) { self.dwEnrollTime = value; });
    auto internal_message_g2m_occupy_sabac_type = cqyh::lua::usertype<InternalMessage::G2M_OCCUPY_SABAC>(L, internal_message_namespace, "G2M_OCCUPY_SABAC", "InternalMessage::G2M_OCCUPY_SABAC", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_occupy_sabac_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_OCCUPY_SABAC(); });
    internal_message_g2m_occupy_sabac_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_OCCUPY_SABAC>(new InternalMessage::G2M_OCCUPY_SABAC()); });
    internal_message_g2m_occupy_sabac_type["byServerGroup"] = sol::property([](const InternalMessage::G2M_OCCUPY_SABAC& self) { return self.byServerGroup; }, [](InternalMessage::G2M_OCCUPY_SABAC& self, decltype(InternalMessage::G2M_OCCUPY_SABAC::byServerGroup) value) { self.byServerGroup = value; });
    internal_message_g2m_occupy_sabac_type["dwOldGuildID"] = sol::property([](const InternalMessage::G2M_OCCUPY_SABAC& self) { return self.dwOldGuildID; }, [](InternalMessage::G2M_OCCUPY_SABAC& self, decltype(InternalMessage::G2M_OCCUPY_SABAC::dwOldGuildID) value) { self.dwOldGuildID = value; });
    internal_message_g2m_occupy_sabac_type["dwNewGuildID"] = sol::property([](const InternalMessage::G2M_OCCUPY_SABAC& self) { return self.dwNewGuildID; }, [](InternalMessage::G2M_OCCUPY_SABAC& self, decltype(InternalMessage::G2M_OCCUPY_SABAC::dwNewGuildID) value) { self.dwNewGuildID = value; });
    auto internal_message_g2m_erect_statue_type = cqyh::lua::usertype<InternalMessage::G2M_ERECT_STATUE>(L, internal_message_namespace, "G2M_ERECT_STATUE", "InternalMessage::G2M_ERECT_STATUE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_erect_statue_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ERECT_STATUE(); });
    internal_message_g2m_erect_statue_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ERECT_STATUE>(new InternalMessage::G2M_ERECT_STATUE()); });
    internal_message_g2m_erect_statue_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ERECT_STATUE& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ERECT_STATUE& self, decltype(InternalMessage::G2M_ERECT_STATUE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_erect_statue_type["byHairType"] = sol::property([](const InternalMessage::G2M_ERECT_STATUE& self) { return self.byHairType; }, [](InternalMessage::G2M_ERECT_STATUE& self, decltype(InternalMessage::G2M_ERECT_STATUE::byHairType) value) { self.byHairType = value; });
    internal_message_g2m_erect_statue_type["byHairColor"] = sol::property([](const InternalMessage::G2M_ERECT_STATUE& self) { return self.byHairColor; }, [](InternalMessage::G2M_ERECT_STATUE& self, decltype(InternalMessage::G2M_ERECT_STATUE::byHairColor) value) { self.byHairColor = value; });
    internal_message_g2m_erect_statue_type["byFaceType"] = sol::property([](const InternalMessage::G2M_ERECT_STATUE& self) { return self.byFaceType; }, [](InternalMessage::G2M_ERECT_STATUE& self, decltype(InternalMessage::G2M_ERECT_STATUE::byFaceType) value) { self.byFaceType = value; });
    internal_message_g2m_erect_statue_type["bySkinColor"] = sol::property([](const InternalMessage::G2M_ERECT_STATUE& self) { return self.bySkinColor; }, [](InternalMessage::G2M_ERECT_STATUE& self, decltype(InternalMessage::G2M_ERECT_STATUE::bySkinColor) value) { self.bySkinColor = value; });
    internal_message_g2m_erect_statue_type["byTitleID"] = sol::property([](const InternalMessage::G2M_ERECT_STATUE& self) { return self.byTitleID; }, [](InternalMessage::G2M_ERECT_STATUE& self, decltype(InternalMessage::G2M_ERECT_STATUE::byTitleID) value) { self.byTitleID = value; });
    internal_message_g2m_erect_statue_type["byRefineFx"] = sol::property([](const InternalMessage::G2M_ERECT_STATUE& self) { return self.byRefineFx; }, [](InternalMessage::G2M_ERECT_STATUE& self, decltype(InternalMessage::G2M_ERECT_STATUE::byRefineFx) value) { self.byRefineFx = value; });
    internal_message_g2m_erect_statue_type["anAvatar"] = cqyh::lua::array_property(&InternalMessage::G2M_ERECT_STATUE::anAvatar);
}

}
