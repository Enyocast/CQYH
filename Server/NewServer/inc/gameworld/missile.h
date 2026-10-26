#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "simple_timer.h"

#include "scene_object.h"
#include "target_scanner.h"
#include "spell.h"
#include "missile_data.h"

class CRegion;
class CRole;
class CNpc;
class CDoodad;
class CCharacter;
class CSpellInstance;
struct GRID_INSTANCE_DATA;

struct COLLISION_NODE : BASE_LIST_NODE
{
	UINT32		dwID;
	UINT32		dwType;
};

struct MISSILE_PLACED_GRID
{
	GRID_INSTANCE_DATA* pGridInstance;
	INT64 llX;
	INT64 llY;
};

class CMissile : public CSceneObject
{
public:
	CMissile();
	virtual ~CMissile();
	virtual INT32 GetObjType(void);

	inline INT32 GetAttr(INT32 eAttrType);
	inline INT32 GetTemplateID(void);
	inline void SetAttr(INT32 eAttrType, INT32 nValue);

	inline INT64 GetDestX(void);
	inline INT64 GetDestY(void);
	inline INT64 GetDestZ(void);

	inline INT32 GetLifeTimeFrm(void);
	inline INT32 GetIntervalFrm(void);
	inline INT32 GetDelayFrm(void);


	inline UINT32 GetOwnerID(void);

	inline UINT32 GetLockedTargetID(void);
	void SetLockedTargetID(UINT32 dwTargetID);

	inline const SPELL_ENTRY* GetSpellData(void);

	inline INT32 GetSpellAttr(INT32 eAttrType);
	inline void SetSpellAttr(INT32 eAttrType, INT32 nValue);

	inline INT32 GetCollisionCount(void);
	inline void AddCollisionCount(void);
	inline ExtraParam* GetSpellExParam(void);

	inline CTargetScanner& GetScanner(void);

	inline INT32 GetSpellSerial(void);
	inline INT32 GetCastSerial(void);
	inline INT32 GetEffectSerial(void);

	inline void HitTarget(BOOL bVal);

	inline CCharacter* GetPendingChar(void);

	BOOL Init(const MISSILE_DATA* poMissileData, CCharacter* poOwner, CSpellInstance* poSpell, INT64 llInitX, INT64 llInitY, INT64 llInitZ, CSceneObject* pTarget, INT32 nLifeFrm);
	BOOL Init(const MISSILE_DATA* poMissileData, CCharacter* poOwner, CSpellInstance* poSpell, INT64 llInitX, INT64 llInitY, INT64 llInitZ, INT32 nDirection, INT32 nLifeFrm);

	BOOL UnInit(void);
	BOOL MainLoop(void);

	BOOL TrigSubSpell(INT32 nSpellID, CCharacter* poTarget, INT64 nTargetX, INT64 nTargetY, INT64 nTargetZ);

	BOOL AddAffectedTarget(UINT32 dwTargetID);

	void AdjustTargetPt(INT64 llDestX, INT64 llDestY, INT64 llDestZ);

	inline void AddBullet(CBullet* poBullet);
	inline void BeginBullet(void);
	inline CBullet* NextBullet(void);

	BOOL DoBullet(CCharacter* poOwner, INT32 eBulletType);

	BOOL OnCharEnter(CCharacter* poChar);
	BOOL OnCharLeave(CCharacter* poChar);

protected:
	virtual BOOL _GridMove(INT64 llDestX, INT64 llDestY);

	typedef BOOL (CMissile::*_MoveFunc)(void);

	BOOL _LineMove(void);
	BOOL _NoMove(void);
	BOOL _LockTargetMove(void);
	BOOL _AccordingToTerrainMove(void);

	BOOL _CheckCollision(void);
	void _OnRemove(void);
    BOOL _ChangeRegion(CRegion* poDestRegion);

#ifndef _ROBOT
	BOOL _ProcessPlacedGrid(void);

	BOOL _PlacedGridLine(void);
	BOOL _PlacedGridRect(void);
	BOOL _PlacedGridCross(void);
	BOOL _PlacedGridX(void);
	BOOL _PlacedGridU(void);
	BOOL _PlacedGridSingle(void);

	BOOL _TryPlaceSingleGrid(INT64 x, INT64 y);
#endif //_ROBOT

private:
	MISSILE_DATA		m_MissileData;
	SPELL_ENTRY			m_SpellData;
	ExtraParam			m_ExtraSpellParam;
	UINT32				m_dwOwnerID;
	INT32				m_nCollisionCount;
	INT32				m_nLifeTimeFrm;
	CSimpleTimer		m_LifeTimeTimer;
	CSimpleTimer		m_IntervalTimer;
	CTargetScanner		m_Scanner;
	UINT32				m_dwLockedTargetID;
	UINT32				m_dwInitFrm;

