#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/g2m_message.h"
#include "../../../../../../Common/define/friend_def.h"
#include "../../../../../../Common/define/guild_def.h"
#include "../../../../../../Common/define/master_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net::bindings {

void register_internal_game_to_manage_loot_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_drop_limit_type = cqyh::lua::usertype<InternalMessage::G2M_DROP_LIMIT>(L, internal_message_namespace, "G2M_DROP_LIMIT", "InternalMessage::G2M_DROP_LIMIT", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_drop_limit_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_DROP_LIMIT(); });
    internal_message_g2m_drop_limit_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_DROP_LIMIT>(new InternalMessage::G2M_DROP_LIMIT()); });
    internal_message_g2m_drop_limit_type["nItemID"] = sol::property([](const InternalMessage::G2M_DROP_LIMIT& self) { return self.nItemID; }, [](InternalMessage::G2M_DROP_LIMIT& self, decltype(InternalMessage::G2M_DROP_LIMIT::nItemID) value) { self.nItemID = value; });
    internal_message_g2m_drop_limit_type["nDropCount"] = sol::property([](const InternalMessage::G2M_DROP_LIMIT& self) { return self.nDropCount; }, [](InternalMessage::G2M_DROP_LIMIT& self, decltype(InternalMessage::G2M_DROP_LIMIT::nDropCount) value) { self.nDropCount = value; });
}

}
