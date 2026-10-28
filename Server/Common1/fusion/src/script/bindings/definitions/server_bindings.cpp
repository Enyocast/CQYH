#include "stdafx.h"
#include "sol_bindings.h"
#include "../registration.h"
#include "../../../../../define/server_def.h"

namespace cqyh::fusion::bindings {

void register_server_definitions(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    globals["sgsInvalid"] = static_cast<lua_Number>(sgsInvalid);
    globals["sgsInitializing"] = static_cast<lua_Number>(sgsInitializing);
    globals["sgsSelfReady"] = static_cast<lua_Number>(sgsSelfReady);
    globals["sgsAllReady"] = static_cast<lua_Number>(sgsAllReady);
    globals["sgsUnInitializing"] = static_cast<lua_Number>(sgsUnInitializing);
    globals["sgsClosing"] = static_cast<lua_Number>(sgsClosing);
    globals["sgsClosed"] = static_cast<lua_Number>(sgsClosed);
    globals["sgsTotal"] = static_cast<lua_Number>(sgsTotal);
    globals["stInvalid"] = static_cast<lua_Number>(stInvalid);
    globals["stGD"] = static_cast<lua_Number>(stGD);
    globals["stMS"] = static_cast<lua_Number>(stMS);
    globals["stDB"] = static_cast<lua_Number>(stDB);
    globals["stBS"] = static_cast<lua_Number>(stBS);
    globals["stLS"] = static_cast<lua_Number>(stLS);
    globals["stGT"] = static_cast<lua_Number>(stGT);
    globals["stGS"] = static_cast<lua_Number>(stGS);
    globals["stGM"] = static_cast<lua_Number>(stGM);
    globals["stDL"] = static_cast<lua_Number>(stDL);
    globals["stMM"] = static_cast<lua_Number>(stMM);
    globals["stMG"] = static_cast<lua_Number>(stMG);
    globals["stClient"] = static_cast<lua_Number>(stClient);
    globals["stMT"] = static_cast<lua_Number>(stMT);
    globals["stCS"] = static_cast<lua_Number>(stCS);
    globals["stNS"] = static_cast<lua_Number>(stNS);
    globals["stTL"] = static_cast<lua_Number>(stTL);
    globals["stAll"] = static_cast<lua_Number>(stAll);
    globals["stTotal"] = static_cast<lua_Number>(stTotal);
    globals["csdtInvalid"] = static_cast<lua_Number>(csdtInvalid);
    globals["csdtLogout"] = static_cast<lua_Number>(csdtLogout);
    globals["csdtTimeout"] = static_cast<lua_Number>(csdtTimeout);
    globals["csdtClient"] = static_cast<lua_Number>(csdtClient);
    globals["csdtDB"] = static_cast<lua_Number>(csdtDB);
    globals["csdtGS"] = static_cast<lua_Number>(csdtGS);
    globals["csdtGT"] = static_cast<lua_Number>(csdtGT);
    globals["csdtMS"] = static_cast<lua_Number>(csdtMS);
    globals["csdtMG"] = static_cast<lua_Number>(csdtMG);
    globals["csdtMM"] = static_cast<lua_Number>(csdtMM);
    globals["csdtTotal"] = static_cast<lua_Number>(csdtTotal);
    globals["ktInvalid"] = static_cast<lua_Number>(ktInvalid);
    globals["ktImmediately"] = static_cast<lua_Number>(ktImmediately);
    globals["ktDelayed"] = static_cast<lua_Number>(ktDelayed);
    globals["ktLogged"] = static_cast<lua_Number>(ktLogged);
    globals["ktTotal"] = static_cast<lua_Number>(ktTotal);
    globals["Group0"] = static_cast<lua_Number>(Group0);
    globals["Group1"] = static_cast<lua_Number>(Group1);
    globals["Group2"] = static_cast<lua_Number>(Group2);
    globals["Group3"] = static_cast<lua_Number>(Group3);
    globals["Group4"] = static_cast<lua_Number>(Group4);
    globals["Group5"] = static_cast<lua_Number>(Group5);
    globals["Group6"] = static_cast<lua_Number>(Group6);
    globals["Group7"] = static_cast<lua_Number>(Group7);
    globals["Group8"] = static_cast<lua_Number>(Group8);
    globals["Group9"] = static_cast<lua_Number>(Group9);
    globals["Group10"] = static_cast<lua_Number>(Group10);
    globals["Group11"] = static_cast<lua_Number>(Group11);
    globals["Group12"] = static_cast<lua_Number>(Group12);
    globals["Group13"] = static_cast<lua_Number>(Group13);
    globals["Group14"] = static_cast<lua_Number>(Group14);
    globals["Group15"] = static_cast<lua_Number>(Group15);
    globals["Group16"] = static_cast<lua_Number>(Group16);
    globals["Group17"] = static_cast<lua_Number>(Group17);
    globals["Group18"] = static_cast<lua_Number>(Group18);
    globals["Group19"] = static_cast<lua_Number>(Group19);
    globals["Group20"] = static_cast<lua_Number>(Group20);
    globals["Group21"] = static_cast<lua_Number>(Group21);
    globals["Group22"] = static_cast<lua_Number>(Group22);
    globals["Group23"] = static_cast<lua_Number>(Group23);
    globals["Group24"] = static_cast<lua_Number>(Group24);
    globals["Group25"] = static_cast<lua_Number>(Group25);
    globals["Group26"] = static_cast<lua_Number>(Group26);
    globals["Group27"] = static_cast<lua_Number>(Group27);
    globals["Group28"] = static_cast<lua_Number>(Group28);
    globals["Group29"] = static_cast<lua_Number>(Group29);
    globals["Group30"] = static_cast<lua_Number>(Group30);
    globals["Group31"] = static_cast<lua_Number>(Group31);
    globals["GroupAll"] = static_cast<lua_Number>(GroupAll);
    globals["SNDA_APPID"] = static_cast<lua_Number>(SNDA_APPID);
    globals["FCM_APPID"] = static_cast<lua_Number>(FCM_APPID);
    globals["MAX_GS_SESSION_COUNT"] = static_cast<lua_Number>(MAX_GS_SESSION_COUNT);
    globals["MAX_GT_SESSION_COUNT"] = static_cast<lua_Number>(MAX_GT_SESSION_COUNT);
    globals["MAX_MS_SESSION_COUNT"] = static_cast<lua_Number>(MAX_MS_SESSION_COUNT);
    globals["MAX_GM_SESSION_COUNT"] = static_cast<lua_Number>(MAX_GM_SESSION_COUNT);
    globals["MAX_GM_TL_SESSION_COUNT"] = static_cast<lua_Number>(MAX_GM_TL_SESSION_COUNT);
    globals["MAX_MG_SESSION_COUNT"] = static_cast<lua_Number>(MAX_MG_SESSION_COUNT);
    globals["MAX_REMOTE_SESSION_COUNT"] = static_cast<lua_Number>(MAX_REMOTE_SESSION_COUNT);
    globals["MAX_SERVER_GROUP_COUNT"] = static_cast<lua_Number>(MAX_SERVER_GROUP_COUNT);
    globals["MAX_AREA_COUNT"] = static_cast<lua_Number>(MAX_AREA_COUNT);
    globals["MAX_GUARD_COUNT_PER_AREA"] = static_cast<lua_Number>(MAX_GUARD_COUNT_PER_AREA);
    globals["MAX_CLIENT_SESSION_COUNT"] = static_cast<lua_Number>(MAX_CLIENT_SESSION_COUNT);
    globals["MAX_BS_CLIENT_SESSION_COUNT"] = static_cast<lua_Number>(MAX_BS_CLIENT_SESSION_COUNT);
    globals["MAX_EXTERNAL_IP_COUNT"] = static_cast<lua_Number>(MAX_EXTERNAL_IP_COUNT);
}

}
