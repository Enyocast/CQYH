#ifndef _SPELL_BULLET_H_
#define _SPELL_BULLET_H_

#include "base_list.h"
#include "attr_list.h"
#include "attr_modifier.h"
#include "spell_data.h"
#include "spell_def.h"

class CSpell;
class CCharacter;
class CSceneObject;
class CSpellInstance;
class CMissile;
struct ATTR_LEVEL;
/*
enum EBulletEffectType
{
	betInvalid = -1,

	betDamage,
	betHeal,
	betNone,

	betTotal
};
*/

struct BulletEvent
{
	UINT32 dwEventKey;
	INT32 nModifierID;
};


class CBullet
{
public:
	CBullet(void);
	virtual ~CBullet(void);

	void UnInit(void);

	BOOL Init(INT32 eEffectType, INT32 nCastSerial, INT32 nEffectSerial, INT32 nIndex, INT32 nDelayFrm);

	BOOL OnCreate(CSpellInstance* poSpell, CCharacter* poCaster, CCharacter* poTarget, CSceneObject* poFromObj, BOOL bTargetLocked);

	BOOL OnCreate(CMissile* poMissile, const ExtraParam* exparam, CCharacter* poCaster, CCharacter* poTarget, CSceneObject* poFromObj, BOOL bTargetLocked);

	void OnTimeup(CCharacter* poTarget, INT32 nFrm);

	void Update(CCharacter* poTarget, INT32 nFrm);

	inline UINT32 GetCasterID(void);
	inline INT32 GetParam1(void);
	inline INT32 GetParam2(void);
	inline INT32 GetSpellID(void);
	inline INT32 GetSpellLevel(void);
	inline INT32 GetSpellRuneSlot(void);
	inline INT32 GetBulletType(void);

	inline void SetRemoveFlag(BOOL bRemove);
	inline BOOL NeedRemove(void);

	inline INT32 GetEffectValue(void);
	inline void SetEffectValue(INT32 nEffectValue);

	inline void SetFromObjID(UINT32 dwID);
	inline UINT32 GetFromObjID(void);
	inline INT32 GetDelayFrame(void);

	inline CFlagBits& GetEffectFlag(void);
	inline CFlagBits& GetSpellFlag(void);

	inline void SetSpellSerial(INT32 nSerial);
	inline INT32 GetSpellSerial(void);
	
	inline void SetX(INT64 nValue);
	inline INT64 GetX(void);

	inline INT32 GetAtkHi(void);
	inline INT32 GetAtkLo(void);
	inline INT64 GetAttackRandom(void);

	inline INT32 GetIndex(void);

	inline ExtraParam* GetSpellExParam(void);
	inline SPELL_ENTRY* GetSpellData(void);

	inline void SetTargetHpChangeValue(INT32 nValue);
	inline INT32 GetTargetHpChangeValue(void);

	inline INT32 GetStiffFrm(void);

	inline INT32 GetStiffRandomNum(void);

	inline CCharacter* GetTarget(void);

	inline INT32 GetSpellAttr(INT32 eAttrType);
	inline BOOL SetSpellAttr(INT32 eAttrType, INT32 nValue);

	inline INT32 GetCastSerial(void);
	inline INT32 GetEffectSerial(void);

	inline BASE_LIST_NODE& GetListNode(void);

	inline INT64 GetTargetX(void);
	inline INT64 GetTargetY(void);
	inline INT64 GetTargetZ(void);

	inline BOOL IsFromMissile(void);
	inline BOOL IsTargetLocked(void);

	inline void SetEventOwner(CCharacter* poOwner);
	inline CCharacter* GetEventOwner(void);

protected:
	typedef void (CBullet::*OnCreateFunc)(CCharacter* poCaster, CCharacter* poTarget);
	typedef void (CBullet::*OnRollFunc)(CCharacter* poCaster, CCharacter* poTarget);
	typedef void (CBullet::*OnTimeupFunc)(CCharacter* poTarget, CCharacter* poCaster, INT32 nFrm);
	typedef void (CBullet::*OnAfterEffectFunc)(CCharacter* poTarget, CCharacter* poCaster, INT32 nFrm);

