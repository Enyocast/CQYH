#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/variable_def.h"

namespace cqyh::fusion::bindings {

void register_variable_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_SCENE_VARIABLE_COUNT"] = static_cast<lua_Number>(MAX_SCENE_VARIABLE_COUNT);
    globals["MAX_ROLE_VARIABLE_COUNT"] = static_cast<lua_Number>(MAX_ROLE_VARIABLE_COUNT);
    globals["MAX_CLIENT_VARIABLE_COUNT"] = static_cast<lua_Number>(MAX_CLIENT_VARIABLE_COUNT);
    globals["MAX_GUILD_VARIABLE_COUNT"] = static_cast<lua_Number>(MAX_GUILD_VARIABLE_COUNT);
    globals["MAX_VARIABLE_PER_QUEST"] = static_cast<lua_Number>(MAX_VARIABLE_PER_QUEST);
    globals["MAX_AI_VARIABLE_COUNT"] = static_cast<lua_Number>(MAX_AI_VARIABLE_COUNT);
    globals["VARIABLE_ID_MASK"] = static_cast<lua_Number>(VARIABLE_ID_MASK);
    globals["INVALID_VARIABLE_ID"] = static_cast<lua_Number>(INVALID_VARIABLE_ID);
    globals["vtInvalid"] = static_cast<lua_Number>(vtInvalid);
    globals["vtRole"] = static_cast<lua_Number>(vtRole);
    globals["vtScene"] = static_cast<lua_Number>(vtScene);
    globals["vtGuild"] = static_cast<lua_Number>(vtGuild);
    globals["vtQuest"] = static_cast<lua_Number>(vtQuest);
    globals["vtItemRecycle"] = static_cast<lua_Number>(vtItemRecycle);
    globals["vtKillNpcCount"] = static_cast<lua_Number>(vtKillNpcCount);
    globals["vtClient"] = static_cast<lua_Number>(vtClient);
    globals["vtAI"] = static_cast<lua_Number>(vtAI);
    globals["vtAISpell"] = static_cast<lua_Number>(vtAISpell);
    globals["vtServer"] = static_cast<lua_Number>(vtServer);
    globals["vtKillDoodad"] = static_cast<lua_Number>(vtKillDoodad);
    globals["vtAchievement"] = static_cast<lua_Number>(vtAchievement);
    globals["vtKillPlayerCount"] = static_cast<lua_Number>(vtKillPlayerCount);
    globals["vtKillItemNpcCount"] = static_cast<lua_Number>(vtKillItemNpcCount);
    globals["vtTotal"] = static_cast<lua_Number>(vtTotal);
    globals["vRole"] = static_cast<lua_Number>(vRole);
    globals["vScene"] = static_cast<lua_Number>(vScene);
    globals["vGuild"] = static_cast<lua_Number>(vGuild);
    globals["vQuest"] = static_cast<lua_Number>(vQuest);
    globals["vClient"] = static_cast<lua_Number>(vClient);
    globals["vAI"] = static_cast<lua_Number>(vAI);
    globals["vServer"] = static_cast<lua_Number>(vServer);
    globals["svtBegin"] = static_cast<lua_Number>(svtBegin);
    globals["svtSabacWinner0"] = static_cast<lua_Number>(svtSabacWinner0);
    globals["svtSabacWinner1"] = static_cast<lua_Number>(svtSabacWinner1);
    globals["svtSabacWinner2"] = static_cast<lua_Number>(svtSabacWinner2);
    globals["svtSabacWinner3"] = static_cast<lua_Number>(svtSabacWinner3);
    globals["svtSabacWinner4"] = static_cast<lua_Number>(svtSabacWinner4);
    globals["svtSabacWinner5"] = static_cast<lua_Number>(svtSabacWinner5);
    globals["svtSabacDoor"] = static_cast<lua_Number>(svtSabacDoor);
    globals["svtSabacWall1"] = static_cast<lua_Number>(svtSabacWall1);
    globals["svtSabacWall2"] = static_cast<lua_Number>(svtSabacWall2);
    globals["svtSabacWall3"] = static_cast<lua_Number>(svtSabacWall3);
    globals["svtSabacArcher1"] = static_cast<lua_Number>(svtSabacArcher1);
    globals["svtSabacArcher2"] = static_cast<lua_Number>(svtSabacArcher2);
    globals["svtSabacArcher3"] = static_cast<lua_Number>(svtSabacArcher3);
    globals["svtSabacArcher4"] = static_cast<lua_Number>(svtSabacArcher4);
    globals["svtSabacArcher5"] = static_cast<lua_Number>(svtSabacArcher5);
    globals["svtSabacArcher6"] = static_cast<lua_Number>(svtSabacArcher6);
    globals["svtSabacArcher7"] = static_cast<lua_Number>(svtSabacArcher7);
    globals["svtSabacArcher8"] = static_cast<lua_Number>(svtSabacArcher8);
    globals["svtSabacArcher9"] = static_cast<lua_Number>(svtSabacArcher9);
    globals["svtSabacArcher10"] = static_cast<lua_Number>(svtSabacArcher10);
    globals["svtSabacArcher11"] = static_cast<lua_Number>(svtSabacArcher11);
    globals["svtSabacArcher12"] = static_cast<lua_Number>(svtSabacArcher12);
    globals["svtEnd"] = static_cast<lua_Number>(svtEnd);
    globals.set_function("MakeVariableID", [](unsigned int dwType, unsigned int dwIndex) -> decltype(auto) { return MakeVariableID(dwType,dwIndex); });
}

}
