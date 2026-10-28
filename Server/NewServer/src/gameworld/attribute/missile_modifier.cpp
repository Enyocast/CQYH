#include "stdafx.h"
#include "attr_modifier.h"
#include "missile_modifier.h"
#include "missile.h"
#include "missile_data.h"
#include "spell_bullet.h"
#include "game_world.h"
#include "level_data.h"
#include "spell_config.h"

INT32 ModifierMissile_001(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	CCharacter* target = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	target = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetLockedTargetID());

	nRetCode = poMissile->TrigSubSpell(nParam1, target, poMissile->GetX(), poMissile->GetY(), poMissile->GetZ());
	PROCESS_SUCCESS(!nRetCode);

	return mrcTrue;
Exit1:
	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_002(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	CCharacter* poOwner = NULL;
	INT32 nRetCode = 0;
	UINT32 dwTargetID = 0;
	INT64 llCollisionTargetX, llCollisionTargetY, llCollisionTargetZ = 0;
	CRegion* poRegion = NULL;
	CSceneObject* poLastFromObj = NULL;	
	INT32 nCount = 0;

	//LOG_PROCESS_ERROR(m_poRegion);

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	PROCESS_ERROR(poOwner);


	poRegion = poMissile->GetRegion();
	LOG_PROCESS_ERROR(poRegion);

	llCollisionTargetX = poMissile->GetX();
	llCollisionTargetY = poMissile->GetY();
	llCollisionTargetZ = poMissile->GetZ();

	poMissile->GetScanner().ClearTarget();

	poMissile->GetScanner().SetCenterPt(poMissile->GetX(), poMissile->GetY(), poMissile->GetZ());
	poMissile->GetScanner().SetTargetPt(llCollisionTargetX, llCollisionTargetY, llCollisionTargetZ);
	poMissile->GetScanner().SetDirection(poMissile->GetFaceDirection());

	nRetCode = poMissile->GetScanner().Scan(poRegion, poOwner);
	PROCESS_ERROR(nRetCode);

	nCount = poMissile->GetScanner().DoBullet(poMissile, poOwner, betDamage);
	LOG_PROCESS_ERROR(nCount >= 0);

	if(nCount > 0)
		return mrcTrue;

	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_003(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	CRegion* poRegion = NULL;
	INT32 nRetCode = 0;
	CCharacter* poOwner = NULL;
	TARGET_NODE* pTargetNode = NULL;
	BOOL bHasTarget = FALSE;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poRegion = poMissile->GetRegion();
	LOG_PROCESS_ERROR(poRegion);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	PROCESS_ERROR(poOwner);

	poMissile->GetScanner().ClearTarget();

	poMissile->GetScanner().SetCenterPt(poMissile->GetX(), poMissile->GetY(), poMissile->GetZ());
	poMissile->GetScanner().SetTargetPt(poMissile->GetX(), poMissile->GetY(), poMissile->GetZ());
	poMissile->GetScanner().SetDirection(poMissile->GetFaceDirection());

	nRetCode = poMissile->GetScanner().Scan(poRegion, poOwner);
	PROCESS_ERROR(nRetCode);

	poMissile->GetScanner().BeginTarget();

	while((pTargetNode = poMissile->GetScanner().NextTarget()) != NULL)
	{
		CCharacter* poCurrentTarget = CGameWorld::GetInstance().FindValidCharacter(pTargetNode->dwTargetID);

		if(poCurrentTarget != NULL)
		{
			if(!poMissile->AddAffectedTarget(pTargetNode->dwTargetID))
				continue;

			if(poMissile->GetCollisionCount() < poMissile->GetAttr(matMaxCollisionCount))
			{
				poMissile->AddCollisionCount();
				bHasTarget = TRUE;
			}
		}
	}

	if (bHasTarget)
		return mrcTrue;

	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_004(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poMissile->RotateTo(CONVERT_ANGLE(nParam1), CONVERT_TIME(nParam2));

	return mrcTrue;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_005(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	CCharacter* poOwner = NULL;
	CSpellInstance* spell = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	LOG_PROCESS_ERROR(poOwner);

	spell = poOwner->GetPendingSpell();
	LOG_PROCESS_ERROR(spell);

	return mrcTrue;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_006(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	if(poMissile->GetCollisionCount() > 0)
	{
		poMissile->SetAttr(matMaxCollisionCount, poMissile->GetAttr(matMaxCollisionCount) - 1);
		return mrcTrue;
	}

	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_007(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	INT32 nRadius = nParam1;
	INT32 nAngle = CONVERT_ANGLE(nParam3);
	CTargetScanner Scanner;
	CRegion* poRegion = NULL;
	CCharacter* target = NULL;
	TARGET_NODE* pTargetNode = NULL;
	CCharacter* poOwner = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	poRegion = poMissile->GetRegion();
	LOG_PROCESS_ERROR(poRegion);

	PROCESS_ERROR(nParam1 >= 0 && nParam2 >= 0 && nParam3 >= 0);

	PROCESS_ERROR(!bIsRollingBack);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	LOG_PROCESS_ERROR(poOwner);

	nRetCode = Scanner.Init(poOwner, sprtSector, nRadius, 0, nAngle, poMissile->GetFaceDirection(), poMissile->GetSpellAttr(satTargetObjType), poMissile->GetSpellAttr(satTargetRelationship), poMissile->GetSpellAttr(satTargetStance), poMissile->GetSpellAttr(satTargetDeadLimit), FALSE, poMissile->GetSpellAttr(satIgnoreObstacle), poMissile->GetSpellAttr(satTargetCheckNode));
	LOG_PROCESS_ERROR(nRetCode);

	Scanner.SetCenterPt(poMissile->GetX(), poMissile->GetY(), poMissile->GetZ());
	Scanner.Scan(poRegion, poOwner);

	Scanner.BeginTarget();
	pTargetNode = Scanner.NextTarget();

	if(pTargetNode != NULL)
		poMissile->SetLockedTargetID(pTargetNode->dwTargetID);

	return mrcTrue;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_008(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	INT32 nRadius1 = nParam1;
	INT32 nRadius2 = nParam2;
	CTargetScanner Scanner;
	CRegion* poRegion = NULL;
	TARGET_NODE* pTargetNode = NULL;
	CCharacter* poOwner = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	poRegion = poMissile->GetRegion();
	LOG_PROCESS_ERROR(poRegion);

	PROCESS_ERROR(nParam1 >= 0 && nParam2 >= 0 && nParam3 >= 0);

	PROCESS_ERROR(!bIsRollingBack);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	LOG_PROCESS_ERROR(poOwner);

	nRetCode = Scanner.Init(poOwner, sprtCircle, nRadius1, nRadius2, 0, poMissile->GetFaceDirection(), poMissile->GetSpellAttr(satTargetObjType), poMissile->GetSpellAttr(satTargetRelationship), poMissile->GetSpellAttr(satTargetStance), poMissile->GetSpellAttr(satTargetDeadLimit), FALSE, poMissile->GetSpellAttr(satIgnoreObstacle), poMissile->GetSpellAttr(satTargetCheckNode));
	LOG_PROCESS_ERROR(nRetCode);

//	SPL("ModifierMissile_LockNearestTargetInCircle");

	Scanner.SetCenterPt(poMissile->GetX(), poMissile->GetY(), poMissile->GetZ());
	Scanner.SetTargetPt(poMissile->GetX(), poMissile->GetY(), poMissile->GetZ());
	Scanner.Scan(poRegion, poOwner);

	Scanner.BeginTarget();

	while((pTargetNode = Scanner.NextTarget()) != NULL)
	{
		if (pTargetNode->dwTargetID != poMissile->GetLockedTargetID())
		{
			if (pTargetNode->dwTargetID != 0)
			{
				SPL("Lock Target ID: %u", pTargetNode->dwTargetID);
				poMissile->SetLockedTargetID(pTargetNode->dwTargetID);
			}
			break;
		}
	}

	return mrcTrue;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_009(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	CCharacter* poOwner = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	LOG_PROCESS_ERROR(poOwner);

	if(poOwner->GetMoveState() == CMS_STAND)
		return mrcTrue;

	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_010(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	CCharacter* poOwner = NULL;
	CSpellInstance* spell = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	LOG_PROCESS_ERROR(poOwner);

	if(poOwner->GetExFlag().CheckFlag(nParam1))
		return mrcTrue;

	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_011(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	CCharacter* poOwner = NULL;
	CSpellInstance* spell = NULL;
	INT32 nEffectPct = 0;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	nEffectPct = poMissile->GetSpellAttr(satEffectPct);

	nEffectPct = nEffectPct * (RATE_MAX + nParam1 * (nParam2 - (poMissile->GetAttr(matMaxCollisionCount) - poMissile->GetCollisionCount()))) / RATE_MAX;

	poMissile->SetSpellAttr(satEffectPct, nEffectPct);

	return mrcTrue;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_012(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	CCharacter* poOwner = NULL;
	CSpellInstance* spell = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);
	poMissile->DeleteSelf();

	return mrcTrue;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_013(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	CCharacter* poOwner = NULL;
	CSpellInstance* spell = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	PROCESS_ERROR(poOwner);

	poMissile->AdjustTargetPt(poOwner->GetX(), poOwner->GetY(), poOwner->GetZ());

	return mrcTrue;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_014(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 eAttr = nParam1;
	INT32 nValue = nParam2;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	LOG_PROCESS_ERROR(eAttr > matInvalid && eAttr < matTotal);

	poMissile->SetAttr(eAttr, nValue);

	return mrcTrue;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_015(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT64 llDist = CONVERT_LENGTH(nParam1);
	INT32 nCount = nParam2;
	CRegion* poRegion = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	poRegion = poMissile->GetRegion();
	LOG_PROCESS_ERROR(poRegion);

	PROCESS_ERROR(!bIsRollingBack);

	{
		struct ScanMissile
		{
			INT32 nSelfID;
			INT32 nSpellID;
			INT32 nCasterID;
			INT32 nCountLimit;
			INT32 nCurrentCount;
			INT64 llDist;
			CMissile* poSelfMissile;

			BOOL operator()(CMissile* poMissile)
			{
				if(poMissile->GetObjID() != nSelfID && poMissile->GetSpellData()->m_nID == nSpellID && poMissile->GetOwnerID() == nCasterID && nCurrentCount++ <= nCountLimit)
				{
					if(poMissile->GetDistance3D(poSelfMissile) < llDist * llDist)
						poMissile->DeleteSelf();
				}

				return TRUE;
			}

			BOOL operator()(CRegion* poRegion)
			{
				return poRegion->TraverseMissile(*this);
			}
		};

		ScanMissile scanner;
		scanner.nSelfID = poMissile->GetObjID();
		scanner.nSpellID = poMissile->GetSpellData()->m_nID;
		scanner.nCasterID = poMissile->GetOwnerID();
		scanner.nCountLimit = nCount;
		scanner.nCurrentCount = 0;
		scanner.poSelfMissile = poMissile;
		scanner.llDist = llDist;

		poRegion->Traverse9Region(scanner);
	}

	return mrcTrue;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_016(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	CRegion* poRegion = NULL;
	INT32 nRetCode = 0;
	CCharacter* poOwner = NULL;
	TARGET_NODE* pTargetNode = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poRegion = poMissile->GetRegion();
	LOG_PROCESS_ERROR(poRegion);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	PROCESS_ERROR(poOwner);

	poMissile->GetScanner().ClearTarget();

	poMissile->GetScanner().SetCenterPt(poMissile->GetX(), poMissile->GetY(), poMissile->GetZ());
	poMissile->GetScanner().SetTargetPt(poMissile->GetX(), poMissile->GetY(), poMissile->GetZ());
	poMissile->GetScanner().SetDirection(poMissile->GetFaceDirection());

	nRetCode = poMissile->GetScanner().Scan(poRegion, poOwner);
	PROCESS_ERROR(nRetCode);

	poMissile->GetScanner().BeginTarget();

	while((pTargetNode = poMissile->GetScanner().NextTarget()) != NULL)
	{
		CCharacter* poCurrentTarget = CGameWorld::GetInstance().FindValidCharacter(pTargetNode->dwTargetID);

		if(poCurrentTarget != NULL)
		{
			if (poCurrentTarget->GetObjType() == otRole)
				return mrcTrue;

			if (poCurrentTarget->GetObjType() == otNpc)
			{
				CNpc* poNpc = static_cast<CNpc*>(poCurrentTarget);

				if (poNpc->GetPetType() != 0)
					return mrcTrue;
			}

		}
	}

	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_017(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	INT32 nRetCode = 0;
	CCharacter* poPendingChar = NULL;
	CAura* poAuraInfo = NULL;
	CAuraInstance* poAuraInst = NULL;
	CCharacter* poOwner = NULL;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	LOG_PROCESS_ERROR(poOwner);

	poPendingChar = poMissile->GetPendingChar();
	LOG_PROCESS_ERROR(poPendingChar);

	poAuraInfo = CSpellConfig::GetInstance().FindAuraTemplate(nParam1);
	LOG_PROCESS_ERROR(poAuraInfo);

	poAuraInst = poPendingChar->AppendAura(poAuraInfo, poOwner, poMissile->GetObjID(), NULL, CONVERT_TIME(nParam3), 0, poMissile->GetSpellData()->m_nID, poMissile->GetSpellData()->m_nLevel);
	PROCESS_SUCCESS(poAuraInst == NULL);

	return mrcTrue;
Exit1:
	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_018(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	CCharacter* target = NULL;
	CAuraInstance* poAura = NULL;
	INT32 nRetCode = 0;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	target = poMissile->GetPendingChar();
	LOG_PROCESS_ERROR(target);

	if(nParam1 > 0)
	{
		poAura = target->GetFirstAura(nParam1);
		PROCESS_SUCCESS(poAura == NULL);

		target->RemoveAura(poAura, TRUE);
	}

	if(nParam2 > 0)
	{
		nRetCode = target->RemoveAuraByType(nParam2);
		LOG_CHECK_ERROR(nRetCode);
	}

	if(nParam3 > 0)
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

INT32 ModifierMissile_019(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	CCharacter* owner = NULL;
	CCharacter* target = NULL;
	CAuraInstance* poAura = NULL;
	INT32 nRetCode = 0;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	target = poMissile->GetPendingChar();
	LOG_PROCESS_ERROR(target);

	owner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	LOG_PROCESS_ERROR(owner);

	nRetCode = owner->CanAttack(target);
	PROCESS_SUCCESS(!nRetCode);

	return mrcTrue;
Exit1:
	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_020(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	CCharacter* poOwner = NULL;
	INT32 nRetCode = 0;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	LOG_PROCESS_ERROR(poOwner);

	PROCESS_SUCCESS(!poOwner->IsDead());

	return mrcTrue;
Exit1:
	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_021(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	CCharacter* poChar = NULL;
	INT32 nRetCode = 0;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poChar = poMissile->GetPendingChar();
	LOG_PROCESS_ERROR(poChar);

	nRetCode = poMissile->TrigSubSpell(nParam1, poChar, poChar->GetX(), poChar->GetY(), poChar->GetZ());
	PROCESS_SUCCESS(!nRetCode);

	return mrcTrue;
Exit1:
	return mrcFalse;
Exit0:
	return mrcError;
}

INT32 ModifierMissile_022(void* poTarget, BOOL bIsRollingBack, INT32 nParam1, INT32 nParam2, INT32 nParam3, void* pExParam)
{
	//WRN("Execute Function - %s", __FUNCTION__);

	CCharacter* poChar = NULL;
	CCharacter* poOwner = NULL;
	CBullet* poBullet = NULL;

	INT32 nRetCode = 0;

	CMissile* poMissile = static_cast<CMissile*>(poTarget);
	LOG_PROCESS_ERROR(poMissile);

	PROCESS_ERROR(!bIsRollingBack);

	poChar = poMissile->GetPendingChar();
	LOG_PROCESS_ERROR(poChar);

	poOwner = CGameWorld::GetInstance().FindValidCharacter(poMissile->GetOwnerID());
	LOG_PROCESS_ERROR(poOwner);

	poBullet = poMissile->GetScanner().DoSingleBullet(poMissile, poOwner, poChar, poMissile, betDamage);
	PROCESS_SUCCESS(poBullet == NULL);

	return mrcTrue;
Exit1:
	return mrcFalse;
Exit0:
	return mrcError;
}


ModifierFunc g_MissileModifier[mmiCount] = 
{
	{ NULL, FALSE }, 
	{ ModifierMissile_001, FALSE },  // CastSubSpellToCurPos					 Cast a sub-spell at the current position (such as an area explosion)
	{ ModifierMissile_002, FALSE },  // BulletToEachTarget					     Fire a projectile at each target (multiple locks)
	{ ModifierMissile_003, FALSE },  // JustAddCollisionCount					 Only increment the collision count (record hits)
	{ ModifierMissile_004, FALSE },  // RotateTo								 Rotate toward the target (adjust projectile trajectory)
	{ ModifierMissile_005, FALSE },  // CoverParam1WithTargetPt				     Replace parameter 1 with the target point (adjust trajectory dynamically)
	{ ModifierMissile_006, FALSE },  // ReduceMaxCollisionCountIfCollision	     Reduce the maximum collision count after a collision (such as diminishing penetration)
	{ ModifierMissile_007, FALSE },  // LockNearestTargetInSector				 Lock the nearest target in a sector (such as a melee sweep)
	{ ModifierMissile_008, FALSE },  // LockNearestTargetInCircle				 Lock the nearest target in a circular area (area-of-effect spell)
	{ ModifierMissile_009, FALSE },  // CheckOwnerMovementStateAndDeleteSelf     Check owner movement and destroy itself (such as disappearing when the character stops)
	{ ModifierMissile_010, FALSE },  // CheckOwnerExFlag						 Check owner extra flags (such as whether invincibility affects the projectile)
	{ ModifierMissile_011, FALSE },  // AddEffectByRemainCollisionCount		     Add an effect based on remaining collisions (such as increased damage after penetration)
	{ ModifierMissile_012, FALSE },  // DeleteSelf							     Destroy itself (projectile lifetime ends)
	{ ModifierMissile_013, FALSE },  // TurnToCaster							 Turn toward the caster (such as aggro attraction or camera follow)
	{ ModifierMissile_014, FALSE },  // ModifyMissileAttr						 Modify projectile attributes (speed, damage, direction, etc.)
	{ ModifierMissile_015, FALSE },  // RemoveSameMissile						 Remove projectiles of the same type (avoid duplicate effects)
	{ ModifierMissile_016, FALSE },  // RemoveSameMissile						 Remove projectiles of the same type (avoid duplicate effects)
	{ ModifierMissile_017, FALSE },  // RemoveSameMissile						 Remove projectiles of the same type (avoid duplicate effects)
	{ ModifierMissile_018, FALSE },  // RemoveSameMissile						 Remove projectiles of the same type (avoid duplicate effects)
	{ ModifierMissile_019, FALSE },  // RemoveSameMissile						 Remove projectiles of the same type (avoid duplicate effects)
	{ ModifierMissile_020, FALSE },  // RemoveSameMissile						 Remove projectiles of the same type (avoid duplicate effects)
	{ ModifierMissile_021, FALSE },  // RemoveSameMissile						 Remove projectiles of the same type (avoid duplicate effects)
	{ ModifierMissile_022, FALSE },  // RemoveSameMissile						 Remove projectiles of the same type (avoid duplicate effects)
};
