#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "doodad.h"
#include "../../../inc/gameworld/scene_object.h"
#include "../../../inc/gameworld/character.h"
#include "../../../../Common/fusion/inc/doodad_data.h"

int sol_doodad_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CDoodad>(L, globals, "CDoodad", "CDoodad", sol::base_classes, sol::bases<CSceneObject>());
    type1.set_function("GetDoodadData", [](CDoodad* self) -> decltype(auto) { return self->GetDoodadData(); });
    type1.set_function("GetOpenCount", [](CDoodad* self) -> decltype(auto) { return self->GetOpenCount(); });
    type1.set_function("OnOpen", [](CDoodad* self, CCharacter* poChar, signed int nDelayFrame) -> decltype(auto) { self->OnOpen(poChar,nDelayFrame); });
    return 1;
}
