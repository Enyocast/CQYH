#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/cer_message.h"

namespace cqyh::net::bindings {

void register_internal_certification_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    internal_message_namespace["cer_begin"] = static_cast<lua_Number>(InternalMessage::cer_begin);
    internal_message_namespace["cer_sync_certification"] = static_cast<lua_Number>(InternalMessage::cer_sync_certification);
    internal_message_namespace["cer_end"] = static_cast<lua_Number>(InternalMessage::cer_end);
    auto internal_message_cer_sync_certification_type = cqyh::lua::usertype<InternalMessage::CER_SYNC_CERTIFICATION>(L, internal_message_namespace, "CER_SYNC_CERTIFICATION", "InternalMessage::CER_SYNC_CERTIFICATION", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_cer_sync_certification_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::CER_SYNC_CERTIFICATION(); });
    internal_message_cer_sync_certification_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::CER_SYNC_CERTIFICATION>(new InternalMessage::CER_SYNC_CERTIFICATION()); });
    internal_message_cer_sync_certification_type["byKey"] = sol::property([](const InternalMessage::CER_SYNC_CERTIFICATION& self) { return self.byKey; }, [](InternalMessage::CER_SYNC_CERTIFICATION& self, decltype(InternalMessage::CER_SYNC_CERTIFICATION::byKey) value) { self.byKey = value; });
    internal_message_cer_sync_certification_type["szMathTable"] = cqyh::lua::string_property(&InternalMessage::CER_SYNC_CERTIFICATION::szMathTable);
}

}
