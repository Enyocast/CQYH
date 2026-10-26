#include "stdafx.h"
#include "spell_instance.h"
#include "spell_data.h"
#include "spell_def.h"
#include "spell_bullet.h"
#include "character.h"
#include "region.h"
#include "game_world.h"
#include "modifier_tree.h"
#include "message_handler.h"
#include "level_data.h"
#include "profile.h"

CSpellInstance::CSpellInstance(void)
{
	m_nCasterFaceDirection = 0;
	m_nAttackForce = 0;
	m_dwFromObjID = 0;
	m_nStartFrm = 0;
	m_llInitX = 0;
	m_llInitY = 0;
	m_llInitZ = 0;

	m_nWeaponSpeedFactor = 0;
	m_nWeaponStiffFactor = 0;
	m_nAtkSpeedFactor = 0;

	m_nSpellSerial = 0;
	m_nCastSerial = 0;
	m_nEffectSerial = MAX_EX_CAST;

	m_nPrepareTimeMinFrm = 0;
	m_nPrepareTimeMaxFrm = 0;
	m_nIntervalFrm = 0;
	m_nHardTimeFrm = 0;
	m_nResetTimeFrm = 0;
	m_nCacheTimeFrm = 0;
	m_nAccumulateTimeMaxFrm = 0;
	m_nStiffFrm = 0;
	m_bHitTarget = FALSE;
	m_bHitRole = FALSE;
	m_bFastStop = FALSE;
	m_bSelfCanceled = FALSE;
	memset(m_nExCastFrm, 0, sizeof(m_nExCastFrm));
	m_StackNode.pNext = NULL;
}

CSpellInstance::~CSpellInstance(void)
{
}

BOOL CSpellInstance::Init(CSpell* pInfo, CCharacter* poChar, UINT32 dwFromObjID, INT32 dwStartFrm, INT64 llInitX, INT64 llInitY, INT64 llInitZ)
{
	INT32 nWeaponType = 0;

	LOG_PROCESS_ERROR(pInfo);
	LOG_PROCESS_ERROR(poChar);

	pInfo->CopyTo(this);

	ClearBulletList();

	m_nAttackForce = 0;
	m_dwFromObjID = dwFromObjID;
	m_nStartFrm = dwStartFrm;
	m_llInitX = llInitX;
	m_llInitY = llInitY;
	m_llInitZ = llInitZ;
	m_nWeaponSpeedFactor = RATE_MAX;
	m_nWeaponStiffFactor = RATE_MAX;
	m_nPrepareTimeMinFrm = 0;
	m_nPrepareTimeMaxFrm = 0;
	m_nIntervalFrm = 0;
	m_nHardTimeFrm = 0;
	m_nResetTimeFrm = 0;
	m_nCacheTimeFrm = 0;


	m_nSpellSerial = poChar->GetSpellSerial();
	m_nCastSerial = 0;
	m_nEffectSerial = MAX_EX_CAST;

	m_bHitTarget = FALSE;
	m_bHitRole = FALSE;
	m_bFastStop = FALSE;
	m_bSelfCanceled = FALSE;
	m_nAtkSpeedFactor = RATE_MAX;
	m_FlagBits.ResetFlag();
	m_StackNode.pNext = NULL;


	nWeaponType = poChar->GetWeaponType();
	LOG_PROCESS_ERROR(nWeaponType > WEAPONTYPE_INVALID && nWeaponType < WEAPONTYPE_TOTAL);


	if(m_Data.m_nAttrTable[satAffectedByWeaponSpeed])
	{
		m_nWeaponSpeedFactor = g_GWConfig.BaseWeaponSpeed[nWeaponType];
		m_nWeaponStiffFactor = g_GWConfig.BaseWeaponStiffFactor[nWeaponType];
	}


	if(m_Data.m_nAttrTable[satAffectedByAtkSpeed])
	{
		m_nAtkSpeedFactor = poChar->GetAttr(s_SpeedTable[m_Data.m_nAttrTable[satAttackType]]);
	}

	m_nAtkSpeedFactor = m_nAtkSpeedFactor <= 0 ? RATE_MAX : m_nAtkSpeedFactor;


	return TRUE;
Exit0:
	return FALSE;
}

