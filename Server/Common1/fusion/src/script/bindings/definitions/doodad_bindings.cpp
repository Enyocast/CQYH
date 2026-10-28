#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/doodad_def.h"

namespace cqyh::fusion::bindings {

void register_doodad_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_DOODAD_LEVEL"] = static_cast<lua_Number>(MAX_DOODAD_LEVEL);
    globals["dtInvalid"] = static_cast<lua_Number>(dtInvalid);
    globals["dtResource"] = static_cast<lua_Number>(dtResource);
    globals["dtTreasureBox"] = static_cast<lua_Number>(dtTreasureBox);
    globals["dtQuest"] = static_cast<lua_Number>(dtQuest);
    globals["dtDestrucible"] = static_cast<lua_Number>(dtDestrucible);
    globals["dtCorpse"] = static_cast<lua_Number>(dtCorpse);
    globals["dtTotal"] = static_cast<lua_Number>(dtTotal);
    globals["dstInvalid"] = static_cast<lua_Number>(dstInvalid);
    globals["dstOre"] = static_cast<lua_Number>(dstOre);
    globals["dstHerb"] = static_cast<lua_Number>(dstHerb);
    globals["dstFishingPool"] = static_cast<lua_Number>(dstFishingPool);
    globals["dstItem"] = static_cast<lua_Number>(dstItem);
    globals["dstBook"] = static_cast<lua_Number>(dstBook);
    globals["dstTotal"] = static_cast<lua_Number>(dstTotal);
}

}
