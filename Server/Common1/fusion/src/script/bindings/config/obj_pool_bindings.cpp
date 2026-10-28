#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/obj_pool_config.h"

namespace cqyh::fusion::bindings {

void register_obj_pool_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto obj_pool_config_type = cqyh::lua::usertype<OBJ_POOL_CONFIG>(L, globals, "OBJ_POOL_CONFIG", "OBJ_POOL_CONFIG");
    obj_pool_config_type["nSceneCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nSceneCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nSceneCount) value) { self.nSceneCount = value; });
    obj_pool_config_type["nRegionCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nRegionCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nRegionCount) value) { self.nRegionCount = value; });
    obj_pool_config_type["nRoleCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nRoleCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nRoleCount) value) { self.nRoleCount = value; });
    obj_pool_config_type["nNpcCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nNpcCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nNpcCount) value) { self.nNpcCount = value; });
    obj_pool_config_type["nDoodadCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nDoodadCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nDoodadCount) value) { self.nDoodadCount = value; });
    obj_pool_config_type["nMissileCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nMissileCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nMissileCount) value) { self.nMissileCount = value; });
    obj_pool_config_type["nSpellInstanceCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nSpellInstanceCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nSpellInstanceCount) value) { self.nSpellInstanceCount = value; });
    obj_pool_config_type["nSpellSetCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nSpellSetCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nSpellSetCount) value) { self.nSpellSetCount = value; });
    obj_pool_config_type["nAuraInstanceCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nAuraInstanceCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nAuraInstanceCount) value) { self.nAuraInstanceCount = value; });
    obj_pool_config_type["nBulletCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nBulletCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nBulletCount) value) { self.nBulletCount = value; });
    obj_pool_config_type["nRuneCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nRuneCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nRuneCount) value) { self.nRuneCount = value; });
    obj_pool_config_type["nExtraModifierNodeCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nExtraModifierNodeCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nExtraModifierNodeCount) value) { self.nExtraModifierNodeCount = value; });
    obj_pool_config_type["nThreadNodeCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nThreadNodeCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nThreadNodeCount) value) { self.nThreadNodeCount = value; });
    obj_pool_config_type["nBTCtxCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nBTCtxCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nBTCtxCount) value) { self.nBTCtxCount = value; });
    obj_pool_config_type["nBTNodeCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nBTNodeCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nBTNodeCount) value) { self.nBTNodeCount = value; });
    obj_pool_config_type["nAITemplateCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nAITemplateCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nAITemplateCount) value) { self.nAITemplateCount = value; });
    obj_pool_config_type["nBlockCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nBlockCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nBlockCount) value) { self.nBlockCount = value; });
    obj_pool_config_type["nVolumeCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nVolumeCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nVolumeCount) value) { self.nVolumeCount = value; });
    obj_pool_config_type["nDropCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nDropCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nDropCount) value) { self.nDropCount = value; });
    obj_pool_config_type["nTeamCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nTeamCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nTeamCount) value) { self.nTeamCount = value; });
    obj_pool_config_type["nArenaTeamCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nArenaTeamCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nArenaTeamCount) value) { self.nArenaTeamCount = value; });
    obj_pool_config_type["nItemCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nItemCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nItemCount) value) { self.nItemCount = value; });
    obj_pool_config_type["nSignalCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nSignalCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nSignalCount) value) { self.nSignalCount = value; });
    obj_pool_config_type["nMasterTeacherPoolCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nMasterTeacherPoolCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nMasterTeacherPoolCount) value) { self.nMasterTeacherPoolCount = value; });
    obj_pool_config_type["nMasterStudentPoolCount"] = sol::property([](const OBJ_POOL_CONFIG& self) { return self.nMasterStudentPoolCount; }, [](OBJ_POOL_CONFIG& self, decltype(OBJ_POOL_CONFIG::nMasterStudentPoolCount) value) { self.nMasterStudentPoolCount = value; });
    globals["g_ObjPoolConfig"] = &g_ObjPoolConfig;
}

}