void CSpellInstance::Release(void)
{
	m_Scanner.UnInit();

	CGameWorld::GetInstance().DelSpellInstance(this);
}

void CSpellInstance::ResetTimeParam(void)
{
	m_nPrepareTimeMinFrm = CONVERT_TIME(((m_Data.m_nAttrTable[satPrepareTimeMin] * RATE_MAX / m_nAtkSpeedFactor) * m_nWeaponSpeedFactor / RATE_MAX));
	m_nPrepareTimeMaxFrm = CONVERT_TIME(((m_Data.m_nAttrTable[satPrepareTimeMax] * RATE_MAX / m_nAtkSpeedFactor) * m_nWeaponSpeedFactor / RATE_MAX));
	m_nIntervalFrm = CONVERT_TIME(((m_Data.m_nAttrTable[satInterval] * RATE_MAX / m_nAtkSpeedFactor) * m_nWeaponSpeedFactor / RATE_MAX));
	m_nHardTimeFrm = CONVERT_TIME(((m_Data.m_nAttrTable[satHardTime] * RATE_MAX / m_nAtkSpeedFactor) * m_nWeaponSpeedFactor / RATE_MAX));
	m_nResetTimeFrm = CONVERT_TIME(m_Data.m_nAttrTable[satResetTime]);
	m_nCacheTimeFrm = CONVERT_TIME(((m_Data.m_nAttrTable[satCacheTime] * RATE_MAX / m_nAtkSpeedFactor) * m_nWeaponSpeedFactor / RATE_MAX));
	m_nAccumulateTimeMaxFrm = m_Data.m_nAttrTable[satAccumulateTimeMax] > 0 ? CONVERT_TIME(((m_Data.m_nAttrTable[satAccumulateTimeMax] * RATE_MAX / m_nAtkSpeedFactor) * m_nWeaponSpeedFactor / RATE_MAX)) : 1;
	m_nStiffFrm = CONVERT_TIME(m_Data.m_nAttrTable[satBaseStiffTime] * m_nWeaponStiffFactor / RATE_MAX);

	for(INT32 i = 0; i < MAX_EX_CAST; i++)
	{
		if(m_Data.m_ExCastPoint[i].m_nExCastTime > 0)
		{
			m_nExCastFrm[i] = CGameWorld::GetInstance().GetGameFrame() + CONVERT_TIME(((m_Data.m_ExCastPoint[i].m_nExCastTime * RATE_MAX / m_nAtkSpeedFactor) * m_nWeaponSpeedFactor / RATE_MAX));
		}
	}
}

