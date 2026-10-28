#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../inc/net/internal_message_header.h"
#include "../../../../../inc/net/gmtl_message.h"
#include "../../../../../../Common/define/server_def.h"
#include "../../../../../../Common/define/string_def.h"

namespace cqyh::net_tools::bindings {

void register_internal_gm_tool_inventory_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    sol::table internal_message_namespace = globals["InternalMessage"].get_or_create<sol::table>();
    auto internal_message_item_template_data_type = cqyh::lua::usertype<InternalMessage::ITEM_TEMPLATE_DATA>(L, internal_message_namespace, "ITEM_TEMPLATE_DATA", "InternalMessage::ITEM_TEMPLATE_DATA");
    internal_message_item_template_data_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::ITEM_TEMPLATE_DATA(); });
    internal_message_item_template_data_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::ITEM_TEMPLATE_DATA>(new InternalMessage::ITEM_TEMPLATE_DATA()); });
    internal_message_item_template_data_type["dwTempID"] = sol::property([](const InternalMessage::ITEM_TEMPLATE_DATA& self) { return self.dwTempID; }, [](InternalMessage::ITEM_TEMPLATE_DATA& self, decltype(InternalMessage::ITEM_TEMPLATE_DATA::dwTempID) value) { self.dwTempID = value; });
    internal_message_item_template_data_type["szName"] = cqyh::lua::string_property(&InternalMessage::ITEM_TEMPLATE_DATA::szName);
    auto internal_message_gm2_tl_item_list_ntf_type = cqyh::lua::usertype<InternalMessage::GM2TL_ITEM_LIST_NTF>(L, internal_message_namespace, "GM2TL_ITEM_LIST_NTF", "InternalMessage::GM2TL_ITEM_LIST_NTF", sol::base_classes, sol::bases<InternalMessage::MESSAGE_HEADER>());
    internal_message_gm2_tl_item_list_ntf_type.set_function("new", [](sol::table) -> decltype(auto) { return new InternalMessage::GM2TL_ITEM_LIST_NTF(); });
    internal_message_gm2_tl_item_list_ntf_type.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<InternalMessage::GM2TL_ITEM_LIST_NTF>(new InternalMessage::GM2TL_ITEM_LIST_NTF()); });
    internal_message_gm2_tl_item_list_ntf_type["bCLS"] = sol::property([](const InternalMessage::GM2TL_ITEM_LIST_NTF& self) { return static_cast<bool>(self.bCLS); }, [](InternalMessage::GM2TL_ITEM_LIST_NTF& self, bool value) { self.bCLS = value; });
    internal_message_gm2_tl_item_list_ntf_type["nCount"] = sol::property([](const InternalMessage::GM2TL_ITEM_LIST_NTF& self) { return self.nCount; }, [](InternalMessage::GM2TL_ITEM_LIST_NTF& self, decltype(InternalMessage::GM2TL_ITEM_LIST_NTF::nCount) value) { self.nCount = value; });
    internal_message_gm2_tl_item_list_ntf_type["data"] = cqyh::lua::array_property(&InternalMessage::GM2TL_ITEM_LIST_NTF::data);
}

}
