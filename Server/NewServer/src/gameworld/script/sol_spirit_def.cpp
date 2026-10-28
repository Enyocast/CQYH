#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../../Common/define/spirit_def.h"

int sol_spirit_def_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["SPIRIT_OPEN_LEVEL"] = static_cast<lua_Number>(SPIRIT_OPEN_LEVEL);
    globals["MAX_EXT2PTS_MULTIPLE"] = static_cast<lua_Number>(MAX_EXT2PTS_MULTIPLE);
    globals["MAX_EXP2PTS_THRESHOLD"] = static_cast<lua_Number>(MAX_EXP2PTS_THRESHOLD);
    globals["MAX_SPIRIT_LEVEL"] = static_cast<lua_Number>(MAX_SPIRIT_LEVEL);
    globals["MAX_SPIRIT_NODE_PER_LEVEL"] = static_cast<lua_Number>(MAX_SPIRIT_NODE_PER_LEVEL);
    globals["MAX_AIRSEA_BAG_CONTAINER_SIZE"] = static_cast<lua_Number>(MAX_AIRSEA_BAG_CONTAINER_SIZE);
    globals["MAX_AIRSEA_STALL_CONTAINER_SIZE"] = static_cast<lua_Number>(MAX_AIRSEA_STALL_CONTAINER_SIZE);
    globals["MAX_AIRSEA_EQUIP_CONTAINER_SIZE"] = static_cast<lua_Number>(MAX_AIRSEA_EQUIP_CONTAINER_SIZE);
    globals["MAX_AIR_PROCEDURE"] = static_cast<lua_Number>(MAX_AIR_PROCEDURE);
    globals["MAX_DROP_AIR_COUNT"] = static_cast<lua_Number>(MAX_DROP_AIR_COUNT);
    globals["MAX_AIR_LEVEL"] = static_cast<lua_Number>(MAX_AIR_LEVEL);
    globals["MAX_AIR_NODE"] = static_cast<lua_Number>(MAX_AIR_NODE);
    globals["MAX_ATTR_PER_NODE"] = static_cast<lua_Number>(MAX_ATTR_PER_NODE);
    globals["MAX_SPIRIT_BUY_SLOT_COST"] = static_cast<lua_Number>(MAX_SPIRIT_BUY_SLOT_COST);
    globals["INVALID_AIR_ID"] = static_cast<lua_Number>(INVALID_AIR_ID);
    globals["INVALID_AIR_INDEX"] = static_cast<lua_Number>(INVALID_AIR_INDEX);
    globals["MAX_EXP2PTS_LEVEL"] = static_cast<lua_Number>(MAX_EXP2PTS_LEVEL);
    globals["MAX_BLOODSEA_PAGE"] = static_cast<lua_Number>(MAX_BLOODSEA_PAGE);
    globals["MAX_BLOODSEA_SLOT_PER_PAGE"] = static_cast<lua_Number>(MAX_BLOODSEA_SLOT_PER_PAGE);
    globals["MAX_BLOODSEA_SLOT_NUMBER"] = static_cast<lua_Number>(MAX_BLOODSEA_SLOT_NUMBER);
    globals["MAX_BLOODSEA_ATTR_PER_SLOT"] = static_cast<lua_Number>(MAX_BLOODSEA_ATTR_PER_SLOT);
    globals["BLOODSEA_SLOT_INIT_SLOT"] = static_cast<lua_Number>(BLOODSEA_SLOT_INIT_SLOT);
    globals["sasbtInvalid"] = static_cast<lua_Number>(sasbtInvalid);
    globals["sasbtBag"] = static_cast<lua_Number>(sasbtBag);
    globals["sasbtStall"] = static_cast<lua_Number>(sasbtStall);
    globals["sasbtEquip"] = static_cast<lua_Number>(sasbtEquip);
    globals["sasbtTotal"] = static_cast<lua_Number>(sasbtTotal);
    globals["spiritInvalid"] = static_cast<lua_Number>(spiritInvalid);
    globals["spiritPower"] = static_cast<lua_Number>(spiritPower);
    globals["spiritSwift"] = static_cast<lua_Number>(spiritSwift);
    globals["spiritWise"] = static_cast<lua_Number>(spiritWise);
    globals["spiritBody"] = static_cast<lua_Number>(spiritBody);
    globals["spiritDivine"] = static_cast<lua_Number>(spiritDivine);
    globals["spiritKing"] = static_cast<lua_Number>(spiritKing);
    globals.set_function("MAKE_AIR_LEVEL_KEY", [](INT32 nLevel, INT32 nClass) -> decltype(auto) { return MAKE_AIR_LEVEL_KEY(nLevel,nClass); });
    globals.set_function("MAKE_BLOOD_KEY", [](INT32 nPage, INT32 nIndex, INT32 nNumber) -> decltype(auto) { return MAKE_BLOOD_KEY(nPage,nIndex,nNumber); });
    return 1;
}