BOOL CSpellInstance::DoEffect(CCharacter* poCaster)
{
	INT32 nRetCode = 0;
	INT32 nResCost = 0;

	CSceneObject* poFromObj = NULL;
	CRegion* poRegion = NULL;

	m_nCastSerial++;
	m_nEffectSerial = MAX_EX_CAST;
	ClearBulletList();

	nResCost = GetConsumeAttr(satDurativeCostValue) + (INT64)GetConsumeAttr(satDurativeCostValuePct) * poCaster->GetAttr(catMaxMp) / RATE_MAX;

	if (nResCost >= 0)
		PROCESS_ERROR(nResCost <= poCaster->GetMp());

	poFromObj = CGameWorld::GetInstance().FindValidObj(m_dwFromObjID);
	PROCESS_ERROR(poFromObj);

	GetScanner().SetCenterPt(poFromObj->GetX(), poFromObj->GetY(), poFromObj->GetZ());
	GetScanner().SetDirection(poFromObj->GetFaceDirection());

	if(GetAttr(satLockType) == spltObject)
	{
		CCharacter* target = CGameWorld::GetInstance().FindValidCharacter(GetScanner().GetLockedTarget());
		if(target != NULL)
		{
			nRetCode = poCaster->CheckTargetPos(poFromObj, this, target->GetX(), target->GetY(), target->GetZ(), target->GetRadius(), GetAttr(satTolerantGrids));
			PROCESS_ERROR(nRetCode == errSuccess);

			nRetCode = poCaster->CheckTarget(this, target);
			PROCESS_ERROR(nRetCode == errSuccess);
		}
	}

	poRegion = poCaster->GetRegion();
	LOG_PROCESS_ERROR(poRegion);

	poCaster->ApplyModifierTree(GetAttr(satOnCast), this);

//	if(m_bHitTarget)
//	{
//		nResCost = nResCost + GetConsumeAttr(satModifierCostValue) + (INT64)GetConsumeAttr(satModifierCostValuePct) * poCaster->GetAttr(catMaxMp) / RATE_MAX;
//	}

	poCaster->ChangeMp(-nResCost);

	if(GetAttr(satCoolDownTriggerType) == spcdtOnCast)
	{
		INT32 nCoolDownFrm = GetSelfCoolDownFrm();
		poCaster->AddCooldown(MakeCoolDownID(COOLDOWN_SPELL, GetID()), nCoolDownFrm);

		// group cooldown
		{
			for(INT32 i = 0; i < m_Data.m_nCdGrpCount; i++)
			{
				nCoolDownFrm = m_Data.m_CdGrp[i].m_nCdGrpValue;
				poCaster->AddCooldown(MakeCoolDownID(COOLDOWN_GROUP, m_Data.m_CdGrp[i].m_nCdGrpID), nCoolDownFrm);
			}
		}
	}

	if (poCaster->GetObjType() == otRole && GetAttr(satDuraCost))
	{
		CItemBag* poItemBag = ((CRole*)poCaster)->GetItemBag();
		LOG_PROCESS_ERROR(poItemBag);

		poItemBag->LoseWeaponDur();
	}

#ifndef _ROBOT
	nRetCode = CCliMessageHandler::GetInstance().DoCharCastSpell(poFromObj, this, poCaster);
	LOG_CHECK_ERROR(nRetCode);
#endif  // _ROBOT

//	{
//		CBullet* poBullet = NULL;
//
//		BeginBullet();
//
//		while((poBullet = NextBullet()) != NULL)
//		{
//			poBullet->Update(poBullet->GetTarget(), CGameWorld::GetInstance().GetGameFrame());
//		}
//	}

	return TRUE;
Exit0:
	return FALSE;
}

void CSpellInstance::TryExCastTrigger(CCharacter* poCaster, INT32 nFrm)
{
	CSceneObject* poFromObj = CGameWorld::GetInstance().FindValidObj(m_dwFromObjID);
	LOG_PROCESS_ERROR(poFromObj);

	GetScanner().SetCenterPt(poFromObj->GetX(), poFromObj->GetY(), poFromObj->GetZ());
	GetScanner().SetDirection(poCaster->GetFaceDirection());

	for(INT32 i = 0; i < MAX_EX_CAST; i++)
	{
		if(m_nExCastFrm[i] > 0 && nFrm >= m_nExCastFrm[i])
		{
//			DBG("Ex Cast id: %d", i);
			m_nEffectSerial = i;

			poCaster->ApplyModifierTree(m_Data.m_ExCastPoint[i].m_nExOnCast, this);
			m_nExCastFrm[i] = 0;

#ifndef _ROBOT
			CCliMessageHandler::GetInstance().DoCharExCastSpell(poFromObj, this, poCaster);
#endif
//			DBG("Ex Cast End.");
		}
	}
Exit0:
	return;
}

INT32 CSpellInstance::GetDelayFrm(CSceneObject* poFromObj, CSceneObject* poTargetObj)
{
	INT32 nDelayFrm = 0;

	INT32 nSpeed = GetAttr(satSpeed);

	if(nSpeed != 0)
	{
		INT64 llDistCM = 0;
		INT64 llDistCM2 = poFromObj->GetDistance3D(poTargetObj) / POINT_PER_CM / POINT_PER_CM;
		llDistCM2 = llDistCM2 / 64 / 64;
		llDistCM2 = llDistCM2 > MAX_SQUARE ? MAX_SQUARE : llDistCM2;

		llDistCM = g_Sqrt((UINT16)llDistCM2) * 64;

		nDelayFrm = CONVERT_TIME(llDistCM * 1000 / nSpeed);
	}

	return nDelayFrm;
}
