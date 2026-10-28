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

void register_internal_manage_to_game_economy_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_exchange_add_order_type = cqyh::lua::usertype<InternalMessage::M2G_EXCHANGE_ADD_ORDER>(L, internal_message_namespace, "M2G_EXCHANGE_ADD_ORDER", "InternalMessage::M2G_EXCHANGE_ADD_ORDER", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_exchange_add_order_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_EXCHANGE_ADD_ORDER(); });
    internal_message_m2g_exchange_add_order_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_EXCHANGE_ADD_ORDER>(new InternalMessage::M2G_EXCHANGE_ADD_ORDER()); });
    internal_message_m2g_exchange_add_order_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_EXCHANGE_ADD_ORDER& self) { return self.dwRoleID; }, [](InternalMessage::M2G_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::M2G_EXCHANGE_ADD_ORDER::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_exchange_add_order_type["nItemIDRequire"] = sol::property([](const InternalMessage::M2G_EXCHANGE_ADD_ORDER& self) { return self.nItemIDRequire; }, [](InternalMessage::M2G_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::M2G_EXCHANGE_ADD_ORDER::nItemIDRequire) value) { self.nItemIDRequire = value; });
    internal_message_m2g_exchange_add_order_type["nItemCountRequire"] = sol::property([](const InternalMessage::M2G_EXCHANGE_ADD_ORDER& self) { return self.nItemCountRequire; }, [](InternalMessage::M2G_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::M2G_EXCHANGE_ADD_ORDER::nItemCountRequire) value) { self.nItemCountRequire = value; });
    internal_message_m2g_exchange_add_order_type["byOrderType"] = sol::property([](const InternalMessage::M2G_EXCHANGE_ADD_ORDER& self) { return self.byOrderType; }, [](InternalMessage::M2G_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::M2G_EXCHANGE_ADD_ORDER::byOrderType) value) { self.byOrderType = value; });
    internal_message_m2g_exchange_add_order_type["nPriceOrder"] = sol::property([](const InternalMessage::M2G_EXCHANGE_ADD_ORDER& self) { return self.nPriceOrder; }, [](InternalMessage::M2G_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::M2G_EXCHANGE_ADD_ORDER::nPriceOrder) value) { self.nPriceOrder = value; });
    internal_message_m2g_exchange_add_order_type["nCountOrder"] = sol::property([](const InternalMessage::M2G_EXCHANGE_ADD_ORDER& self) { return self.nCountOrder; }, [](InternalMessage::M2G_EXCHANGE_ADD_ORDER& self, decltype(InternalMessage::M2G_EXCHANGE_ADD_ORDER::nCountOrder) value) { self.nCountOrder = value; });
    auto internal_message_m2g_real_money_buy_success_type = cqyh::lua::usertype<InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS>(L, internal_message_namespace, "M2G_REAL_MONEY_BUY_SUCCESS", "InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_real_money_buy_success_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS(); });
    internal_message_m2g_real_money_buy_success_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS>(new InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS()); });
    internal_message_m2g_real_money_buy_success_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self) { return self.dwRoleID; }, [](InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self, decltype(InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_real_money_buy_success_type["nItemID"] = sol::property([](const InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self) { return self.nItemID; }, [](InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self, decltype(InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS::nItemID) value) { self.nItemID = value; });
    internal_message_m2g_real_money_buy_success_type["nStackCount"] = sol::property([](const InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self) { return self.nStackCount; }, [](InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self, decltype(InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS::nStackCount) value) { self.nStackCount = value; });
    internal_message_m2g_real_money_buy_success_type["nItemCount"] = sol::property([](const InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self) { return self.nItemCount; }, [](InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self, decltype(InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS::nItemCount) value) { self.nItemCount = value; });
    internal_message_m2g_real_money_buy_success_type["nOriginalPrice"] = sol::property([](const InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self) { return self.nOriginalPrice; }, [](InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self, decltype(InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS::nOriginalPrice) value) { self.nOriginalPrice = value; });
    internal_message_m2g_real_money_buy_success_type["szGiverRoleName"] = cqyh::lua::string_property(&InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS::szGiverRoleName);
    internal_message_m2g_real_money_buy_success_type["dwGiveRoleID"] = sol::property([](const InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self) { return self.dwGiveRoleID; }, [](InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS& self, decltype(InternalMessage::M2G_REAL_MONEY_BUY_SUCCESS::dwGiveRoleID) value) { self.dwGiveRoleID = value; });
    auto internal_message_m2g_fcm_state_type = cqyh::lua::usertype<InternalMessage::M2G_FCM_STATE>(L, internal_message_namespace, "M2G_FCM_STATE", "InternalMessage::M2G_FCM_STATE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_fcm_state_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_FCM_STATE(); });
    internal_message_m2g_fcm_state_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_FCM_STATE>(new InternalMessage::M2G_FCM_STATE()); });
    internal_message_m2g_fcm_state_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_FCM_STATE& self) { return self.dwRoleID; }, [](InternalMessage::M2G_FCM_STATE& self, decltype(InternalMessage::M2G_FCM_STATE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_fcm_state_type["byFcmState"] = sol::property([](const InternalMessage::M2G_FCM_STATE& self) { return self.byFcmState; }, [](InternalMessage::M2G_FCM_STATE& self, decltype(InternalMessage::M2G_FCM_STATE::byFcmState) value) { self.byFcmState = value; });
    auto internal_message_m2g_free_mode_type = cqyh::lua::usertype<InternalMessage::M2G_FREE_MODE>(L, internal_message_namespace, "M2G_FREE_MODE", "InternalMessage::M2G_FREE_MODE", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_free_mode_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_FREE_MODE(); });
    internal_message_m2g_free_mode_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_FREE_MODE>(new InternalMessage::M2G_FREE_MODE()); });
    internal_message_m2g_free_mode_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_FREE_MODE& self) { return self.dwRoleID; }, [](InternalMessage::M2G_FREE_MODE& self, decltype(InternalMessage::M2G_FREE_MODE::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_free_mode_type["byFreeMode"] = sol::property([](const InternalMessage::M2G_FREE_MODE& self) { return self.byFreeMode; }, [](InternalMessage::M2G_FREE_MODE& self, decltype(InternalMessage::M2G_FREE_MODE::byFreeMode) value) { self.byFreeMode = value; });
}

}
