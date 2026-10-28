#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/npc_def.h"

namespace cqyh::fusion::bindings {

void register_npc_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_NPC_ID"] = static_cast<lua_Number>(MAX_NPC_ID);
    globals["MAX_NPC_FORCE_ID"] = static_cast<lua_Number>(MAX_NPC_FORCE_ID);
    globals["INVALID_FORCE_ID"] = static_cast<lua_Number>(INVALID_FORCE_ID);
    globals["MAX_NPC_LEVEL"] = static_cast<lua_Number>(MAX_NPC_LEVEL);
    globals["MIN_NPC_RADIUS"] = static_cast<lua_Number>(MIN_NPC_RADIUS);
    globals["MAX_LEVEL_DIFF"] = static_cast<lua_Number>(MAX_LEVEL_DIFF);
    globals["MAX_PET_LEVEL"] = static_cast<lua_Number>(MAX_PET_LEVEL);
    globals["CASTER_WASHOUT_TIME"] = static_cast<lua_Number>(CASTER_WASHOUT_TIME);
    globals["TARGET_WASHOUT_TIME"] = static_cast<lua_Number>(TARGET_WASHOUT_TIME);
    globals["npcInvalid"] = static_cast<lua_Number>(npcInvalid);
    globals["npcSpawn"] = static_cast<lua_Number>(npcSpawn);
    globals["npcAlive"] = static_cast<lua_Number>(npcAlive);
    globals["npcCorpse"] = static_cast<lua_Number>(npcCorpse);
    globals["npcRespawn"] = static_cast<lua_Number>(npcRespawn);
    globals["npcRevive"] = static_cast<lua_Number>(npcRevive);
    globals["npcTotal"] = static_cast<lua_Number>(npcTotal);
    globals["nqInvalid"] = static_cast<lua_Number>(nqInvalid);
    globals["nqNormal1"] = static_cast<lua_Number>(nqNormal1);
    globals["nqNormal2"] = static_cast<lua_Number>(nqNormal2);
    globals["nqNormal3"] = static_cast<lua_Number>(nqNormal3);
    globals["nqNormal4"] = static_cast<lua_Number>(nqNormal4);
    globals["nqNormal5"] = static_cast<lua_Number>(nqNormal5);
    globals["nqElite"] = static_cast<lua_Number>(nqElite);
    globals["nqRare"] = static_cast<lua_Number>(nqRare);
    globals["nqBoss"] = static_cast<lua_Number>(nqBoss);
    globals["nqTotal"] = static_cast<lua_Number>(nqTotal);
    globals["npctInvalid"] = static_cast<lua_Number>(npctInvalid);
    globals["npctNpc"] = static_cast<lua_Number>(npctNpc);
    globals["npctPet"] = static_cast<lua_Number>(npctPet);
    globals["npctTotal"] = static_cast<lua_Number>(npctTotal);
    globals["petInvalid"] = static_cast<lua_Number>(petInvalid);
    globals["petTotal"] = static_cast<lua_Number>(petTotal);
    globals["petBornInvalid"] = static_cast<lua_Number>(petBornInvalid);
    globals["petBornHoly"] = static_cast<lua_Number>(petBornHoly);
    globals["petBornSkeleton"] = static_cast<lua_Number>(petBornSkeleton);
    globals["petBornByMage"] = static_cast<lua_Number>(petBornByMage);
    globals["petBornTotal"] = static_cast<lua_Number>(petBornTotal);
    globals["psInvalid"] = static_cast<lua_Number>(psInvalid);
    globals["psIdle"] = static_cast<lua_Number>(psIdle);
    globals["psFight"] = static_cast<lua_Number>(psFight);
    globals["psTotal"] = static_cast<lua_Number>(psTotal);
    globals["PET_AIV_MAGE_PET_SPELL_ID"] = static_cast<lua_Number>(PET_AIV_MAGE_PET_SPELL_ID);
    globals["PET_AIV_FIGHT_STATE_INDEX"] = static_cast<lua_Number>(PET_AIV_FIGHT_STATE_INDEX);
    globals["PET_AI_CONTROL"] = static_cast<lua_Number>(PET_AI_CONTROL);
    globals["PET_AI_IS_EXTRA_WALK"] = static_cast<lua_Number>(PET_AI_IS_EXTRA_WALK);
    globals["PET_AI_MAGE_CHASE_THRESHOLD"] = static_cast<lua_Number>(PET_AI_MAGE_CHASE_THRESHOLD);
    globals["PET_AI_MAGE_PREFER_DISTANCE"] = static_cast<lua_Number>(PET_AI_MAGE_PREFER_DISTANCE);
    globals["PET_AI_GO_HOME"] = static_cast<lua_Number>(PET_AI_GO_HOME);
}

}
