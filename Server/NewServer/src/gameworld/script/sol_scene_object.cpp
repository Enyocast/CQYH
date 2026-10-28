#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "scene_object.h"
#include "../../../../Common/define/grid_def.h"
#include "../../../../Common/define/zone_def.h"
#include "../../../inc/gameworld/scene.h"
#include "../../../inc/gameworld/region.h"

int sol_scene_object_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CSceneObject>(L, globals, "CSceneObject", "CSceneObject");
    type1.set_function("GetObjID", [](CSceneObject* self) -> decltype(auto) { return self->GetObjID(); });
    type1.set_function("GetObjType", [](CSceneObject* self) -> decltype(auto) { return self->GetObjType(); });
    type1.set_function("GetScene", [](CSceneObject* self) -> decltype(auto) { return self->GetScene(); });
    type1.set_function("GetRegion", [](CSceneObject* self) -> decltype(auto) { return self->GetRegion(); });
    type1.set_function("GetZone", [](CSceneObject* self) -> decltype(auto) { return self->GetZone(); });
    type1.set_function("GetGrid", [](CSceneObject* self) -> decltype(auto) { return self->GetGrid(); });
    type1.set_function("GetGridInstance", [](CSceneObject* self) -> decltype(auto) { return self->GetGridInstance(); });
    type1.set_function("SetX", [](CSceneObject* self, INT64 fX) -> decltype(auto) { self->SetX(fX); });
    type1.set_function("SetY", [](CSceneObject* self, INT64 fY) -> decltype(auto) { self->SetY(fY); });
    type1.set_function("SetZ", [](CSceneObject* self, INT64 fZ) -> decltype(auto) { self->SetZ(fZ); });
    type1.set_function("GetX", [](CSceneObject* self) -> decltype(auto) { return self->GetX(); });
    type1.set_function("GetY", [](CSceneObject* self) -> decltype(auto) { return self->GetY(); });
    type1.set_function("GetZ", [](CSceneObject* self) -> decltype(auto) { return self->GetZ(); });
    type1.set_function("SetFaceDirection", [](CSceneObject* self, signed int nFaceDirection) -> decltype(auto) { self->SetFaceDirection(nFaceDirection); });
    type1.set_function("GetFaceDirection", [](CSceneObject* self) -> decltype(auto) { return self->GetFaceDirection(); });
    type1.set_function("SetBodyType", [](CSceneObject* self, signed int nBodyType) -> decltype(auto) { self->SetBodyType(nBodyType); });
    type1.set_function("GetBodyType", [](CSceneObject* self) -> decltype(auto) { return self->GetBodyType(); });
    type1.set_function("CanTeleport", [](CSceneObject* self) -> decltype(auto) { return static_cast<bool>(self->CanTeleport()); });
    return 1;
}
