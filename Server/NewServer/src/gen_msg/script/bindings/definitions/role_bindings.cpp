#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/role_def.h"
#include "../../../../../../Common/define/scene_def.h"

namespace cqyh::gen_msg::bindings {

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
    sol::table e_role_logout_type_namespace = globals["ERoleLogoutType"].get_or_create<sol::table>();
    e_role_logout_type_namespace["rltInvalid"] = static_cast<lua_Number>(rltInvalid);
    e_role_logout_type_namespace["rltReturnLogin"] = static_cast<lua_Number>(rltReturnLogin);
    e_role_logout_type_namespace["rltReturnSelectRole"] = static_cast<lua_Number>(rltReturnSelectRole);
    e_role_logout_type_namespace["rltDisconnect"] = static_cast<lua_Number>(rltDisconnect);
    e_role_logout_type_namespace["rltKickout"] = static_cast<lua_Number>(rltKickout);
    e_role_logout_type_namespace["rltTotal"] = static_cast<lua_Number>(rltTotal);
    sol::table e_role_state_namespace = globals["ERoleState"].get_or_create<sol::table>();
    e_role_state_namespace["rsInvalid"] = static_cast<lua_Number>(rsInvalid);
    e_role_state_namespace["rsPreEntered"] = static_cast<lua_Number>(rsPreEntered);
    e_role_state_namespace["rsWaitRoleData"] = static_cast<lua_Number>(rsWaitRoleData);
    e_role_state_namespace["rsWaitMSApprove"] = static_cast<lua_Number>(rsWaitMSApprove);
    e_role_state_namespace["rsWaitClientLoad"] = static_cast<lua_Number>(rsWaitClientLoad);
    e_role_state_namespace["rsPlaying"] = static_cast<lua_Number>(rsPlaying);
    e_role_state_namespace["rsInJump"] = static_cast<lua_Number>(rsInJump);
    e_role_state_namespace["rsJumpInGSWaitClientLoad"] = static_cast<lua_Number>(rsJumpInGSWaitClientLoad);
    e_role_state_namespace["rsWaitUnlockRoleData"] = static_cast<lua_Number>(rsWaitUnlockRoleData);
    e_role_state_namespace["rsLogout"] = static_cast<lua_Number>(rsLogout);
    e_role_state_namespace["rsTotal"] = static_cast<lua_Number>(rsTotal);
    sol::table e_fcm_state_namespace = globals["EFcmState"].get_or_create<sol::table>();
    e_fcm_state_namespace["fcmsFull"] = static_cast<lua_Number>(fcmsFull);
    e_fcm_state_namespace["fcmsHalf"] = static_cast<lua_Number>(fcmsHalf);
    e_fcm_state_namespace["fcmsNone"] = static_cast<lua_Number>(fcmsNone);
    e_fcm_state_namespace["fcmsTotal"] = static_cast<lua_Number>(fcmsTotal);
    sol::table role_face_type_namespace = globals["ROLE_FACE_TYPE"].get_or_create<sol::table>();
    role_face_type_namespace["faceInvalid"] = static_cast<lua_Number>(faceInvalid);
    role_face_type_namespace["faceTotal"] = static_cast<lua_Number>(faceTotal);
    sol::table e_role_pk_mode_namespace = globals["ERolePkMode"].get_or_create<sol::table>();
    e_role_pk_mode_namespace["rpmInvalid"] = static_cast<lua_Number>(rpmInvalid);
    e_role_pk_mode_namespace["rpmPeace"] = static_cast<lua_Number>(rpmPeace);
    e_role_pk_mode_namespace["rpmGuild"] = static_cast<lua_Number>(rpmGuild);
    e_role_pk_mode_namespace["rpmTeam"] = static_cast<lua_Number>(rpmTeam);
    e_role_pk_mode_namespace["rpmSlayer"] = static_cast<lua_Number>(rpmSlayer);
    e_role_pk_mode_namespace["rpmJustice"] = static_cast<lua_Number>(rpmJustice);
    e_role_pk_mode_namespace["rpmMaster"] = static_cast<lua_Number>(rpmMaster);
    e_role_pk_mode_namespace["rpmTotal"] = static_cast<lua_Number>(rpmTotal);
    sol::table role_pk_result_namespace = globals["ROLE_PK_RESULT"].get_or_create<sol::table>();
    role_pk_result_namespace["rprInvalid"] = static_cast<lua_Number>(rprInvalid);
    role_pk_result_namespace["rprNormal"] = static_cast<lua_Number>(rprNormal);
    role_pk_result_namespace["rprRedName"] = static_cast<lua_Number>(rprRedName);
    role_pk_result_namespace["rprCounterStrike"] = static_cast<lua_Number>(rprCounterStrike);
    role_pk_result_namespace["rprOpponentGuildMember"] = static_cast<lua_Number>(rprOpponentGuildMember);
    role_pk_result_namespace["rprLuckyKill"] = static_cast<lua_Number>(rprLuckyKill);
    role_pk_result_namespace["rprNoPunishment"] = static_cast<lua_Number>(rprNoPunishment);
    role_pk_result_namespace["rprTotal"] = static_cast<lua_Number>(rprTotal);
    sol::table e_role_name_color_namespace = globals["ERoleNameColor"].get_or_create<sol::table>();
    e_role_name_color_namespace["rncInvalid"] = static_cast<lua_Number>(rncInvalid);
    e_role_name_color_namespace["rncWhite"] = static_cast<lua_Number>(rncWhite);
    e_role_name_color_namespace["rncYellow"] = static_cast<lua_Number>(rncYellow);
    e_role_name_color_namespace["rncRed"] = static_cast<lua_Number>(rncRed);
    e_role_name_color_namespace["rncTotal"] = static_cast<lua_Number>(rncTotal);
    sol::table e_role_var_type_namespace = globals["ERoleVarType"].get_or_create<sol::table>();
    e_role_var_type_namespace["ervtInvalid"] = static_cast<lua_Number>(ervtInvalid);
    e_role_var_type_namespace["ervtTotal"] = static_cast<lua_Number>(ervtTotal);
    sol::table role_faction_relation_namespace = globals["ROLE_FACTION_RELATION"].get_or_create<sol::table>();
    role_faction_relation_namespace["rfrInvalid"] = static_cast<lua_Number>(rfrInvalid);
    role_faction_relation_namespace["rfrDefault"] = static_cast<lua_Number>(rfrDefault);
    role_faction_relation_namespace["rfrFriend"] = static_cast<lua_Number>(rfrFriend);
    role_faction_relation_namespace["rfrEnemy"] = static_cast<lua_Number>(rfrEnemy);
    role_faction_relation_namespace["rfrTotal"] = static_cast<lua_Number>(rfrTotal);
    sol::table vip_level_namespace = globals["VIP_LEVEL"].get_or_create<sol::table>();
    vip_level_namespace["vlLevel0"] = static_cast<lua_Number>(vlLevel0);
    vip_level_namespace["vlLevel1"] = static_cast<lua_Number>(vlLevel1);
    vip_level_namespace["vlLevel2"] = static_cast<lua_Number>(vlLevel2);
    vip_level_namespace["vlLevel3"] = static_cast<lua_Number>(vlLevel3);
    vip_level_namespace["vlTotal"] = static_cast<lua_Number>(vlTotal);
    sol::table msg_paopao_type_namespace = globals["MSG_PAOPAO_TYPE"].get_or_create<sol::table>();
    msg_paopao_type_namespace["MSG_PP_PERSONAL_ENEMY"] = static_cast<lua_Number>(MSG_PP_PERSONAL_ENEMY);
    sol::table e_activity_pts_reason_namespace = globals["EActivityPtsReason"].get_or_create<sol::table>();
    e_activity_pts_reason_namespace["aprInvalid"] = static_cast<lua_Number>(aprInvalid);
    e_activity_pts_reason_namespace["aprWuDouChang"] = static_cast<lua_Number>(aprWuDouChang);
    e_activity_pts_reason_namespace["aprBaoku"] = static_cast<lua_Number>(aprBaoku);
    e_activity_pts_reason_namespace["aprYanWuChang"] = static_cast<lua_Number>(aprYanWuChang);
    e_activity_pts_reason_namespace["aprPray"] = static_cast<lua_Number>(aprPray);
    e_activity_pts_reason_namespace["aprEscort"] = static_cast<lua_Number>(aprEscort);
    e_activity_pts_reason_namespace["aprGuildBoss"] = static_cast<lua_Number>(aprGuildBoss);
    e_activity_pts_reason_namespace["aprSpring"] = static_cast<lua_Number>(aprSpring);
    e_activity_pts_reason_namespace["aprQuest"] = static_cast<lua_Number>(aprQuest);
    e_activity_pts_reason_namespace["aprYaoTa"] = static_cast<lua_Number>(aprYaoTa);
    e_activity_pts_reason_namespace["aprYouMingSea"] = static_cast<lua_Number>(aprYouMingSea);
    e_activity_pts_reason_namespace["aprTotal"] = static_cast<lua_Number>(aprTotal);
}

}
