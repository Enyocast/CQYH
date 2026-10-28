#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/quest_def.h"

namespace cqyh::datalogserver::bindings {

void register_quest_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_NORMAL_QUEST_COUNT"] = static_cast<lua_Number>(MAX_NORMAL_QUEST_COUNT);
    globals["MAX_NORMAL_QUEST_BYTE_SIZE"] = static_cast<lua_Number>(MAX_NORMAL_QUEST_BYTE_SIZE);
    globals["REPEAT_QUEST_START_ID"] = static_cast<lua_Number>(REPEAT_QUEST_START_ID);
    globals["MAX_REPEAT_QUEST_COUNT"] = static_cast<lua_Number>(MAX_REPEAT_QUEST_COUNT);
    globals["MAX_REPEAT_QUEST_CYCLE"] = static_cast<lua_Number>(MAX_REPEAT_QUEST_CYCLE);
    globals["MAX_ACCEPTED_NORMAL_QUEST_COUNT"] = static_cast<lua_Number>(MAX_ACCEPTED_NORMAL_QUEST_COUNT);
    globals["MAX_ACCEPTED_EMERGENCY_QUEST_COUNT"] = static_cast<lua_Number>(MAX_ACCEPTED_EMERGENCY_QUEST_COUNT);
    globals["MAX_CONDITION_PER_QUEST"] = static_cast<lua_Number>(MAX_CONDITION_PER_QUEST);
    globals["MAX_REWARD_PER_QUEST"] = static_cast<lua_Number>(MAX_REWARD_PER_QUEST);
    globals["MAX_SELECTABLE_REWARD_COUNT"] = static_cast<lua_Number>(MAX_SELECTABLE_REWARD_COUNT);
    globals["MAX_DIALOG_CONTENT_LEN"] = static_cast<lua_Number>(MAX_DIALOG_CONTENT_LEN);
    globals["INVALID_QUEST_ID"] = static_cast<lua_Number>(INVALID_QUEST_ID);
    globals["MAX_FLY_SPOT_PER_QUEST"] = static_cast<lua_Number>(MAX_FLY_SPOT_PER_QUEST);
    globals["CIRCLE_QUEST_START_ID"] = static_cast<lua_Number>(CIRCLE_QUEST_START_ID);
    globals["EMERGENCY_QUEST_START_ID"] = static_cast<lua_Number>(EMERGENCY_QUEST_START_ID);
    globals["MAX_EMERGENCY_QUEST_COUNT"] = static_cast<lua_Number>(MAX_EMERGENCY_QUEST_COUNT);
    globals["MAX_EMERGENCY_QUEST_COMPLETE_PER_DAY"] = static_cast<lua_Number>(MAX_EMERGENCY_QUEST_COMPLETE_PER_DAY);
    globals["MAX_EMERGENCY_QUEST_PER_ROLE"] = static_cast<lua_Number>(MAX_EMERGENCY_QUEST_PER_ROLE);
    globals["MAX_CHECK_VAR_COUNT"] = static_cast<lua_Number>(MAX_CHECK_VAR_COUNT);
    globals["MAX_KILL_NPC_QUEST_COUNT"] = static_cast<lua_Number>(MAX_KILL_NPC_QUEST_COUNT);
    globals["MAX_KILL_COUNT_PER_NPC"] = static_cast<lua_Number>(MAX_KILL_COUNT_PER_NPC);
    sol::table quest_accept_type_namespace = globals["QUEST_ACCEPT_TYPE"].get_or_create<sol::table>();
    quest_accept_type_namespace["qatInvalid"] = static_cast<lua_Number>(qatInvalid);
    quest_accept_type_namespace["qatNpc"] = static_cast<lua_Number>(qatNpc);
    quest_accept_type_namespace["qatShare"] = static_cast<lua_Number>(qatShare);
    quest_accept_type_namespace["qatPublish"] = static_cast<lua_Number>(qatPublish);
    quest_accept_type_namespace["qatEmegency"] = static_cast<lua_Number>(qatEmegency);
    quest_accept_type_namespace["qatItem"] = static_cast<lua_Number>(qatItem);
    quest_accept_type_namespace["qatTotal"] = static_cast<lua_Number>(qatTotal);
    sol::table quest_time_type_namespace = globals["QUEST_TIME_TYPE"].get_or_create<sol::table>();
    quest_time_type_namespace["qttInvalid"] = static_cast<lua_Number>(qttInvalid);
    quest_time_type_namespace["qttNoReset"] = static_cast<lua_Number>(qttNoReset);
    quest_time_type_namespace["qttDay"] = static_cast<lua_Number>(qttDay);
    quest_time_type_namespace["qttWeek"] = static_cast<lua_Number>(qttWeek);
    quest_time_type_namespace["qttTotal"] = static_cast<lua_Number>(qttTotal);
    sol::table quest_relation_type_namespace = globals["QUEST_RELATION_TYPE"].get_or_create<sol::table>();
    quest_relation_type_namespace["qrtInvalid"] = static_cast<lua_Number>(qrtInvalid);
    quest_relation_type_namespace["qrtMaster"] = static_cast<lua_Number>(qrtMaster);
    quest_relation_type_namespace["qrtDisciple"] = static_cast<lua_Number>(qrtDisciple);
    quest_relation_type_namespace["qrtHusband"] = static_cast<lua_Number>(qrtHusband);
    quest_relation_type_namespace["qrtWife"] = static_cast<lua_Number>(qrtWife);
    quest_relation_type_namespace["qrtGuildLeader"] = static_cast<lua_Number>(qrtGuildLeader);
    quest_relation_type_namespace["qrtGuildMember"] = static_cast<lua_Number>(qrtGuildMember);
    quest_relation_type_namespace["qrtTeamMaster"] = static_cast<lua_Number>(qrtTeamMaster);
    quest_relation_type_namespace["qrtTeamHusband"] = static_cast<lua_Number>(qrtTeamHusband);
    quest_relation_type_namespace["qrtTeamGuild"] = static_cast<lua_Number>(qrtTeamGuild);
    quest_relation_type_namespace["qrtTotal"] = static_cast<lua_Number>(qrtTotal);
    sol::table quest_type_namespace = globals["QUEST_TYPE"].get_or_create<sol::table>();
    quest_type_namespace["qtInvalid"] = static_cast<lua_Number>(qtInvalid);
    quest_type_namespace["qtTrunk"] = static_cast<lua_Number>(qtTrunk);
    quest_type_namespace["qtBranch"] = static_cast<lua_Number>(qtBranch);
    quest_type_namespace["qtDaily"] = static_cast<lua_Number>(qtDaily);
    quest_type_namespace["qtReward"] = static_cast<lua_Number>(qtReward);
    quest_type_namespace["qtCircle"] = static_cast<lua_Number>(qtCircle);
    quest_type_namespace["qtActivity"] = static_cast<lua_Number>(qtActivity);
    quest_type_namespace["qtGuild"] = static_cast<lua_Number>(qtGuild);
    quest_type_namespace["qtMaster"] = static_cast<lua_Number>(qtMaster);
    quest_type_namespace["qtWedding"] = static_cast<lua_Number>(qtWedding);
    quest_type_namespace["qtAdventure"] = static_cast<lua_Number>(qtAdventure);
    quest_type_namespace["qtGuide"] = static_cast<lua_Number>(qtGuide);
    quest_type_namespace["qtEmegency"] = static_cast<lua_Number>(qtEmegency);
    quest_type_namespace["qtTotal"] = static_cast<lua_Number>(qtTotal);
}

}
