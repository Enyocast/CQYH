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

void register_internal_game_to_manage_economy_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_exchange_add_order_type = cqyh::lua::usertype<InternalMessage::G2M_EXCHANGE_ADD_ORDER>(L, internal_message_namespace, "G2M_EXCHANGE_ADD_ORDER", "InternalMessage::G2M_EXCHANGE_ADD_ORDER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_exchange_add_order_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_EXCHANGE_ADD_ORDER(); });
    internal_message_g2m_exchange_add_order_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_EXCHANGE_ADD_ORDER>(new InternalMessage::G2M_EXCHANGE_ADD_ORDER()); });
    internal_message_g2m_exchange_add_order_type["nResult"] = sol::property([](const InternalMessage::G2M_EXCHANGE_ADD_ORDER& self) { return self.nResult; }, [](InternalMessage::G2M_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::G2M_EXCHANGE_ADD_ORDER::nResult) value) { self.nResult = value; });
    internal_message_g2m_exchange_add_order_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_EXCHANGE_ADD_ORDER& self) { return self.dwRoleID; }, [](InternalMessage::G2M_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::G2M_EXCHANGE_ADD_ORDER::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_exchange_add_order_type["nItemIDRequire"] = sol::property([](const InternalMessage::G2M_EXCHANGE_ADD_ORDER& self) { return self.nItemIDRequire; }, [](InternalMessage::G2M_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::G2M_EXCHANGE_ADD_ORDER::nItemIDRequire) value) { self.nItemIDRequire = value; });
    internal_message_g2m_exchange_add_order_type["nItemCountRequire"] = sol::property([](const InternalMessage::G2M_EXCHANGE_ADD_ORDER& self) { return self.nItemCountRequire; }, [](InternalMessage::G2M_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::G2M_EXCHANGE_ADD_ORDER::nItemCountRequire) value) { self.nItemCountRequire = value; });
    internal_message_g2m_exchange_add_order_type["byOrderType"] = sol::property([](const InternalMessage::G2M_EXCHANGE_ADD_ORDER& self) { return self.byOrderType; }, [](InternalMessage::G2M_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::G2M_EXCHANGE_ADD_ORDER::byOrderType) value) { self.byOrderType = value; });
    internal_message_g2m_exchange_add_order_type["nPriceOrder"] = sol::property([](const InternalMessage::G2M_EXCHANGE_ADD_ORDER& self) { return self.nPriceOrder; }, [](InternalMessage::G2M_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::G2M_EXCHANGE_ADD_ORDER::nPriceOrder) value) { self.nPriceOrder = value; });
    internal_message_g2m_exchange_add_order_type["nCountOrder"] = sol::property([](const InternalMessage::G2M_EXCHANGE_ADD_ORDER& self) { return self.nCountOrder; }, [](InternalMessage::G2M_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::G2M_EXCHANGE_ADD_ORDER::nCountOrder) value) { self.nCountOrder = value; });
    auto internal_message_g2m_query_real_money_ack_type = cqyh::lua::usertype<InternalMessage::G2M_QUERY_REAL_MONEY_ACK>(L, internal_message_namespace, "G2M_QUERY_REAL_MONEY_ACK", "InternalMessage::G2M_QUERY_REAL_MONEY_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_query_real_money_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_QUERY_REAL_MONEY_ACK(); });
    internal_message_g2m_query_real_money_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_QUERY_REAL_MONEY_ACK>(new InternalMessage::G2M_QUERY_REAL_MONEY_ACK()); });
    internal_message_g2m_query_real_money_ack_type["dwCliSessionID"] = sol::property([](const InternalMessage::G2M_QUERY_REAL_MONEY_ACK& self) { return self.dwCliSessionID; }, [](InternalMessage::G2M_QUERY_REAL_MONEY_ACK& self, decltype(InternalMessage::G2M_QUERY_REAL_MONEY_ACK::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_g2m_query_real_money_ack_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_QUERY_REAL_MONEY_ACK& self) { return self.dwRoleID; }, [](InternalMessage::G2M_QUERY_REAL_MONEY_ACK& self, decltype(InternalMessage::G2M_QUERY_REAL_MONEY_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_query_real_money_ack_type["llRealMoney"] = sol::property([](const InternalMessage::G2M_QUERY_REAL_MONEY_ACK& self) { return self.llRealMoney; }, [](InternalMessage::G2M_QUERY_REAL_MONEY_ACK& self, decltype(InternalMessage::G2M_QUERY_REAL_MONEY_ACK::llRealMoney) value) { self.llRealMoney = value; });
    auto internal_message_g2m_role_real_money_shop_buy_ack_type = cqyh::lua::usertype<InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK>(L, internal_message_namespace, "G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK", "InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_role_real_money_shop_buy_ack_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK(); });
    internal_message_g2m_role_real_money_shop_buy_ack_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK>(new InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK()); });
    internal_message_g2m_role_real_money_shop_buy_ack_type["nResult"] = sol::property([](const InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self) { return self.nResult; }, [](InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self, decltype(InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK::nResult) value) { self.nResult = value; });
    internal_message_g2m_role_real_money_shop_buy_ack_type["dwCliSessionID"] = sol::property([](const InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self) { return self.dwCliSessionID; }, [](InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self, decltype(InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK::dwCliSessionID) value) { self.dwCliSessionID = value; });
    internal_message_g2m_role_real_money_shop_buy_ack_type["szRoleName"] = cqyh::lua::array_property(&InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK::szRoleName);
    internal_message_g2m_role_real_money_shop_buy_ack_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self) { return self.dwRoleID; }, [](InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self, decltype(InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_role_real_money_shop_buy_ack_type["nItemID"] = sol::property([](const InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self) { return self.nItemID; }, [](InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self, decltype(InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK::nItemID) value) { self.nItemID = value; });
    internal_message_g2m_role_real_money_shop_buy_ack_type["nItemCount"] = sol::property([](const InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self) { return self.nItemCount; }, [](InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK& self, decltype(InternalMessage::G2M_ROLE_REAL_MONEY_SHOP_BUY_ACK::nItemCount) value) { self.nItemCount = value; });
}

}
