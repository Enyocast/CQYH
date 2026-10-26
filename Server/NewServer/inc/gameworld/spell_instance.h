#ifndef _SPELL_INSTANCE_H_
#define _SPELL_INSTANCE_H_

#include "spell_def.h"
#include "spell.h"
#include "target_scanner.h"
#include "spell_bullet.h"

class CSpell;
class CCharacter;
class CRegion;

#define MAX_TEMP_VALUE_COUNT	8

class CSpellInstance : public CSpell
{
public:
	CSpellInstance(void);
	virtual ~CSpellInstance(void);
	virtual void Release(void);
	virtual CSpell* MakeCopy(void) { return NULL; }

	BOOL Init(CSpell* pInfo, CCharacter* poChar, UINT32 dwFromObjID, INT32 dwStartFrm, INT64 llInitX, INT64 llInitY, INT64 llInitZ);
	BOOL DoEffect(CCharacter* poCaster);
	void TryExCastTrigger(CCharacter* poCaster, INT32 nFrm);

	INT32 GetDelayFrm(CSceneObject* poFromObj, CSceneObject* poTargetObj);

	void ResetTimeParam(void);

	inline INT32 GetBulletAttack(void);
	inline INT32 GetCasterFaceDirection(void);
	inline INT32 GetStartFrm(void);

	inline UINT32 GetFromObjID(void);
	inline CTargetScanner& GetScanner(void);

	inline INT64 GetInitX(void);
	inline INT64 GetInitY(void);
	inline INT64 GetInitZ(void);

	inline BOOL IsChannelOver(void);

	inline INT32 GetAtkSpeedFactor(void);
	inline INT32 GetWeaponSpeedFactor(void);
	inline INT32 GetWeaponStiffFactor(void);

	inline INT32 GetSpellSerial(void);
	inline INT32 GetCastSerial(void);
	inline INT32 GetEffectSerial(void);

	inline INT32 GetPrepareTimeMinFrm(void);
	inline INT32 GetPrepareTimeMaxFrm(void);
	inline INT32 GetIntervalFrm(void);
	inline INT32 GetHardTimeFrm(void);
	inline INT32 GetResetTimeFrm(void);
	inline INT32 GetCacheTimeFrm(void);
	inline INT32 GetAccumulateTimeMaxFrm(void);
	inline INT32 GetStiffFrm(void);
	inline INT32 GetExCastFrm(INT32 idx);

	inline void SetFastStop(BOOL bFastStop);
	inline BOOL IsFastStop(void);

	inline void HitTarget(BOOL bHit);
	inline BOOL HasHitTarget(void);

	inline void HitRole(BOOL bHit);
	inline BOOL HasHitRole(void);

	inline void SetSelfCancel(BOOL bCancel);
	inline BOOL IsSelfCancened(void);

	inline void AddBullet(CBullet* poBullet);
	inline void BeginBullet(void);
	inline CBullet* NextBullet(void);
	inline INT32 GetBulletCount(void);
	inline void ClearBulletList(void);

	inline CFlagBits& GetFlagBits(void);

	inline SimpleListNode& GetStackNode(void);

protected:
	CTargetScanner m_Scanner;
	CFlagBits m_FlagBits;

	UINT32 m_dwFromObjID;
	INT32 m_nStartFrm;

	INT32 m_nBulletFlag;
	INT32 m_nAttackForce;
	INT32 m_nCasterFaceDirection;

	INT64 m_llInitX;
	INT64 m_llInitY;
	INT64 m_llInitZ;

	INT32 m_nWeaponSpeedFactor;
	INT32 m_nWeaponStiffFactor;
	INT32 m_nAtkSpeedFactor;

	INT32 m_nSpellSerial;
	INT32 m_nCastSerial;
	INT32 m_nEffectSerial;

	INT32 m_nPrepareTimeMinFrm;
	INT32 m_nPrepareTimeMaxFrm;
	INT32 m_nIntervalFrm;
	INT32 m_nHardTimeFrm;
	INT32 m_nResetTimeFrm;
	INT32 m_nCacheTimeFrm;
	INT32 m_nAccumulateTimeMaxFrm;
	INT32 m_nStiffFrm;

	BOOL m_bHitTarget;
	BOOL m_bHitRole;
	BOOL m_bFastStop;
	BOOL m_bBreakMark;
	BOOL m_bSelfCanceled;

	INT32 m_nExCastFrm[MAX_EX_CAST];

	typedef std::list<CBullet*> TBulletList;
	TBulletList m_BulletList;
	TBulletList::iterator m_BulletItr;

	SimpleListNode m_StackNode;
};

#include "spell_instance_inl.h"

#endif // _spell_instance_h__
