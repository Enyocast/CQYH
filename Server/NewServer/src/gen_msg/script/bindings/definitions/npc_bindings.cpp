#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/npc_def.h"

namespace cqyh::gen_msg::bindings {

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
    sol::table npc_state_namespace = globals["NPC_STATE"].get_or_create<sol::table>();
    npc_state_namespace["npcInvalid"] = static_cast<lua_Number>(npcInvalid);
    npc_state_namespace["npcSpawn"] = static_cast<lua_Number>(npcSpawn);
    npc_state_namespace["npcAlive"] = static_cast<lua_Number>(npcAlive);
    npc_state_namespace["npcCorpse"] = static_cast<lua_Number>(npcCorpse);
    npc_state_namespace["npcRespawn"] = static_cast<lua_Number>(npcRespawn);
    npc_state_namespace["npcRevive"] = static_cast<lua_Number>(npcRevive);
    npc_state_namespace["npcTotal"] = static_cast<lua_Number>(npcTotal);
    sol::table npc_quality_namespace = globals["NPC_QUALITY"].get_or_create<sol::table>();
    npc_quality_namespace["nqInvalid"] = static_cast<lua_Number>(nqInvalid);
    npc_quality_namespace["nqNormal1"] = static_cast<lua_Number>(nqNormal1);
    npc_quality_namespace["nqNormal2"] = static_cast<lua_Number>(nqNormal2);
    npc_quality_namespace["nqNormal3"] = static_cast<lua_Number>(nqNormal3);
    npc_quality_namespace["nqNormal4"] = static_cast<lua_Number>(nqNormal4);
    npc_quality_namespace["nqNormal5"] = static_cast<lua_Number>(nqNormal5);
    npc_quality_namespace["nqElite"] = static_cast<lua_Number>(nqElite);
    npc_quality_namespace["nqRare"] = static_cast<lua_Number>(nqRare);
    npc_quality_namespace["nqBoss"] = static_cast<lua_Number>(nqBoss);
    npc_quality_namespace["nqTotal"] = static_cast<lua_Number>(nqTotal);
    sol::table npc_transform_state_namespace = globals["NPC_TRANSFORM_STATE"].get_or_create<sol::table>();
    npc_transform_state_namespace["npctInvalid"] = static_cast<lua_Number>(npctInvalid);
    npc_transform_state_namespace["npctNpc"] = static_cast<lua_Number>(npctNpc);
    npc_transform_state_namespace["npctPet"] = static_cast<lua_Number>(npctPet);
    npc_transform_state_namespace["npctTotal"] = static_cast<lua_Number>(npctTotal);
    sol::table pet_type_namespace = globals["PET_TYPE"].get_or_create<sol::table>();
    pet_type_namespace["petInvalid"] = static_cast<lua_Number>(petInvalid);
    pet_type_namespace["petTotal"] = static_cast<lua_Number>(petTotal);
    sol::table pet_born_type_namespace = globals["PET_BORN_TYPE"].get_or_create<sol::table>();
    pet_born_type_namespace["petBornInvalid"] = static_cast<lua_Number>(petBornInvalid);
    pet_born_type_namespace["petBornHoly"] = static_cast<lua_Number>(petBornHoly);
    pet_born_type_namespace["petBornSkeleton"] = static_cast<lua_Number>(petBornSkeleton);
    pet_born_type_namespace["petBornByMage"] = static_cast<lua_Number>(petBornByMage);
    pet_born_type_namespace["petBornTotal"] = static_cast<lua_Number>(petBornTotal);
    sol::table pet_state_namespace = globals["PET_STATE"].get_or_create<sol::table>();
    pet_state_namespace["psInvalid"] = static_cast<lua_Number>(psInvalid);
    pet_state_namespace["psIdle"] = static_cast<lua_Number>(psIdle);
    pet_state_namespace["psFight"] = static_cast<lua_Number>(psFight);
    pet_state_namespace["psTotal"] = static_cast<lua_Number>(psTotal);
    sol::table pet_ai_variables_namespace = globals["PET_AI_VARIABLES"].get_or_create<sol::table>();
    pet_ai_variables_namespace["PET_AIV_MAGE_PET_SPELL_ID"] = static_cast<lua_Number>(PET_AIV_MAGE_PET_SPELL_ID);
    pet_ai_variables_namespace["PET_AIV_FIGHT_STATE_INDEX"] = static_cast<lua_Number>(PET_AIV_FIGHT_STATE_INDEX);
    pet_ai_variables_namespace["PET_AI_CONTROL"] = static_cast<lua_Number>(PET_AI_CONTROL);
    pet_ai_variables_namespace["PET_AI_IS_EXTRA_WALK"] = static_cast<lua_Number>(PET_AI_IS_EXTRA_WALK);
    pet_ai_variables_namespace["PET_AI_MAGE_CHASE_THRESHOLD"] = static_cast<lua_Number>(PET_AI_MAGE_CHASE_THRESHOLD);
    pet_ai_variables_namespace["PET_AI_MAGE_PREFER_DISTANCE"] = static_cast<lua_Number>(PET_AI_MAGE_PREFER_DISTANCE);
    pet_ai_variables_namespace["PET_AI_GO_HOME"] = static_cast<lua_Number>(PET_AI_GO_HOME);
}

}
