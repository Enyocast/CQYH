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

void register_internal_game_to_manage_auction_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_g2m_auction_sell_type = cqyh::lua::usertype<InternalMessage::G2M_AUCTION_SELL>(L, internal_message_namespace, "G2M_AUCTION_SELL", "InternalMessage::G2M_AUCTION_SELL", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_auction_sell_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_AUCTION_SELL(); });
    internal_message_g2m_auction_sell_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_AUCTION_SELL>(new InternalMessage::G2M_AUCTION_SELL()); });
    internal_message_g2m_auction_sell_type["nResult"] = sol::property([](const InternalMessage::G2M_AUCTION_SELL& self) { return self.nResult; }, [](InternalMessage::G2M_AUCTION_SELL& self, decltype(InternalMessage::G2M_AUCTION_SELL::nResult) value) { self.nResult = value; });
    internal_message_g2m_auction_sell_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_AUCTION_SELL& self) { return self.dwRoleID; }, [](InternalMessage::G2M_AUCTION_SELL& self, decltype(InternalMessage::G2M_AUCTION_SELL::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_auction_sell_type["nPrice"] = sol::property([](const InternalMessage::G2M_AUCTION_SELL& self) { return self.nPrice; }, [](InternalMessage::G2M_AUCTION_SELL& self, decltype(InternalMessage::G2M_AUCTION_SELL::nPrice) value) { self.nPrice = value; });
    internal_message_g2m_auction_sell_type["nBuyoutPrice"] = sol::property([](const InternalMessage::G2M_AUCTION_SELL& self) { return self.nBuyoutPrice; }, [](InternalMessage::G2M_AUCTION_SELL& self, decltype(InternalMessage::G2M_AUCTION_SELL::nBuyoutPrice) value) { self.nBuyoutPrice = value; });
    internal_message_g2m_auction_sell_type["acItem"] = cqyh::lua::string_property(&InternalMessage::G2M_AUCTION_SELL::acItem);
    auto internal_message_g2m_auction_buy_type = cqyh::lua::usertype<InternalMessage::G2M_AUCTION_BUY>(L, internal_message_namespace, "G2M_AUCTION_BUY", "InternalMessage::G2M_AUCTION_BUY", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_g2m_auction_buy_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::G2M_AUCTION_BUY(); });
    internal_message_g2m_auction_buy_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::G2M_AUCTION_BUY>(new InternalMessage::G2M_AUCTION_BUY()); });
    internal_message_g2m_auction_buy_type["nResult"] = sol::property([](const InternalMessage::G2M_AUCTION_BUY& self) { return self.nResult; }, [](InternalMessage::G2M_AUCTION_BUY& self, decltype(InternalMessage::G2M_AUCTION_BUY::nResult) value) { self.nResult = value; });
    internal_message_g2m_auction_buy_type["dwRoleID"] = sol::property([](const InternalMessage::G2M_AUCTION_BUY& self) { return self.dwRoleID; }, [](InternalMessage::G2M_AUCTION_BUY& self, decltype(InternalMessage::G2M_AUCTION_BUY::dwRoleID) value) { self.dwRoleID = value; });
    internal_message_g2m_auction_buy_type["dwAuctionID"] = sol::property([](const InternalMessage::G2M_AUCTION_BUY& self) { return self.dwAuctionID; }, [](InternalMessage::G2M_AUCTION_BUY& self, decltype(InternalMessage::G2M_AUCTION_BUY::dwAuctionID) value) { self.dwAuctionID = value; });
    internal_message_g2m_auction_buy_type["nPrice"] = sol::property([](const InternalMessage::G2M_AUCTION_BUY& self) { return self.nPrice; }, [](InternalMessage::G2M_AUCTION_BUY& self, decltype(InternalMessage::G2M_AUCTION_BUY::nPrice) value) { self.nPrice = value; });
}

}
