#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "scene_object.h"
#include "character.h"
#include "aura_instance.h"
#include "spell_instance.h"
#include "../../../inc/gameworld/spell_slot.h"
#include "../../../../Common/fusion/inc/rune_data.h"
#include "../../../inc/gameworld/item.h"
#include "../../../../Common/define/grid_def.h"
#include "../../../../Common/define/zone_def.h"
#include "../../../inc/gameworld/scene.h"
#include "../../../inc/gameworld/cooldown.h"
#include "../../../inc/gameworld/target_scanner.h"
#include "../../../inc/gameworld/attr_list.h"
#include "../../../inc/gameworld/aura.h"
#include "../../../inc/gameworld/ai_processor.h"
#include "../../../inc/gameworld/spell_book.h"
#include "../../../../Common/define/spell_def.h"
#include "../../../inc/baselib/math_ex.h"
#include "../../../inc/gameworld/region.h"

int sol_character_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<CSceneObject>(L, globals, "CSceneObject", "CSceneObject");
    type1.set_function("GetObjID", [](CSceneObject* self) -> decltype(auto) { return self->GetObjID(); });
    type1.set_function("GetObjType", [](CSceneObject* self) -> decltype(auto) { return self->GetObjType(); });
    type1.set_function("GetScene", [](CSceneObject* self) -> decltype(auto) { return self->GetScene(); });
    type1.set_function("GetRegion", [](CSceneObject* self) -> decltype(auto) { return self->GetRegion(); });
    type1.set_function("GetZone", [](CSceneObject* self) -> decltype(auto) { return self->GetZone(); });
    type1.set_function("GetGrid", [](CSceneObject* self) -> decltype(auto) { return self->GetGrid(); });
    type1.set_function("GetGridInstance", [](CSceneObject* self) -> decltype(auto) { return self->GetGridInstance(); });
    type1.set_function("SetX", [](CSceneObject* self, INT64 fX) -> decltype(auto) { self->SetX(fX); });
    type1.set_function("SetY", [](CSceneObject* self, INT64 fY) -> decltype(auto) { self->SetY(fY); });
    type1.set_function("SetZ", [](CSceneObject* self, INT64 fZ) -> decltype(auto) { self->SetZ(fZ); });
    type1.set_function("GetX", [](CSceneObject* self) -> decltype(auto) { return self->GetX(); });
    type1.set_function("GetY", [](CSceneObject* self) -> decltype(auto) { return self->GetY(); });
    type1.set_function("GetZ", [](CSceneObject* self) -> decltype(auto) { return self->GetZ(); });
    type1.set_function("SetFaceDirection", [](CSceneObject* self, signed int nFaceDirection) -> decltype(auto) { self->SetFaceDirection(nFaceDirection); });
    type1.set_function("GetFaceDirection", [](CSceneObject* self) -> decltype(auto) { return self->GetFaceDirection(); });
    type1.set_function("SetBodyType", [](CSceneObject* self, signed int nBodyType) -> decltype(auto) { self->SetBodyType(nBodyType); });
    type1.set_function("GetBodyType", [](CSceneObject* self) -> decltype(auto) { return self->GetBodyType(); });
    type1.set_function("CanTeleport", [](CSceneObject* self) -> decltype(auto) { return static_cast<bool>(self->CanTeleport()); });
    auto type2 = cqyh::lua::usertype<CAuraInstance>(L, globals, "CAuraInstance", "CAuraInstance", sol::base_classes, sol::bases<CAura>());
    type2.set_function("GetInstanceID", [](CAuraInstance* self) -> decltype(auto) { return self->GetInstanceID(); });
    auto type3 = cqyh::lua::usertype<CCoolDown>(L, globals, "CCoolDown", "CCoolDown");
    type3.set_function("Add", [](CCoolDown* self, signed int nKey, signed int nInterval) -> decltype(auto) { return static_cast<bool>(self->Add(nKey,nInterval)); });
    type3.set_function("Reset", [](CCoolDown* self, signed int nKey) -> decltype(auto) { self->Reset(nKey); });
    type3.set_function("CheckReady", [](CCoolDown* self, signed int nKey) -> decltype(auto) { return static_cast<bool>(self->CheckReady(nKey)); });
    type3.set_function("GetRemainFrm", [](CCoolDown* self, signed int nKey) -> decltype(auto) { return self->GetRemainFrm(nKey); });
    type3.set_function("Enable", [](CCoolDown* self, bool bEnabled) -> decltype(auto) { self->Enable(bEnabled); });
    auto type4 = cqyh::lua::usertype<CTargetScanner>(L, globals, "CTargetScanner", "CTargetScanner");
    type4.set_function("new", [](sol::table) -> decltype(auto) { return new CTargetScanner(); });
    type4.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<CTargetScanner>(new CTargetScanner()); });
    type4.set_function("delete", [](CTargetScanner* self) -> decltype(auto) { delete self; });
    type4.set_function("GetTargetX", [](CTargetScanner* self) -> decltype(auto) { return self->GetTargetX(); });
    type4.set_function("GetTargetY", [](CTargetScanner* self) -> decltype(auto) { return self->GetTargetY(); });
    type4.set_function("GetTargetZ", [](CTargetScanner* self) -> decltype(auto) { return self->GetTargetZ(); });
    auto type5 = cqyh::lua::usertype<CSpellInstance>(L, globals, "CSpellInstance", "CSpellInstance");
    type5.set_function("new", [](sol::table) -> decltype(auto) { return new CSpellInstance(); });
    type5.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<CSpellInstance>(new CSpellInstance()); });
    type5.set_function("delete", [](CSpellInstance* self) -> decltype(auto) { delete self; });
    type5.set_function("GetScanner", [](CSpellInstance* self) -> decltype(auto) { return self->GetScanner(); });
    auto type6 = cqyh::lua::usertype<CCharacter>(L, globals, "CCharacter", "CCharacter", sol::base_classes, sol::bases<CSceneObject>());
    type6.set_function("JumpTo", [](CCharacter* self, INT64 llX, INT64 llY, INT64 llZ, signed int nFaceDirection) -> decltype(auto) { return static_cast<bool>(self->JumpTo(llX,llY,llZ,nFaceDirection)); });
    type6.set_function("GetClass", [](CCharacter* self) -> decltype(auto) { return self->GetClass(); });
    type6.set_function("GetSex", [](CCharacter* self) -> decltype(auto) { return self->GetSex(); });
    type6.set_function("GetLevel", [](CCharacter* self) -> decltype(auto) { return self->GetLevel(); });
    type6.set_function("GetName", [](CCharacter* self) -> decltype(auto) { return self->GetName(); });
    type6.set_function("SetClass", [](CCharacter* self, signed int nClass) -> decltype(auto) { self->SetClass(nClass); });
    type6.set_function("SetSex", [](CCharacter* self, signed int nSex) -> decltype(auto) { self->SetSex(nSex); });
    type6.set_function("SetLevel", [](CCharacter* self, signed int nLevel) -> decltype(auto) { return static_cast<bool>(self->SetLevel(nLevel)); });
    type6.set_function("GetAttr", [](CCharacter* self, signed int eAttrType) -> decltype(auto) { return self->GetAttr(eAttrType); });
    type6.set_function("GetAttrList", [](CCharacter* self) -> decltype(auto) { return self->GetAttrList(); });
    type6.set_function("SetInCutScene", [](CCharacter* self, bool bInCutScene, signed int nDurationFrm) -> decltype(auto) { self->SetInCutScene(bInCutScene,nDurationFrm); });
    type6.set_function("MoveTo", [](CCharacter* self, signed int nDestX, signed int nDestY) -> decltype(auto) { return static_cast<bool>(self->MoveTo(nDestX,nDestY)); });
    type6.set_function("Die", [](CCharacter* self, signed int nParam) -> decltype(auto) { return static_cast<bool>(self->Die(nParam)); });
    type6.set_function("Revive", [](CCharacter* self, signed int nParam, signed int nHpPercent) -> decltype(auto) { return static_cast<bool>(self->Revive(nParam,nHpPercent)); });
    type6.set_function("RotateTo", [](CCharacter* self, signed int nFaceDirection, signed int nDurationFrm) -> decltype(auto) { self->RotateTo(nFaceDirection,nDurationFrm); });
    type6.set_function("SetCanRun", [](CCharacter* self, bool bCanRun) -> decltype(auto) { self->SetCanRun(bCanRun); });
    type6.set_function("GetMoveState", [](CCharacter* self) -> decltype(auto) { return self->GetMoveState(); });
    type6.set_function("SetHome", [](CCharacter* self, signed int nSceneID, signed int nHomeX, signed int nHomeY, signed int nHomeZ) -> decltype(auto) { self->SetHome(nSceneID,nHomeX,nHomeY,nHomeZ); });
    type6.set_function("GetHomeX", [](CCharacter* self) -> decltype(auto) { return self->GetHomeX(); });
    type6.set_function("GetHomeY", [](CCharacter* self) -> decltype(auto) { return self->GetHomeY(); });
    type6.set_function("GetHomeZ", [](CCharacter* self) -> decltype(auto) { return self->GetHomeZ(); });
    type6.set_function("CancelCast", [](CCharacter* self) -> decltype(auto) { self->CancelCast(); });
    type6.set_function("IsCasting", [](CCharacter* self) -> decltype(auto) { return static_cast<bool>(self->IsCasting()); });
    type6.set_function("EquipRune", [](CCharacter* self, const RUNE_DATA* pRuneData, Item* poItem) -> decltype(auto) { return self->EquipRune(pRuneData,poItem); });
    type6.set_function("UnEquipRune", [](CCharacter* self, const RUNE_DATA* pRuneData, Item* poItem) -> decltype(auto) { return static_cast<bool>(self->UnEquipRune(pRuneData,poItem)); });
    type6.set_function("GetSpellSlot", [](CCharacter* self, signed int nIndex) -> decltype(auto) { return self->GetSpellSlot(nIndex); });
    type6.set_function("CastSpell", [](CCharacter* self, signed int nSpellID, CCharacter* poTarget, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ) -> decltype(auto) { return self->CastSpell(nSpellID,poTarget,nTargetX,nTargetY,nTargetZ); });
    type6.set_function("PlayAction", [](CCharacter* self, unsigned int dwActionID) -> decltype(auto) { return static_cast<bool>(self->PlayAction(dwActionID)); });
    type6.set_function("GetCastingSpell", [](CCharacter* self) -> decltype(auto) { return self->GetCastingSpell(); });
    type6.set_function("GetHp", [](CCharacter* self) -> decltype(auto) { return self->GetHp(); });
    type6.set_function("SetHp", [](CCharacter* self, signed int nHp) -> decltype(auto) { self->SetHp(nHp); });
    type6.set_function("ChangeHp", [](CCharacter* self, signed int nValue, signed int nReason) -> decltype(auto) { self->ChangeHp(nValue,nReason); });
    type6.set_function("GetMp", [](CCharacter* self) -> decltype(auto) { return self->GetMp(); });
    type6.set_function("ChangeMp", [](CCharacter* self, signed int nValue) -> decltype(auto) { self->ChangeMp(nValue); });
    type6.set_function("CanAttack", [](CCharacter* self, CCharacter* poChar) -> decltype(auto) { return static_cast<bool>(self->CanAttack(poChar)); });
    type6.set_function("GetSpellBook", [](CCharacter* self) -> decltype(auto) { return self->GetSpellBook(); });
    type6.set_function("AppendAura", [](CCharacter* self, CAura* pAuraInfo, CCharacter* poCaster, unsigned int dwFromObjID, ExtraParam* pExParam, signed int nNewDurationFrm, signed int nNewStackCount, signed int nSpellID, signed int nSpellLevel) -> decltype(auto) { return self->AppendAura(pAuraInfo,poCaster,dwFromObjID,pExParam,nNewDurationFrm,nNewStackCount,nSpellID,nSpellLevel); });
    type6.set_function("GetFirstAura", [](CCharacter* self, signed int nAuraID) -> decltype(auto) { return self->GetFirstAura(nAuraID); });
    type6.set_function("RemoveAura", [](CCharacter* self, CAuraInstance* pAura, bool bTrigOnRemove) -> decltype(auto) { self->RemoveAura(pAura,bTrigOnRemove); });
    type6.set_function("RemoveAuraByType", [](CCharacter* self, signed int nType) -> decltype(auto) { return static_cast<bool>(self->RemoveAuraByType(nType)); });
    type6.set_function("RemoveAuraBySubType", [](CCharacter* self, signed int nSubType) -> decltype(auto) { return static_cast<bool>(self->RemoveAuraBySubType(nSubType)); });
    type6.set_function("IsDead", [](CCharacter* self) -> decltype(auto) { return static_cast<bool>(self->IsDead()); });
    type6.set_function("GetFlag", [](CCharacter* self) -> decltype(auto) { return self->GetFlag(); });
    type6.set_function("GetExFlag", [](CCharacter* self) -> decltype(auto) { return self->GetExFlag(); });
    type6.set_function("GetCCFlag", [](CCharacter* self) -> decltype(auto) { return self->GetCCFlag(); });
    type6.set_function("IncControlCount", [](CCharacter* self, signed int nControlType) -> decltype(auto) { return static_cast<bool>(self->IncControlCount(nControlType)); });
    type6.set_function("DecControlCount", [](CCharacter* self, signed int nControlType) -> decltype(auto) { return static_cast<bool>(self->DecControlCount(nControlType)); });
    type6.set_function("GetControlCount", [](CCharacter* self, signed int nControlType) -> decltype(auto) { return self->GetControlCount(nControlType); });
    type6.set_function("SetLastCasterID", [](CCharacter* self, unsigned int dwID) -> decltype(auto) { self->SetLastCasterID(dwID); });
    type6.set_function("GetLastCasterID", [](CCharacter* self) -> decltype(auto) { return self->GetLastCasterID(); });
    type6.set_function("GetLastCasterTimer", [](CCharacter* self) -> decltype(auto) { return self->GetLastCasterTimer(); });
    type6.set_function("SetLastTargetID", [](CCharacter* self, unsigned int dwObjID) -> decltype(auto) { self->SetLastTargetID(dwObjID); });
    type6.set_function("GetLastTargetID", [](CCharacter* self) -> decltype(auto) { return self->GetLastTargetID(); });
    type6.set_function("GetLastTargetTimer", [](CCharacter* self) -> decltype(auto) { return self->GetLastTargetTimer(); });
    type6.set_function("SetDropOwnerID", [](CCharacter* self, unsigned int dwID) -> decltype(auto) { self->SetDropOwnerID(dwID); });
    type6.set_function("GetDropOwnerID", [](CCharacter* self) -> decltype(auto) { return self->GetDropOwnerID(); });
    type6.set_function("SelectFocus", [](CCharacter* self, unsigned int dwTargetID) -> decltype(auto) { self->SelectFocus(dwTargetID); });
    type6.set_function("GetFocusID", [](CCharacter* self) -> decltype(auto) { return self->GetFocusID(); });
    type6.set_function("Say", [](CCharacter* self, unsigned int dwTargetID, unsigned int dwLocation, const char* pcszMessage) -> decltype(auto) { return self->Say(dwTargetID,dwLocation,pcszMessage); });
    type6.set_function("SendMail", [](CCharacter* self, unsigned int dwRoleID, signed int nMailTemplateID) -> decltype(auto) { return static_cast<bool>(self->SendMail(dwRoleID,nMailTemplateID)); });
    type6.set_function("SendMail", sol::overload([](CCharacter* self, unsigned int dwRoleID, signed int nMailTemplateID, signed int nItemID, signed int nItemCount) -> decltype(auto) { return static_cast<bool>(self->SendMail(dwRoleID,nMailTemplateID,nItemID,nItemCount)); }, [](CCharacter* self, unsigned int dwRoleID, signed int nMailTemplateID) -> decltype(auto) { return static_cast<bool>(self->SendMail(dwRoleID,nMailTemplateID)); }));
    type6.set_function("SetAIProcessor", [](CCharacter* self, unsigned int nAIID) -> decltype(auto) { return static_cast<bool>(self->SetAIProcessor(nAIID)); });
    type6.set_function("GetAIProcessor", [](CCharacter* self) -> decltype(auto) { return self->GetAIProcessor(); });
    type6.set_function("GetOriginalAiID", [](CCharacter* self) -> decltype(auto) { return self->GetOriginalAiID(); });
    type6.set_function("SetGlobalCDDelayFrame", [](CCharacter* self, signed int nFrame) -> decltype(auto) { self->SetGlobalCDDelayFrame(nFrame); });
    type6.set_function("GetGlobalCDDelayFrame", [](CCharacter* self) -> decltype(auto) { return self->GetGlobalCDDelayFrame(); });
    type6.set_function("GetCoolDown", [](CCharacter* self) -> decltype(auto) { return self->GetCoolDown(); });
    type6.set_function("GetHostID", [](CCharacter* self) -> decltype(auto) { return self->GetHostID(); });
    type6.set_function("Mine", [](CCharacter* self, INT64 llDestX, INT64 llDestY) -> decltype(auto) { return static_cast<bool>(self->Mine(llDestX,llDestY)); });
    auto type7 = cqyh::lua::usertype<CFlagBits>(L, globals, "CFlagBits", "CFlagBits");
    type7.set_function("new", [](sol::table) -> decltype(auto) { return new CFlagBits(); });
    type7.set_function("new_local", [](sol::table) -> decltype(auto) { return std::unique_ptr<CFlagBits>(new CFlagBits()); });
    type7.set_function("CheckFlag", [](CFlagBits* self, unsigned int eBit) -> decltype(auto) { return static_cast<bool>(self->CheckFlag(eBit)); });
    type7.set_function("SetFlag", [](CFlagBits* self, unsigned int eBit) -> decltype(auto) { self->SetFlag(eBit); });
    type7.set_function("ClearFlag", [](CFlagBits* self, unsigned int eBit) -> decltype(auto) { self->ClearFlag(eBit); });
    type7.set_function("ResetFlag", [](CFlagBits* self) -> decltype(auto) { self->ResetFlag(); });
    type7.set_function("FlagIncludeBits", [](CFlagBits* self, unsigned int dwMask) -> decltype(auto) { return static_cast<bool>(self->FlagIncludeBits(dwMask)); });
    type7.set_function("FlagNotIncludeBits", [](CFlagBits* self, unsigned int dwMask) -> decltype(auto) { return static_cast<bool>(self->FlagNotIncludeBits(dwMask)); });
    type7.set_function("GetFlag", [](CFlagBits* self) -> decltype(auto) { return self->GetFlag(); });
    return 1;
}
