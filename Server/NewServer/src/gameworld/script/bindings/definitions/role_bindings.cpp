#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/role_def.h"
#include "../../../../../../Common/define/scene_def.h"

namespace cqyh::gameworld::bindings {

void register_role_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_ROLE_FRACTION_ID"] = static_cast<lua_Number>(MAX_ROLE_FRACTION_ID);
    globals["MAX_ROLE_LEVEL"] = static_cast<lua_Number>(MAX_ROLE_LEVEL);
    globals["MAX_PK_VALUE"] = static_cast<lua_Number>(MAX_PK_VALUE);
    globals["MIN_REPUTATION"] = static_cast<lua_Number>(MIN_REPUTATION);
    globals["MAX_ACTIVITY_LEVEL"] = static_cast<lua_Number>(MAX_ACTIVITY_LEVEL);
    globals["MAX_USABLE_ROLE_PER_USER"] = static_cast<lua_Number>(MAX_USABLE_ROLE_PER_USER);
    globals["MAX_DELETE_ROLE_PER_USER"] = static_cast<lua_Number>(MAX_DELETE_ROLE_PER_USER);
    globals["MAX_ROLE_PER_USER"] = static_cast<lua_Number>(MAX_ROLE_PER_USER);
    globals["MAX_ROLE_HAIR_TYPE"] = static_cast<lua_Number>(MAX_ROLE_HAIR_TYPE);
    globals["MAX_ROLE_HAIR_COLOR"] = static_cast<lua_Number>(MAX_ROLE_HAIR_COLOR);
    globals["MAX_ROLE_FACE_TYPE"] = static_cast<lua_Number>(MAX_ROLE_FACE_TYPE);
    globals["MAX_ROLE_SKIN_COLOR"] = static_cast<lua_Number>(MAX_ROLE_SKIN_COLOR);
    globals["MOMENTARY_KILL_NPC_TIEM"] = static_cast<lua_Number>(MOMENTARY_KILL_NPC_TIEM);
    globals["MIN_MOMENTARY_KILL_NPC_COUNT"] = static_cast<lua_Number>(MIN_MOMENTARY_KILL_NPC_COUNT);
    globals["MIN_CONSECUTIVE_KILL_NPC_COUNT"] = static_cast<lua_Number>(MIN_CONSECUTIVE_KILL_NPC_COUNT);
    globals["MAX_CONSECUTIVE_KILL_NPC_FRAME"] = static_cast<lua_Number>(MAX_CONSECUTIVE_KILL_NPC_FRAME);
    globals["MAX_CONSECTIVE_KILL_PLAYER_FRAME"] = static_cast<lua_Number>(MAX_CONSECTIVE_KILL_PLAYER_FRAME);
    globals["MAX_CONSECUTIVE_KILL_PLAYER_COUNT"] = static_cast<lua_Number>(MAX_CONSECUTIVE_KILL_PLAYER_COUNT);
    globals["MAX_QUERY_ROLE_INFO_PER_SEC"] = static_cast<lua_Number>(MAX_QUERY_ROLE_INFO_PER_SEC);
    globals["MAX_VIP_MONTH"] = static_cast<lua_Number>(MAX_VIP_MONTH);
    globals["MAX_GM_LEVEL"] = static_cast<lua_Number>(MAX_GM_LEVEL);
    globals["MAX_PET_PER_ROLE"] = static_cast<lua_Number>(MAX_PET_PER_ROLE);
    globals["MAX_REPUTATION_AWARD_COUNT"] = static_cast<lua_Number>(MAX_REPUTATION_AWARD_COUNT);
    globals["ROLE_DELAY_LOGOUT_FRAME"] = static_cast<lua_Number>(ROLE_DELAY_LOGOUT_FRAME);
    globals["ROLE_DELAY_LOGOUT_FRAME_ABNORMAL"] = static_cast<lua_Number>(ROLE_DELAY_LOGOUT_FRAME_ABNORMAL);
    globals["ROLE_DELAY_LOGOUT_FRAME"] = static_cast<lua_Number>(ROLE_DELAY_LOGOUT_FRAME);
    globals["ROLE_DELAY_LOGOUT_FRAME_ABNORMAL"] = static_cast<lua_Number>(ROLE_DELAY_LOGOUT_FRAME_ABNORMAL);
    globals["DEFAULT_ROLE_ANTI_CHEAT_LEVEL"] = static_cast<lua_Number>(DEFAULT_ROLE_ANTI_CHEAT_LEVEL);
    globals["MAX_ROLE_ANTI_CHEAT_LEVEL"] = static_cast<lua_Number>(MAX_ROLE_ANTI_CHEAT_LEVEL);
    globals["MAX_ROLE_ANTI_CHEAT_PUNISH_LEVEL"] = static_cast<lua_Number>(MAX_ROLE_ANTI_CHEAT_PUNISH_LEVEL);
    globals["MAX_ROLE_GPK_PUNISH_LEVEL"] = static_cast<lua_Number>(MAX_ROLE_GPK_PUNISH_LEVEL);
    globals["rltInvalid"] = static_cast<lua_Number>(rltInvalid);
    globals["rltReturnLogin"] = static_cast<lua_Number>(rltReturnLogin);
    globals["rltReturnSelectRole"] = static_cast<lua_Number>(rltReturnSelectRole);
    globals["rltDisconnect"] = static_cast<lua_Number>(rltDisconnect);
    globals["rltKickout"] = static_cast<lua_Number>(rltKickout);
    globals["rltTotal"] = static_cast<lua_Number>(rltTotal);
    globals["rsInvalid"] = static_cast<lua_Number>(rsInvalid);
    globals["rsPreEntered"] = static_cast<lua_Number>(rsPreEntered);
    globals["rsWaitRoleData"] = static_cast<lua_Number>(rsWaitRoleData);
    globals["rsWaitMSApprove"] = static_cast<lua_Number>(rsWaitMSApprove);
    globals["rsWaitClientLoad"] = static_cast<lua_Number>(rsWaitClientLoad);
    globals["rsPlaying"] = static_cast<lua_Number>(rsPlaying);
    globals["rsInJump"] = static_cast<lua_Number>(rsInJump);
    globals["rsJumpInGSWaitClientLoad"] = static_cast<lua_Number>(rsJumpInGSWaitClientLoad);
    globals["rsWaitUnlockRoleData"] = static_cast<lua_Number>(rsWaitUnlockRoleData);
    globals["rsLogout"] = static_cast<lua_Number>(rsLogout);
    globals["rsTotal"] = static_cast<lua_Number>(rsTotal);
    globals["fcmsFull"] = static_cast<lua_Number>(fcmsFull);
    globals["fcmsHalf"] = static_cast<lua_Number>(fcmsHalf);
    globals["fcmsNone"] = static_cast<lua_Number>(fcmsNone);
    globals["fcmsTotal"] = static_cast<lua_Number>(fcmsTotal);
    globals["faceInvalid"] = static_cast<lua_Number>(faceInvalid);
    globals["faceTotal"] = static_cast<lua_Number>(faceTotal);
    globals["rpmInvalid"] = static_cast<lua_Number>(rpmInvalid);
    globals["rpmPeace"] = static_cast<lua_Number>(rpmPeace);
    globals["rpmGuild"] = static_cast<lua_Number>(rpmGuild);
    globals["rpmTeam"] = static_cast<lua_Number>(rpmTeam);
    globals["rpmSlayer"] = static_cast<lua_Number>(rpmSlayer);
    globals["rpmJustice"] = static_cast<lua_Number>(rpmJustice);
    globals["rpmMaster"] = static_cast<lua_Number>(rpmMaster);
    globals["rpmTotal"] = static_cast<lua_Number>(rpmTotal);
    globals["rprInvalid"] = static_cast<lua_Number>(rprInvalid);
    globals["rprNormal"] = static_cast<lua_Number>(rprNormal);
    globals["rprRedName"] = static_cast<lua_Number>(rprRedName);
    globals["rprCounterStrike"] = static_cast<lua_Number>(rprCounterStrike);
    globals["rprOpponentGuildMember"] = static_cast<lua_Number>(rprOpponentGuildMember);
    globals["rprLuckyKill"] = static_cast<lua_Number>(rprLuckyKill);
    globals["rprNoPunishment"] = static_cast<lua_Number>(rprNoPunishment);
    globals["rprTotal"] = static_cast<lua_Number>(rprTotal);
    globals["rncInvalid"] = static_cast<lua_Number>(rncInvalid);
    globals["rncWhite"] = static_cast<lua_Number>(rncWhite);
    globals["rncYellow"] = static_cast<lua_Number>(rncYellow);
    globals["rncRed"] = static_cast<lua_Number>(rncRed);
    globals["rncTotal"] = static_cast<lua_Number>(rncTotal);
    globals["ervtInvalid"] = static_cast<lua_Number>(ervtInvalid);
    globals["ervtTotal"] = static_cast<lua_Number>(ervtTotal);
    globals["rfrInvalid"] = static_cast<lua_Number>(rfrInvalid);
    globals["rfrDefault"] = static_cast<lua_Number>(rfrDefault);
    globals["rfrFriend"] = static_cast<lua_Number>(rfrFriend);
    globals["rfrEnemy"] = static_cast<lua_Number>(rfrEnemy);
    globals["rfrTotal"] = static_cast<lua_Number>(rfrTotal);
    globals["vlLevel0"] = static_cast<lua_Number>(vlLevel0);
    globals["vlLevel1"] = static_cast<lua_Number>(vlLevel1);
    globals["vlLevel2"] = static_cast<lua_Number>(vlLevel2);
    globals["vlLevel3"] = static_cast<lua_Number>(vlLevel3);
    globals["vlTotal"] = static_cast<lua_Number>(vlTotal);
    globals["MSG_PP_PERSONAL_ENEMY"] = static_cast<lua_Number>(MSG_PP_PERSONAL_ENEMY);
    globals["aprInvalid"] = static_cast<lua_Number>(aprInvalid);
    globals["aprWuDouChang"] = static_cast<lua_Number>(aprWuDouChang);
    globals["aprBaoku"] = static_cast<lua_Number>(aprBaoku);
    globals["aprYanWuChang"] = static_cast<lua_Number>(aprYanWuChang);
    globals["aprPray"] = static_cast<lua_Number>(aprPray);
    globals["aprEscort"] = static_cast<lua_Number>(aprEscort);
    globals["aprGuildBoss"] = static_cast<lua_Number>(aprGuildBoss);
    globals["aprSpring"] = static_cast<lua_Number>(aprSpring);
    globals["aprQuest"] = static_cast<lua_Number>(aprQuest);
    globals["aprYaoTa"] = static_cast<lua_Number>(aprYaoTa);
    globals["aprYouMingSea"] = static_cast<lua_Number>(aprYouMingSea);
    globals["aprTotal"] = static_cast<lua_Number>(aprTotal);
}

}
