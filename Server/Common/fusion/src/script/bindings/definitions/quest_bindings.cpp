#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/quest_def.h"

namespace cqyh::fusion::bindings {

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
    globals["qatInvalid"] = static_cast<lua_Number>(qatInvalid);
    globals["qatNpc"] = static_cast<lua_Number>(qatNpc);
    globals["qatShare"] = static_cast<lua_Number>(qatShare);
    globals["qatPublish"] = static_cast<lua_Number>(qatPublish);
    globals["qatEmegency"] = static_cast<lua_Number>(qatEmegency);
    globals["qatItem"] = static_cast<lua_Number>(qatItem);
    globals["qatTotal"] = static_cast<lua_Number>(qatTotal);
    globals["qttInvalid"] = static_cast<lua_Number>(qttInvalid);
    globals["qttNoReset"] = static_cast<lua_Number>(qttNoReset);
    globals["qttDay"] = static_cast<lua_Number>(qttDay);
    globals["qttWeek"] = static_cast<lua_Number>(qttWeek);
    globals["qttTotal"] = static_cast<lua_Number>(qttTotal);
    globals["qrtInvalid"] = static_cast<lua_Number>(qrtInvalid);
    globals["qrtMaster"] = static_cast<lua_Number>(qrtMaster);
    globals["qrtDisciple"] = static_cast<lua_Number>(qrtDisciple);
    globals["qrtHusband"] = static_cast<lua_Number>(qrtHusband);
    globals["qrtWife"] = static_cast<lua_Number>(qrtWife);
    globals["qrtGuildLeader"] = static_cast<lua_Number>(qrtGuildLeader);
    globals["qrtGuildMember"] = static_cast<lua_Number>(qrtGuildMember);
    globals["qrtTeamMaster"] = static_cast<lua_Number>(qrtTeamMaster);
    globals["qrtTeamHusband"] = static_cast<lua_Number>(qrtTeamHusband);
    globals["qrtTeamGuild"] = static_cast<lua_Number>(qrtTeamGuild);
    globals["qrtTotal"] = static_cast<lua_Number>(qrtTotal);
    globals["qtInvalid"] = static_cast<lua_Number>(qtInvalid);
    globals["qtTrunk"] = static_cast<lua_Number>(qtTrunk);
    globals["qtBranch"] = static_cast<lua_Number>(qtBranch);
    globals["qtDaily"] = static_cast<lua_Number>(qtDaily);
    globals["qtReward"] = static_cast<lua_Number>(qtReward);
    globals["qtCircle"] = static_cast<lua_Number>(qtCircle);
    globals["qtActivity"] = static_cast<lua_Number>(qtActivity);
    globals["qtGuild"] = static_cast<lua_Number>(qtGuild);
    globals["qtMaster"] = static_cast<lua_Number>(qtMaster);
    globals["qtWedding"] = static_cast<lua_Number>(qtWedding);
    globals["qtAdventure"] = static_cast<lua_Number>(qtAdventure);
    globals["qtGuide"] = static_cast<lua_Number>(qtGuide);
    globals["qtEmegency"] = static_cast<lua_Number>(qtEmegency);
    globals["qtTotal"] = static_cast<lua_Number>(qtTotal);
}

}
