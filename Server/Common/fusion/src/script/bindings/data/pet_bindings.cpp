#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../inc/pet_data.h"
#include "../../../../../../NewServer/inc/baselib/tabfile.h"

namespace cqyh::fusion::bindings {

void register_pet_bindings(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto pet_data_type = cqyh::lua::usertype<PET_DATA>(L, globals, "PET_DATA", "PET_DATA");
    pet_data_type["nID"] = sol::property([](const PET_DATA& self) { return self.nID; }, [](PET_DATA& self, decltype(PET_DATA::nID) value) { self.nID = value; });
    pet_data_type["nAIID"] = sol::property([](const PET_DATA& self) { return self.nAIID; }, [](PET_DATA& self, decltype(PET_DATA::nAIID) value) { self.nAIID = value; });
    pet_data_type["nBornType"] = sol::property([](const PET_DATA& self) { return self.nBornType; }, [](PET_DATA& self, decltype(PET_DATA::nBornType) value) { self.nBornType = value; });
    pet_data_type["nLevel"] = sol::property([](const PET_DATA& self) { return self.nLevel; }, [](PET_DATA& self, decltype(PET_DATA::nLevel) value) { self.nLevel = value; });
    pet_data_type["nAccurate"] = sol::property([](const PET_DATA& self) { return self.nAccurate; }, [](PET_DATA& self, decltype(PET_DATA::nAccurate) value) { self.nAccurate = value; });
    pet_data_type["nBonusphyAtkMax"] = sol::property([](const PET_DATA& self) { return self.nBonusphyAtkMax; }, [](PET_DATA& self, decltype(PET_DATA::nBonusphyAtkMax) value) { self.nBonusphyAtkMax = value; });
    pet_data_type["nBonusHPMaxA"] = sol::property([](const PET_DATA& self) { return self.nBonusHPMaxA; }, [](PET_DATA& self, decltype(PET_DATA::nBonusHPMaxA) value) { self.nBonusHPMaxA = value; });
    pet_data_type["nBonusHPMaxB"] = sol::property([](const PET_DATA& self) { return self.nBonusHPMaxB; }, [](PET_DATA& self, decltype(PET_DATA::nBonusHPMaxB) value) { self.nBonusHPMaxB = value; });
    pet_data_type["nMagDef"] = sol::property([](const PET_DATA& self) { return self.nMagDef; }, [](PET_DATA& self, decltype(PET_DATA::nMagDef) value) { self.nMagDef = value; });
    pet_data_type["nMagDefMax"] = sol::property([](const PET_DATA& self) { return self.nMagDefMax; }, [](PET_DATA& self, decltype(PET_DATA::nMagDefMax) value) { self.nMagDefMax = value; });
    pet_data_type.set_function("ReadLine", [](sol::table, signed int rnID, const char* rpcszName, PET_DATA* pData, CTabFile* pTabConfig, signed int nRow) -> decltype(auto) { decltype(auto) result = static_cast<bool>(PET_DATA::ReadLine(rnID,rpcszName,pData,pTabConfig,nRow)); return std::make_tuple(result, rnID, rpcszName); });
    globals.set_function("GetPetData", [](signed int nType, signed int nLevel) -> decltype(auto) { return GetPetData(nType,nLevel); });
}

}
