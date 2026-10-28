#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/doodad_def.h"

namespace cqyh::gen_msg::bindings {

void register_doodad_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_DOODAD_LEVEL"] = static_cast<lua_Number>(MAX_DOODAD_LEVEL);
    sol::table doodad_type_namespace = globals["DOODAD_TYPE"].get_or_create<sol::table>();
    doodad_type_namespace["dtInvalid"] = static_cast<lua_Number>(dtInvalid);
    doodad_type_namespace["dtResource"] = static_cast<lua_Number>(dtResource);
    doodad_type_namespace["dtTreasureBox"] = static_cast<lua_Number>(dtTreasureBox);
    doodad_type_namespace["dtQuest"] = static_cast<lua_Number>(dtQuest);
    doodad_type_namespace["dtDestrucible"] = static_cast<lua_Number>(dtDestrucible);
    doodad_type_namespace["dtCorpse"] = static_cast<lua_Number>(dtCorpse);
    doodad_type_namespace["dtTotal"] = static_cast<lua_Number>(dtTotal);
    sol::table doodad_sub_type_namespace = globals["DOODAD_SUB_TYPE"].get_or_create<sol::table>();
    doodad_sub_type_namespace["dstInvalid"] = static_cast<lua_Number>(dstInvalid);
    doodad_sub_type_namespace["dstOre"] = static_cast<lua_Number>(dstOre);
    doodad_sub_type_namespace["dstHerb"] = static_cast<lua_Number>(dstHerb);
    doodad_sub_type_namespace["dstFishingPool"] = static_cast<lua_Number>(dstFishingPool);
    doodad_sub_type_namespace["dstItem"] = static_cast<lua_Number>(dstItem);
    doodad_sub_type_namespace["dstBook"] = static_cast<lua_Number>(dstBook);
    doodad_sub_type_namespace["dstTotal"] = static_cast<lua_Number>(dstTotal);
}

}
