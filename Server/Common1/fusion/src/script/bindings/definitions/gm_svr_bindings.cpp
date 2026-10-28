#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/gm_svr_def.h"

namespace cqyh::fusion::bindings {

void register_gm_svr_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_GM_USER"] = static_cast<lua_Number>(MAX_GM_USER);
    globals["MAX_ITEM_BUFFER_SIZE"] = static_cast<lua_Number>(MAX_ITEM_BUFFER_SIZE);
    globals["MAX_GMSVR_ROLE_KEY_NUM"] = static_cast<lua_Number>(MAX_GMSVR_ROLE_KEY_NUM);
    globals["GM_CMD_NONE"] = static_cast<lua_Number>(GM_CMD_NONE);
    globals["GM_CMD_PRE_QUERY"] = static_cast<lua_Number>(GM_CMD_PRE_QUERY);
    globals["GM_CMD_QUERY_ROLE_ID"] = static_cast<lua_Number>(GM_CMD_QUERY_ROLE_ID);
    globals["GM_CMD_QUERY_ROLE_DATA"] = static_cast<lua_Number>(GM_CMD_QUERY_ROLE_DATA);
    globals["GM_CMD_FORBID_CHAT"] = static_cast<lua_Number>(GM_CMD_FORBID_CHAT);
    globals["GM_CMD_FREEZE_ROLE"] = static_cast<lua_Number>(GM_CMD_FREEZE_ROLE);
    globals["GM_CMD_KICK_ROLE"] = static_cast<lua_Number>(GM_CMD_KICK_ROLE);
    globals["GM_CMD_ANNOUNCE"] = static_cast<lua_Number>(GM_CMD_ANNOUNCE);
    globals["GM_CMD_GET_ANNOUNCE_LIST"] = static_cast<lua_Number>(GM_CMD_GET_ANNOUNCE_LIST);
    globals["GM_CMD_DEL_ANNOUNCE"] = static_cast<lua_Number>(GM_CMD_DEL_ANNOUNCE);
    globals["GM_CMD_SEND_MAIL"] = static_cast<lua_Number>(GM_CMD_SEND_MAIL);
    globals["GM_CMD_LOG"] = static_cast<lua_Number>(GM_CMD_LOG);
    globals["GM_CMD_EXE_GM_STR"] = static_cast<lua_Number>(GM_CMD_EXE_GM_STR);
    globals["GM_CMD_LOAD_ROLE"] = static_cast<lua_Number>(GM_CMD_LOAD_ROLE);
    globals["GM_CMD_MODIFY_ROLE"] = static_cast<lua_Number>(GM_CMD_MODIFY_ROLE);
    globals["GM_CMD_QUERY_NAME_TO_ID"] = static_cast<lua_Number>(GM_CMD_QUERY_NAME_TO_ID);
    globals["GM_CMD_ROLE_EXE_GM_CMD"] = static_cast<lua_Number>(GM_CMD_ROLE_EXE_GM_CMD);
    globals["GM_CMD_SYS_EXCHANGE_INFO"] = static_cast<lua_Number>(GM_CMD_SYS_EXCHANGE_INFO);
    globals["GM_CMD_NUM"] = static_cast<lua_Number>(GM_CMD_NUM);
    globals["CMD_STEP_1"] = static_cast<lua_Number>(CMD_STEP_1);
    globals["CMD_STEP_2"] = static_cast<lua_Number>(CMD_STEP_2);
    globals["CMD_STEP_3"] = static_cast<lua_Number>(CMD_STEP_3);
    globals["CMD_STEP_4"] = static_cast<lua_Number>(CMD_STEP_4);
    globals["CMD_STEP_5"] = static_cast<lua_Number>(CMD_STEP_5);
    globals["CMD_STEP_6"] = static_cast<lua_Number>(CMD_STEP_6);
    globals["CMD_STEP_7"] = static_cast<lua_Number>(CMD_STEP_7);
    globals["CMD_STEP_8"] = static_cast<lua_Number>(CMD_STEP_8);
    globals["GM_RECORD_FORBID_CHAT"] = static_cast<lua_Number>(GM_RECORD_FORBID_CHAT);
    globals["GM_RECORD_FREEZE_ROLE"] = static_cast<lua_Number>(GM_RECORD_FREEZE_ROLE);
    globals["GM_RECORD_FREEZE_CHEAT_ROLE"] = static_cast<lua_Number>(GM_RECORD_FREEZE_CHEAT_ROLE);
    globals["TL_STATE_BUSY"] = static_cast<lua_Number>(TL_STATE_BUSY);
    globals["TL_STATE_IDLE"] = static_cast<lua_Number>(TL_STATE_IDLE);
    globals["GM_ROLE_PRE_LOCK"] = static_cast<lua_Number>(GM_ROLE_PRE_LOCK);
    globals["GM_ROLE_LOCK"] = static_cast<lua_Number>(GM_ROLE_LOCK);
    globals["GM_ROLE_PRE_UNLOCK"] = static_cast<lua_Number>(GM_ROLE_PRE_UNLOCK);
    globals["GM_ROLE_UNLOCK"] = static_cast<lua_Number>(GM_ROLE_UNLOCK);
    globals["GM_PERMISSION_A"] = static_cast<lua_Number>(GM_PERMISSION_A);
    globals["GM_PERMISSION_PM"] = static_cast<lua_Number>(GM_PERMISSION_PM);
    globals["GM_PERMISSION_3"] = static_cast<lua_Number>(GM_PERMISSION_3);
    globals["GM_PERMISSION_4"] = static_cast<lua_Number>(GM_PERMISSION_4);
    globals["GM_PERMISSION_L"] = static_cast<lua_Number>(GM_PERMISSION_L);
    globals["GM_PERMISSION_6"] = static_cast<lua_Number>(GM_PERMISSION_6);
    globals["GM_PERMISSION_GM"] = static_cast<lua_Number>(GM_PERMISSION_GM);
    globals["GM_PERMISSION_8"] = static_cast<lua_Number>(GM_PERMISSION_8);
    globals["GM_PERMISSION_9"] = static_cast<lua_Number>(GM_PERMISSION_9);
    globals["GM_PERMISSION_GUEST"] = static_cast<lua_Number>(GM_PERMISSION_GUEST);
}

}
