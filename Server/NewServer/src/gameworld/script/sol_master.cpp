#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "../../../Common/define/master_def.h"
#include "master.h"
#include "../../../inc/gameworld/role.h"

int sol_master_open(lua_State* L)
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
    globals["MASTER_NONE"] = static_cast<lua_Number>(MASTER_NONE);
    globals["MASTER_STUDENT"] = static_cast<lua_Number>(MASTER_STUDENT);
    globals["MASTER_TEACHER"] = static_cast<lua_Number>(MASTER_TEACHER);
    globals["MASTER_BECOME_TEACHER"] = static_cast<lua_Number>(MASTER_BECOME_TEACHER);
    globals["MASTER_CONG_BEGIN"] = static_cast<lua_Number>(MASTER_CONG_BEGIN);
    globals["MASTER_CONG_BY_FREE"] = static_cast<lua_Number>(MASTER_CONG_BY_FREE);
    globals["MASTER_CONG_BY_MONEY"] = static_cast<lua_Number>(MASTER_CONG_BY_MONEY);
    globals["MASTER_CONG_BY_GOLD"] = static_cast<lua_Number>(MASTER_CONG_BY_GOLD);
    globals["MASTER_CONG_END"] = static_cast<lua_Number>(MASTER_CONG_END);
    globals["MTAT_FROM_COMMON"] = static_cast<lua_Number>(MTAT_FROM_COMMON);
    globals["MTAT_FROM_TWITTER"] = static_cast<lua_Number>(MTAT_FROM_TWITTER);
    globals["MST_APPLY_RECRUIT_SUCC"] = static_cast<lua_Number>(MST_APPLY_RECRUIT_SUCC);
    globals["MST_CANCEL_RECRUIT_SUCC"] = static_cast<lua_Number>(MST_CANCEL_RECRUIT_SUCC);
    globals["MST_SYNC_GS_CD"] = static_cast<lua_Number>(MST_SYNC_GS_CD);
    globals["MST_SYNC_GS_TWITTER_CD"] = static_cast<lua_Number>(MST_SYNC_GS_TWITTER_CD);
    globals["MST_SYNC_PUNISH_EXP"] = static_cast<lua_Number>(MST_SYNC_PUNISH_EXP);
    globals["MST_SYNC_MASTER_EXP_DEC"] = static_cast<lua_Number>(MST_SYNC_MASTER_EXP_DEC);
    auto type1 = cqyh::lua::usertype<CMaster>(L, globals, "CMaster", "CMaster");
    type1.set_function("IsTeacher", [](CMaster* self) -> decltype(auto) { return static_cast<bool>(self->IsTeacher()); });
    type1.set_function("IsStudent", [](CMaster* self) -> decltype(auto) { return static_cast<bool>(self->IsStudent()); });
    type1.set_function("GetStudentCount", [](CMaster* self) -> decltype(auto) { return self->GetStudentCount(); });
    type1.set_function("IsStudentFull", [](CMaster* self) -> decltype(auto) { return static_cast<bool>(self->IsStudentFull()); });
    type1.set_function("GetState", [](CMaster* self) -> decltype(auto) { return self->GetState(); });
    type1.set_function("GetCD", [](CMaster* self) -> decltype(auto) { return self->GetCD(); });
    type1.set_function("GetStudentByIndex", [](CMaster* self, signed int nIndex) -> decltype(auto) { return self->GetStudentByIndex(nIndex); });
    type1.set_function("GetTeacherID", [](CMaster* self) -> decltype(auto) { return self->GetTeacherID(); });
    type1.set_function("LuaSyncMasterExpToMS", [](CMaster* self, CRole* poRole) -> decltype(auto) { return static_cast<bool>(self->LuaSyncMasterExpToMS(poRole)); });
    return 1;
}
