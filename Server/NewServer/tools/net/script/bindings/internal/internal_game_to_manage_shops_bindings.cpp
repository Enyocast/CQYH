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

void register_internal_game_to_manage_shops_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_get_black_market_limit_info_type = cqyh::lua::usertype<InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO>(L, internal_message_namespace, "G2M_GET_BLACK_MARKET_LIMIT_INFO", "InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_get_black_market_limit_info_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO(); });
    internal_message_g2m_get_black_market_limit_info_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO>(new InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO()); });
    internal_message_g2m_get_black_market_limit_info_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO& self) { return self.dwRoleID; }, [](InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO& self, decltype(InternalMessage::G2M_GET_BLACK_MARKET_LIMIT_INFO::dwRoleID) value) { self.dwRoleID = value; });
    auto internal_message_g2m_check_black_market_product_type = cqyh::lua::usertype<InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT>(L, internal_message_namespace, "G2M_CHECK_BLACK_MARKET_PRODUCT", "InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_check_black_market_product_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT(); });
    internal_message_g2m_check_black_market_product_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT>(new InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT()); });
    internal_message_g2m_check_black_market_product_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT& self) { return self.dwRoleID; }, [](InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT& self, decltype(InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_check_black_market_product_type["nBlackMarketProductID"] = sol::property([](const InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT& self) { return self.nBlackMarketProductID; }, [](InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT& self, decltype(InternalMessage::G2M_CHECK_BLACK_MARKET_PRODUCT::nBlackMarketProductID) value) { self.nBlackMarketProductID = value; });
}

}
