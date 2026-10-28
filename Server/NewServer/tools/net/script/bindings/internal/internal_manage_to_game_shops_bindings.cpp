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

void register_internal_manage_to_game_shops_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_black_market_limit_info_type = cqyh::lua::usertype<InternalMessage::BLACK_MARKET_LIMIT_INFO>(L, internal_message_namespace, "BLACK_MARKET_LIMIT_INFO", "InternalMessage::BLACK_MARKET_LIMIT_INFO");
    internal_message_black_market_limit_info_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::BLACK_MARKET_LIMIT_INFO(); });
    internal_message_black_market_limit_info_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::BLACK_MARKET_LIMIT_INFO>(new InternalMessage::BLACK_MARKET_LIMIT_INFO()); });
    internal_message_black_market_limit_info_type["nBlackMarketProductID"] = sol::property([](const InternalMessage::BLACK_MARKET_LIMIT_INFO& self) { return self.nBlackMarketProductID; }, [](InternalMessage::BLACK_MARKET_LIMIT_INFO& self, decltype(InternalMessage::BLACK_MARKET_LIMIT_INFO::nBlackMarketProductID) value) { self.nBlackMarketProductID = value; });
    internal_message_black_market_limit_info_type["dwCount"] = sol::property([](const InternalMessage::BLACK_MARKET_LIMIT_INFO& self) { return self.dwCount; }, [](InternalMessage::BLACK_MARKET_LIMIT_INFO& self, decltype(InternalMessage::BLACK_MARKET_LIMIT_INFO::dwCount) value) { self.dwCount = value; });
    auto internal_message_m2g_get_black_market_limit_info_type = cqyh::lua::usertype<InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO>(L, internal_message_namespace, "M2G_GET_BLACK_MARKET_LIMIT_INFO", "InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_get_black_market_limit_info_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO(); });
    internal_message_m2g_get_black_market_limit_info_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO>(new InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO()); });
    internal_message_m2g_get_black_market_limit_info_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO& self) { return self.dwRoleID; }, [](InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO& self, decltype(InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_get_black_market_limit_info_type["nLimitInfoCount"] = sol::property([](const InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO& self) { return self.nLimitInfoCount; }, [](InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO& self, decltype(InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO::nLimitInfoCount) value) { self.nLimitInfoCount = value; });
    internal_message_m2g_get_black_market_limit_info_type["LimitInfo"] = cqyh::lua::array_property(&InternalMessage::M2G_GET_BLACK_MARKET_LIMIT_INFO::LimitInfo);
    auto internal_message_m2g_check_black_market_product_type = cqyh::lua::usertype<InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT>(L, internal_message_namespace, "M2G_CHECK_BLACK_MARKET_PRODUCT", "InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_check_black_market_product_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT(); });
    internal_message_m2g_check_black_market_product_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT>(new InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT()); });
    internal_message_m2g_check_black_market_product_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT& self) { return self.dwRoleID; }, [](InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT& self, decltype(InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_check_black_market_product_type["nBlackMarketProductID"] = sol::property([](const InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT& self) { return self.nBlackMarketProductID; }, [](InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT& self, decltype(InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT::nBlackMarketProductID) value) { self.nBlackMarketProductID = value; });
    internal_message_m2g_check_black_market_product_type["nResult"] = sol::property([](const InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT& self) { return self.nResult; }, [](InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT& self, decltype(InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT::nResult) value) { self.nResult = value; });
    internal_message_m2g_check_black_market_product_type["nCount"] = sol::property([](const InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT& self) { return self.nCount; }, [](InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT& self, decltype(InternalMessage::M2G_CHECK_BLACK_MARKET_PRODUCT::nCount) value) { self.nCount = value; });
}

}
