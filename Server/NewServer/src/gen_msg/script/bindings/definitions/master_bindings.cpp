#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../../Common/define/master_def.h"

namespace cqyh::gen_msg::bindings {

void register_master_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["MAX_STUDENT_NUM"] = static_cast<lua_Number>(MAX_STUDENT_NUM);
    globals["GRADUATE_LEVEL"] = static_cast<lua_Number>(GRADUATE_LEVEL);
    globals["STUD_LEVEL_LOWER_LIMIT"] = static_cast<lua_Number>(STUD_LEVEL_LOWER_LIMIT);
    globals["REGET_MASTER_CD"] = static_cast<lua_Number>(REGET_MASTER_CD);
    globals["APPLY_VALID_TIME"] = static_cast<lua_Number>(APPLY_VALID_TIME);
    globals["SEND_MASTER_INFO_NUM"] = static_cast<lua_Number>(SEND_MASTER_INFO_NUM);
    globals["SEND_SOLO_INFO_NUM"] = static_cast<lua_Number>(SEND_SOLO_INFO_NUM);
    globals["MAX_CZ_TEXT_LENGTH"] = static_cast<lua_Number>(MAX_CZ_TEXT_LENGTH);
    globals["MAX_MASTER_SEND_APP_NUM"] = static_cast<lua_Number>(MAX_MASTER_SEND_APP_NUM);
    globals["MAX_MASTER_RECV_APP_NUM"] = static_cast<lua_Number>(MAX_MASTER_RECV_APP_NUM);
    sol::table master_state_namespace = globals["MASTER_STATE"].get_or_create<sol::table>();
    master_state_namespace["MASTER_NONE"] = static_cast<lua_Number>(MASTER_NONE);
    master_state_namespace["MASTER_STUDENT"] = static_cast<lua_Number>(MASTER_STUDENT);
    master_state_namespace["MASTER_TEACHER"] = static_cast<lua_Number>(MASTER_TEACHER);
    master_state_namespace["MASTER_BECOME_TEACHER"] = static_cast<lua_Number>(MASTER_BECOME_TEACHER);
    sol::table master_cong_type_namespace = globals["MASTER_CONG_TYPE"].get_or_create<sol::table>();
    master_cong_type_namespace["MASTER_CONG_BEGIN"] = static_cast<lua_Number>(MASTER_CONG_BEGIN);
    master_cong_type_namespace["MASTER_CONG_BY_FREE"] = static_cast<lua_Number>(MASTER_CONG_BY_FREE);
    master_cong_type_namespace["MASTER_CONG_BY_MONEY"] = static_cast<lua_Number>(MASTER_CONG_BY_MONEY);
    master_cong_type_namespace["MASTER_CONG_BY_GOLD"] = static_cast<lua_Number>(MASTER_CONG_BY_GOLD);
    master_cong_type_namespace["MASTER_CONG_END"] = static_cast<lua_Number>(MASTER_CONG_END);
    sol::table master_teacher_app_type_namespace = globals["MASTER_TEACHER_APP_TYPE"].get_or_create<sol::table>();
    master_teacher_app_type_namespace["MTAT_FROM_COMMON"] = static_cast<lua_Number>(MTAT_FROM_COMMON);
    master_teacher_app_type_namespace["MTAT_FROM_TWITTER"] = static_cast<lua_Number>(MTAT_FROM_TWITTER);
    sol::table mst_success_rsp_type_namespace = globals["MST_SUCCESS_RSP_TYPE"].get_or_create<sol::table>();
    mst_success_rsp_type_namespace["MST_APPLY_RECRUIT_SUCC"] = static_cast<lua_Number>(MST_APPLY_RECRUIT_SUCC);
    mst_success_rsp_type_namespace["MST_CANCEL_RECRUIT_SUCC"] = static_cast<lua_Number>(MST_CANCEL_RECRUIT_SUCC);
    sol::table mst_sync_gs_data_type_namespace = globals["MST_SYNC_GS_DATA_TYPE"].get_or_create<sol::table>();
    mst_sync_gs_data_type_namespace["MST_SYNC_GS_CD"] = static_cast<lua_Number>(MST_SYNC_GS_CD);
    mst_sync_gs_data_type_namespace["MST_SYNC_GS_TWITTER_CD"] = static_cast<lua_Number>(MST_SYNC_GS_TWITTER_CD);
    mst_sync_gs_data_type_namespace["MST_SYNC_PUNISH_EXP"] = static_cast<lua_Number>(MST_SYNC_PUNISH_EXP);
    mst_sync_gs_data_type_namespace["MST_SYNC_MASTER_EXP_DEC"] = static_cast<lua_Number>(MST_SYNC_MASTER_EXP_DEC);
}

}