	BOOL _OnCreate(const SPELL_ENTRY* data, const ExtraParam* exparam, CCharacter* poCaster, CCharacter* poTarget, CSceneObject* poFromObj);

	void _OnCreateDamage(CCharacter* poCaster, CCharacter* poTarget);
	void _OnCreateHeal(CCharacter* poCaster, CCharacter* poTarget);
	void _OnCreateNone(CCharacter* poCaster, CCharacter* poTarget);

	void _OnTimeupDamage(CCharacter* poTarget, CCharacter* poCaster, INT32 nFrm);
	void _OnTimeupHeal(CCharacter* poTarget, CCharacter* poCaster, INT32 nFrm);
	void _OnTimeupNone(CCharacter* poTarget, CCharacter* poCaster, INT32 nFrm);

	void _AfterDamageEffectProcess(CCharacter* poTarget, CCharacter* poCaster, INT32 nFrm);
	void _AfterHealEffectProcess(CCharacter* poTarget, CCharacter* poCaster, INT32 nFrm);
	void _AfterNoneEffectProcess(CCharacter* poTarget, CCharacter* poCaster, INT32 nFrm);

	void _OnRollPhy(CCharacter* poCaster, CCharacter* poTarget);
	void _OnRollMag(CCharacter* poCaster, CCharacter* poTarget);

protected:
	BASE_LIST_NODE m_ListNode;
	SPELL_ENTRY m_SpellData;
	ExtraParam m_ExParam;
	INT32 m_eBulletType;
	BOOL m_bRemoveFlag;
	BOOL m_bFrontAttack;
	BOOL m_bFromMissile;
	BOOL m_bTargetLocked;
	CFlagBits m_oEffectFlag;
	CFlagBits m_oSpellFlag;

	INT32 m_nDodgeRate;
	INT32 m_nParryRate;
	INT32 m_nBlockRate;
	INT32 m_nCritRate;
	INT32 m_nSpellEffectValue;

	INT32 m_nHitRecovery;
	INT32 m_nCasterLevel;
	INT32 m_nY3;
	
	CCharacter* m_poTarget;        // +792
	CCharacter* m_poEventOwner;    // +800

	UINT32 m_dwCasterCharID;
	INT32 m_dwTimeupFrm;
	UINT32 m_dwFromObjID;
	INT32 m_nDelayFrm;

	INT32 m_nAtkHi;
	INT32 m_nAtkLo;
	INT64 m_llAtkRandom;

	INT64 m_llAttackX;
	INT64 m_llEffectValue;
	INT32 m_nTargetHpChangeValue;
	INT32 m_nThreatValue;

	INT32 m_nParam1;
	INT32 m_nParam2;
	INT32 m_nSpellSerial;
	INT32 m_nCastSerial;
	INT32 m_nEffectSerial;
	INT32 m_nIndex;

	INT64 m_llTargetX;
	INT64 m_llTargetY;
	INT64 m_llTargetZ;

	INT32 m_nStiffFrm;
	INT32 m_nStiffRandomNum;

	const ATTR_LEVEL* m_pCasterLevel;
	const ATTR_LEVEL* m_pTargetLevel;

	OnCreateFunc m_CreateFunc[betTotal];
	OnRollFunc m_RollFunc[spjtTotal];
	OnTimeupFunc m_TimeupFunc[betTotal];
	OnAfterEffectFunc m_AfterEffectFunc[betTotal];

};

#define MAX_TABLE_NODES 8

class CRoundTable
{
public:
	CRoundTable(void);

	void Init(INT32 nRate, INT32 nDefaultKey);

	BOOL AddNode(INT32 nKey, INT32 nRate);

	//BOOL AddLastNode(INT32 nKey);

	INT32 Roll(void);

private:
	struct TableNode
	{
		INT32 nNodeKey;
		INT32 nMin;
		INT32 nMax;
	};

	INT32 m_nMaxRate;
	INT32 m_nRate;
	INT32 m_nDefaultKey;
	INT32 m_nNodeCount;
	TableNode m_Nodes[MAX_TABLE_NODES];
};


#include "spell_bullet_inl.h"

#endif // _spell_bullet_h__