	_MoveFunc			m_MoveFunc[mmtTotal];
	INT32				m_nMoveTimer;
	INT64				m_llDestX;
	INT64				m_llDestY;
	INT64				m_llDestZ;
	BOOL				m_bHitTarget;

	INT32				m_nSpellSerial;
	INT32				m_nCastSerial;
	INT32				m_nEffectSerial;
	UINT32				m_dwLastTargetID;

	CCharacter*			m_poPendingChar;

	typedef std::list<MISSILE_PLACED_GRID> TGridList;
	TGridList			m_PlacedGridList;

	typedef std::list<UINT32> TAffectedList;
	TAffectedList		m_AffectedList;

	typedef std::list<CBullet*> TBulletList;
	TBulletList m_BulletList;
	TBulletList::iterator m_BulletItr;
};

inline INT32 CMissile::GetTemplateID(void)
{
	return m_MissileData.m_nTemplateID;
}

inline INT32 CMissile::GetAttr(INT32 eAttrType)
{
	LOG_PROCESS_ERROR(eAttrType > matDefault && eAttrType < matTotal);

	return m_MissileData.m_nAttr[eAttrType];
Exit0:
	return m_MissileData.m_nAttr[matDefault];
}

void CMissile::SetAttr(INT32 eAttrType, INT32 nValue)
{
	LOG_PROCESS_ERROR(eAttrType > matDefault && eAttrType < matTotal);

	m_MissileData.m_nAttr[eAttrType] = nValue;
Exit0:
	return;
}

inline INT64 CMissile::GetDestX(void)
{
	return m_llDestX;
}

inline INT64 CMissile::GetDestY(void)
{
	return m_llDestY;
}

inline INT64 CMissile::GetDestZ(void)
{
	return m_llDestZ;
}

inline UINT32 CMissile::GetOwnerID(void)
{
	return m_dwOwnerID;
}

inline UINT32 CMissile::GetLockedTargetID(void)
{
	return m_dwLockedTargetID;
}

inline const SPELL_ENTRY* CMissile::GetSpellData(void)
{
	return &m_SpellData;
}

inline ExtraParam* CMissile::GetSpellExParam(void)
{
	return &m_ExtraSpellParam;
}

inline INT32 CMissile::GetCollisionCount(void)
{
	return m_nCollisionCount;
}

inline void CMissile::AddCollisionCount(void)
{
	m_nCollisionCount++;
}

inline CTargetScanner& CMissile::GetScanner(void)
{
	return m_Scanner;
}

inline INT32 CMissile::GetLifeTimeFrm(void)
{
//	return CONVERT_TIME(m_MissileData.m_nAttr[matLifeTime]);
	return m_nLifeTimeFrm;
}

inline INT32 CMissile::GetIntervalFrm(void)
{
	return CONVERT_TIME(m_MissileData.m_nAttr[matInterval]);
}

inline INT32 CMissile::GetDelayFrm(void)
{
	return CONVERT_TIME(m_MissileData.m_nAttr[matDelay]);
}

inline INT32 CMissile::GetSpellSerial(void)
{
	return m_nSpellSerial;
}

inline INT32 CMissile::GetCastSerial(void)
{
	return m_nCastSerial;
}

inline INT32 CMissile::GetEffectSerial(void)
{
	return m_nEffectSerial;
}

inline void CMissile::HitTarget(BOOL bVal)
{
	m_bHitTarget = bVal;
}

inline INT32 CMissile::GetSpellAttr(INT32 eAttrType)
{
	LOG_PROCESS_ERROR(eAttrType > satInvalid && eAttrType < satTotal);

	return m_SpellData.m_nAttrTable[eAttrType];
Exit0:
	return -1;
}

inline void CMissile::SetSpellAttr(INT32 eAttrType, INT32 nValue)
{
	LOG_PROCESS_ERROR(eAttrType > satInvalid && eAttrType < satTotal);

	m_SpellData.m_nAttrTable[eAttrType] = nValue;
Exit0:
	return;
}

inline void CMissile::BeginBullet(void)
{
	m_BulletItr = m_BulletList.begin();
}

inline CBullet* CMissile::NextBullet(void)
{
	CBullet* poBullet = NULL;

	PROCESS_ERROR(m_BulletItr != m_BulletList.end());

	poBullet = *m_BulletItr;
	++m_BulletItr;

	return poBullet;
Exit0:
	return NULL;
}

inline void CMissile::AddBullet(CBullet* poBullet)
{
	m_BulletList.push_back(poBullet);
}

inline CCharacter* CMissile::GetPendingChar(void)
{
	return m_poPendingChar;
}

#endif	// _MISSILE_H_

