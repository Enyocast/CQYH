#include "stdafx.h"
#include "spell_bullet.h"
#include "bullet_modifier.h"
#include "game_world.h"
#include "spell_config.h"
#include "npc_data.h"
#include "chat_def.h"

#if defined(WIN32) | defined(WIN64)
#pragma warning(disable:4102)
#endif	// WIN32 | WIN64

INT32 ModifierBullet_001(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT64 x1 = 0;
    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    x1 = nParam1 + poBullet->GetX() * nParam2 / RATE_MAX;

    poBullet->SetX(x1);

    return mrcTrue;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_002(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRand = 0;
    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    nRand = g_Random(RATE_MAX);

    if (nRand < nParam1)
        return mrcTrue;

    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_003(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    INT64 nDistance = nParam1 * POINT_PER_CM;
    INT32 nSpeed = nParam2 * POINT_PER_CM / 1000;
    INT64 llDestX, llDestY = 0;
    INT32 nDirection = 0;
    CCharacter* pTarget = NULL;
    CCharacter* pCaster = NULL;

    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    pTarget = poBullet->GetTarget();
    LOG_PROCESS_ERROR(pTarget);

    //PROCESS_ERROR(!pTarget->GetFlag().CheckFlag(cfImmunePassiveMove));

    //PROCESS_ERROR(!pTarget->CheckFlag(cfImmuneControl));

    pCaster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(pCaster);

    nDirection = g_GetDirection(pCaster->GetX(), pCaster->GetY(), pTarget->GetX(), pTarget->GetY());

    llDestX = pTarget->GetX() + nDistance * g_Cos(nDirection) / SIN_COS_NUMBER;
    llDestY = pTarget->GetY() + nDistance * g_Sin(nDirection) / SIN_COS_NUMBER;

    //DBG("KnockBack From (%llu, %llu, %llu) To (%llu, %llu)", pTarget->GetX(), pTarget->GetY(), pTarget->GetZ(), llDestX, llDestY);

    if (pTarget->KnockBack(nSpeed, llDestX, llDestY))
        return mrcTrue;

    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_004(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CAura* poAuraInfo = NULL;
    CCharacter* target = NULL;
    CCharacter* caster = NULL;
    CAuraInstance* poAuraInstance = NULL;
    SpellEventNode* poEventNode = NULL;
    CCharacter* poEventOwner = NULL;
    INT32 nRootSpellID = 0;
    INT32 nRootSpellLevel = 0;

    INT32 nAuraID = abs(nParam1);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poAuraInfo = CSpellConfig::GetInstance().FindAuraTemplate(nAuraID);
    LOG_PROCESS_ERROR(poAuraInfo);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nRootSpellID = poBullet->GetSpellID();
    nRootSpellLevel = poBullet->GetSpellLevel();

    poEventOwner = poBullet->GetEventOwner();

    if (poEventOwner != NULL)
    {
        poEventNode = poEventOwner->GetPendingEventNode();

        if (poEventNode != NULL)
        {
            nRootSpellID = poEventNode->nRootSpellID;
            nRootSpellLevel = poEventNode->nRootSpellLevel;
        }
    }

    poAuraInstance = target->AppendAura(poAuraInfo, caster, poBullet->GetFromObjID(), (ExtraParam*)pExParam, CONVERT_TIME(nParam3), 0, nRootSpellID, nRootSpellLevel);
    PROCESS_SUCCESS(poAuraInstance == NULL);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    CRI("param1: %d, param2: %d, param3: %d", nParam1, nParam2, nParam3);
    return mrcError;
}

INT32 ModifierBullet_005(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 mp = 0;
    INT64 x1 = 0;

    CBullet* bullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(bullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(bullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    mp = caster->GetMp();
    x1 = bullet->GetX();
    x1 = x1 * (RATE_MAX + nParam1 * mp) / RATE_MAX;
    bullet->SetX(x1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_006(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CAura* poAuraInfo = NULL;
    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    CAuraInstance* poAuraInstace = NULL;
    SpellEventNode* poEventNode = NULL;
    CCharacter* poEventOwner = NULL;
    CCharacter* poAuraCaster = NULL;
    INT32 nRootSpellID = 0;
    INT32 nRootSpellLevel = 0;

    INT32 nAuraID = abs(nParam1);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poAuraInfo = CSpellConfig::GetInstance().FindAuraTemplate(nAuraID);
    LOG_PROCESS_ERROR(poAuraInfo);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nRootSpellID = poBullet->GetSpellID();
    nRootSpellLevel = poBullet->GetSpellLevel();

    poEventOwner = poBullet->GetEventOwner();

    if (poEventOwner != NULL)
    {
        poEventNode = poEventOwner->GetPendingEventNode();

        if (poEventNode != NULL)
        {
            nRootSpellID = poEventNode->nRootSpellID;
            nRootSpellLevel = poEventNode->nRootSpellLevel;
        }
    }

    if (nParam2 > 0)
        poAuraCaster = caster;
    else
        poAuraCaster = target;

    poAuraInstace = caster->AppendAura(poAuraInfo, poAuraCaster, poBullet->GetFromObjID(), (ExtraParam*)pExParam, CONVERT_TIME(nParam3), 0, nRootSpellID, nRootSpellLevel);
    PROCESS_SUCCESS(poAuraInstace == NULL);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_007(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nAttackType = abs(nParam1);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    PROCESS_SUCCESS(poBullet->GetSpellAttr(satAttackType) != nAttackType);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_008(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nPctValue = nParam1;
    INT32 nAddValue = nParam2;
    INT32 nEffectValue = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    nEffectValue = poBullet->GetEffectValue();

    nEffectValue = g_Max(0LL, nEffectValue * (RATE_MAX + nPctValue) / RATE_MAX + nAddValue);

    poBullet->SetEffectValue(nEffectValue);

    return mrcTrue;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_009(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nEffectValue = 0;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nEffectValue = poBullet->GetEffectValue();

    if (poBullet->GetBulletType() == betDamage && nEffectValue >= target->GetHp() + target->GetRemainAbsorb())
        return mrcTrue;

    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_010(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    INT32 nAbsValue = nParam1;
    INT32 nPctValue = nParam2;
    INT32 nResultValue = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poBullet->SetEffectValue(0);

    nResultValue = target->GetAttr(catMaxHp) * nPctValue / RATE_MAX + nAbsValue;

    target->ChangeHp(nResultValue - target->GetHp(), cdrSpell);

    return mrcTrue;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_011(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    INT32 nPctValue = abs(nParam1);
    INT32 nAbsValue = abs(nParam2);
    INT32 nModifiedValue = 0;
    INT32 nEffectValue = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nEffectValue = poBullet->GetEffectValue();

    nModifiedValue = target->GetAttr(catMaxHp) * nPctValue / RATE_MAX + nAbsValue;

    poBullet->SetEffectValue(nModifiedValue);

    return mrcTrue;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_012(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nSubSpellID = abs(nParam1);
    CSpell* poSpell = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    poSpell = CSpellConfig::GetInstance().FindSpellTemplate(nSubSpellID, poBullet->GetSpellLevel(), 0);
    LOG_PROCESS_ERROR(poSpell);

    nRetCode = caster->CastInstantSpell(caster, poSpell, target, target->GetX(), target->GetY(), target->GetZ());
    PROCESS_SUCCESS(nRetCode != errSuccess);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_013(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    INT32 nAttrID = abs(nParam1);
    INT32 nRand = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nAttrID >= catDefault && nAttrID < catTotal);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nRand = g_Random(RATE_MAX);

    if (nRand < target->GetAttr(nAttrID))
        return mrcTrue;

    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_014(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CSpellSlot* poSlot = NULL;
    INT32 nSpellSlotID = nParam1;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    LOG_PROCESS_ERROR(nSpellSlotID >= qssSlotBegin && nSpellSlotID < qssSlotCount);

    poSlot = target->GetSpellSlot(nSpellSlotID);
    LOG_PROCESS_ERROR(poSlot);

    poSlot->SetNextTargetID(poBullet->GetCasterID());

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_015(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    INT32 nWantedFlag = nParam1;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    PROCESS_SUCCESS(!poBullet->GetEffectFlag().CheckFlag(nWantedFlag));

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_016(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    INT32 nFlag = abs(nParam1);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam1 > 0)
        target->GetFlag().SetFlag(nFlag);
    else if (nParam1 < 0)
        target->GetFlag().ClearFlag(nFlag);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_017(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 nFlag = abs(nParam1);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    if (nParam1 > 0)
        caster->GetFlag().SetFlag(nFlag);
    else if (nParam1 < 0)
        caster->GetFlag().ClearFlag(nFlag);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_018(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 nPct = abs(nParam1);
    INT32 nRealPct = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    LOG_PROCESS_ERROR(caster->GetAttr(catMaxMp) > 0);

    nRealPct = caster->GetMp() * RATE_MAX / caster->GetAttr(catMaxMp);

    if (nRealPct >= nPct)
        return mrcTrue;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_019(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 nPct = abs(nParam1);
    INT32 nRealPct = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    if (caster->GetMp() >= nPct)
        return mrcTrue;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_020(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 nResCost = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    if (nParam1 == 0 && nParam2 == 0)
        nResCost = poBullet->GetSpellAttr(satModifierCostValue) + (INT64)poBullet->GetSpellAttr(satModifierCostValuePct) * caster->GetAttr(catMaxMp) / RATE_MAX;
    else
        nResCost = nParam1 + (INT64)nParam2 * caster->GetAttr(catMaxMp) / RATE_MAX;

    if (nResCost >= 0)
        PROCESS_SUCCESS(nResCost > caster->GetMp());
    else
        PROCESS_SUCCESS((caster->GetMp() - nResCost) > caster->GetAttr(catMaxMp));

    caster->ChangeMp(-nResCost);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_021(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nEffectValue = 0;
    CCharacter* poCaster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poCaster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(poCaster == NULL);

    nEffectValue = poBullet->GetEffectValue();
    PROCESS_SUCCESS(poBullet->GetBulletType() != betDamage);

    poCaster->DirectlyHpChange(nEffectValue * nParam1 / RATE_MAX + nParam2 + poCaster->GetAttr(catMaxHp) * nParam3 / RATE_MAX);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_022(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nEffectValue = 0;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if ((nParam1 & (1 << target->GetObjType())) != 0 && (nParam2 & (1 << target->GetSpecies())) != 0)
        return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_023(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nFaceAngleDiff = 0;
    INT32 nTargetDirDiff = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    if (nParam1 == 0)
        return mrcTrue;

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nFaceAngleDiff = NormalizeDirection(target->GetFaceDirection() - caster->GetFaceDirection());
    nTargetDirDiff = NormalizeDirection(caster->GetFaceDirection() - g_GetDirection(caster->GetX(), caster->GetY(), target->GetX(), target->GetY()));

    PROCESS_ERROR(g_Cos(nTargetDirDiff) >= 0);

    if (nParam1 == 1 && g_Cos(nFaceAngleDiff) < 0)
        return mrcTrue;

    if (nParam1 == 2 && g_Cos(nFaceAngleDiff) >= 0)
        return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_024(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nCooldownFrm = 0;

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    nCooldownFrm = caster->GetCoolDown().GetRemainFrm(MakeCoolDownID(COOLDOWN_SPELL, poBullet->GetSpellID()));

    if (nParam2 == 0)
        return nCooldownFrm > CONVERT_TIME(nParam1);
    else if (nParam2 == 1)
        return nCooldownFrm <= CONVERT_TIME(nParam1);

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_025(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRemainFrm = 0;
    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nCoolDownFrm = -CONVERT_TIME(nParam1);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    caster->ChangeCooldown(MakeCoolDownID(COOLDOWN_SPELL, poBullet->GetSpellID()), nCoolDownFrm);

    {
        const SPELL_ENTRY* inf = poBullet->GetSpellData();

        for (INT32 i = 0; i < inf->m_nCdGrpCount; i++)
        {
            caster->ChangeCooldown(MakeCoolDownID(COOLDOWN_GROUP, inf->m_CdGrp[i].m_nCdGrpID), nCoolDownFrm);
        }
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_026(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;

    CItemBag* poBag = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);
    LOG_PROCESS_ERROR(caster->GetObjType() == otRole);

    poBag = ((CRole*)caster)->GetItemBag();
    LOG_PROCESS_ERROR(poBag);

#ifndef _ROBOT
    PROCESS_SUCCESS(poBag->GetWeaponType() != nParam1);
#endif

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_027(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT64 nResult = 0;
    INT32 nAtkHi = 0;
    INT32 eSpellAtkType = 0;

    static INT32 s_AtkTableHi[] =
    {
        catDefault,		// 1  none
        catMaxPhyAtk,	// 7  melee
        catMaxMagAtk,	// 9  magic
        catMaxTaoAtk,	// 11 magic
    };

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    eSpellAtkType = poBullet->GetSpellAttr(satAttackType);
    LOG_PROCESS_ERROR(eSpellAtkType > spatInvalid && eSpellAtkType < spatTotal);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    nAtkHi = caster->GetAttr(s_AtkTableHi[eSpellAtkType]);

    nResult = nAtkHi * caster->GetMp() * nParam2 / nParam1 / RATE_MAX + nParam3;

    poBullet->SetX(poBullet->GetX() + nResult);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_028(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 nEffectValue = 0;
    INT32 nHp = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);
    PROCESS_SUCCESS(poBullet->GetBulletType() != betDamage);

    nEffectValue = poBullet->GetEffectValue();

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    nHp = caster->GetHp();

    nEffectValue = nEffectValue * nParam1 / RATE_MAX + nParam2;

    caster->DirectlyHpChange(-nEffectValue);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_029(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    INT64 llDist = CONVERT_LENGTH(nParam1);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (g_GetDistance3D(caster->GetX(), caster->GetY(), caster->GetZ(), target->GetX(), target->GetY(), target->GetZ()) <= llDist * llDist)
        return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_030(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    return target->GetExFlag().CheckFlag(nParam1);
Exit0:
    return mrcError;
}

INT32 ModifierBullet_031(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poBullet->SetX(target->GetAttr(catMaxHp) * nParam1 / RATE_MAX);

    return mrcTrue;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_032(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    return poBullet->GetBulletType() == betHeal;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_033(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nValue = 0;
    INT32 nCurrentMp = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nValue = nParam1 + target->GetAttr(catMaxMp) * nParam2 / RATE_MAX;

    target->ChangeMp(nValue);

    if (nValue > 0 && nParam3 > 0)
    {
        caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
        PROCESS_SUCCESS(caster == NULL);

        nCurrentMp = caster->GetMp() + nValue * nParam3 / RATE_MAX;
        caster->ChangeMp(nValue * nParam3 / RATE_MAX);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_034(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CAuraInstance* poAura = NULL;
    INT32 nRetCode = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam1 > 0)
    {
        poAura = target->GetFirstAura(nParam1);
        PROCESS_SUCCESS(poAura == NULL);

        target->RemoveAura(poAura, TRUE);
    }

    if (nParam2 > 0)
    {
        nRetCode = target->RemoveAuraByType(nParam2);
        LOG_CHECK_ERROR(nRetCode);
    }

    if (nParam3 > 0)
    {
        nRetCode = target->RemoveAuraBySubType(nParam3);
        LOG_CHECK_ERROR(nRetCode);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_035(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    return target->GetHp() < nParam1 + nParam2 * target->GetAttr(catMaxHp) / RATE_MAX;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_036(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    return poBullet->GetSpellID() == nParam1 && ((1 << poBullet->GetSpellRuneSlot()) & nParam2) != 0;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_037(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CCharacter* caster = NULL;
    INT32 nSubSpellID = abs(nParam1);
    SpellEventNode* poEventNode = NULL;
    CCharacter* poEventOwner = NULL;
    INT32 nRootSpellLevel = 0;
    CSpell* poSpell = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    nRootSpellLevel = poBullet->GetSpellLevel();

    poEventOwner = poBullet->GetEventOwner();

    if (poEventOwner != NULL)
    {
        poEventNode = poEventOwner->GetPendingEventNode();

        if (poEventNode != NULL)
            nRootSpellLevel = poEventNode->nRootSpellLevel;
    }

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    poSpell = CSpellConfig::GetInstance().FindSpellTemplate(nSubSpellID, nRootSpellLevel, 0);
    LOG_PROCESS_ERROR(poSpell);

    nRetCode = caster->CastInstantSpell(caster, poSpell, caster, caster->GetX(), caster->GetY(), caster->GetZ());
    PROCESS_SUCCESS(nRetCode != errSuccess);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_038(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CCharacter* target = NULL;
    INT32 nSubSpellID = abs(nParam1);
    SpellEventNode* poEventNode = NULL;
    CCharacter* poEventOwner = NULL;
    INT32 nRootSpellLevel = 0;
    CSpell* poSpell = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    nRootSpellLevel = poBullet->GetSpellLevel();

    poEventOwner = poBullet->GetEventOwner();

    if (poEventOwner != NULL)
    {
        poEventNode = poEventOwner->GetPendingEventNode();

        if (poEventNode != NULL)
            nRootSpellLevel = poEventNode->nRootSpellLevel;
    }

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poSpell = CSpellConfig::GetInstance().FindSpellTemplate(nSubSpellID, nRootSpellLevel, 0);
    LOG_PROCESS_ERROR(poSpell);

    nRetCode = target->CastInstantSpell(target, poSpell, target, target->GetX(), target->GetY(), target->GetZ());
    PROCESS_SUCCESS(nRetCode != errSuccess);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_039(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nSubSpellID = abs(nParam1);
    SpellEventNode* poEventNode = NULL;
    CCharacter* poEventOwner = NULL;
    INT32 nRootSpellLevel = 0;
    CSpell* poSpell = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    nRootSpellLevel = poBullet->GetSpellLevel();

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    poEventOwner = poBullet->GetEventOwner();
    if (poEventOwner != NULL)
    {
        poEventNode = poEventOwner->GetPendingEventNode();

        if (poEventNode != NULL)
            nRootSpellLevel = poEventNode->nRootSpellLevel;
    }

    poSpell = CSpellConfig::GetInstance().FindSpellTemplate(nSubSpellID, nRootSpellLevel, 0);
    LOG_PROCESS_ERROR(poSpell);

    nRetCode = target->CastInstantSpell(target, poSpell, caster, caster->GetX(), caster->GetY(), caster->GetZ());
    PROCESS_SUCCESS(nRetCode != errSuccess);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_040(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 nResult = 0;
    INT32 nAtkHi = 0;
    INT32 eSpellAtkType = 0;

    static INT32 s_AtkTableHi[] =
    {
        catDefault,		// none
        catMaxPhyAtk,	// melee
        catMaxMagAtk,	// magic
        catMaxTaoAtk,
    };

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    // 根据IDA反编译的代码 补充进来的, 暂时先屏蔽
    //LOG_PROCESS_ERROR(nParam1 > 0);

    eSpellAtkType = poBullet->GetSpellAttr(satAttackType);
    LOG_PROCESS_ERROR(eSpellAtkType > spatInvalid && eSpellAtkType < spatTotal);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    nAtkHi = caster->GetAttr(s_AtkTableHi[eSpellAtkType]);

    nResult = nAtkHi * (caster->GetAttr(catMaxMp) - caster->GetMp()) * nParam2 / nParam1 + nParam3 * RATE_MAX;

    poBullet->SetX(poBullet->GetX() + nResult);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_041(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    return mrcTrue;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_042(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CAuraInstance* poAura = NULL;
    INT32 nRetCode = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    poAura = caster->GetFirstAura(nParam1);
    PROCESS_SUCCESS(poAura == NULL);

    caster->RemoveAura(poAura, TRUE);

    if (nParam2 > 0)
    {
        nRetCode = caster->RemoveAuraByType(nParam2);
        LOG_CHECK_ERROR(nRetCode);
    }

    if (nParam3 > 0)
    {
        nRetCode = caster->RemoveAuraBySubType(nParam3);
        LOG_CHECK_ERROR(nRetCode);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_043(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    return caster->GetExFlag().CheckFlag(nParam1);
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_044(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CNpc* npc = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    PROCESS_SUCCESS(target->GetObjType() != otNpc);

    npc = static_cast<CNpc*>(target);

    PROCESS_SUCCESS(npc->GetQuality() != nqBoss);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_045(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CNpc* npc = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nParam1 >= sfbRoundTableBegin && nParam1 < sfbRoundTableEnd);

    poBullet->GetEffectFlag().ResetFlag();
    poBullet->GetEffectFlag().SetFlag(nParam1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_046(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    return poBullet->GetSpellAttr(satInitialCostValue) >= 0 || poBullet->GetSpellAttr(satDurativeCostValue) >= 0 || poBullet->GetSpellAttr(satModifierCostValue) >= 0;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_047(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    return caster->GetHp() <= nParam1 * caster->GetAttr(catMaxHp) / RATE_MAX + nParam2;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_048(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CAuraInstance* poAura = NULL;
    INT32 nRetCode = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    if (nParam1 > 0)
    {
        poAura = caster->GetFirstAura(nParam1);
        PROCESS_SUCCESS(poAura == NULL);
    }

    if (nParam2 > 0)
    {
        poAura = caster->GetFirstAuraByType(nParam2);
        PROCESS_SUCCESS(poAura == NULL);
    }

    if (nParam3 > 0)
    {
        poAura = caster->GetFirstAuraBySubType(nParam3);
        PROCESS_SUCCESS(poAura == NULL);
    }

    PROCESS_SUCCESS(poAura == NULL);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_049(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT64 x1 = 0;

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    INT64 llDist2 = 0;
    INT64 llDistCM2 = 0;
    INT64 llDist = 0;
    INT64 llEffectPct = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nParam2 != 0);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    llDist2 = caster->GetDistance3D(target);
    llDistCM2 = llDist2 / POINT_PER_CM / POINT_PER_CM;

    llDist = llDistCM2 / 64 / 64;
    PROCESS_SUCCESS(llDist > MAX_SQUARE);

    llDist = g_Sqrt((UINT16)llDist) * 64;

    if (llDist <= nParam3)
        llDist = nParam3;

    llEffectPct = poBullet->GetSpellAttr(satEffectPct);

    llEffectPct = llEffectPct * (nParam2 * RATE_MAX + (llDist - nParam3) * nParam1) / nParam2 / RATE_MAX;

    poBullet->SetSpellAttr(satEffectPct, llEffectPct);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;

}

INT32 ModifierBullet_050(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    return !target->GetFlag().CheckFlag(cfCannotBeThrown);
Exit0:
    return mrcError;
}

INT32 ModifierBullet_051(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CScene* poScene = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poScene = target->GetScene();
    LOG_PROCESS_ERROR(poScene);

    PROCESS_SUCCESS(poScene->GetWeather() != nParam1 + 1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_052(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam1 == 0)
        PROCESS_SUCCESS(caster->GetLevel() <= target->GetLevel());
    else
        PROCESS_SUCCESS(caster->GetLevel() < target->GetLevel());

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_053(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    INT32 nEffectValue = 0;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nRetCode = target->Dash(poBullet->GetSpellAttr(satSpeed), poBullet->GetTargetX(), poBullet->GetTargetY());
    PROCESS_SUCCESS(!nRetCode);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_054(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    return target->GetMp() > nParam2 + nParam1 * target->GetAttr(catMaxMp) / RATE_MAX;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_055(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CScene* poScene = NULL;

    CCharacter* poChar = static_cast<CCharacter*>(poTarget);
    LOG_PROCESS_ERROR(poChar);

    PROCESS_ERROR(!bIsRollingBack);

    return CGameWorld::GetInstance().IsDaytime();
Exit0:
    return mrcError;
}

INT32 ModifierBullet_056(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* host = NULL;
    INT32 nHpChange = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_ERROR(caster);

    host = CGameWorld::GetInstance().FindValidCharacter(caster->GetHostID());
    PROCESS_ERROR(host);

    nHpChange = poBullet->GetEffectValue() * nParam1 / RATE_MAX + nParam2 + nParam3 * host->GetAttr(catMaxHp) / RATE_MAX;

    host->ChangeHp(nHpChange, cdrSpell);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_057(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nEffectValue = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nEffectValue = (target->GetAttr(catMaxHp) * nParam1 + caster->GetAttr(catMaxHp) * nParam2) / RATE_MAX;

    poBullet->SetEffectValue(nEffectValue);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_058(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CAuraInstance* poAura = NULL;
    INT32 nRetCode = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam1 > 0)
    {
        poAura = target->GetFirstAura(nParam1);
        PROCESS_SUCCESS(poAura == NULL);

        target->ReduceAuraStack(poAura, 1);
    }

    if (nParam2 > 0)
    {
        nRetCode = target->ReduceAuraStackByType(nParam2, 1);
        PROCESS_SUCCESS(!nRetCode);
    }

    if (nParam3 > 0)
    {
        nRetCode = target->ReduceAuraStackBySubType(nParam3, 1);
        PROCESS_SUCCESS(!nRetCode);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_059(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 eSpellAttr = nParam1;
    INT32 nValue = nParam2;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);
    LOG_PROCESS_ERROR(eSpellAttr > satInvalid && eSpellAttr < satTotal);

    poBullet->SetSpellAttr(eSpellAttr, nValue);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_060(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nPctValue = nParam1;
    INT32 nEffectValue = 0;
    CCharacter* target = NULL;
    CCharacter* poDamageShareChar = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poDamageShareChar = CGameWorld::GetInstance().FindValidCharacter(target->GetDamageShareCharID());
    PROCESS_SUCCESS(poDamageShareChar == NULL);
    PROCESS_SUCCESS(poDamageShareChar->IsDead());

    nEffectValue = poBullet->GetEffectValue();

    poDamageShareChar->DirectlyHpChange(-nEffectValue * nParam1 / RATE_MAX);

    poBullet->SetEffectValue(nEffectValue * (RATE_MAX - nParam1) / RATE_MAX);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_061(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    PROCESS_SUCCESS(poBullet->GetSpellAttr(satElementaryType) != nParam1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_062(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    SpellEventNode* pNode = NULL;
    CSpell* poRootSpell = NULL;
    INT32 nCooldownFrm = 0;
    CCharacter* poCaster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poCaster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(poCaster == NULL);

    pNode = poCaster->GetPendingEventNode();
    LOG_PROCESS_ERROR(pNode);

    poRootSpell = poCaster->GetSpellBook().GetMainSpell(pNode->nRootSpellID);
    LOG_PROCESS_ERROR(poRootSpell);

    nCooldownFrm = poRootSpell->GetEventCoolDownFrm();

    return poCaster->AddCooldown(MakeCoolDownID(COOLDOWN_SPELL_EVENT_TRIGGER, poRootSpell->GetID()), nCooldownFrm);
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_063(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    SpellEventNode* pNode = NULL;
    CSpell* poRootSpell = NULL;
    INT32 nCooldownFrm = 0;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    pNode = target->GetPendingEventNode();
    LOG_PROCESS_ERROR(pNode);

    poRootSpell = target->GetSpellBook().GetMainSpell(pNode->nRootSpellID);
    LOG_PROCESS_ERROR(poRootSpell);

    nCooldownFrm = poRootSpell->GetEventCoolDownFrm();

    target->AddCooldown(MakeCoolDownID(COOLDOWN_SPELL_EVENT_TRIGGER, poRootSpell->GetID()), nCooldownFrm);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_064(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    return poBullet->GetSpellFlag().CheckFlag(nParam1);
Exit0:
    return mrcError;
}

INT32 ModifierBullet_065(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CCharacter* target = NULL;
    CAuraInstance* poAura = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);
    LOG_PROCESS_ERROR(nParam3 > 0);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam1 >= 0)
    {
        poAura = target->GetFirstAura(nParam1);
        PROCESS_SUCCESS(poAura == NULL);

        nRetCode = target->DispelAura(poAura, nParam3);
    }
    else if (nParam2 >= 0)
    {
        poAura = target->GetFirstAuraBySubType(nParam2);
        PROCESS_SUCCESS(poAura == NULL);

        nRetCode = target->DispelAura(poAura, nParam3);
    }

    PROCESS_SUCCESS(!nRetCode);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

void __finish_single_aura(CCharacter* poChar, CAuraInstance* poAura)
{
    INT32 nRemainTimes = 0;
    INT32 nEffectPct = 0;
    INT32 nEffectValue = 0;

    LOG_PROCESS_ERROR(poAura);

    nRemainTimes = poAura->GetRemainFrm() / poAura->GetIntervalFrm();
    nEffectPct = poAura->GetEffectPct() * nRemainTimes;
    nEffectValue = poAura->GetEffectValue() * nRemainTimes;

    //	poAura->SetAttr(aatEffectPct, nEffectPct);
    //	poAura->SetAttr(aatEffectValue, nEffectValue);

    poAura->SetEffectPct(nEffectPct);
    poAura->SetEffectValue(nEffectValue);

    //	poAura->OnTimeup(poChar);
    poChar->UpdateSingleAura(poAura, TRUE);

    poChar->RemoveAura(poAura, TRUE);

Exit0:
    return;
}

INT32 ModifierBullet_066(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CAuraInstance* poAura = NULL;
    CCharacter* target = NULL;
    BOOL bHasAura = FALSE;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    //	for(INT32 i = auetNone; i < auetTotal; i++)
    //	{
    //		poAura = target->GetAuraList().GetStaticAura(i);
    //		if(poAura == NULL)
    //			continue;
    //
    //		if(poAura->GetID() == nParam1 || poAura->GetAttr(aatType) == nParam2)
    //			__finish_single_aura(target, poAura);
    //	}

    for (INT32 i = auetNone; i < auetTotal; i++)
    {
        poAura = target->GetAuraList().BeginAura(i);

        while ((poAura = target->GetAuraList().NextAura(i, poAura)) != NULL)
        {
            if (poAura->GetID() == nParam1 || poAura->GetAttr(aatType) == nParam2 || poAura->GetAttr(aatGroup) == nParam3)
            {
                __finish_single_aura(target, poAura);
                bHasAura = TRUE;
            }
        }
    }

    if (bHasAura)
        return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_067(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CCharacter* caster = NULL;
    INT32 nDirection = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    nDirection = g_GetDirection(target->GetX(), target->GetY(), caster->GetX(), caster->GetY());

    DBG("rotate: %s : %d", __FILE__, __LINE__);
    target->RotateToDir8(nDirection, 0);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_068(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poBullet->SetSpellAttr(satEffectPct, 0);
    poBullet->SetSpellAttr(satEffectValue, 0);

    target->ChangeHp(nParam1 + nParam2 * target->GetAttr(catMaxHp) / RATE_MAX, cdrSpell);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_069(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CAuraInstance* poAura = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam1 > 0)
    {
        poAura = target->GetFirstAura(nParam1);
        PROCESS_SUCCESS(poAura == NULL);
    }

    if (nParam2 > 0)
    {
        poAura = target->GetFirstAuraByType(nParam2);
        PROCESS_SUCCESS(poAura == NULL);
    }

    if (nParam3 > 0)
    {
        poAura = target->GetFirstAuraBySubType(nParam3);
        PROCESS_SUCCESS(poAura == NULL);
    }

    PROCESS_SUCCESS(poAura == NULL);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_070(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* poCaster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poCaster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(poCaster);

    poCaster->DirectlyHpChange(nParam2 + nParam1 * poBullet->GetEffectValue() / RATE_MAX);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_071(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT64 llX = 0;
    CCharacter* poCaster = NULL;
    INT32 nResult = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nParam2 > catDefault && nParam2 < catTotal);

    poCaster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(poCaster);

    llX = poBullet->GetX();

    nResult = poCaster->GetAttr(nParam2) * nParam3 / nParam1;

    nResult = nResult > RATE_MAX ? RATE_MAX : nResult;

    llX = llX * (RATE_MAX + nResult) / RATE_MAX;

    poBullet->SetX(llX);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_072(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nX = 0;
    CCharacter* target = NULL;
    CAuraInstance* poAura = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    for (INT32 i = auetNone; i < auetTotal; i++)
    {
        poAura = target->GetAuraList().BeginAura(i);

        while ((poAura = target->GetAuraList().NextAura(i, poAura)) != NULL)
        {
            if (poAura->GetCasterID() == poBullet->GetCasterID())
            {
                if (poAura->GetID() == nParam1 || poAura->GetAttr(aatType) == nParam2 || poAura->GetAttr(aatGroup) == nParam3)
                    return mrcTrue;
            }
        }
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_073(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nMaxHp = 0;
    CCharacter* poCaster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poCaster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(poCaster);

    nMaxHp = poCaster->GetAttr(catMaxHp);

    poCaster->DirectlyHpChange(nParam1 + (nMaxHp * nParam2) / RATE_MAX);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_074(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nMaxHp = 0;
    CCharacter* poCaster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poCaster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(poCaster);

    //	DBG("Hi: %d, Lo: %d, AtkRand: %d, AfterParam1: %lld", poBullet->GetAtkHi(), poBullet->GetAtkLo(), poBullet->GetAttackRandom(), (INT64)nParam1 * poBullet->GetAtkHi() / RATE_MAX);

    PROCESS_SUCCESS(poBullet->GetAttackRandom() < g_Max<INT64>((INT64)nParam1 * poBullet->GetAtkHi() / RATE_MAX, (INT64)poBullet->GetAtkLo()));

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_075(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nSlotID = nParam1;
    CSpellSlot* poSlot = NULL;
    CCharacter* poCaster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nSlotID > qssSlotInvalid && nSlotID < qssSlotCount);

    poCaster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(poCaster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poSlot = poCaster->GetSpellSlot(nSlotID);
    LOG_PROCESS_ERROR(poSlot);

    PROCESS_SUCCESS(poSlot->GetNextTargetID() != target->GetObjID());

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_076(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    CSpellSlot* poSlot = NULL;
    INT32 nSpellSlotID = nParam1;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    LOG_PROCESS_ERROR(nSpellSlotID >= qssSlotBegin && nSpellSlotID < qssSlotCount);

    poSlot = caster->GetSpellSlot(nSpellSlotID);
    LOG_PROCESS_ERROR(poSlot);

    poSlot->SetNextTargetID(target->GetObjID());

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_077(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    INT32 nExtraDamge = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nExtraDamge = target->GetAttr(catExtraDmg);

    target->DirectlyHpChange(-nExtraDamge);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_078(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nLevel = nParam1;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    return poBullet->GetSpellLevel() >= nLevel;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_079(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nSpellLevel = 0;
    INT32 nRandNum = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    nSpellLevel = poBullet->GetSpellLevel();

    nRandNum = g_Random(0, nParam1 - nSpellLevel);

    if (nParam3 == 0 && nRandNum == nParam2)
        return mrcTrue;

    if (nParam3 > 0 && nRandNum > nParam2)
        return mrcTrue;

    if (nParam3 < 0 && nRandNum < nParam2)
        return mrcTrue;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_080(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CAuraInstance* poAura = NULL;
    CCharacter* target = NULL;
    INT32 nDuration = CONVERT_TIME(nParam1);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    PROCESS_ERROR(target);

    PROCESS_SUCCESS(poBullet->GetBulletType() != betDamage || poBullet->GetEffectValue() <= 0);

    poAura = target->GetAuraList().BeginAura(nParam2);

    while ((poAura = target->GetAuraList().NextAura(nParam2, poAura)) != NULL)
    {
        INT32 nRemainFrm = poAura->GetRemainFrm();

        if (nRemainFrm > nDuration)
            poAura->ResetFrm(poAura->GetRemainFrm() - nDuration, 0, TRUE);

        if (nRemainFrm < 3 * GAME_FPS)
            target->RemoveAura(poAura, FALSE);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_081(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (g_Random(0, 4) + caster->GetLevel() - 1 > target->GetLevel())
        return mrcTrue;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_082(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    target->ChangeMp(-poBullet->GetX() / 2);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_083(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam3 == 0)
    {
        if (nParam2 == 0)
        {
            if (target->GetLevel() > nParam1)
                return mrcTrue;
        }
        else
        {
            if (target->GetLevel() < nParam1)
                return mrcTrue;
        }
    }
    else
    {
        if (nParam2 == 0)
        {
            if (target->GetLevel() >= nParam1)
                return mrcTrue;
        }
        else
        {
            if (target->GetLevel() <= nParam1)
                return mrcTrue;
        }
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_084(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam1 * poBullet->GetSpellLevel() + nParam2 + caster->GetLevel() - target->GetLevel() > g_Random(0, nParam3))
        return mrcTrue;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_085(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CRole* caster_role = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    LOG_PROCESS_ERROR(caster->GetObjType() == otRole);

    caster_role = static_cast<CRole*>(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    PROCESS_SUCCESS(target->GetSpecies() == spcUndead);
    PROCESS_SUCCESS(target->GetLevel() >= nParam1);

    if (caster_role->GetPetCount() < poBullet->GetSpellLevel() + nParam2 + nParam3)
        return mrcTrue;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_086(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CAuraInstance* poAura = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    // 判断 诱惑神水
    poAura = caster->GetFirstAura(45780);
    if (poAura)
    {
        return mrcTrue;  // 有诱惑神水Buff, 直接成功
    }
    else
    {
        // 默认代码 - 没有诱惑神水Buff, 正常概率
        if (g_Random(0, nParam1) == nParam2)
            return mrcTrue;
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_087(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CRole* caster_role = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    LOG_PROCESS_ERROR(caster->GetObjType() == otRole);

    caster_role = static_cast<CRole*>(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    for (INT32 i = 0; i < caster_role->GetPetCount(); i++)
    {
        if (target->GetObjID() == caster_role->GetPetNpcID(i))
            return mrcTrue;
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_088(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (caster->GetLevel() - target->GetLevel() + nParam1 + nParam2 * poBullet->GetSpellLevel() > g_Random(0, nParam3))
        return mrcTrue;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_089(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (target->GetHostID() != INVALID_OBJECT_ID)
        return mrcTrue;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_090(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam2 == 0)
    {
        if (caster->GetLevel() - target->GetLevel() >= nParam1)
            return mrcTrue;
    }
    else
    {
        if (caster->GetLevel() - target->GetLevel() <= nParam1)
            return mrcTrue;
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_091(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poBullet->SetEffectValue(target->GetAttr(catMaxHp));

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_092(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    CAuraInstance* poAura = NULL;
    INT32 nRoleDiff = 0;
    INT32 nNpcLevelDiff = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    // 判断 诱惑神水
    poAura = caster->GetFirstAura(45780);
    if (poAura)
    {
        // 有诱惑神水Buff, 提高概率
        nRoleDiff = caster->GetLevel() + nParam1 + nParam2 * poBullet->GetSpellLevel();
        nNpcLevelDiff = target->GetLevel() + nParam3;
        if (nRoleDiff > nNpcLevelDiff)
        {
            return g_Random(0, 3) == 1;  // 33.33% 概率 (0,1,2)
        }
    }
    else
    {
        // 默认代码 - 没有诱惑神水Buff, 正常概率
        if (g_Random(0, caster->GetLevel() + nParam1 + nParam2 * poBullet->GetSpellLevel()) > target->GetLevel() + nParam3)
            return mrcTrue;
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_093(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    CAuraInstance* poAura = NULL;
    INT32 nA = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nA = target->GetAttr(catMaxHp) / nParam1;
    nA = nA <= 2 ? 2 : nA * 2;

    PROCESS_SUCCESS(target->GetHostID());

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    // 判断 诱惑神水
    poAura = caster->GetFirstAura(45780);
    if (poAura)
    {
        return mrcTrue;  // 有诱惑神水Buff, 直接成功
    }
    else
    {
        // 默认代码 - 没有诱惑神水Buff, 正常概率
        if (g_Random(0, nA) == nParam2)
            return mrcTrue;
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_094(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    return poBullet->GetSpellAttr(satIgnoreDefense);
Exit0:
    return mrcError;
}

INT32 ModifierBullet_095(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT64 llCasterGridX = 0, llCasterGridY = 0;
    INT64 llTargetGridX = 0, llTargetGridY = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    llCasterGridX = caster->GetX() / GRID_WIDTH;
    llCasterGridY = caster->GetY() / GRID_WIDTH;
    llTargetGridX = target->GetX() / GRID_WIDTH;
    llTargetGridY = target->GetY() / GRID_WIDTH;

    PROCESS_SUCCESS(g_Max(g_Abs(llCasterGridX - llTargetGridX), g_Abs(llCasterGridY - llTargetGridY)) > nParam1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_096(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CNpc* npc = NULL;
    CAIProcessor* ai = NULL;
    INT32 nA = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    PROCESS_SUCCESS(target->GetObjType() != otNpc);

    npc = static_cast<CNpc*>(target);

    ai = npc->GetAIProcessor();
    LOG_PROCESS_ERROR(ai);

    npc->GetThreatList().Clear();
    ai->SetTargetID(0);

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_097(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    INT32 nStep = 0;

    CCharacter* target = NULL;
    CRole* poMaster = NULL;

    CNpc* poNpc = NULL;
    CNpc* poPet = NULL;
    CScene* poScene = NULL;
    INT32 nTemplateID = 0;
    INT32 nFaceDirection = 0;
    UINT32 dwOriginHostID = 0;
    INT32  nOldPetHp = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);
    LOG_PROCESS_ERROR(nParam2 != 0);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poMaster = CGameWorld::GetInstance().FindValidRole(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(poMaster);

    poScene = poMaster->GetScene();
    LOG_PROCESS_ERROR(poScene);

    PROCESS_SUCCESS(target->GetObjType() != otNpc);

    poNpc = static_cast<CNpc*>(target);

    poNpc->SetGenerateDrop(FALSE);

    nTemplateID = poNpc->GetNpcData()->nTemplateID;
    nFaceDirection = poNpc->GetFaceDirection();
    dwOriginHostID = poNpc->GetHostID();

    nOldPetHp = poNpc->GetHp();
    nRetCode = poNpc->Die(cdrSilent);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = poNpc->RemoveCorpse();
    LOG_PROCESS_ERROR(nRetCode);

    poPet = poScene->SpawnPet(nTemplateID, poNpc->GetX(), poNpc->GetY(), poNpc->GetZ(), nFaceDirection, poBullet->GetCasterID(), NULL, soatNoPerforSpawn);
    LOG_PROCESS_ERROR(poPet);
    nStep = 1;

    nRetCode = poPet->TransformToPet(nParam2, 0, poBullet->GetSpellLevel(), nParam1, CONVERT_TIME(nParam3), 0);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = poMaster->AddPet(poPet->GetObjID(), nParam2);
    LOG_PROCESS_ERROR(nRetCode);
    nStep = 2;

    if (dwOriginHostID != INVALID_OBJECT_ID)
    {
        INT32   nHp = nOldPetHp / 10;
        nHp = (nHp == 0 ? 1 : nHp);
        poPet->SetHp(nHp);
    }
Exit1:
    return mrcFalse;
Exit0:
    if (2 <= nStep)
    {
        nRetCode = poMaster->DelPet(poPet->GetObjID());
        LOG_CHECK_ERROR(nRetCode);
    }
    if (1 <= nStep)
    {
        LOG_CHECK_ERROR(poPet->GetScene());
        if (poPet->GetScene())
        {
            nRetCode = poPet->GetScene()->RemoveNpc(poPet);
            LOG_CHECK_ERROR(nRetCode);

            nRetCode = poPet->UnInit();
            LOG_CHECK_ERROR(nRetCode);

            nRetCode = CGameWorld::GetInstance().DelNpc(poPet);
            LOG_CHECK_ERROR(nRetCode);
        }
    }
    return mrcError;
}

INT32 ModifierBullet_098(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CCharacter* caster = NULL;
    CRole* poRole = NULL;
    INT32 nAbilityPts = 0;


    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    LOG_PROCESS_ERROR(caster->GetObjType() == otRole);

    poRole = static_cast<CRole*>(caster);

    if (nParam2 > 0)
        nAbilityPts = 3;
    else
        nAbilityPts = g_Random(0, 3) + 1;

    nRetCode = poRole->AddSpellPts(nParam1, nAbilityPts);
    PROCESS_SUCCESS(!nRetCode);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_099(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CCharacter* caster = NULL;
    CRole* poRole = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    LOG_PROCESS_ERROR(caster->GetObjType() == otRole);

    poRole = static_cast<CRole*>(caster);

    PROCESS_SUCCESS(poRole->GetPetCount() >= nParam1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_100(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CAura* poAuraInfo = NULL;
    CAuraInstance* poAuraInstance = NULL;

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    INT32 nNewDurationFrm = 0;
    INT32 nB = 0, nC = 0;
    INT32 nTaoAtk = 0;
    INT32 nMaxTaoAtk = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poAuraInfo = CSpellConfig::GetInstance().FindAuraTemplate(nParam1);
    LOG_PROCESS_ERROR(poAuraInfo);

    nTaoAtk = caster->GetAttr(catTaoAtk);
    nMaxTaoAtk = caster->GetAttr(catMaxTaoAtk);

    nB = round_div((6 + 2 * poBullet->GetSpellLevel()) * nParam2, 12) + g_Random(poBullet->GetSpellAttr(satDefaultValue), poBullet->GetSpellAttr(satDefaultValueMax));

    if (nTaoAtk > 0)
    {
        if (nMaxTaoAtk > nTaoAtk)
            nC = g_Random(nTaoAtk, nMaxTaoAtk + 1);
        else
            nC = nTaoAtk;
    }

    nNewDurationFrm = GAME_FPS * (nB + nParam3 * nC);

    poAuraInstance = target->AppendAura(poAuraInfo, caster, poBullet->GetFromObjID(), (ExtraParam*)pExParam, nNewDurationFrm, 0, poBullet->GetSpellID(), poBullet->GetSpellLevel());
    PROCESS_SUCCESS(!poAuraInstance);

    return mrcTrue;

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_101(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nParam1 != 0 && nParam2 != 0);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (target->GetMp() * nParam2 / nParam1 >= poBullet->GetEffectValue())
    {
        target->ChangeMp(-poBullet->GetEffectValue() * nParam1 / nParam2);
        poBullet->SetEffectValue(0);
    }
    else
    {
        poBullet->SetEffectValue(poBullet->GetEffectValue() - target->GetMp() * nParam2 / nParam1);
        target->ChangeMp(-target->GetAttr(catMaxMp));
    }


    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_102(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* obj = NULL;
    CNpc* poNpc = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nParam1 != 0);

    if (nParam2 == 0)
    {
        obj = poBullet->GetTarget();
    }
    else
    {
        obj = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    }

    LOG_PROCESS_ERROR(obj);

    PROCESS_SUCCESS(obj->GetObjType() != otNpc);

    poNpc = static_cast<CNpc*>(obj);

    PROCESS_SUCCESS(poNpc->GetQuality() < nParam1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_103(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 nHpRecovery = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    PROCESS_SUCCESS(caster->GetAttr(catLeech) <= 0);

    nHpRecovery = round_div(poBullet->GetEffectValue() * caster->GetAttr(catLeech), 100) + caster->GetHpLeech();

    caster->SetHpLeech(nHpRecovery);

    if (nHpRecovery > 2)
    {
        caster->ChangeHp(nHpRecovery, cdrLeech);
        caster->SetHpLeech(0);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_104(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 nHpRecovery = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_SUCCESS(poBullet->GetEffectValue() <= nParam1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_105(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (poBullet->GetEffectValue() >= nParam1)
    {
        target->ChangeHp(nParam1, cdrRecovery);
        poBullet->SetEffectValue(poBullet->GetEffectValue() - nParam1);
    }
    else
    {
        target->ChangeHp(poBullet->GetEffectValue() - 1, cdrRecovery);
        poBullet->SetEffectValue(1);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_106(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CAuraInstance* poAura = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    for (INT32 i = auetNone; i < auetTotal; i++)
    {
        poAura = target->GetAuraList().BeginAura(i);

        while ((poAura = target->GetAuraList().NextAura(i, poAura)) != NULL)
        {
            if (poAura->GetCasterID() != poBullet->GetCasterID())
                continue;

            PROCESS_SUCCESS(poAura->GetID() == nParam1);
            PROCESS_SUCCESS(poAura->GetAttr(aatType) == nParam1);
            PROCESS_SUCCESS(poAura->GetAttr(aatGroup) == nParam1);
        }
    }

    return mrcTrue;
Exit1:
    poBullet->SetRemoveFlag(TRUE);
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_107(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    PROCESS_SUCCESS(((1 << poBullet->GetSpellAttr(satAttackType)) & nParam1) == 0);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_108(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CNpc* poNpc = NULL;
    INT32 nSpellEffectGroup = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    if (nParam2 == 0)
    {
        target = poBullet->GetTarget();
    }
    else
    {
        target = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    }

    LOG_PROCESS_ERROR(target);

    PROCESS_SUCCESS(target->GetObjType() != otNpc);

    poNpc = static_cast<CNpc*>(target);

    nSpellEffectGroup = poNpc->GetNpcData()->nSpellEffectGroup;

    PROCESS_SUCCESS((nSpellEffectGroup & nParam1) == 0);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_109(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;


    INT32 nHitCount = 0;
    INT32 nTotalDamage = 0;
    INT32 nAvgDamage = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    LOG_PROCESS_ERROR(caster->GetDamageStatCount() > 0);

    nAvgDamage = caster->GetTotalDamage() / caster->GetDamageStatCount();

    target->Say(caster->GetObjID(), cltNormal, nParam1, nAvgDamage);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_110(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nDirection8 = 0;

    INT32 nTgGridX = 0, nTgGridY = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nDirection8 = ConvertToDir8(caster->GetFaceDirection());

    nTgGridX = caster->GetX() / GRID_WIDTH + g_nAdjacentX[nDirection8] * nParam1;
    nTgGridY = caster->GetY() / GRID_WIDTH + g_nAdjacentY[nDirection8] * nParam1;

    PROCESS_SUCCESS(target->GetX() / GRID_WIDTH != nTgGridX || target->GetY() / GRID_WIDTH != nTgGridY);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_111(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nValue = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam3 > 0)
        nValue = nParam1 / g_Max(1, caster->GetLevel() - target->GetLevel());
    else
        nValue = nParam1;

    PROCESS_ERROR(nValue >= 0);

    if (nValue > 0)
    {
        caster->ChangeTotalDrugCureHp(nValue);
        return mrcTrue;
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_112(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nValue = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    if (nParam3 == 0)
    {
        if (nParam2 == 0)
            PROCESS_SUCCESS(caster->GetLevel() <= nParam1);
        else
            PROCESS_SUCCESS(caster->GetLevel() >= nParam1);
    }
    else
    {
        if (nParam2 == 0)
            PROCESS_SUCCESS(caster->GetLevel() < nParam1);
        else
            PROCESS_SUCCESS(caster->GetLevel() > nParam1);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_113(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nValue = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nParam1 != 0);

    LOG_PROCESS_ERROR(nParam2 > catDefault && nParam2 < catTotal);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    nValue = poBullet->GetX() + caster->GetAttr(nParam2) / nParam1 * nParam3 / RATE_MAX;

    poBullet->SetX(nValue);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_114(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poBullet->SetX(nParam1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_115(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    INT32 nStep = 0;

    CCharacter* target = NULL;
    CRole* poMaster = NULL;

    CNpc* poNpc = NULL;
    CNpc* poPet = NULL;
    CScene* poScene = NULL;
    INT32 nTemplateID = 0;
    INT32 nFaceDirection = 0;
    UINT32 dwOriginHostID = 0;
    INT32  nOldPetHp = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);
    LOG_PROCESS_ERROR(nParam2 != 0);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poMaster = CGameWorld::GetInstance().FindValidRole(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(poMaster);

    poScene = poMaster->GetScene();
    LOG_PROCESS_ERROR(poScene);

    PROCESS_SUCCESS(target->GetObjType() != otNpc);

    poNpc = static_cast<CNpc*>(target);

    poNpc->SetGenerateDrop(FALSE);

    nTemplateID = poNpc->GetNpcData()->nTemplateID;
    nFaceDirection = poNpc->GetFaceDirection();
    dwOriginHostID = poNpc->GetHostID();

    nOldPetHp = poNpc->GetHp();
    nRetCode = poNpc->Die(cdrSilent);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = poNpc->RemoveCorpse();
    LOG_PROCESS_ERROR(nRetCode);

    poPet = poScene->SpawnPet(nTemplateID, poNpc->GetX(), poNpc->GetY(), poNpc->GetZ(), nFaceDirection, poBullet->GetCasterID(), NULL, soatNoPerforSpawn);
    LOG_PROCESS_ERROR(poPet);
    nStep = 1;

    nRetCode = poPet->TransformToPet(nParam2, poBullet->GetSpellLevel(), poBullet->GetSpellLevel(), nParam1, CONVERT_TIME(nParam3), 0);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = poMaster->AddPet(poPet->GetObjID(), nParam2);
    LOG_PROCESS_ERROR(nRetCode);
    nStep = 2;

    if (dwOriginHostID != INVALID_OBJECT_ID)
    {
        INT32   nHp = nOldPetHp / 10;
        nHp = (nHp == 0 ? 1 : nHp);
        poPet->SetHp(nHp);
    }
Exit1:
    return mrcFalse;
Exit0:
    if (2 <= nStep)
    {
        nRetCode = poMaster->DelPet(poPet->GetObjID());
        LOG_CHECK_ERROR(nRetCode);
    }
    if (1 <= nStep)
    {
        LOG_CHECK_ERROR(poPet->GetScene());
        if (poPet->GetScene())
        {
            nRetCode = poPet->GetScene()->RemoveNpc(poPet);
            LOG_CHECK_ERROR(nRetCode);

            nRetCode = poPet->UnInit();
            LOG_CHECK_ERROR(nRetCode);

            nRetCode = CGameWorld::GetInstance().DelNpc(poPet);
            LOG_CHECK_ERROR(nRetCode);
        }
    }
    return mrcError;
}

INT32 ModifierBullet_116(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nEffectValue = 0;
    CCharacter* caster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    if ((nParam1 & (1 << caster->GetObjType())) != 0 && (nParam2 & (1 << caster->GetSpecies())) != 0)
        return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_117(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRate = 0;
    CCharacter* target = NULL;
    CNpc* poNpc = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    PROCESS_SUCCESS(target->GetObjType() != otNpc);

    poNpc = static_cast<CNpc*>(target);

    if (nParam3 <= 0)
    {
        nRate = nParam1 * poNpc->GetPetLevel() + nParam2;
        PROCESS_SUCCESS(g_Random(0, RATE_MAX) > nRate);
    }
    else
    {
        nRate = nParam1 * poNpc->GetPetLevel() + (nParam3 - 1) * poNpc->GetPetLevel() + nParam2;
        PROCESS_SUCCESS(g_Random(0, RATE_MAX) > nRate);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_118(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    PROCESS_SUCCESS(target == NULL);

    PROCESS_SUCCESS(poBullet->GetCasterID() != target->GetObjID());

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_119(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CRole* poRole = NULL;
    CItemBag* poBag = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    PROCESS_SUCCESS(target == NULL);

    PROCESS_SUCCESS(target->GetObjType() != otRole);

    poRole = static_cast<CRole*>(target);

    poBag = poRole->GetItemBag();
    LOG_PROCESS_ERROR(poBag);

    nRetCode = poBag->LoseItemDur(CONSLOT_EQUIPPED, nParam1, nParam2, ITEMLOG_SPELL);
    PROCESS_SUCCESS(!nRetCode);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_120(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    INT32 nValue = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    PROCESS_SUCCESS(!caster->CanAttack(target));

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_121(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CRole* poRole = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poRole = CGameWorld::GetInstance().FindValidRole(poBullet->GetCasterID());
    PROCESS_SUCCESS(poRole == NULL);

    PROCESS_SUCCESS(poRole->GetPkMode() != rpmSlayer);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_122(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    INT32 nStep = 0;

    CCharacter* target = NULL;
    CRole* poMaster = NULL;

    CNpc* poNpc = NULL;
    CNpc* poPet = NULL;
    CScene* poScene = NULL;
    INT32 nTemplateID = 0;
    INT32 nFaceDirection = 0;
    UINT32 dwOriginHostID = 0;
    INT32  nOldPetHp = 0;
    INT32 nOldPetLevel = 0;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);
    LOG_PROCESS_ERROR(nParam2 != 0);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poMaster = CGameWorld::GetInstance().FindValidRole(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(poMaster);

    poScene = poMaster->GetScene();
    LOG_PROCESS_ERROR(poScene);

    PROCESS_SUCCESS(target->GetObjType() != otNpc);

    poNpc = static_cast<CNpc*>(target);

    poNpc->SetGenerateDrop(FALSE);

    nOldPetLevel = poNpc->GetPetLevel();

    nTemplateID = poNpc->GetNpcData()->nTemplateID;
    nFaceDirection = poNpc->GetFaceDirection();
    dwOriginHostID = poNpc->GetHostID();

    nOldPetHp = poNpc->GetHp();
    nRetCode = poNpc->Die(cdrSilent);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = poNpc->RemoveCorpse();
    LOG_PROCESS_ERROR(nRetCode);

    poPet = poScene->SpawnPet(nTemplateID, poNpc->GetX(), poNpc->GetY(), poNpc->GetZ(), nFaceDirection, poBullet->GetCasterID(), NULL, soatNoPerforSpawn);
    LOG_PROCESS_ERROR(poPet);
    nStep = 1;

    nRetCode = poPet->TransformToPet(nParam2, nOldPetLevel, poBullet->GetSpellLevel(), nParam1, CONVERT_TIME(nParam3), 0);
    LOG_PROCESS_ERROR(nRetCode);

    nRetCode = poMaster->AddPet(poPet->GetObjID(), nParam2);
    LOG_PROCESS_ERROR(nRetCode);
    nStep = 2;

    if (dwOriginHostID != INVALID_OBJECT_ID)
    {
        INT32   nHp = nOldPetHp / 10;
        nHp = (nHp == 0 ? 1 : nHp);
        poPet->SetHp(nHp);
    }
Exit1:
    return mrcFalse;
Exit0:
    if (2 <= nStep)
    {
        nRetCode = poMaster->DelPet(poPet->GetObjID());
        LOG_CHECK_ERROR(nRetCode);
    }
    if (1 <= nStep)
    {
        LOG_CHECK_ERROR(poPet->GetScene());
        if (poPet->GetScene())
        {
            nRetCode = poPet->GetScene()->RemoveNpc(poPet);
            LOG_CHECK_ERROR(nRetCode);

            nRetCode = poPet->UnInit();
            LOG_CHECK_ERROR(nRetCode);

            nRetCode = CGameWorld::GetInstance().DelNpc(poPet);
            LOG_CHECK_ERROR(nRetCode);
        }
    }
    return mrcError;
}

INT32 ModifierBullet_123(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nX = 0;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    nX = poBullet->GetX();

    nX = nX * g_Max(nParam1 - target->GetLevel(), 1) * nParam2 / RATE_MAX + g_Max(nParam1 - target->GetLevel(), 1) * nParam3;

    poBullet->SetX(nX);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_124(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;

    CRole* poRole = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poRole = CGameWorld::GetInstance().FindValidRole(poBullet->GetCasterID());
    PROCESS_SUCCESS(poRole == NULL);

    nRetCode = poRole->CheckPet(nParam1);
    PROCESS_SUCCESS(!nRetCode);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_125(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;

    CCharacter* poCaster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poCaster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(poCaster == NULL);

    //	poCaster->ChangeMp(g_Max(poBullet->GetEffectValue() + nParam1, nParam3) * nParam2 / RATE_MAX);
    poCaster->ChangeMp(g_Min<INT32>(g_Max<INT32>(poBullet->GetEffectValue() + nParam1, 1) * nParam2 / RATE_MAX, nParam3));

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_126(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;

    CCharacter* caster = NULL;
    CCharacter* target = NULL;
    CAura* poAuraInfo = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    poAuraInfo = CSpellConfig::GetInstance().FindAuraTemplate(nParam1);
    LOG_PROCESS_ERROR(poAuraInfo);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    LOG_PROCESS_ERROR(nParam2 != 0);

    {
        INT32 A = (6 + 2 * poBullet->GetSpellLevel()) * 10;
        INT32 B = round_div(A, 3) + g_Random(poBullet->GetSpellAttr(satDefaultValue), poBullet->GetSpellAttr(satDefaultValueMax));
        INT32 C = caster->GetAttr(catMaxTaoAtk) > caster->GetAttr(catTaoAtk) ? g_Random(caster->GetAttr(catTaoAtk), caster->GetAttr(catMaxTaoAtk) + 1) : caster->GetAttr(catTaoAtk);

        INT32 D = (B + 2 * C) * GAME_FPS;

        INT32 Value1 = nParam2 + g_Max(caster->GetAttr(catMaxTaoAtk) + nParam3, 0) / nParam2;
        INT32 Value2 = nParam2 + g_Max(caster->GetAttr(catMaxTaoAtk) / 2 + nParam3, 0) / nParam2;

        INT32 nAuraLifeFrm = Value2 * D / Value1;

        CAuraInstance* poAuraInst = target->AppendAura(poAuraInfo, caster, caster->GetObjID(), (ExtraParam*)pExParam, nAuraLifeFrm, 0, poBullet->GetSpellID(), poBullet->GetSpellLevel());
        PROCESS_ERROR(poAuraInst == NULL);
    }

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_127(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT64 x1 = 0;
    CCharacter* caster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nParam1 != 0);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    x1 = g_Min<INT32>(g_Max(caster->GetAttr(catMaxPhyAtk) - caster->GetAttr(catPhyAtk), 0) / nParam1 + nParam2 + poBullet->GetX(), g_Max(caster->GetAttr(catMaxPhyAtk) + nParam3, 0));

    poBullet->SetX(x1);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

INT32 ModifierBullet_128(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT64 x1 = 0;
    CCharacter* caster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    PROCESS_SUCCESS(poBullet->GetBulletType() != betDamage);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

// 自己新增加的函数, 有的函数内容不知道该咋写, 暂时先留空
INT32 ModifierBullet_129(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;
    CCharacter* host = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    // 这里是获取主人对象
    host = CGameWorld::GetInstance().FindValidCharacter(target->GetHostID());
    PROCESS_ERROR(host);

    // 判断 [主人状态] 是否为[挖矿]
    if (host->GetMoveState() == CMS_MINE)
    {
        return mrcTrue;
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}
INT32 ModifierBullet_130(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (target->GetMoveState() == CMS_MINE)
    {
        return mrcTrue;
    }

Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}
INT32 ModifierBullet_131(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    INT32 nRetCode = 0;
    CCharacter* target = NULL;
    CCharacter* host = NULL;
    CItemBag* poBag = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    host = CGameWorld::GetInstance().FindValidCharacter(target->GetHostID());
    PROCESS_ERROR(host);

    poBag = ((CRole*)host)->GetItemBag();
    LOG_PROCESS_ERROR(poBag);

    nRetCode = poBag->LoseItemDur(CONSLOT_EQUIPPED, nParam1, nParam2, ITEMLOG_SPELL);
    PROCESS_SUCCESS(!nRetCode);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}
INT32 ModifierBullet_132(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    INT32 nAtkHi = 0;
    INT32 eSpellAtkType = 0;
    INT64 v8 = 0;
    INT32 v13 = 0;
    INT32 v14 = 0;
    INT32 v17 = 0;
    INT64 v18 = 0;

    static INT32 s_AtkTableHi[] =
    {
        catDefault,      // 1  none
        catMaxPhyAtk,    // 7  melee
        catMaxMagAtk,    // 9  magic
        catMaxTaoAtk,    // 11 magic
    };

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    eSpellAtkType = poBullet->GetSpellAttr(satAttackType);
    LOG_PROCESS_ERROR(eSpellAtkType > spatInvalid && eSpellAtkType < spatTotal);

    PROCESS_ERROR(!bIsRollingBack);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    PROCESS_SUCCESS(caster == NULL);

    nAtkHi = caster->GetAttr(s_AtkTableHi[eSpellAtkType]);

    v14 = poBullet->GetSpellAttr(satEffectValue);
    v17 = (int)((poBullet->GetSpellLevel() + 1) * v14) / 4 + nAtkHi;

    v18 = nParam3 * (INT64)(poBullet->GetSpellAttr(satDefaultValue) + v17) / RATE_MAX;

    v8 = (nParam1 + RATE_MAX) * poBullet->GetX();

    v13 = g_Max<INT64>(nParam2 + (v8 / RATE_MAX), v18);

    poBullet->SetX(v13);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}
INT32 ModifierBullet_133(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* poChar = NULL;
    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    LOG_PROCESS_ERROR(nParam1 > catDefault && nParam1 < catTotal);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    if (nParam3 > 0)
        poChar = caster;
    else
        poChar = target;

    //return poChar->GetAttr(nParam1) <= nParam2;

    PROCESS_SUCCESS(poChar->GetAttr(nParam1) > nParam2);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}
INT32 ModifierBullet_134(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nParam1 > catDefault && nParam1 < catTotal);
    LOG_PROCESS_ERROR(nParam2 > catDefault && nParam2 < catTotal);
    LOG_PROCESS_ERROR(nParam3 >= 0);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam3 > 0)
    {
        if (caster->GetAttr(nParam1) >= target->GetAttr(nParam2))
            return mrcTrue;
    }
    else
    {
        if (caster->GetAttr(nParam1) > target->GetAttr(nParam2))
            return mrcTrue;
    }

    //return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}
INT32 ModifierBullet_135(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    LOG_PROCESS_ERROR(nParam1 > 0);

    caster = CGameWorld::GetInstance().FindValidCharacter(poBullet->GetCasterID());
    LOG_PROCESS_ERROR(caster);

    INT32 v18 = caster->GetAttr(catMaxMagAtk);
    INT32 v16 = poBullet->GetSpellAttr(satEffectValueMax);
    INT32 v19 = (int)((poBullet->GetSpellLevel() + 1) * v16) / 4 + v18;

    INT32 v9 = poBullet->GetSpellAttr(satDefaultValueMax);
    INT32 v14 = g_Max((v19 + nParam3 + v9), 0);

    INT32 v17 = caster->GetAttr(catMaxMagAtk);
    INT32 v10 = caster->GetAttr(catMagAtk);
    INT64 v22 = nParam2 + g_Max<INT64>((v17 - v10), 0) / nParam1;

    INT64 v15 = poBullet->GetX() + v22;
    INT64 v21 = g_Min<INT64>(v15, (INT64)v14);

    poBullet->SetX(v21);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}
INT32 ModifierBullet_136(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    if (nParam1 & (1 << target->GetClass())) 
    {
        return mrcTrue;
    }
    else 
    {
        return mrcFalse;
    }

Exit0:
    return mrcError;
}
INT32 ModifierBullet_137(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CAura* poAuraTemplate = NULL;
    CAuraInstance* poAuraInstance = NULL;
    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    poAuraTemplate = CSpellConfig::GetInstance().FindAuraTemplate(nParam1);
    LOG_PROCESS_ERROR(poAuraTemplate);

    target->SetLastCasterID(0);

    INT32 nRootSpellID = poBullet->GetSpellID();
    INT32 nRootSpellLevel = poBullet->GetSpellLevel();

    poAuraInstance = target->AppendAura(poAuraTemplate, target, target->GetObjID(), (ExtraParam*)pExParam, CONVERT_TIME(nParam3), 0, nRootSpellID, nRootSpellLevel);
    PROCESS_SUCCESS(poAuraInstance == NULL);

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

// 未知函数 - 赤月恶魔会触发这个
INT32 ModifierBullet_138(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
    //WRN("Execute Function - %s", __FUNCTION__);

    CCharacter* caster = NULL;
    CCharacter* target = NULL;

    CBullet* poBullet = static_cast<CBullet*>(poTarget);
    LOG_PROCESS_ERROR(poBullet);

    PROCESS_ERROR(!bIsRollingBack);

    target = poBullet->GetTarget();
    LOG_PROCESS_ERROR(target);

    // 疾光电影-无铭文, 要走这个函数
    //target->未知函数(nParam1);    // 在IDA中 没找到这个函数, 可能是他新加的函数, 暂时先屏蔽

    return mrcTrue;
Exit1:
    return mrcFalse;
Exit0:
    return mrcError;
}

ModifierFunc g_BulletModifier[bmiCount] =
{
    { NULL, FALSE },
    { ModifierBullet_001, FALSE },  // Attack,								   基础攻击计算（物理/魔法伤害计算）
    { ModifierBullet_002, FALSE },  // Roll,								   随机骰子判定（暴击、闪避、命中率等）
    { ModifierBullet_003, FALSE },  // TargetKnockBack,						   击退目标（强制位移）
    { ModifierBullet_004, FALSE },  // AppendAuraToTarget,					   给目标附加状态（Buff/Debuff）
    { ModifierBullet_005, FALSE },  // ModifyAttackByRage,					   根据怒气值调整攻击（战士类技能）
    { ModifierBullet_006, FALSE },  // AppendAuraToCaster,					   给施法者附加状态（增益效果）
    { ModifierBullet_007, FALSE },  // CheckAttackType,						   检查攻击类型（物理/魔法/真实伤害等）
    { ModifierBullet_008, FALSE },  // ModifyEffect,						   修改技能效果（动态调整数值）
    { ModifierBullet_009, FALSE },  // CheckTargetDying,					   检查目标是否濒死（HP低于阈值？）
    { ModifierBullet_010, FALSE },  // SetTargetHp,							   直接设置目标HP（秒杀/治疗到固定值）
    { ModifierBullet_011, FALSE },  // ModifyEffectAccordingToMaxHp,		   修改技能效果根据最大HP
    { ModifierBullet_012, FALSE },  // CastSubSpellFromCasterToTarget,		   施放子技能（从施法者→目标）
    { ModifierBullet_013, FALSE },  // IsRollResultLessThanTargetAttribute,    判定结果是否小于目标属性
    { ModifierBullet_014, FALSE },  // RecordCasterToTargetSpellSlot,		   记录施法者到目标技能卡槽
    { ModifierBullet_015, FALSE },  // CheckRoundTableResult,				   检查回合制结果（如先攻/闪避/格挡）
    { ModifierBullet_016, FALSE },  // SetTargetFlagBit,					   设置目标标记位（如“沉默”“眩晕”）
    { ModifierBullet_017, FALSE },  // SetCasterFlagBit,					   设置施法者标记位（如“无敌”“隐身”）
    { ModifierBullet_018, FALSE },  // CheckMpByPercent,					   按百分比检查MP（蓝量是否足够）
    { ModifierBullet_019, FALSE },  // CheckMpByValue,						   按固定值检查MP（是否≥X MP）
    { ModifierBullet_020, FALSE },  // ModifierCost,						   修改花费? 不确定
    { ModifierBullet_021, FALSE },  // Leech,								   吸血/吸蓝效果（生命偷取）
    { ModifierBullet_022, FALSE },  // CheckTargetType,						   检查目标类型（玩家/NPC/BOSS/友军等）
    { ModifierBullet_023, FALSE },  // IsTargetFaceToCaster,				   检查目标是否面向施法者（背刺/格挡机制）
    { ModifierBullet_024, FALSE },  // CheckRemainCooldown,					   检查剩余冷却时间（CD是否转好）
    { ModifierBullet_025, FALSE },  // ReduceCooldown,						   减少冷却时间（刷新/加速CD）
    { ModifierBullet_026, FALSE },  // CheckCasterWeaponType,				   检查施法者武器类型（剑/法杖/弓等）
    { ModifierBullet_027, FALSE },  // ModifyEffectByRemainMp,				   根据剩余MP调整效果（蓝量越高伤害越高）
    { ModifierBullet_028, FALSE },  // DamageReflect,						   伤害反弹（反伤机制）
    { ModifierBullet_029, FALSE },  // CheckTargetDistance,					   检查目标距离（是否在技能范围内）
    { ModifierBullet_030, FALSE },  // CheckTargetExFlag,					   检查目标额外标记（自定义状态）
    { ModifierBullet_031, FALSE },  // ModifyX1ByTargetHp,					   修改X1根据目标HP
    { ModifierBullet_032, FALSE },  // CheckHealBullet,						   检查治愈子弹 不确定
    { ModifierBullet_033, FALSE },  // ChangeTargetMp,						   改变目标MP（吸蓝/回蓝）
    { ModifierBullet_034, FALSE },  // RemoveTargetAura,					   移除目标状态（驱散Debuff）
    { ModifierBullet_035, FALSE },  // CheckTargetHp,						   检查目标HP（是否满足条件，如>50%）
    { ModifierBullet_036, FALSE },  // CheckSpellAndRune,					   检查技能与符文（符文强化效果）
    { ModifierBullet_037, FALSE },  // CastSubSpellFromCasterToCaster,		   施放子技能（自身→自身）
    { ModifierBullet_038, FALSE },  // CastSubSpellFromTargetToTarget,		   施放子技能（从施法者→目标）
    { ModifierBullet_039, FALSE },  // CastSubSpellFromTargetToCaster,		   施放子技能（目标→目标）
    { ModifierBullet_040, FALSE },  // ModifyEffectByUsedMp,				   根据已消耗MP调整效果（类似“法力燃烧”机制）
    { ModifierBullet_041, FALSE },  // CommonStiff,							   普通刚性? 不确定
    { ModifierBullet_042, FALSE },  // RemoveCasterAura,					   移除施法者状态（清除Buff）
    { ModifierBullet_043, FALSE },  // CheckCasterExFlag,					   检查施法者额外标记
    { ModifierBullet_044, FALSE },  // CheckTargetIsBoss,					   检查目标是否为BOSS（特殊机制）
    { ModifierBullet_045, FALSE },  // ForceChangeRoundTableResult,			   强制修改回合结果（必定命中/闪避）
    { ModifierBullet_046, FALSE },  // CheckSpellCost,						   检查技能消耗（MP/HP/物品等）
    { ModifierBullet_047, FALSE },  // CheckCasterHp,						   检查施法者HP（是否满足施法条件）
    { ModifierBullet_048, FALSE },  // CheckCasterAura,						   检查施法者是否有某状态
    { ModifierBullet_049, FALSE },  // ModifyEffectPctByDistance,			   根据距离调整效果百分比（远程衰减/近战增强）
    { ModifierBullet_050, FALSE },  // CheckTargetCanbeThrown,				   检查目标是否可被投掷（击飞/抓取判定）
    { ModifierBullet_051, FALSE },  // CheckWeather,						   检查天气（某些技能受天气影响）
    { ModifierBullet_052, FALSE },  // CheckLevel,							   检查等级（是否达到技能要求）
    { ModifierBullet_053, FALSE },  // MoveTargetToSpellTargetPos,			   将目标移动到技能目标位置（传送/拉拽）
    { ModifierBullet_054, FALSE },  // CheckTargetMp,						   检查目标MP
    { ModifierBullet_055, FALSE },  // CheckIsDaytime,						   检查是否为白天（昼夜机制）
    { ModifierBullet_056, FALSE },  // ConvertToCasterHp,					   将伤害/治疗转换为施法者HP（吸血/转换）
    { ModifierBullet_057, FALSE },  // ModifyEffectByHpMax,					   根据最大HP调整效果（百分比伤害/治疗）
    { ModifierBullet_058, FALSE },  // ReduceTargetAura,					   减少目标状态层数/时间（如Dot）
    { ModifierBullet_059, FALSE },  // ModifySpellAtrr,						   修改技能属性
    { ModifierBullet_060, FALSE },  // DamageShare,							   伤害分摊（团队分担伤害）
    { ModifierBullet_061, FALSE },  // CheckElementaryType,					   检查元素类型（火/冰/雷等相克）
    { ModifierBullet_062, FALSE },  // TriggerEventRootSpellCD: Caster,		   施法者: 触发事件根部技能CD
    { ModifierBullet_063, FALSE },  // TriggerEventRootSpellCD: Target,		   目标: 触发事件根部技能CD
    { ModifierBullet_064, FALSE },  // CheckSpellFlag,						   检查技能标记（如“是否可打断”）
    { ModifierBullet_065, FALSE },  // ReduceTargetAuraStack,				   减少目标状态叠加层数
    { ModifierBullet_066, FALSE },  // FinishAuraImmidiately,				   立即结束光环
    { ModifierBullet_067, FALSE },  // TargetTurnToCaster,                     目标转施法者
    { ModifierBullet_068, FALSE },  // AddTargetHp,                            增肌目标HP
    { ModifierBullet_069, FALSE },  // CheckTargetAura,                        检查目标光环
    { ModifierBullet_070, FALSE },
    { ModifierBullet_071, FALSE },
    { ModifierBullet_072, FALSE },
    { ModifierBullet_073, FALSE },
    { ModifierBullet_074, FALSE },
    { ModifierBullet_075, FALSE },
    { ModifierBullet_076, FALSE },
    { ModifierBullet_077, FALSE },
    { ModifierBullet_078, FALSE },
    { ModifierBullet_079, FALSE },
    { ModifierBullet_080, FALSE },
    { ModifierBullet_081, FALSE },
    { ModifierBullet_082, FALSE },
    { ModifierBullet_083, FALSE },
    { ModifierBullet_084, FALSE },
    { ModifierBullet_085, FALSE },
    { ModifierBullet_086, FALSE },
    { ModifierBullet_087, FALSE },
    { ModifierBullet_088, FALSE },
    { ModifierBullet_089, FALSE },
    { ModifierBullet_090, FALSE },
    { ModifierBullet_091, FALSE },
    { ModifierBullet_092, FALSE },
    { ModifierBullet_093, FALSE },
    { ModifierBullet_094, FALSE },
    { ModifierBullet_095, FALSE },
    { ModifierBullet_096, FALSE },
    { ModifierBullet_097, FALSE },
    { ModifierBullet_098, FALSE },
    { ModifierBullet_099, FALSE },
    { ModifierBullet_100, FALSE },
    { ModifierBullet_101, FALSE },
    { ModifierBullet_102, FALSE },
    { ModifierBullet_103, FALSE },
    { ModifierBullet_104, FALSE },
    { ModifierBullet_105, FALSE },
    { ModifierBullet_106, FALSE },
    { ModifierBullet_107, FALSE },
    { ModifierBullet_108, FALSE },
    { ModifierBullet_109, FALSE },
    { ModifierBullet_110, FALSE },
    { ModifierBullet_111, FALSE },
    { ModifierBullet_112, FALSE },
    { ModifierBullet_113, FALSE },
    { ModifierBullet_114, FALSE },
    { ModifierBullet_115, FALSE },
    { ModifierBullet_116, FALSE },
    { ModifierBullet_117, FALSE },
    { ModifierBullet_118, FALSE },
    { ModifierBullet_119, FALSE },
    { ModifierBullet_120, FALSE },
    { ModifierBullet_121, FALSE },
    { ModifierBullet_122, FALSE },
    { ModifierBullet_123, FALSE },
    { ModifierBullet_124, FALSE },
    { ModifierBullet_125, FALSE },
    { ModifierBullet_126, FALSE },
    { ModifierBullet_127, FALSE },
    { ModifierBullet_128, FALSE },

    // 自己新增加的
    { ModifierBullet_129, FALSE },
    { ModifierBullet_130, FALSE },
    { ModifierBullet_131, FALSE },
    { ModifierBullet_132, FALSE },
    { ModifierBullet_133, FALSE },
    { ModifierBullet_134, FALSE },
    { ModifierBullet_135, FALSE },
    { ModifierBullet_136, FALSE },
    { ModifierBullet_137, FALSE },
    { ModifierBullet_138, FALSE },

};

