#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "game_world.h"
#include "../../../inc/gameworld/scene_object.h"
#include "../../../inc/gameworld/character.h"
#include "../../../inc/gameworld/doodad.h"
#include "../../../inc/baselib/btnod.h"
#include "../../../inc/gameworld/role.h"
#include "../../../inc/gameworld/team.h"
#include "../../../inc/gameworld/npc.h"

int sol_gameworld_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CGameWorld>(L, globals, "CGameWorld", "CGameWorld");
    type1.set_function("GetInstance", []() -> decltype(auto) { return CGameWorld::GetInstance(); });
    type1.set_function("GetGameFrame", [](CGameWorld* self) -> decltype(auto) { return self->GetGameFrame(); });
    type1.set_function("FindRole", [](CGameWorld* self, unsigned int dwRoleID) -> decltype(auto) { return self->FindRole(dwRoleID); });
    type1.set_function("SetCanCast", [](CGameWorld* self, bool bCanCast) -> decltype(auto) { self->SetCanCast(bCanCast); });
    type1.set_function("CanCast", [](CGameWorld* self) -> decltype(auto) { return static_cast<bool>(self->CanCast()); });
    type1.set_function("SetDrawDebugLine", [](CGameWorld* self, bool bDraw) -> decltype(auto) { self->SetDrawDebugLine(bDraw); });
    type1.set_function("SetCheckConsume", [](CGameWorld* self, bool bCheck) -> decltype(auto) { self->SetCheckConsume(bCheck); });
    type1.set_function("NewRole", [](CGameWorld* self, unsigned int dwRoleID) -> decltype(auto) { return self->NewRole(dwRoleID); });
    type1.set_function("DelRole", [](CGameWorld* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->DelRole(poRole)); });
    type1.set_function("FindRole", sol::overload([](CGameWorld* self, unsigned int dwRoleID) -> decltype(auto) { return self->FindRole(dwRoleID); }, [](CGameWorld* self, unsigned int dwRoleID) -> decltype(auto) { return self->FindRole(dwRoleID); }));
    type1.set_function("GetRoleCount", [](CGameWorld* self) -> decltype(auto) { return self->GetRoleCount(); });
    type1.set_function("NewNpc", [](CGameWorld* self, unsigned int dwNpcID) -> decltype(auto) { return self->NewNpc(dwNpcID); });
    type1.set_function("DelNpc", [](CGameWorld* self, CNpc* poNpc) -> decltype(auto) { return static_cast<bool>(self->DelNpc(poNpc)); });
    type1.set_function("FindNpc", [](CGameWorld* self, unsigned int dwNpcID) -> decltype(auto) { return self->FindNpc(dwNpcID); });
    type1.set_function("GetNpcID", [](CGameWorld* self, CNpc* poNpc) -> decltype(auto) { return self->GetNpcID(poNpc); });
    type1.set_function("FindTeam", [](CGameWorld* self, unsigned int dwTeamID) -> decltype(auto) { return self->FindTeam(dwTeamID); });
    type1.set_function("NewDoodad", [](CGameWorld* self) -> decltype(auto) { return self->NewDoodad(); });
    type1.set_function("DelDoodad", [](CGameWorld* self, CDoodad* poDoodad) -> decltype(auto) { return static_cast<bool>(self->DelDoodad(poDoodad)); });
    type1.set_function("FindDoodad", [](CGameWorld* self, unsigned int dwDoodadID) -> decltype(auto) { return self->FindDoodad(dwDoodadID); });
    type1.set_function("FindCharacter", [](CGameWorld* self, unsigned int dwCharID) -> decltype(auto) { return self->FindCharacter(dwCharID); });
    type1.set_function("FindValidRole", [](CGameWorld* self, unsigned int dwRoleID) -> decltype(auto) { return self->FindValidRole(dwRoleID); });
    type1.set_function("FindValidCharacter", [](CGameWorld* self, unsigned int dwCharID) -> decltype(auto) { return self->FindValidCharacter(dwCharID); });
    type1.set_function("FindValidObj", [](CGameWorld* self, unsigned int dwObj) -> decltype(auto) { return self->FindValidObj(dwObj); });
    type1.set_function("JumpTo", [](CGameWorld* self, CRole* poRole, signed int nSceneTempID, signed int nSceneID, signed int nX, signed int nY, signed int nZ, signed int nFaceDirection) -> decltype(auto) { return static_cast<bool>(self->JumpTo(poRole,nSceneTempID,nSceneID,nX,nY,nZ,nFaceDirection)); });
    type1.set_function("JumpToRole", [](CGameWorld* self, CRole* poRole, const char* pcszRoleName) -> decltype(auto) { return static_cast<bool>(self->JumpToRole(poRole,pcszRoleName)); });
    type1.set_function("TakeRole", [](CGameWorld* self, CRole* poRole, const char* pcszRoleName) -> decltype(auto) { return static_cast<bool>(self->TakeRole(poRole,pcszRoleName)); });
    type1.set_function("NewBTNod", [](CGameWorld* self) -> decltype(auto) { return self->NewBTNod(); });
    type1.set_function("DelBTNod", [](CGameWorld* self, BTNod* poNod) -> decltype(auto) { return static_cast<bool>(self->DelBTNod(poNod)); });
    type1.set_function("SetGameTime", [](CGameWorld* self, unsigned int dwGameTime) -> decltype(auto) { self->SetGameTime(dwGameTime); });
    type1.set_function("GetGameTime", [](CGameWorld* self) -> decltype(auto) { return self->GetGameTime(); });
    type1.set_function("GetTimeZone", [](CGameWorld* self) -> decltype(auto) { return self->GetTimeZone(); });
    type1.set_function("SetFreezeTime", [](CGameWorld* self, bool bFreezeTime) -> decltype(auto) { self->SetFreezeTime(bFreezeTime); });
    type1.set_function("IsFreezeTime", [](CGameWorld* self) -> decltype(auto) { return static_cast<bool>(self->IsFreezeTime()); });
    type1.set_function("ToggleGlobalDropMax", [](CGameWorld* self) -> decltype(auto) { self->ToggleGlobalDropMax(); });
    type1.set_function("SetGlobalDropRate", [](CGameWorld* self, signed int nDropRate) -> decltype(auto) { self->SetGlobalDropRate(nDropRate); });
    type1.set_function("GetGlobalDropRate", [](CGameWorld* self) -> decltype(auto) { return self->GetGlobalDropRate(); });
    type1.set_function("SetGlobalExpRate", [](CGameWorld* self, signed int nExpRate) -> decltype(auto) { self->SetGlobalExpRate(nExpRate); });
    type1.set_function("GetGlobalExpRate", [](CGameWorld* self) -> decltype(auto) { return self->GetGlobalExpRate(); });
    type1.set_function("GetAverageLevel", [](CGameWorld* self, signed int nServerGroup) -> decltype(auto) { return self->GetAverageLevel(nServerGroup); });
    type1.set_function("GetServerVariable", [](CGameWorld* self, signed int nServerGroup, signed int nVarIndex) -> decltype(auto) { return self->GetServerVariable(nServerGroup,nVarIndex); });
    type1.set_function("SetServerVariable", [](CGameWorld* self, signed int nServerGroup, signed int nVarIndex, bool bAbsoluteValue, signed int nVarValue) -> decltype(auto) { self->SetServerVariable(nServerGroup,nVarIndex,bAbsoluteValue,nVarValue); });
    type1.set_function("GetGsSessionID", [](CGameWorld* self) -> decltype(auto) { return self->GetGsSessionID(); });
    type1.set_function("PrintMemoryStat", [](CGameWorld* self) -> decltype(auto) { self->PrintMemoryStat(); });
    type1.set_function("PrintNpcPool", [](CGameWorld* self) -> decltype(auto) { self->PrintNpcPool(); });
    type1.set_function("PrintRolePool", [](CGameWorld* self) -> decltype(auto) { self->PrintRolePool(); });
    type1.set_function("PrintScenePool", [](CGameWorld* self, bool bDetail) -> decltype(auto) { self->PrintScenePool(bDetail); });
    type1.set_function("GetAverageLevel", sol::overload([](CGameWorld* self, signed int nServerGroup) -> decltype(auto) { return self->GetAverageLevel(nServerGroup); }, [](CGameWorld* self, signed int nServerGroup) -> decltype(auto) { return self->GetAverageLevel(nServerGroup); }));
    return 1;
}
