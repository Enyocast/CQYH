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

void register_internal_manage_to_game_auction_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_m2g_auction_sell_type = cqyh::lua::usertype<InternalMessage::M2G_AUCTION_SELL>(L, internal_message_namespace, "M2G_AUCTION_SELL", "InternalMessage::M2G_AUCTION_SELL", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_auction_sell_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_AUCTION_SELL(); });
    internal_message_m2g_auction_sell_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_AUCTION_SELL>(new InternalMessage::M2G_AUCTION_SELL()); });
    internal_message_m2g_auction_sell_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_AUCTION_SELL& self) { return self.dwRoleID; }, [](InternalMessage::M2G_AUCTION_SELL& self, decltype(InternalMessage::M2G_AUCTION_SELL::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_auction_sell_type["byConSlot"] = sol::property([](const InternalMessage::M2G_AUCTION_SELL& self) { return self.byConSlot; }, [](InternalMessage::M2G_AUCTION_SELL& self, decltype(InternalMessage::M2G_AUCTION_SELL::byConSlot) value) { self.byConSlot = value; });
    internal_message_m2g_auction_sell_type["byItemSlot"] = sol::property([](const InternalMessage::M2G_AUCTION_SELL& self) { return self.byItemSlot; }, [](InternalMessage::M2G_AUCTION_SELL& self, decltype(InternalMessage::M2G_AUCTION_SELL::byItemSlot) value) { self.byItemSlot = value; });
    internal_message_m2g_auction_sell_type["byAuctionTimeType"] = sol::property([](const InternalMessage::M2G_AUCTION_SELL& self) { return self.byAuctionTimeType; }, [](InternalMessage::M2G_AUCTION_SELL& self, decltype(InternalMessage::M2G_AUCTION_SELL::byAuctionTimeType) value) { self.byAuctionTimeType = value; });
    internal_message_m2g_auction_sell_type["byOpen"] = sol::property([](const InternalMessage::M2G_AUCTION_SELL& self) { return self.byOpen; }, [](InternalMessage::M2G_AUCTION_SELL& self, decltype(InternalMessage::M2G_AUCTION_SELL::byOpen) value) { self.byOpen = value; });
    internal_message_m2g_auction_sell_type["llPrice"] = sol::property([](const InternalMessage::M2G_AUCTION_SELL& self) { return self.llPrice; }, [](InternalMessage::M2G_AUCTION_SELL& self, decltype(InternalMessage::M2G_AUCTION_SELL::llPrice) value) { self.llPrice = value; });
    internal_message_m2g_auction_sell_type["llBuyoutPrice"] = sol::property([](const InternalMessage::M2G_AUCTION_SELL& self) { return self.llBuyoutPrice; }, [](InternalMessage::M2G_AUCTION_SELL& self, decltype(InternalMessage::M2G_AUCTION_SELL::llBuyoutPrice) value) { self.llBuyoutPrice = value; });
    internal_message_m2g_auction_sell_type["llDepositePrice"] = sol::property([](const InternalMessage::M2G_AUCTION_SELL& self) { return self.llDepositePrice; }, [](InternalMessage::M2G_AUCTION_SELL& self, decltype(InternalMessage::M2G_AUCTION_SELL::llDepositePrice) value) { self.llDepositePrice = value; });
    auto internal_message_m2g_auction_buy_type = cqyh::lua::usertype<InternalMessage::M2G_AUCTION_BUY>(L, internal_message_namespace, "M2G_AUCTION_BUY", "InternalMessage::M2G_AUCTION_BUY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_auction_buy_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_AUCTION_BUY(); });
    internal_message_m2g_auction_buy_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_AUCTION_BUY>(new InternalMessage::M2G_AUCTION_BUY()); });
    internal_message_m2g_auction_buy_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_AUCTION_BUY& self) { return self.dwRoleID; }, [](InternalMessage::M2G_AUCTION_BUY& self, decltype(InternalMessage::M2G_AUCTION_BUY::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_auction_buy_type["dwAuctionID"] = sol::property([](const InternalMessage::M2G_AUCTION_BUY& self) { return self.dwAuctionID; }, [](InternalMessage::M2G_AUCTION_BUY& self, decltype(InternalMessage::M2G_AUCTION_BUY::dwAuctionID) value) { self.dwAuctionID = value; });
    internal_message_m2g_auction_buy_type["llBidPrice"] = sol::property([](const InternalMessage::M2G_AUCTION_BUY& self) { return self.llBidPrice; }, [](InternalMessage::M2G_AUCTION_BUY& self, decltype(InternalMessage::M2G_AUCTION_BUY::llBidPrice) value) { self.llBidPrice = value; });
    internal_message_m2g_auction_buy_type["llAuctionPrice"] = sol::property([](const InternalMessage::M2G_AUCTION_BUY& self) { return self.llAuctionPrice; }, [](InternalMessage::M2G_AUCTION_BUY& self, decltype(InternalMessage::M2G_AUCTION_BUY::llAuctionPrice) value) { self.llAuctionPrice = value; });
    internal_message_m2g_auction_buy_type["llDepositPrice"] = sol::property([](const InternalMessage::M2G_AUCTION_BUY& self) { return self.llDepositPrice; }, [](InternalMessage::M2G_AUCTION_BUY& self, decltype(InternalMessage::M2G_AUCTION_BUY::llDepositPrice) value) { self.llDepositPrice = value; });
    internal_message_m2g_auction_buy_type["byBuyType"] = sol::property([](const InternalMessage::M2G_AUCTION_BUY& self) { return self.byBuyType; }, [](InternalMessage::M2G_AUCTION_BUY& self, decltype(InternalMessage::M2G_AUCTION_BUY::byBuyType) value) { self.byBuyType = value; });
    auto internal_message_m2g_auction_pay_type = cqyh::lua::usertype<InternalMessage::M2G_AUCTION_PAY>(L, internal_message_namespace, "M2G_AUCTION_PAY", "InternalMessage::M2G_AUCTION_PAY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_m2g_auction_pay_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::M2G_AUCTION_PAY(); });
    internal_message_m2g_auction_pay_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::M2G_AUCTION_PAY>(new InternalMessage::M2G_AUCTION_PAY()); });
    internal_message_m2g_auction_pay_type["dwRoleID"] = sol::property([](const InternalMessage::M2G_AUCTION_PAY& self) { return self.dwRoleID; }, [](InternalMessage::M2G_AUCTION_PAY& self, decltype(InternalMessage::M2G_AUCTION_PAY::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_m2g_auction_pay_type["dwAuctionID"] = sol::property([](const InternalMessage::M2G_AUCTION_PAY& self) { return self.dwAuctionID; }, [](InternalMessage::M2G_AUCTION_PAY& self, decltype(InternalMessage::M2G_AUCTION_PAY::dwAuctionID) value) { self.dwAuctionID = value; });
    internal_message_m2g_auction_pay_type["llPrice"] = sol::property([](const InternalMessage::M2G_AUCTION_PAY& self) { return self.llPrice; }, [](InternalMessage::M2G_AUCTION_PAY& self, decltype(InternalMessage::M2G_AUCTION_PAY::llPrice) value) { self.llPrice = value; });
}

}
