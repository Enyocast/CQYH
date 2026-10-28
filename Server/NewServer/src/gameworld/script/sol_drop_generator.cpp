#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "drop_generator.h"
#include "../../../inc/gameworld/scene.h"

int sol_drop_generator_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CDropGenerator>(L, globals, "CDropGenerator", "CDropGenerator");
    type1.set_function("GetInstance", []() -> decltype(auto) { return CDropGenerator::GetInstance(); });
    type1.set_function("GenerateDrop", [](CDropGenerator* self, signed int nServerGroup, signed int itemid, signed int itemcount, CScene* scene, INT64 llX, INT64 llY, INT64 llZ, unsigned int srcid, bool instantpick) -> decltype(auto) { return static_cast<bool>(self->GenerateDrop(nServerGroup,itemid,itemcount,scene,llX,llY,llZ,srcid,instantpick)); });
    return 1;
}
